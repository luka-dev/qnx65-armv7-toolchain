# GCC 8.5 C++ repairs — 2026-09-17

The confirmed GCC 8.5 defects in the [September 16 audit](README.md) are fixed
in the compiler port and rebuilt base/full images. This includes header-generated
math loops, mutex lifetime failures, coarse/non-monotonic C++ clocks, header
ordering, leaked math macros and integer classification. Shared-library testing
also exposed and fixed split `call_once` state caused by blanket `-Bsymbolic`.

## Changes

- The compiler sets the QNX C++ feature gates before any C header is read.
  GNU `<cmath>` owns the complete overload set; Dinkum generic templates are
  disabled and the incorrect `__CORRECT_ISO_CPP11_MATH_H_PROTO_*` claims removed.
  A compiler-local `include-fixed/math.h` adapter gives raw configure probes
  working classification macros. `<cmath>` removes QNX's suffixed libm macros.
- `os_defines.h` establishes global `size_t`/`ptrdiff_t` and removes GCC's empty
  guard macros that QNX headers mistakenly consume as type names.
- QNX uses explicit mutex and recursive-mutex initialization/destruction,
  releasing kernel synchronization state before an address is reused.
- Cross-configuration enables `clock_gettime` for monotonic/realtime clocks,
  plus `nanosleep` and `sched_yield`. The runtime is rebuilt with those settings.
- The shared runtime retains local RTTI binding required by the QNX ARM loader,
  but permits exported non-RTTI data to interpose. A dynamic list derived from
  the actual exports prevents executable COPY relocations from splitting
  `std::__once_functor` and iostream state. The resulting library has no dynamic
  `R_ARM_REL32` relocations, and shared exception/future tests execute correctly.
- Selftests check both static/shared math stubs, actual math call references,
  header order and runtime configuration. `--runtime` runs the QNX regression
  matrix. The guest runner now packages the compiler's shared C++ runtime when
  the ELF needs it, and fails if a process exit status is missing.
- Clean Docker builds hit removed Bullseye security package URLs. A signed
  Debian repository snapshot, `20260831T235959Z`, now matches the pinned base
  image. Only historical `Valid-Until` expiry is ignored; signatures and package
  checksums remain enforced. See the [Debian mirror notice](https://lists.debian.org/debian-mirrors/2026/09/msg00001.html).

## Validation

Tests ran on ARM under the QNX 6.5 guest using the rebuilt GCC 8.5 image.

| Check | Result |
| --- | --- |
| C++ math, 56 functions × 3 types | 168/168 pass; previously 68 timeouts |
| Header/classification/macro/type probes, strict and GNU C++11 | 300/300 pass |
| Static and shared C++ runtime | Both pass |
| Ordinary, recursive, timed, recursive-timed mutex address reuse | 32 cycles each pass |
| Futures, timed wait, TLS, concurrent atomic64, iostream, exceptions including a library throw | Pass |
| C++ clocks compared with direct `CLOCK_MONOTONIC` | 4/4 subsecond samples pass |
| Upstream libstdc++ compile suite, positive tests | 7038/7198 pass |
| Upstream libstdc++ compile suite, negative tests | 245/249 correctly rejected |
| Change from recorded compile baseline | 32 failures fixed, zero new failures |
| Base/full selftests | Pass |
| Base/full compiler, headers, static/shared runtime hashes | Identical |
| Actual `mhi2-carplay` maneuver/alternate-screen renderer builds | Both pass |
| Maneuver CPU geometry test in QNX | 729 combinations and 32 camera fits pass |

The maneuver CPU test's original 10-second alarm expires for both the old and
new binaries in this emulator. A diagnostic copy with the same assertions and
a 60-second alarm completes successfully. Application sources were not changed
to relax their timeout.

The updated compile baseline removes only the 32 repaired failures. **164
pre-existing compile failures remain**, including four accepted negative tests;
not every residual failure is classified. This is not a claim of complete C++
conformance. The historical GCC 4.9 images were not repaired or runtime-certified
by this change. Go/Rust versions were checked in the full image; their full
runtime suites were not rerun.

## Installed local images

| Tags | Image ID |
| --- | --- |
| `8.5`, `8.5-cxx-fix` | `sha256:0d587cff28e6d572e9cc477e1047d664fcf840c600282a35d5226d49db998799` |
| `latest`, `8.5-full`, `8.5-full-cxx-fix` | `sha256:59cf5a575d69869e3983f136bdcf9e7e7d997e1206dcfc912e0d1988c68ad213` |

All tags use repository `qnx65-armv7-toolchain`. Previous local images are
preserved as `8.5-before-cxx-fix-20260917` and
`8.5-full-before-cxx-fix-20260917`. The candidate tags remain available for
explicit reproduction. No images were published to a registry.

Rebuild consumers to pick up header-generated math and synchronization fixes;
replacing a shared library alone cannot repair code already inlined into an
application. Shared runtime global `operator new/delete` interposition remains
limited by local function binding; use `-static-libstdc++` when required.
No binaries were deployed to the HU and no HU processes were restarted.

## Reproduction and evidence

```sh
host-scripts/qnx-selftest.sh --runtime
bash tests/libstdcxx.sh 8.5
```

The machine-readable [fixed result](fixed-20260917.json) records image IDs,
component hashes and counts. Detailed local artifacts are in
`tests/.cache/cxx-fix/`: `audit-validated.log`, `validated/`, `upstream.summary`,
`upstream.fails`, `selftest.log`, `selftest-full.log`, `consumer-build.log`,
`consumer-long-runtime.log` and `consumer-long-qemu.log`.
