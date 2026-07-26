# qnx65-armv7-toolchain

**A single Docker image that cross-compiles C/C++, Go, and Rust for QNX Neutrino
6.5.0 `armle-v7` - no QNX VM, no external SDP install.**

Everything is assembled from source in one multi-stage `docker build`: the QNX
6.5 SDP tree with a modern **GCC 4.9.4** (full C++11, partial C++14) in place of the stock
4.4.2, a from-scratch **`GOOS=qnx` Go 1.26 port**, and a **nightly Rust**
`build-std` target - all three linking through the same QNX toolchain.

```sh
docker build --platform=linux/amd64 -t qnx65-armv7-toolchain .
```

---

## Table of contents

- [What you get](#what-you-get)
- [Inventory](#inventory)
- [The target](#the-target)
- [Quick start](#quick-start)
- [Usage per language](#usage-per-language)
  - [C / C++](#c--c)
  - [Go](#go)
  - [Rust](#rust)
- [Cross-building real software (CMake / Autotools / Meson)](#cross-building-real-software-cmake--autotools--meson)
- [How the image is built](#how-the-image-is-built)
- [Repository layout](#repository-layout)
- [Design decisions](#design-decisions)
- [Building the image](#building-the-image)
- [In-image environment](#in-image-environment)
- [Updating / regenerating components](#updating--regenerating-components)
- [Testing on real hardware](#testing-on-real-hardware)
- [Troubleshooting](#troubleshooting)
- [Status & limitations](#status--limitations)

---

## What you get

| Language | Compiler | Standard | Invocation | Output |
|----------|----------|----------|------------|--------|
| C / C++  | **GCC 4.9.4** (custom-built, replaces SDP 4.4.2) | C99 / **C++11** + partial C++14 | `arm-unknown-nto-qnx6.5.0eabi-{gcc,g++}` | ELF 32-bit ARM QNX exe/`.so` |
| Go       | **Go 1.26.4**, `GOOS=qnx GOARCH=arm` port | full `gc` toolchain | `GOOS=qnx GOARCH=arm GOARM=7 go build` | ELF 32-bit ARM QNX exe |
| Rust     | **nightly** rustc + `build-std` | **full `std`** (threads/fs/net/Command) | `build-std <crate>` | ELF 32-bit ARM QNX exe, linked by the QNX gcc |

All three emit:

```
ELF 32-bit LSB, ARM, EABI5, dynamically linked, interpreter /usr/lib/ldqnx.so.2
```

The host binaries (compilers) run as `linux/amd64`; on Apple Silicon they run
under emulation, but the ARM **output** is native QNX regardless.

---

## Inventory

Everything the image ships, in one place. The **toolchain, languages and
utilities** are on `PATH` inside the container; the **target sysroot** is what
your builds link and run against; the **host-scripts** run on your machine and
drive the container. Other sections show *how* to use these - this is *what
exists*.

### Toolchain (on `PATH`, prefix `arm-unknown-nto-qnx6.5.0eabi-`)
- **GCC 4.9.4** - `gcc` / `g++` / `cpp`. C99, C++11, partial C++14. Ships a static
  `libstdc++.a` (so `-static-libstdc++` works) beside the shared one.
- **Binutils 2.19** - `as ld ar nm ranlib strip objcopy objdump readelf size
  strings addr2line c++filt gprof`.
- **`qcc`** - qcc-to-gcc shim for `mkifs` / qcc Makefiles (`tools/qcc`; full flag
  table in `tools/README.md`).
- **`neon-as`** - gas-2.19 NEON alignment-hint shim, via `-B/opt/tools/neon-as/bin`.

### Languages
- **Go 1.26.4** - `go` / `gofmt`, `GOOS=qnx GOARCH=arm` port.
- **Rust nightly** - `rustc` / `cargo` / `build-std`, full `std` for `armv7-nto-qnx650`.

### Image & filesystem builders
The QNX `mkxfs` family (the 6.6 `mkxfs`, [vendored](#selectively-backported-from-qnx-66)):
- `mkifs` + `dumpifs` - IFS boot image.
- `mkefs` / `mketfs` + `dumpefs` - flash / ETFS images.
- `mkqnx6fsimg` - qnx6 Power-Safe fs image (`mount -t qnx6`).
- `mkfatfsimg` - FAT fs image. `mkrcfsimg` / `mkrcfs` - RCFS.
- `mkifsf_{elf,srec,openbios,coff,bswap,opah,densan}` - mkifs output-format
  filters. `mkrec` - record/S-record tool.

### Cross-build systems
`cmake`, `meson`, `ninja`, `pkg-config`, with ready cross files at
`/opt/qnx-cross/` (`config.site`, `qnx-armv7.cmake`, `qnx-armv7.ini`).

### Other host utilities
`rpcgen` (ONC-RPC stub generator), `deflate`, `use` / `usemsg` (QNX
usage-message tools), `file`.

### Target sysroot (`$QNX_TARGET = /opt/qnx650/target/qnx6`, arch `armle-v7`)
What output links against and the runtime it targets:
- **Shared libs** (`armle-v7/lib`): `libc` (`.so.3`), `libm`, `libstdc++`
  (`.so.6.0.13`), `libsocket`, `libcpp` / `libecpp`, `libasound`, `libimg`,
  `libfont`, `libusbdi`, `libsnmp`, `libcam`, `libhiddi`, `libpps`, ...
- **Static libs**: 27 in `lib/` + 117 in `usr/lib/` (including the built `libstdc++.a`).
- **CRT**: `crt1 crti crtbegin crtend crtn mcrt1 .o`.
- **Driver / resource-manager DLLs** (`armle-v7/lib/dll`, ~60): `fs-qnx6`,
  `fs-qnx4`, `fs-ext2`, `fs-dos`, `fs-udf`, `io-blk`, `io-winmgr-*`, `devc-*`, ...
- **Prebuilt kernels** (`armle-v7/boot/sys`): `procnto`, `procnto-instr`,
  `procnto-smp`, `procnto-smp-instr` - drop straight into an IFS build file.
- **Headers** (`usr/include`, ~1700 `.h`): C / POSIX, `arm/`, `sys/`, `net*/`,
  plus bundled `openssl/`, `curl/`, `libxml/`, `c++/`, `io-pkt/`, `photon/`, ...

### Host-scripts (`host-scripts/`, run on your machine)
- `qnx-run.sh` - run any toolchain command on the cwd (or an interactive shell).
- `qnx-mkifs.sh` / `qnx-mkqnx6fs.sh` - build an IFS / qnx6 fs image.
- `qnx-configure` / `qnx-cmake` / `qnx-meson` - cross-configure autotools/CMake/Meson.
- `qnx-check-so` - flag a `.so` the QNX loader would silently drop.

---

## The target

Ground truth, verified against the QNX 6.5 SDP and the on-device libraries:

| Property | Value |
|----------|-------|
| Target triplet | `arm-unknown-nto-qnx6.5.0eabi` |
| CPU / ABI | ARMv7-A, **EABI5**, **softfp** (base PCS - no `Tag_ABI_VFP_args`) |
| Default codegen | `-march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=softfp -mlittle-endian` |
| Dynamic linker | `/usr/lib/ldqnx.so.2` |
| Linker emulation | `armnto` (binutils 2.19) |
| Sysroot | `$QNX_TARGET = /opt/qnx650/target/qnx6`, libs under `armle-v7/lib` |
| CRT | `crt1.o crti.o crtbegin.o crtend.o crtn.o mcrt1.o` |
| On-device C++ runtime | `libstdc++.so.6.0.13` (GCC 4.4.x ABI - GCC 4.9 keeps the pre-C++11 ABI) |

**Runtime compatibility matters:** binaries built here run on a QNX **6.5**
device. QNX 6.6+ has a different libc/ABI - do not mix. GCC 4.9 was chosen
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

# 4. Rust (full std) - build_std links via the QNX gcc for you
docker run --rm -v "$PWD":/src qnx65-armv7-toolchain build-std path/to/crate

# interactive shell
docker run --rm -it -v "$PWD":/src qnx65-armv7-toolchain bash
```

Verify any output binary:

```sh
file hello    # -> ELF 32-bit LSB executable, ARM, EABI5 ..., interpreter /usr/lib/ldqnx.so.2
```

Shortcut: `host-scripts/qnx-run.sh <cmd>` runs any of the above in the image with
the cwd mounted, e.g. `./host-scripts/qnx-run.sh build-std ./mycrate` or
`./host-scripts/qnx-run.sh` for an interactive shell.

---

## Usage per language

### C / C++

Invoke the compiler **directly** by its target triplet - it sets all QNX defines
(`__QNXNTO__`, `__QNX__`, `__ELF__`, `__ARM__`), sysroot, CRT and specs itself.
The stock SDP `qcc` driver was replaced by GCC, but a **`qcc` shim** on `PATH`
translates qcc-style invocations to gcc/g++ for anything that still calls it
(`mkifs`, qcc-based Makefiles) - see [The `qcc` shim](#the-qcc-shim).

```sh
# C
arm-unknown-nto-qnx6.5.0eabi-gcc -O2 app.c -o app

# C++14 (lambdas, auto, move, <thread>, <chrono>, smart pointers ...)
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

**C++ shared objects / mkifs grafts / preloads.** Linking a `.so` with `g++` puts
`libstdc++.so.6` in its `DT_NEEDED`. If the target IFS/graft image doesn't ship
that library, QNX's loader **silently drops the whole preload/graft** - no error,
no output. Three ways out, depending on what the code uses:

```sh
# full C++ (new/delete, STL, exceptions): statically fold libstdc++/libgcc in -
# no libstdc++ dependency, no dangling symbols. General fix.
arm-unknown-nto-qnx6.5.0eabi-g++ -shared -fPIC -static-libstdc++ -static-libgcc mod.cpp -o mod.so

# minimal C++ only (NO new/delete/STL/exceptions/rtti): compile freestanding-ish
# and link with gcc so libstdc++ is never pulled. VERIFY nothing dangles:
arm-unknown-nto-qnx6.5.0eabi-g++ -c -fPIC -fno-exceptions -fno-rtti mod.cpp -o mod.o
arm-unknown-nto-qnx6.5.0eabi-gcc -shared mod.o -o mod.so
arm-unknown-nto-qnx6.5.0eabi-nm -D -u mod.so   # must show NO _Znwj/_ZdlPv/_ZNSt* (new/delete/std::)

# or: actually ship libstdc++.so.6 in the image (it's in the SDP sysroot at
# target/qnx6/armle-v7/lib/libstdc++.so.6.0.13 + the .so.6 symlink).
```

`gcc -shared` alone won't error on the missing symbols - shared objects allow
undefined references - so a `new`/STL module links "clean" but leaves `_Znwj`
&co. unresolved and fails the same silent way at load. Check any module before
grafting with `host-scripts/qnx-check-so mod.so` (flags a libstdc++ NEEDED or
dangling C++ runtime symbols), or by hand with `nm -D -u`.

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

**Full `std`** for QNX 6.5 armv7 - nightly rustc + `-Z build-std=std,panic_abort`
against a custom target (`rust/armv7-unknown-nto-qnx650.json`: arm/eabi, softfp,
**`+strict-align`** for QNX's `SCTLR.A=1`, `panic = abort`). The std port (an
`nto65` libc fork + std source patches for 32-bit `time_t` and `/dev/random`)
is **baked into the image** - no per-machine setup.

```sh
# one command: build-std compiles std + your crate and links via the QNX gcc
build-std path/to/crate
# -> path/to/crate/target/armv7-unknown-nto-qnx650/release/<crate>  (ARM QNX ELF)
```

Under the hood it runs `cargo build -Z build-std=std,panic_abort` with
`RUSTFLAGS="-C linker=/opt/rust/qnx-cc"`; `qnx-cc` is a linker shim that calls the
in-image gcc, remaps `-lgcc_s -> -lgcc`, adds the sysroot, and links the EHABI
`_Unwind_GetIP` shim. What works (validated on real QNX 6.5 QEMU): threads +
`thread_local!` + `Arc<Mutex>`/atomics, `fs`, `Command`/`posix_spawn`,
`TcpListener`/`TcpStream`/`UdpSocket`, `HashMap`/`BTreeMap`, `fmt`. `panic=abort`
(no unwind/backtrace - 6.5 lacks `dl_iterate_phdr`). See `rust/README.md` +
`rust/port/PLATFORM_NOTES.md`.

`rust/rust-toolchain.toml` pins a **dated nightly** (`nightly-2026-07-21`) +
`rust-src` - the std-port patches are calibrated to it, so the pin is load-bearing,
not just for reproducibility. **Stable can't build this**: `-Z build-std` and
`-Z json-target-spec` are nightly-only.

---

## Cross-building real software (CMake / Autotools / Meson)

The direct compilers cross-build a single file fine; real projects also need
their build system pointed at the target and their cross **run-tests** answered
(a cross-compiler can't *execute* a probe binary at configure time - the classic
`cannot run test program` / gnulib `conftest` wall). The image ships ready-made
cross files at `/opt/qnx-cross/` and host wrappers so you rarely type them:

| Build system | In-image file | Host wrapper |
|--------------|---------------|--------------|
| Autotools    | `config.site` | `host-scripts/qnx-configure` |
| CMake        | `qnx-armv7.cmake` | `host-scripts/qnx-cmake` |
| Meson        | `qnx-armv7.ini` | `host-scripts/qnx-meson` |

```sh
# Autotools - config.site pre-answers the cross run-tests
cd myproject && /path/to/host-scripts/qnx-configure --disable-shared && make

# CMake - the toolchain file is injected on configure, not on --build
qnx-cmake -S . -B build && qnx-cmake --build build

# Meson - --cross-file injected on 'setup'
qnx-meson setup build && qnx-meson compile -C build
```

Or run the raw tools inside the image (what the wrappers do):

```sh
CONFIG_SITE=/opt/qnx-cross/config.site ./configure --host=arm-unknown-nto-qnx6.5.0eabi
cmake -DCMAKE_TOOLCHAIN_FILE=/opt/qnx-cross/qnx-armv7.cmake -S . -B build
meson setup --cross-file /opt/qnx-cross/qnx-armv7.ini build
```

What the files set up: the target triplet + compilers/`ar`/`strip`, the QNX
sysroot for `find_*`/pkg-config (host libs excluded), `needs_exe_wrapper`, and -
for autotools - a curated set of `ac_cv_*`/`gl_cv_*` results (malloc/realloc(0),
memcmp, mmap, mktime, ...) plus `CPPFLAGS=-include stddef.h`. gnulib defines
hundreds of `gl_cv_*` run-tests; the common offenders are covered, and a stubborn
project just adds its own to `cross/config.site`. `cmake`, `meson`, `ninja`, and
`pkg-config` are installed in the image for this.

Two toolchain-level fixes make most C/C++ software link and compile without
per-project patching (both in `gcc/port/arm-nto.h`):

- **Static-only libc functions resolve automatically.** 113 libc functions -
  the regex family (`regcomp`/`regexec`/`regfree`/`regerror`), `glob`/`globfree`,
  `wordexp`, `scandir`, ... - live only in `libc.a`, not the shared `libc.so.3`,
  so software that uses them used to fail to link. The default link now appends
  `-l:libc.a`, and the linker pulls those members statically on demand (programs
  that don't use them pull nothing).
- **`_QNX_SOURCE` is predefined** (QNX's `_GNU_SOURCE` analog), so the POSIX/
  pthread extensions that headers hide under strict `-std=cNN` are visible. Stock
  QNX's own libstdc++ predefines it too; it gates declarations, not ABI.

---

## How the image is built

One multi-stage `Dockerfile`:

```
+-- base: qnx-sdp -----------------------------------------------+
| debian:bullseye-slim@sha256 (amd64 + i386 multilib)           |
|   + libc6/libstdc++6/zlib1g:i386  (QNX binutils are 32-bit x86)|
|   + libgmp10 libmpfr6 libmpc3     (GCC 4.9 host libs)          |
|   + gcc libc6-dev                 (host cc for Cargo scripts)  |
|   + make curl ca-certificates xz-utils                         |
| COPY sdp/  ->  /opt/qnx650                                     |
|   = QNX 6.5 SDP: binutils 2.19 + armle-v7 sysroot (NO gcc)     |
+---------------------------------------------------------------+
   |                    |                        |
   v FROM qnx-sdp       v FROM qnx-sdp           v FROM qnx-sdp
+-- gcc-build ------+ +-- go-build -------+ +-- rust-build --------+
| COPY gcc/ (port)  | | COPY go/ (src)    | | rustup nightly + src |
| curl gcc-4.9.4    | | curl Go bootstrap | | COPY rust/ (std port)|
| apply port,       | | make.bash:        | | bake std: libc fork  |
|  configure, make  | |  host go +        | |  + std patches       |
|  -> /gcc-out      | |  qnx/arm stdlib   | |  (apply_std_port)    |
+-------------------+ +-------------------+ +----------------------+
   |                     |                        |
   +---------------------+------------------------+
                    v FROM qnx-sdp
+-- final: qnx65-armv7-toolchain ---------------------+
| COPY --from=gcc-build   /gcc-out -> SDP host tree   |
| COPY --from=go-build    /opt/go                     |
| COPY --from=rust-build  /opt/rustup /opt/cargo      |
| + cmake/meson/ninja/pkg-config (cross build systems)|
| build the unwind shim; install the build-std wrapper|
| COPY tools/ (qcc shim) + cross/ + entrypoint <- LAST |
+-----------------------------------------------------+
```

The base carries **binutils + the sysroot but no compiler**; GCC 4.9.4 is compiled
from source in `gcc-build` (~20-40 min, see `gcc/`) and merged into the host tree
in the final stage. Go and Rust stages are `FROM qnx-sdp` and **link through that
GCC** - Go's external linker and Rust's `.a -> .so` step both call
`arm-unknown-nto-qnx6.5.0eabi-gcc`. That is why no QNX VM is needed anymore.
`tools/` and the entrypoint are copied **last**, so editing the `qcc` shim (or any
drop-in) re-runs only those cheap layers, never the cached gcc/go/rust stages.

---

## Repository layout

```
Dockerfile          the multi-stage build described above
entrypoint.sh       prepends every /opt/tools/*/bin to PATH at container start
sdp/                the QNX 6.5 SDP base - the foundation all languages link against:
  - host/             binutils 2.19 (as/ld) + QNX host tools (no gcc - built from source)
  - target/           armle-v7 sysroot - headers, CRT, libc/libm/libstdc++ (the 6.5 runtime)
  - etc/              QNX config + license key
gcc/                GCC 4.9.4 port + build recipe (port/ patches, build.sh, README):
                    the arm-nto-qnx port applied to vanilla upstream at build time
go/                 patched Go 1.26.4 source - src/ + lib/ only (~152 MB);
                    make.bash regenerates bin/ + pkg/ at build time
rust/               full-std QNX port: target spec + rust-toolchain.toml + port/
                    (libc fork + std patches) + qnx-cc linker shim + shim/ + build_std.sh
tools/              in-container PATH additions - the bundled qcc/ shim (for mkifs)
                    plus any user drop-in compilers; see tools/README.md
cross/              cross-build files baked to /opt/qnx-cross: config.site (autotools),
                    qnx-armv7.cmake (CMake toolchain), qnx-armv7.ini (Meson cross file)
host-scripts/       host-side runners (qnx-run.sh, qnx-mkifs.sh, qnx-mkqnx6fs.sh,
                    qnx-configure/qnx-cmake/qnx-meson, qnx-check-so) - see the Inventory
```

The top-level inputs map 1:1 to the Docker stages: `sdp/` -> `base`, `gcc/` ->
`gcc-build`, `go/` -> `go-build`, `rust/` -> `rust-build`. `~310 MB` in git
(`sdp/` ~ 161 MB, `go/` ~ 152 MB). Final image ~ **1.4 GB**.

---

## Design decisions

### GCC 4.4.2 -> 4.9.4, in place
The stock SDP compiler was **fully replaced** by a custom GCC 4.9.4 built from
source (recipe in `gcc/`) for the same `arm-unknown-nto-qnx6.5.0eabi` target. It
reuses the SDP's binutils 2.19 and the 6.5 sysroot, and lives exactly where 4.4.2
did (`usr/bin` drivers, `usr/lib/gcc/.../4.9.4`, `usr/libexec/gcc/.../4.9.4`).
Gains: full **C++11** and most of **C++14** (generic lambdas, return-type
deduction, `make_unique`, `<thread>`/`<chrono>`/atomics), better ARM/NEON codegen -
while keeping the pre-C++11 libstdc++ ABI so output stays link-compatible with the
6.5 device libraries. C++14 is GCC 4.9's experimental level (`__cplusplus =
201300L`; **no variable templates** - those need GCC 5 - and **no C++17**). For a
newer standard, rebuild a newer GCC against this sysroot the same way.

### <a name="the-qcc-shim"></a>The `qcc` shim
The stock SDP `qcc` was removed: it exists only to select among **multiple**
{arch x compiler version x C++ library} combos via `-V`, and this image has
exactly one of each (armv7 x GCC 4.9 x GNU libstdc++). The direct driver already
sets every QNX define, sysroot, CRT and specs and links correctly.

But `mkifs` build files (and some Makefiles) literally invoke `qcc`, so
`tools/qcc/bin/qcc` is a small **qcc-to-gcc translator** (validated against the
decompiled stock qcc and the QNX make rules). It drops `-V`/`-Y`/`-cxxlib*`/`-*-intel`/`-nopipe`,
maps `-bootstrap`->`-nostdlib`, `-nostartup`->`-nostartfiles`, `-EL/-EB`->endian,
`-Wc,`->compiler opts, `-lang-*`->`-x`, runs `-a <lib>` as the `ar` librarian
(QNX's qcc-driver make builds static libs that way), expands `@response-files`,
and picks **g++** for C++ (a C++ `-V` variant, a C++ source extension, `-lang-c++`,
or a `CC`/`c++` driver name) so C++ links libstdc++. Everything gcc already
understands passes through. Full flag table in `tools/README.md`.

### armv7-only
Only the `armle-v7` (EABI) target is kept. The other SDP arches (arm-old-abi,
x86, mips, ppc, sh), the Momentics IDE, docs, and WebKit were trimmed from the
SDP tree, shrinking it from ~1.1 GB to ~235 MB.

### <a name="selectively-backported-from-qnx-66"></a>Selectively backported from QNX 6.6
A few 6.6 host tools and headers are vendored where 6.5 lacked them, always kept
6.5-compatible:
- **`mkxfs`** (6.6) replaces the 6.5 one - it adds the qnx6fs / FAT / RCFS image
  modes (`mkqnx6fsimg`/`mkfatfsimg`/`mkrcfsimg`), and its IFS/EFS output is
  byte-identical to 6.5's (verified: same build file -> identical bytes modulo
  the embedded timestamp), so `mkifs`/`mkefs`/`mketfs` (symlinks to it) are
  unchanged in behaviour.
- The extra `mkifsf_*` filters, `mkrcfs`, and `rpcgen` (small standalone tools).
- Architectural `arm/*.h` macros 6.6 added and 6.6-vintage startup/BSP code needs
  (`arm/mmu.h` TTBR/PTE, `arm/cpu.h` CPSR IT, `arm/pl011.h`, `arm/gic.h`,
  `arm/mpcore.h` SCU, `arm/opcode.h`, `arm/syspage.h` CPU-flag bits).

Only silicon-/ISA-defined, purely additive bits are taken - never changed struct
layouts, macro values, or anything that needs the 6.6 runtime. The 6.6 cross
toolchain (gcc 4.7.3 / binutils 2.24) is **not** used: it targets qnx6.6 and its
gcc is older than the 4.9.4 built here.

### Go and Rust are real ports, not cross-compiles
QNX is an upstream target for neither. Go adds a `GOOS=qnx GOARCH=arm` libc-call
runtime + a hand-written ARM asm bridge (`go/`). Rust adds a custom
`armv7-nto-qnx650` target + an `nto65` libc fork + std source patches, built via
`-Z build-std` (`rust/`). Both are **softfp** to match the 6.5 ABI (`Tag_VFP_arch:
VFPv3-D16`); Rust's target carries `+strict-align` for QNX's `SCTLR.A=1`, and the
GCC port defaults C/C++ to `-mno-unaligned-access` for the same reason (see below).
Full details in `go/README.md` and `rust/README.md`.

### Strict alignment (`-mno-unaligned-access`) default
QNX 6.5 runs with `SCTLR.A=1`, so a misaligned load/store **faults** on-device.
GCC 4.9 otherwise defaults ARMv7 to `-munaligned-access` and would emit single
misaligned `ldr`/`str` (e.g. an unaligned `memcpy`, packed-struct fields), which
crash there. The port (`gcc/port/arm-nto.h`) defaults C/C++ to
`-mno-unaligned-access` - the compiler splits unaligned accesses into byte ops
instead - matching Rust's `+strict-align`. An explicit `-munaligned-access` still
overrides it; aligned accesses are unaffected (only genuinely-unaligned ones cost
a little).

---

## Building the image

```sh
docker build --platform=linux/amd64 -t qnx65-armv7-toolchain .
```

**Requirements**
- Docker with `linux/amd64` support (native on x86-64; emulated via QEMU/Rosetta
  on Apple Silicon).
- **Network during build** - the Go bootstrap, `rustup`, and Rust crates are
  fetched from `go.dev`, `sh.rustup.rs`, and `crates.io`. For fully offline/
  reproducible builds you would need to vendor those.

**Build arg**
- `GO_BOOTSTRAP` (default `go1.26.4`) - the official Go release fetched from
  `go.dev/dl` to bootstrap `make.bash`.

**Reproducibility / pinning**
- Base image pinned by **digest** (`debian:bullseye-slim@sha256:...`).
- **GCC source** pinned by **sha256** (`GCC_SHA256`, verified after download).
- **Go bootstrap** pinned by version (`GO_BOOTSTRAP`) **and sha256** (`GO_BOOTSTRAP_SHA256`).
- **Rust nightly** pinned by **date** - `RUST_NIGHTLY` at install + the same date
  in `rust/rust-toolchain.toml`; rustup verifies component checksums.
- GCC 4.9.4 is **built from source** in `gcc-build` from vanilla upstream + the
  vendored port (`gcc/port`); `sdp/host` carries only binutils. The
  `gcc-4.9.4.tar.bz2` is fetched from ftp.gnu.org (byte-identical to the canonical
  release, checksum-checked); vendor it under `gcc/` for a fully offline build.
- Still floats: **`apt` package versions** (from the Debian mirror). The digest-
  pinned base fixes the pre-installed set, but `apt-get install` pulls current
  versions. For bit-reproducibility, point `sources.list` at snapshot.debian.org
  (a dated snapshot) - omitted here as it is slower and occasionally flaky.

**Partial builds** (build one stage while iterating - each is an intermediate
build stage, not a ready polyglot image):

```sh
docker build --platform=linux/amd64 --target qnx-sdp    -t _sdp .   # base: binutils + sysroot
docker build --platform=linux/amd64 --target gcc-build  -t _gcc .   # + build GCC 4.9.4
docker build --platform=linux/amd64 --target go-build   -t _go .    # + build the Go port
docker build --platform=linux/amd64 --target rust-build -t _rust .  # + rust toolchain + std port
```

Iterating on the `qcc` shim or `tools/` needs no rebuild at all - mount them at
runtime: `-v "$PWD/tools":/opt/tools` (this is what `host-scripts/qnx-mkifs.sh` does).

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
PATH=/opt/go/bin:/opt/cargo/bin:/opt/qnx650/host/linux/x86/usr/bin:/usr/local/bin:/usr/bin:/bin
LD_LIBRARY_PATH=/opt/qnx650/host/linux/x86/usr/lib
```

`/usr/local/bin` holds `build-std`; `entrypoint.sh` additionally prepends every
`/opt/tools/*/bin` at container start (so the bundled `qcc` shim and any drop-in
under `tools/<name>/bin` land on `PATH`) - works for baked-in `COPY` and for a
runtime `-v host:/opt/tools` mount. See `tools/README.md`.

---

## Updating / regenerating components

- **C/C++ (GCC 4.9.4)** - the port lives in `gcc/port` (the `arm-nto-qnx`
  `config.gcc` stanza, `arm/nto.h`, `arm.md` gas-2.19 fixups, the libstdc++
  os_defines/ctype_base/valarray patches for QNX Dinkum headers, the wchar_t
  fix). `gcc/build.sh` applies it to vanilla gcc-4.9.4 and builds. To change the
  compiler, edit `gcc/port/*` and rebuild - no external project needed.
- **Go** - bump the patched tree in `go/src`; `make.bash` rebuilds at
  `docker build`. Only `src/` + `lib/` are vendored; `bin/` and `pkg/` regenerate.
- **Rust** - edit `rust/armv7-unknown-nto-qnx650.json` or bump the pinned nightly
  in `rust/rust-toolchain.toml`.

---

## Testing on real hardware

The compilers are `linux/amd64` and cannot execute ARM QNX output directly.
Run and validate on `qemu-system-arm -M virt -cpu cortex-a15` (boots real
`procnto` + `libc.so.3`) or a physical QNX 6.5 board. Package binaries into a
bootable image with the QNX `mkifs`/`mkefs` tools (in the image);
`host-scripts/qnx-mkifs.sh <build-file> <out.bin>` wraps that, and `dumpifs`
(also in the image) extracts an existing image to rebuild it with a file added.

To build a **qnx6 Power-Safe filesystem image** (mountable on 6.5 with `mount -t
qnx6`, e.g. over a loopback device), use `mkqnx6fsimg` /
`host-scripts/qnx-mkqnx6fs.sh <build-file> <out.img>` (`mkfatfsimg` builds a FAT
image the same way). These come from the vendored 6.6 `mkxfs` - see
[Selectively backported from QNX 6.6](#selectively-backported-from-qnx-66) for
why that swap is format-safe. The full tool list is in the [Inventory](#inventory).

---

## Troubleshooting

- **`Unknown EABI object attribute 34`** during link - cosmetic. Binutils 2.19
  doesn't recognize a newer EABI attribute tag emitted by GCC 4.9 / LLVM; the
  linker skips it and the binary is correct.
- **Debug symbols / `addr2line` / `objdump -S`** - `-g` defaults to **DWARF 3**
  (set in `gcc/port/arm-nto.h`), because the SDP's binutils 2.19 read DWARF <= 3
  and GCC 4.9's own default (DWARF 4) makes them warn `unsupported version 4` and
  drop file:line. So the in-image `addr2line`/`objdump`/`readelf` symbolize `-g`
  output out of the box. This only sets the *version*; `-g` isn't forced, an
  explicit `-gdwarf-N` still wins, and it never touches the code (debug lives in
  non-loadable `.debug_*` sections the device never maps).
- **Rust: `linker cc not found` / `cannot open Scrt1.o`** - the image needs a
  *host* C toolchain (`gcc` + `libc6-dev`) for Cargo build scripts and
  proc-macros; both are installed in the base. (This is separate from the QNX
  cross-gcc.)
- **Rust: `.json target specs require -Zjson-target-spec`** - pass
  `-Z json-target-spec` (already in the examples).
- **Go tries to download a toolchain** - ensure `GOTOOLCHAIN=local` (set in the
  image).
- **Binary won't resolve libc on device** with pure internal linking - use
  external linking (`-linkmode=external -extld=arm-unknown-nto-qnx6.5.0eabi-gcc`).
- **A C++ preload / mkifs graft is silently ignored** (loads nothing, no output) -
  its `.so` was linked with `g++`, which adds `libstdc++.so.6` to `DT_NEEDED`, and
  that library isn't in the target image, so the loader drops the whole object
  without a diagnostic. Link it self-contained with `-static-libstdc++
  -static-libgcc`, or (minimal C++ only) build with `-fno-exceptions -fno-rtti`
  and link via `gcc -shared` - then confirm with `nm -D -u` that no `_Znwj`/`_ZNSt*`
  symbols dangle. See [C / C++](#c--c).

---

## Status & limitations

- **C/C++** - C99 + full C++11 + partial C++14 (GCC 4.9, `__cplusplus=201300L`;
  no variable templates, no C++17). Runtime-validated on real QNX 6.5 ARM
  (thread/atomic/chrono/shared_ptr all run on QEMU cortex-a15 - see gcc/README.md).
- **Go** - the `GOOS=qnx GOARCH=arm` port builds the full stdlib and links
  internally (`DT_NEEDED libc.so.3`); binaries **run on real QNX 6.5 hardware** -
  TCP end-to-end validated on the MHI2q head unit (see `go/README.md`). cgo uses
  external linking through the in-image gcc.
- **Rust** - **full `std`** via `build-std=std,panic_abort` (threads, fs, net,
  Command, collections), runtime-validated on real QNX 6.5 QEMU. `panic=abort`,
  no unwind/backtrace. Port baked into the image (`build-std <crate>`).
- **One arch** - `armle-v7` only (other SDP arches trimmed from the tree).
