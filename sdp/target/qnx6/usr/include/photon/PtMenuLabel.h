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
 *	PtMenuLabel.h
 *		Header file for the PtMenuLabel widget class
 *

 */
#ifndef __PT_MENULABEL_H_INCLUDED
#define __PT_MENULABEL_H_INCLUDED

#include <photon/PtLabel.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtMenuLabel public
 */

extern PtWidgetClassRef_t *PtMenuLabel;

/* Resources */
#define	Pt_ARG_ACCEL_TEXT		Pt_RESOURCE( 7, 0 )
#define	Pt_ARG_ACCEL_FONT		Pt_RESOURCE( 7, 1 )
#define	Pt_ARG_BUTTON_TYPE		Pt_RESOURCE( 7, 2 )
#define Pt_ARG_OFFSET			Pt_RESOURCE( 7, 3 )
#define Pt_ARG_MODIFIER_KEYS	Pt_RESOURCE( 7, 4 )


/* Button types */
#define Pt_MENU_TEXT		0x01
#define Pt_MENU_RIGHT		0x02
#define Pt_MENU_DOWN		0x04
#define Pt_MENU_UP			0x08
#define	Pt_MENU_DIRECTION_FLAGS	( Pt_MENU_RIGHT | Pt_MENU_DOWN | Pt_MENU_UP )
#define Pt_MENU_ACCL_CTRL	0x10
#define Pt_MENU_ACCL_ALT	0x20
#define Pt_MENU_ACCL_SHFT	0x40

/* Default menu label margins */
#define	Pt_MENU_LABEL_MARGIN_RIGHT	4
#define	Pt_MENU_LABEL_MARGIN_LEFT	4

/*
 * PtMenuLabel private
 */

/* Widget structure */
typedef struct Pt_menu_label_widget {
	PtLabelWidget_t			label;
	char					*text;			/* the shortcut text */
	const char				*font;			/* the shortcut and modifier font */
	ushort_t				button_type;
	short					image_offset;	/* used to align label images */
	short					max_text_width; /* set up by PtMenu or menulabel_init() */
	PhDim_t					text_dim;		/* the (beveled) dimensions of shortcut text */
	ulong_t					flags;			/* the modifier keys for the shortcuts */
											/* from <photon/PkKeydef.h> */
	char					reserved[2];
} PtMenuLabelWidget_t;

/* Widget union */
typedef union Pt_menu_label_union {
	PtWidget_t				core;
	PtBasicWidget_t			basic;
	PtLabelWidget_t			label;
	PtMenuLabelWidget_t		mlabel;
} PtMenuLabelUnion_t;


#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtMenuLabel.h $ $Rev: 219996 $" )
#endif
