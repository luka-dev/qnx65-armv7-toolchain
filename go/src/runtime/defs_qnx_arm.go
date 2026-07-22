// Copyright 2026 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// QNX Neutrino 6.5.0 / ARMv7 (armle-v7) runtime definitions.
//
// Values extracted directly from the QNX 6.5.0 target sysroot headers
// (/usr/qnx650/target/qnx6/usr/include) — see go-qnx65/NOTES-qnx-defs.md.
// NOT the same as Linux: several constants are QNX-specific and getting
// them wrong is a silent-corruption bug, so they are called out below.

//go:build qnx && arm

package runtime

const (
	// errno (errno.h) — QNX-specific numeric values.
	_EINTR       = 0x4   // 4
	_EBADF       = 0x9   // 9
	_EAGAIN      = 0xb   // 11  (EWOULDBLOCK==EAGAIN on QNX)
	// _ENOMEM (12) is declared in mem_bsd.go.
	_EACCES      = 0xd   // 13
	_EFAULT      = 0xe   // 14
	_EBUSY       = 0x10  // 16
	_ETIME       = 0x3e  // 62
	_ENOSYS      = 0x59  // 89
	_EINPROGRESS = 0xec  // 236
	_ECONNRESET  = 0xfe  // 254
	_ETIMEDOUT   = 0x104 // 260
	_EWOULDBLOCK = 0xb   // == EAGAIN

	// mmap prot (sys/mman.h) — NOTE: NOT 1/2/4 like Linux. Bit-shifted.
	_PROT_NONE  = 0x0
	_PROT_READ  = 0x100
	_PROT_WRITE = 0x200
	_PROT_EXEC  = 0x400

	// mmap flags (sys/mman.h) — NOTE: MAP_ANON is 0x80000, not 0x20.
	_MAP_ANON    = 0x80000
	_MAP_PRIVATE = 0x2
	_MAP_FIXED   = 0x10

	// QNX 6.5 has no madvise(MADV_DONTNEED/FREE); scavenging is a no-op.
	// Defined as 0 so shared code compiles; sysUnused must not rely on them.
	_MADV_DONTNEED = 0x0 // ponytail: unsupported on QNX 6.5 -> sysUnused no-op
	_MADV_FREE     = 0x0 // ponytail: unsupported on QNX 6.5

	// sigaction flags (signal.h) — NOTE: QNX has NO SA_RESTART, NO SA_ONSTACK.
	_SA_SIGINFO = 0x2
	_SA_RESTART = 0x0 // ponytail: absent on QNX 6.5; EINTR retried in Go, verify
	_SA_ONSTACK = 0x0 // ponytail: absent on QNX 6.5; altstack via sigaltstack(SS_*)

	// sigprocmask how (signal.h)
	_SIG_BLOCK   = 0x0
	_SIG_UNBLOCK = 0x1
	_SIG_SETMASK = 0x2

	// _SIG_DFL / _SIG_IGN are declared in signal_unix.go.

	// sigaltstack (signal.h)
	_SS_DISABLE  = 0x2
	_SS_ONSTACK  = 0x1
	_SIGSTKSZ    = 0x2000 // fallback; QNX MINSIGSTKSZ not #defined in 6.5 headers

	// signal numbers (signal.h) — QNX order differs from Linux!
	_SIGHUP    = 0x1  // 1
	_SIGINT    = 0x2  // 2
	_SIGQUIT   = 0x3  // 3
	_SIGILL    = 0x4  // 4
	_SIGTRAP   = 0x5  // 5
	_SIGABRT   = 0x6  // 6
	_SIGEMT    = 0x7  // 7
	_SIGFPE    = 0x8  // 8
	_SIGKILL   = 0x9  // 9
	_SIGBUS    = 0xa  // 10
	_SIGSEGV   = 0xb  // 11
	_SIGSYS    = 0xc  // 12
	_SIGPIPE   = 0xd  // 13
	_SIGALRM   = 0xe  // 14
	_SIGTERM   = 0xf  // 15
	_SIGUSR1   = 0x10 // 16
	_SIGUSR2   = 0x11 // 17
	_SIGCHLD   = 0x12 // 18
	_SIGPWR    = 0x13 // 19
	_SIGWINCH  = 0x14 // 20
	_SIGURG    = 0x15 // 21  (Linux is 23; QNX is 21)
	_SIGPOLL   = 0x16 // 22
	_SIGIO     = 0x16 // == SIGPOLL
	_SIGSTOP   = 0x17 // 23
	_SIGTSTP   = 0x18 // 24
	_SIGCONT   = 0x19 // 25
	_SIGTTIN   = 0x1a // 26
	_SIGTTOU   = 0x1b // 27
	_SIGVTALRM = 0x1c // 28
	_SIGPROF   = 0x1d // 29
	_SIGXCPU   = 0x1e // 30
	_SIGXFSZ   = 0x1f // 31
	_NSIG      = 0x39 // 57

	// si_code fault codes (sys/siginfo.h)
	_FPE_INTDIV = 0x1
	_FPE_INTOVF = 0x2
	_FPE_FLTDIV = 0x3
	_FPE_FLTOVF = 0x4
	_FPE_FLTUND = 0x5
	_FPE_FLTRES = 0x6
	_FPE_FLTINV = 0x7
	_FPE_FLTSUB = 0x8

	_BUS_ADRALN = 0x1
	_BUS_ADRERR = 0x2
	_BUS_OBJERR = 0x3

	_SEGV_MAPERR = 0x1
	_SEGV_ACCERR = 0x2

	_SI_USER = 0x0

	// setitimer (sys/*.h)
	_ITIMER_REAL    = 0x0
	_ITIMER_VIRTUAL = 0x1
	_ITIMER_PROF    = 0x2

	// clock ids (time.h)
	_CLOCK_REALTIME  = 0x0
	_CLOCK_MONOTONIC = 0x2

	// open flags (fcntl.h) — NOTE: octal in headers, values in hex here.
	_O_RDONLY   = 0x0
	_O_WRONLY   = 0x1
	_O_RDWR     = 0x2
	_O_APPEND   = 0x8    // 0o10
	_O_NONBLOCK = 0x80   // 0o200
	_O_CREAT    = 0x100  // 0o400
	_O_TRUNC    = 0x200  // 0o1000
	_O_CLOEXEC  = 0x2000 // 0o20000
)

