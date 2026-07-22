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
 *	PtPanelGroup.h
 *		Header file for the PtPanelGroup widget class
 *

 */
 
#ifndef __PT_PANELGROUP_H_INCLUDED
#define __PT_PANELGROUP_H_INCLUDED

#include <photon/PtContainer.h>
#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


extern PtWidgetClassRef_t *PtPanelGroup;

/* Resources */

#define Pt_ARG_PG_FLAGS						Pt_RESOURCE( 64, 0 )
#define Pt_ARG_PG_CURRENT					Pt_RESOURCE( 64, 1 )
#define Pt_ARG_PG_PANEL_TITLES				Pt_RESOURCE( 64, 2 )
#define Pt_ARG_PG_CONTAINERS				Pt_RESOURCE( 64, 3 )
#define Pt_ARG_PG_SELECTION_MODE			Pt_RESOURCE( 64, 4 )
#define Pt_ARG_PG_CURRENT_INDEX				Pt_RESOURCE( 64, 5 )
#define Pt_ARG_PG_OVERLAP_THRESHOLD			Pt_RESOURCE( 64, 6 )
#define Pt_ARG_PG_DEFAULT_TAB_COLOR			Pt_RESOURCE( 64, 7 )
#define Pt_CB_PG_PANEL_SWITCHING			Pt_RESOURCE( 64, 10 )

/* PtPanelGroup Flag Manifests */

#define Pt_PG_SELECTOR_ON_BOTTOM		0x0001
#define Pt_PG_SELECTOR_ALIGN_RIGHT		0x0002
#define Pt_PG_DND						0x0004
#define Pt_PG_TABS_EQUAL_SIZE			0x0008
#define Pt_PG_CLOSABLE					0x0010
#define Pt_PG_USE_PANEL_COLORS			0x0020

#define Pt_PG_PANEL_CLOSING				0x1000
#define Pt_PG_MENU_OPEN					0x2000
#define Pt_PG_MULTI_CONTAINER_MODE		0x4000
#define Pt_PG_IN_POPUP					0x8000
#define Pt_PG_RO_FLAGS					0xf000

/* PtPanelGroup selection modes */

#define Pt_PG_NONE			0	/* Provide no selection mechanism (done by code) */
#define Pt_PG_TABBED		1	/* Use tabs to select panels (internal use only) */
#define Pt_PG_SINGLE_TAB	2	/* Force use of a popup menu to select panel */
#define Pt_PG_AUTO			3	/* Switch between modes as size dictates */

#define Pt_PG_INVALID		Pt_MAX_SURFACE_ID

/* Widget structure */

typedef struct pt_panelgroup_widget
{
	PtContainerWidget_t container;	/* Superclass */

	uint16_t flags;					/* PtPanelGroup-specific flags */
	uint8_t selection_mode;
	uint8_t max_compress;			/* Maximum compression of tabs */

	uint16_t panel_count;			/* Total number of panels contained by this widget */
	uint16_t current;				/* Currently selected panel (0 -> n - 1, 255 if none) */
	
	char *tab_font;					/* Font to display in tabs */
	char **titles;					/* Titles of associated panels */

	PtSurfaceId_t *tabs;			/* index of surface id's for tabs */

	/* Following used in multi-container mode only, pointer to child
	   panels followed by their focused children (ie panel_count panel
	   pointers immediately followed by panel_count widget pointers */

	PtWidget_t **containers;

	PgColor_t tab_color;

	uint16_t current_wannabe;		/* Wants to be current, but can't (yet) */
	uint8_t cur_sel_mode;			/* Indicates actual selection mode in use */
	uint8_t padding;
		
	PhRect_t margins;				/* Container margins */

	PtWidget_t *display;			/* Procreated container to display current panel */

} PtPanelGroupWidget_t;


/* Widget union */

typedef union pt_panelgroup_union
{
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtContainerWidget_t			container;
	PtPanelGroupWidget_t		panelgroup;

} PtPanelGroupUnion_t;


/* Callback structure */

typedef struct panelgroup_callback
{
	char *old_panel,*new_panel;
	uint16_t old_panel_index,new_panel_index;
	
} PtPanelGroupCallback_t;


/* PtPanelGroup convenience functions */

extern PtWidget_t *PtPGFindPanelByTitle( PtWidget_t *, char const * );
extern char *PtPGFindTitleByIndex( PtWidget_t *, int );
extern int PtPGFindIndexByTitle( PtWidget_t *, char const * );
extern int PtPGFindIndexByPanel( PtWidget_t *, PtWidget_t * );
extern PtWidget_t *PtPGFindPanelByIndex( PtWidget_t *, int );
extern PtWidget_t *PtPGCreatePopup( PtWidget_t *, PhPoint_t const * );

#ifdef __CYGWIN__
/* Resources pane tracking globals */
extern int PtPGResourcesPaneCovered;
extern void (*PtPGResourcesUncoveredCallback)( int force );
extern int PtPGResourcesNumSkipped;
#endif

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtPanelGroup.h $ $Rev: 219996 $" )
#endif
