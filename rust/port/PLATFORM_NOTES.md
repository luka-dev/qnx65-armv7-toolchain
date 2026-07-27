# QNX 6.5 ARMv7 platform notes (bear on the Rust std target choices)

## Unaligned access - why the std target carries `+strict-align`
QNX 6.5 procnto boots with **`SCTLR.A=1`** (strict alignment). Any unaligned
`ldr`/`str` SIGBUSes (fltno=5, odd `ref=`). std's integer `fmt::num` Display
reads its 2-digit LUT unaligned, so `println!("{}", n)` deterministically faulted
until `+strict-align` was added to `armv7-unknown-nto-qnx650.json` features.

`+strict-align` is set on the Rust std target, and the C/C++ compiler now
**defaults** to `-mno-unaligned-access` too (see the root README) - both because
QNX 6.5 procnto boots `SCTLR.A=1`, where an unaligned access SIGBUSes. std is not
an emulator hot path, so the byte-op penalty there is marginal.
- **Emulator hot paths** (gpSP / PCSX / mib2q dynarec) still need care. The inner
  loop is `*(u32*)(guest_mem+addr)`, and `-mno-unaligned-access` does NOT protect
  that raw cast - the pointer promises alignment, so GCC still emits an `ldr` that
  SIGBUSes on A=1. So the compiler default is not enough there; in order: (a) run
  that target with `SCTLR.A=0` (Cortex-A15 handles unaligned to normal memory in
  HW, keeps the fast `ldr`); (b) lean on the emulator's own aligned-access
  helpers; (c) override with `-munaligned-access` per-file for speed once the
  A-bit is under your control.

## JIT / dynarec (not used by std, kept for a future Rust dynarec)
W^X is not enforced: `mmap(PROT_READ|WRITE|EXEC, MAP_ANON)` returns RWX pages with
no privilege. The one required ARM step after emitting code is the I-cache flush -
`__builtin___clear_cache(code, code+len)` - omit it and execution hits stale/garbage
insns and crashes randomly. Strict-W^X variant: mmap RW -> write -> `mprotect(RX)` ->
`clear_cache` -> run. Only the stack is NX (irrelevant to a heap code-cache; use
`-Wl,-z,execstack` if an executable stack is ever needed).
