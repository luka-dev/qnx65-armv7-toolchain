#!/bin/sh
# Compile the no-op libintl stub into the shared ports sysroot.
set -e
PREFIX=/ports/sysroot
CC=arm-unknown-nto-qnx6.5.0eabi-gcc
AR=arm-unknown-nto-qnx6.5.0eabi-ar
cd /ports/libintl-stub

$CC -O2 -include stddef.h -c libintl.c -o /tmp/libintl.o
$AR rcs /tmp/libintl.a /tmp/libintl.o
mkdir -p "$PREFIX/include" "$PREFIX/lib"
cp libintl.h "$PREFIX/include/libintl.h"
cp /tmp/libintl.a "$PREFIX/lib/libintl.a"
echo "OK libintl-stub -> $PREFIX"
