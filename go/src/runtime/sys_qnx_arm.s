// Copyright 2026 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// QNX 6.5 / ARMv7 (EABI, softfp) libc-call bridge. Analogous to
// sys_solaris_amd64.s:asmsysvicall6, retargeted to 32-bit AAPCS.

#include "go_asm.h"
#include "go_tls.h"
#include "textflag.h"

// asmsysvicall6 calls a libc.so.3 function described by a *libcall.
// asmcgocall passes the *libcall in R0. On a scheduling (g0) stack.
//
// libcall layout (see runtime2.go): fn, n, args, r1, r2, err.
// EABI: integer args 0-3 in R0-R3, args 4-5 on the outgoing stack.
TEXT runtime·asmsysvicall6(SB),NOSPLIT,$16
	MOVW	R0, R4                 // R4 = *libcall (callee-saved; survives the libc call)

	// Clear errno (*perrno) before the call, if g and perrno are set.
	CMP	$0, g
	BEQ	skiperr1
	MOVW	g_m(g), R1
	MOVW	(m_mOS+mOS_perrno)(R1), R2
	CMP	$0, R2
	BEQ	skiperr1
	MOVW	$0, R3
	MOVW	R3, 0(R2)
skiperr1:
	MOVW	libcall_fn(R4), R8     // fn
	MOVW	libcall_n(R4), R5      // n (arg count)
	MOVW	libcall_args(R4), R6   // args*

	CMP	$0, R6
	BEQ	docall_noargs

	// Load the register args (arg0..arg3 -> R0..R3).
	MOVW	0(R6), R0
	MOVW	4(R6), R1
	MOVW	8(R6), R2
	MOVW	12(R6), R3

	// EABI: args 4,5 go on the stack at 0(SP),4(SP) as seen by the callee.
	// Go's arm frame keeps the saved LR at 0(SP), so we must NOT write the C
	// stack args into our own frame — instead drop SP by 8 (stays 8-aligned)
	// so the args sit just below our frame, exactly where the callee reads them.
	CMP	$4, R5
	BLE	docall_noargs
	SUB	$8, R13
	MOVW	16(R6), R7
	MOVW	R7, 0(R13)
	CMP	$5, R5
	BLE	docall_shifted
	MOVW	20(R6), R7
	MOVW	R7, 4(R13)
docall_shifted:
	BL	(R8)
	ADD	$8, R13
	B	results

docall_noargs:
	BL	(R8)
results:
	// Store return values.
	MOVW	R0, libcall_r1(R4)
	MOVW	R1, libcall_r2(R4)

	// Read errno into libcall.err.
	CMP	$0, g
	BEQ	skiperr2
	MOVW	g_m(g), R1
	MOVW	(m_mOS+mOS_perrno)(R1), R2
	CMP	$0, R2
	BEQ	skiperr2
	MOVW	0(R2), R1
	MOVW	R1, libcall_err(R4)
skiperr2:
	RET

// Signal handler trampoline. QNX SA_SIGINFO delivers (R0=sig, R1=info, R2=ucontext).
// Mirrors sys_openbsd_arm.s:sigtramp.
TEXT runtime·sigtramp(SB),NOSPLIT|TOPFRAME,$0
	// Reserve space for callee-save registers and arguments.
	MOVM.DB.W [R4-R11], (R13)
	SUB	$16, R13

	// Called in external code context: g may not be set. Save R0 (signum),
	// load_g will clobber it.
	MOVW	R0, 4(R13)
	BL	runtime·load_g(SB)

	MOVW	R1, 8(R13)
	MOVW	R2, 12(R13)
	BL	runtime·sigtrampgo(SB)

	// Restore callee-save registers.
	ADD	$16, R13
	MOVM.IA.W (R13), [R4-R11]

	RET

TEXT runtime·cgoSigtramp(SB),NOSPLIT,$0
	MOVW	$runtime·sigtramp(SB), R11
	B	(R11)

// sigfwd calls a non-Go signal handler fn(sig, info, ctx).
TEXT runtime·sigfwd(SB),NOSPLIT,$0-16
	MOVW	sig+4(FP), R0
	MOVW	info+8(FP), R1
	MOVW	ctx+12(FP), R2
	MOVW	fn+0(FP), R3
	MOVW	R13, R9
	SUB	$24, R13
	BIC	$0x7, R13 // alignment for ELF ABI
	BL	(R3)
	MOVW	R9, R13
	RET

TEXT ·publicationBarrier(SB),NOSPLIT|NOFRAME,$0-0
	B	runtime·armPublicationBarrier(SB)

// tstart is the pthread entry for a new OS thread. R0 = mp (pthread_create arg).
// Sets g = mp.g0, lays out the g0 stack over the pthread stack, calls mstart.
TEXT runtime·tstart(SB),NOSPLIT,$0
	MOVW	m_g0(R0), g        // g register (R10) = mp.g0
	MOVW	R0, g_m(g)         // g0.m = mp

	// QNX has no CP15 TLS; commandeer TPIDRURW as the g TLS base = &mp.tls[0]
	// (save_g/load_g read it, tls_g offset 0). Must precede any save_g/load_g.
	ADD	$m_tls, R0, R1
	MCR	15, 0, R1, C13, C0, 2

	// g0 stack bounds from the current (pthread-provided) SP.
	MOVW	R13, R1
	MOVW	R1, (g_stack+stack_hi)(g)
	SUB	$(0x100000), R1    // 1MB usable
	MOVW	R1, (g_stack+stack_lo)(g)
	ADD	$const_stackGuard, R1
	MOVW	R1, g_stackguard0(g)
	MOVW	R1, g_stackguard1(g)

	BL	runtime·mstart(SB)

	MOVW	$0, R0             // pthread start-routine returns void*
	RET

// qnxInit is the DT_INIT target. QNX 6.5's ldqnx calls DT_INIT unconditionally
// (a missing DT_INIT makes it branch to a 0xffffffff sentinel and crash), so we
// provide a no-op C-ABI init that just returns before the Go runtime starts.
TEXT runtime·qnxInit(SB),NOSPLIT|NOFRAME,$0-0
	MOVW	R14, R15

// qnxInitArray is a real one-entry array of function pointers = { &qnxInit }.
// DT_INIT_ARRAY/DT_FINI_ARRAY must point at an array of POINTERS, not at code:
// QNX 6.5 ldqnx dereferences element [0] while decoding the dynamic section, so
// pointing those tags at qnxInit's code (as the linker previously did) made it
// read instruction bytes as a function pointer and crash during load.
DATA runtime·qnxInitArray+0(SB)/4, $runtime·qnxInit(SB)
GLOBL runtime·qnxInitArray(SB), NOPTR|RODATA, $4
