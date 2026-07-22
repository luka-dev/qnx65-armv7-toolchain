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
 * Definitions for the IBM PPC400 series onboard SDRAM controller
 *

 *
 */
#ifndef __PPC_400SDRAM_H_INCLUDED
#define __PPC_400SDRAM_H_INCLUDED
#include <ppc/inline.h>

#define PPC400_DCR_SDRAM0_CFGADDR	0x010
#define PPC400_DCR_SDRAM0_CFGDATA	0x011

#define ppc400_get_sdram0(r)	\
	({set_dcr(PPC400_DCR_SDRAM0_CFGADDR,(r)); get_dcr(PPC400_DCR_SDRAM0_CFGDATA);})
#define ppc400_set_sdram0(r,v)	\
	({set_dcr(PPC400_DCR_SDRAM0_CFGADDR,(r)); set_dcr(PPC400_DCR_SDRAM0_CFGDATA,(v));})

#define PPC400_SDRAM0_BESR0			0x00
#define PPC400_SDRAM0_BESR0_TEST	0x04
#define PPC400_SDRAM0_BESR1			0x08
#define PPC400_SDRAM0_BESR1_TEST	0x0c
#define PPC400_SDRAM0_BEAR			0x10
#define PPC400_SDRAM0_MIRQ			0x11
#define PPC400_SDRAM0_MIRQ_TEST		0x12
#define PPC400_SDRAM0_SLI0			0x18
#define PPC400_SDRAM0_CFG0			0x20
#define PPC400_SDRAM0_CFG1			0x21
#define PPC400_SDRAM0_DEVOPT		0x22
#define PPC400_SDRAM0_MCSTS			0x24
#define PPC400_SDRAM0_RTR			0x30
#define PPC400_SDRAM0_PMIT			0x34
#define PPC400_SDRAM0_UABBA			0x38
#define PPC400_SDRAM0_B0CR			0x40
#define PPC400_SDRAM0_B1CR			0x44
#define PPC400_SDRAM0_B2CR			0x48
#define PPC400_SDRAM0_B3CR			0x4c
#define PPC400_SDRAM0_TR0			0x80
#define PPC400_SDRAM0_TR1			0x81
#define PPC400_SDRAM0_CLKTR			0x82
#define PPC400_SDRAM0_WDDCTR		0x83
#define PPC400_SDRAM0_DLYCAL		0x84
#define PPC400_SDRAM0_ECCESR		0x98
#define PPC400_SDRAM0_CID			0xa4
#define PPC400_SDRAM0_RID			0xa8

#define PPC400_SDRAM0_BxCR_SDBA_MASK	_BITFIELD32B(8, 0x1ff)
#define PPC400_SDRAM0_BxCR_SDBA_SHIFT	(31-8)
#define PPC400_SDRAM0_BxCR_SDSZ_MASK	_BITFIELD32B(14,0x7)
#define PPC400_SDRAM0_BxCR_SDSZ_SHIFT	(31-14)
#define PPC400_SDRAM0_BxCR_SDSZ_RESVD	_BITFIELD32B(14,0x0)
#define PPC400_SDRAM0_BxCR_SDSZ_8M		_BITFIELD32B(14,0x1)
#define PPC400_SDRAM0_BxCR_SDSZ_16M		_BITFIELD32B(14,0x2)
#define PPC400_SDRAM0_BxCR_SDSZ_32M		_BITFIELD32B(14,0x3)
#define PPC400_SDRAM0_BxCR_SDSZ_64M		_BITFIELD32B(14,0x4)
#define PPC400_SDRAM0_BxCR_SDSZ_128M	_BITFIELD32B(14,0x5)
#define PPC400_SDRAM0_BxCR_SDSZ_256M	_BITFIELD32B(14,0x6)
#define PPC400_SDRAM0_BxCR_SDSZ_512M	_BITFIELD32B(14,0x7)
#define PPC400_SDRAM0_BxCR_SDAM_MASK	_BITFIELD32B(18,0x7)
#define PPC400_SDRAM0_BxCR_SDAM_SHIFT	(31-18)
#define PPC400_SDRAM0_BxCR_SDAM_MODE1	_BITFIELD32B(18,0x0)
#define PPC400_SDRAM0_BxCR_SDAM_MODE2	_BITFIELD32B(18,0x1)
#define PPC400_SDRAM0_BxCR_SDAM_MODE3	_BITFIELD32B(18,0x2)
#define PPC400_SDRAM0_BxCR_SDAM_MODE4	_BITFIELD32B(18,0x3)
#define PPC400_SDRAM0_BxCR_SDBE			_ONEBIT32B(31)

#endif

/* __SRCVERSION("400sdram.h $Rev: 169799 $"); */
