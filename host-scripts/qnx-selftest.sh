#!/bin/sh
# Toolchain self-check: the two things that silently miscompile if they regress.
#   1. gas encodes the VFP multiply-accumulate family correctly (2.19 did not:
#      it emitted vnmls for vmls, vmls for vnmla, vnmla for vnmls).
#   2. static libstdc++.a does not define QNX's libm float entry points - the
#      libstdc++ math_stubs recurse forever on this target.
# Usage: ./qnx-selftest.sh   (needs the qnx65-armv7-toolchain image)
set -e
IMG=qnx65-armv7-toolchain
exec docker run --rm --platform=linux/amd64 "$IMG" sh -c '
set -e
B=/opt/qnx650/host/linux/x86/usr/bin
P=$B/arm-unknown-nto-qnx6.5.0eabi
cd /tmp

# ponytail: objdump prints the pre-UAL names; fnmacs IS vmls, fmscs IS vnmls,
# fnmscs IS vnmla. Matching on those is the check - no encoding table needed.
printf ".syntax unified\n.arch armv7-a\n.fpu vfpv3-d16\nvmla.f32 s0,s1,s2\nvmls.f32 s0,s1,s2\nvnmla.f32 s0,s1,s2\nvnmls.f32 s0,s1,s2\n" > v.s
$P-as v.s -o v.o
got=$($P-objdump -d v.o | sed -n "s/.*\t\(f[a-z]*\)\t.*/\1/p" | tr "\n" " ")
[ "$got" = "fmacs fnmacs fnmscs fmscs " ] || { echo "FAIL: gas mis-encodes VFP mla family: $got" >&2; exit 1; }
echo "ok: gas encodes vmla/vmls/vnmla/vnmls correctly ($($P-as --version | head -1))"

L=/opt/qnx650/host/linux/x86/usr/arm-unknown-nto-qnx6.5.0eabi/lib/libstdc++.a
$P-nm -A --defined-only "$L" 2>/dev/null | grep -E " [TW] (ceilf|expf|floorf|powf|sqrtf)$" \
  && { echo "FAIL: libstdc++.a defines libm float functions (math_stubs recurse)" >&2; exit 1; }
echo "ok: libstdc++.a leaves float math to libm"
'
