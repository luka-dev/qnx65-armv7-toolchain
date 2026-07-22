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
/* PtTrend.h */

#ifndef __PT_TREND_H_INCLUDED
#define __PT_TREND_H_INCLUDED

#ifndef __PT_BASIC_H_INCLUDED
 #include <photon/PtBasic.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

#define Pt_TREND_ID		73

#define Pt_ARG_TREND_DATA			Pt_RESOURCE( Pt_TREND_ID,  0 )
#define Pt_ARG_TREND_GRID_X			Pt_RESOURCE( Pt_TREND_ID,  1 )
#define Pt_ARG_TREND_GRID_Y 		Pt_RESOURCE( Pt_TREND_ID,  2 )
#define Pt_ARG_TREND_COUNT			Pt_RESOURCE( Pt_TREND_ID,  3 )
#define Pt_ARG_TREND_MAX			Pt_RESOURCE( Pt_TREND_ID,  4 )
#define Pt_ARG_TREND_MIN			Pt_RESOURCE( Pt_TREND_ID,  5 )
#define Pt_ARG_TREND_INC			Pt_RESOURCE( Pt_TREND_ID,  6 )
#define Pt_ARG_TREND_FLAGS			Pt_RESOURCE( Pt_TREND_ID,  7 )
#define Pt_ARG_TREND_GRID_COLOR		Pt_RESOURCE( Pt_TREND_ID,  8 )
#define Pt_ARG_TREND_COLOR_LIST		Pt_RESOURCE( Pt_TREND_ID,  9 )
#define Pt_ARG_TREND_ATTRIBUTES		Pt_RESOURCE( Pt_TREND_ID, 10 )
#define Pt_ARG_TREND_PALETTE_END	Pt_RESOURCE( Pt_TREND_ID, 11 )

#define Pt_PIXEL					0x00000001
#define Pt_GRID						0x00000002
#define Pt_TREND_HORIZONTAL			0x00000004
#define Pt_TREND_VERTICAL			0x00000008
#define Pt_TREND_LEFT_TO_RIGHT		0x00000010
#define Pt_TREND_RIGHT_TO_LEFT		0x00000020
#define Pt_TREND_TOP_TO_BOTTOM		0x00000040
#define Pt_TREND_BOTTOM_TO_TOP		0x00000080
#define	Pt_GRID_ABOVE_TRENDS		0x00000100
#define	Pt_TRENDS_ABOVE_GRID		0x00000200
#define Pt_GRID_IS_TRANSLUCENT		0x00000400
#define Pt_GRID_FORCE				0x00000800

extern PtWidgetClassRef_t *PtTrend;

typedef struct Pt_trend_attr {
	int map;
	}
		PtTrendAttr_t;


typedef struct Pt_trend_lines {
	void	 	*data;
	short int	valid_size;	
	#ifdef __QNXNTO__
		short	reserved;
	#endif
	}
		PtTrendLines_t;

typedef struct Pt_trend_widget {
	PtBasicWidget_t		basic;
	#ifdef __QNXNTO__
		short padding1;
	#endif
	long 				flags;
	short 				grid_x;
	short 				grid_y;
	short 				trend_count;
	short 				reserved1;
	unsigned			n_data;
	short 				max;
	short 				min;
	short 				inc;
	short 				reserved2;	
	PtTrendLines_t		*lines;
	PtTrendAttr_t		*attrs;
	PgColor_t			grid_color;
	PgColor_t			*list;
	short				tmask;
	unsigned short		pallen;
	short 				base;
	short 				grid_base;
	short 	 			color_count;
	unsigned short 		width;
	short				delta;
	unsigned short		dflag;
	PhPoint_t			origin;
	}
		PtTrendWidget_t;

/* Widget union */
typedef union Pt_trend_union {
	PtWidget_t			core;
	PtBasicWidget_t		basic;
	PtTrendWidget_t		trend;
	}
		PtTrendUnion_t;



extern void PtTrendPutData(
	PtWidget_t *trend, const short *newdata, int nsamples
	);

extern void PtTrendChangeData( PtWidget_t *widget,
	short const *newdata, unsigned last_sample, unsigned nsamples
	);

extern void PtTrendChangeTrendData( PtWidget_t *widget, unsigned tn,
	short const *newdata, unsigned last_sample, unsigned nsamples
	);

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtTrend.h $ $Rev: 224590 $" )
#endif
