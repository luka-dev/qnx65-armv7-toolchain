# Polyglot QNX 6.5 / ARMv7 (armle-v7) cross-toolchain: C/C++ + Go + Rust.
# Single multi-stage build - one `docker build` yields an image that cross-
# compiles all three for QNX Neutrino 6.5.0 armle-v7, no VM, no external QNX.
#
#   base  qnx-sdp     : QNX 6.5 SDP tree (binutils 2.19 + armle-v7 sysroot), no gcc
#   stage gcc-build   : builds GCC 8.5.0 (C++17) for the target from source (gcc/port)
#   stage binutils-build : builds a gas that encodes ARM VFP correctly (2.19 does not)
#   stage gcc49-build : builds GCC 4.9.4 (previous generation) as an A/B baseline
#   variant gcc49     : GCC 4.9.4 + the SDP's stock gas 2.19 (no 2.38)
#   variant stock442  : the SDP's own GCC 4.4.2 + qcc (gcc/stock-4.4.2, A/B baseline)
#   variant ctoolchain: GCC 8.5.0 + gas 2.38, no Go/Rust (what tests/ runs against)
#   stage go-build    : builds the GOOS=qnx GOARCH=arm port from source (make.bash)
#   stage rust-build  : rustup nightly + rust-src (custom armv7-nto-qnx650 target)
#   final full        : ctoolchain + the Go and Rust toolchains
#
# Pick one with --target; see host-scripts/qnx-run.sh for the tag each maps to.
#
# Build:  docker build --platform=linux/amd64 -t qnx65-armv7-toolchain .
# Use:    docker run --rm -v "$PWD":/src qnx65-armv7-toolchain \
#             arm-unknown-nto-qnx6.5.0eabi-g++ -std=c++17 -O2 a.cpp -o a
#         docker run --rm -v "$PWD":/src qnx65-armv7-toolchain \
#             sh -c 'cd proj && GOOS=qnx GOARCH=arm GOARM=7 go build ./...'

# -------------------- base: QNX 6.5 SDP (binutils + sysroot, no gcc) ------------
# Pinned by digest for reproducible builds (bullseye-slim as of 2026-07).
# Which compiler variant the `full` stage stacks Go and Rust onto. Default is
# ctoolchain (GCC 8.5 + gas 2.38); --build-arg FULL_BASE=gcc49 gives 4.9-full,
# which is an experiment - Go's cgo and Rust's unwind shim were only ever made
# to work against 8.5.
ARG FULL_BASE=ctoolchain

