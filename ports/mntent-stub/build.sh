#!/bin/sh
set -e
PREFIX=/ports/sysroot
CC=arm-unknown-nto-qnx6.5.0eabi-gcc
AR=arm-unknown-nto-qnx6.5.0eabi-ar
cd /ports/mntent-stub
$CC -O2 -include stddef.h -c mntent.c -o /tmp/mntent.o
$AR rcs /tmp/libmntent.a /tmp/mntent.o
mkdir -p "$PREFIX/include" "$PREFIX/lib"
cp mntent.h "$PREFIX/include/mntent.h"
cp /tmp/libmntent.a "$PREFIX/lib/libmntent.a"
echo "OK mntent-stub -> $PREFIX"
