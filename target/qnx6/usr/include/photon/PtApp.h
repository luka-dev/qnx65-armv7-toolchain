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
 *	PtApp.h
 *		Header file for the PtApp resources
 *

 */
#ifndef __PT_APP_H_INCLUDED
#define __PT_APP_H_INCLUDED

#ifndef __PT_T_H_INCLUDED
#include <photon/PtT.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtApp public 
 */

/* Resources */
#define Pt_CB_APP_EXIT					Pt_RESOURCE( 0, 0 )
#define Pt_CB_APP_WCLASS_CREATED			Pt_RESOURCE( 0, 1 )

/* Callback structure */
typedef struct Pt_app_wclass_callback_t {
	PtWidgetClass_t *wclass;	
} PtAppWClassCallback_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtApp.h $ $Rev: 219996 $" )
#endif
