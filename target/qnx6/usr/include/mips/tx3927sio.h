/*
 * $QNXLicenseC: 
 * Copyright 2007, 2008, 2009 QNX Software Systems.  
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








#ifndef _TX3927SIO_H_INCLUDED
#define _TX3927SIO_H_INCLUDED

#define TX3927_SIO_NREG        9

#define TX3927_SIRFIFO         8
#define TX3927_SITFIFO         7
#define TX3927_SIBGR           6
#define TX3927_SIFLCR          5
#define TX3927_SIFCR           4
#define TX3927_SISCISR         3
#define TX3927_SIDISR          2
#define TX3927_SIDICR          1
#define TX3927_SILCR           0

#define TX3927_SILCR_SCS_BGIMCLK   0x20
#define TX3927_SILCR_SCS_EXTSCLK   0x40
#define TX3927_SILCR_SCS_BGSCLK    0x60
#define TX3927_SILCR_UMODE8        0x00000000
#define TX3927_SILCR_UMODE7        0x00000001
#define TX3927_SILCR_USBL          0x00000004
#define TX3927_SILCR_UPEN          0x00000008
#define TX3927_SILCR_UEPS          0x00000010

#define TX3927_SIDISR_ERRMASK      0x0000b800
#define TX3927_SIDISR_RFDNMASK     0x0000001f
#define TX3927_SIDISR_STIS         0x00000040
#define TX3927_SIDISR_RDIS         0x00000080
#define TX3927_SIDISR_TDIS         0x00000100
#define TX3927_SIDISR_TOUT         0x00000200
#define TX3927_SIDISR_ERI          0x00000400
#define TX3927_SIDISR_UOER         0x00000800
#define TX3927_SIDISR_UPER         0x00001000
#define TX3927_SIDISR_UFER         0x00002000
#define TX3927_SIDISR_UBRK         0x00008000
#define TX3927_SIDISR_UVALID       0x00004000

#define TX3927_SISCISR_OERS        0x00000020
#define TX3927_SISCISR_CTSS        0x00000010
#define TX3927_SISCISR_RBRKD       0x00000008
#define TX3927_SISCISR_TRDY        0x00000004
#define TX3927_SISCISR_TXALS       0x00000002
#define TX3927_SISCISR_UBRKD       0x00000001

#define TX3927_SIFCR_FRSTE         0x00000001
#define TX3927_SIFCR_RFRST         0x00000002
#define TX3927_SIFCR_TFRST         0x00000004
#define TX3927_SIFCR_TDIL1         0x00000000
#define TX3927_SIFCR_TDIL4         0x00000008
#define TX3927_SIFCR_TDIL8         0x00000010
#define TX3927_SIFCR_RDIL1         0x00000000
#define TX3927_SIFCR_RDIL4         0x00000080
#define TX3927_SIFCR_RDIL8         0x00000100
#define TX3927_SIFCR_RDIL12        0x00000180
#define TX3927_SIFCR_SWRST         0x00008000

#define TX3927_SIFLCR_TBRK         0x00000001
#define TX3927_SIFLCR_TSDE         0x00000080
#define TX3927_SIFLCR_RSDE         0x00000100
#define TX3927_SIFLCR_RTSSC        0x00000200
#define TX3927_SIFLCR_RTSTL(x)     ((x&0xf)<<1)

#define TX3927_SIDICR_TDE          0x00008000
#define TX3927_SIDICR_RDE          0x00004000
#define TX3927_SIDICR_TIE          0x00002000
#define TX3927_SIDICR_RIE          0x00001000
#define TX3927_SIDICR_SPIE         0x00000800
#define TX3927_SIDICR_CTSAC_DISABLE	0x0000000
#define TX3927_SIDICR_CTSAC_RISING	0x0000200
#define TX3927_SIDICR_CTSAC_FALLING	0x0000400
#define TX3927_SIDICR_CTSAC_BOTH	0x0000600
#define TX3927_SIDICR_STIE_OERS    0x00000020
#define TX3927_SIDICR_STIE_CTSS    0x00000010
#define TX3927_SIDICR_STIE_RBRKD   0x00000008
#define TX3927_SIDICR_STIE_TRDY    0x00000004
#define TX3927_SIDICR_STIE_TXALS   0x00000002
#define TX3927_SIDICR_STIE_UBRKD   0x00000001

#define TX3927_SIFCR_RDIL_MASK     0x00000180
#define TX3927_SIFCR_TDIL_MASK     0x00000018

#endif /* _TX3927SIO_H_INCLUDED */

/* __SRCVERSION("tx3927sio.h $Rev: 228008 $"); */
