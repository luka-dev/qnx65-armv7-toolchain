#!/bin/bash
# Build the assembler from a modern binutils for arm-unknown-nto-qnx6.5.0eabi.
#
# WHY: the SDP ships gas 2.19.1 (2007), which MIS-ENCODES three of the four VFP
# multiply-accumulate mnemonics - it emits vnmls for vmls, vmls for vnmla and
# vnmla for vnmls. Each silently flips a sign, so any a*b+-c expression computes
# the wrong value instead of failing to build. Upstream fixed this in
# gas/config/tc-arm.c on 2009-10-29 (binutils 2.20); 2.19 predates it. GCC 4.9
# rarely formed those patterns so the bug lay dormant, but GCC 8.5 forms them
# freely and it corrupted the RetroArch menu renderer end to end.
#
# Only `as` is replaced. ld/ar/objcopy stay at the SDP's 2.19: linking was never
# implicated, and keeping the link step byte-identical limits the blast radius.
# The old assembler remains available as ...-as-2.19.
#
#   build.sh <binutils-x.y.tar.xz> <install-prefix>
set -euxo pipefail

TGT=arm-unknown-nto-qnx6.5.0eabi
SRC_TAR=${1:?usage: build.sh <binutils tarball> <prefix>}
PREFIX=${2:?missing install prefix}
: "${QNX_TARGET:?QNX_TARGET must be set}"

# Debian's make/bison ahead of the SDP's 2011-era ones.
export PATH=/usr/bin:/bin:$PATH

WORK=/tmp/binutilsbuild
rm -rf "$WORK"; mkdir -p "$WORK/obj"
tar -C "$WORK" -xf "$SRC_TAR"
SRC=$(ls -d "$WORK"/binutils-*)

cd "$WORK/obj"
"$SRC"/configure \
  --target=$TGT --prefix="$PREFIX" --with-sysroot="$QNX_TARGET" \
  --disable-nls --disable-werror --disable-sim --disable-gdb

# MAKEINFO=true: no texinfo in the image and the manuals are not wanted.
make -j"$(nproc)" MAKEINFO=true all-gas
make MAKEINFO=true install-gas

test -x "$PREFIX/bin/$TGT-as"
test -x "$PREFIX/$TGT/bin/as"
"$PREFIX/bin/$TGT-as" --version | head -1