FROM --platform=linux/amd64 debian:bullseye-slim@sha256:cba95a21c96c1f5fc2470081829363eed57706634f7dc26e8c6712934303d57a AS qnx-sdp
# i386: QNX binutils (as/ld) are 32-bit x86. gmp/mpfr/mpc: GCC host binaries
# link them. gcc: host C compiler for Cargo build scripts/proc-macros (NOT the
# QNX cross-gcc). curl/ca-certificates/xz: fetch Go bootstrap + rustup.
RUN dpkg --add-architecture i386 && apt-get update && \
    apt-get install -y --no-install-recommends \
        libc6:i386 libstdc++6:i386 zlib1g:i386 \
        libgmp10 libmpfr6 libmpc3 make gcc libc6-dev \
        ca-certificates curl xz-utils && \
    rm -rf /var/lib/apt/lists/*

# The QNX 6.5 SDP tree: binutils 2.19 + armle-v7 sysroot.
# GCC is NOT here - it's built from source in the gcc-build stage and merged in
# the final stage.
COPY sdp/ /opt/qnx650/

# NOTE: tools/ and entrypoint are intentionally NOT copied here - they go in the
# final stage (bottom) so iterating on them never invalidates this base and the
# gcc/go/rust stages built FROM it. See the tail of the file.

ENV QNX_HOST=/opt/qnx650/host/linux/x86 \
    QNX_TARGET=/opt/qnx650/target/qnx6 \
    QNX_CONFIGURATION=/opt/qnx650/etc/qnx \
    PATH=/opt/qnx650/host/linux/x86/usr/bin:/usr/bin:/bin \
    LD_LIBRARY_PATH=/opt/qnx650/host/linux/x86/usr/lib

# --------------------------- gcc-build: GCC 8.5.0 from source ------------------
# Rebuilds the arm-nto-qnx6.5.0eabi GCC 8.5.0 (full C++17) from vanilla upstream
# + gcc/port, against the SDP sysroot. Installs to /gcc-out (merged into the SDP
# host tree in the final stage). ~20-40 min. See gcc/README.md for the port +
# defect log.
FROM qnx-sdp AS gcc-build
RUN apt-get update && apt-get install -y --no-install-recommends \
        build-essential libgmp-dev libmpfr-dev libmpc-dev flex bison texinfo file && \
    rm -rf /var/lib/apt/lists/*
# Only the 8.5 recipe - NOT all of gcc/, which also holds the 4.9 port and the
# 20M stock-4.4.2 tree; a wide COPY here rebuilds GCC on any of their edits.
COPY gcc/build.sh /opt/gcc-src/build.sh
COPY gcc/port/   /opt/gcc-src/port/
ARG GCC_VER=8.5.0
ARG GCC_SHA256=d308841a511bb830a6100397b0042db24ce11f642dab6ea6ee44842e5325ed50
RUN curl -fsSL "https://ftp.gnu.org/gnu/gcc/gcc-${GCC_VER}/gcc-${GCC_VER}.tar.xz" -o /tmp/gcc.tar.xz && \
    echo "${GCC_SHA256}  /tmp/gcc.tar.xz" | sha256sum -c - && \
    bash /opt/gcc-src/build.sh /tmp/gcc.tar.xz /gcc-out && \
    rm -rf /tmp/gcc.tar.xz /tmp/gccbuild

# ------------------ binutils-build: a gas that encodes ARM correctly -----------
# The SDP ships gas 2.19.1 (2007), which mis-encodes three of the four VFP
# multiply-accumulate mnemonics - every a*b+-c silently gets a sign flipped.
# Upstream fixed it in 2.20 (2009-10-29). Only `as` is rebuilt here; ld and the
# rest stay at 2.19. See binutils/build.sh for the full write-up. ~10-20 min.
FROM qnx-sdp AS binutils-build
RUN apt-get update && apt-get install -y --no-install-recommends \
        build-essential flex bison file && \
    rm -rf /var/lib/apt/lists/*
COPY binutils/ /opt/binutils-src/
ARG BINUTILS_VER=2.38
ARG BINUTILS_SHA256=e316477a914f567eccc34d5d29785b8b0f5a10208d36bbacedcc39048ecfe024
RUN curl -fsSL "https://ftp.gnu.org/gnu/binutils/binutils-${BINUTILS_VER}.tar.xz" -o /tmp/binutils.tar.xz && \
    echo "${BINUTILS_SHA256}  /tmp/binutils.tar.xz" | sha256sum -c - && \
    bash /opt/binutils-src/build.sh /tmp/binutils.tar.xz /binutils-out && \
    rm -rf /tmp/binutils.tar.xz /tmp/binutilsbuild

# --------------------------- go-build: GOOS=qnx port from source ---------------
FROM qnx-sdp AS go-build
ARG GO_BOOTSTRAP=go1.26.4
ARG GO_BOOTSTRAP_SHA256=1153d3d50e0ac764b447adfe05c2bcf08e889d42a02e0fe0259bd47f6733ad7f
COPY go/ /opt/go/
# Fetch the official Go as bootstrap (checksum-verified), rebuild the patched
# tree with make.bash. CGO_ENABLED=0 keeps make.bash from needing a host C
# compiler; the qnx/arm cross uses the QNX gcc via CC at build time, not here.
RUN curl -fsSL "https://go.dev/dl/${GO_BOOTSTRAP}.linux-amd64.tar.gz" -o /tmp/go-boot.tar.gz && \
    echo "${GO_BOOTSTRAP_SHA256}  /tmp/go-boot.tar.gz" | sha256sum -c - && \
    tar -C /tmp -xzf /tmp/go-boot.tar.gz && rm /tmp/go-boot.tar.gz && \
    cd /opt/go/src && \
    GOROOT=/opt/go GOROOT_BOOTSTRAP=/tmp/go GOTOOLCHAIN=local CGO_ENABLED=0 ./make.bash && \
    rm -rf /tmp/go /opt/go/pkg/obj

# --------------------------- rust-build: nightly + rust-src --------------------
FROM qnx-sdp AS rust-build
COPY rust/ /opt/rust/
ENV RUSTUP_HOME=/opt/rustup CARGO_HOME=/opt/cargo
# Pin the toolchain to the same dated nightly as rust/rust-toolchain.toml so the
# install doesn't grab a floating "latest". rustup verifies component checksums.
ARG RUST_NIGHTLY=nightly-2026-07-21
RUN curl -fsSL https://sh.rustup.rs | \
        sh -s -- -y --default-toolchain "${RUST_NIGHTLY}" --profile minimal --component rust-src && \
    /opt/cargo/bin/rustup --version && \
    rm -rf /opt/cargo/registry/cache
ENV PATH=/opt/cargo/bin:/opt/qnx650/host/linux/x86/usr/bin:/usr/bin:/bin
# Bake the full-std QNX port. A first build-std pulls libc-0.2.185 into the
# registry (the link step fails - no gcc in this stage - but that's after the
# download); apply_std_port then installs the nto libc fork + std source patches
# onto the active toolchain (rustc --print sysroot). std then builds clean in the
# final stage, which has the gcc linker.
RUN cd /opt/rust/tests/stdhello && \
    ( RUSTFLAGS="-C linker=/opt/rust/qnx-cc" cargo build \
        -Z build-std=std,panic_abort -Z build-std-features= -Z json-target-spec \
        --target /opt/rust/armv7-unknown-nto-qnx650.json --release 2>/dev/null || true ) && \
    cd /opt/rust && bash port/apply_std_port.sh && \
    rm -rf /opt/rust/tests/stdhello/target /opt/cargo/registry/cache

# --------------------- gcc49-build: GCC 4.9.4 baseline from source -------------
# The previous toolchain generation, kept as an A/B baseline for tests/. Same
# port mechanism as 8.5 but its own tree (gcc/4.9/{build.sh,port}), taken from
# the gcc4.9.4-* release tag. Built against the CURRENT sdp/, not the tag's, so
# all three compilers share one sysroot and stay comparable. ~20-40 min.
FROM qnx-sdp AS gcc49-build
RUN apt-get update && apt-get install -y --no-install-recommends \
        build-essential libgmp-dev libmpfr-dev libmpc-dev flex bison texinfo file && \
    rm -rf /var/lib/apt/lists/*
COPY gcc/4.9/ /opt/gcc49-src/
ARG GCC49_VER=4.9.4
ARG GCC49_SHA256=6c11d292cd01b294f9f84c9a59c230d80e9e4a47e5c6355f046bb36d4f358092
RUN curl -fsSL "https://ftp.gnu.org/gnu/gcc/gcc-${GCC49_VER}/gcc-${GCC49_VER}.tar.bz2" -o /tmp/gcc49.tar.bz2 && \
    echo "${GCC49_SHA256}  /tmp/gcc49.tar.bz2" | sha256sum -c - && \
    bash /opt/gcc49-src/build.sh /tmp/gcc49.tar.bz2 /gcc49-out && \
    rm -rf /tmp/gcc49.tar.bz2 /tmp/gccbuild

# ------------------ variant gcc49: GCC 4.9.4 + the SDP's stock gas -------------
# Deliberately NOT given the 2.38 assembler: the point of this image is what the
# 4.9 generation actually shipped with, gas 2.19 and all.
FROM qnx-sdp AS gcc49
COPY --from=gcc49-build /gcc49-out /opt/qnx650/host/linux/x86/usr
RUN arm-unknown-nto-qnx6.5.0eabi-gcc --version | head -1 && \
    arm-unknown-nto-qnx6.5.0eabi-as  --version | head -1

# ------------------ variant stock442: the SDP's own 4.4.2 + qcc ----------------
# Restored, not built: drivers, cc1/cc1plus, libgcc, crt, fixed headers and qcc
# with its .conf profiles, exactly as the 2010 SDP shipped them. The base stage
# deliberately carries "no gcc" because 4.4.2 and 8.5 both claim the plain
# ...eabi-gcc name, so this lives in its own stage and never merges with the
# others. Exists purely as the A/B baseline for tests/ - not a working toolchain.
FROM qnx-sdp AS stock442
COPY gcc/stock-4.4.2/ /opt/qnx650/
# The 4.4.2 driver invokes a bare `as`/`ld` and its baked-in tooldir is an
# absolute path that gets pasted onto the install prefix, so it searches a
# nonexistent .../4.4.2//opt/qnx650/... and falls through to Debian's x86
# assembler, dying on "unrecognized option '-EL'" (-B and COMPILER_PATH do not
# override it). The SDP bin dir is already first on PATH, so unprefixed
# symlinks there are what the driver actually picks up. Safe in this stage
# only, which never builds host code.
RUN cd /opt/qnx650/host/linux/x86/usr/bin && \
    for t in as ld ar nm objcopy objdump ranlib strip; do \
        ln -sf arm-unknown-nto-qnx6.5.0eabi-$t $t; done && \
    arm-unknown-nto-qnx6.5.0eabi-gcc --version | head -1 && \
    as --version | head -1

# ---------------- ctoolchain: C/C++ only (GCC 8.5.0 + gas 2.38) ----------------
# The compiler half of the final image, without Go and Rust: all the test
# harness needs, and a far smaller image to spin up once per test run.
FROM qnx-sdp AS ctoolchain
# GCC 8.5.0 built from source, merged into the SDP host tree (drivers, cc1/cc1plus,
# libgcc, libstdc++ headers; binutils symlinks resolve to the SDP's binutils).
COPY --from=gcc-build  /gcc-out   /opt/qnx650/host/linux/x86/usr
# Modern gas installed beside the SDP's, then made the default by repointing the
# symlinks. 2.19 stays reachable as ...-as-2.19 for A/B comparison.
COPY --from=binutils-build /binutils-out/bin/arm-unknown-nto-qnx6.5.0eabi-as \
     /opt/qnx650/host/linux/x86/usr/bin/arm-unknown-nto-qnx6.5.0eabi-as-2.38
RUN cd /opt/qnx650/host/linux/x86/usr/bin && \
    ln -sf arm-unknown-nto-qnx6.5.0eabi-as-2.38 arm-unknown-nto-qnx6.5.0eabi-as && \
    ln -sf arm-unknown-nto-qnx6.5.0eabi-as-2.38 ntoarmv7-as && \
    ./arm-unknown-nto-qnx6.5.0eabi-as --version | head -1

# --------------------------- final: compiler + Go and Rust ---------------------
ARG FULL_BASE
FROM ${FULL_BASE} AS full
COPY --from=go-build   /opt/go     /opt/go
COPY --from=rust-build /opt/rustup /opt/rustup
COPY --from=rust-build /opt/cargo  /opt/cargo
COPY --from=rust-build /opt/rust   /opt/rust

ENV GOROOT=/opt/go \
    GOTOOLCHAIN=local \
    RUSTUP_HOME=/opt/rustup \
    CARGO_HOME=/opt/cargo \
    PATH=/opt/go/bin:/opt/cargo/bin:/opt/qnx650/host/linux/x86/usr/bin:/usr/local/bin:/usr/bin:/bin \
    LD_LIBRARY_PATH=/opt/qnx650/host/linux/x86/usr/lib

# Cross-build drivers so the cross/ files (config.site, cmake toolchain, meson
# cross file) are usable in-container end to end. autotools ./configure needs
# only sh+make+gcc (already present), so autoconf/automake aren't installed.
RUN apt-get update && apt-get install -y --no-install-recommends \
        cmake meson ninja-build pkg-config file && \
    rm -rf /var/lib/apt/lists/*

# Build the Rust std linker's unwind shim with the in-image gcc (defines the
# EHABI _Unwind_GetIP symbol std wants), and expose the one-command std builder.
RUN cd /opt/rust/shim && \
    arm-unknown-nto-qnx6.5.0eabi-gcc -c unwind_shim.c -o unwind_shim.o && \
    arm-unknown-nto-qnx6.5.0eabi-ar rcs libqnxunwind.a unwind_shim.o && \
    printf '#!/bin/sh\nexec /opt/rust/build_std.sh "$@"\n' > /usr/local/bin/build-std && \
    chmod +x /usr/local/bin/build-std

# tools/ (bundled qcc shim + user drop-ins) and the entrypoint come LAST, so
# editing them re-runs only these cheap copy layers - never the cached gcc/go/
# rust stages. (For rapid qcc-shim iteration, skip rebuilding entirely and mount
# tools/ at runtime: -v "$PWD/tools":/opt/tools.)
COPY tools/ /opt/tools/
# Cross-build helper files (autotools config.site, CMake toolchain, Meson cross
# file) at a stable path the wrappers/docs reference.
COPY cross/ /opt/qnx-cross/
COPY entrypoint.sh /usr/local/bin/entrypoint
RUN chmod +x /usr/local/bin/entrypoint

WORKDIR /src
ENTRYPOINT ["/usr/local/bin/entrypoint"]
CMD ["bash"]
