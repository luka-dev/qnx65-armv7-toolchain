#!/usr/bin/env bash
# One-command cross-build for QNX 6.5 armv7:
#   cargo (Mac, no_std staticlib) -> ship object -> link .so with the QNX 6.5
#   gcc on the VM -> pull the .so back next to the crate.
# Rust can't host on QNX and the 6.5 toolchain is QNX-x86-only, so the link step
# runs over ssh; this script hides that behind a single invocation.
#
# Usage: ./build.sh <crate-dir> <exported-symbol> [extra ld flags e.g. -lsocket]
set -euo pipefail
export PATH="$HOME/.cargo/bin:$PATH"   # use the rustup cargo (honors rust-toolchain.toml)

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
CRATE="${1:?usage: build.sh <crate-dir> <symbol> [ld flags]}"
SYM="${2:?missing exported symbol}"
shift 2
EXTRA="$*"
NAME="$(basename "$CRATE")"
TGT="$HERE/armv7-unknown-nto-qnx650.json"
VM=root@192.168.64.16
SSHOPTS="-oHostKeyAlgorithms=+ssh-rsa -oPubkeyAcceptedAlgorithms=+ssh-rsa -oStrictHostKeyChecking=no"

echo "[1/4] cargo build ($NAME) for armv7-nto-qnx650 ..."
( cd "$HERE/$CRATE" && cargo build -Z build-std=core,alloc -Z json-target-spec --target "$TGT" --release )
AR="$HERE/$CRATE/target/armv7-unknown-nto-qnx650/release/lib${NAME}.a"

echo "[2/4] ship object to VM ..."
sshpass -p root ssh $SSHOPTS "$VM" "mkdir -p /root/xbuild/$NAME"
sshpass -p root scp $SSHOPTS "$AR" "$VM:/root/xbuild/$NAME/lib${NAME}.a" >/dev/null

echo "[3/4] link .so on QNX 6.5 VM (gcc 4.4.2) ..."
sshpass -p root ssh $SSHOPTS "$VM" \
  "export QNX_HOST=/usr/qnx650/host/qnx6/x86 QNX_TARGET=/usr/qnx650/target/qnx6; \
   export PATH=\$QNX_HOST/usr/bin:\$PATH LD_LIBRARY_PATH=\$QNX_HOST/usr/lib; \
   cd /root/xbuild/$NAME; \
   arm-unknown-nto-qnx6.5.0eabi-gcc -shared -Wl,-u$SYM -o lib${NAME}.so lib${NAME}.a -lc $EXTRA"

echo "[4/4] pull .so back ..."
sshpass -p root scp $SSHOPTS "$VM:/root/xbuild/$NAME/lib${NAME}.so" "$HERE/$CRATE/lib${NAME}.so" >/dev/null
echo "OK -> $CRATE/lib${NAME}.so"
sshpass -p root ssh $SSHOPTS "$VM" \
  "export PATH=/usr/qnx650/host/qnx6/x86/usr/bin:\$PATH; ntoarmv7-readelf -A /root/xbuild/$NAME/lib${NAME}.so 2>/dev/null | grep -iE 'FP_arch|CPU_arch:' | head -3"
