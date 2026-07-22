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
 * 8259 interrupt numbers for MIPS
 *

 *
 */
#ifndef __MIPS_8259INTR_H_INCLUDED
#define __MIPS_8259INTR_H_INCLUDED

#include <mips/intr.h>

#define MIPS8259_INTR_CLASS_SYS			(0x8002UL<<16)
#define MIPS8259_INTR_INT0			(MIPS8259_INTR_CLASS_SYS+0)
#define MIPS8259_INTR_INT1			(MIPS8259_INTR_CLASS_SYS+1)
#define MIPS8259_INTR_INT2			(MIPS8259_INTR_CLASS_SYS+2) /*cascades to slave*/
#define MIPS8259_INTR_INT3			(MIPS8259_INTR_CLASS_SYS+3) 
#define MIPS8259_INTR_INT4			(MIPS8259_INTR_CLASS_SYS+4)
#define MIPS8259_INTR_INT5			(MIPS8259_INTR_CLASS_SYS+5)
#define MIPS8259_INTR_INT6			(MIPS8259_INTR_CLASS_SYS+6)
#define MIPS8259_INTR_INT7			(MIPS8259_INTR_CLASS_SYS+7)
#define MIPS8259_INTR_INT8			(MIPS8259_INTR_CLASS_SYS+8)
#define MIPS8259_INTR_INT9			(MIPS8259_INTR_CLASS_SYS+9) /*from master*/
#define MIPS8259_INTR_INT10			(MIPS8259_INTR_CLASS_SYS+10)
#define MIPS8259_INTR_INT11			(MIPS8259_INTR_CLASS_SYS+11)
#define MIPS8259_INTR_INT12			(MIPS8259_INTR_CLASS_SYS+12)
#define MIPS8259_INTR_INT13			(MIPS8259_INTR_CLASS_SYS+13)
#define MIPS8259_INTR_INT14			(MIPS8259_INTR_CLASS_SYS+14)
#define MIPS8259_INTR_INT15			(MIPS8259_INTR_CLASS_SYS+15)

#endif

/* __SRCVERSION("8259intr.h $Rev: 152112 $"); */
