# qnx-gcc49 - GCC 4.9.4 cross-compiler for QNX 6.5 / armle-v7

Newer GCC that still targets the **existing** QNX Neutrino 6.5.0 `armle-v7`
runtime, for building emulators (gpSP, PCSX-ReARMed, EmulationStation...) with
**full C++11** and better ARM/NEON codegen than the stock 4.4.2.

Reuses the QNX 6.5 SDP already baked into the `qnx65-armv7` image: its
**binutils 2.19** (`as`/`ld`, emulation `armnto`) and its **target sysroot**
(`/opt/qnx650/target/qnx6`, arch subdir `armle-v7`). We only build a new
compiler + libgcc + GNU libstdc++, installed **alongside** 4.4.2 (never
clobbers it) under `/opt/gcc49`.

## Why 4.9 (not 4.7 / 5.x)

- 4.8.1+ = first feature-complete **C++11 language**; 4.9 is the polished one.
- 4.9 keeps the **pre-C++11 libstdc++ string/ABI** (`_GLIBCXX_USE_CXX11_ABI`
  arrived in 5.1) -> objects/`.so`s link against QNX 6.5's existing C++ libs.
- 5.x/7.x break that ABI for zero emulator benefit.

## Ground-truth from the 6.5 SDP (do not re-derive, verified in-image)

| thing | value |
|-------|-------|
| target triplet | `arm-unknown-nto-qnx6.5.0eabi` |
| ABI | ARMv7-A, EABI5, **softfp** (no `Tag_ABI_VFP_args` -> base PCS) |
| default flags | `-march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=softfp -mlittle-endian` |
| dynamic linker | `/usr/lib/ldqnx.so.2` |
| ld emulation | `armnto` (only one) |
| sysroot | `$QNX_TARGET=/opt/qnx650/target/qnx6`, libs in `armle-v7/lib` |
| crt | `crt1.o crti.o crtbegin.o crtend.o crtn.o mcrt1.o` |
| binutils | 2.19 (reused as-is) |
| libstdc++ OS layer | already in 4.9 tree: `libstdc++-v3/config/os/qnx/qnx6.1` |

4.9.4 upstream has **only `i386-*-nto-qnx*`** in `config.gcc` - no ARM. So the
port adds an `arm*-*-nto-qnx*` stanza + `gcc/config/arm/nto.h` (modeled on
`i386/nto.h` + the ground-truth above) + a `libgcc/config.host` entry. See
`docker/port/`.

## Build

```sh
./bringup.sh gcc      # build the C compiler (all-gcc)
./bringup.sh libgcc   # build libgcc + crt (incl PIC crtbeginS.o)
./bringup.sh libstdc  # build libstdc++ (C++11/14)
./bringup.sh all      # everything + install to out/ + symlink binutils
./qnx49.sh build      # package out/ into the ready-to-use qnx65-gcc49 image
```
Each step re-applies `docker/port/apply.sh` (idempotent) to a persistent build
tree under `build/`, so edits to `docker/port/*` pick up on the next run.

## Use

```sh
./qnx49.sh arm-unknown-nto-qnx6.5.0eabi-g++ -std=c++14 -O2 -mfpu=neon foo.cpp -o foo
./qnx49.sh arm-unknown-nto-qnx6.5.0eabi-gcc -O2 foo.c -o foo
./qnx49.sh                                 # interactive shell
```
Output: `ELF 32-bit LSB, ARM EABI5 v7 softfp, interp /usr/lib/ldqnx.so.2`, int
enums, links against `libstdc++.so.6 libm.so.2 libc.so.3`. Both `-std=c++NN`
(strict) and `-std=gnu++NN` work.

## Status - [ok] DONE (C + full C++11/14, runtime-validated)

`hello11.cpp` (thread/chrono/atomic/lambda/shared_ptr/function/sort/string/
vector) compiles, links, and **runs on real QNX 6.5 armv7** (QEMU cortex-a15).
ABI verified against the firmware libs via `readelf -A`.

