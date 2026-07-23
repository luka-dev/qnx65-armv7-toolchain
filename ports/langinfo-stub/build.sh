#!/bin/sh
set -e
PREFIX=/ports/sysroot
CC=arm-unknown-nto-qnx6.5.0eabi-gcc
AR=arm-unknown-nto-qnx6.5.0eabi-ar
cd /ports/langinfo-stub
$CC -O2 -include stddef.h -c langinfo.c -o /tmp/langinfo.o
$AR rcs /tmp/liblanginfo.a /tmp/langinfo.o
mkdir -p "$PREFIX/include" "$PREFIX/lib"
cp langinfo.h "$PREFIX/include/langinfo.h"
cp /tmp/liblanginfo.a "$PREFIX/lib/liblanginfo.a"
echo "OK langinfo-stub -> $PREFIX"
