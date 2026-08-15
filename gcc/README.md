# gcc - GCC 8.5.0 (C++17) cross-compiler for QNX 6.5 / armle-v7

The image's C/C++ compiler: **GCC 8.5.0** with full **C++17** (structured
bindings, `if constexpr`, fold expressions, `<optional>`, `<variant>`,
`<string_view>`, `<filesystem>` via `-lstdc++fs`) and C11, targeting the QNX
6.5 SDP as-is: binutils **2.19**, the 6.5 `armle-v7` sysroot, triplet
`arm-unknown-nto-qnx6.5.0eabi`. `build.sh` applies `port/` onto vanilla
upstream gcc-8.5.0 and builds in the `gcc-build` Docker stage; the result is
merged into the SDP host tree in the final image, exactly where the stock
4.4.2 lived.

This is a forward-port of the earlier GCC 4.9.4 port (in git history), which
in turn replaced the stock 4.4.2. The 4.9-era design notes below are kept as
the defect log - each "vs 4.9" delta documents a real Dinkum/binutils trap
and why the fix looks the way it does.

## ABI: static libstdc++ by default

GCC 8's libstdc++ is dual-ABI (`_GLIBCXX_USE_CXX11_ABI=1` default) and NOT
link-compatible with the device's `libstdc++.so.6.0.13` (GCC 4.4 era). Link
C++ with **`-static-libstdc++ -static-libgcc`** (the `libstdc++.a` is
assembled by `build.sh`, same trick as the 4.9 port), or ship the new
`libstdc++.so.6` (v6.0.25) into the device image. C output is unaffected (same
libc.so.3).

## binutils 2.19 stays (probe-verified)

GCC 8's output assembles with the stock gas 2.19 after two source-side fixes
(`port/apply.sh`): the trap insn `.inst` -> `.word`/`.short` (as in 4.9), and
`vmrs APSR_nzcv, FPSCR` -> `fmstat` (pre-UAL name of the same instruction -
the only UAL VFP mnemonic 2.19 lacks; it is also exactly what 4.9 emits).
Everything else (`.loc` discriminators, `.cfi_sections` codegen, DWARF
version) is auto-suppressed because configure probes the real 2.19. libgcc's
hand-written ARM asm carries unconditional `.cfi_*` - stripped by apply.sh
(debug-only, matches what the 4.9 libgcc shipped).

## Port delta vs the 4.9 port (git history)

- **`port/arm-nto.h`**
  - `TARGET_UNIFIED_ASM` dropped (GCC 6+ always emits unified syntax).
  - `SUBTARGET_OVERRIDE_OPTIONS` must mark the forced
    `-mno-unaligned-access` (SCTLR.A=1!) as *user-set*: GCC 8 re-resolves
    any not-user-set value, silently re-enabling unaligned access.
  - `INTPTR_TYPE`/`UINTPTR_TYPE` defined (= QNX `_Intptrt`/`_Uintptrt`);
    libstdc++ 8 uses `__UINTPTR_TYPE__` directly and no *-stdint.h is used.
  - `LINK_SPEC` adds **`--target2=rel`**: R_ARM_TARGET2 (typeinfo refs in
    `.ARM.extab`) is platform-defined, and only `rel` matches what libgcc's
    EHABI unwinder decodes on non-linux targets. Without it EVERY throw
    SIGSEGVs (QEMU-verified; the 4.9 baseline has the same latent bug -
    exceptions never worked on-device there either). Ceiling: catching by a
    typeinfo imported from another `.so` can't GOT-indirect under `rel`;
    static libstdc++ / same-module catches are unaffected.
- **`port/qnx-os_defines.h`** - the Dinkum-vs-libstdc++8 arbitration:
  - `_HAS_C9X=1`: the terminal Dinkum C99 gate. g++ can never reach it via
    the header routes (platform.h re-derives `__EXT_ANSIC_199901` from the
    C-only `__STDC_VERSION__`, and the `__GNUC__` fallback dies under strict
    `-std=c++NN`). Unlocks isblank/snprintf/strtoll/... declarations ->
    `_GLIBCXX_USE_C99*` -> `std::to_string` etc.
  - `_GLIBCXX_USE_C99_CTYPE_TR1`: turns on `<cctype>`'s own
    `#undef isblank; using ::isblank` fix for QNX's isblank macro.
  - function-like `is*/to*` ctype macro undefs (their bodies reference the
    `_UP/_LO/...` masks the port already removes; calls fall through to the
    real libc functions - all present in libc.so.3, isblank included).
  - `__CORRECT_ISO_CPP11_MATH_H_PROTO_FP/_INT`: Dinkum math.h (with
    `_HAS_C9X`) already provides the C++11 classification overload set
    (fpclassify/signbit/isnan/... in std, reachable through `_CSTD` wrapper
    macros that `<cmath>` #undefs); these knobs stop `<cmath>` from
    redefining it. Ceiling: `std::isnan(int)` (integer-arg classification)
    is ambiguous - classify FP values, not ints.
- **`port/apply.sh`**
  - config.gcc / libgcc stanzas re-anchored on the 8.5 case labels;
    `target_cpu_cname=generic-armv7-a` (8.x defaults `with_cpu` from it).
  - `sync.md` `dmb ish` -> `dmb sy` (gas 2.19 knows no barrier domains; `sy`
    is a superset and is what 4.9 emits).
  - libgcc arm `.S`: strip `.cfi_*` (unconditional `.cfi_sections`).
  - `stl_map.h`/`stl_multimap.h`: template param `_C2` -> `_Cmp2` (QNX
    yvals.h defines `_C2`; undef would break math.h's `FP_ILOGB0`).
  - `system_error.cc`: guard the `EALREADY` case (QNX 6.5: == `EBUSY`).
- **`build.sh`**
  - GCC 8.5.0 tar.xz; `--enable-libstdcxx-filesystem-ts` (else no
    `libstdc++fs.a` in a cross build).
  - `*FLAGS_FOR_TARGET += -D_HAS_C9X=1 -D_NO_CPP_INLINES=1`: libstdc++'s
    configure probes include QNX headers RAW (no os_defines in their chain);
    without mirroring the gates the probes and the library disagree about
    what `<math.h>`/`<stdio.h>` declare.
  - same wchar_t/size_t fixincludes fixes and static-`libstdc++.a` assembly
    as `gcc/build.sh`.

## Validated (QEMU, real procnto + libc.so.3: `-M virt -cpu cortex-a15`)

C++17 core (structured bindings, init-if, fold expressions), `std::variant`/
`optional`/`string_view`, `map::merge`, 4 threads + atomics + mutex
(`dmb sy` barriers), virtual dispatch, **exceptions** (throw/catch, needs
the `--target2=rel` default), `std::sqrt`/classification, `std::to_string`,
packed-struct access under strict alignment. `<filesystem>` links via
`-lstdc++fs` (degrades per configure: no `d_type`, no `*at` on 6.5).
