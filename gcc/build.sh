#!/bin/bash
# Build the GCC 4.9.4 arm-unknown-nto-qnx6.5.0eabi cross-compiler from vanilla
# upstream source + the port in ./port, against the QNX 6.5 sysroot. Installs to
# $PREFIX. Runs inside the gcc-build Docker stage (QNX SDP + host build tools
# present, QNX_HOST/QNX_TARGET set). Ported from qnx-gcc49/bringup.sh.
#
#   build.sh <gcc-4.9.4.tar.bz2> <install-prefix>
set -euxo pipefail

TGT=arm-unknown-nto-qnx6.5.0eabi
SRC_TAR=${1:?usage: build.sh <gcc-4.9.4.tar.bz2> <prefix>}
PREFIX=${2:?missing install prefix}
PORT="$(cd "$(dirname "$0")/port" && pwd)"
: "${QNX_TARGET:?QNX_TARGET must be set}" "${QNX_HOST:?QNX_HOST must be set}"

WORK=/tmp/gccbuild
rm -rf "$WORK"; mkdir -p "$WORK/obj"
tar -C "$WORK" -xjf "$SRC_TAR"
SRC="$WORK/gcc-4.9.4"

# apply the arm-nto-qnx port (config.gcc stanza, arm/nto.h, arm.md, libstdc++ ...)
bash "$PORT/apply.sh" "$SRC"

cd "$WORK/obj"
"$SRC/configure" \
  --target=$TGT --prefix="$PREFIX" --with-sysroot="$QNX_TARGET" \
  --with-gnu-as --with-gnu-ld \
  --with-arch=armv7-a --with-fpu=vfpv3-d16 --with-float=softfp \
  --enable-languages=c,c++ \
  --enable-threads=posix --disable-tls --disable-libssp \
  --enable-__cxa_atexit --enable-shared --enable-static --disable-multilib \
  --disable-nls --disable-libstdcxx-pch --disable-libmudflap \
  --disable-werror

J=$(nproc)
make -j"$J" all-gcc

# wchar_t fix: fixincludes regenerates include-fixed/stdlib.h from the QNX
# sysroot on every all-gcc; <malloc.h> pre-sets _GCC_WCHAR_T without the typedef
# so bare <stdlib.h> drops wchar_t in C - force the undef. (Idempotent.)
F="$WORK/obj/gcc/include-fixed/stdlib.h"
if [ -f "$F" ] && ! grep -q wchar-fix "$F"; then
  sed -i 's|#if defined(__WCHAR_T)|#undef _GCC_WCHAR_T /* wchar-fix: <malloc.h> pre-set the guard w/o the typedef; force it */\n#if defined(__WCHAR_T)|' "$F"
fi

make -j"$J" all-target-libgcc
make -j"$J" all-target-libstdc++-v3
make install-gcc install-target-libgcc install-target-libstdc++-v3

# Static libstdc++.a: the shared-enabled libtool build for this target produces
# only libstdc++.so (libstdc++.la carries old_library='' - no non-PIC archive),
# so -static-libstdc++ has nothing to link and self-contained C++ (exes and the
# .so/graft modules that need it on a device without libstdc++.so.6) is
# impossible. Assemble it from the per-standard convenience archives the shared
# lib itself was built from - PIC objects archive into a .a and link fine into
# both exes and shared objects.
AR="$QNX_HOST/usr/bin/$TGT-ar"; RANLIB="$QNX_HOST/usr/bin/$TGT-ranlib"
DEST="$PREFIX/$TGT/lib/libstdc++.a"
LV="$WORK/obj/$TGT/libstdc++-v3"
# diagnostic: what did libstdc++-v3's OWN libtool decide (root cause of old_library='')
echo ">> libstdc++-v3 static state:"
grep -E '^build_old_libs=' "$LV/libtool" 2>/dev/null | sed 's/^/     /' || true
grep -E '^old_library=' "$LV/src/libstdc++.la" 2>/dev/null | sed 's/^/     /' || true
if [ ! -f "$DEST" ]; then
  conv=$(find "$LV" -name 'lib*convenience.a' 2>/dev/null)
  if [ -n "$conv" ]; then
    echo ">> assembling static libstdc++.a from convenience archives + src compat objects:"
    echo "$conv" | sed 's/^/     /'
    tmp="$WORK/lsa"; rm -rf "$tmp"; i=0
    for a in $conv; do d="$tmp/$i"; mkdir -p "$d"; ( cd "$d" && "$AR" x "$a" ); i=$((i+1)); done
    # compatibility*.o are compiled straight into libstdc++.la (not a convenience
    # .a); include them so the archive matches a normal static-enabled libstdc++.a
    compat=$(find "$LV/src/.libs" -maxdepth 1 -name '*.o' 2>/dev/null)
    "$AR" qcs "$DEST" $(find "$tmp" -name '*.o') $compat
    "$RANLIB" "$DEST"
    echo ">> created $DEST ($("$AR" t "$DEST" | wc -l) objects)"
  else
    echo ">> WARNING: no libstdc++ convenience archives found - libstdc++.a not built" >&2
  fi
fi

# reuse QNX's binutils: expose them where the installed gcc looks for as/ld
# ($prefix/$target/bin), so the toolchain works with no -B/PATH gymnastics.
TB="$PREFIX/$TGT/bin"; mkdir -p "$TB"
for t in as ld ar nm ranlib strip objcopy objdump readelf; do
  ln -sf "$QNX_HOST/usr/bin/$TGT-$t" "$TB/$t"
done

# strip the x86-64 host binaries (cc1/cc1plus/lto1/drivers) - saves ~250 MB
find "$PREFIX" -type f -exec sh -c \
  'file "$1" | grep -q "ELF 64-bit.*x86-64" && strip "$1" 2>/dev/null || true' _ {} \;

echo ">> gcc 4.9.4 installed to $PREFIX"
