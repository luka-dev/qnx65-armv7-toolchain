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
 * AU1000 interrupt number definitions
 *

 *
 */
#ifndef __MIPS_AU1000INTR_H_INCLUDED
#define __MIPS_AU1000INTR_H_INCLUDED

#include <mips/intr.h>

#define AU1000_INTR_CLASS_SYS		(0x8004UL<<16)
#define AU1000_INTR_UART0			(AU1000_INTR_CLASS_SYS+0)
#define AU1000_INTR_UART1			(AU1000_INTR_CLASS_SYS+1)
#define AU1000_INTR_UART2			(AU1000_INTR_CLASS_SYS+2) 
#define AU1000_INTR_UART3			(AU1000_INTR_CLASS_SYS+3) 
#define AU1000_INTR_SSI0			(AU1000_INTR_CLASS_SYS+4)
#define AU1000_INTR_SSI1			(AU1000_INTR_CLASS_SYS+5)
#define AU1000_INTR_DMA0			(AU1000_INTR_CLASS_SYS+6)
#define AU1000_INTR_DMA1			(AU1000_INTR_CLASS_SYS+7)
#define AU1000_INTR_DMA2			(AU1000_INTR_CLASS_SYS+8)
#define AU1000_INTR_DMA3			(AU1000_INTR_CLASS_SYS+9) 
#define AU1000_INTR_DMA4			(AU1000_INTR_CLASS_SYS+10)
#define AU1000_INTR_DMA5			(AU1000_INTR_CLASS_SYS+11)
#define AU1000_INTR_DMA6			(AU1000_INTR_CLASS_SYS+12)
#define AU1000_INTR_DMA7			(AU1000_INTR_CLASS_SYS+13)
#define AU1000_INTR_TOY				(AU1000_INTR_CLASS_SYS+14)
#define AU1000_INTR_TOY_MATCH0		(AU1000_INTR_CLASS_SYS+15)
#define AU1000_INTR_TOY_MATCH1		(AU1000_INTR_CLASS_SYS+16)
#define AU1000_INTR_TOY_MATCH2		(AU1000_INTR_CLASS_SYS+17)
#define AU1000_INTR_RTC 			(AU1000_INTR_CLASS_SYS+18)
#define AU1000_INTR_RTC_MATCH0		(AU1000_INTR_CLASS_SYS+19) 
#define AU1000_INTR_RTC_MATCH1		(AU1000_INTR_CLASS_SYS+20) 
#define AU1000_INTR_RTC_MATCH2		(AU1000_INTR_CLASS_SYS+21)
#define AU1000_INTR_IRDA_TX			(AU1000_INTR_CLASS_SYS+22)
#define AU1000_INTR_IRDA_RX			(AU1000_INTR_CLASS_SYS+23)
#define AU1000_INTR_USB_DEV_REQ		(AU1000_INTR_CLASS_SYS+24)
#define AU1000_INTR_USB_DEV_SUS		(AU1000_INTR_CLASS_SYS+25)
#define AU1000_INTR_USB_HOST		(AU1000_INTR_CLASS_SYS+26) 
#define AU1000_INTR_AC97_ACSYNC		(AU1000_INTR_CLASS_SYS+27)
#define AU1000_INTR_MAC0			(AU1000_INTR_CLASS_SYS+28)
#define AU1000_INTR_MAC1			(AU1000_INTR_CLASS_SYS+29)
#define AU1000_INTR_RESERVED		(AU1000_INTR_CLASS_SYS+30)
#define AU1000_INTR_AC97			(AU1000_INTR_CLASS_SYS+31)

#endif                                                      

/* __SRCVERSION("au1000intr.h $Rev: 152112 $"); */
