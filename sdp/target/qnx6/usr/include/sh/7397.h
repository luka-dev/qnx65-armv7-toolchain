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
 * SH 7397 internal register offsets
 *

 *
 */
#ifndef _SH_7397_H_INCLUDED
#define _SH_7397_H_INCLUDED

/*
 * INTC registers
 */
#define	SH7397_ICR0			0xFFD00000
#define	SH7397_ICR1			0xFFD0001C
#define	SH7397_INTPRI		0xFFD00010
#define	SH7397_INTREQ		0xFFD00024
#define	SH7397_INTMSK0		0xFFD00044
#define	SH7397_INTMSK1		0xFFD00048
#define	SH7397_INTMSK2		0xFFD40080
#define	SH7397_INTMSKCLR0	0xFFD00064
#define	SH7397_INTMSKCLR1	0xFFD00068
#define	SH7397_INTMSKCLR2	0xFFD40084
#define	SH7397_NMIFCR		0xFFD000C0
#define	SH7397_USERIMASK	0xFFD30000

#define	SH7397_INT2PRI0		0xFFD40000
#define	SH7397_INT2PRI1		0xFFD40004
#define	SH7397_INT2PRI2		0xFFD40008
#define	SH7397_INT2PRI3		0xFFD4000C
#define	SH7397_INT2PRI4		0xFFD40010
#define	SH7397_INT2PRI6		0xFFD40018
#define	SH7397_INT2PRI7		0xFFD4001C
#define	SH7397_INT2PRI8		0xFFD400A0
#define	SH7397_INT2PRI9		0xFFD400A4
#define	SH7397_INT2PRI10	0xFFD400A8
#define	SH7397_INT2PRI11	0xFFD400AC
#define	SH7397_INT2PRI12	0xFFD400B0
#define	SH7397_INT2A0		0xFFD40030
#define	SH7397_INT2A01		0xFFD400C0
#define	SH7397_INT2A1		0xFFD40034
#define	SH7397_INT2A11		0xFFD400C4
#define	SH7397_INT2MSKR		0xFFD40038
#define	SH7397_INT2MSKR1	0xFFD400D0
#define	SH7397_INT2MSKCR	0xFFD4003C
#define	SH7397_INT2MSKCR1	0xFFD400D4

#define	SH7397_INT2B0		0xFFD40040
#define	SH7397_INT2B1		0xFFD40044
#define	SH7397_INT2B2		0xFFD40048
#define	SH7397_INT2B3		0xFFD4004C
#define	SH7397_INT2B5		0xFFD40054
#define	SH7397_INT2B6		0xFFD40058
#define	SH7397_INT2B7		0xFFD4005C
#define	SH7397_INT2B9		0xFFD40064
#define	SH7397_INT2B10		0xFFD40068
#define	SH7397_INT2B11		0xFFD4006C
#define	SH7397_INT2B12		0xFFD40094
#define	SH7397_INT2GPIC		0xFFD40090


/*
 * SCIF 0, 1, 2
 */
#define	SH7397_SCIF0_BASE	0xFFE00000
#define	SH7397_SCIF1_BASE	0xFFE08000
#define	SH7397_SCIF2_BASE	0xFFE10000

/*
 * DMAC
 */
#define	SH7397_DMAC_BASE	0xFF608000

#define	SH7397_DMAC_SAR0	0x0020
#define	SH7397_DMAC_DAR0	0x0024
#define	SH7397_DMAC_TCR0	0x0028
#define	SH7397_DMAC_CHCR0	0x002C

#define	SH7397_DMAC_SAR1	0x0030
#define	SH7397_DMAC_DAR1	0x0034
#define	SH7397_DMAC_TCR1	0x0038
#define	SH7397_DMAC_CHCR1	0x003C

#define	SH7397_DMAC_SAR2	0x0040
#define	SH7397_DMAC_DAR2	0x0044
#define	SH7397_DMAC_TCR2	0x0048
#define	SH7397_DMAC_CHCR2	0x004C

