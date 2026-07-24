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
- `-nostartup`      -> `-nostartfiles` (no crt startup files)
- `-nopipe`         -> dropped (gcc uses temp files by default anyway)
- `-nostdlib++`     -> link via the C driver (gcc 4.9 predates gcc 9's
  `-nostdlib++`; the C driver still compiles C++ but never auto-links libstdc++)
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

    docker build --platform=linux/amd64 -t qnx65-armv7-toolchain .

Or mount at runtime (no rebuild - add/remove folders and just re-run):

    docker run --rm -it --platform=linux/amd64 \
        -v "$PWD/tools":/opt/tools -v "$PWD":/src qnx65-armv7-toolchain bash

Binaries must be `linux/amd64` (the image runs under amd64, emulated on Apple Silicon).


## neon-as/bin/as — NEON alignment-hint shim

`gas` 2.19 (stock QNX SDP) supports the ARM NEON element-alignment hint but only
in the UAL comma spelling `[Rn, :align]`. GCC 4.9 and hand-written core NEON emit
the no-comma spelling `[Rn:align]`, which 2.19 rejects with "']' expected". The
shim rewrites the former to the latter and calls the real `…-as-2.19`; it touches
only operands of the exact shape `[<reg>:<num>]`.

This was long recorded as a "binutils 2.19 ceiling" that forced NEON off. It is
not a ceiling — the assembler accepts the hint, just spelled with a comma. No
binutils upgrade needed.

GCC resolves `as` by ABSOLUTE path, not PATH, so unlike the qcc shim this cannot
work via PATH. It is picked up with:  `gcc -B/opt/tools/neon-as/bin`  (GCC looks
for a plain-named `as` in each -B dir first). Verified: autovec NEON and
hand-written `[Rn:64/128/256]` incl. writeback `[Rn:64]!` all assemble; the
retroarch griffin build enables it via `-mfpu=neon -B/opt/tools/neon-as/bin` in
Makefile.griffin's qnx stanza.
