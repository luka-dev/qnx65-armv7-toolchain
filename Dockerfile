# Polyglot QNX 6.5 / ARMv7 (armle-v7) cross-toolchain: C/C++ + Go + Rust.
# Single multi-stage build — one `docker build` yields an image that cross-
# compiles all three for QNX Neutrino 6.5.0 armle-v7, no VM, no external QNX.
#
#   base  qnx-gcc     : QNX 6.5 SDP tree + GCC 4.9.4 (replaces stock 4.4.2)
#   stage go-build    : builds the GOOS=qnx GOARCH=arm port from source (make.bash)
#   stage rust-build  : rustup nightly + rust-src (custom armv7-nto-qnx650 target)
#   final qnx65-sdp-arm: base + the built Go and Rust toolchains
#
# Build:  docker build --platform=linux/amd64 -t qnx65-sdp-arm .
# Use:    docker run --rm -v "$PWD":/src qnx65-sdp-arm \
#             arm-unknown-nto-qnx6.5.0eabi-g++ -std=c++14 -O2 a.cpp -o a
#         docker run --rm -v "$PWD":/src qnx65-sdp-arm \
#             sh -c 'cd proj && GOOS=qnx GOARCH=arm GOARM=7 go build ./...'

# ─────────────────────────────── base: QNX 6.5 + GCC 4.9 ───────────────────────
FROM --platform=linux/amd64 debian:bullseye-slim AS qnx-gcc
# i386: QNX binutils (as/ld) are 32-bit x86. gmp/mpfr/mpc: GCC 4.9 host binaries
# link them. gcc: host C compiler for Cargo build scripts/proc-macros (NOT the
# QNX cross-gcc). curl/ca-certificates/xz: fetch Go bootstrap + rustup.
RUN dpkg --add-architecture i386 && apt-get update && \
    apt-get install -y --no-install-recommends \
        libc6:i386 libstdc++6:i386 zlib1g:i386 \
        libgmp10 libmpfr6 libmpc3 make gcc libc6-dev \
        ca-certificates curl xz-utils && \
    rm -rf /var/lib/apt/lists/*

# The QNX 6.5 SDP tree (host tools + GCC 4.9.4, armle-v7 sysroot, config+license).
COPY sdp/ /opt/qnx650/

COPY tools/ /opt/tools/
COPY entrypoint.sh /usr/local/bin/entrypoint
RUN chmod +x /usr/local/bin/entrypoint

ENV QNX_HOST=/opt/qnx650/host/linux/x86 \
    QNX_TARGET=/opt/qnx650/target/qnx6 \
    QNX_CONFIGURATION=/opt/qnx650/etc/qnx \
    PATH=/opt/qnx650/host/linux/x86/usr/bin:/usr/bin:/bin \
    LD_LIBRARY_PATH=/opt/qnx650/host/linux/x86/usr/lib

# ─────────────────────────── go-build: GOOS=qnx port from source ───────────────
FROM qnx-gcc AS go-build
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
FROM qnx-gcc AS rust-build
COPY rust/ /opt/rust/
ENV RUSTUP_HOME=/opt/rustup CARGO_HOME=/opt/cargo
RUN curl -fsSL https://sh.rustup.rs | \
        sh -s -- -y --default-toolchain nightly --profile minimal --component rust-src && \
    /opt/cargo/bin/rustup --version && \
    rm -rf /opt/cargo/registry/cache

# ─────────────────────────── final: qnx65-sdp-arm ─────────────────────────────
FROM qnx-gcc AS full
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
