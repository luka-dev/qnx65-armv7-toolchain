#!/bin/sh
# Run an armle-v7 binary on real QNX 6.5 under QEMU and report what it printed
# plus its exit status.
#
# Compiling proves nothing about the bug that started all this: gas 2.19
# encoded vmls/vnmla/vnmls with a flipped sign, which builds perfectly and only
# produces wrong NUMBERS. So the toolchain needs a way to actually run things.
#
#   tests/qemu-run.sh <binary> [variant]     variant default: 8.5
#
# Pieces (tests/qemu/, all built once from the QEMU BSP in Refferences):
#   startup-virt   the board's startup, rebuilt against the BSP's libstartup -
#                  the SDP's own 2010 libstartup has no Cortex-A15 support and
#                  the boot dies with "Unsupported CPUID"
#   libstartup.a   same library; mkifs relinks the relocatable startup with it
#   devc-serdebug  serial driver, so the program's stdout reaches the console
#   u-boot.bin     loads the IFS at 0x40200000 and jumps to it
set -eu
HERE=$(cd "$(dirname "$0")" && pwd)
BIN=${1:?usage: qemu-run.sh <binary> [variant]}
VAR=${2:-8.5}
IMG=qnx65-armv7-toolchain:$VAR
Q=$HERE/qemu
command -v qemu-system-arm >/dev/null || { echo "qemu-system-arm not installed" >&2; exit 1; }
docker image inspect "$IMG" >/dev/null 2>&1 || { echo "$IMG not built" >&2; exit 1; }

WORK=$(mktemp -d); trap 'rm -rf "$WORK"' EXIT
NAME=$(basename "$BIN")
cp "$BIN" "$WORK/$NAME"
cp "$Q/startup-virt" "$Q/libstartup.a" "$Q/devc-serdebug" "$WORK/"

# mkifs needs libc and procnto from the sysroot; take them from the image.
cat > "$WORK/test.build" <<EOF
[linker="(40;1;)qcc -bootstrap -nostdlib -Wl,--no-keep-memory -Vgcc_ntoarmv7%(m!=3,%(m!=6,%(e==0, -EL%)%(e==1, -EB%)%)%)%(h!=0, -Wl,-Ttext -Wl,0x%t%)%(d!=0, -Wl,-Tdata -Wl,0x%d%) -o%o %i %[M -L%^i -Wl,-uinit_%n -lmod_%n%] /w/libstartup.a -L/opt/qnx650/target/qnx6/armle-v7/lib -L/opt/qnx650/target/qnx6/armle-v7/usr/lib -llzo -lucl -ldrvr"]
[linker="(40;2;)cp %i %o"]
[image=0x40200000]
[virtual=armle-v7,raw] .bootstrap = {
    startup-virt -v -S
    PATH=:/proc/boot LD_LIBRARY_PATH=:/proc/boot procnto-smp -vvv
}
[+script] .script = {
    procmgr_symlink ../../proc/boot/libc.so.3 /usr/lib/ldqnx.so.2
    slogger
    pipe
    devc-serdebug -e -F -S
    waitfor /dev/ser1 4
    reopen /dev/ser1
    display_msg "@@QNXRUN-START@@"
    $NAME
    display_msg "@@QNXRUN-END@@"
}
[type=link] /usr/lib/ldqnx.so.2=/proc/boot/libc.so.3
[perms=+r,+x]
libc.so.3
libm.so.2
procnto-smp
devc-serdebug
slogger
pipe
$NAME
EOF

docker run --rm --platform=linux/amd64 -v "$WORK":/w -w /w "$IMG" sh -c '
T=/opt/qnx650/target/qnx6/armle-v7
cp $T/lib/libc.so.3 $T/lib/libm.so.2 $T/boot/sys/procnto-smp /w/ 2>/dev/null || true
cp $T/sbin/slogger $T/bin/pipe /w/ 2>/dev/null || true
# a dynamically linked C++ binary also needs libstdc++; ship it when present
if [ -f /w/NEEDS_CXX ]; then cp $T/usr/lib/libstdc++.so.6 /w/ 2>/dev/null || true; fi
export MKIFS_PATH=/w:$T/boot/sys:$T/bin:$T/lib:$T/usr/lib
mkifs test.build ifs.bin' >/dev/null 2>&1 || { echo "mkifs failed" >&2; exit 1; }

mkdir -p "$WORK/fat"; mv "$WORK/ifs.bin" "$WORK/fat/"
LOG="$WORK/qemu.log"
# u-boot eats the first keystrokes for its autoboot prompt, hence the leading
# newline and the pauses - without them the first command arrives truncated.
( printf '\n'; sleep 4
  printf 'virtio scan\n'; sleep 2
  printf 'fatload virtio 0:1 0x40200000 ifs.bin\n'; sleep 3
  printf 'go 0x40200000\n'; sleep "${QEMU_RUN_SECS:-20}" ) | \
  timeout "${QEMU_TIMEOUT:-70}" qemu-system-arm -M virt -m 256 -cpu cortex-a15 \
    -bios "$Q/u-boot.bin" -drive file=fat:rw:"$WORK/fat",format=raw,media=disk \
    -display none -serial stdio > "$LOG" 2>&1 || true

if ! grep -q '@@QNXRUN-START@@' "$LOG"; then
    echo "=== boot did not reach the program ===" >&2
    tail -15 "$LOG" >&2; exit 1
fi
# The start marker shares a line with startup's own last output, so strip
# everything up to it rather than dropping the line.
awk '
  /@@QNXRUN-START@@/ { sub(/.*@@QNXRUN-START@@/, ""); inside = 1 }
  /@@QNXRUN-END@@/   { sub(/@@QNXRUN-END@@.*/, ""); if (length($0)) print; exit }
  /@@QNXRUN-EXIT=/     { next }
  inside && length($0) { print }
' "$LOG"
[ -n "${QEMU_KEEP_LOG:-}" ] && cp "$LOG" "$QEMU_KEEP_LOG"

# Exit with the program's own status so this is usable as a test, not just as a
# viewer. QNX prints "Process N (name) exited status=X" when a process ends;
# no such line means it never finished (crash, hang, or the boot stalled).
# mkifs's .script parser is not a shell - `sh -c "prog; echo $?"` does not work
# there, and procnto does not announce process exits in this configuration, so
# there is no exit CODE to report. What we can tell is whether the script got
# past the program: reaching the end marker means it returned instead of
# hanging or taking the system down. Correctness itself is judged by the
# program's own output (see vfp-runtime.sh).
if ! grep -q '@@QNXRUN-END@@' "$LOG"; then
    echo "warning: program did not return - hung, or crashed hard" >&2
    exit 1
fi
# With procnto -vvv the kernel does report process exits, so a real exit code
# is available after all - use it when present.
code=$(grep -oE "Process [0-9]+ \($NAME\) exited status=[0-9]+" "$LOG" | tail -1 | grep -oE '[0-9]+$')
# procnto -vvv announces abnormal termination; without that verbosity it says
# nothing at all and a segfaulting program looks like a clean run.
if [ -n "${code:-}" ] && [ "$code" != 0 ]; then
    echo "(exit status $code)" >&2
    exit "$code"
fi
if grep -qE 'terminated SIG' "$LOG"; then
    grep -oE 'Process [0-9]+ \([^)]*\) terminated SIG[A-Z]+[^ ]*( [a-z]+=[0-9a-fx]+)*' "$LOG" | tail -1 >&2
    exit 1
fi
exit 0
