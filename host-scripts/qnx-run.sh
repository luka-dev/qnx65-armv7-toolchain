#!/bin/sh
# Run the QNX 6.5 / armle-v7 polyglot cross-toolchain (C/C++ GCC 8.5.0 +
# Go GOOS=qnx + Rust armv7-nto-qnx650) on the current directory: mounts the cwd
# as /src inside the qnx65-armv7-toolchain image and runs the command there.
#
#   ./qnx-run.sh                                                  # interactive shell
#   ./qnx-run.sh arm-unknown-nto-qnx6.5.0eabi-g++ -std=c++17 -O2 a.cpp -o a
#   ./qnx-run.sh arm-unknown-nto-qnx6.5.0eabi-gcc -O2 -mfpu=neon a.c -o a
#   ./qnx-run.sh sh -c 'GOOS=qnx GOARCH=arm GOARM=7 go build ./...'
#   ./qnx-run.sh build-std path/to/crate                         # Rust full-std
#   ./qnx-run.sh build                                           # (re)build the image
#   ./qnx-run.sh build 8.5                                       # C/C++ only
#   ./qnx-run.sh build 4.9-go                                    # 4.9 + Go
#   ./qnx-run.sh build 4.4                                       # stock SDP compiler
#   ./qnx-run.sh -V4.9   arm-unknown-nto-qnx6.5.0eabi-g++ ...    # run in a variant
#   ./qnx-run.sh -V4.4   qcc -Vgcc_ntoarmv7le_gpp ...            # stock qcc
#
# Run it from the project dir you want mounted (cwd -> /src).
#
# Compiler: arm-unknown-nto-qnx6.5.0eabi-{gcc,g++} (GCC 8.5.0), default
# -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=softfp; output ELF EABI5 v7 softfp,
# interp /usr/lib/ldqnx.so.2. Note: common headers (unistd.h, sys/types.h,
# stdio.h, ...) provide size_t; gnulib-style code that ships its own <stddef.h>
# may still need -include stddef.h (baked into cross/config.site for autotools).

IMG=qnx65-armv7-toolchain
CTX="$(cd "$(dirname "$0")/.." && pwd)"   # repo root (Dockerfile / build context)
PLAT=linux/amd64

# Variants are <ver>[-<lang>]: ver = 4.4 | 4.9 | 8.5, lang = go | rust | full.
# The compiler half is picked with --build-arg BASE, the language half with
# --target, so any combination is one build. Tag == variant name.
#   8.5-full  GCC 8.5 + gas 2.38 + Go + Rust   (also tagged :latest)
#   4.9       GCC 4.9.4 + stock gas 2.19, C/C++ only
#   4.4       the SDP's own GCC 4.4.2 + qcc
# Go/Rust are only offered on 4.9 and 8.5: the stock 4.4.2 driver rejects the
# options cgo passes (-pthread, -rdynamic), so those images would be half-dead.
variant_split() {   # sets $ver and $lang, or fails with a message
    ver=${1%%-*}
    lang=${1#"$ver"}; lang=${lang#-}
    case "$ver" in
        4.4|4.9|8.5) ;;
        *) echo "unknown compiler '$ver' (4.4|4.9|8.5)" >&2; return 1 ;;
    esac
    case "$lang" in
        ""|go|rust|full) ;;
        *) echo "unknown language variant '$lang' (go|rust|full)" >&2; return 1 ;;
    esac
    if [ "$ver" = 4.4 ] && [ -n "$lang" ]; then
        echo "4.4 is C/C++ only - Go/Rust need 4.9 or 8.5" >&2; return 1
    fi
}

build() {
    spec=${1:-8.5-full}
    variant_split "$spec" || return 1
    case "$lang" in
        "")   stage=base-env  ;;
        go)   stage=with-go   ;;
        rust) stage=with-rust ;;
        full) stage=full      ;;
    esac
    set -- docker build --platform="$PLAT" --target "$stage" \
           --build-arg "BASE=base-$ver" -t "$IMG:$spec"
    [ "$spec" = 8.5-full ] && set -- "$@" -t "$IMG:latest"
    "$@" "$CTX"
}

if [ "$1" = "build" ]; then shift; build "$1"; exit $?; fi

# -V<variant> picks which compiler to run in; without it, :latest (= 8.5-full).
# Different jobs genuinely need different compilers - old ABI-compatible hooks
# against 4.4.2/4.9, modern C++ against 8.5 - so this is a per-command choice.
case "${1:-}" in
    -V*) TAG=${1#-V}; shift ;;
    *)   TAG=${QNX_VARIANT:-latest} ;;
esac
REF="$IMG:$TAG"

if ! docker image inspect "$REF" >/dev/null 2>&1; then
    case "$TAG" in
        latest|8.5-full) build ;;
        *) echo "$REF not built - run: $0 build $TAG" >&2; exit 1 ;;
    esac || exit 1
fi

if [ $# -eq 0 ]; then set -- bash; TTY=-it; else TTY=; fi
exec docker run --rm $TTY --platform="$PLAT" -v "$PWD":/src "$REF" "$@"
