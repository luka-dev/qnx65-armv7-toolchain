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
 *	PtMenuButton.h
 *		Header file for the PtMenuButton widget class
 *

 */
#ifndef __PT_MENUBUTTON_H_INCLUDED
#define __PT_MENUBUTTON_H_INCLUDED

#include <photon/PtCompound.h>

#include "PtMenuLabel.h"

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtMenuButton public
 */

extern PtWidgetClassRef_t *PtMenuButton;

#define Pt_MENUEBUTTON_ID	7

/* Resources */

/*
 * PtMenuButton private
 */

/* Widget structure */
typedef struct Pt_menu_button_widget {
	PtCompoundWidget_t		compound;
	PtWidget_t				*mlabel;
	PhArea_t				area;
	PgColor_t				hcolor;
} PtMenuButtonWidget_t;

/* Widget union */
typedef union Pt_menu_button_union {
	PtWidget_t				core;
	PtBasicWidget_t			basic;
	PtContainerWidget_t		container;
	PtCompoundWidget_t		compound;
	PtMenuButtonWidget_t	mbutton;
} PtMenuButtonUnion_t;


#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtMenuButton.h $ $Rev: 219996 $" )
#endif
