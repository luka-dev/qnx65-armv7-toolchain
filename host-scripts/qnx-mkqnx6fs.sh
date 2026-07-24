#!/bin/sh
# Build a QNX6 Power-Safe filesystem image (fs-qnx6) with mkqnx6fsimg inside the
# qnx65-armv7-toolchain container.
#
#   ./qnx-mkqnx6fs.sh <build-file> <output.img> [extra mkqnx6fsimg args]
#
# Run it from the directory holding the build file and its inputs - that dir is
# mounted as /src, so paths in the build file must be /src/... (or point into the
# image's own /opt/qnx650 SDP). The output is a qnx6 filesystem image mountable
# on QNX 6.5 (`mount -t qnx6 <dev> <mountpoint>`, e.g. over a loopback device).
#
# mkqnx6fsimg is the QNX 6.6 mkxfs (qnx6fs mode) backported into this 6.5 SDP -
# the 6.5 mkxfs cannot build qnx6 images. Its IFS/EFS output is byte-identical to
# the 6.5 mkxfs (verified), and the qnx6 superblock it writes (magic 0x68191122)
# is the standard Power-Safe format the 6.5 fs-qnx6.so mounts. Unlike mkifs it
# does not invoke qcc, so tools/ is not mounted.
set -eu

[ $# -ge 2 ] || { echo "usage: $(basename "$0") <build-file> <output.img> [mkqnx6fsimg args]" >&2; exit 2; }
BUILD=$1; OUT=$2; shift 2

IMG=qnx65-armv7-toolchain
PLAT=linux/amd64

docker image inspect "$IMG" >/dev/null 2>&1 || \
    { echo "image $IMG missing - run: $(dirname "$0")/qnx-run.sh build" >&2; exit 1; }

exec docker run --rm --platform="$PLAT" \
    -v "$PWD":/src \
    "$IMG" sh -c "cd /src && mkqnx6fsimg $* '$BUILD' '$OUT' && ls -l '$OUT'"
