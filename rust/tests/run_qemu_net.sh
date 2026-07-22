#!/usr/bin/env bash
# Like run_qemu.sh but brings up the QNX io-pkt TCP/IP stack (loopback) before
# launching the test. io-pkt on the hand-built qemu-virt BSP needs CACHE_MSYNC=1
# (else cache_init dlopen's a nonexistent cache-*.so and dies ESRCH - see no_std M2b).
# Usage: ./run_qemu_net.sh <path-to-arm-binary>
set -euo pipefail
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BIN="${1:?usage: run_qemu_net.sh <binary>}"
NAME="$(basename "$BIN")"
STAGE="$HERE/m1/stage"; RUN="$HERE/m1"
cp "$BIN" "$STAGE/$NAME"
BUILD="$RUN/$NAME-net.build"
cat > "$BUILD" <<EOF
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
    display_msg "=== $NAME IFS boot (net) ==="
    SYSNAME=nto
    PATH=/proc/boot
    LD_LIBRARY_PATH=/proc/boot:/lib
    # bring up the stack (loopback only): CACHE_MSYNC=1 dodges the cache-DLL dlopen
    CACHE_MSYNC=1
    io-pkt-v4 &
    waitfor /dev/socket 6
    ifconfig lo0 127.0.0.1 up
    display_msg "--- launching $NAME ---"
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
/proc/boot/io-pkt-v4=/w/m1/stage/io-pkt-v4
/proc/boot/ifconfig=/w/m1/stage/ifconfig
/proc/boot/random=/w/m1/stage/random
/proc/boot/$NAME=/w/m1/stage/$NAME
EOF
docker run --rm --platform=linux/amd64 -v "$HERE":/w -w /w qnx65-armv7 \
  mkifs -v "/w/m1/$NAME-net.build" "/w/m1/$NAME-net.bin" >/dev/null 2>&1 || { echo "mkifs FAILED"; exit 1; }
LOG="/tmp/${NAME}_net_serial.log"; rm -f "$LOG" "/tmp/qnx_${NAME}n.ram"
timeout 60 qemu-system-arm -M virt,memory-backend=mem -m 2048 -cpu cortex-a15 \
  -icount shift=auto,sleep=off \
  -object memory-backend-file,id=mem,size=2048M,mem-path=/tmp/qnx_${NAME}n.ram,share=on \
  -device "loader,file=$RUN/$NAME-net.bin,addr=0x40200000,force-raw=on,cpu-num=0" \
  -display none -serial file:"$LOG" -monitor none >/dev/null 2>&1 || true
echo "=== serial ($NAME net) ==="
sed -n '/IFS boot/,$p' "$LOG" 2>/dev/null || cat "$LOG"
