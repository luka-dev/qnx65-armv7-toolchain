#!/usr/bin/env bash
# One-command FULL-std cross-build for QNX 6.5 armv7 (executable), fully local.
#   cargo build-std (Mac) -> link with QNX 6.5 gcc 4.4.2 in docker via qnx-cc.
# Prereq once per machine: ./port/apply_std_port.sh  (patches toolchain libc+std).
# Usage: ./build_std.sh <crate-dir>
set -euo pipefail
export PATH="$HOME/.cargo/bin:$PATH"
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
CRATE="${1:?usage: build_std.sh <crate-dir>}"
TGT="$HERE/armv7-unknown-nto-qnx650.json"

# backtrace off: QNX 6.5 has no dl_iterate_phdr and only inline EHABI _Unwind_GetIP.
# qnx-cc linker shim handles -lgcc_s->-lgcc, sysroot -L, and the _Unwind_GetIP shim.
( cd "$HERE/$CRATE" && \
  RUSTFLAGS="-C linker=$HERE/qnx-cc" cargo build \
    -Z build-std=std,panic_abort -Z build-std-features= -Z json-target-spec \
    --target "$TGT" --release )
BIN="$HERE/$CRATE/target/armv7-unknown-nto-qnx650/release/$(basename "$CRATE")"
echo "OK -> $BIN"
docker run --rm --platform=linux/amd64 -v /Users/luka:/Users/luka -w "$HERE/$CRATE" qnx65-armv7 \
  ntoarm-readelf -hA "$BIN" 2>/dev/null | grep -iE 'Type:|Machine:|CPU_arch:|FP_arch' | head
