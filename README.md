# qnx65-sdp-arm — polyglot QNX 6.5 / ARMv7 cross-toolchain

One Docker image that cross-compiles **C/C++, Go, and Rust** for QNX Neutrino
6.5.0 `armle-v7` (32-bit, EABI5, softfp) — **no QNX VM, no external SDP install**.
Everything builds from source in a single multi-stage `docker build`.

```sh
docker build --platform=linux/amd64 -t qnx65-sdp-arm .
```

## Use

```sh
# C / C++14  (GCC 4.9.4)
docker run --rm -v "$PWD":/src qnx65-sdp-arm \
    arm-unknown-nto-qnx6.5.0eabi-g++ -std=c++14 -O2 a.cpp -o a

# Go  (GOOS=qnx port, GOARCH=arm)
docker run --rm -v "$PWD":/src qnx65-sdp-arm \
    sh -c 'GOOS=qnx GOARCH=arm GOARM=7 CGO_ENABLED=0 go build ./...'

# Rust  (nightly build-std, no_std/core+alloc; link the .a with the QNX gcc)
docker run --rm -v "$PWD":/src qnx65-sdp-arm sh -c '
  cargo build -Z build-std=core,alloc -Z json-target-spec \
    --target /opt/rust/armv7-unknown-nto-qnx650.json --release &&
  arm-unknown-nto-qnx6.5.0eabi-gcc -shared -Wl,-u<sym> \
    -o lib.so target/armv7-unknown-nto-qnx650/release/lib*.a -lc'

# interactive
docker run --rm -it -v "$PWD":/src qnx65-sdp-arm bash
```

All three emit `ELF 32-bit LSB, ARM, EABI5, interpreter /usr/lib/ldqnx.so.2`.

## How it's built (single multi-stage Dockerfile)

```
base  qnx-gcc      QNX 6.5 SDP tree + GCC 4.9.4 (replaces stock 4.4.2), binutils 2.19, sysroot
  │
  ├─ go-build      COPY go/ (patched Go source, GOOS=qnx port) → make.bash w/ downloaded bootstrap
  ├─ rust-build    rustup nightly + rust-src + COPY rust/ (custom target spec)
  │
final qnx65-sdp-arm  base + COPY --from go-build /opt/go + COPY --from rust-build the toolchain
```

Go and Rust both **link through the base's GCC 4.9** — that's why their stages
build `FROM qnx-gcc`. The build needs network (Go bootstrap, rustup, crates).

## Repo layout

```
Dockerfile          the multi-stage build above
entrypoint.sh       prepends /opt/tools/*/bin to PATH
host/ target/ etc/  QNX 6.5 SDP tree — GCC 4.9.4 + binutils 2.19 + armle-v7 sysroot (~235 MB)
go/                 patched Go source (src/ + lib/ only, ~152 MB); make.bash rebuilds bin/+pkg/
rust/               custom target spec armv7-unknown-nto-qnx650.json + toolchain.toml + build.sh
tools/              extra drop-in compilers — see tools/README.md
```

## Notes

- **C compiler is GCC 4.9.4** (full C++11/14), installed where the stock SDP 4.4.2
  lived. No `qcc` — call the triple driver `arm-unknown-nto-qnx6.5.0eabi-*` directly.
- **Only `armle-v7` (EABI) is kept**; other arches + IDE/docs/webkit moved to
  `Refferences/qnx650-extras/`.
- **Go** = a from-scratch `GOOS=qnx GOARCH=arm` port (go1.26.4) — internal-link
  binaries build; cgo / full-run paths use `-linkmode=external -extld=arm-...eabi-gcc`.
- **Rust** = nightly + `-Z build-std` (no prebuilt std → `no_std`/core+alloc today);
  compiler is stock rustc via rustup, the QNX part is just the target spec.
- Linker warning `Unknown EABI object attribute 34` is cosmetic (binutils 2.19 vs
  newer GCC/LLVM EABI tag); binaries are correct.
- Image ≈ 1.4 GB. QNX 6.5 content is proprietary (BlackBerry) — keep this repo private.
