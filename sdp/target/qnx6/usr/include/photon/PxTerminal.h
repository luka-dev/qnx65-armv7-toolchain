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
 *	PxTerminal.h
 *		Header file for the PtTerminal extras
 *

 */
#ifndef __PX_TERMINAL_H_INCLUDED
#define __PX_TERMINAL_H_INCLUDED

#ifndef __PT_TERMINAL_H_INCLUDED
	#include <photon/PtTerm.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Px_terminal_cs_names_t {
	char *AnsiCharsetName;
	char *InternalCharsetName;
	char *FontCharsetName;
	int reserved;
	}
		PxTerminalCsNames_t;

#define Px_TERMINAL_UNICODE_FONT	( (char*) -1 )

PtTerminalCharsets_t *PxTerminalBuildCharsets( PxTerminalCsNames_t const *names );

PtTerminalCharsets_t *PxTerminalLoadCharsets(
	const char *filename, PxTerminalCsNames_t *names
	);

int PxTerminalSaveCharsets(
	PtTerminalCharsets_t *charsets,
	PxTerminalCsNames_t *names,
	const char *filename
	);

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif /* __PX_TERMINAL_H_INCLUDED */

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/phexlib/public/photon/PxTerminal.h $ $Rev: 219996 $" )
#endif
