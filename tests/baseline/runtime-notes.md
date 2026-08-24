# Runtime wrong-answer baseline

`tests/runtime.sh` executes every gcc.c-torture test ON the target and checks
the exit status, not just that it compiles. A test that calls `abort()` when
its self-check fails and does abort is a genuine miscompilation.

## 4.9: 4 real bugs, 1 false positive

Investigated by hand on 2026-08-24 (`tests/baseline/runtime-4.9.wrong`):

- `pr68648`, `pr94591`, `pr97421-2`, `pr97421-3` - each calls
  `__builtin_abort()`/`abort()` on its own self-check, confirmed via the QEMU
  log (`Process N (name) exited status=1/3/...`, not 0). All four are `prNNNNN`
  regression tests for GCC bugs found and fixed **after** 4.9.4 shipped in 2016
  (`pr97421-2`/`-3` are specifically about `-fmodulo-sched`, a known-bad RTL
  scheduler pass of that GCC generation). Backporting those upstream fixes into
  our GCC 4.9.4 port is out of scope - it would mean maintaining a private GCC
  fork, not a QNX port. Documented as a known limitation of the `:4.9` variant,
  not something to chase.

- `pr90949` looked identical (wrong exit status) but is NOT a codegen bug: its
  `main()` has no `return 0;`. Under C99+ that is well-defined (implicit
  `return 0`); under GCC 4.9's DEFAULT dialect, `-std=gnu90`, it is undefined
  behaviour - the exit status is whatever garbage sat in the return register.
  Proof: the same source compiled with `-std=gnu90` gave two DIFFERENT garbage
  exit codes on two separate runs (1048388, then 1048372); compiled with
  `-std=gnu99` it returns 0 cleanly every time. `pr90949` is a GCC bugzilla
  number from ~2019, well after 4.9.4 shipped, so this test was never run
  against 4.9 by anyone, including upstream - it assumes C99+ semantics that
  4.9's default dialect does not provide. Not counted as a compiler defect.

## 8.5: 0 wrong answers (1476 executed)

No investigation needed.
