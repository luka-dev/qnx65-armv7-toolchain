// GCC include-fixed adapter for QNX 6.5 math.h.
// Dinkum's non-template classification macros use C-only typeof tricks that
// are ill-formed in C++. Configure reads the raw C header before GNU cmath is
// available, so give that view working macros as well. GNU cmath later undefines
// these and supplies its normal overloads. C translation units are unchanged.
#pragma GCC system_header
#ifndef _QNX_GNU_MATH_FIXED_H
#define _QNX_GNU_MATH_FIXED_H
#include_next <math.h>

#if defined(__cplusplus) && !_HAS_GENERIC_TEMPLATES
#undef fpclassify
#undef isfinite
#undef isinf
#undef isnan
#undef isnormal
#undef signbit
#undef isgreater
#undef isgreaterequal
#undef isless
#undef islessequal
#undef islessgreater
#undef isunordered
#define fpclassify(x) __builtin_fpclassify(FP_NAN, FP_INFINITE, FP_NORMAL, FP_SUBNORMAL, FP_ZERO, (x))
#define isfinite(x) __builtin_isfinite(x)
#define isinf(x) __builtin_isinf(x)
#define isnan(x) __builtin_isnan(x)
#define isnormal(x) __builtin_isnormal(x)
#define signbit(x) __builtin_signbit(x)
#define isgreater(x, y) __builtin_isgreater((x), (y))
#define isgreaterequal(x, y) __builtin_isgreaterequal((x), (y))
#define isless(x, y) __builtin_isless((x), (y))
#define islessequal(x, y) __builtin_islessequal((x), (y))
#define islessgreater(x, y) __builtin_islessgreater((x), (y))
#define isunordered(x, y) __builtin_isunordered((x), (y))
#endif
#endif