// sigset_t: struct { long __bits[2]; } — 8 bytes on 32-bit.
type sigset struct {
	__bits [2]uint32
}

// stack_t: { void *ss_sp; size_t ss_size; int ss_flags; } — 12 bytes.
type stackt struct {
	ss_sp    *byte
	ss_size  uintptr
	ss_flags int32
}

// struct timespec { time_t tv_sec; long tv_nsec; } — 8 bytes on 32-bit.
type timespec struct {
	tv_sec  int32
	tv_nsec int32
}

//go:nosplit
func (ts *timespec) setNsec(ns int64) {
	ts.tv_sec = int32(ns / 1e9)
	ts.tv_nsec = int32(ns % 1e9)
}

type timeval struct {
	tv_sec  int32
	tv_usec int32
}

func (tv *timeval) set_usec(x int32) {
	tv.tv_usec = x
}

type itimerval struct {
	it_interval timeval
	it_value    timeval
}

// siginfo_t (sys/siginfo.h) — sizeof 40. Fault variant offsets:
//   si_signo@0 si_code@4 si_errno@8 | __fltno@12 __fltip@16 si_addr@20 __bdslot@24
type siginfo struct {
	si_signo int32
	si_code  int32
	si_errno int32
	__fltno  int32
	__fltip  uintptr
	si_addr  uintptr
	__bdslot int32
	__pad    [3]int32 // pad union to __pad[7] (28 bytes from offset 12)
}

// struct sigaction (signal.h): { handler; int sa_flags; sigset_t sa_mask; } — 16 bytes.
// NOTE: sa_flags comes BEFORE sa_mask (opposite of Linux).
type sigactiont struct {
	sa_handler uintptr // union _sa_handler / _sa_sigaction
	sa_flags   int32
	sa_mask    sigset
}

// ARM mcontext (arm/context.h): ARM_CPU_REGISTERS { uint32 gpr[16]; uint32 spsr; }
// followed by ARM_FPU_REGISTERS (not read by Go).
type mcontextt struct {
	gpr  [16]uint32
	spsr uint32
	fpu  [280]byte // ARM_FPU_REGISTERS pad (X[32]u64 + 4x u32 + slack)
}

// ucontext_t (ucontext.h): { uc_link; sigset uc_sigmask; stackt uc_stack; mcontextt uc_mcontext }
// gpr[0] lands at offset 24; gpr[15]/PC at offset 84.
type ucontextt struct {
	uc_link    uintptr
	uc_sigmask sigset
	uc_stack   stackt
	uc_mcontext mcontextt
}
