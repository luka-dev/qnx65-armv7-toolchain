// Copyright 2026 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

//go:build qnx && arm

package runtime

import "unsafe"

type sigctxt struct {
	info *siginfo
	ctxt unsafe.Pointer
}

//go:nosplit
//go:nowritebarrierrec
func (c *sigctxt) regs() *mcontextt { return &(*ucontextt)(c.ctxt).uc_mcontext }

func (c *sigctxt) r0() uint32  { return c.regs().gpr[0] }
func (c *sigctxt) r1() uint32  { return c.regs().gpr[1] }
func (c *sigctxt) r2() uint32  { return c.regs().gpr[2] }
func (c *sigctxt) r3() uint32  { return c.regs().gpr[3] }
func (c *sigctxt) r4() uint32  { return c.regs().gpr[4] }
func (c *sigctxt) r5() uint32  { return c.regs().gpr[5] }
func (c *sigctxt) r6() uint32  { return c.regs().gpr[6] }
func (c *sigctxt) r7() uint32  { return c.regs().gpr[7] }
func (c *sigctxt) r8() uint32  { return c.regs().gpr[8] }
func (c *sigctxt) r9() uint32  { return c.regs().gpr[9] }
func (c *sigctxt) r10() uint32 { return c.regs().gpr[10] }
func (c *sigctxt) fp() uint32  { return c.regs().gpr[11] }
func (c *sigctxt) ip() uint32  { return c.regs().gpr[12] }
func (c *sigctxt) sp() uint32  { return c.regs().gpr[13] }
func (c *sigctxt) lr() uint32  { return c.regs().gpr[14] }

//go:nosplit
//go:nowritebarrierrec
func (c *sigctxt) pc() uint32 { return c.regs().gpr[15] }

func (c *sigctxt) cpsr() uint32   { return c.regs().spsr }
func (c *sigctxt) fault() uintptr { return c.info.si_addr }
func (c *sigctxt) trap() uint32   { return 0 }
func (c *sigctxt) error() uint32  { return 0 }
func (c *sigctxt) oldmask() uint32 { return 0 }

func (c *sigctxt) sigcode() uint32 { return uint32(c.info.si_code) }
func (c *sigctxt) sigaddr() uint32 { return uint32(c.info.si_addr) }

func (c *sigctxt) set_pc(x uint32)  { c.regs().gpr[15] = x }
func (c *sigctxt) set_sp(x uint32)  { c.regs().gpr[13] = x }
func (c *sigctxt) set_lr(x uint32)  { c.regs().gpr[14] = x }
func (c *sigctxt) set_r10(x uint32) { c.regs().gpr[10] = x }

func (c *sigctxt) set_sigcode(x uint32) { c.info.si_code = int32(x) }
func (c *sigctxt) set_sigaddr(x uint32) { c.info.si_addr = uintptr(x) }
