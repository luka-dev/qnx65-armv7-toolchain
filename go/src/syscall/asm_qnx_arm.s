// Copyright 2026 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "textflag.h"

//
// QNX system calls are implemented in ../runtime/syscall_qnx.go, reached here.
//

TEXT ·sysvicall6(SB),NOSPLIT,$0
	JMP	runtime·syscall_sysvicall6(SB)

TEXT ·rawSysvicall6(SB),NOSPLIT,$0
	JMP	runtime·syscall_rawsysvicall6(SB)