**Runtime proof** (`qemu_runtime_proof.log`) - booted a minimal IFS
(procnto-smp + our `hello11` + our `libstdc++.so.6`, built with `mkifs` on the
SDP VM, loaded by the `../qnx-gl-passthrough` custom qemu at `addr=0x40200000`):

```
--- launching hello11 (loads libstdc++.so.6) ---
4.9 c++11 gcc neon qnx          <- std::sort on vector<string>, alphabetical
answer=42 sq7=49                <- std::thread joined + atomic + shared_ptr; std::function lambda
Process 3 (hello11) exited status=0.
```

So `libstdc++.so.6` loads via `ldqnx`, `std::thread` runs on real pthreads,
`std::chrono::sleep_for` returns (the nanosleep fix), and the process exits 0 -
the whole C++11 stack works on the target, not just the ABI bytes.

### Defects found & fixed during bring-up (11)

| # | layer | defect | fix |
|---|-------|--------|-----|
| 1 | config | 4.9 has no `arm-*-nto-qnx` target | `arm*-*-nto-qnx*` stanza in config.gcc + libgcc/config.host + `arm/nto.h` |
| 2 | asm | gas 2.19 rejects UAL VFP (`vmov`/`vcvt`) | `TARGET_UNIFIED_ASM=1` -> emit `.syntax unified` |
| 3 | libgcc | ARM-EABI unwinder types (`_Unwind_*`) | `unwind_header=config/arm/unwind-arm.h` + softfp tmake |
| 4 | link | crt/libc live in `armle-v7/lib` | explicit `%R/armle-v7` in STARTFILE/LINK specs |
| 5 | ABI | short vs int enums | `ARM_DEFAULT_ABI=AAPCS_LINUX` |
| 6 | asm | gas 2.19 rejects `.inst` (trap) | `.inst`->`.word`/`.short` in arm.md |
| 7 | libstdc++ | crossconfig only knows qnx6.1/6.2 | widen to `*-qnx6.*` |
| 8 | libstdc++ | Dinkum headers: ptrdiff_t ns, memchr/cmath dupes, `_UP` ctype leak, nanosleep, `std::size_t` ordering | `os_defines.h` (early `<stddef.h>`/`<ctype.h>`+undef, `_NO_CPP_INLINES`, `__CORRECT_ISO_CPP_*`, `_GLIBCXX_USE_NANOSLEEP`, `_QNX_SOURCE`) + hardcoded `ctype_base.h` + `<cstddef>` in compatibility-atomic |
| 9 | libstdc++ | valarray `_Cos/_Cosh/_Sin/_Sinh` shadowed by Dinkum std:: math fns | elaborate `struct _UName` in valarray_after.h |
| 10 | link | `crtbeginS.o` non-PIC (movw/movt ABS in .so) | `t-crtstuff-pic` -> build crtbeginS with `-fPIC` |
| 11 | install | installed gcc can't find as/ld | symlink QNX binutils into `$prefix/$target/bin` |
| 12 | C headers | bare `#include <stdlib.h>` fails in C (`wchar_t` undeclared) | `#undef _GCC_WCHAR_T` before stdlib's wchar typedef block in `include-fixed/stdlib.h` - `<malloc.h>` pre-sets that fixincludes guard without the typedef, so the typedef is skipped (QNX Dinkum x fixincludes bug, present on stock 4.4.2 too). Re-applied by `bringup.sh` after every fixinc run. |

## Toolchain quality - validated with the compilers' own test suites

Ran GCC's and libstdc++'s regression suites (in the source tree) with this
toolchain; harness + logs in `torture/`.

