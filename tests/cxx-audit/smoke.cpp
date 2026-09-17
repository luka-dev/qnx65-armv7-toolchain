// C headers first: these must work without application-specific -D/-include.
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <cmath>
#include <cstdlib>
#include <mutex>
#include <complex>
#include <type_traits>

#ifndef _GTHREAD_USE_MUTEX_INIT_FUNC
#error QNX mutexes must release synchronization state at destruction
#endif
#ifndef _GTHREAD_USE_RECURSIVE_MUTEX_INIT_FUNC
#error QNX recursive mutexes must release synchronization state at destruction
#endif
#if !_GLIBCXX_USE_CLOCK_MONOTONIC || !_GLIBCXX_USE_CLOCK_REALTIME
#error QNX chrono must use clock_gettime, not time()
#endif
static_assert(std::is_same<decltype(std::round(1.f)), float>::value, "float overload");
static_assert(!std::isnan(5) && std::isfinite(5), "integer classification");
extern "C" float audit_round(float x) { return std::round(x); }
extern "C" float audit_cos(float x) { return std::cosf(x); }
extern "C" float audit_min(float a, float b) { return std::fmin(a, b); }
