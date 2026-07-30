# Rust -> QNX 6.5 / ARMv7 (Cortex-A7)

Goal: build Rust code that runs on the MHI2Q head unit (QNX 6.5, ARMv7-A).
This is **not** a host-compiler port. `rustc`+LLVM already cross-compile ARMv7;
we add a *target* and cross-build from the dev box. The QNX assets are the
**sysroot** the target links against, nothing more.

## Target facts (from `readelf -A` on a stock 6.5 ARM binary)
- CPU: Cortex-A7, `Tag_CPU_arch: v7`, profile Application
- FP: `VFPv3-D16` (so `-d32`, i.e. d16), **softfp** (no `Tag_ABI_VFP_args` => float args in core regs)
- ABI: EABI5, 8-byte alignment, wchar=4
- => target ABI = `armv7 + vfp3-d16 + soft float-abi`, PIC, dynamic linking.

## Assets -> role
| Asset | Use |
|---|---|
| **QNX 6.5 SDP toolchain** (in this image: `arm-unknown-nto-qnx6.5.0eabi-gcc` + binutils 2.19 + `target/qnx6/armle-v7` sysroot + `mkifs`) | the linker + sysroot the Rust target links against (Rust doesn't host on QNX; rustc emits objects, the QNX gcc links the ELF). |
| ~~qnx66 / qnx800~~ | rejected: qnx66 = 6.6 (gcc 4.6, wrong ver, ABI risk); qnx800 = QNX 8 aarch64 (diff OS gen). Neither fits a 6.5-armv7 target. |
| **QEMU harness** (cortex-a15) | the on-device test bed: `qemu-system-arm -M virt -cpu cortex-a15` (armv7-A, runs our armv7 `.so`), boots real `procnto-smp` + `libc.so.3`, IFS has `sh`/`ls`/`cat`/`pidin`. dlopen milestone runs here - no real HU needed. |
| QNX 6.3.0 source | reference for libc struct layouts / syscall shims **only if** full `std` is attempted |

## Scope decision (pick before writing tooling)
**A. `no_std` (core + alloc) - days. Default.**
Enough for an `LD_PRELOAD` `.so` and the `altscreen_render` decoder - both are
FFI-to-libc anyway (dlsym, sockets, pthread, OMX). Avoids Rust `#[thread_local]`
=> **dodges the emutls trap** (use pthread keys via FFI, like the C hook).
`has-thread-local: false` in the target json enforces this.

**B. full `std` - months. Only if A proves insufficient.**
Fork `std::sys::pal::unix` for 15-yr-old POSIX (missing `pipe2`/`accept4`/
`posix_spawn`/`clock_*`/`O_CLOEXEC`), add a `libc` `nto650` variant, then fight
emulated-TLS through std's thread-locals. This is where QNX 6.3 sources matter.

## Emutls landmine (both scopes touch it)
QNX 6.5 gcc 4.4 traps on native ELF TLS in a dlopen'd `.so`. LLVM must emit
**emulated TLS** (`-femulated-tls` equivalent) and the `__emutls_get_address`
runtime must resolve from the 6.5 libgcc/libc. `no_std` avoids Rust-side TLS
entirely; that's why A is the safe first bet.

## FIRST MILESTONE - the decisive experiment (~1 weekend)
Prove on-device Rust loads *at all* before building anything else.

1. Point `linker` in `armv7-unknown-nto-qnx650.json` at the real 6.5 ARM `qcc` wrapper.
2. Trivial crate: `#![no_std]`, `#![crate_type="cdylib"]`, one `#[no_mangle] extern "C" fn`, `panic = "abort"`, a `#[panic_handler]`.
3. Build:
   ```
   cargo +nightly build -Z build-std=core,alloc \
     --target ./armv7-unknown-nto-qnx650.json --release
   ```
4. Push `.so` to the HU, `dlopen` + call the fn from a tiny C stub.

- Loads + runs -> on-device Rust is real; scope `std` later only if needed.
- Loader/emutls rejects it -> learned cheaply, before any std work.

## Build flow (in this image)
Rust doesn't host on QNX, so rustc (linux/amd64) emits objects and the **in-image
QNX gcc links the ELF**. `build_std.sh` wraps it: `cargo build -Z build-std=std`
with `-C linker=qnx-cc` (the linker shim -> `arm-unknown-nto-qnx6.5.0eabi-gcc`).
No external VM - the 6.5 toolchain now lives in the image. On-device validation
uses the `qnx-gl-passthrough` QEMU (cortex-a15, real procnto + libc.so.3).

## Status
- [x] cross-sysroot located: `/usr/qnx650` armle-v7 (QNX 6.5.0), qcc variant `gcc_ntoarmv7le`
- [x] on-device test bed: qnx-gl-passthrough QEMU (cortex-a15, real procnto+libc.so.3, has `sh`)
- [x] target json validated + builds (`-Z build-std=core -Z json-target-spec`, nightly 1.99)
- [x] **MILESTONE 1 PASSED (2026-07)** - Rust no_std cdylib `dlopen`'d by the real QNX 6.5
      loader in QEMU, `rust_probe(10)` returned the exact expected `0x515253D5`, exit 0.
      Proof: `dltest/` crate + `dltest.build` IFS + `dltest_run.c` harness.
- [x] **MILESTONE 2 PASSED (2026-07)** - no_std cdylib does the full hook backbone on real QNX 6.5:
      calls libc, spawns a pthread running Rust, keyed TLS (pthread_key_* - emutls-avoidance live),
      ARMv7 atomics (LDREX/STREX), dlsym interposition. Serial: `thread_shared=1 counter=1042 dlsym=1 -> PASS`.
      Proof: `ffitest/` crate + `ffitest.build` + `ffi_run.c`. Link: `arm-...-gcc -shared -Wl,-uffi_probe ... -lc`.
- [x] **MILESTONE 2b PASSED (2026-07)** - end-to-end TCP: `sockfwd/` no_std cdylib `sock_send` connected
      to 127.0.0.1 through the QNX io-pkt stack and pushed 8 bytes; the C decoder-side harness recv'd exactly
      `deadbeefcafebabe`. Serial: `rust sock_send returned 8 / recv n=8 ok=1 / SOCK: PASS`, exit 0.
      ROOT CAUSE + FIX (no BSP rebuild): decompiled io-pkt `cache_init` @0x17d6a8 - on a NULL dll arg it
      builds `cache-%s-%s.so` and `dlopen`s a cache-controller DLL that doesn't exist on the hand-built
      QEMU-virt BSP -> returned -1 (ESRCH). `cache_init` has an env escape hatch checked first:
      **`CACHE_MSYNC=1`** -> kernel msync flush/invalidate coherency, skips the dlopen path entirely.
      Set `CACHE_MSYNC=1` before `io-pkt-v4 &` and the stack inits, `/dev/socket` appears, loopback works.
      (`Unable to attach to pci server` + `pseudo random generator` slog lines are harmless for loopback.)
      Isolated sim sandbox for the debugging lives in `sim/` (does not touch qnx-gl-passthrough).
- [x] **MILESTONE 3 PASSED (2026-07)** - `alloc` works: `alloctest/` cdylib with a `GlobalAlloc`
      over QNX `malloc`/`free`/`posix_memalign` ran Vec (grew to cap=16384 = many realloc/free),
      Box, String on the real QNX heap. Serial: `sum=49995000 bsum=43520 slen=20 -> PASS`, exit 0.
      (`-Z build-std=core,alloc`; align<=8->malloc else posix_memalign; `#[alloc_error_handler]`.)
- [x] **MILESTONE 4 PASSED (2026-07)** - real altscreen NAL pipeline end-to-end on QNX 6.5:
      `altpipe/` = pure `avcc_to_annexb` reframer (no_std, 7 host unit tests), reused by `altpipe_test/`
      cdylib. Rust HOOK framed AVCC NALs (`[u32 len][payload]`) + TCP-sent through io-pkt; Rust DECODER
      recv'd + reframed to Annex B (00000001 start codes) matching the expected bytes.
      Serial: `alt_send=26 / payload_len=26 / alt_decode->26 / annexb=000000016742000a / ALT: PASS`, exit 0.
      This is the first real `altscreen_render` logic (wire proto from `altscreen_av.h` + AVCC->AnnexB) on-target.
- [x] **float ABI fixed (2026-07)** - target now `+v7,+vfp3,-d32` + `llvm-floatabi:soft` = softfp,
      objects report `Tag_VFP_arch: VFPv3-D16` (matches stock QNX binaries; call ABI stays soft ->
      ABI-compatible with QNX libc/libsocket). Regression-checked: sockfwd TCP test still PASSes.
- [x] **one-command cross-build (2026-07)** - `./build.sh <crate> <symbol> [ld flags]` does
      cargo->ship->link-on-VM->pull. `rust-toolchain.toml` pins nightly+rust-src (no `+nightly`/`-Z` typing).
- [x] **panic = abort, done right** - `#[panic_handler]` prints `RUST PANIC <file>:<line>` then calls
      libc `abort()` (was a silent `loop{}` deadlock). alloc OOM handler aborts too.
- note: `ntoarm-ld` warns `Unknown EABI object attribute 34` (softfp/vfp3 -> LLVM emits Tag_MPextension_use;
  binutils 2.19 doesn't know it) - benign, linker skips it; runtime verified working.
- [x] **VM-FREE toolchain (2026-07)** - link step moved from the SSH-to-VM path onto the
      in-image QNX toolchain (x86-Linux host tools). No VM needed for the whole
      build->link->mkifs->QEMU loop; now the in-image gcc links (see the top-level README).
- [x] **FULL `std` - M1 PASSED (2026-07)** - Scope B is now real, not just no_std. A full-`std` Rust
      executable (`stdhello/`, `fn main(){ println!("std boot"); }`) built with
      `-Z build-std=std,panic_abort -Z build-std-features=` and BOOTED on real QNX 6.5 armv7 in QEMU:
      serial showed `std boot` then `Process 3 (stdhello) exited status=0`. Proves stdout/write/errno/
      fmt/global-alloc all live under std. Proof: `m1/stdhello.bin` + `m1/stdhello-virt.build`.
      What the std port required (all kept reproducible, `./port/apply_std_port.sh` + `./build_std.sh`):
        * **libc**: forked `libc-0.2.185` (`vendor/libc/`), added `src/unix/nto/arm.rs` (32-bit ARM nto
          arch module: `time_t=u32` per 6.5 `__TIME_T=_Uint32t`, arm_cpu/fpu registers, mcontext, stack_t),
          wired `target_arch="arm"`, and stopped linking `-lregex` on `nto65` (6.5 folds regex into libc).
        * **std source**: 32-bit-time_t cast in `sys/pal/unix/time.rs` (TIMESPEC_MAX_CAPPED `as _`), and
          in `sys/fs/unix.rs` the file-time reads are redirected from `st_*tim.tv_sec`/`.tv_nsec` to the
          real `__old_st_*time` fields - QNX 6.5's `struct stat` has NO `st_*tim` timespec (only the
          32-bit `st_*time`), so the binding's `st_*tim` sits past the struct's end and reading it gives
          zero/garbage mtimes; `__old_st_*time` is what `fstat` actually fills (nsec = 0, no sub-second).
        * **backtrace off**: QNX 6.5 has no `dl_iterate_phdr` and only an inline EHABI `_Unwind_GetIP`;
          `-Z build-std-features=` drops gimli, and `shim/libqnxunwind.a` (a 12-line C shim over
          `_Unwind_VRS_Get`) provides the `_Unwind_GetIP`/`GetIPInfo` symbols std still references.
        * **linker `qnx-cc`**: remaps `-lgcc_s`->`-lgcc` (6.5 has only static libgcc.a), re-adds the
          sysroot `-L` that `-nodefaultlibs` drops, appends the unwind shim; target json PIE off
          (6.5 crt1.o has no `__preinit_array_start`).
      POSIX surface confirmed on 6.5: HAS posix_spawn/O_CLOEXEC/clock_gettime/pthread_setname_np;
      MISSING pipe2/accept4/SOCK_CLOEXEC/ppoll/preadv/dup3/eventfd/getrandom (shim as std hits them).
- [x] **`+strict-align` - critical (2026-07)** - QNX 6.5 procnto runs `SCTLR.A=1`; unaligned loads
      SIGBUS (fltno=5, odd `ref=`). std's integer `fmt::num` Display read its LUT unaligned ->
      `println!("{}", n)` faulted until `+strict-align` was added to the target features. Scoped to the
      Rust std target only - NOT a blanket emulator default (see `port/PLATFORM_NOTES.md`; emulator
      hot paths want `SCTLR.A=0` instead). Symptom: SIGBUS with odd `ref` in fmt/memcpy.
- [x] **std M2-M5 ALL PASSED (2026-07)** on real QNX 6.5 armv7 QEMU - std is functionally complete:
        * **M2** `stdtest/`: 8 threads + per-thread `thread_local!` isolation + `Arc<Mutex>` + `AtomicU32`.
        * **M3** `stdtest/`: fs write/read/metadata/remove, `Instant` monotonic, `env::args`.
          (`SystemTime::now`=0 - bare QEMU has no RTC, not a std bug.)
        * **M4** `stdtest/`: `Command::new(sh).status()` -> posix_spawn, child exit code read back.
        * **M5** `nettest/`: `TcpListener`/`TcpStream` loopback echo (8B) + `UdpSocket` send/recv,
          through real io-pkt-v4 (`run_qemu_net.sh` starts it with `CACHE_MSYNC=1`).
        * **torture** `tortst/`: HashMap(1000)/HashSet/BTreeMap, `env::var`, `eprintln!`, fmt
          precision/hex/binary/scientific, sort+dedup - all correct.
      Random gap closed: QNX `/dev/random` (via the `random` daemon, needs libz.so.2) EAGAINs before its
      pool is primed and there's no `/dev/urandom`; std's `sys/random/unix_legacy.rs` was patched to
      retry on WouldBlock (`port/patches/std_random_unix_legacy.rs`). `run_qemu.sh` starts `random -t`
      + symlinks `/dev/urandom`->`/dev/random`.
      Panic=abort (a thread panic aborts the process - by design; no catch_unwind/backtrace, since 6.5
      lacks dl_iterate_phdr and shared unwind). All deltas reproducible: `./port/apply_std_port.sh`
      then `./build_std.sh <crate>` (+ `./run_qemu.sh`/`run_qemu_net.sh <bin>` to boot in QEMU).
- [x] **smallest dynamic binary (2026-07)** - binaries are already dynamically linked (NEEDED
      libc.so.3 [+ libsocket.so.3]); std itself is linked *statically* (build-std emits only rlibs, no
      shared libstd.so - Rust dylib crate-type isn't produced for a custom target, so `-C
      prefer-dynamic` has nothing to bind and falls back to static). Practical size floor for a
      static-std binary: `[profile.release] panic="abort", opt-level="z", strip=true` + build-std
      `-Z build-std-features=` (backtrace off) -> **stdhello 202KB -> 122KB**. Do NOT use `lto` - with
      build-std it makes the binary BIGGER (274KB) and interferes with stripping. A shared libstd.so
      (~15KB/binary + one ~2-3MB .so) would need manually building the std dylib; only worth it with
      many Rust binaries, not a single hook/.so.

## Reproduce (in this image)
```sh
# full-std binary - build_std compiles std + links via the in-image QNX gcc
build-std <crate-dir>
# -> <crate-dir>/target/armv7-unknown-nto-qnx650/release/<crate>  (ARM QNX ELF)
```
On-device: package the binary into an IFS with `mkifs` and boot it in QEMU
(`qemu-system-arm -M virt -cpu cortex-a15`) - see the `qnx-gl-passthrough`
harness for the `.build` + boot invocation (real procnto + libc.so.3).
