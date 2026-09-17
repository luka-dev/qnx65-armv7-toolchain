# C++ toolchain audit — 2026-09-16

**Historical baseline.** The confirmed GCC 8.5 defects below were repaired on
2026-09-17. See [FIXES.md](FIXES.md) for the implementation, validated image IDs,
test results and remaining limitations. The following findings describe the
original images; the reproducers now serve as regression tests.

The installed GCC 8.5 toolchain has three confirmed runtime defects: recursive
`<cmath>` overloads, broken mutex address reuse, and second-resolution C++ clocks.
The normal `host-scripts/qnx-selftest.sh` passes despite all three.
There are also reproducible header compatibility failures and a stale Docker tag.

This audit adds reproducers and records findings. It does **not** modify compiler
headers, rebuild/tag images, deploy binaries, or restart the HU.

## Environment and scope

- Source checkout: `4440b75d`.
- Compiler/runtime tested: `qnx65-armv7-toolchain:latest` = `:8.5-full`, GCC 8.5.0.
- Image: `sha256:5d9d97c0944b54f96b28c9a5d7a458035b9c23663d0a849f6932fdd44f65501f`,
  built 2026-08-26.
- Installed `bits/os_defines.h` SHA-256:
  `172b1b650993b427e7e97c8264c8218667409be27957924fc2118b2e52c17b46`.
- ARM programs execute under real QNX 6.5 using `tests/qemu-run.sh`, the `:8.5`
  guest sysroot, and Homebrew QEMU 11.0.3. No RetroArch C++ compatibility header
  or sanitized archive is used. The mutex control explicitly adds one define.
- C++ math is built at `-std=c++17 -O2`; header probes cover `c++11` and `gnu++11`.
- GCC 4.9 is a **compile-only comparison**, not a runtime validation in this audit.

These are targeted tests, not a full compiler/ABI certification. The math matrix
checks dispatch and representative values, not comprehensive libm accuracy,
NaN/signed-zero behavior, mixed argument types, or floating-point exceptions.
This audit does not cover Go/Rust, GPU drivers, or device-specific scheduling.

## 1. Critical: 34 math functions recurse for float and long double

Result: **168 cases, 100 pass, 68 timeout**. All 56 double cases pass.
Both float and long-double overloads of these 34 functions hang:

```
acosh asinh atanh cbrt copysign erf erfc exp2 expm1 fdim fma fmax fmin
hypot ilogb lgamma llrint llround log1p log2 logb lrint lround nearbyint
nextafter nexttoward remainder remquo rint round scalbln scalbn tgamma trunc
```

Minimal example (input must be runtime data):

```cpp
#include <cmath>
float f(float x) { return std::round(x); }
```

The cause is in [qnx-os_defines.h](../../gcc/port/qnx-os_defines.h):
`_NO_CPP_INLINES` disables the concrete Dinkum overloads;
`__CORRECT_ISO_CPP11_MATH_H_PROTO_FP` also disables the GNU replacements;
Dinkum `_TGEN_*` templates remain and resolve back to themselves.
At `-O2`, e.g. `std_round_f`, `std_hypot_f`, and `std_fma_f` contain a `b` to
that same instruction **without a relocation**. These are real loops, not an
unresolved external tail call in a relocatable object.

Each candidate is compared against the corresponding explicit C libm function.
A 100 ms signal timer escapes a stuck scalar call, so the remaining cases run.
The C references return successfully. The matrix links with `gcc -lm` and
does not link libstdc++, proving this is generated from headers.

This extends the previously diagnosed `fmin`/`fmax` renderer defect. It is
different from the August 24 `math_stubs` library fix (`95917883`).

Fix direction: give GNU `<cmath>` a complete, consistent overload set and prevent
conflicting Dinkum templates. Do not simply remove the two `__CORRECT_*` flags:
classification redefinitions must be addressed too. An isolated trial disabling
`_HAS_GENERIC_TEMPLATES` and removing both flags still fails to compile because
GNU `<cmath>` expects global `::isinf`/`::isnan` declarations. The configure
assumptions and header ownership need to be fixed together. No trial change
was applied to the source tree or retained Docker image.

