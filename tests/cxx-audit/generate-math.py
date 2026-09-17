#!/usr/bin/env python3
"""Generate independent std::<cmath> / C libm overload comparisons."""
from pathlib import Path
import sys
UNARY = ['acos', 'acosh', 'asin', 'asinh', 'atan', 'atanh', 'cbrt', 'ceil', 'cos', 'cosh', 'erf', 'erfc', 'exp', 'exp2', 'expm1', 'fabs', 'floor', 'ilogb', 'lgamma', 'llrint', 'llround', 'log', 'log10', 'log1p', 'log2', 'logb', 'lrint', 'lround', 'nearbyint', 'rint', 'round', 'sin', 'sinh', 'sqrt', 'tan', 'tanh', 'tgamma', 'trunc']
BINARY = ['atan2', 'copysign', 'fdim', 'fmax', 'fmin', 'fmod', 'hypot', 'nextafter', 'pow', 'remainder']
FUNCS = UNARY + BINARY + ['fma', 'frexp', 'ldexp', 'modf', 'nexttoward', 'remquo', 'scalbn', 'scalbln']
lines = ['#include <cmath>', '#include "math-driver.h"']
entries = []
for kind, typ, suffix in [('f', 'float', 'f'), ('d', 'double', ''), ('l', 'long double', 'l')]:
    for fn in FUNCS:
        name = fn + '_' + kind
        x = '1.25' if fn in ('acosh', 'log', 'log10', 'log2', 'logb', 'lgamma', 'tgamma') else '0.75'
        args = 'a'
        if fn in BINARY: args = 'a, b'
        if fn == 'fma': args = 'a, b, c'
        if fn == 'frexp': args = 'a, &q'
        if fn in ('ldexp', 'scalbn'): args = 'a, 2'
        if fn == 'scalbln': args = 'a, 2L'
        if fn == 'modf': args = 'a, &whole'
        if fn == 'nexttoward': args = 'a, (long double)b'
        if fn == 'remquo': args = 'a, b, &q'
        for label, call in [('std', 'std::'+fn), ('ref', '(::'+fn+suffix+')')]:
            lines += [f'static __attribute__((noinline)) double {label}_{name}() {{',
                      f'  volatile {typ} input = ({typ}){x};',
                      f'  {typ} a=input, b=({typ})1.5, c=({typ})2.0, whole=0; int q=0;',
                      f'  return (double){call}({args});', '}']
        entries.append(f'  {{"{fn}({typ})", std_{name}, ref_{name}}}')
lines += ['static Entry entries[] = {', ',\n'.join(entries), '};',
          'int main() { return audit_math(entries, sizeof(entries)/sizeof(entries[0])); }']
Path(sys.argv[1]).write_text('\n'.join(lines)+'\n')
