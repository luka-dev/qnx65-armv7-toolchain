/* Definitions for ARM running QNX Neutrino 6.5 (armle-v7, EABI/softfp).
   Ported for GCC 4.9 from gcc/config/i386/nto.h plus ground-truth harvested
   from the QNX 6.5 SDP's own 4.4.2 toolchain:
     - target triplet arm-unknown-nto-qnx6.5.0eabi
     - dynamic linker /usr/lib/ldqnx.so.2
     - ld emulation 'armnto' (the only one this binutils 2.19 ld supports)
     - default -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=softfp (set via
       configure --with-arch/--with-fpu/--with-float, not here)
   This header is included last in tm_file so it overrides the LINK/STARTFILE/
   OS-builtin bits that arm/bpabi.h and arm/arm.h set.  */

#undef  TARGET_OS_CPP_BUILTINS
#define TARGET_OS_CPP_BUILTINS()			\
  do							\
    {							\
	builtin_define ("__QNX__");			\
	builtin_define ("__QNXNTO__");			\
	builtin_define ("__ELF__");			\
	builtin_define ("__ARM__");			\
	builtin_define ("__unix__");			\
	builtin_define ("__unix");			\
	/* QNX's _GNU_SOURCE analog: exposes the POSIX/pthread extensions	\
	   that headers gate on _QNX_SOURCE (hidden under strict -std=cNN	\
	   otherwise). Stock QNX's own libstdc++ predefines it too; it gates	\
	   declarations, not struct layout, so it's ABI-safe. */		\
	builtin_define ("_QNX_SOURCE");			\
	builtin_assert ("system=qnx");			\
	builtin_assert ("system=qnxnto");		\
	builtin_assert ("system=nto");			\
	builtin_assert ("system=unix");			\
	if (TARGET_BIG_END)				\
	  builtin_define ("__BIGENDIAN__");		\
	else						\
	  builtin_define ("__LITTLEENDIAN__");		\
    }							\
  while (0)

#undef  THREAD_MODEL_SPEC
#define THREAD_MODEL_SPEC "posix"

/* QNX keeps the armle-v7 C runtime + libraries in $sysroot/armle-v7/{lib,
   usr/lib}, NOT $sysroot/lib. The stock bare gcc leaves this arch path to the
   qcc wrapper; we bake it in so the compiler links standalone. crt1/crti/crtn
   are referenced by explicit sysroot-relative path (%R = sysroot); crtbegin/
   crtend come from gcc's own libgcc dir (%s). LINK_SPEC adds the arch -L dirs
   so -lc and friends resolve. (SYSROOT_SUFFIX is deliberately NOT used: it
   would also move the arch-independent headers in $sysroot/usr/include.) */
// crtbegin/crtend come from our libgcc; use the PIC (S) variants for shared
// objects / PIE, else the non-PIC ones. (armv7 uses movw/movt absolute relocs
// that ld rejects in a .so - the S variants are built -fPIC.)
#undef  STARTFILE_SPEC
#define STARTFILE_SPEC \
  "%{!shared: %{!symbolic: \
     %{pg:%R/armle-v7/lib/mcrt1.o} \
     %{!pg:%{p:%R/armle-v7/lib/mcrt1.o} %{!p:%R/armle-v7/lib/crt1.o}}}} \
   %R/armle-v7/lib/crti.o \
   %{shared|symbolic|pie:crtbeginS.o%s;:crtbegin.o%s}"

#undef  ENDFILE_SPEC
#define ENDFILE_SPEC \
  "%{shared|symbolic|pie:crtendS.o%s;:crtend.o%s} %R/armle-v7/lib/crtn.o"

/* -m armnto is the only emulation; keep it explicit. QNX ld wants -Qy note. */
#undef  LINK_SPEC
#define LINK_SPEC \
  "%{h*} %{v:-V} \
   %{static:-Bstatic} \
   %{shared:-shared} \
   %{symbolic:-Bsymbolic} \
   %{G:-G} \
   %{Qy:} %{!Qn:-Qy} \
   -m armnto \
   -L%R/armle-v7/lib -L%R/armle-v7/usr/lib \
   %{!shared: --dynamic-linker /usr/lib/ldqnx.so.2}"

/* -lc pulls the shared libc (libc.so.3); -l:libc.a appends the static libc as a
   fallback. 113 libc functions live ONLY in libc.a - the regex family
   (regcomp/regexec/regfree/regerror), glob/globfree, wordexp, scandir, ... -
   and are NOT exported by libc.so.3, so software that uses them fails to link
   by default. ld pulls archive members only to satisfy still-undefined symbols,
   so this resolves those functions statically while everything else stays
   dynamic; programs that don't use them pull nothing and pay nothing. */
#undef  LIB_SPEC
#define LIB_SPEC "%{!shared:%{!symbolic:-lc -l:libc.a}}"

/* QNX is a full unix; its headers already guard extern "C" themselves. */
#define NO_IMPLICIT_EXTERN_C 1
#define TARGET_POSIX_IO

/* QNX: 4-byte wchar_t (Tag_ABI_PCS_wchar_t: 4), unsigned. */
#undef  WCHAR_TYPE
#define WCHAR_TYPE "unsigned int"
#undef  WCHAR_TYPE_SIZE
#define WCHAR_TYPE_SIZE 32

/* QNX uses __cxa_atexit; configured with --enable-__cxa_atexit too. */
#undef  TARGET_DEFAULT_CXA_ATEXIT
#define TARGET_DEFAULT_CXA_ATEXIT 1

/* QNX's system libraries are built with int-sized enums (Tag_ABI_enum_size:
   int), like the Linux ARM ABI. bpabi.h defaults to plain AAPCS, whose enum
   default is short/packed (arm.c: arm_default_short_enums() returns true unless
   arm_abi == AAPCS_LINUX) - that mismatches QNX's libs and the linker warns.
   Default to AAPCS_LINUX: still AAPCS-based/BPABI/EABI, but int enums, and it
   also enables 8-byte __sync_* atomics. */
#undef  ARM_DEFAULT_ABI
#define ARM_DEFAULT_ABI ARM_ABI_AAPCS_LINUX

/* binutils 2.19's gas only accepts UAL VFP/NEON mnemonics (vmov/vcvt/...) when
   '.syntax unified' is active, which stock GCC 4.9 emits in Thumb-2 only
   (arm.h: TARGET_UNIFIED_ASM == TARGET_THUMB2). In ARM state it emits UAL
   mnemonics with no such header, so this old gas rejects them ("bad
   instruction"). Force fully-unified output - header + mnemonics stay
   consistent and gas 2.19 accepts the lot. This is exactly what GCC 5+ later
   made the default (-masm-syntax-unified). */
#undef  TARGET_UNIFIED_ASM
#define TARGET_UNIFIED_ASM 1