## 2. High: std::mutex lifetime does not release QNX synchronization state

`runtime.cpp` placement-constructs a mutex/condition-variable object, runs and
joins a waiter, destroys the object, then reuses the same storage.

Without workarounds:

```
PASS exceptions
SYNC round=0
SYNC round=1
terminate called after throwing an instance of 'std::system_error'
  what(): Invalid argument
Process 3 (runtime-raw) terminated SIGABRT
```

With `-D_GTHREAD_USE_MUTEX_INIT_FUNC`, the same toolchain/archive passes all 32
reuse cycles, future/promise, thread-local isolation, and concurrent atomic64
increments. It subsequently fails the independent clock check, exit 5.

The preprocessed `std::__mutex_base` uses `PTHREAD_MUTEX_INITIALIZER` and a
default destructor. QNX keeps kernel synchronization state associated with the
address; overwriting the object for a new lifetime does not destroy that state.
The define selects explicit `pthread_mutex_init`/`pthread_mutex_destroy` instead.

RetroArch already uses this workaround in `Common/QnxCompat.h`; the common
toolchain does not. Fix the QNX gthread policy centrally, rebuild libstdc++ and
consumers consistently, and test mutex/recursive-mutex/timed-mutex lifetimes.
Only ordinary mutex plus condition-variable reuse was validated here.

## 3. High: steady_clock and system_clock have one-second resolution

`clock.cpp` compares four 200 ms sleeps against direct `CLOCK_MONOTONIC`:

```
steady_clock::is_steady=1
CLOCK c_monotonic_ns=203999796 cxx_steady_ns=0 cxx_system_ns=0
CLOCK c_monotonic_ns=204999795 cxx_steady_ns=0 cxx_system_ns=0
CLOCK c_monotonic_ns=203999796 cxx_steady_ns=0 cxx_system_ns=0
CLOCK c_monotonic_ns=204999795 cxx_steady_ns=1000000000 cxx_system_ns=1000000000
CLOCK_AUDIT cases=4 fail=4
```

Installed `c++config.h` leaves `_GLIBCXX_USE_CLOCK_MONOTONIC`,
`_GLIBCXX_USE_CLOCK_REALTIME`, and `_GLIBCXX_USE_GETTIMEOFDAY` undefined.
Disassembly confirms `steady_clock::now()` calls `system_clock::now()`, which
calls `time()` and multiplies seconds by 1e9. Thus even the nominal steady clock
uses wall time. Its behavior under an actual system-time adjustment was not
tested; the fallback itself is verified.

This can break animation deltas, profiling and short C++ timeouts. The direct
clock advances normally in the same guest, separating the defect from QEMU's
timer behavior. The sleep itself works.

Fix QNX cross-configuration to detect/enable CLOCK_MONOTONIC and CLOCK_REALTIME
and rebuild libstdc++. Defining these macros only in application code will not
replace the already-compiled `chrono` implementation.

## 4. High: legal include order still breaks C++ compilation

Minimal examples:

```cpp
#include <stdio.h>
#include <cstdlib>
// malloc.h:40: typedef __SIZE_T size_t;
// error: declaration does not declare anything
```

```cpp
#include <stdint.h>
#include <mutex>
// cxxabi_init_exception.h: 'size_t' was not declared in this scope
```

```cpp
#include <ctype.h>
#include <complex>
// strict c++11: '::isblank' has not been declared
```

In the first example, QNX consumes its `__SIZE_T` type carrier, then GCC's
`stddef.h` defines `__SIZE_T` as an empty guard macro. `malloc.h` later treats it
as a type again, producing `typedef size_t;`. In the second, `std::size_t`
exists but global `size_t` is missing. The `isblank` case has already consumed
the C header before the GNU compatibility layer enables C99 declarations.
The early setup in `os_defines.h` is still too late when a C header is first.

