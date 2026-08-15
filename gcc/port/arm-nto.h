/* Definitions for ARM running QNX Neutrino 6.5 (armle-v7, EABI/softfp).
   Forward-port of gcc/port/arm-nto.h (GCC 4.9.4) to GCC 8.5, same ground
   truth from the QNX 6.5 SDP's own 4.4.2 toolchain:
     - target triplet arm-unknown-nto-qnx6.5.0eabi
     - dynamic linker /usr/lib/ldqnx.so.2
     - ld emulation 'armnto' (the only one this binutils 2.19 ld supports)
     - default -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=softfp (set via
       configure --with-arch/--with-fpu/--with-float, not here)
   This header is included last in tm_file so it overrides the LINK/STARTFILE/
   OS-builtin bits that arm/bpabi.h and arm/arm.h set.

   Differences from the 4.9 version:
     - TARGET_UNIFIED_ASM dropped: GCC 6+ always emits unified syntax.
     - SUBTARGET_OVERRIDE_OPTIONS also marks unaligned_access as user-set:
       GCC 8's resolution is opts_set-based, not the 4.9 '== 2' sentinel,
       so a bare preset would be recomputed back to 1.  */

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

/* -m armnto is the only emulation; keep it explicit. QNX ld wants -Qy note.

   --target2=rel: R_ARM_TARGET2 (the typeinfo references inside .ARM.extab)
   is platform-defined; libgcc's EHABI unwinder for non-linux/non-bsd targets
   decodes those entries as RELATIVE, while this ld's armnto default does not
   match - the personality routine then chases garbage and every throw dies
   in a SIGSEGV (jump into the typeinfo object; QEMU-verified, and 'rel' is
   the only one of abs/rel/got-rel that unwinds correctly on-device). Known
   ceiling: catching by a typeinfo IMPORTED from another .so may not match
   (rel can't indirect through the GOT) - the -static-libstdc++ default and
   same-module catches are unaffected. */
#undef  LINK_SPEC
#define LINK_SPEC \
  "%{h*} %{v:-V} \
   %{static:-Bstatic} \
   %{shared:-shared} \
   %{symbolic:-Bsymbolic} \
   %{rdynamic:-export-dynamic} \
   %{G:-G} \
   %{Qy:} %{!Qn:-Qy} \
   -m armnto --target2=rel \
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

/* intptr_t/uintptr_t, matching QNX's <stdint.h> (_Intptrt/_Uintptrt are
   int/unsigned int in pointer mode - 32-bit here). Without these the
   __INTPTR_TYPE__/__UINTPTR_TYPE__ builtin macros stay undefined (no
   *-stdint.h in tm_file - QNX has its own stdint.h), and libstdc++ 8's
   std::greater<T*> total-order path uses __UINTPTR_TYPE__ directly. */
#undef  INTPTR_TYPE
#define INTPTR_TYPE "int"
#undef  UINTPTR_TYPE
#define UINTPTR_TYPE "unsigned int"

/* QNX uses __cxa_atexit; configured with --enable-__cxa_atexit too. */
#undef  TARGET_DEFAULT_CXA_ATEXIT
#define TARGET_DEFAULT_CXA_ATEXIT 1

/* QNX's system libraries are built with int-sized enums (Tag_ABI_enum_size:
   int), like the Linux ARM ABI. bpabi.h defaults to plain AAPCS, whose enum
   default is short/packed - that mismatches QNX's libs and the linker warns.
   Default to AAPCS_LINUX: still AAPCS-based/BPABI/EABI, but int enums, and it
   also enables 8-byte __sync_* atomics. (Same override as arm/linux-eabi.h
   and arm/freebsd.h.) */
#undef  ARM_DEFAULT_ABI
#define ARM_DEFAULT_ABI ARM_ABI_AAPCS_LINUX

/* Target-default option fixups, run from arm.c's arm_option_override() (which
   invokes SUBTARGET_OVERRIDE_OPTIONS before calling
   arm_option_override_internal, where unaligned_access is resolved). Each only
   sets a default when the user did NOT pass the option, so an explicit flag
   always wins.

   1. -g -> DWARF 3, not GCC 8's DWARF 4: the SDP's binutils 2.19
      readelf/objdump/addr2line (and any gdb on that BFD) only read DWARF <= 3 -
      DWARF 4 makes them warn "unsupported version 4" and drop file:line. DWARF 3
      (not 2) keeps the richer info 2.19 still reads. Only the *version* changes;
      -g isn't forced, and it never touches the emitted code (debug lives in
      non-loadable .debug_* sections the target never maps).

   2. -mno-unaligned-access by default (strict alignment): GCC 8 defaults ARMv7
      to -munaligned-access and will emit single misaligned ldr/str (and set
      __ARM_FEATURE_UNALIGNED). QNX 6.5 runs with SCTLR.A=1, where a misaligned
      access faults - so that codegen crashes on device (measured: Rust fmt LUT
      SIGBUS before +strict-align). Unlike 4.9's '== 2' sentinel, GCC 8's
      arm_option_override_internal recomputes the default whenever
      opts_set->x_unaligned_access is false - so ALSO mark it set, making the
      forced 0 stick exactly as if the user passed -mno-unaligned-access. */
#undef  SUBTARGET_OVERRIDE_OPTIONS
#define SUBTARGET_OVERRIDE_OPTIONS			\
  do {							\
    if (!global_options_set.x_dwarf_version)		\
      global_options.x_dwarf_version = 3;		\
    if (!global_options_set.x_unaligned_access)		\
      {							\
	global_options.x_unaligned_access = 0;		\
	global_options_set.x_unaligned_access = 1;	\
      }							\
  } while (0)
