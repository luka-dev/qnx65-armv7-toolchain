// Copyright 2014 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

//go:build !windows

#include "go_asm.h"
#include "go_tls.h"
#include "funcdata.h"
#include "textflag.h"

// We have to resort to TLS variable to save g(R10).
// One reason is that external code might trigger
// SIGSEGV, and our runtime.sigtramp don't even know we
// are in external code, and will continue to use R10,
// this might as well result in another SIGSEGV.
// Note: both functions will clobber R0 and R11 and
// can be called from 5c ABI code.

// On android, runtime.tls_g is a normal variable.
// TLS offset is computed in x_cgo_inittls.
#ifdef GOOS_android
#define TLSG_IS_VARIABLE
#endif

// On QNX, ldqnx uses a proprietary TLS scheme and does not relocate ELF TLS
// (R_ARM_TLS_TPOFF32) in dynamically-loaded shared objects, so buildmode=shared
// would leave tls_g's offset unresolved. Treat tls_g as a normal variable
// holding a fixed offset (8, the free CP15 TLS slot the static build already
// uses) — works for both the static and the shared runtime.
#ifdef GOOS_qnx
#define TLSG_IS_VARIABLE
#endif

// save_g saves the g register into pthread-provided
// thread-local memory, so that we can call externally compiled
// ARM code that will overwrite those registers.
// NOTE: runtime.gogo assumes that R1 is preserved by this function.
//       runtime.mcall assumes this function only clobbers R0 and R11.
// Returns with g in R0.
TEXT runtime·save_g(SB),NOSPLIT,$0
	// If the host does not support MRC the linker will replace it with
	// a call to runtime.read_tls_fallback which jumps to __kuser_get_tls.
	// The replacement function saves LR in R11 over the call to read_tls_fallback.
	// To make stack unwinding work, this function should NOT be marked as NOFRAME,
	// as it may contain a call, which clobbers LR even just temporarily.
#ifdef GOOS_qnx
	// QNX 6.5 does not use the CP15 TLS registers (both TPIDRURO and TPIDRURW
	// read 0); its own TLS is reached through __tls(). We commandeer TPIDRURW
	// (user read-write, unused by QNX) as the g TLS base — set per-thread in
	// tstart and rt0_go to &m.tls[0]. tls_g is 0 (g lives at m.tls[0]).
	MRC	15, 0, R0, C13, C0, 2 // fetch TPIDRURW (our g TLS base)
#else
	MRC	15, 0, R0, C13, C0, 3 // fetch TLS base pointer
#endif
	BIC $3, R0 // Darwin/ARM might return unaligned pointer
	MOVW	runtime·tls_g(SB), R11
	ADD	R11, R0
	MOVW	g, 0(R0)
	MOVW	g, R0 // preserve R0 across call to setg<>
	RET

// load_g loads the g register from pthread-provided
// thread-local memory, for use after calling externally compiled
// ARM code that overwrote those registers.
TEXT runtime·load_g(SB),NOSPLIT,$0
	// See save_g
#ifdef GOOS_qnx
	MRC	15, 0, R0, C13, C0, 2 // fetch TPIDRURW (our g TLS base)
#else
	MRC	15, 0, R0, C13, C0, 3 // fetch TLS base pointer
#endif
	BIC $3, R0 // Darwin/ARM might return unaligned pointer
	MOVW	runtime·tls_g(SB), R11
	ADD	R11, R0
	MOVW	0(R0), g
	RET

// This is called from rt0_go, which runs on the system stack
// using the initial stack allocated by the OS.
// It calls back into standard C using the BL (R4) below.
// To do that, the stack pointer must be 8-byte-aligned
// on some systems, notably FreeBSD.
// The ARM ABI says the stack pointer must be 8-byte-aligned
// on entry to any function, but only FreeBSD's C library seems to care.
// The caller was 8-byte aligned, but we push an LR.
// Declare a dummy word ($4, not $0) to make sure the
// frame is 8 bytes and stays 8-byte-aligned.
TEXT runtime·_initcgo(SB),NOSPLIT,$4
	// if there is an _cgo_init, call it.
	MOVW	_cgo_init(SB), R4
	CMP	$0, R4
	B.EQ	nocgo
	MRC     15, 0, R0, C13, C0, 3 	// load TLS base pointer
	MOVW 	R0, R3 			// arg 3: TLS base pointer
#ifdef TLSG_IS_VARIABLE
	MOVW 	$runtime·tls_g(SB), R2 	// arg 2: &tls_g
#else
	MOVW	$0, R2			// arg 2: not used when using platform tls
#endif
	MOVW	$setg_gcc<>(SB), R1 	// arg 1: setg
	MOVW	g, R0 			// arg 0: G
	BL	(R4) // will clobber R0-R3
nocgo:
	RET

// void setg_gcc(G*); set g called from gcc.
TEXT setg_gcc<>(SB),NOSPLIT,$0
	MOVW	R0, g
	B		runtime·save_g(SB)

#ifdef TLSG_IS_VARIABLE
#ifdef GOOS_android
// Use the free TLS_SLOT_APP slot #2 on Android Q.
// Earlier androids are set up in gcc_android.c.
DATA runtime·tls_g+0(SB)/4, $8
#endif
#ifdef GOOS_qnx
// g lives at m.tls[0]; TPIDRURW already points at &m.tls[0], so offset is 0.
DATA runtime·tls_g+0(SB)/4, $0
#endif
GLOBL runtime·tls_g+0(SB), NOPTR, $4
#else
GLOBL runtime·tls_g+0(SB), TLSBSS, $4
#endif
