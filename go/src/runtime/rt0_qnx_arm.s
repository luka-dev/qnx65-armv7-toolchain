// Copyright 2026 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "textflag.h"

// Process entry. QNX (ELF, ldqnx.so.2) hands us a SysV-style initial stack:
// (R13) = argc, 4(R13) = argv. No OABI/SWI probe (QNX has no Linux syscalls).
//
// The internal-linked static binary has no crt, so QNX libc is uninitialized at
// entry: __tls() (QNX's own thread-local block), errno, malloc and the main
// thread's stack normalization are all set up by libc's _init_libc, which
// crt1.o's _start calls before main. We replicate that prologue here, then fall
// through to rt0_go. (buildmode=shared enters via crt's _start, not this symbol,
// so _init_libc runs exactly once in either mode.)
TEXT _rt0_arm_qnx(SB),NOSPLIT|NOFRAME,$0
	MOVW	R0, R6              // R6 = procnto entry R0 (callee-saved across the call)
	MOVW	(R13), R4           // R4 = argc (callee-saved)
	ADD	$4, R13, R5         // R5 = argv (callee-saved)
	MOVW	R4, R0              // arg0: argc
	MOVW	R5, R1              // arg1: argv
	ADD	R4<<2, R5, R2       // R2 = argv + argc*4
	ADD	$4, R2, R2          // arg2: envp (past argv NULL)
	MOVW	R2, R3              // R3 walks envp to find auxv
initenvloop:
	MOVW.P	4(R3), R12          // R12 = *R3; R3 += 4
	CMP	$0, R12
	BNE	initenvloop         // arg3 (R3) = start of auxv (past envp NULL)
	MOVW.W	R6, -4(R13)         // push {procnto R0} (matches crt1.o exactly)
	MOVW	$libc__init_libc(SB), R8
	CALL	(R8)                // _init_libc(argc, argv, envp, auxv)
	ADD	$4, R13             // pop

	// _init_libc has normalized the main-thread stack (procnto hands a 512KB
	// stack); enter the Go runtime on it with fresh argc/argv.
	MOVW	(R13), R0           // argc
	ADD	$4, R13, R1         // argv
	MOVW	$runtime·rt0_go(SB), R4
	B	(R4)

// Entry for -buildmode=c-shared / c-archive (loaded by ldqnx). Unused for the
// initial executable milestone; kept so the symbol resolves.
TEXT _rt0_arm_qnx_lib(SB),NOSPLIT,$0
	B	_rt0_arm_lib(SB)
