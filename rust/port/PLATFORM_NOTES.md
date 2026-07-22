# QNX 6.5 ARMv7 platform notes (bear on the Rust std target choices)

## Unaligned access — why the std target carries `+strict-align`
QNX 6.5 procnto boots with **`SCTLR.A=1`** (strict alignment). Any unaligned
`ldr`/`str` SIGBUSes (fltno=5, odd `ref=`). std's integer `fmt::num` Display
reads its 2-digit LUT unaligned, so `println!("{}", n)` deterministically faulted
until `+strict-align` was added to `armv7-unknown-nto-qnx650.json` features.

`+strict-align` is deliberately scoped to the **Rust std target only**:
- A deployed std binary runs on the stock HU whose A-bit is fixed by the factory
  startup (not ours) — strict-align is correct for A=1 *or* A=0, so it's the safe,
  portable choice. std is also not an emulator hot path, so the byte-op penalty is
  marginal here.
- Do **NOT** make `-mno-unaligned-access` / `+strict-align` a blanket compiler
  default for the emulator work (gpSP / PCSX / mib2q dynarec). There the hottest
  path is `*(u32*)(guest_mem+addr)`; strict-align turns each into 4 byte-ops.
  Preferred there, in order: (a) run that target with `SCTLR.A=0` (Cortex-A15
  handles unaligned to normal memory in HW, keeps the fast `ldr`); (b) lean on the
  emulator's own aligned-access helpers; (c) `-mno-unaligned-access` per-file only.
  Keep such a "never-SIGBUS" build as a separate qcc profile, not the default.

## JIT / dynarec (not used by std, kept for a future Rust dynarec)
W^X is not enforced: `mmap(PROT_READ|WRITE|EXEC, MAP_ANON)` returns RWX pages with
no privilege. The one required ARM step after emitting code is the I-cache flush —
`__builtin___clear_cache(code, code+len)` — omit it and execution hits stale/garbage
insns and crashes randomly. Strict-W^X variant: mmap RW → write → `mprotect(RX)` →
`clear_cache` → run. Only the stack is NX (irrelevant to a heap code-cache; use
`-Wl,-z,execstack` if an executable stack is ever needed).
