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
#   ./qnx-run.sh build 8.5                                       # C/C++ only variant
#   ./qnx-run.sh build 4.4.2                                     # stock SDP compiler
#   ./qnx-run.sh -V4.9   arm-unknown-nto-qnx6.5.0eabi-g++ ...    # run in a variant
#   ./qnx-run.sh -V4.4.2 qcc -Vgcc_ntoarmv7le_gpp ...            # stock qcc
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

# Image variants: stage -> tag. `full` is the default and also gets :latest,
# which is what every other script and the README already reference.
#   full   qnx65-armv7-toolchain:8.5-full  GCC 8.5 + gas 2.38 + Go + Rust
#   8.5    qnx65-armv7-toolchain:8.5       C/C++ only - smaller, what tests/ uses
#   4.9    qnx65-armv7-toolchain:4.9       GCC 4.9.4 + stock gas 2.19 (A/B baseline)
#   4.4.2  qnx65-armv7-toolchain:4.4.2     the SDP's own compiler + qcc (A/B baseline)
variant_stage() {
    case "$1" in
        ""|full)  echo full       ;;
        8.5)      echo ctoolchain ;;
        4.9)      echo gcc49      ;;
        4.4.2)    echo stock442   ;;
        *) echo "unknown variant '$1' (full|8.5|4.9|4.4.2)" >&2; return 1 ;;
    esac
}
variant_tag() { case "$1" in ""|full) echo 8.5-full ;; *) echo "$1" ;; esac; }

build() {
    # `<ver>-full` = the full stage (Go + Rust) stacked on that compiler variant.
    case "$1" in
        *-full) base=$(variant_stage "${1%-full}") || return 1
                set -- docker build --platform="$PLAT" --target full \
                       --build-arg "FULL_BASE=$base" -t "$IMG:$1"
                "$@" "$CTX"; return $? ;;
    esac
    stage=$(variant_stage "$1") || return 1
    tag=$(variant_tag "$1")
    set -- docker build --platform="$PLAT" --target "$stage" -t "$IMG:$tag"
    [ "$tag" = 8.5-full ] && set -- "$@" -t "$IMG:latest"
    "$@" "$CTX"
}

if [ "$1" = "build" ]; then shift; build "$1"; exit $?; fi

# -V<variant> picks which compiler to run in; without it, :latest (= 8.5-full).
# Different jobs genuinely need different compilers - old ABI-compatible hooks
# against 4.4.2/4.9, modern C++ against 8.5 - so this is a per-command choice.
case "${1:-}" in
    -V*) TAG=${1#-V}; shift
         [ "$TAG" = full ] && TAG=8.5-full ;;
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
