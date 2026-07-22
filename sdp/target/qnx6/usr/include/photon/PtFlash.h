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
 *	PtFlash.h
 *		Header file for the PtFlash widget class
 *

 */
#ifndef __PT_FLASH_H_INCLUDED
#define __PT_FLASH_H_INCLUDED

#ifndef __PT_CONTAINER_H_INCLUDED
 #include <photon/PtContainer.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtFlash public
 */

extern PtWidgetClassRef_t *PtFlash;

/* Resources */
#define Pt_ARG_FLASH_FILE				Pt_RESOURCE( 14000, 0 )


/*
 * PtFlash private
 */

/* Widget structure */
typedef struct Pt_flash_widget {
	PtContainerWidget_t			container;
	char						*flash_file;
	void						*playerWnd;
} PtFlashWidget_t;

/* Widget union */
typedef union Pt_flash_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtContainerWidget_t			container;
	PtFlashWidget_t				flash;
} PtFlashUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtFlash.h $ $Rev: 219996 $" )
#endif
