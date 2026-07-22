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
 *	PtColorPanel.h
 *		Header file for the PtColorPanel class
 *

 */
 
#ifndef __PT_COLORPANEL_H_INCLUDED
#define __PT_COLORPANEL_H_INCLUDED

#include <photon/PtColorSel.h>
#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

extern PtWidgetClassRef_t *PtColorPanel;

/* Resources */

#define Pt_ARG_CPANEL_FLAGS			Pt_RESOURCE( 155, 0 )
#define Pt_ARG_CPANEL_HISTORY		Pt_RESOURCE( 155, 1 )
#define Pt_ARG_CPANEL_ENTRY_MODE	Pt_RESOURCE( 155, 2 )

/* Pt_ARG_CPANEL_FLAGS manifests */

#define Pt_CPANEL_SHOW_FIELDS		0x1		/* Display numeric entry fields */
#define Pt_CPANEL_SHOW_WELL			0x2		/* Display color well */
#define Pt_CPANEL_SHOW_DROPPER		0x4		/* Display dropper button */

#define Pt_CPANEL_RO_FLAGS			0

/* Pt_ARG_CPANEL_ENTRY_MODE manifests */

#define Pt_CPANEL_DECIMAL		Pg_CC_DECIMAL	/* decimal entry */
#define Pt_CPANEL_HEX			Pg_CC_HEX		/* hex entry */
#define Pt_CPANEL_PERCENTAGE	Pg_CC_PERCENT	/* percentage entry (0 - 100%) */

enum
{
	Pt_CPANEL_HISTORY_SELECT_ACTION = 0
};

/* Widget structure */

typedef struct pt_colorpanel_widget
{
	PtColorSelWidget_t colorsel;

	uint16_t flags;
	uint8_t nhistory;								/* # colors to maintain in history */
	uint8_t entry_mode;								/* numeric entry mode */

	PtWidget_t *numeric[Pg_CM_MAX_CHANNELS];		/* Numeric entry fields */
	PtWidget_t *label[Pg_CM_MAX_CHANNELS];			/* Numeric entry labels */
	PtWidget_t *well;								/* Color well */
	PtWidget_t *dropper;							/* Button to activate dropper mode */

} PtColorPanelWidget_t;


/* Widget union */

typedef union pt_colorpanel_union
{
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtContainerWidget_t			container;
	PtCompoundWidget_t			compound;
	PtColorSelWidget_t			colorsel;
	PtColorPanelWidget_t		colorpanel;

} PtColorPanelUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtColorPanel.h $ $Rev: 219996 $" )
#endif
