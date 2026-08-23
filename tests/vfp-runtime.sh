#!/bin/sh
# Prove on real hardware that the VFP multiply-accumulate family computes the
# right numbers - and that gas 2.19 does not.
#
# This is the test the whole assembler swap exists for. The bug produces no
# diagnostic: the build succeeds, the binary runs, it just returns a wrong
# value with a flipped sign. Only executing it catches that, which is why
# compile-only checks (tests/asm-ab.sh, c-torture) cannot replace this one.
#
# Both binaries come from the SAME compiler and the same .s file; only the
# assembler differs. Anything that differs in the output is the assembler.
set -eu
HERE=$(cd "$(dirname "$0")" && pwd)
IMG=qnx65-armv7-toolchain:8.5
W=$(mktemp -d); trap 'rm -rf "$W"' EXIT
cp "$HERE/vfp-mla.c" "$W/vfp.c"

docker run --rm --platform=linux/amd64 -v "$W":/w -w /w "$IMG" sh -c '
set -e
G=arm-unknown-nto-qnx6.5.0eabi
F="-O2 -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=softfp"
$G-gcc $F -S vfp.c -o vfp.s
grep -qE "^[[:space:]]+v(mls|nmls)" vfp.s || {
    echo "FAIL: no multiply-accumulate in the generated asm - the test would prove nothing" >&2
    exit 1; }
$G-gcc $F vfp.c -o good
$G-as-2.19 -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=softfp -meabi=5 vfp.s -o old.o
$G-gcc old.o -o old
' >/dev/null 2>&1 || { echo "build step failed" >&2; exit 1; }

echo "--- built with gas 2.38 (what we ship) ---"
good_out=$("$HERE/qemu-run.sh" "$W/good")
echo "$good_out" | sed 's/^/  /'
echo "--- same code assembled by the SDP's gas 2.19 ---"
"$HERE/qemu-run.sh" "$W/old" | sed 's/^/  /'

if echo "$good_out" | grep -q '88.0 (expect 88.0)' &&
   echo "$good_out" | grep -q -- '-88.0 (expect -88.0)' &&
   echo "$good_out" | grep -q -- '-112.0 (expect -112.0)'; then
    echo "ok: multiply-accumulate is correct at runtime with the shipped assembler"
else
    echo "FAIL: shipped assembler produces wrong arithmetic at runtime" >&2; exit 1
fi
