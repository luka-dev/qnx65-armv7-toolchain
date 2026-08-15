#!/bin/bash
# Build the GCC 8.5.0 arm-unknown-nto-qnx6.5.0eabi cross-compiler (C++17) from
# vanilla upstream source + the port in ./port, against the QNX 6.5 sysroot.
# Forward-port of gcc/build.sh (GCC 4.9.4). Installs to $PREFIX. Runs inside
# the gcc-build Docker stage (QNX SDP + host build tools present,
# QNX_HOST/QNX_TARGET set).
#
#   build.sh <gcc-8.5.0.tar.xz> <install-prefix>
set -euxo pipefail

TGT=arm-unknown-nto-qnx6.5.0eabi
SRC_TAR=${1:?usage: build.sh <gcc-8.5.0.tar.xz> <prefix>}
PREFIX=${2:?missing install prefix}
PORT="$(cd "$(dirname "$0")/port" && pwd)"
: "${QNX_TARGET:?QNX_TARGET must be set}" "${QNX_HOST:?QNX_HOST must be set}"

WORK=/tmp/gccbuild
rm -rf "$WORK"; mkdir -p "$WORK/obj"
tar -C "$WORK" -xf "$SRC_TAR"
SRC=$(ls -d "$WORK"/gcc-8.*)

# apply the arm-nto-qnx port (config.gcc stanza, arm/nto.h, sync.md dmb, ...)
bash "$PORT/apply.sh" "$SRC"

cd "$WORK/obj"
# Mirror port/qnx-os_defines.h's Dinkum gates for libstdc++'s configure
# probes, which include QNX headers RAW (no os_defines in the chain). Without
# this the probes and the library/user view of <math.h>/<stdio.h> diverge -
# e.g. the obsolete-isinf probe found Dinkum's template isinf (raw view) while
# the library build had it disabled, leaving 'using ::isinf' dangling.
#   _HAS_C9X=1: C99 declarations visible (=> _GLIBCXX_USE_C99*, to_string/stoi)
#   _NO_CPP_INLINES: Dinkum's abs/sqrt-style C++ inlines off, exactly as
#     os_defines.h sets for every libstdc++ TU. (The classification templates
#     stay ON - the probes reach fpclassify/isnan through Dinkum's _CSTD
#     wrapper macros, and <cmath> consumes them via the __CORRECT_ISO_CPP11_
#     MATH_H_PROTO knobs in os_defines.h.)
# The -g -O2 defaults must be repeated: setting *FLAGS_FOR_TARGET replaces them.
QNX_DINKUM_GATES='-D_HAS_C9X=1 -D_NO_CPP_INLINES=1'
export CFLAGS_FOR_TARGET="-g -O2 $QNX_DINKUM_GATES"
export CXXFLAGS_FOR_TARGET="-g -O2 $QNX_DINKUM_GATES"

# -Bsymbolic for the target shared libs (i.e. libstdc++.so - libgcc is
# static-only here): under --target2=rel, .ARM.extab references to the
# library's own EXPORTED typeinfos are preemptible and ld emits R_ARM_REL32
# dynamic relocations - a type QNX 6.5's ldqnx.so.2 does not know ("unknown
# relocation type", library refuses to load). -Bsymbolic binds them locally
# so they resolve at link time (QEMU-verified: the REL32s disappear). The
# stock 4.4 libstdc++.so.6.0.13 shipped with zero dynamic relocs in extab -
# same convention. Ceiling: a global operator new/delete replacement in the
# program is not seen by allocations made INSIDE libstdc++.so; use
# -static-libstdc++ if you need that.
export LDFLAGS_FOR_TARGET='-Wl,-Bsymbolic'

# Same flag set as the 4.9 build. configure probes the REAL gas/ld 2.19, so
# feature macros (HAVE_GAS_DISCRIMINATOR, HAVE_GAS_CFI_SECTIONS_DIRECTIVE, ...)
# come out right for the old binutils automatically.
"$SRC"/configure \
  --target=$TGT --prefix="$PREFIX" --with-sysroot="$QNX_TARGET" \
  --with-gnu-as --with-gnu-ld \
  --with-arch=armv7-a --with-fpu=vfpv3-d16 --with-float=softfp \
  --enable-languages=c,c++ \
  --enable-threads=posix --disable-tls --disable-libssp \
  --enable-__cxa_atexit --enable-shared --enable-static --disable-multilib \
  --disable-nls --disable-libstdcxx-pch \
  --enable-libstdcxx-filesystem-ts \
  --disable-werror

