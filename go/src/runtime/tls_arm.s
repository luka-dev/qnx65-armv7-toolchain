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
// (R_ARM_TLS_TPOFF32), so tls_g is a plain variable holding a fixed offset.
//
// QNX 6.5 procnto never touches the CP15 thread-ID registers (TPIDRURO/URW):
// it neither sets them nor saves/restores them on a context switch, so they
// are per-CPU scratch shared by every process on that core. The kernel's real
// per-thread pointer is cpupage->tls (kernel.S sets cpupageptr[RUNCPU]->tls on
// every switch; libc's __tls() is exactly *(*_cpupage_ptr)). g lives in the
// __reserved3 word of that struct _thread_local_storage (sys/storage.h), which
// neither libc nor procnto use. Base = **_cpupage_ptr, tls_g = 56.
#ifdef GOOS_qnx
#define TLSG_IS_VARIABLE
#define QNX_TLS_BASE(r) \
	MOVW	runtime·qnx_cpupage_ptr(SB), r; \
	MOVW	(r), r; \
	MOVW	(r), r
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
	QNX_TLS_BASE(R0) // **_cpupage_ptr = this thread's _thread_local_storage
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
	QNX_TLS_BASE(R0) // see save_g
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
// offsetof(struct _thread_local_storage, __reserved3): unused by libc/procnto.
DATA runtime·tls_g+0(SB)/4, $56
// runtime·qnx_cpupage_ptr (os_qnx.go) = &_cpupage_ptr, resolved by ldqnx.
#endif
GLOBL runtime·tls_g+0(SB), NOPTR, $4
#else
GLOBL runtime·tls_g+0(SB), TLSBSS, $4
#endif
