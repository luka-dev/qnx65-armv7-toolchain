#!/bin/bash
# Apply the arm-*-nto-qnx* target port onto a vanilla GCC 4.9.4 tree.
# Run from inside the extracted gcc-4.9.4/ dir. Idempotent.
set -eu
SRC=$(cd "$(dirname "$0")" && pwd)   # docker/port
GCCDIR=${1:-$PWD}
cd "$GCCDIR"
[ -f gcc/config.gcc ] || { echo "not a gcc source tree: $GCCDIR" >&2; exit 1; }

echo ">> dropping arm/nto.h + arm/nto.opt (only if changed, to avoid needless rebuilds)"
cmp -s "$SRC/arm-nto.h"   gcc/config/arm/nto.h   || cp "$SRC/arm-nto.h"   gcc/config/arm/nto.h
cmp -s "$SRC/arm-nto.opt" gcc/config/arm/nto.opt || cp "$SRC/arm-nto.opt" gcc/config/arm/nto.opt

if grep -q 'arm\*-\*-nto-qnx\*' gcc/config.gcc; then
  echo ">> config.gcc already patched, skipping"
else
  echo ">> inserting arm nto stanza into gcc/config.gcc"
  awk '
    /^arm\*-\*-eabi\* \| arm\*-\*-symbianelf\* \| arm\*-\*-rtems\*\)/ && !done {
      print "arm*-*-nto-qnx*)\t\t\t# QNX Neutrino ARM EABI (armle-v7, softfp)"
      print "\tdefault_use_cxa_atexit=yes"
      print "\ttm_file=\"dbxelf.h elfos.h arm/unknown-elf.h arm/elf.h arm/bpabi.h arm/aout.h vxworks-dummy.h arm/arm.h arm/nto.h\""
      print "\ttmake_file=\"${tmake_file} arm/t-arm arm/t-arm-elf arm/t-bpabi\""
      print "\textra_options=\"${extra_options} arm/nto.opt\""
      print "\tgnu_ld=yes"
      print "\tgas=yes"
      print "\t;;"
      done=1
    }
    { print }
  ' gcc/config.gcc > gcc/config.gcc.new && mv gcc/config.gcc.new gcc/config.gcc
fi

if grep -q 'arm\*-\*-nto-qnx\*' libgcc/config.host; then
  echo ">> libgcc/config.host already patched, skipping"
else
  echo ">> inserting arm nto entry into libgcc/config.host"
  awk '
    /^arm\*-\*-eabi\* \| arm\*-\*-symbianelf\* \| arm\*-\*-rtems\*\)/ && !done {
      print "arm*-*-nto-qnx*)\t\t\t# mirror of arm eabi recipe"
      print "\ttmake_file=\"${tmake_file} arm/t-arm arm/t-elf t-fixedpoint-gnu-prefix\""
      print "\ttm_file=\"$tm_file arm/bpabi-lib.h\""
      print "\ttmake_file=\"${tmake_file} arm/t-bpabi\""
      print "\textra_parts=\"crtbegin.o crtbeginS.o crtbeginT.o crtend.o crtendS.o crti.o crtn.o\""
      print "\ttmake_file=\"$tmake_file t-softfp-sfdf t-softfp-excl arm/t-softfp t-softfp t-libgcc-pic t-crtstuff-pic\""
      print "\tunwind_header=config/arm/unwind-arm.h"
      print "\t;;"
      done=1
    }
    { print }
  ' libgcc/config.host > libgcc/config.host.new && mv libgcc/config.host.new libgcc/config.host
fi

echo ">> arm.md: .inst -> .word/.short for the trap insn (gas 2.19 has no .inst)"
# GCC 4.9 emits the trap (__builtin_trap / bounds check) as '.inst 0xe7f000f0'
# (ARM) / '.inst 0xdeff' (Thumb); binutils 2.19's gas predates the .inst
# pseudo-op. Emit the identical instruction word as data instead - the CPU
# executes it the same; only the disassembler's code/data marking differs.
sed -i '/0xe7f000f0/ s/\.inst/.word/; /0xdeff/ s/\.inst/.short/' gcc/config/arm/arm.md

echo ">> widening libstdc++ qnx os match (qnx6.[12]* -> qnx6.[0-9]*)"
sed -i 's/qnx6\.\[12\]\*)/qnx6.[0-9]*)/' libstdc++-v3/configure.host

echo ">> compatibility-atomic-c++0x.cc: pull <cstddef> before gstdint.h"
# This src file #includes gstdint.h (-> QNX <stdint.h> -> <sys/types.h>, whose
# Dinkum footer does 'using ::std::size_t') before any libstdc++ header has set
# up std::size_t. Establish std::size_t first.
CA=libstdc++-v3/src/c++11/compatibility-atomic-c++0x.cc
grep -q '#include <cstddef>' "$CA" || \
  sed -i 's|#include "gstdint.h"|#include <cstddef>\n#include "gstdint.h"|' "$CA"

echo ">> valarray: elaborate struct tags so QNX Dinkum std:: math fns don't shadow"
# QNX <math.h> declares _Sin/_Cos/_Cosh/_Sinh as functions in namespace std;
# libstdc++ valarray defines structs of the same name. In valarray_after.h the
# _DEFINE_EXPR_UNARY_FUNCTION macro uses the functor bare (_UnClos<_UName,...>),
# which then resolves to the Dinkum FUNCTION -> "expected a type, got std::_Cosh".
# Elaborate the tag (struct _UName) so it names the struct; type + mangling are
# unchanged, unlike renaming. (Applies to all functors; harmless for non-clashing
# ones since the struct exists.)
sed -i 's/_UnClos<_UName,/_UnClos<struct _UName,/g' \
    libstdc++-v3/include/bits/valarray_after.h

echo ">> installing QNX os_defines.h (global ptrdiff_t ordering + ISO string/wchar protos)"
# configure.host has NO nto case, so arm-unknown-nto-qnx6.5.0eabi resolves its
# host_os to a string that matches neither qnx6.[12]* nor the widened qnx6.[0-9]*
# - libstdc++ actually selects os/generic (verified: OS_INC_SRCDIR=config/os/
# generic). So the fix MUST land in os/generic; the qnx6.1 copy is kept for the
# i386-nto path but is unused for arm.
for D in config/os/generic config/os/qnx/qnx6.1; do
  cmp -s "$SRC/qnx-os_defines.h" "libstdc++-v3/$D/os_defines.h" \
    || cp "$SRC/qnx-os_defines.h" "libstdc++-v3/$D/os_defines.h"
done

echo ">> installing QNX ctype_base.h (undef leaked _UP/_LO/... ctype macros)"
cmp -s "$SRC/qnx-ctype_base.h" libstdc++-v3/config/os/qnx/qnx6.1/ctype_base.h \
  || cp "$SRC/qnx-ctype_base.h" libstdc++-v3/config/os/qnx/qnx6.1/ctype_base.h

echo ">> widening libstdc++ crossconfig qnx target case (6.1/6.2 -> 6.x)"
# crossconfig.m4 (source) + the already-generated configure both hardcode
# '*-qnx6.1* | *-qnx6.2*' and error out for 6.5; broaden both to '*-qnx6.*'.
sed -i 's/\*-qnx6\.1\* | \*-qnx6\.2\*)/*-qnx6.*)/' \
    libstdc++-v3/crossconfig.m4 libstdc++-v3/configure

echo ">> done. arm*-*-nto-qnx* port applied."
