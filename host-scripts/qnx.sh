#!/bin/sh
# Canonical entry point for the QNX 6.5 / armle-v7 polyglot cross-toolchain
# (C/C++ GCC 4.9.4 + Go GOOS=qnx + Rust armv7-nto-qnx650), image qnx65-sdp-arm.
# Mounts the current dir as /src and runs the toolchain there.
#
#   ./qnx.sh                                                   # interactive shell
#   ./qnx.sh arm-unknown-nto-qnx6.5.0eabi-g++ -std=c++14 -O2 a.cpp -o a
#   ./qnx.sh arm-unknown-nto-qnx6.5.0eabi-gcc -O2 -mfpu=neon a.c -o a
#   ./qnx.sh sh -c 'GOOS=qnx GOARCH=arm GOARM=7 go build ./...'
#   ./qnx.sh build                                             # (re)build the image
#
# Run it from the project dir you want mounted (cwd → /src), e.g.:
#   cd Tools/retroarch-qnx/src && /path/to/qnx.sh arm-...-gcc -c foo.c
#
# Compiler: arm-unknown-nto-qnx6.5.0eabi-{gcc,g++} (GCC 4.9.4), default
# -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=softfp; output ELF EABI5 v7 softfp,
# interp /usr/lib/ldqnx.so.2. Note QNX Dinkum headers don't pull <stddef.h>
# transitively — add -include stddef.h for code that assumes it (e.g. RetroArch).

IMG=qnx65-sdp-arm
CTX="$(cd "$(dirname "$0")/.." && pwd)"   # repo root (Dockerfile / build context)
PLAT=linux/amd64

build() { docker build --platform="$PLAT" -t "$IMG" "$CTX"; }

if [ "$1" = "build" ]; then build; exit $?; fi
docker image inspect "$IMG" >/dev/null 2>&1 || build || exit 1

if [ $# -eq 0 ]; then set -- bash; TTY=-it; else TTY=; fi
exec docker run --rm $TTY --platform="$PLAT" -v "$PWD":/src "$IMG" "$@"
