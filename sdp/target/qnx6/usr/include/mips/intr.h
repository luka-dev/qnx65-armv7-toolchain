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
 * MIPS interrupt numbers
 *

 *
 */
#ifndef __MIPS_INTR_H_INCLUDED
#define __MIPS_INTR_H_INCLUDED

#include <sys/neutrino.h>

#define MIPS_INTR_SW0				(_NTO_INTR_CLASS_EXTERNAL+0)
#define MIPS_INTR_SW1				(_NTO_INTR_CLASS_EXTERNAL+1)
#define MIPS_INTR_HW0				(_NTO_INTR_CLASS_EXTERNAL+2)
#define MIPS_INTR_HW1				(_NTO_INTR_CLASS_EXTERNAL+3)
#define MIPS_INTR_HW2				(_NTO_INTR_CLASS_EXTERNAL+4)
#define MIPS_INTR_HW3				(_NTO_INTR_CLASS_EXTERNAL+5)
#define MIPS_INTR_HW4				(_NTO_INTR_CLASS_EXTERNAL+6)
#define MIPS_INTR_HW5				(_NTO_INTR_CLASS_EXTERNAL+7)
#define MIPS_INTR_TIMER				(_NTO_INTR_CLASS_EXTERNAL+7)

#endif

/* __SRCVERSION("intr.h $Rev: 152112 $"); */
