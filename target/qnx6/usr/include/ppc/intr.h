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
 * PPC interrupt number definitions
 *

 *
 */
#ifndef __PPC_INTR_H_INCLUDED
#define __PPC_INTR_H_INCLUDED

#include <sys/neutrino.h>

/* Timer class */
#define PPC_INTR_CLASS_TIMER		(0x8000UL<<16)
#define PPC_INTR_DECREMENTER		(PPC_INTR_CLASS_TIMER + 0)
#define PPC_INTR_FIT				(PPC_INTR_CLASS_TIMER + 1) /* book E */
#define PPC_INTR_WATCHDOG			(PPC_INTR_CLASS_TIMER + 2) /* book E */

/* For backwards compatability */
#define PPC_INTR_CLASS_DEC			PPC_INTR_CLASS_TIMER

/* Performance management class */
#define PPC_INTR_CLASS_PMI		(PPC_INTR_CLASS_DEC + 0x1000)

#endif

/* __SRCVERSION("intr.h $Rev: 169799 $"); */
