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
 *  PtScrollWindow.h
 *      Header file for the PtScrollWindow widget class
 *

 */
#ifndef __PT_SCROLLWINDOW_H_INCLUDED
#define __PT_SCROLLWINDOW_H_INCLUDED

#ifndef __PT_COMPOUND_H_INCLUDED
 #include <photon/PtCompound.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtScrollWindow public
 */

extern PtWidgetClassRef_t *PtScrollWindow;

/* Resources */
/* NONE */

/*
 * PtScrollWindow private
 */

/* Widget structure */
typedef struct Pt_scrollwindow{
	PtCompoundWidget_t	compound;
	PtWidget_t		*window;
	PtWidget_t		*scroll_area;
} PtScrollWindowWidget_t;

/* Widget union */
typedef struct Pt_scrollwindow_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtContainerWidget_t			container;
	PtCompoundWidget_t			compound;
	PtScrollWindowWidget_t		scrollwindow;
} PtScrollWindowUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtScrollWindow.h $ $Rev: 219996 $" )
