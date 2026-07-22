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
 * M1543 interrupt classes
 *

 *
 */
#ifndef __MIPS_1543INTR_H_INCLUDED
#define __MIPS_1543INTR_H_INCLUDED

#include <sys/neutrino.h>

#define MIPS_INTR_CLASS_M1543		(_NTO_INTR_CLASS_EXTERNAL+0x8750)
#define MIPS_INTR_M1543_1		(MIPS_INTR_CLASS_M1543	+	0)
#define MIPS_INTR_M1543_3		(MIPS_INTR_CLASS_M1543	+	1)
#define MIPS_INTR_M1543_4		(MIPS_INTR_CLASS_M1543	+	2)
#define MIPS_INTR_M1543_5		(MIPS_INTR_CLASS_M1543	+	3)
#define MIPS_INTR_M1543_6		(MIPS_INTR_CLASS_M1543	+	4)
#define MIPS_INTR_M1543_7		(MIPS_INTR_CLASS_M1543	+	5)
#define MIPS_INTR_M1543_8		(MIPS_INTR_CLASS_M1543	+	6)
#define MIPS_INTR_M1543_9		(MIPS_INTR_CLASS_M1543	+	7)
#define MIPS_INTR_M1543_10		(MIPS_INTR_CLASS_M1543	+	8)
#define MIPS_INTR_M1543_11		(MIPS_INTR_CLASS_M1543	+	9)
#define MIPS_INTR_M1543_12		(MIPS_INTR_CLASS_M1543	+	10)
#define MIPS_INTR_M1543_13		(MIPS_INTR_CLASS_M1543	+	11)
#define MIPS_INTR_M1543_14		(MIPS_INTR_CLASS_M1543	+	12)
#define MIPS_INTR_M1543_15		(MIPS_INTR_CLASS_M1543	+	13)

#endif

/* __SRCVERSION("m1543intr.h $Rev: 152112 $"); */
