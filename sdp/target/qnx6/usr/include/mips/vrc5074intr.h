/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
 * 
 * You must obtain a written license from and pay applicable license fees to QNX 
 * Software Systems before you may reproduce, modify or distribute this software, 
 * or any work that includes all or part of this software.   Free development 
 * licenses are available for evaluation and non-commercial purposes.  For more 
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *  
 * This file may contain contributions from others.  Please review this entire 
 * file for other proprietary rights or license notices, as well as the QNX 
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/ 
 * for other information.
 * $
 */



/*
 * Vrc5074 interrupt number definitions
 *

 *
 */
#ifndef __MIPS_5074INTR_H_INCLUDED
#define __MIPS_5074INTR_H_INCLUDED

#include <sys/neutrino.h>

#define MIPS_INTR_CLASS_VRC5074                 (_NTO_INTR_CLASS_EXTERNAL+0x8500)
#define MIPS_INTR_VRC5074_CPCEEN                (MIPS_INTR_CLASS_VRC5074        +       0)
#define MIPS_INTR_VRC5074_CNTDEN                (MIPS_INTR_CLASS_VRC5074        +       1)
#define MIPS_INTR_VRC5074_MCEEN                 (MIPS_INTR_CLASS_VRC5074        +       2)
#define MIPS_INTR_VRC5074_DMAEN                 (MIPS_INTR_CLASS_VRC5074        +       3)
#define MIPS_INTR_VRC5074_UARTEN                (MIPS_INTR_CLASS_VRC5074        +       4)
#define MIPS_INTR_VRC5074_WDOGEN                (MIPS_INTR_CLASS_VRC5074        +       5)
#define MIPS_INTR_VRC5074_GPTDEN                (MIPS_INTR_CLASS_VRC5074        +       6)
#define MIPS_INTR_VRC5074_LBRTDEN               (MIPS_INTR_CLASS_VRC5074        +       7)
#define MIPS_INTR_VRC5074_INTAEN                (MIPS_INTR_CLASS_VRC5074        +       8)
#define MIPS_INTR_VRC5074_INTBEN                (MIPS_INTR_CLASS_VRC5074        +       9)
#define MIPS_INTR_VRC5074_INTCEN                (MIPS_INTR_CLASS_VRC5074        +       10)
#define MIPS_INTR_VRC5074_INTDEN                (MIPS_INTR_CLASS_VRC5074        +       11)
#define MIPS_INTR_VRC5074_INTEEN                (MIPS_INTR_CLASS_VRC5074        +       12)
#define MIPS_INTR_VRC5074_PCISEN                (MIPS_INTR_CLASS_VRC5074        +       14)
#define MIPS_INTR_VRC5074_PCIEEN                (MIPS_INTR_CLASS_VRC5074        +       15)


#define VRC5074_BASE_PHYS	0x1fa00000
#define VRC5074_BASE_VIRT	0xbfa00000
#define VRC5074_CPUSTAT		0x0080
#define VRC5074_INTCTRL		0x0088
#define VRC5074_INTSTAT0	0x0090
#define VRC5074_INTSTAT1	0x0098
#define VRC5074_INTCLR		0x00a0
#define VRC5074_INTPPES		0x00a8
#define VRC5074_T0CTRL		0x01c0
#define VRC5074_T0CNTR		0x01c8
#define VRC5074_T1CTRL		0x01d0
#define VRC5074_T1CNTR		0x01d8
#define VRC5074_T2CTRL		0x01e0
#define VRC5074_T2CNTR		0x01e8
#define VRC5074_T3CTRL		0x01f0
#define VRC5074_T3CNTR		0x01f8

#endif

/* __SRCVERSION("vrc5074intr.h $Rev: 152112 $"); */
