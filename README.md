# qnx65-armv7-toolchain

**A single Docker image that cross-compiles C/C++, Go, and Rust for QNX Neutrino
6.5.0 `armle-v7` — no QNX VM, no external SDP install.**

Everything is assembled from source in one multi-stage `docker build`: the QNX
6.5 SDP tree with a modern **GCC 4.9.4** (full C++11/14) in place of the stock
4.4.2, a from-scratch **`GOOS=qnx` Go 1.26 port**, and a **nightly Rust**
`build-std` target — all three linking through the same QNX toolchain.

```sh
docker build --platform=linux/amd64 -t qnx65-armv7-toolchain .
```

> ⚠️ **Private repository.** This tree contains proprietary QNX SDP 6.5 content
> (BlackBerry/QNX) and a license key (`etc/qnx/license/licenses`). Do **not**
> make it public or redistribute the QNX bytes. See [Licensing](#licensing).

---

## Table of contents

- [What you get](#what-you-get)
- [The target](#the-target)
- [Quick start](#quick-start)
- [Usage per language](#usage-per-language)
  - [C / C++](#c--c)
  - [Go](#go)
  - [Rust](#rust)
- [How the image is built](#how-the-image-is-built)
- [Repository layout](#repository-layout)
- [Design decisions](#design-decisions)
- [Building the image](#building-the-image)
- [In-image environment](#in-image-environment)
- [Updating / regenerating components](#updating--regenerating-components)
- [Testing on real hardware](#testing-on-real-hardware)
- [Troubleshooting](#troubleshooting)
- [Status & limitations](#status--limitations)
- [Licensing](#licensing)
- [Related projects](#related-projects)

---

## What you get

| Language | Compiler | Standard | Invocation | Output |
|----------|----------|----------|------------|--------|
| C / C++  | **GCC 4.9.4** (custom-built, replaces SDP 4.4.2) | C99 / **C++11 & C++14** | `arm-unknown-nto-qnx6.5.0eabi-{gcc,g++}` | ELF 32-bit ARM QNX exe/`.so` |
| Go       | **Go 1.26.4**, `GOOS=qnx GOARCH=arm` port | full `gc` toolchain | `GOOS=qnx GOARCH=arm GOARM=7 go build` | ELF 32-bit ARM QNX exe |
| Rust     | **nightly** rustc + `build-std` | `no_std` (core + alloc) | `cargo build -Z build-std=… --target …json` | static/`cdylib`, linked by the QNX gcc |

All three emit:

```
ELF 32-bit LSB, ARM, EABI5, dynamically linked, interpreter /usr/lib/ldqnx.so.2
```

The host binaries (compilers) run as `linux/amd64`; on Apple Silicon they run
under emulation, but the ARM **output** is native QNX regardless.

---

## The target

Ground truth, verified against the QNX 6.5 SDP and the on-device libraries:

| Property | Value |
|----------|-------|
| Target triplet | `arm-unknown-nto-qnx6.5.0eabi` |
| CPU / ABI | ARMv7-A, **EABI5**, **softfp** (base PCS — no `Tag_ABI_VFP_args`) |
| Default codegen | `-march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=softfp -mlittle-endian` |
| Dynamic linker | `/usr/lib/ldqnx.so.2` |
| Linker emulation | `armnto` (binutils 2.19) |
| Sysroot | `$QNX_TARGET = /opt/qnx650/target/qnx6`, libs under `armle-v7/lib` |
| CRT | `crt1.o crti.o crtbegin.o crtend.o crtn.o mcrt1.o` |
| On-device C++ runtime | `libstdc++.so.6.0.13` (GCC 4.4.x ABI — GCC 4.9 keeps the pre-C++11 ABI) |

**Runtime compatibility matters:** binaries built here run on a QNX **6.5**
device. QNX 6.6+ has a different libc/ABI — do not mix. GCC 4.9 was chosen
partly because it keeps the pre-C++11 libstdc++ string ABI (`_GLIBCXX_USE_CXX11_ABI`
arrived in GCC 5.1), so its C++ objects stay link-compatible with the 6.5 libs.

---

## Quick start

```sh
# 1. Build the image (needs network; ~few minutes; ~1.4 GB image)
docker build --platform=linux/amd64 -t qnx65-armv7-toolchain .

# 2. C++14
docker run --rm -v "$PWD":/src qnx65-armv7-toolchain \
    arm-unknown-nto-qnx6.5.0eabi-g++ -std=c++14 -O2 hello.cpp -o hello

# 3. Go
docker run --rm -v "$PWD":/src qnx65-armv7-toolchain \
    sh -c 'GOOS=qnx GOARCH=arm GOARM=7 CGO_ENABLED=0 go build -o hello ./...'

# 4. Rust (no_std)
docker run --rm -v "$PWD":/src qnx65-armv7-toolchain sh -c '
  cargo build -Z build-std=core,alloc -Z json-target-spec \
    --target /opt/rust/armv7-unknown-nto-qnx650.json --release'

# interactive shell
docker run --rm -it -v "$PWD":/src qnx65-armv7-toolchain bash
```

Verify any output binary:

```sh
file hello    # -> ELF 32-bit LSB executable, ARM, EABI5 …, interpreter /usr/lib/ldqnx.so.2
```

---

## Usage per language

### C / C++

The compiler is invoked **directly** by its target triplet — there is **no
`qcc`** (see [Design decisions](#why-no-qcc)). The driver sets all QNX defines
(`__QNXNTO__`, `__QNX__`, `__ELF__`, `__ARM__`) itself.

```sh
# C
arm-unknown-nto-qnx6.5.0eabi-gcc -O2 app.c -o app

# C++14 (lambdas, auto, move, <thread>, <chrono>, smart pointers …)
arm-unknown-nto-qnx6.5.0eabi-g++ -std=c++14 -O2 app.cpp -o app

# raise the FPU (default is vfpv3-d16, softfp calling convention)
arm-unknown-nto-qnx6.5.0eabi-g++ -std=c++14 -O2 -mfpu=neon app.cpp -o app

# a Makefile project
make CC=arm-unknown-nto-qnx6.5.0eabi-gcc CXX=arm-unknown-nto-qnx6.5.0eabi-g++
```

**Self-contained C++ binaries** (carry their own libstdc++ so they don't depend
on the device's older one):

```sh
arm-unknown-nto-qnx6.5.0eabi-g++ -std=c++14 -static-libstdc++ -static-libgcc app.cpp -o app
```

### Go

A **new-GOOS port** (`GOOS=qnx GOARCH=arm`). QNX is a message-passing microkernel
with no raw syscalls, so the runtime calls into `libc.so.3` (libc-call model,
like the `aix`/`solaris` ports) rather than issuing SVC instructions.

```sh
# internal-link binary (pure Go, no cgo)
GOOS=qnx GOARCH=arm GOARM=7 CGO_ENABLED=0 go build -o app ./cmd/app

# external link through the QNX gcc (needed for cgo / full runtime linkage)
GOOS=qnx GOARCH=arm GOARM=7 \
  go build -ldflags '-linkmode=external -extld=arm-unknown-nto-qnx6.5.0eabi-gcc' -o app ./cmd/app

# whole standard library builds for the target
GOOS=qnx GOARCH=arm GOARM=7 CGO_ENABLED=0 go build std
```

`GOTOOLCHAIN=local` is set in the image so `go` never tries to auto-download a
different toolchain version.

### Rust

Nightly rustc with **`-Z build-std`** — there is no prebuilt `std` for QNX, so
you compile `core`/`alloc` from source per build. Targets are described by
`rust/armv7-unknown-nto-qnx650.json` (arm/eabi, softfp, `linker =
arm-unknown-nto-qnx6.5.0eabi-gcc`, `panic = abort`, PIC/PIE).

```sh
# build a no_std staticlib for the target
cargo build -Z build-std=core,alloc -Z json-target-spec \
  --target /opt/rust/armv7-unknown-nto-qnx650.json --release

# link the produced .a into a QNX .so with the base GCC 4.9
arm-unknown-nto-qnx6.5.0eabi-gcc -shared -Wl,-u<exported_symbol> \
  -o libfoo.so target/armv7-unknown-nto-qnx650/release/libfoo.a -lc
```

`rust/rust-toolchain.toml` pins `nightly` + `rust-src`, so you don't type
`+nightly`/`-Z` toolchain flags. Full `std` is not available (QNX is not a Rust
target); this is `no_std` + `core`/`alloc` today.

---

## How the image is built

One multi-stage `Dockerfile`:

```
┌─ base: qnx-gcc ────────────────────────────────────────────────┐
│ debian:bullseye-slim (amd64 + i386 multilib)                   │
│   + libc6/libstdc++6/zlib1g:i386   (QNX binutils are 32-bit x86)│
│   + libgmp10 libmpfr6 libmpc3      (GCC 4.9 host libs)          │
│   + gcc libc6-dev                  (host cc for Cargo scripts)  │
│   + make curl ca-certificates xz-utils                         │
│ COPY sdp/  →  /opt/qnx650                                       │
│   = QNX 6.5 SDP tree with GCC 4.9.4 in place of stock 4.4.2     │
└────────────────────────────────────────────────────────────────┘
        │                                   │
        ▼ FROM qnx-gcc                       ▼ FROM qnx-gcc
┌─ go-build ───────────────┐        ┌─ rust-build ─────────────────┐
│ COPY go/ (patched src)   │        │ rustup nightly + rust-src    │
│ curl official Go bootstrap│        │ COPY rust/ (target spec)     │
│ make.bash → host go +    │        │                              │
│   qnx/arm stdlib          │        │ (links via base gcc at use)  │
└──────────────────────────┘        └──────────────────────────────┘
        │                                   │
        └───────────────┬───────────────────┘
                        ▼ FROM qnx-gcc
        ┌─ final: qnx65-armv7-toolchain ──────────────────┐
        │ COPY --from=go-build   /opt/go                  │
        │ COPY --from=rust-build /opt/rustup /opt/cargo   │
        │ ENV GOROOT, PATH=go/cargo/qnx-gcc, …            │
        └─────────────────────────────────────────────────┘
```

Go and Rust stages are `FROM qnx-gcc` because **both link through the base's
GCC 4.9** — Go's external linker and Rust's final `.a → .so` step both call
`arm-unknown-nto-qnx6.5.0eabi-gcc`. That is also why no QNX VM is needed anymore.

---

## Repository layout

```
Dockerfile          the multi-stage build described above
entrypoint.sh       prepends every /opt/tools/*/bin to PATH at container start
sdp/                the QNX 6.5 SDP base — the foundation all three languages link against:
  ├ host/             GCC 4.9.4 drivers + cc1/cc1plus (stripped), binutils 2.19 (qcc removed)
  ├ target/           armle-v7 sysroot — headers, CRT, libc/libm/libstdc++ (the 6.5 runtime)
  └ etc/              QNX config + license key
go/                 patched Go 1.26.4 source — src/ + lib/ only (~152 MB);
                    make.bash regenerates bin/ + pkg/ at build time
rust/               custom target spec armv7-unknown-nto-qnx650.json + rust-toolchain.toml + build.sh
tools/              extra drop-in compilers (each tools/<name>/bin joins PATH) — see tools/README.md
```

The three top-level inputs map 1:1 to the Docker stages: `sdp/` → `base`,
`go/` → `go-build`, `rust/` → `rust-build`. `~387 MB` in git (`sdp/` ≈ 235 MB,
`go/` ≈ 152 MB). Final image ≈ **1.4 GB**.

---

## Design decisions

### Files-based tree, not a tarball
The QNX tree is stored unpacked so it can be browsed, patched, and versioned in
git. (The stock `cc`/`CC`/`QCC` names were symlinks to `qcc` and collided by case
on macOS/APFS; with `qcc` removed this is no longer relevant.)

### GCC 4.4.2 → 4.9.4, in place
The stock SDP compiler was **fully replaced** by a custom GCC 4.9.4 built for the
same `arm-unknown-nto-qnx6.5.0eabi` target (see [qnx-gcc49](#related-projects)).
It reuses the SDP's binutils 2.19 and the 6.5 sysroot, and lives exactly where
4.4.2 did (`usr/bin` drivers, `usr/lib/gcc/.../4.9.4`, `usr/libexec/gcc/.../4.9.4`).
Gains: full **C++11/14**, better ARM/NEON codegen, `<thread>`/`<chrono>`/atomics —
while keeping the pre-C++11 libstdc++ ABI so output stays compatible with the 6.5
device libraries.

### <a name="why-no-qcc"></a>No `qcc`
`qcc` exists to select among **multiple** {arch × compiler version × C++ library}
combos via `-V`. This image has exactly one of each (armv7 × GCC 4.9 × GNU
libstdc++), so there is nothing to select. The direct driver
`arm-unknown-nto-qnx6.5.0eabi-gcc` already sets every QNX define, knows the
sysroot/CRT/specs, and links correctly — verified for C and C++14. `qcc` and its
4.4.2 `-V` config (which assumed the incompatible Dinkum C++ headers) were removed.

### armv7-only
Only the `armle-v7` (EABI) target is kept. The other SDP arches (arm-old-abi,
x86, mips, ppc, sh), the Momentics IDE, docs, and WebKit were moved out to
`Refferences/qnx650-extras/` (not in this repo), shrinking the tree from ~1.1 GB
to ~235 MB.

### Go: a real GOOS port
Not a cross-compile of existing code — QNX is not an upstream Go target. The port
adds `GOOS=qnx GOARCH=arm`, a libc-call runtime, and a hand-written ARM asm
bridge. See `go/src` and the upstream project notes.

### Rust: build-std, softfp
No prebuilt `std`; `-Z build-std` compiles `core`/`alloc` per build. The target
spec uses `+v7,+vfp3,-d32` + `llvm-floatabi:soft` = **softfp**, matching stock
QNX binaries (`Tag_VFP_arch: VFPv3-D16`, soft call ABI) so objects stay ABI-
compatible with QNX libc/libsocket.

---

## Building the image

```sh
docker build --platform=linux/amd64 -t qnx65-armv7-toolchain .
```

**Requirements**
- Docker with `linux/amd64` support (native on x86-64; emulated via QEMU/Rosetta
  on Apple Silicon).
- **Network during build** — the Go bootstrap, `rustup`, and Rust crates are
  fetched from `go.dev`, `sh.rustup.rs`, and `crates.io`. For fully offline/
  reproducible builds you would need to vendor those.

**Build arg**
- `GO_BOOTSTRAP` (default `go1.26.4`) — the official Go release fetched from
  `go.dev/dl` to bootstrap `make.bash`.

**Partial builds** (handy while iterating):

```sh
docker build --platform=linux/amd64 --target qnx-gcc     -t qnx65-gcc .   # C/C++ only
docker build --platform=linux/amd64 --target go-build    -t _go .          # + Go
docker build --platform=linux/amd64 --target rust-build  -t _rust .        # + Rust toolchain
```

---

## In-image environment

Already set in the final image:

```
QNX_HOST=/opt/qnx650/host/linux/x86
QNX_TARGET=/opt/qnx650/target/qnx6
QNX_CONFIGURATION=/opt/qnx650/etc/qnx
GOROOT=/opt/go
GOTOOLCHAIN=local
RUSTUP_HOME=/opt/rustup
CARGO_HOME=/opt/cargo
PATH=/opt/go/bin:/opt/cargo/bin:/opt/qnx650/host/linux/x86/usr/bin:/usr/bin:/bin
LD_LIBRARY_PATH=/opt/qnx650/host/linux/x86/usr/lib
```

Drop extra compilers into `tools/<name>/` (each with a `bin/`); `entrypoint.sh`
adds them to `PATH` at container start — works for baked-in `COPY` and for a
runtime `-v host:/opt/tools` mount. See `tools/README.md`.

---

## Updating / regenerating components

- **C/C++ (GCC 4.9.4)** — rebuilt by the `qnx-gcc49` project (bring-up scripts +
  the `arm/nto.h` port), then its `out/` is laid into `sdp/host/`. Host binaries
  are stripped to keep size down.
- **Go** — bump the patched tree in `go/src`; `make.bash` rebuilds at
  `docker build`. Only `src/` + `lib/` are vendored; `bin/` and `pkg/` regenerate.
- **Rust** — edit `rust/armv7-unknown-nto-qnx650.json` or bump the pinned nightly
  in `rust/rust-toolchain.toml`.

---

## Testing on real hardware

The compilers are `linux/amd64` and cannot execute ARM QNX output directly.
Use the QEMU cortex-a15 target (real `procnto` + `libc.so.3`) from the sibling
`qnx-gl-passthrough` project, or a physical QNX 6.5 board, to run and validate.
Package binaries into a bootable image with the QNX `mkifs`/`mkefs` tools.

---

## Troubleshooting

- **`Unknown EABI object attribute 34`** during link — cosmetic. Binutils 2.19
  doesn't recognize a newer EABI attribute tag emitted by GCC 4.9 / LLVM; the
  linker skips it and the binary is correct.
- **Rust: `linker cc not found` / `cannot open Scrt1.o`** — the image needs a
  *host* C toolchain (`gcc` + `libc6-dev`) for Cargo build scripts and
  proc-macros; both are installed in the base. (This is separate from the QNX
  cross-gcc.)
- **Rust: `.json target specs require -Zjson-target-spec`** — pass
  `-Z json-target-spec` (already in the examples).
- **Go tries to download a toolchain** — ensure `GOTOOLCHAIN=local` (set in the
  image).
- **Binary won't resolve libc on device** with pure internal linking — use
  external linking (`-linkmode=external -extld=arm-unknown-nto-qnx6.5.0eabi-gcc`).

---

## Status & limitations

- **C/C++** — complete. C99 + C++11/14, verified building and linking.
- **Go** — the `GOOS=qnx` port compiles and the full stdlib builds for `qnx/arm`;
  internal-link binaries are produced. Full on-device runtime coverage (cgo,
  external-link defaults) is the ongoing work of the upstream port.
- **Rust** — `no_std` (`core` + `alloc`) via `build-std`, verified building and
  linking a QNX `.so`. No `std`.
- **One arch** — `armle-v7` only. Other arches live in `Refferences/qnx650-extras/`.

---

## Licensing

QNX SDP 6.5.0 and its toolchain, headers, libraries, and the license key under
`etc/qnx/license/licenses` are **proprietary** (BlackBerry/QNX). This repository
is **private** and must stay private; do not redistribute the QNX content. The
build glue (`Dockerfile`, `entrypoint.sh`, scripts, this README) is your own, but
it is useless without a legally obtained QNX 6.5 tree.

GCC and binutils are GPL; the Go and Rust ports follow their respective upstream
licenses.

---

## Related projects

- **`qnx-gcc49`** — builds the GCC 4.9.4 cross-compiler used here (from-source
  bring-up against the 6.5 sysroot, the `arm/nto.h` port, defect log).
- **`tailscale/go-qnx65`** — the upstream of the `GOOS=qnx` Go port (`go/` here is
  its trimmed source tree).
- **`mhi2-carplay/tools/rust-qnx65`** — the upstream of the Rust target spec and
  the `no_std` milestones (dltest, ffitest, sockfwd, alloctest, altpipe).
- **`qnx-gl-passthrough`** — QEMU cortex-a15 test bed (real QNX 6.5 runtime).
