# Drop-in toolchains

Anything you put here shows up on `PATH` inside the container. One folder per
toolchain, each with a `bin/` subdir - that's the only rule.

```
tools/
  go/        -> /opt/tools/go/bin    (go, gofmt)
  rust/      -> /opt/tools/rust/bin  (rustc, cargo)
  gcc13/     -> /opt/tools/gcc13/bin (gcc, g++)
```

Add one: unpack a **linux/amd64** release into a subdir here.

```sh
# Go
curl -sL https://go.dev/dl/go1.22.5.linux-amd64.tar.gz | tar xz -C tools/   # makes tools/go/

# Rust (standalone, no rustup)
curl -sL https://static.rust-lang.org/dist/rust-1.79.0-x86_64-unknown-linux-gnu.tar.gz | tar xz
mv rust-1.79.0-*/  tools/rust/       # its bin/ has rustc+cargo
```

Remove one: delete its folder. No archive to rebuild.

## Bundled: `qcc/` (do not delete)

`tools/qcc/bin/qcc` is a small shim that ships with the repo (tracked, not a
user drop-in). It puts a `qcc` on the container `PATH` because `mkifs` build
files carry a `[linker=...]` spec that literally invokes `qcc` - and this image
replaced the stock SDP `qcc` with GCC 4.9 directly. Without it, building an IFS
image fails with `qcc: not found` when it links a relocatable startup.

It's a full qcc-to-gcc translator, not just a passthrough - qcc-based Makefiles
and hand invocations work too, not only mkifs. It maps the qcc-only options and
execs the real cross driver (`arm-unknown-nto-qnx6.5.0eabi-{gcc,g++}`):

- `-V[ver,]variant` / `-Y` -> dropped (single target), but its language is
  honoured: a C++ profile (`*cpp/*gpp/*acpp/*ecpp/*c++`) selects **g++** so C++
  links libstdc++; else gcc. C++ source extensions (`.cc/.cpp/.cxx/...`) also pick g++.
- `-bootstrap`      -> `-nostdlib`
- `-EL` / `-EB`     -> `-mlittle-endian` / `-mbig-endian`
- `-Wc,a,b`         -> `a b` (options to the compiler proper)
- `-lang-c++/-c/-asm` -> `-x c++ / c / assembler`
- `@file`           -> response file expanded and re-translated
- everything gcc already knows (`-Wl,`/`-Wa,`/`-Wp,`, `-o`, `-L`, `-l`, `-std=`,
  `-M*`, `-shared`, inputs, ...) passes through untouched

`QCC_TARGET` / `QCC_CC` / `QCC_CXX` override the drivers; `QCC_DEBUG=1` echoes the
rewritten command. This is toolchain glue - keep it tracked, unlike user drop-ins.

## Two ways to use them

Bake into the image (self-contained, rebuild on change):

    docker build --platform=linux/amd64 -t qnx65-sdp-arm .

Or mount at runtime (no rebuild - add/remove folders and just re-run):

    docker run --rm -it --platform=linux/amd64 \
        -v "$PWD/tools":/opt/tools -v "$PWD":/src qnx65-sdp-arm bash

Binaries must be `linux/amd64` (the image runs under amd64, emulated on Apple Silicon).
