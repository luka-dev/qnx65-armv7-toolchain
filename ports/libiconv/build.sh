#!/bin/sh
# Port GNU libiconv 1.14 -> QNX 6.5 armle-v7. QNX libc has no iconv(); glib
# hard-needs it. Static-only, installs into the shared ports sysroot.
#
#   mount: host qnx-65-sdp-docker/ports -> /ports   (staging prefix lives here)
#   run:   docker run --rm --platform=linux/amd64 -v <ports>:/ports \
#              -w /ports qnx65-armv7-toolchain sh /ports/libiconv/build.sh
set -e
VER="${1:-1.14}"   # pass another version to build it: sh build.sh 1.17
PREFIX=/ports/sysroot

# Build in container FS, never on the bind mount (conftest race under emulation).
TB=/ports/libiconv/libiconv-"$VER".tar.gz
[ -f "$TB" ] || curl -fsSL "https://ftp.gnu.org/pub/gnu/libiconv/libiconv-$VER.tar.gz" -o "$TB"
rm -rf /build && mkdir /build && tar xf "$TB" -C /build
cd /build/libiconv-"$VER"

# -include stddef.h: QNX Dinkum headers don't pull <stddef.h> transitively, so
# size_t is missing in files that don't include it. GCC's own stddef.h defines
# it -- but ONLY if __SIZE_T is NOT defined (defining it tells stddef "the system
# will", and QNX's then doesn't either). So force-include, do not -D__SIZE_T.
./configure --host=arm-unknown-nto-qnx6.5.0eabi \
    CC=arm-unknown-nto-qnx6.5.0eabi-gcc \
    CFLAGS="-O2 -D__EXT -include stddef.h" \
    --prefix="$PREFIX" \
    --enable-static --disable-shared --disable-nls --disable-rpath

make -j"$(nproc)"
make install

echo "=== installed into $PREFIX ==="
ls -l "$PREFIX"/lib/libiconv.a "$PREFIX"/include/iconv.h
arm-unknown-nto-qnx6.5.0eabi-nm "$PREFIX"/lib/libiconv.a 2>/dev/null | grep -E " T (libiconv_open|iconv_open)$" | head
echo "OK libiconv -> $PREFIX"
