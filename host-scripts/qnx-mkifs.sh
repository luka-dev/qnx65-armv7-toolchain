#!/bin/sh
# Build a QNX IFS boot image with mkifs inside the qnx65-armv7-toolchain container.
#
#   ./qnx-mkifs.sh <build-file> <output.bin> [extra mkifs args]
#
# Run it from the directory that holds the build file and its inputs - that dir
# is mounted as /src, so paths inside the build file must be /src/... (or point
# into the image's own /opt/qnx650 SDP).
#
# Why this exists rather than calling qnx-run.sh directly: mkifs build files
# carry a `[linker=...]` spec that literally invokes `qcc`, which this image
# replaced with GCC. tools/qcc/bin/qcc translates that. This script mounts
# tools/ at runtime so the CURRENT shim is always used - a full image rebuild
# recompiles GCC from source (tens of minutes), which you do not want in the
# edit/build loop. Bake it in (`qnx-run.sh build`) only once it settles.
#
# Companion: dumpifs (in the same image) extracts an existing image, so you can
# rebuild a working boot image with one file added:
#   ./qnx-run.sh dumpifs -x /src/old.bin        # (pre-create the dirs first)
set -eu

[ $# -ge 2 ] || { echo "usage: $(basename "$0") <build-file> <output.bin> [mkifs args]" >&2; exit 2; }
BUILD=$1; OUT=$2; shift 2

IMG=qnx65-armv7-toolchain
REPO="$(cd "$(dirname "$0")/.." && pwd)"
PLAT=linux/amd64

docker image inspect "$IMG" >/dev/null 2>&1 || \
    { echo "image $IMG missing - run: $(dirname "$0")/qnx-run.sh build" >&2; exit 1; }

exec docker run --rm --platform="$PLAT" \
    -v "$PWD":/src \
    -v "$REPO/tools":/opt/tools \
    "$IMG" sh -c "cd /src && mkifs $* '$BUILD' '$OUT' && ls -l '$OUT'"
