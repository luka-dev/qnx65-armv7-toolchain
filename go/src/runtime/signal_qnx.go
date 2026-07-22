// Copyright 2026 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

//go:build qnx

package runtime

import (
	"internal/abi"
	"unsafe"
)

// sigtramp is the signal-handler entry trampoline, implemented in sys_qnx_arm.s.
func sigtramp()

var sigset_all = sigset{__bits: [2]uint32{^uint32(0), ^uint32(0)}}

//go:nosplit
//go:nowritebarrierrec
func sigaction(sig uint32, new, old *sigactiont) {
	sysvicall3(&libc_sigaction, uintptr(sig), uintptr(unsafe.Pointer(new)), uintptr(unsafe.Pointer(old)))
}

//go:nosplit
//go:nowritebarrierrec
func setsig(i uint32, fn uintptr) {
	var sa sigactiont
	sa.sa_flags = _SA_SIGINFO | _SA_ONSTACK | _SA_RESTART
	sa.sa_mask = sigset_all
	if fn == abi.FuncPCABIInternal(sighandler) {
		fn = abi.FuncPCABI0(sigtramp)
	}
	sa.sa_handler = fn
	sigaction(i, &sa, nil)
}

//go:nosplit
//go:nowritebarrierrec
func setsigstack(i uint32) {
	var sa sigactiont
	sigaction(i, nil, &sa)
	h := sa.sa_handler
	if h == 0 || h == _SIG_DFL || h == _SIG_IGN || sa.sa_flags&_SA_ONSTACK != 0 {
		return
	}
	sa.sa_flags |= _SA_ONSTACK
	sigaction(i, &sa, nil)
}

//go:nosplit
//go:nowritebarrierrec
func getsig(i uint32) uintptr {
	var sa sigactiont
	sigaction(i, nil, &sa)
	return sa.sa_handler
}

//go:nosplit
func setSignalstackSP(s *stackt, sp uintptr) {
	s.ss_sp = (*byte)(unsafe.Pointer(sp))
}

//go:nosplit
//go:nowritebarrierrec
func sigaddset(mask *sigset, i int) {
	mask.__bits[(i-1)/32] |= 1 << (uint32(i-1) & 31)
}

func sigdelset(mask *sigset, i int) {
	mask.__bits[(i-1)/32] &^= 1 << (uint32(i-1) & 31)
}

//go:nosplit
func sigaltstack(new, old *stackt) {
	// ponytail: QNX 6.5 has NO sigaltstack() (verified absent from libc.so.3).
	// Report the alt stack as disabled so minitSignalStack runs signals on the
	// current stack. A QNX-native alt-stack mechanism is the M4 milestone.
	if old != nil {
		old.ss_sp = nil
		old.ss_size = 0
		old.ss_flags = _SS_DISABLE
	}
}

// dumpregs is provided generically by signal_arm.go.
