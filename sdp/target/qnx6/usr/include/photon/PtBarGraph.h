/* Copyright 2009, QNX Software Systems. All Rights Reserved.
 * 
 * You must obtain a written license from and pay applicable license fees to 
 * QNX Software Systems before you may reproduce, modify or distribute this 
 * software, or any work that includes all or part of this software.  Free 
 * development licenses are available for evaluation and non-commercial purposes.  
 * For more information visit http://licensing.qnx.com or email licensing@qnx.com.
 * 
 * This file may contain contributions from others.  Please review this entire 
 * file for other proprietary rights or license notices, as well as the QNX 
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 */
#ifndef __PT_BARGRAPH_H_INCLUDED
#define __PT_BARGRAPH_H_INCLUDED

#ifndef __PT_BASIC_H_INCLUDED
 #include <photon/PtBasic.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

extern PtWidgetClassRef_t *PtBarGraph;

typedef struct Pt_bargraph_widget
{
	PtBasicWidget_t				basic;
	short						depth;
	short						max;		
	short						min;
	short						base;
	short						num_bars;
	short						bar_width;
	short						grid_x;
	short						grid_y;
	#ifdef __QNXNTO__
		short padding1;
		long						flags;
		PgColor_t					grid_color;
		short						*bar_data;
		short						num_colors;
	#else
		long						flags;
		PgColor_t					grid_color;
		short						*bar_data;
		short						num_colors;
	#endif
	PgColor_t					*bar_color;
} PtBarGraphWidget_t;

#define Pt_ARG_BARGRAPH_DEPTH		Pt_RESOURCE( Pt_CONTRIB(1), 0 )
#define Pt_ARG_BARGRAPH_MAX			Pt_RESOURCE( Pt_CONTRIB(1), 1 )
#define Pt_ARG_BARGRAPH_MIN			Pt_RESOURCE( Pt_CONTRIB(1), 2 )
#define Pt_ARG_BARGRAPH_BASE		Pt_RESOURCE( Pt_CONTRIB(1), 3 )
#define Pt_ARG_BARGRAPH_FLAGS		Pt_RESOURCE( Pt_CONTRIB(1), 4 )
#define Pt_ARG_BARGRAPH_DATA		Pt_RESOURCE( Pt_CONTRIB(1), 5 )
#define Pt_ARG_BARGRAPH_COLOR		Pt_RESOURCE( Pt_CONTRIB(1), 6 )
#define Pt_ARG_BARGRAPH_GRID_HORIZ  Pt_RESOURCE( Pt_CONTRIB(1), 7 )
#define Pt_ARG_BARGRAPH_GRID_VERT   Pt_RESOURCE( Pt_CONTRIB(1), 8 )
#define Pt_ARG_BARGRAPH_GRID_COLOR  Pt_RESOURCE( Pt_CONTRIB(1), 9 )

#define Pt_BARGRAPH_GRID			0x00000001
#define Pt_BARGRAPH_VERTICAL		0x00000002
#define Pt_BARGRAPH_HORIZONTAL		0x00000004

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtBarGraph.h $ $Rev: 224590 $" )
#endif