Out of 112 C/C++ header pairs, 59 fail in strict C++11 and 58 in GNU C++11:
52 with the empty carrier as the first diagnostic, 6 with missing global
size_t, and one additional strict-mode isblank failure. These are related
families of failures, **not 59 independent bugs**.

Fix the carrier/namespace/feature-gate interaction in the shared headers and
fixincludes policy. Validate C, C++, both include orders and both GCC variants;
local include reordering only hides the problem for one consumer.

## 5. Medium: cmath macro leakage and integer classification

After `<cmath>`, all of `cosf`, `coshf`, `sinf`, `sinhf`, `logf`, `log10f` still
expand as QNX macros. Both `::cosf(x)` and `std::cosf(x)` fail to compile;
the other five behave the same. `( ::cosf )(x)` bypasses the macro and works.
The math matrix uses this spelling for its C references. `log2f` was also
tested and does not exhibit this leakage on GCC 8.5.

`std::isfinite(5)`, `isinf(5)`, `isnan(5)`, `isnormal(5)`, `signbit(5)` and
`fpclassify(5)` are ambiguous; corresponding float and double probes pass.
This limitation was already acknowledged in `qnx-os_defines.h`, but it remains
a C++ compatibility defect and belongs in the math repair/regression suite.

All 150 compile probes: **73 pass / 77 fail** in c++11; **74 / 76** in gnu++11.
GCC 4.9 comparison: **45 / 105** and **51 / 99**, respectively. The 4.9 totals
include its older C99/C++ support gaps and should not be called new regressions.

## 6. High: local :8.5 tag still contains the old shared-library math bug

The local `:8.5` image is from August 23:
`sha256:d3a1485fa996bb1473e7f614b85540d8bd1c38947f9c53f1f7b300e143b20776`.
Its static archive is sanitized, but its **shared** libstdc++ still exports the
old recursive stubs, including:

```
0008fcd4 <sqrtf>: eafffffe  b 8fcd4 <sqrtf>
0008fcc0 <ceilf>: eafffffe  b 8fcc0 <ceilf>
0008fd7c <powf>:  eafffffe  b 8fd7c <powf>
```

The newer `:latest`/`:8.5-full` image has the August 24 fix. This is stale local
build output, not a missing source fix. Rebuild supported tags from the same
revision and check both static and shared runtimes. The current selftest only
checks the default image's static archive for this defect.

## Reproduction and evidence

Run the complete audit (passes on the repaired GCC 8.5 images; fails on the
original images recorded above):

```sh
bash tests/cxx-audit/run.sh
```

Use `QNX_AUDIT_RUN_QEMU=0` for compile-only checks. `QNX_AUDIT_IMAGE` selects the
compiler image; the full runner requires GCC 8/C++17. To repeat only the 4.9
header comparison, run `compile-probes.py OUTPUT_DIRECTORY` inside that image.
`QNX_AUDIT_GUEST_VARIANT` selects the SDK used to package the QNX guest.
`QNX_AUDIT_OUT` selects the artifact directory, default `tests/.cache/cxx-audit`.

- `generate-math.py` + `math-driver.h`: 56 functions × 3 types, direct C reference.
- `compile-probes.py`: 112 include pairs + 18 classification + 14 macro + 6 type probes,
  each under two dialects; JSON records every result, per-case logs hold errors.
- `runtime.cpp`: exceptions, synchronization reuse, future, TLS, atomic64 and clock.
- `clock.cpp`: independent C versus C++ clock comparison, nonzero on failure.
- `baseline-20260916.json`: compact recorded results and image identity.

Original full logs, binaries, preprocessed headers and disassembly are retained
locally in `tests/.cache/audit-20260916/`. A compile-only invocation of the final
runner was also checked in `tests/.cache/audit-20260916-runner/`; runtime cases
were built and executed individually during the audit. All three runtime
defects returned an explicit QNX error/status, not just a host timeout.

Repair order: math overload ownership; QNX mutex lifecycle; chrono configure;
header include ordering/macro cleanup; rebuild all advertised tags. Extend the
normal selftest with runtime checks so successful compilation cannot conceal
these failures again.
