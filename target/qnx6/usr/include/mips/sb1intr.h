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
 * SB-1 interrupt number definitions
 *

 *
 */
#ifndef __MIPS_SB1INTR_H_INCLUDED
#define __MIPS_SB1INTR_H_INCLUDED

#include <mips/intr.h>

#define SB1_INTR_CLASS		(0x8006UL<<16)
#define SB1_INTR_PERF	(SB1_INTR_CLASS +  0)

#endif

/* __SRCVERSION("sb1intr.h $Rev: 152112 $"); */
