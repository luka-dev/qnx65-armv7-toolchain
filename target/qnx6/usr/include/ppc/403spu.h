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
 *  ppc/spu403.h
 *
 *  Serial Port Unit registers on the 403 chip
 *
 */

#ifndef __PPC_SPU403_H_INCLUDED
#define __PPC_SPU403_H_INCLUDED

#include <sys/platform.h>

/*
    Memory mapped addresses where SPU registers show up
*/
#define PPC403_SPUBASE	0x40000000

/* offsets from the base address */
#define PPC403_SPLS		0x0
#define PPC403_SPHS		0x2
#define PPC403_BRDH		0x4
#define PPC403_BRDL		0x5
#define PPC403_SPCTL	0x6
#define PPC403_SPRC		0x7
#define	PPC403_SPTC		0x8
#define PPC403_SPRB		0x9
#define PPC403_SPTB		0x9

/*
 * Serial Port Control Register
 */
#define PPC403_SPCTL_LM_MASK		_BITFIELD8B( 1, 3 )
#define PPC403_SPCTL_LM_NORMAL		_BITFIELD8B( 1, 0 )
#define PPC403_SPCTL_LM_INTERNAL	_BITFIELD8B( 1, 1 )
#define PPC403_SPCTL_LM_AUTOECHO	_BITFIELD8B( 1, 2 )
#define PPC403_SPCTL_DTR			_ONEBIT8B( 2 )
#define PPC403_SPCTL_RTS			_ONEBIT8B( 3 )
#define PPC403_SPCTL_DB				_ONEBIT8B( 4 )
#define PPC403_SPCTL_PE				_ONEBIT8B( 5 )
#define PPC403_SPCTL_PTY			_ONEBIT8B( 6 )
#define PPC403_SPCTL_SB				_ONEBIT8B( 7 )

/*
 * Serial Port Handshake Register
 */
#define PPC403_SPHS_DIS	_ONEBIT8B( 0 )
#define PPC403_SPHS_CS	_ONEBIT8B( 1 )

/*
 * Serial Port Line Status Register
 */
#define PPC403_SPLS_RBR	_ONEBIT8B( 0 )
#define PPC403_SPLS_FE	_ONEBIT8B( 1 )
#define PPC403_SPLS_OE	_ONEBIT8B( 2 )
#define PPC403_SPLS_PE	_ONEBIT8B( 3 )
#define PPC403_SPLS_LB	_ONEBIT8B( 4 )
#define PPC403_SPLS_TBR	_ONEBIT8B( 5 )
#define PPC403_SPLS_TSR	_ONEBIT8B( 6 )

/*
 * Serial Port Receiver Command Register
 */
#define PPC403_SPRC_ER				_ONEBIT8B( 0 )
#define PPC403_SPRC_DME_MASK		_BITFIELD8B( 2, 3 )
#define PPC403_SPRC_DME_NODMA_NORBR	_BITFIELD8B( 2, 0 )
#define PPC403_SPRC_DME_NODMA_RBR	_BITFIELD8B( 2, 1 )
#define PPC403_SPRC_DME_DMA2		_BITFIELD8B( 2, 2 )
#define PPC403_SPRC_DME_DMA3		_BITFIELD8B( 2, 3 )
#define PPC403_SPRC_EIE				_ONEBIT8B( 3 )

/*
 * Serial Port Transmitter Command Register
 */
#define PPC403_SPTC_ET				_ONEBIT8B( 0 )
#define PPC403_SPTC_DME_MASK		_BITFIELD8B( 2, 3 )
#define PPC403_SPTC_DME_NODMA_NOTBR	_BITFIELD8B( 2, 0 )
#define PPC403_SPTC_DME_NODMA_TBR	_BITFIELD8B( 2, 1 )
#define PPC403_SPTC_DME_DMA2		_BITFIELD8B( 2, 2 )
#define PPC403_SPTC_DME_DMA3		_BITFIELD8B( 2, 3 )
#define PPC403_SPTC_TIE				_ONEBIT8B( 3 )
#define PPC403_SPTC_EIE				_ONEBIT8B( 4 )
#define PPC403_SPTC_SPE				_ONEBIT8B( 5 )
#define PPC403_SPTC_TB				_ONEBIT8B( 6 )
#define PPC403_SPTC_PGM				_ONEBIT8B( 7 )

#endif


__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/hardware/devc/public/ppc/403spu.h $ $Rev: 219612 $" )
