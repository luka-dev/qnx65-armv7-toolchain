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
    PATH=:/proc/boot LD_LIBRARY_PATH=:/proc/boot procnto-smp
}
[+script] .script = {
    procmgr_symlink ../../proc/boot/libc.so.3 /usr/lib/ldqnx.so.2
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
procnto-smp
devc-serdebug
$NAME
EOF

docker run --rm --platform=linux/amd64 -v "$WORK":/w -w /w "$IMG" sh -c '
T=/opt/qnx650/target/qnx6/armle-v7
cp $T/lib/libc.so.3 $T/boot/sys/procnto-smp /w/ 2>/dev/null || true
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
  inside && length($0) { print }
' "$LOG"
status=$(grep -o 'exited status=[0-9]*' "$LOG" | tail -1)
[ -n "$status" ] && echo "($status)"
[ -n "${QEMU_KEEP_LOG:-}" ] && cp "$LOG" "$QEMU_KEEP_LOG"
exit 0
