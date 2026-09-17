#!/usr/bin/env python3
"""Run inside a toolchain container; keep diagnostics for every header probe."""
import itertools
import json
from pathlib import Path
import subprocess
import sys

out = Path(sys.argv[1])
out.mkdir(parents=True, exist_ok=True)
cc = 'arm-unknown-nto-qnx6.5.0eabi-g++'
c_headers = 'stdio.h stdlib.h stdint.h string.h math.h pthread.h sys/types.h stddef.h malloc.h ctype.h wchar.h signal.h stdarg.h time.h'.split()
cpp_headers = 'cmath cstdlib cstddef string mutex thread future complex'.split()
probes = {}
for first, second in itertools.product(c_headers, cpp_headers):
    name = first.replace('/', '_') + '-' + second
    probes[name] = f'#include <{first}>\n#include <{second}>\nint main() {{}}\n'
for fn in 'isfinite isinf isnan isnormal signbit fpclassify'.split():
    for typ, val in [('int', '5'), ('float', '5.f'), ('double', '5.')]:
        probes[fn+'-'+typ] = f'#include <cmath>\nint main() {{ return std::{fn}({val}); }}\n'
for fn in 'cosf coshf sinf sinhf logf log10f log2f'.split():
    for scope in ('global', 'std'):
        prefix = '::' if scope == 'global' else 'std::'
        probes[fn+'-'+scope] = f'#include <cmath>\nfloat f(float x) {{ return {prefix}{fn}(x); }}\n'
for fn in 'fmin fmax hypot round copysign fma'.split():
    args = 'x, x, x' if fn == 'fma' else ('x' if fn == 'round' else 'x, x')
    probes['return-'+fn] = f'#include <cmath>\n#include <type_traits>\nfloat x; static_assert(std::is_same<decltype(std::{fn}({args})), float>::value, "wrong float return type");\n'
rows = []
for dialect in ('c++11', 'gnu++11'):
    folder = out / dialect
    folder.mkdir(exist_ok=True)
    for name, source in probes.items():
        path = folder / (name+'.cpp')
        path.write_text(source)
        proc = subprocess.run([cc, '-std='+dialect, '-fsyntax-only', str(path)], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
        (folder / (name+'.log')).write_text(proc.stdout)
        rows.append({'dialect': dialect, 'probe': name, 'ok': proc.returncode == 0})
(out / 'results.json').write_text(json.dumps(rows, indent=2)+'\n')
for dialect in ('c++11', 'gnu++11'):
    selected = [r for r in rows if r['dialect'] == dialect]
    bad = [r['probe'] for r in selected if not r['ok']]
    print(dialect, 'pass', len(selected)-len(bad), 'fail', len(bad), 'total', len(selected), flush=True)
    if bad: print('FAIL:', ', '.join(bad), flush=True)
