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
 * Jolt interrupt number definitions
 *

 *
 */
#ifndef __MIPS_JOLTINTR_H_INCLUDED
#define __MIPS_JOLTINTR_H_INCLUDED

#include <mips/intr.h>

#define JOLT_INTR_CLASS_SYS			(0x8003UL<<16)
#define JOLT_INTR_GBUS				(JOLT_INTR_CLASS_SYS+0)
#define JOLT_INTR_PCI 				(JOLT_INTR_CLASS_SYS+1)
#define JOLT_INTR_DMA				(JOLT_INTR_CLASS_SYS+5) 
#define JOLT_INTR_TIMER0			(JOLT_INTR_CLASS_SYS+6) 
#define JOLT_INTR_TIMER1			(JOLT_INTR_CLASS_SYS+7)
#define JOLT_INTR_TIMER2			(JOLT_INTR_CLASS_SYS+8)
#define JOLT_INTR_UART0				(JOLT_INTR_CLASS_SYS+9)
#define JOLT_INTR_UART1				(JOLT_INTR_CLASS_SYS+10)
#define JOLT_INTR_PCI_RESET			(JOLT_INTR_CLASS_SYS+20)
#define JOLT_INTR_VGPORT1			(JOLT_INTR_CLASS_SYS+22)
#define JOLT_INTR_VGPORT2			(JOLT_INTR_CLASS_SYS+23)
#define JOLT_INTR_PW2D				(JOLT_INTR_CLASS_SYS+24) 
#define JOLT_INTR_PW97				(JOLT_INTR_CLASS_SYS+25)
#define JOLT_INTR_USB				(JOLT_INTR_CLASS_SYS+26)
#define JOLT_INTR_2WIRE_SERIAL		(JOLT_INTR_CLASS_SYS+27)
#define JOLT_INTR_IR				(JOLT_INTR_CLASS_SYS+28)
#define JOLT_INTR_GPIO1				(JOLT_INTR_CLASS_SYS+29)
#define JOLT_INTR_GPIO2				(JOLT_INTR_CLASS_SYS+30)
#define JOLT_INTR_GPIO3				(JOLT_INTR_CLASS_SYS+31)
#define JOLT_INTR_GPIO4				(JOLT_INTR_CLASS_SYS+32)
#define JOLT_INTR_GPIO5				(JOLT_INTR_CLASS_SYS+33)
#define JOLT_INTR_GPIO6				(JOLT_INTR_CLASS_SYS+34)
#define JOLT_INTR_GPIO7				(JOLT_INTR_CLASS_SYS+35)
#define JOLT_INTR_GPIO8				(JOLT_INTR_CLASS_SYS+36)
#define JOLT_INTR_GPIO9				(JOLT_INTR_CLASS_SYS+37)
#define JOLT_INTR_GPIO10			(JOLT_INTR_CLASS_SYS+38)
#define JOLT_INTR_GPIO11			(JOLT_INTR_CLASS_SYS+39)
#define JOLT_INTR_GPIO12			(JOLT_INTR_CLASS_SYS+40)
#define JOLT_INTR_GPIO13			(JOLT_INTR_CLASS_SYS+41)
#define JOLT_INTR_GPIO14			(JOLT_INTR_CLASS_SYS+42)
#define JOLT_INTR_GPIO15			(JOLT_INTR_CLASS_SYS+43)
#define JOLT_INTR_GPIO16			(JOLT_INTR_CLASS_SYS+44)
#define JOLT_INTR_GPIO17			(JOLT_INTR_CLASS_SYS+45)
#define JOLT_INTR_GPIO18			(JOLT_INTR_CLASS_SYS+46)
#define JOLT_INTR_GPIO19			(JOLT_INTR_CLASS_SYS+47)
#define JOLT_INTR_GPIO20			(JOLT_INTR_CLASS_SYS+48)
#define JOLT_INTR_GPIO21			(JOLT_INTR_CLASS_SYS+49)
#define JOLT_INTR_GPIO22			(JOLT_INTR_CLASS_SYS+50)
#define JOLT_INTR_GPIO23			(JOLT_INTR_CLASS_SYS+51)
#define JOLT_INTR_GPIO24			(JOLT_INTR_CLASS_SYS+52)
#define JOLT_INTR_GPIO25			(JOLT_INTR_CLASS_SYS+53)
#define JOLT_INTR_GPIO26			(JOLT_INTR_CLASS_SYS+54)
#define JOLT_INTR_GPIO27			(JOLT_INTR_CLASS_SYS+55)
#define JOLT_INTR_GPIO28			(JOLT_INTR_CLASS_SYS+56)
#define JOLT_INTR_GPIO29			(JOLT_INTR_CLASS_SYS+57)
#define JOLT_INTR_GPIO30			(JOLT_INTR_CLASS_SYS+58)
#define JOLT_INTR_GPIO31			(JOLT_INTR_CLASS_SYS+59)
#define JOLT_INTR_GPIO32			(JOLT_INTR_CLASS_SYS+60)
#define JOLT_INTR_GPIO33   			(JOLT_INTR_CLASS_SYS+61)
#define JOLT_INTR_GPIO34			(JOLT_INTR_CLASS_SYS+62)
#define JOLT_INTR_GPIO35			(JOLT_INTR_CLASS_SYS+63)

#endif

/* __SRCVERSION("joltintr.h $Rev: 152112 $"); */
