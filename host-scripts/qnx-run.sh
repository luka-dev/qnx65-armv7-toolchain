#!/bin/sh
# Run the QNX 6.5 / armle-v7 polyglot cross-toolchain (C/C++ GCC 4.9.4 +
# Go GOOS=qnx + Rust armv7-nto-qnx650) on the current directory: mounts the cwd
# as /src inside the qnx65-sdp-arm image and runs the command there.
#
#   ./qnx-run.sh                                                  # interactive shell
#   ./qnx-run.sh arm-unknown-nto-qnx6.5.0eabi-g++ -std=c++14 -O2 a.cpp -o a
#   ./qnx-run.sh arm-unknown-nto-qnx6.5.0eabi-gcc -O2 -mfpu=neon a.c -o a
#   ./qnx-run.sh sh -c 'GOOS=qnx GOARCH=arm GOARM=7 go build ./...'
#   ./qnx-run.sh build-std path/to/crate                         # Rust full-std
#   ./qnx-run.sh build                                           # (re)build the image
#
# Run it from the project dir you want mounted (cwd -> /src).
#
# Compiler: arm-unknown-nto-qnx6.5.0eabi-{gcc,g++} (GCC 4.9.4), default
# -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=softfp; output ELF EABI5 v7 softfp,
# interp /usr/lib/ldqnx.so.2. Note: QNX Dinkum headers don't pull <stddef.h>
# transitively - add -include stddef.h for code that assumes it.

IMG=qnx65-sdp-arm
CTX="$(cd "$(dirname "$0")/.." && pwd)"   # repo root (Dockerfile / build context)
PLAT=linux/amd64

build() { docker build --platform="$PLAT" -t "$IMG" "$CTX"; }

if [ "$1" = "build" ]; then build; exit $?; fi
docker image inspect "$IMG" >/dev/null 2>&1 || build || exit 1

if [ $# -eq 0 ]; then set -- bash; TTY=-it; else TTY=; fi
exec docker run --rm $TTY --platform="$PLAT" -v "$PWD":/src "$IMG" "$@"
