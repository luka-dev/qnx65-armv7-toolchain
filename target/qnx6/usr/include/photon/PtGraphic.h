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
 *	PtGraphic.h
 *		Header file for the PtGraphic widget class
 *

 */
#ifndef __PT_GRAPHIC_H_INCLUDED
#define __PT_GRAPHIC_H_INCLUDED

#ifndef __PT_BASIC_H_INCLUDED
 #include <photon/PtBasic.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtGraphic public
 */

extern PtWidgetClassRef_t *PtGraphic;

#define Pt_GRAPHIC_ID		25

/* Resources */
#define Pt_ARG_DASH_LIST				Pt_RESOURCE( 25, 0 )
#define Pt_ARG_GRAPHIC_FLAGS			Pt_RESOURCE( 25, 1 )
#define Pt_ARG_LINE_WIDTH				Pt_RESOURCE( 25, 2 )
#define Pt_ARG_LINE_JOIN				Pt_RESOURCE( 25, 3 )
#define Pt_ARG_LINE_CAP					Pt_RESOURCE( 25, 4 )
#define Pt_ARG_ORIGIN					Pt_RESOURCE( 25, 5 )
#define Pt_ARG_POINTS					Pt_RESOURCE( 25, 6 )
#define Pt_CB_RESCALE					Pt_RESOURCE( 25, 7 )
#define	Pt_ARG_DASH_SCALE				Pt_RESOURCE( 25, 8 )
#define	Pt_ARG_INSIDE_COLOR				Pt_RESOURCE( 25, 9 )
#define	Pt_ARG_INSIDE_FILL_PATTERN		Pt_RESOURCE( 25, 10 )
#define	Pt_ARG_INSIDE_TRANS_PATTERN		Pt_RESOURCE( 25, 11 )



/*** Valid flag bits ****/
#define Pt_FLOAT_POS		0x01
#define Pt_FLOAT_ORIGIN		0x02

/*
 * PtGraphic private
 */

/* Widget structure */
typedef struct Pt_graphic_widget {
	PtBasicWidget_t		basic;
	PhPoint_t			origin;
	PhPoint_t			*point_array;
	long				line_width;  /* keep this signed to allow free use in arithmetic with signed values */
	ushort_t			line_cap;
	ushort_t			line_join;
	char				*dash_list;
	ushort_t			npoints;
	char				flags;
	char				reserved;
	short				dash_len;
	long				dash_scale;
	PgColor_t			inside_color;
} PtGraphicWidget_t;

/* Widget union */
typedef union Pt_graphic_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtGraphicWidget_t			graphic;
} PtGraphicUnion_t;

typedef struct Pt_graphic_widget_exdata {
	char				fill_pattern[8];
	char				trans_pattern[8];
} PtGraphicWidgetExdata_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtGraphic.h $ $Rev: 219996 $" )
#endif
