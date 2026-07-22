/*
 * $QNXLicenseC:
 * Copyright 2008, QNX Software Systems. 
 * 
 * Licensed under the Apache License, Version 2.0 (the "License"). You 
 * may not reproduce, modify or distribute this software except in 
 * compliance with the License. You may obtain a copy of the License 
 * at: http://www.apache.org/licenses/LICENSE-2.0 
 * 
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" basis, 
 * WITHOUT WARRANTIES OF ANY KIND, either express or implied.
 *
 * This file may contain contributions from others, either as 
 * contributors under the License or as licensors under other terms.  
 * Please review this entire file for other proprietary rights or license 
 * notices, as well as the QNX Development Suite License Guide at 
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */




/*
 * PPC800 interrupt number definitions
 *

 *
 */
#ifndef __PPC_800INTR_H_INCLUDED
#define __PPC_800INTR_H_INCLUDED

#include <ppc/intr.h>

#define PPC800_INTR_IRQ0	(_NTO_INTR_CLASS_EXTERNAL + 0)
#define PPC800_INTR_LVL0	(_NTO_INTR_CLASS_EXTERNAL + 1)
#define PPC800_INTR_IRQ1	(_NTO_INTR_CLASS_EXTERNAL + 2)
#define PPC800_INTR_LVL1	(_NTO_INTR_CLASS_EXTERNAL + 3)
#define PPC800_INTR_IRQ2	(_NTO_INTR_CLASS_EXTERNAL + 4)
#define PPC800_INTR_LVL2	(_NTO_INTR_CLASS_EXTERNAL + 5)
#define PPC800_INTR_IRQ3	(_NTO_INTR_CLASS_EXTERNAL + 6)
#define PPC800_INTR_LVL3	(_NTO_INTR_CLASS_EXTERNAL + 7)
#define PPC800_INTR_IRQ4	(_NTO_INTR_CLASS_EXTERNAL + 8)
#define PPC800_INTR_LVL4	(_NTO_INTR_CLASS_EXTERNAL + 9)
#define PPC800_INTR_IRQ5	(_NTO_INTR_CLASS_EXTERNAL + 10)
#define PPC800_INTR_LVL5	(_NTO_INTR_CLASS_EXTERNAL + 11)
#define PPC800_INTR_IRQ6	(_NTO_INTR_CLASS_EXTERNAL + 12)
#define PPC800_INTR_LVL6	(_NTO_INTR_CLASS_EXTERNAL + 13)
#define PPC800_INTR_IRQ7	(_NTO_INTR_CLASS_EXTERNAL + 14)
#define PPC800_INTR_LVL7	(_NTO_INTR_CLASS_EXTERNAL + 15)

/* CPM class */
#define PPC800_INTR_CLASS_CPM	(0x8001 << 16)
#define PPC800_INTR_CPMNONE		(PPC800_INTR_CLASS_CPM	+ 0X0000)
#define PPC800_INTR_CPMPC4		(PPC800_INTR_CLASS_CPM	+ 0X0001)
#define PPC800_INTR_CPMPC5		(PPC800_INTR_CLASS_CPM	+ 0X0002)
#define PPC800_INTR_CPMSMC2PIP	(PPC800_INTR_CLASS_CPM	+ 0X0003)
#define PPC800_INTR_CPMSMC1		(PPC800_INTR_CLASS_CPM	+ 0X0004)
#define PPC800_INTR_CPMSPI 		(PPC800_INTR_CLASS_CPM	+ 0X0005)
#define PPC800_INTR_CPMPC6		(PPC800_INTR_CLASS_CPM	+ 0X0006)
#define PPC800_INTR_CPMTMR4		(PPC800_INTR_CLASS_CPM	+ 0X0007)
#define PPC800_INTR_CPMPC7		(PPC800_INTR_CLASS_CPM	+ 0X0009)
#define PPC800_INTR_CPMPC8		(PPC800_INTR_CLASS_CPM	+ 0X000a)
#define PPC800_INTR_CPMPC9		(PPC800_INTR_CLASS_CPM	+ 0X000b)
#define PPC800_INTR_CPMTMR3		(PPC800_INTR_CLASS_CPM	+ 0X000c)
#define PPC800_INTR_CPMPC10		(PPC800_INTR_CLASS_CPM	+ 0X000e)
#define PPC800_INTR_CPMPC11		(PPC800_INTR_CLASS_CPM	+ 0X000f)
#define PPC800_INTR_CPMI2C 		(PPC800_INTR_CLASS_CPM	+ 0X0010)
#define PPC800_INTR_CPMTMRT		(PPC800_INTR_CLASS_CPM	+ 0X0011)
#define PPC800_INTR_CPMTMR2		(PPC800_INTR_CLASS_CPM	+ 0X0012)
#define PPC800_INTR_CPMIDMA2	(PPC800_INTR_CLASS_CPM	+ 0X0014)
#define PPC800_INTR_CPMIDMA1	(PPC800_INTR_CLASS_CPM	+ 0X0015)
#define PPC800_INTR_CPMSDMA		(PPC800_INTR_CLASS_CPM	+ 0X0016)
#define PPC800_INTR_CPMPC12		(PPC800_INTR_CLASS_CPM	+ 0X0017)
#define PPC800_INTR_CPMPC13		(PPC800_INTR_CLASS_CPM	+ 0X0018)
#define PPC800_INTR_CPMTMR1		(PPC800_INTR_CLASS_CPM	+ 0X0019)
#define PPC800_INTR_CPMPC14		(PPC800_INTR_CLASS_CPM	+ 0X001a)
#define PPC800_INTR_CPMSCC4		(PPC800_INTR_CLASS_CPM	+ 0X001b)
#define PPC800_INTR_CPMSCC3		(PPC800_INTR_CLASS_CPM	+ 0X001c)
#define PPC800_INTR_CPMSCC2		(PPC800_INTR_CLASS_CPM	+ 0X001d)
#define PPC800_INTR_CPMSCC1		(PPC800_INTR_CLASS_CPM	+ 0X001e)
#define PPC800_INTR_CPMPC15		(PPC800_INTR_CLASS_CPM	+ 0X001f)

#endif

/* __SRCVERSION("800intr.h $Rev: 169799 $"); */
