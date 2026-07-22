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
 * Vrc4372 interrupt number definitions
 *

 *
 */
#ifndef __MIPS_4372INTR_H_INCLUDED
#define __MIPS_4372INTR_H_INCLUDED

#include <sys/neutrino.h>

#define MIPS_INTR_CLASS_VRC4372		(_NTO_INTR_CLASS_EXTERNAL+0x8000)
#define MIPS_INTR_VRC4372_0			(MIPS_INTR_CLASS_VRC4372	+	0)
#define MIPS_INTR_VRC4372_1			(MIPS_INTR_CLASS_VRC4372	+	1)
#define MIPS_INTR_VRC4372_2			(MIPS_INTR_CLASS_VRC4372	+	2)
#define MIPS_INTR_VRC4372_3			(MIPS_INTR_CLASS_VRC4372	+	3)
#define MIPS_INTR_VRC4372_4			(MIPS_INTR_CLASS_VRC4372	+	4)
#define MIPS_INTR_VRC4372_5			(MIPS_INTR_CLASS_VRC4372	+	5)
#define MIPS_INTR_VRC4372_6			(MIPS_INTR_CLASS_VRC4372	+	6)
#define MIPS_INTR_VRC4372_7			(MIPS_INTR_CLASS_VRC4372	+	7)
#define MIPS_INTR_VRC4372_8			(MIPS_INTR_CLASS_VRC4372	+	8)
#define MIPS_INTR_VRC4372_9			(MIPS_INTR_CLASS_VRC4372	+	9)
#define MIPS_INTR_VRC4372_10		(MIPS_INTR_CLASS_VRC4372	+	10)
#define MIPS_INTR_VRC4372_11		(MIPS_INTR_CLASS_VRC4372	+	11)
#define MIPS_INTR_VRC4372_12		(MIPS_INTR_CLASS_VRC4372	+	12)
#define MIPS_INTR_VRC4372_13		(MIPS_INTR_CLASS_VRC4372	+	13)

#endif

/* __SRCVERSION("vrc4372intr.h $Rev: 152112 $"); */
