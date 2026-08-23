#!/bin/sh
# Runs INSIDE the container: compile every libstdc++ test once and classify it.
# Kept as its own file because quoting it through docker + xargs was a mess.
# $STD = fallback standard when the test does not name one.
cd /tmp && mkdir -p o && cd o
CXX=arm-unknown-nto-qnx6.5.0eabi-g++

one() {
    f=$1
    n=$(echo "$f" | sed 's|/suite/||; s|/|_|g; s|\.cc$||')
    # A test carrying dg-error is NEGATIVE: rejecting it is the pass condition.
    # xfail marks a test the suite itself expects to fail everywhere, so it
    # is not a negative test - treating it as one scores a correct result as
    # wrong. (27_io/fpos/mbstate_t/4_neg is exactly that.)
    if grep -q 'dg-error' "$f" && ! grep -q 'xfail' "$f"; then kind=neg; else kind=pos; fi
    # Honour the test's own -std. Many tests check that something is NOT
    # available in an older standard; forcing one -std across the suite makes
    # those compile and scores them as failures - measuring the harness, not
    # the compiler.
    tstd=$(sed -n 's/.*dg-options[^"]*"[^"]*-std=\([a-z0-9+]*\).*/\1/p' "$f" | head -1)
    [ -n "$tstd" ] && use=$tstd || use=$STD
    if $CXX -std="$use" -O1 -w -fsyntax-only -I/suite/util "$f" >/dev/null 2>&1; then
        ok=1
    else
        # Part of the suite is ISO-8859 encoded (umlauts in wide literals in
        # 22_locale). GCC then dies on "converting to execution character set",
        # which says nothing about the compiler under test - retry telling it
        # the real input encoding.
        if $CXX -std="$use" -O1 -w -fsyntax-only -finput-charset=ISO-8859-1 \
                -I/suite/util "$f" >/dev/null 2>&1; then ok=1; else ok=0; fi
    fi
    if [ "$kind" = neg ]; then
        [ "$ok" = 0 ] && echo "P neg $n" || echo "F neg $n"
    else
        [ "$ok" = 1 ] && echo "P pos $n" || echo "F pos $n"
    fi
}

if [ "${1:-}" = --one ]; then one "$2"; exit 0; fi

find /suite -name '*.cc' ! -path '*/util/*' | sort | \
    xargs -P "$(nproc)" -I{} /inner.sh --one {} > r.txt
echo "pos=$(grep -c '^P pos' r.txt)/$(grep -c ' pos ' r.txt) neg=$(grep -c '^P neg' r.txt)/$(grep -c ' neg ' r.txt)" >&2
grep '^F ' r.txt | awk '{print $2" "$3}' | sort
