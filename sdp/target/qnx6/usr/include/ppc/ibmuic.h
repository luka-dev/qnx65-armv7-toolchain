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
 * IBM universal interrupt controller interrupt number definitions
 *

 *
 */
#ifndef __PPC_IBMUIC_H_INCLUDED
#define __PPC_IBMUIC_H_INCLUDED

#define PPCIBM_DCR_UIC_SR(b)	((b) + 0)
#define PPCIBM_DCR_UIC_ER(b)	((b) + 2)
#define PPCIBM_DCR_UIC_CR(b)	((b) + 3)
#define PPCIBM_DCR_UIC_PR(b)	((b) + 4)
#define PPCIBM_DCR_UIC_TR(b)	((b) + 5)
#define PPCIBM_DCR_UIC_MSR(b)	((b) + 6)
#define PPCIBM_DCR_UIC_VCR(b)	((b) + 7)
#define PPCIBM_DCR_UIC_VR(b)	((b) + 8)

#endif

/* __SRCVERSION("ibmuic.h $Rev: 169799 $"); */
