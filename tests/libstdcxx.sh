#!/bin/sh
# Compile the libstdc++ testsuite with each toolchain variant.
#
# This is the mass C++ check the toolchain never had: until now C++ was only
# ever exercised by a handful of hand-written programs. Compile-only, because
# the real suite links against DejaGnu harness objects (testsuite_hooks,
# __gnu_test::) that we are not reproducing - see the note on residue below.
#
#   tests/libstdcxx.sh [variant ...]     default: 4.9 8.5
#   tests/libstdcxx.sh --update [...]    rewrite the baselines
#
# Tests carrying dg-error are NEGATIVE: the source is invalid on purpose and
# rejecting it is the pass condition. Scoring them like the rest would count a
# compiler that accepts broken C++ as better, which is backwards.
#
# What the residue means (checked, not assumed):
#   performance_* (65), experimental_filesystem (26)  need the DejaGnu harness
#       we deliberately do not reproduce - they measure the harness, not us.
#   26_numerics (24)  REAL, but narrow: QNX's <xtgmath.h> collides with GNU
#       <complex> when a program defines its own arg/conj/imag/pow for its own
#       types and does `using namespace std` (26_numerics/complex/51083.cc).
#       Plain <complex>, including with <cmath>, compiles fine on 4.9 and 8.5 -
#       verified separately - so this does not affect ordinary code.
#   5 negative tests on 8.5 are still unexplained; that is the one place left
#       where the compiler might be accepting something it should reject.
#
# Chasing the count to zero is not the goal - most of what is left is not about
# the compiler at all. The baseline is, so a NEW failure stands out.
set -eu
UPDATE=0
[ "${1:-}" = --update ] && { UPDATE=1; shift; }
HERE=$(cd "$(dirname "$0")" && pwd)
IMG=qnx65-armv7-toolchain
GCC_VER=8.5.0
CACHE="$HERE/.cache"
SUITE="$CACHE/gcc-$GCC_VER/libstdc++-v3/testsuite"
BASE="$HERE/baseline"; mkdir -p "$BASE"

[ -d "$SUITE" ] || {
    echo ">> extracting libstdc++ testsuite"
    tar -C "$CACHE" -xf "$CACHE/gcc-$GCC_VER.tar.xz" "gcc-$GCC_VER/libstdc++-v3/testsuite"; }

[ $# -eq 0 ] && set -- 4.9 8.5
RES="$CACHE/cxxresults"; rm -rf "$RES"; mkdir -p "$RES"

for v in "$@"; do
    docker image inspect "$IMG:$v" >/dev/null 2>&1 || { echo "skip $v: not built"; continue; }
    case "$v" in 4.9) STD=gnu++11 ;; *) STD=gnu++17 ;; esac
    printf '%-5s (-std=%s) ' "$v" "$STD"
    docker run --rm --platform=linux/amd64 -v "$SUITE":/suite:ro \
        -v "$HERE/libstdcxx-inner.sh":/inner.sh:ro -e STD="$STD" \
        "$IMG:$v" /inner.sh > "$RES/$v.raw" 2>"$RES/$v.sum"
    cat "$RES/$v.sum"
    sort "$RES/$v.raw" > "$RES/$v.list"
done

echo
echo "=== vs baseline ==========================================="
rc=0
for v in "$@"; do
    b="$BASE/cxx-$v.fails"; l="$RES/$v.list"
    [ -f "$l" ] || continue
    if [ "$UPDATE" = 1 ]; then
        cp "$l" "$b"; echo "$v: baseline updated ($(wc -l < "$b" | tr -d ' ') expected failures)"; continue
    fi
    [ -f "$b" ] || { echo "$v: no baseline - run: $0 --update $v"; continue; }
    new=$(comm -13 "$b" "$l"); fixed=$(comm -23 "$b" "$l")
    [ -n "$new" ]   && { echo "$v: REGRESSION - newly failing:"; echo "$new" | head -20 | sed 's/^/    /'; rc=1; }
    [ -n "$fixed" ] && echo "$v: improved ($(echo "$fixed" | wc -l | tr -d ' ') now passing) - rerun with --update"
    [ -z "$new" ] && [ -z "$fixed" ] && echo "$v: matches baseline ($(wc -l < "$b" | tr -d ' ') expected failures)"
done
exit $rc
