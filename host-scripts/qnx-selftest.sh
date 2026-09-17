#!/bin/sh
# Toolchain self-check: header, assembler and runtime configuration regressions.
#   1. gas encodes the VFP multiply-accumulate family correctly (2.19 did not:
#      it emitted vnmls for vmls, vmls for vnmla, vnmla for vnmls).
#   2. static libstdc++.a does not define QNX's libm float entry points - the
#      libstdc++ math_stubs recurse forever on this target.
#   3. the shared sdp/ headers still build C and C++ with both supported GCCs.
# Skipped when a variant image is not built.
# Usage: ./qnx-selftest.sh [--runtime] (QEMU required for --runtime)
set -e
IMG=qnx65-armv7-toolchain
IMAGE=${QNX_SELFTEST_IMAGE:-$IMG}
ROOT=$(CDPATH= cd -- "$(dirname "$0")/.." && pwd)
docker run --rm --platform=linux/amd64 -v "$ROOT/tests/cxx-audit":/audit:ro "$IMAGE" sh -c '
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
SO=$($P-g++ -print-file-name=libstdc++.so)
$P-nm -D --defined-only "$SO" 2>/dev/null | grep -E " [TW] (ceilf|expf|floorf|powf|sqrtf)$" \
  && { echo "FAIL: shared libstdc++ defines recursive math stubs" >&2; exit 1; }
echo "ok: shared libstdc++ leaves float math to libm"

$P-g++ -std=c++17 -O2 -c /audit/smoke.cpp -o smoke.o
# Require real libm references, not just a successful compile. fmin/round
# previously optimized into loops with no external relocation at all.
$P-nm -u smoke.o > smoke.undefined
grep -q " U fminf$" smoke.undefined
grep -q " U roundf$" smoke.undefined
echo "ok: C-header-first C++, math dispatch, mutex and chrono configuration"
'

# --- 3. the __PTRDIFF_T carrier, both directions, on every built variant ------
# sdp/ is ONE tree shared by every compiler, and sys/platform.h decides whether
# QNX's ptrdiff_t type-carrier is set.  Get it wrong either way and code breaks
# silently at compile time, in opposite directions:
#   carrier missing where QNX's <stddef.h> wins  -> C++ dies in <cstddef>
#   carrier set where GCC's <stddef.h> wins      -> C loses ptrdiff_t entirely
#                                                   (this is Go's cgo prolog)
# So test both shapes against each variant that is actually built.
for tag in 4.9 8.5; do
    docker image inspect "$IMG:$tag" >/dev/null 2>&1 || { echo "skip: $IMG:$tag not built"; continue; }
    docker run --rm --platform=linux/amd64 "$IMG:$tag" sh -c '
set -e
cd /tmp
G=arm-unknown-nto-qnx6.5.0eabi
# C, cgo-prolog shape: <stdlib.h> before <stddef.h>, then use ptrdiff_t
printf "#include <stdlib.h>\n#include <stddef.h>\nptrdiff_t f(char*a,char*b){return a-b;}\n" > c.c
$G-gcc -O2 -c c.c -o c.o 2>&1 | head -3
test -f c.o || { echo "FAIL: C lost ptrdiff_t (carrier set where GCC stddef.h wins)" >&2; exit 1; }
# C++: std::ptrdiff_t via <cstddef>
printf "#include <cstddef>\nstd::ptrdiff_t f(char*a,char*b){return a-b;}\n" > c.cpp
$G-g++ -O2 -c c.cpp -o cpp.o 2>&1 | head -3
test -f cpp.o || { echo "FAIL: C++ lost std::ptrdiff_t (carrier missing where QNX stddef.h wins)" >&2; exit 1; }
' || exit 1
    echo "ok: ptrdiff_t works both ways on $tag"
done

# --- 4. driver options cgo/portable build systems pass unconditionally -------
# -pthread and -rdynamic are no-ops / spec mappings on QNX, but a port that
# does not DECLARE them makes the driver reject them outright, which is how
# cgo fails on this target.  Cheap to check, and it caught two real gaps in
# the 4.9 port.
for tag in 4.9 8.5; do
    docker image inspect "$IMG:$tag" >/dev/null 2>&1 || { echo "skip: $IMG:$tag not built"; continue; }
    docker run --rm --platform=linux/amd64 "$IMG:$tag" sh -c '
set -e
cd /tmp; echo "int main(void){return 0;}" > o.c
for opt in -pthread -rdynamic; do
    # Checking only that a binary appeared is not enough: a driver can print
    # "unrecognized option" to stderr, ignore the flag and still exit 0. Go
    # rejects that stderr output, so the option counts only if it is silent.
    msg=$(arm-unknown-nto-qnx6.5.0eabi-gcc $opt o.c -o o 2>&1)
    test -f o || { echo "FAIL: driver rejects $opt (cgo needs it)" >&2; exit 1; }
    case "$msg" in
        *unrecognized*) echo "FAIL: driver warns on $opt - Go treats that as an error" >&2; exit 1 ;;
    esac
    rm -f o
done
' || exit 1
    echo "ok: driver accepts -pthread and -rdynamic on $tag"
done

if [ "${1:-}" = --runtime ]; then
    case "$IMAGE" in *:*) variant=${IMAGE##*:} ;; *) variant=latest ;; esac
    QNX_AUDIT_IMAGE="$IMAGE" QNX_AUDIT_GUEST_VARIANT="$variant" \
        bash "$ROOT/tests/cxx-audit/run.sh"
elif [ -n "${1:-}" ]; then
    echo "usage: $0 [--runtime]" >&2
    exit 2
fi
