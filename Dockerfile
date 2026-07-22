# Polyglot QNX 6.5 / ARMv7 (armle-v7) cross-toolchain: C/C++ + Go + Rust.
# Single multi-stage build — one `docker build` yields an image that cross-
# compiles all three for QNX Neutrino 6.5.0 armle-v7, no VM, no external QNX.
#
#   base  qnx-sdp     : QNX 6.5 SDP tree (binutils 2.19 + armle-v7 sysroot), no gcc
#   stage gcc-build   : builds GCC 4.9.4 for the target from source (gcc/port)
#   stage go-build    : builds the GOOS=qnx GOARCH=arm port from source (make.bash)
#   stage rust-build  : rustup nightly + rust-src (custom armv7-nto-qnx650 target)
#   final qnx65-sdp-arm: base + the built GCC, Go and Rust toolchains
#
# Build:  docker build --platform=linux/amd64 -t qnx65-sdp-arm .
# Use:    docker run --rm -v "$PWD":/src qnx65-sdp-arm \
#             arm-unknown-nto-qnx6.5.0eabi-g++ -std=c++14 -O2 a.cpp -o a
#         docker run --rm -v "$PWD":/src qnx65-sdp-arm \
#             sh -c 'cd proj && GOOS=qnx GOARCH=arm GOARM=7 go build ./...'

# ──────────────────── base: QNX 6.5 SDP (binutils + sysroot, no gcc) ────────────
# Pinned by digest for reproducible builds (bullseye-slim as of 2026-07).
FROM --platform=linux/amd64 debian:bullseye-slim@sha256:cba95a21c96c1f5fc2470081829363eed57706634f7dc26e8c6712934303d57a AS qnx-sdp
# i386: QNX binutils (as/ld) are 32-bit x86. gmp/mpfr/mpc: GCC 4.9 host binaries
# link them. gcc: host C compiler for Cargo build scripts/proc-macros (NOT the
# QNX cross-gcc). curl/ca-certificates/xz: fetch Go bootstrap + rustup.
RUN dpkg --add-architecture i386 && apt-get update && \
    apt-get install -y --no-install-recommends \
        libc6:i386 libstdc++6:i386 zlib1g:i386 \
        libgmp10 libmpfr6 libmpc3 make gcc libc6-dev \
        ca-certificates curl xz-utils && \
    rm -rf /var/lib/apt/lists/*

# The QNX 6.5 SDP tree: binutils 2.19, armle-v7 sysroot, config+license.
# GCC is NOT here — it's built from source in the gcc-build stage and merged in
# the final stage.
COPY sdp/ /opt/qnx650/

COPY tools/ /opt/tools/
COPY entrypoint.sh /usr/local/bin/entrypoint
RUN chmod +x /usr/local/bin/entrypoint

ENV QNX_HOST=/opt/qnx650/host/linux/x86 \
    QNX_TARGET=/opt/qnx650/target/qnx6 \
    QNX_CONFIGURATION=/opt/qnx650/etc/qnx \
    PATH=/opt/qnx650/host/linux/x86/usr/bin:/usr/bin:/bin \
    LD_LIBRARY_PATH=/opt/qnx650/host/linux/x86/usr/lib

# ─────────────────────────── gcc-build: GCC 4.9.4 from source ──────────────────
# Rebuilds the arm-nto-qnx6.5.0eabi GCC 4.9.4 from vanilla upstream + gcc/port,
# against the SDP sysroot. Installs to /gcc-out (merged into the SDP host tree in
# the final stage). ~20-40 min. See gcc/README.md for the port + defect log.
FROM qnx-sdp AS gcc-build
RUN apt-get update && apt-get install -y --no-install-recommends \
        build-essential libgmp-dev libmpfr-dev libmpc-dev flex bison texinfo file && \
    rm -rf /var/lib/apt/lists/*
COPY gcc/ /opt/gcc-src/
ARG GCC_VER=4.9.4
RUN curl -fsSL "https://ftp.gnu.org/gnu/gcc/gcc-${GCC_VER}/gcc-${GCC_VER}.tar.bz2" -o /tmp/gcc.tar.bz2 && \
    bash /opt/gcc-src/build.sh /tmp/gcc.tar.bz2 /gcc-out && \
    rm -rf /tmp/gcc.tar.bz2 /tmp/gccbuild

# ─────────────────────────── go-build: GOOS=qnx port from source ───────────────
FROM qnx-sdp AS go-build
ARG GO_BOOTSTRAP=go1.26.4
COPY go/ /opt/go/
# Fetch the official Go as bootstrap, rebuild the patched tree with make.bash.
# CGO_ENABLED=0 keeps make.bash from needing a host C compiler; the qnx/arm
# cross uses the QNX gcc via CC at build time, not here.
RUN curl -fsSL "https://go.dev/dl/${GO_BOOTSTRAP}.linux-amd64.tar.gz" | tar -C /tmp -xz && \
    cd /opt/go/src && \
    GOROOT=/opt/go GOROOT_BOOTSTRAP=/tmp/go GOTOOLCHAIN=local CGO_ENABLED=0 ./make.bash && \
    rm -rf /tmp/go /opt/go/pkg/obj

# ─────────────────────────── rust-build: nightly + rust-src ────────────────────
FROM qnx-sdp AS rust-build
COPY rust/ /opt/rust/
ENV RUSTUP_HOME=/opt/rustup CARGO_HOME=/opt/cargo
RUN curl -fsSL https://sh.rustup.rs | \
        sh -s -- -y --default-toolchain nightly --profile minimal --component rust-src && \
    /opt/cargo/bin/rustup --version && \
    rm -rf /opt/cargo/registry/cache

# ─────────────────────────── final: qnx65-sdp-arm ─────────────────────────────
FROM qnx-sdp AS full
# GCC 4.9.4 built from source, merged into the SDP host tree (drivers, cc1/cc1plus,
# libgcc, libstdc++ headers; binutils symlinks resolve to the SDP's binutils).
COPY --from=gcc-build  /gcc-out   /opt/qnx650/host/linux/x86/usr
COPY --from=go-build   /opt/go     /opt/go
COPY --from=rust-build /opt/rustup /opt/rustup
COPY --from=rust-build /opt/cargo  /opt/cargo
COPY --from=rust-build /opt/rust   /opt/rust

ENV GOROOT=/opt/go \
    GOTOOLCHAIN=local \
    RUSTUP_HOME=/opt/rustup \
    CARGO_HOME=/opt/cargo \
    PATH=/opt/go/bin:/opt/cargo/bin:/opt/qnx650/host/linux/x86/usr/bin:/usr/bin:/bin \
    LD_LIBRARY_PATH=/opt/qnx650/host/linux/x86/usr/lib

WORKDIR /src
ENTRYPOINT ["/usr/local/bin/entrypoint"]
CMD ["bash"]
