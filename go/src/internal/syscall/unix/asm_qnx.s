// Copyright 2026 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "textflag.h"

// QNX system calls are implemented in runtime/syscall_qnx.go.

TEXT ·syscall6(SB),NOSPLIT,$0-40
	JMP	syscall·sysvicall6(SB)

TEXT ·rawSyscall6(SB),NOSPLIT,$0-40
	JMP	syscall·rawSysvicall6(SB)
