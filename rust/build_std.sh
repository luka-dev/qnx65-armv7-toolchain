#!/usr/bin/env bash
# One-command FULL-std cross-build for QNX 6.5 armv7 (executable), in-image.
#   cargo build-std -> link with the in-image QNX gcc via qnx-cc.
# The std port (libc nto fork + std source patches) is baked into the image; run
# port/apply_std_port.sh only after a toolchain change. Usage: build_std.sh <crate-dir>
set -euo pipefail
export PATH="${CARGO_HOME:-$HOME/.cargo}/bin:$PATH"
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
arm-unknown-nto-qnx6.5.0eabi-readelf -hA "$BIN" 2>/dev/null | \
  grep -iE 'Type:|Machine:|CPU_arch:|FP_arch|Tag_ABI_align' | head
