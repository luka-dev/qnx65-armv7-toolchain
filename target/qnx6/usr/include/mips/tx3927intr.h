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
 * MIPS 4122 interrupt number definitions
 *

 *
 */
#ifndef __MIPS_4122INTR_H_INCLUDED
#define __MIPS_4122INTR_H_INCLUDED

#define TX3927_INTR_INT0				(_NTO_INTR_CLASS_EXTERNAL+0)
#define TX3927_INTR_INT1				(_NTO_INTR_CLASS_EXTERNAL+1)
#define TX3927_INTR_INT2				(_NTO_INTR_CLASS_EXTERNAL+2)
#define TX3927_INTR_INT3				(_NTO_INTR_CLASS_EXTERNAL+3)
#define TX3927_INTR_INT4				(_NTO_INTR_CLASS_EXTERNAL+4)
#define TX3927_INTR_INT5				(_NTO_INTR_CLASS_EXTERNAL+5)
#define TX3927_INTR_SIO0				(_NTO_INTR_CLASS_EXTERNAL+6)
#define TX3927_INTR_SIO1				(_NTO_INTR_CLASS_EXTERNAL+7)
#define TX3927_INTR_DMA					(_NTO_INTR_CLASS_EXTERNAL+8)
#define TX3927_INTR_PIO					(_NTO_INTR_CLASS_EXTERNAL+9)
#define TX3927_INTR_PCI					(_NTO_INTR_CLASS_EXTERNAL+10)
#define TX3927_INTR_RESERVED1			(_NTO_INTR_CLASS_EXTERNAL+11)
#define TX3927_INTR_RESERVED2			(_NTO_INTR_CLASS_EXTERNAL+12)
#define TX3927_INTR_TMR0				(_NTO_INTR_CLASS_EXTERNAL+13)
#define TX3927_INTR_TMR1				(_NTO_INTR_CLASS_EXTERNAL+14)
#define TX3927_INTR_TMR2				(_NTO_INTR_CLASS_EXTERNAL+15)

#endif

/* __SRCVERSION("tx3927intr.h $Rev: 152112 $"); */
