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
 *	PtMenuBar.h
 *		Header file for the PtMenu widget class
 *

 */
#ifndef __PT_MENUBAR_H_INCLUDED
#define __PT_MENUBAR_H_INCLUDED

#ifndef __PT_TOOLBAR_H_INCLUDED
#include <photon/PtToolbar.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtMenu public
 */

extern PtWidgetClassRef_t *PtMenuBar;

 
/* Resources */
#define Pt_ARG_MENUBAR_FLAGS		Pt_RESOURCE( 37, 0 )

/* PtMenuBar Flag */

#define Pt_MENUBAR_MENU_OPEN		0x8000	/* read-only */
#define Pt_MENUBAR_RO_FLAGS			0x8000
/*
 * PtMenuBar private
 */

/* Widget structure */

typedef struct Pt_menubar_widget {
	PtToolbarWidget_t			toolbar;
	ushort_t					flags,padding;
	PtWidget_t					*mbutton;
} PtMenuBarWidget_t;

/* Widget union */
typedef union Pt_menubar_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtContainerWidget_t			container;
	PtToolbarWidget_t			toolbar;
	PtMenuBarWidget_t			menubar;
} PtMenuBarUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtMenuBar.h $ $Rev: 219996 $" )
#endif
