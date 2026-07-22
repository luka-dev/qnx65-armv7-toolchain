/*
 * $QNXLicenseC:
 * Copyright 2008, QNX Software Systems. 
 * 
 * Licensed under the Apache License, Version 2.0 (the "License"). You 
 * may not reproduce, modify or distribute this software except in 
 * compliance with the License. You may obtain a copy of the License 
 * at: http://www.apache.org/licenses/LICENSE-2.0 
 * 
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" basis, 
 * WITHOUT WARRANTIES OF ANY KIND, either express or implied.
 *
 * This file may contain contributions from others, either as 
 * contributors under the License or as licensors under other terms.  
 * Please review this entire file for other proprietary rights or license 
 * notices, as well as the QNX Development Suite License Guide at 
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */




/*
 * PPC83xx interrupt number definitions
 *
 */

#ifndef __PPC_83xxINTR_H_INCLUDED
#define __PPC_83xxINTR_H_INCLUDED

#include <ppc/intr.h>

/* CLASS GENERAL */
#define PPC83xx_INTR_CLASS_GENRAL	_NTO_INTR_CLASS_EXTERNAL
#define PPC83xx_INTR_GEN_NONE		(PPC83xx_INTR_CLASS_GENRAL + 0x0000)
#define PPC83xx_INTR_GEN_UART1		(PPC83xx_INTR_CLASS_GENRAL + 0x0009)
#define PPC83xx_INTR_GEN_UART2		(PPC83xx_INTR_CLASS_GENRAL + 0x000A)
#define PPC83xx_INTR_GEN_SEC		(PPC83xx_INTR_CLASS_GENRAL + 0x000B)
#define PPC83xx_INTR_GEN_I2C1		(PPC83xx_INTR_CLASS_GENRAL + 0x000E)
#define PPC83xx_INTR_GEN_I2C2		(PPC83xx_INTR_CLASS_GENRAL + 0x000F)
#define PPC83xx_INTR_GEN_SPI		(PPC83xx_INTR_CLASS_GENRAL + 0x0010)
#define PPC83xx_INTR_GEN_EXT_INT1	(PPC83xx_INTR_CLASS_GENRAL + 0x0011)
#define PPC83xx_INTR_GEN_EXT_INT2	(PPC83xx_INTR_CLASS_GENRAL + 0x0012)
#define PPC83xx_INTR_GEN_EXT_INT3	(PPC83xx_INTR_CLASS_GENRAL + 0x0013)
#define PPC83xx_INTR_GEN_IRQ4		(PPC83xx_INTR_CLASS_GENRAL + 0x0014)
#define PPC83xx_INTR_GEN_IRQ5		(PPC83xx_INTR_CLASS_GENRAL + 0x0015)
#define PPC83xx_INTR_GEN_IRQ6		(PPC83xx_INTR_CLASS_GENRAL + 0x0016)
#define PPC83xx_INTR_GEN_IRQ7		(PPC83xx_INTR_CLASS_GENRAL + 0x0017)
#define PPC83xx_INTR_GEN_TSEC1_Tx	(PPC83xx_INTR_CLASS_GENRAL + 0x0020)
#define PPC83xx_INTR_GEN_TSEC1_Rx	(PPC83xx_INTR_CLASS_GENRAL + 0x0021)
#define PPC83xx_INTR_GEN_TSEC1_Err	(PPC83xx_INTR_CLASS_GENRAL + 0x0022)
#define PPC83xx_INTR_GEN_TSEC2_Tx	(PPC83xx_INTR_CLASS_GENRAL + 0x0023)
#define PPC83xx_INTR_GEN_TSEC2_Rx	(PPC83xx_INTR_CLASS_GENRAL + 0x0024)
#define PPC83xx_INTR_GEN_TSEC2_Err	(PPC83xx_INTR_CLASS_GENRAL + 0x0025)
#define PPC83xx_INTR_GEN_USB_DR		(PPC83xx_INTR_CLASS_GENRAL + 0x0026)
#define PPC83xx_INTR_GEN_USB_MPH	(PPC83xx_INTR_CLASS_GENRAL + 0x0027)
#define PPC83xx_INTR_GEN_EXT_INT0	(PPC83xx_INTR_CLASS_GENRAL + 0x0030)
#define PPC83xx_INTR_GEN_IPI_INTRNL32	(PPC83xx_INTR_CLASS_GENRAL + 0x0040)
#define PPC83xx_INTR_GEN_IPI_INTRNL33	(PPC83xx_INTR_CLASS_GENRAL + 0x0041)
#define PPC83xx_INTR_GEN_IPI_INTRNL34	(PPC83xx_INTR_CLASS_GENRAL + 0x0042)
#define PPC83xx_INTR_GEN_IPI_INTRNL35	(PPC83xx_INTR_CLASS_GENRAL + 0x0043)
#define PPC83xx_INTR_GEN_RTC_ALR	(PPC83xx_INTR_CLASS_GENRAL + 0x0044)
#define PPC83xx_INTR_GEN_MU			(PPC83xx_INTR_CLASS_GENRAL + 0x0045)
#define PPC83xx_INTR_GEN_SBA		(PPC83xx_INTR_CLASS_GENRAL + 0x0046)
#define PPC83xx_INTR_GEN_DMA		(PPC83xx_INTR_CLASS_GENRAL + 0x0047)
#define PPC83xx_INTR_GEN_GTM4		(PPC83xx_INTR_CLASS_GENRAL + 0x0048)
#define PPC83xx_INTR_GEN_GTM8		(PPC83xx_INTR_CLASS_GENRAL + 0x0049)
#define PPC83xx_INTR_GEN_GPIO1		(PPC83xx_INTR_CLASS_GENRAL + 0x004A)
#define PPC83xx_INTR_GEN_GPIO2		(PPC83xx_INTR_CLASS_GENRAL + 0x004B)
#define PPC83xx_INTR_GEN_DDR		(PPC83xx_INTR_CLASS_GENRAL + 0x004C)
#define PPC83xx_INTR_GEN_LBC		(PPC83xx_INTR_CLASS_GENRAL + 0x004D)
#define PPC83xx_INTR_GEN_GTM2		(PPC83xx_INTR_CLASS_GENRAL + 0x004E)
#define PPC83xx_INTR_GEN_GTM6		(PPC83xx_INTR_CLASS_GENRAL + 0x004F)
#define PPC83xx_INTR_GEN_PMC		(PPC83xx_INTR_CLASS_GENRAL + 0x0050)
#define PPC83xx_INTR_GEN_GTM3		(PPC83xx_INTR_CLASS_GENRAL + 0x0054)
#define PPC83xx_INTR_GEN_GTM7		(PPC83xx_INTR_CLASS_GENRAL + 0x0055)
#define PPC83xx_INTR_GEN_GTM1		(PPC83xx_INTR_CLASS_GENRAL + 0x005A)
#define PPC83xx_INTR_GEN_GTM5		(PPC83xx_INTR_CLASS_GENRAL + 0x005B)

#define PPC83xx_INTR_CLASS_GEN_TOTAL	128

#endif

/* __SRCVERSION("83xxintr.h $Rev: 169799 $"); */
