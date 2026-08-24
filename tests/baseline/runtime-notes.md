# Runtime wrong-answer baseline

`tests/runtime.sh` executes every gcc.c-torture test ON the target and checks
the exit status, not just that it compiles. A test that calls `abort()` when
its self-check fails and does abort is a genuine miscompilation.

## 4.9: 4 real bugs (unidentified), 1 false positive

Investigated by hand on 2026-08-24 (`tests/baseline/runtime-4.9.wrong`):

- `pr68648`, `pr94591`, `pr97421-2`, `pr97421-3` - each calls
  `__builtin_abort()`/`abort()` on its own self-check, confirmed via the QEMU
  log (`Process N (name) exited status=1/3/...`, not 0). Genuine, reproducible
  miscompilations at plain `-O2` - **not** the upstream bugs the c-torture
  filenames suggest. gcc.c-torture names each regression test after the PR
  that motivated adding it, but the test itself is target-generic; the PR
  number is where GCC decided to add the test, not proof of which bug you hit
  on a given target. Checked directly, not assumed:
    - `pr94591` claims to be an AArch64 NEON `REV64` encoding bug, but our
      build has no NEON at all (`.fpu vfpv3-d16`) and `__builtin_shuffle`
      compiles to plain `ldr`/`str` here - a completely different code path.
    - `pr97421-2` requires `-fmodulo-sched -fno-dce -fno-strict-aliasing` via
      `dg-additional-options`, which the harness does not apply (bare `-O2`).
      Compiled with those exact flags it passes cleanly (`exit=0`); without
      them it fails. So the bug we hit at bare `-O2` is not the
      modulo-scheduler bug that PR was filed about.
    - `pr97421-3` (needs only `-fmodulo-sched`) fails identically with and
      without that flag, so no conclusion either way there.
  An earlier version of this note claimed these were "found and fixed
  upstream after 4.9.4 shipped" and that backporting was merely out of scope.
  That was wrong: there is no known patch to backport, because these are not
  confirmed to be the bugs their filenames name. Root-causing them for real
  would mean bisecting GCC 4.9.4's own optimization passes against a minimal
  reproducer - compiler engineering, not a cherry-pick - so they stay
  documented as an unidentified limitation of `:4.9` rather than pursued.

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
