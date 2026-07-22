// Copyright 2026 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// Runtime-side bridge for the syscall package on QNX. The syscall package's
// asm stubs (asm_qnx_arm.s) jump here; these funnel libc calls through the same
// asmsysvicall6 bridge the runtime itself uses. Mirrors syscall_solaris.go.

//go:build qnx

package runtime

import "unsafe"

//go:nosplit
//go:linkname syscall_sysvicall6
//go:cgo_unsafe_args
func syscall_sysvicall6(fn, nargs, a1, a2, a3, a4, a5, a6 uintptr) (r1, r2, err uintptr) {
	call := libcall{
		fn:   fn,
		n:    nargs,
		args: uintptr(unsafe.Pointer(&a1)),
	}
	entersyscallblock()
	asmcgocall(unsafe.Pointer(&asmsysvicall6x), unsafe.Pointer(&call))
	exitsyscall()
	return call.r1, call.r2, call.err
}

//go:nosplit
//go:linkname syscall_rawsysvicall6
//go:cgo_unsafe_args
func syscall_rawsysvicall6(fn, nargs, a1, a2, a3, a4, a5, a6 uintptr) (r1, r2, err uintptr) {
	call := libcall{
		fn:   fn,
		n:    nargs,
		args: uintptr(unsafe.Pointer(&a1)),
	}
	asmcgocall(unsafe.Pointer(&asmsysvicall6x), unsafe.Pointer(&call))
	return call.r1, call.r2, call.err
}
