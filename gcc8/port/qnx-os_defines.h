// Specific definitions for QNX 6.x  -*- C++ -*-

// Copyright (C) 2002-2014 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

#ifndef _GLIBCXX_OS_DEFINES
#define _GLIBCXX_OS_DEFINES 1

// System-specific #define, typedefs, corrections, etc, go here.  This
// file will come before all others.  It is pulled in very early by
// <bits/c++config.h>, at global scope, so it is the right place to tame
// QNX's Dinkumware C headers for use with the GNU C++ library.

// (0) Enable QNX's extension surface. Under strict -std=c++NN the compiler
//     defines __STRICT_ANSI__, which makes QNX headers hide the POSIX/QNX
//     extensions (pthread_cond_timedwait, PTHREAD_MUTEX_RECURSIVE, ...) that
//     libstdc++'s gthr-posix layer needs - so <thread>/<mutex> fail to compile
//     in strict mode even though they build fine under -std=gnu++NN. Defining
//     _QNX_SOURCE turns the extensions back on regardless of the dialect; it
//     only exposes more declarations, it does not change existing ABI.
#ifndef _QNX_SOURCE
#define _QNX_SOURCE 1
#endif

// (0) QNX's C99 gate. Dinkum headers gate their C99 declarations (isblank,
//     strtoll, snprintf, ...) on _HAS_C9X, which yvals.h derives from _C99 /
//     __EXT_ANSIC_199901. Neither route works for C++: platform.h #undefs any
//     user __EXT_ANSIC_199901 and re-derives it from __STDC_VERSION__ (a
//     C-only macro g++ never defines), and the __GNUC__ fallback dies under
//     strict -std=c++NN (__STRICT_ANSI__). So set the terminal Dinkum gate
//     directly, BEFORE any header can read yvals.h (yvals honors a pre-set
//     _HAS_C9X). Declarations only, ABI-safe - same philosophy as
//     _QNX_SOURCE. The library build passes the same define via
//     *FLAGS_FOR_TARGET (build.sh) so configure's C99 probes agree.
#ifndef _HAS_C9X
#define _HAS_C9X 1
#endif

// (1) Ordering: QNX's C headers declare ptrdiff_t/size_t inside namespace std
//     and export them to the global namespace via per-header `using` gated on
//     _STD_USING. If a QNX C header (e.g. <stdlib.h>, pulled by <cstdlib>) is
//     seen before <cstddef>, the stddef guards get set without ::ptrdiff_t
//     ever reaching the global namespace, and libsupc++/cxxabi.h then fails
//     ("ptrdiff_t does not name a type"). Establish the global C types up
//     front, before any QNX header can poison the ordering.
#include <stddef.h>

// (2) QNX's <math.h> provides its own C++ inline overloads of abs/fabs/...,
//     gated on _NO_CPP_INLINES. Disable them so the GNU <cmath> supplies the
//     complete, authoritative set without redefinition clashes.
#define _NO_CPP_INLINES 1
//     ... and with _HAS_C9X on (see (0)), Dinkum's math.h adds the C++
//     overload set for the C99 classification interface (inline fpclassify/
//     signbit for float/double/long double + isnan/isinf/isgreater/...
//     templates, all in std, reachable from global scope through
//     '#define isnan(x) (_CSTD isnan(x))' wrapper macros that <cmath>
//     #undefs). That set IS the C++11-conformant one, so tell <cmath> to use
//     it instead of defining its own constexpr versions on top (redefinition
//     errors otherwise) - the same knob mechanism as the string/wchar protos
//     above, C++11-math flavor. Ceiling: integer-argument classification
//     (std::isnan(5)) resolves through Dinkum's unconstrained template into
//     fpclassify(int), which is ambiguous across the three FP overloads -
//     classify FP values, not ints.
#define __CORRECT_ISO_CPP11_MATH_H_PROTO_FP 1
#define __CORRECT_ISO_CPP11_MATH_H_PROTO_INT 1

// (3) QNX's <string.h> and <wchar.h> unconditionally provide the ISO C++
//     overloads of memchr/strchr/... and wcschr/... (no _NO_CPP_INLINES gate),
//     so tell libstdc++ its <cstring>/<cwchar> must NOT add its own - the
//     system headers are already ISO-correct. (Guards use the __-prefixed
//     spelling, not _GLIBCXX_.)
#define __CORRECT_ISO_CPP_STRING_H_PROTO 1
#define __CORRECT_ISO_CPP_WCHAR_H_PROTO 1

// (4) QNX's <ctype.h> leaks short, unguarded mask macros (_UP, _LO, _DI, ...)
//     that collide with identifiers libstdc++ uses elsewhere (notably _UP as a
//     typedef name in <bits/unique_ptr.h>). Pull <ctype.h> in now so its
//     include guard is set, then undef the pollution: no later include can
//     re-introduce it. bits/ctype_base.h (the sole legitimate consumer) is
//     made self-contained (hardcoded masks) so it no longer needs these.
#include <ctype.h>
#undef _UP
#undef _LO
#undef _DI
#undef _XD
#undef _SP
#undef _PU
#undef _CN
#undef _BB
#undef _XA
#undef _XS
#undef _XB
// ... and the function-like is*/to* macros whose bodies reference the mask
// macros just removed (under _NO_CPP_INLINES <ctype.h> defines BOTH extern
// declarations and these macros). libstdc++ 8's generic ctype_inline.h calls
// isblank()/isupper()/... directly, which would expand to the now-broken
// bodies. The extern declarations stay, so these become real libc calls
// (all present in libc.so.3 - verified, including the C99 isblank).
#undef isalnum
#undef isalpha
#undef iscntrl
#undef isdigit
#undef isgraph
#undef islower
#undef isprint
#undef ispunct
#undef isspace
#undef isupper
#undef isxdigit
#undef isblank
#undef tolower
#undef toupper

// (5) libstdc++'s cross-configure did not detect QNX's timing primitives (the
//     link probe ran while the target libc/crt were only half-built). QNX 6.5
//     has both, so declare them: this_thread::sleep_for/yield need them, and
//     emulator timing depends on real nanosleep.
#define _GLIBCXX_USE_NANOSLEEP 1
#define _GLIBCXX_USE_SCHED_YIELD 1

// (6) QNX's <ctype.h> defines isblank as a function-like macro (under
//     _NO_CPP_INLINES, see (2)), which detonates on libstdc++'s two-argument
//     std::isblank(_CharT, const locale&) declarations. <cctype> has the
//     canonical fix - '#undef isblank; using ::isblank;' - but only under
//     _GLIBCXX_USE_C99_CTYPE_TR1, which the qnx crossconfig never sets. QNX
//     6.5 does have ::isblank (declared whenever _HAS_C9X, guaranteed by (0)),
//     so turn the fix on.
#define _GLIBCXX_USE_C99_CTYPE_TR1 1

#endif