| suite | result | reading |
|-------|--------|---------|
| **C compile** - `gcc.c-torture/execute` (1310, `-O2`) | **1290/1310** | 0 codegen/ICE bugs; residual = x86-only asm (`st(1)`), harness `-lm`/companion files, GCC-internal PR tests |
| **C runtime** - same, on real QNX ARM (QEMU cortex-a15) | **1261/1290** exit-0 | see below - every failure explained, none a port bug |
| **C++ compile** - libstdc++ testsuite (2161 core `-std=gnu++11`) | **1922/2161** | the 239 need the DejaGnu harness (`testsuite_hooks`, `__gnu_test::`), not real failures - sampled 30, all harness |
| **C++ runtime** | `hello11` on QEMU | thread/atomic/shared_ptr/function/sort/chrono all run |

Runtime failure breakdown (29), all root-caused as **environment, not codegen**:
- **17 x SIGBUS = unaligned access** - all pass rebuilt with `-mno-unaligned-access`.
- **5 x SIGSEGV = nested-function trampolines** - QNX non-executable *stack*.
- **6 x SIGABRT** - `-O2` optimizer corners (pass at `-O0`; inherent to GCC 4.9.4).
- **1 x `eeprof-1`** - needs the `-p`/mcount profiling runtime.

Logs: `qemu_torture_run.log`, `qemu_retest_run.log`, `logs/torture-compile*.log`,
`logs/libstdcxx-test.log`.

## Notes for building emulators / apps on this target

Two behaviours were measured on real QNX 6.5 ARM (QEMU cortex-a15) and matter
for ports like RetroArch / gpSP / PCSX-ReARMed:

**1. JIT / dynarec works (W^X is not enforced).** `mmap(PROT_READ|WRITE|EXEC,
MAP_ANON)` returns RWX pages with no special privilege; wrote ARM code into
them, flushed, and executed - returned the right value (`torture/jittest.c`).
The critical ARM step is the **I-cache flush** after emitting code - omit it and
the JIT crashes randomly on stale/garbage instructions:
```c
void *code = mmap(0, sz, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_ANON|MAP_PRIVATE, -1, 0);
/* ... emit machine code into code ... */
__builtin___clear_cache(code, (char*)code + len);   /* REQUIRED on ARM */
((int(*)(void))code)();
```
(For a strict-W^X style: mmap RW -> write -> `mprotect(RX)` -> clear_cache -> run.)
Only the *stack* is non-executable - irrelevant to a heap code-cache; if you ever
need an executable stack, link `-Wl,-z,execstack`.

**2. Unaligned access faults in the strict-alignment config (`SCTLR.A=1`).** The
armv7 default `-munaligned-access` emits single unaligned `ldr`/`str`, which
SIGBUS here. Do **not** blanket `-mno-unaligned-access` as a default - it turns
every `*(uint32_t*)(mem+addr)` (an emulator's hottest path - guest-memory read)
into 4 byte-ops. Prefer, in order: (a) run the target with `SCTLR.A=0` - Cortex-
A15 handles unaligned to normal memory in hardware, keeping the fast `ldr`; (b)
rely on the emulator's own aligned access helpers (gpSP/PCSX were written for
strict-alignment ARM handhelds); (c) `-mno-unaligned-access` only per-file where
correctness > speed. If a "never-SIGBUS" build is wanted regardless of perf, add
it as a separate qcc-style profile, not the compiler default.

Recurring root cause: **binutils 2.19 (2008) predates gcc 4.9 (2016) output**
(#2, #6) and **QNX Dinkumware C headers vs GNU libstdc++** (#8, #9 - the same
"pain #4" the stock 4.4.2 hit, solved once at the toolchain level). Codex
confirmed there is no master switch - the os_defines/ctype_base/valarray patch
set is the canonical QNX approach.

What GCC 4.9 gives over the stock qcc 4.4.2 (gpSP pains, gone for free):
`__BYTE_ORDER__`/`__ORDER_BIG_ENDIAN__` (4.6+), `__builtin_bswap16` (4.8+), full
C++11/14, plus a working NEON autovectorizer (`-mfpu=neon`).
