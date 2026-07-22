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
/* PtMeter.h - widget header file */

#ifndef __RT_METER_H_INCLUDED
#define __RT_METER_H_INCLUDED

#ifndef __PT_BASIC_H_INCLUDED
 #include <photon/PtBasic.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

#define Pt_METER_ID		74

/* widget resources */
#define Pt_ARG_METER_NEEDLE_COLOR			Pt_RESOURCE( Pt_METER_ID, 0 )
#define Pt_ARG_METER_COLOR					Pt_RESOURCE( Pt_METER_ID, 1 )
#define Pt_ARG_METER_NEEDLE_POSITION		Pt_RESOURCE( Pt_METER_ID, 2 )
#define Pt_ARG_METER_MAX_NEEDLE_POSITION	Pt_RESOURCE( Pt_METER_ID, 3 )
#define Pt_ARG_METER_MIN_NEEDLE_POSITION	Pt_RESOURCE( Pt_METER_ID, 4 )
#define Pt_ARG_METER_FLAGS					Pt_RESOURCE( Pt_METER_ID, 5 )
#define Pt_ARG_METER_NUM_SEVERITY_LEVELS	Pt_RESOURCE( Pt_METER_ID, 6 )
#define Pt_ARG_METER_LEVEL1_COLOR			Pt_RESOURCE( Pt_METER_ID, 7 )
#define Pt_ARG_METER_LEVEL2_COLOR			Pt_RESOURCE( Pt_METER_ID, 8 )
#define Pt_ARG_METER_LEVEL3_COLOR			Pt_RESOURCE( Pt_METER_ID, 9 )
#define Pt_ARG_METER_LEVEL1_POS				Pt_RESOURCE( Pt_METER_ID, 10 )
#define Pt_ARG_METER_LEVEL2_POS				Pt_RESOURCE( Pt_METER_ID, 11 )
#define Pt_ARG_METER_TEXT_FONT				Pt_RESOURCE( Pt_METER_ID, 12 )
#define Pt_CB_METER_MOVED					Pt_RESOURCE( Pt_METER_ID, 13 )
#define Pt_ARG_METER_FONT_COLOR				Pt_RESOURCE( Pt_METER_ID, 14 )
#define Pt_ARG_METER_INCREMENT				Pt_RESOURCE( Pt_METER_ID, 15 )
#define Pt_ARG_METER_KEY_LEFT				Pt_RESOURCE( Pt_METER_ID, 16 )
#define Pt_ARG_METER_KEY_RIGHT				Pt_RESOURCE( Pt_METER_ID, 17 )

/* meter flags */
#define PtM_SELECTABLE 		0x0
#define PtM_NON_SELECTABLE 	0x1
#define PtM_NO_TEXT 		0x2

/* callback subtypes */
#define Pt_KEY_MOVED	0x1
#define Pt_MOUSE_MOVED	0x2
#define Pt_ARG_MOVED	0x4

/* Callback structure */
typedef struct Pt_meter_callback
{	int position;
	int severity;
} PtMeterCallback_t;

/* widget instance structure */
typedef struct Pt_meter_widget{
	PtBasicWidget_t	basic;
	PgColor_t	needle_color;
	PgColor_t	meter_color;
	PgColor_t	font_color;
	short		needle_position;
	short 		max_needle_position;
	short 		min_needle_position;
	#ifdef __QNXNTO__
		short 	num_severity_levels;
		long 	flags;
	#else
		long 	flags;
		short 	num_severity_levels;
	#endif
	PgColor_t	level1_color;
	PgColor_t	level2_color;
	PgColor_t	level3_color;
	short		level1_pos;
	short		level2_pos;
	const char	*font;
	#ifdef __QNXNTO__
		int 	key_left;
		int 	key_right;
		short 	step;
		short	real_position;
	#else
		short 	step;
		int 	key_left;
		int 	key_right;
		short	real_position;
		short 	spare; /*spare */
		char 	spare2[2]; /* spare */
	#endif

/*	PtCallbackList_t *moved; */

	/* internal variables */
	int 		radius;
	int 		max_text;
	#ifdef __QNXNTO__
		PhPoint_t 	needle_length;
		PhPoint_t 	center;
		short		old_needle_position;
		char		min_string[11];
		char		max_string[11];
	#else
		short		old_needle_position;
		PhPoint_t 	needle_length;
		PhPoint_t 	center;
		char		min_string[11];
		char		max_string[11];
	#endif
	int 		REDRAW;
	int 		old_severity;
	int 		FIR;
	PhRect_t rect1, rect2;
}	PtMeterWidget_t;

/* widget class pointer */
extern PtWidgetClassRef_t *PtMeter;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtMeter.h $ $Rev: 224590 $" )
#endif