J=$(nproc)
make -j"$J" all-gcc

# wchar_t fix: fixincludes regenerates include-fixed/stdlib.h from the QNX
# sysroot on every all-gcc; <malloc.h> pre-sets _GCC_WCHAR_T without the typedef
# so bare <stdlib.h> drops wchar_t in C - force the undef. (Idempotent; guarded,
# so if 8.5's fixincludes no longer rewrites it this is a no-op.)
F="$WORK/obj/gcc/include-fixed/stdlib.h"
if [ -f "$F" ] && ! grep -q wchar-fix "$F"; then
  sed -i 's|#if defined(__WCHAR_T)|#undef _GCC_WCHAR_T /* wchar-fix: <malloc.h> pre-set the guard w/o the typedef; force it */\n#if defined(__WCHAR_T)|' "$F"
fi

# size_t fix: fixincludes' "gnu_types" fix rewrites QNX's size_t typedef in
# unistd.h/sys/types.h under the _GCC_SIZE_T guard (GCC's own <stddef.h> guard),
# leaving size_t undefined when those are included without <stddef.h> first.
# The SDP originals are correct and that rewrite is fixincludes' ONLY change to
# these two headers, so drop the broken copies. (See gcc/build.sh for the full
# story.)
rm -f "$WORK/obj/gcc/include-fixed/unistd.h" \
      "$WORK/obj/gcc/include-fixed/sys/types.h"

make -j"$J" all-target-libgcc
make -j"$J" all-target-libstdc++-v3
make install-gcc install-target-libgcc install-target-libstdc++-v3

# Static libstdc++.a: same story as 4.9 - the shared-enabled libtool build
# produces only libstdc++.so (old_library=''), so assemble the .a from the
# convenience archives if make didn't install one. PIC objects archive fine.
AR="$QNX_HOST/usr/bin/$TGT-ar"; RANLIB="$QNX_HOST/usr/bin/$TGT-ranlib"
DEST="$PREFIX/$TGT/lib/libstdc++.a"
LV="$WORK/obj/$TGT/libstdc++-v3"
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
    compat=$(find "$LV/src/.libs" -maxdepth 1 -name '*.o' 2>/dev/null)
    "$AR" qcs "$DEST" $(find "$tmp" -name '*.o') $compat
    "$RANLIB" "$DEST"
    echo ">> created $DEST ($("$AR" t "$DEST" | wc -l) objects)"
  else
    echo ">> WARNING: no libstdc++ convenience archives found - libstdc++.a not built" >&2
  fi
fi

# C++17 <filesystem> lives in libstdc++fs.a in GCC 8 (moved into libstdc++.so
# only in GCC 9) - users link -lstdc++fs. Verify it was installed.
if ls "$PREFIX/$TGT/lib"/libstdc++fs.a >/dev/null 2>&1; then
  echo ">> libstdc++fs.a present ($(du -h "$PREFIX/$TGT/lib"/libstdc++fs.a | cut -f1))"
else
  echo ">> WARNING: libstdc++fs.a missing - std::filesystem won't link" >&2
fi

# reuse QNX's binutils: expose them where the installed gcc looks for as/ld
# ($prefix/$target/bin), so the toolchain works with no -B/PATH gymnastics.
TB="$PREFIX/$TGT/bin"; mkdir -p "$TB"
for t in as ld ar nm ranlib strip objcopy objdump readelf; do
  ln -sf "$QNX_HOST/usr/bin/$TGT-$t" "$TB/$t"
done

# strip the x86-64 host binaries (cc1/cc1plus/lto1/drivers)
find "$PREFIX" -type f -exec sh -c \
  'file "$1" | grep -q "ELF 64-bit.*x86-64" && strip "$1" 2>/dev/null || true' _ {} \;

echo ">> gcc 8.5.0 installed to $PREFIX"
