// Copyright 2026 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

//go:build qnx

package runtime

// Indexed by QNX 6.5 signal numbers (differ from Linux: SIGBUS=10, SIGURG=21…).
var sigtable = [...]sigTabT{
	0:          {0, "SIGNONE: no trap"},
	_SIGHUP:    {_SigNotify + _SigKill, "SIGHUP: terminal line hangup"},
	_SIGINT:    {_SigNotify + _SigKill, "SIGINT: interrupt"},
	_SIGQUIT:   {_SigNotify + _SigThrow, "SIGQUIT: quit"},
	_SIGILL:    {_SigThrow + _SigUnblock, "SIGILL: illegal instruction"},
	_SIGTRAP:   {_SigThrow + _SigUnblock, "SIGTRAP: trace trap"},
	_SIGABRT:   {_SigNotify + _SigThrow, "SIGABRT: abort"},
	_SIGEMT:    {_SigThrow, "SIGEMT: emulate instruction executed"},
	_SIGFPE:    {_SigPanic + _SigUnblock, "SIGFPE: floating-point exception"},
	_SIGKILL:   {0, "SIGKILL: kill"},
	_SIGBUS:    {_SigPanic + _SigUnblock, "SIGBUS: bus error"},
	_SIGSEGV:   {_SigPanic + _SigUnblock, "SIGSEGV: segmentation violation"},
	_SIGSYS:    {_SigThrow, "SIGSYS: bad system call"},
	_SIGPIPE:   {_SigNotify, "SIGPIPE: write to broken pipe"},
	_SIGALRM:   {_SigNotify, "SIGALRM: alarm clock"},
	_SIGTERM:   {_SigNotify + _SigKill, "SIGTERM: termination"},
	_SIGUSR1:   {_SigNotify, "SIGUSR1: user-defined signal 1"},
	_SIGUSR2:   {_SigNotify, "SIGUSR2: user-defined signal 2"},
	_SIGCHLD:   {_SigNotify + _SigUnblock, "SIGCHLD: child status has changed"},
	_SIGPWR:    {_SigNotify, "SIGPWR: power failure restart"},
	_SIGWINCH:  {_SigNotify, "SIGWINCH: window size change"},
	_SIGURG:    {_SigNotify, "SIGURG: urgent condition on socket"},
	_SIGPOLL:   {_SigNotify, "SIGPOLL/SIGIO: pollable event occurred"},
	_SIGSTOP:   {0, "SIGSTOP: stop, unblockable"},
	_SIGTSTP:   {_SigNotify + _SigDefault, "SIGTSTP: keyboard stop"},
	_SIGCONT:   {_SigNotify + _SigDefault, "SIGCONT: continue"},
	_SIGTTIN:   {_SigNotify + _SigDefault, "SIGTTIN: background read from tty"},
	_SIGTTOU:   {_SigNotify + _SigDefault, "SIGTTOU: background write to tty"},
	_SIGVTALRM: {_SigNotify, "SIGVTALRM: virtual alarm clock"},
	_SIGPROF:   {_SigNotify + _SigUnblock, "SIGPROF: profiling alarm clock"},
	_SIGXCPU:   {_SigNotify, "SIGXCPU: cpu limit exceeded"},
	_SIGXFSZ:   {_SigNotify, "SIGXFSZ: file size limit exceeded"},
	// QNX signals 32..40 are unused; 41..56 are SIGRTMIN..SIGRTMAX. initsig
	// iterates i < _NSIG (57) and indexes sigtable[i], so the array MUST be
	// _NSIG long. Size it with a sentinel at the top; the gaps default to {0,""}
	// (flags==0 -> skipped).
	_NSIG - 1: {_SigNotify, "signal RTMAX"},
}