#define	SH7397_DMAC_SAR3	0x0050
#define	SH7397_DMAC_DAR3	0x0054
#define	SH7397_DMAC_TCR3	0x0058
#define	SH7397_DMAC_CHCR3	0x005C

#define	SH7397_DMAC_DMAOR	0x0060

#define	SH7397_DMAC_SAR4	0x0070
#define	SH7397_DMAC_DAR4	0x0074
#define	SH7397_DMAC_TCR4	0x0078
#define	SH7397_DMAC_CHCR4	0x007C

#define	SH7397_DMAC_SAR5	0x0080
#define	SH7397_DMAC_DAR5	0x0084
#define	SH7397_DMAC_TCR5	0x0088
#define	SH7397_DMAC_CHCR5	0x008C

#define	SH7397_DMAC_SARB0	0x0120
#define	SH7397_DMAC_DARB0	0x0124
#define	SH7397_DMAC_TCRB0	0x0128

#define	SH7397_DMAC_SARB1	0x0130
#define	SH7397_DMAC_DARB1	0x0134
#define	SH7397_DMAC_TCRB1	0x0138

#define	SH7397_DMAC_SARB2	0x0140
#define	SH7397_DMAC_DARB2	0x0144
#define	SH7397_DMAC_TCRB2	0x0148

#define	SH7397_DMAC_SARB3	0x0150
#define	SH7397_DMAC_DARB3	0x0154
#define	SH7397_DMAC_TCRB3	0x0158

#define	SH7397_DMAC_DMARS0	0x1000
#define	SH7397_DMAC_DMARS1	0x1004
#define	SH7397_DMAC_DMARS2	0x1008

/*
 * USB Host
 */
#define	SH7397_USBH_BASE	0xFFEC8000
#define SH7397_USBHSC		0xF0

/*
 * GPIO
 */
#define	SH7397_GPIO_BASE	0xFFEF0000
#define	SH7397_PACR			0x00
#define	SH7397_PBCR			0x02
#define	SH7397_PCCR			0x04
#define	SH7397_PDCR			0x06
#define	SH7397_PECR			0x08
#define	SH7397_PFCR			0x0A
#define	SH7397_PGCR			0x0C
#define	SH7397_PHCR			0x0E
#define	SH7397_PICR			0x10
#define	SH7397_PJCR			0x12
#define	SH7397_PKCR			0x14
#define	SH7397_PLCR			0x16
#define	SH7397_PMCR			0x18
#define	SH7397_PNCR			0x1A
#define	SH7397_POCR			0x1C
#define	SH7397_PADR			0x20
#define	SH7397_PBDR			0x22
#define	SH7397_PCDR			0x24
#define	SH7397_PDDR			0x26
#define	SH7397_PEDR			0x28
#define	SH7397_PFDR			0x2A
#define	SH7397_PGDR			0x2C
#define	SH7397_PHDR			0x2E
#define	SH7397_PIDR			0x30
#define	SH7397_PJDR			0x32
#define	SH7397_PKDR			0x34
#define	SH7397_PLDR			0x36
#define	SH7397_PMDR			0x38
#define	SH7397_PNDR			0x3A
#define	SH7397_PODR			0x3C
#define	SH7397_PIPUPR		0x50
#define	SH7397_PJPUPR		0x52
#define	SH7397_PKPUPR		0x54
#define	SH7397_PLPUPR		0x56
#define	SH7397_PMPUPR		0x58
#define	SH7397_PNPUPR		0x5A
#define	SH7397_POPUPR		0x5C
#define	SH7397_PPUPR		0x60
#define	SH7397_PSEL0		0x70
#define	SH7397_PSEL1		0x72
#define	SH7397_PSEL2		0x74
#define	SH7397_PSEL3		0x76
#define	SH7397_PSEL4		0x78


/*
 * Audio Codec (HAC)
 */
#define	SH7397_HAC_BASE		0xFFEB0000


/*
 * LCD Controller (LCDC)
 */
#define	SH7397_LCDC_BASE	0xFFE80000



#endif /* _SH_7397_H_INCLUDED */

/* __SRCVERSION("7397.h $Rev: 169800 $"); */
