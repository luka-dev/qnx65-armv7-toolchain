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




#ifndef	_SH_HAC_H_INCLUDED_
#define	_SH_HAC_H_INCLUDED_

#define	SH_HAC_SIZE			0x80

#define	SH_HAC_CR			0x08
#define	SH_HAC_CSAR			0x20
#define	SH_HAC_CSDR			0x24
#define	SH_HAC_PCML			0x28
#define	SH_HAC_PCMR			0x2C
#define	SH_HAC_TIER			0x50
#define	SH_HAC_TSR			0x54
#define	SH_HAC_RIER			0x58
#define	SH_HAC_RSR			0x5C
#define	SH_HAC_ACR			0x60

/*
 * Control and Status Register (CR) bit defination
 */
#define	HAC_CR_CR				(1 << 15)	/* Codec ready */
#define	HAC_CR_CDRT				(1 << 11)	/* HAC Cold Reset */
#define	HAC_CR_WMRT				(1 << 10)	/* HAC Warm Reset */
#define	HAC_CR_DEFAULT			(1 <<  9)	/* Always 1 */
#define	HAC_CR_ST				(1 <<  5)	/* Start Transfer */

/*
 * Command/Status Address Register (CSAR) bit defination
 */
#define	HAC_CSAR_RW				(1 << 19)	/* Codec ready */
#define	HAC_CSAR_CASA_SHIFT		12
#define	HAC_CSAR_CASA_MASK		0x7F
#define	HAC_CSAR_SLREQ_SHIFT	2
#define	HAC_CSAR_SLREQ_MASK		0x1FF

/*
 * Command/Status Data Register (CSDR) bit defination
 */
#define	HAC_CSDR_CDSD_SHIFT		4
#define	HAC_CSDR_CDSD_MASK		0xFFFF

/*
 * TX Interrupt Enable Register (TIER) bit defination
 */
#define	HAC_TIER_PLTFRQIE		(1 << 29)	/* PCML TX Request Interrupt Enable */
#define	HAC_TIER_PRTFRQIE		(1 << 28)	/* PCMR TX Request Interrupt Enable */
#define	HAC_TIER_PLTFUNIE		(1 <<  9)	/* PCML TX Underrun Interrupt Enable */
#define	HAC_TIER_PRTFUNIE		(1 <<  8)	/* PCMR TX Underrun Interrupt Enable */

/*
 * TX Status Register (TSR) bit defination
 */
#define	HAC_TSR_CMDAMT			(1 << 31)	/* Command Address Empty */
#define	HAC_TSR_CMDDMT			(1 << 30)	/* Command Data Empty */
#define	HAC_TSR_PLTFRQ			(1 << 29)	/* PCML TX Request */
#define	HAC_TSR_PRTFRQ			(1 << 28)	/* PCMR TX Request */
#define	HAC_TSR_PLTFUN			(1 <<  9)	/* PCML TX Underrun */
#define	HAC_TSR_PRTFUN			(1 <<  8)	/* PCMR TX Underrun */

/*
 * RX Interrupt Enable Register (RIER) bit defination
 */
#define	HAC_RIERR_STARYIE		(1 << 22)	/* Status Address Ready Interrupt Enable */
#define	HAC_RIERR_STDRYIE		(1 << 21)	/* Status Data Ready Interrupt Enable */
#define	HAC_RIERR_PLRFRQIE		(1 << 20)	/* PCML Rx Request Interrupt Enable */
#define	HAC_RIERR_PRRFRQIE		(1 << 19)	/* PCMR Rx Request Interrupt Enable */
#define	HAC_RIERR_PLRFOVIE		(1 << 13)	/* PCML Rx Overrun Interrupt Enable */
#define	HAC_RIERR_PRRFOVIE		(1 << 12)	/* PCMR Rx Overrun Interrupt Enable */

/*
 * RX Status Register (RSR) bit defination
 */
#define	HAC_RSR_STARY			(1 << 22)	/* Status Address Ready */
#define	HAC_RSR_STDRY			(1 << 21)	/* Status Data Ready */
#define	HAC_RSR_PLRFRQ			(1 << 20)	/* PCML RX Request */
#define	HAC_RSR_PRRFRQ			(1 << 19)	/* PCMR RX Request */
#define	HAC_RSR_PLRFOV			(1 << 13)	/* PCML RX Overrun */
#define	HAC_RSR_PRRFOV			(1 << 12)	/* PCMR RX Overrun */

/*
 * HAC Control Register (ACR) bit defination
 */
#define	HAC_ACR_DMARX16			(1 << 30)	/* 16-bit RX DMA Enable */
#define	HAC_ACR_DMATX16			(1 << 29)	/* 16-bit TX DMA Enable */
#define	HAC_ACR_TX12_ATOMIC		(1 << 26)	/* TX Slot 1 and 2 Atomic Control */
#define	HAC_ACR_RXDMAL_EN		(1 << 24)	/* RX DMA Left Enable */
#define	HAC_ACR_TXDMAL_EN		(1 << 23)	/* TX DMA Left Enable */
#define	HAC_ACR_RXDMAR_EN		(1 << 22)	/* RX DMA Right Enable */
#define	HAC_ACR_TXDMAR_EN		(1 << 21)	/* TX DMA Right Enable */

#endif	/* _SH_HAC_H_INCLUDED_ */
