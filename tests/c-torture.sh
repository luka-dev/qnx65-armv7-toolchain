#!/bin/sh
# Compile GCC's own gcc.c-torture/execute suite with each toolchain variant and
# report pass/fail per variant. This is a compiler comparison, not a pass/fail
# gate: 4.9 is expected to lose tests that need newer C, and that difference is
# part of the result we are after.
#
# Runtime (running the binaries under QEMU) is a separate step - this one only
# answers "does it build".
#
#   tests/c-torture.sh [variant ...]      default: 4.9 8.5
#   tests/c-torture.sh --update [...]     rewrite the baselines
#
# Chasing zero failures here would mean either reimplementing DejaGnu (which
# tests the harness, not the toolchain) or deleting the inconvenient tests. What
# matters instead is that the set does not CHANGE: a test that starts failing
# after a port edit is a regression. So the expected failures are recorded in
# tests/baseline/<variant>.fails and compared by name, not by count.
#
# The suite is taken from the GCC 8.5.0 tarball (cached under tests/.cache) so
# every variant is measured against the same set of tests.
set -eu
UPDATE=0
[ "${1:-}" = --update ] && { UPDATE=1; shift; }
HERE=$(cd "$(dirname "$0")" && pwd)
BASE="$HERE/baseline"; mkdir -p "$BASE"
IMG=qnx65-armv7-toolchain
GCC_VER=8.5.0
CACHE="$HERE/.cache"
TARBALL="$CACHE/gcc-$GCC_VER.tar.xz"
SUITE="$CACHE/gcc-$GCC_VER/gcc/testsuite/gcc.c-torture/execute"
OPT=${OPT:--O2}

mkdir -p "$CACHE"
if [ ! -d "$SUITE" ]; then
    [ -f "$TARBALL" ] || {
        echo ">> fetching gcc-$GCC_VER source for its testsuite (~70MB)"
        curl -fsSL "https://ftp.gnu.org/gnu/gcc/gcc-$GCC_VER/gcc-$GCC_VER.tar.xz" -o "$TARBALL"
    }
    echo ">> extracting gcc.c-torture/execute"
    tar -C "$CACHE" -xf "$TARBALL" "gcc-$GCC_VER/gcc/testsuite/gcc.c-torture/execute"
fi
total=$(find "$SUITE" -maxdepth 1 -name '*.c' | wc -l | tr -d ' ')
echo ">> suite: $total tests, flags: $OPT"

[ $# -eq 0 ] && set -- 4.9 8.5
RES="$CACHE/results"; rm -rf "$RES"; mkdir -p "$RES"
built=""

for v in "$@"; do
    docker image inspect "$IMG:$v" >/dev/null 2>&1 || {
        echo "skip $v: image not built"; continue; }
    printf '%-6s ' "$v"
    docker run --rm --platform=linux/amd64 -v "$SUITE":/suite:ro -e OPT="$OPT" \
        "$IMG:$v" sh -c '
cd /tmp && mkdir -p out && cd out
CC=arm-unknown-nto-qnx6.5.0eabi-gcc
# -w: the suite is full of deliberate warnings; we score compile+link only.
# -lm: several tests call floor/sqrt and the real harness links libm for them.
find /suite -maxdepth 1 -name "*.c" | sort | \
  xargs -P "$(nproc)" -I{} sh -c "
    n=\$(basename {} .c)
    if $CC $OPT -w {} -o \$n.exe -lm >/dev/null 2>&1; then echo \"P \$n\"; else echo \"F \$n\"; fi
  " > results.txt
p=$(grep -c "^P " results.txt || true)
f=$(grep -c "^F " results.txt || true)
echo "pass=$p fail=$f" >&2
grep "^F " results.txt | cut -d" " -f2 | sort
' > "$RES/$v.fails" 2>&1
    tail -1 "$RES/$v.fails" >/dev/null
    # the pass/fail line went to stderr, which docker merged in: split it back out
    grep -o 'pass=[0-9]* fail=[0-9]*' "$RES/$v.fails" | head -1
    grep -v 'pass=' "$RES/$v.fails" | grep -v '^$' | sort > "$RES/$v.list"
    built="$built $v"
done

set -- $built
[ $# -ge 1 ] || exit 0

echo
echo "=== what the failures mean ==============================="
common="$RES/common"
cp "$RES/$1.list" "$common"
for v in "$@"; do comm -12 "$common" "$RES/$v.list" > "$common.tmp"; mv "$common.tmp" "$common"; done
echo "fail on EVERY variant (not a compiler difference): $(wc -l < "$common" | tr -d ' ')"
tr '\n' ' ' < "$common"; echo
for v in "$@"; do
    n=$(comm -23 "$RES/$v.list" "$common" | wc -l | tr -d ' ')
    echo
    echo "extra failures on $v: $n"
    [ "$n" -gt 0 ] && comm -23 "$RES/$v.list" "$common" | tr '\n' ' ' | sed 's/^/  /'
    echo
done

# --- baseline comparison -----------------------------------------------------
echo "=== vs baseline =========================================="
rc=0
for v in "$@"; do
    b="$BASE/$v.fails"
    if [ "$UPDATE" = 1 ]; then
        cp "$RES/$v.list" "$b"; echo "$v: baseline updated ($(wc -l < "$b" | tr -d ' ') expected failures)"
        continue
    fi
    if [ ! -f "$b" ]; then
        echo "$v: no baseline yet - run: $0 --update $v"; continue
    fi
    new=$(comm -13 "$b" "$RES/$v.list")      # failing now, not in baseline
    fixed=$(comm -23 "$b" "$RES/$v.list")    # in baseline, passing now
    if [ -n "$new" ]; then
        echo "$v: REGRESSION - newly failing: $(echo $new)"; rc=1
    fi
    [ -n "$fixed" ] && echo "$v: improved (now passing): $(echo $fixed) - rerun with --update"
    [ -z "$new" ] && [ -z "$fixed" ] && echo "$v: matches baseline ($(wc -l < "$b" | tr -d ' ') expected failures)"
done
exit $rc
