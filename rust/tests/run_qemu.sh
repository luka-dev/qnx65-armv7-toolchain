#!/usr/bin/env bash
# Boot a QNX-6.5 std executable in QEMU and print its serial output.
# Reuses m1/stage BSP (procnto/startup/libc/devc-serdebug/sh). Local, no VM.
# Usage: ./run_qemu.sh <path-to-arm-binary> [extra /proc/boot files...]
set -euo pipefail
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BIN="${1:?usage: run_qemu.sh <binary> [extra files]}"; shift || true
NAME="$(basename "$BIN")"
STAGE="$HERE/m1/stage"; RUN="$HERE/m1"
cp "$BIN" "$STAGE/$NAME"

# generate a .build that launches $NAME
BUILD="$RUN/$NAME.build"
{
cat <<EOF
[linker="(40;1;)qcc -bootstrap -nostdlib -Wl,--no-keep-memory -Wl,-Map,/tmp/startup.map -Vgcc_nto%(m==40,arm%)%(m!=3,%(m!=6,%(e==0, -EL%)%(e==1, -EB%)%)%)%(h!=0, -Wl,-Ttext -Wl,0x%t%)%(d!=0, -Wl,-Tdata -Wl,0x%d%) -o%o %i %[M -L%^i -Wl,-uinit_%n -lmod_%n%] /opt/qnx650/target/qnx6/armle-v7/usr/lib/libstartup.a -L/opt/qnx650/target/qnx6/armle-v7/lib -L/opt/qnx650/target/qnx6/armle-v7/usr/lib -llzo -lucl -ldrvr"]
[linker="(40;2;)cp %i %o"]
[image=0x40200000]
[virtual=armle-v7,raw] .bootstrap = {
    /w/m1/stage/startup-virt -v -S
    PATH=/proc/boot LD_LIBRARY_PATH=/proc/boot:/lib
    /w/m1/stage/procnto-smp
}
[+script] .script = {
    procmgr_symlink ../../proc/boot/libc.so.3 /usr/lib/ldqnx.so.2
    /proc/boot/devc-serdebug -e -F -S
    waitfor /dev/ser1 4
    reopen /dev/ser1
    display_msg "=== $NAME IFS boot ==="
    SYSNAME=nto
    PATH=/proc/boot
    LD_LIBRARY_PATH=/proc/boot:/lib
    # entropy source for std's RandomState (HashMap) - /dev/urandom -> QNX random
    random -t
    waitfor /dev/random 4
    procmgr_symlink /dev/random /dev/urandom
    $NAME
    display_msg "--- $NAME returned ---"
}
[type=link] /usr/lib/ldqnx.so.2=/proc/boot/libc.so.3
[type=link] /dev/console=/dev/ser1
[type=link] /tmp=/dev/shmem
/proc/boot/libc.so.3=/w/m1/stage/libc.so.3
/proc/boot/libm.so.2=/w/m1/stage/libm.so.2
/proc/boot/libsocket.so.3=/w/m1/stage/libsocket.so.3
/proc/boot/devc-serdebug=/w/m1/stage/devc-serdebug
/proc/boot/waitfor=/w/m1/stage/waitfor
/proc/boot/sh=/w/m1/stage/sh
/proc/boot/libz.so.2=/w/m1/stage/libz.so.2
/proc/boot/random=/w/m1/stage/random
/proc/boot/$NAME=/w/m1/stage/$NAME
EOF
for f in "$@"; do echo "/proc/boot/$(basename "$f")=/w/m1/stage/$(basename "$f")"; cp "$f" "$STAGE/"; done
} > "$BUILD"

docker run --rm --platform=linux/amd64 -v "$HERE":/w -w /w qnx65-armv7 \
  mkifs -v "/w/m1/$NAME.build" "/w/m1/$NAME.bin" >/dev/null 2>&1 || { echo "mkifs FAILED"; exit 1; }

LOG="/tmp/${NAME}_serial.log"; rm -f "$LOG" "/tmp/qnx_${NAME}.ram"
timeout 45 qemu-system-arm -M virt,memory-backend=mem -m 2048 -cpu cortex-a15 \
  -icount shift=auto,sleep=off \
  -object memory-backend-file,id=mem,size=2048M,mem-path=/tmp/qnx_${NAME}.ram,share=on \
  -device "loader,file=$RUN/$NAME.bin,addr=0x40200000,force-raw=on,cpu-num=0" \
  -display none -serial file:"$LOG" -monitor none >/dev/null 2>&1 || true
echo "=== serial ($NAME) ==="
sed -n '/IFS boot/,$p' "$LOG" 2>/dev/null || cat "$LOG"
