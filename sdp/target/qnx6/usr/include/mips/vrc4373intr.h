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
 * Vrc4373 interrupt number definitions
 *

 *
 */
#ifndef __MIPS_4373INTR_H_INCLUDED
#define __MIPS_4373INTR_H_INCLUDED

#include <sys/neutrino.h>

#define MIPS_INTR_CLASS_VRC4373		(_NTO_INTR_CLASS_EXTERNAL+0x9000)
#define MIPS_INTR_VRC4373_CBE		(MIPS_INTR_CLASS_VRC4373	+	0)
#define MIPS_INTR_VRC4373_DMA1		(MIPS_INTR_CLASS_VRC4373	+	1)
#define MIPS_INTR_VRC4373_DMA2		(MIPS_INTR_CLASS_VRC4373	+	2)
#define MIPS_INTR_VRC4373_MB1		(MIPS_INTR_CLASS_VRC4373	+	3)
#define MIPS_INTR_VRC4373_MB2		(MIPS_INTR_CLASS_VRC4373	+	4)
#define MIPS_INTR_VRC4373_DBE		(MIPS_INTR_CLASS_VRC4373	+	5)
#define MIPS_INTR_VRC4373_PBE		(MIPS_INTR_CLASS_VRC4373	+	6)
#define MIPS_INTR_VRC4373_PAR		(MIPS_INTR_CLASS_VRC4373	+	7)

#endif

/* __SRCVERSION("vrc4373intr.h $Rev: 152112 $"); */
