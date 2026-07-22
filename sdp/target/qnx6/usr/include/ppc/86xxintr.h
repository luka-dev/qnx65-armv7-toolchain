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

#ifndef __PPC_86XXINTR_H_INCLUDED
#define __PPC_86XXINTR_H_INCLUDED

#include <ppc/intr.h>

#define PPC_INTR_CLASS_86xx			_NTO_INTR_CLASS_EXTERNAL

#define PPC86xx_INTR_MCM			(PPC_INTR_CLASS_86xx + 1)
#define PPC86xx_INTR_DDR_DRAM		(PPC_INTR_CLASS_86xx + 2)
#define PPC86xx_INTR_LBC			(PPC_INTR_CLASS_86xx + 3)
#define PPC86xx_INTR_DMA0			(PPC_INTR_CLASS_86xx + 4)
#define PPC86xx_INTR_DMA1			(PPC_INTR_CLASS_86xx + 5)
#define PPC86xx_INTR_DMA2			(PPC_INTR_CLASS_86xx + 6)
#define PPC86xx_INTR_DMA3			(PPC_INTR_CLASS_86xx + 7)
#define PPC86xx_INTR_PCIEX_1		(PPC_INTR_CLASS_86xx + 8)
#define PPC86xx_INTR_PCIEX_2		(PPC_INTR_CLASS_86xx + 9)
#define PPC86xx_INTR_DUART2			(PPC_INTR_CLASS_86xx +12)
#define PPC86xx_INTR_TSEC1_TX		(PPC_INTR_CLASS_86xx +13)
#define PPC86xx_INTR_TSEC1_RX		(PPC_INTR_CLASS_86xx +14)
#define PPC86xx_INTR_TSEC3_TX		(PPC_INTR_CLASS_86xx +15)
#define PPC86xx_INTR_TSEC3_RX		(PPC_INTR_CLASS_86xx +16)
#define PPC86xx_INTR_TSEC3_ERROR	(PPC_INTR_CLASS_86xx +17)
#define PPC86xx_INTR_TSEC1_ERROR	(PPC_INTR_CLASS_86xx +18)
#define PPC86xx_INTR_TSEC2_TX		(PPC_INTR_CLASS_86xx +19)
#define PPC86xx_INTR_TSEC2_RX		(PPC_INTR_CLASS_86xx +20)
#define PPC86xx_INTR_TSEC4_TX		(PPC_INTR_CLASS_86xx +21)
#define PPC86xx_INTR_TSEC4_RX		(PPC_INTR_CLASS_86xx +22)
#define PPC86xx_INTR_TSEC4_ERROR	(PPC_INTR_CLASS_86xx +23)
#define PPC86xx_INTR_TSEC2_ERROR	(PPC_INTR_CLASS_86xx +24)
#define PPC86xx_INTR_DUART1			(PPC_INTR_CLASS_86xx +26)
#define PPC86xx_INTR_I2C			(PPC_INTR_CLASS_86xx +27)
#define PPC86xx_INTR_PMI			(PPC_INTR_CLASS_86xx +28)
#define PPC86xx_INTR_SRIO_ERR		(PPC_INTR_CLASS_86xx +32)
#define PPC86xx_INTR_SRIO_OUT_DB	(PPC_INTR_CLASS_86xx +33)
#define PPC86xx_INTR_SRIO_IN_DB		(PPC_INTR_CLASS_86xx +34)
#define PPC86xx_INTR_SRIO_OUT1		(PPC_INTR_CLASS_86xx +37)
#define PPC86xx_INTR_SRIO_IN1		(PPC_INTR_CLASS_86xx +38)
#define PPC86xx_INTR_SRIO_OUT2		(PPC_INTR_CLASS_86xx +39)
#define PPC86xx_INTR_SRIO_IN2		(PPC_INTR_CLASS_86xx +40)

#define PPC86xx_INTR_IRQ0			(PPC_INTR_CLASS_86xx +48)
#define PPC86xx_INTR_IRQ1			(PPC_INTR_CLASS_86xx +49)
#define PPC86xx_INTR_IRQ2			(PPC_INTR_CLASS_86xx +50)
#define PPC86xx_INTR_IRQ3			(PPC_INTR_CLASS_86xx +51)
#define PPC86xx_INTR_IRQ4			(PPC_INTR_CLASS_86xx +52)
#define PPC86xx_INTR_IRQ5			(PPC_INTR_CLASS_86xx +53)
#define PPC86xx_INTR_IRQ6			(PPC_INTR_CLASS_86xx +54)
#define PPC86xx_INTR_IRQ7			(PPC_INTR_CLASS_86xx +55)
#define PPC86xx_INTR_IRQ8			(PPC_INTR_CLASS_86xx +56)
#define PPC86xx_INTR_IRQ9			(PPC_INTR_CLASS_86xx +57)
#define PPC86xx_INTR_IRQ10			(PPC_INTR_CLASS_86xx +58)
#define PPC86xx_INTR_IRQ11			(PPC_INTR_CLASS_86xx +59)

#define PPC86xx_INTR_IPI0			(PPC_INTR_CLASS_86xx +60)
#define PPC86xx_INTR_IPI1			(PPC_INTR_CLASS_86xx +61)
#define PPC86xx_INTR_IPI2			(PPC_INTR_CLASS_86xx +62)
#define PPC86xx_INTR_IPI3			(PPC_INTR_CLASS_86xx +63)

#define PPC86xx_INTR_GTA0			(PPC_INTR_CLASS_86xx +64)
#define PPC86xx_INTR_GTA1			(PPC_INTR_CLASS_86xx +65)
#define PPC86xx_INTR_GTA2			(PPC_INTR_CLASS_86xx +66)
#define PPC86xx_INTR_GTA3			(PPC_INTR_CLASS_86xx +67)

#define PPC86xx_INTR_GTB0			(PPC_INTR_CLASS_86xx +68)
#define PPC86xx_INTR_GTB1			(PPC_INTR_CLASS_86xx +69)
#define PPC86xx_INTR_GTB2			(PPC_INTR_CLASS_86xx +70)
#define PPC86xx_INTR_GTB3			(PPC_INTR_CLASS_86xx +71)

#define PPC86xx_INTR_MSG0			(PPC_INTR_CLASS_86xx +72)
#define PPC86xx_INTR_MSG1			(PPC_INTR_CLASS_86xx +73)
#define PPC86xx_INTR_MSG2			(PPC_INTR_CLASS_86xx +74)
#define PPC86xx_INTR_MSG3			(PPC_INTR_CLASS_86xx +75)

#define PPC86xx_INTR_MSG_SHARED0	(PPC_INTR_CLASS_86xx +76)
#define PPC86xx_INTR_MSG_SHARED1	(PPC_INTR_CLASS_86xx +77)
#define PPC86xx_INTR_MSG_SHARED2	(PPC_INTR_CLASS_86xx +78)
#define PPC86xx_INTR_MSG_SHARED3	(PPC_INTR_CLASS_86xx +79)
#define PPC86xx_INTR_MSG_SHARED4	(PPC_INTR_CLASS_86xx +80)
#define PPC86xx_INTR_MSG_SHARED5	(PPC_INTR_CLASS_86xx +81)
#define PPC86xx_INTR_MSG_SHARED6	(PPC_INTR_CLASS_86xx +82)
#define PPC86xx_INTR_MSG_SHARED7	(PPC_INTR_CLASS_86xx +83)

#endif
/* __SRCVERSION("86xxintr.h $Rev: 169799 $"); */
