#!/bin/sh
# Port glib -> QNX 6.5 armle-v7. mc only needs glib core + gmodule (NOT gobject/
# gio), and libffi is only a gobject dep -> we satisfy configure's mandatory
# libffi check with placeholder flags and build just the glib/ + gmodule/ subdirs.
#
#   run: docker run --rm --platform=linux/amd64 -v <ports>:/ports -w /ports \
#            qnx65-armv7-toolchain sh /ports/glib/build.sh
set -e
VER="${1:-2.40.2}"
PREFIX=/ports/sysroot

# Build-time host tools (not target libs, don't touch the cross sysroot):
#   gettext        -> msgfmt for the NLS macro
#   libglib2.0-dev -> glib-genmarshal/glib-mkenums that cross-configure needs in PATH
if ! command -v msgfmt >/dev/null 2>&1 || ! command -v glib-genmarshal >/dev/null 2>&1; then
    apt-get update >/dev/null && \
    apt-get install -y --no-install-recommends gettext libglib2.0-dev >/dev/null
fi

TB=/ports/glib/glib-"$VER".tar.xz
[ -f "$TB" ] || curl -fsSL "https://download.gnome.org/sources/glib/${VER%.*}/glib-$VER.tar.xz" -o "$TB"
rm -rf /build && mkdir /build && tar xf "$TB" -C /build
cd /build/glib-"$VER"

# --with-pcre=internal: use glib's bundled PCRE (none in the QNX sysroot).
# --with-libiconv=gnu + -I/-L/-liconv: the libiconv we ported into the sysroot.
# LIBFFI_*=" ": non-empty so PKG_CHECK_MODULES skips pkg-config and passes; the
#   flags are never used because we don't build gobject.
# -include stddef.h: the QNX size_t/stddef fix (see qnx65-porting memory).
./configure --host=arm-unknown-nto-qnx6.5.0eabi \
    --cache-file=/ports/glib/qnx.cache \
    CC=arm-unknown-nto-qnx6.5.0eabi-gcc \
    CFLAGS="-O2 -include stddef.h" \
    CPPFLAGS="-I$PREFIX/include" \
    LDFLAGS="-L$PREFIX/lib" \
    LIBS="-liconv -lsocket" \
    LIBFFI_CFLAGS=" " LIBFFI_LIBS=" " \
    --prefix="$PREFIX" \
    --enable-static --disable-shared \
    --with-pcre=internal --with-libiconv=gnu \
    --disable-nls --disable-gtk-doc-html --disable-man --disable-dtrace \
    --disable-selinux --disable-libmount --disable-fam --disable-xattr

# Build only what mc links: glib core + gmodule (skip gobject/gio -> no libffi).
make -C glib -j"$(nproc)"
make -C gmodule -j"$(nproc)"

# Install headers + static libs + the generated glibconfig.h + .pc files.
make -C glib install
make -C gmodule install
make install-pkgconfigDATA 2>/dev/null || true

echo "=== installed glib bits ==="
ls -l "$PREFIX"/lib/libglib-2.0.a "$PREFIX"/lib/libgmodule-2.0.a 2>/dev/null
ls "$PREFIX"/include/glib-2.0/glib.h "$PREFIX"/lib/glib-2.0/include/glibconfig.h 2>/dev/null
echo "OK glib -> $PREFIX"
