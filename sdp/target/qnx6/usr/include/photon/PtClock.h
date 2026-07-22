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
 *	PtClock.h
 *	Header file for the PtClock widget class
 *

 */
#ifndef __PT_CLOCK_H_INCLUDED
#define __PT_CLOCK_H_INCLUDED

#ifndef __PT_BASIC_H_INCLUDED
#include <photon/PtBasic.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

#define Pt_CLOCK_ID		57

/* clock resources */
#define Pt_ARG_CLOCK_TYPE					Pt_RESOURCE(57,0)
#define Pt_ARG_CLOCK_FLAGS					Pt_RESOURCE(57,1)
#define Pt_ARG_CLOCK_HOUR					Pt_RESOURCE(57,2)
#define Pt_ARG_CLOCK_MINUTE					Pt_RESOURCE(57,3)
#define Pt_ARG_CLOCK_SECOND					Pt_RESOURCE(57,4)
#define Pt_ARG_CLOCK_FACE_OUTLINE_COLOR		Pt_RESOURCE(57,5)
#define Pt_ARG_CLOCK_FACE_COLOR				Pt_RESOURCE(57,6)
#define Pt_ARG_CLOCK_HOUR_COLOR				Pt_RESOURCE(57,7)
#define Pt_ARG_CLOCK_MINUTE_COLOR			Pt_RESOURCE(57,8)
#define Pt_ARG_CLOCK_SECOND_COLOR			Pt_RESOURCE(57,9)
#define Pt_ARG_CLOCK_SEP1					Pt_RESOURCE(57,10)
#define Pt_ARG_CLOCK_SEP2					Pt_RESOURCE(57,11)
#define Pt_ARG_CLOCK_SEP1_COLOR				Pt_RESOURCE(57,12)
#define Pt_ARG_CLOCK_SEP2_COLOR				Pt_RESOURCE(57,13)
#define Pt_ARG_CLOCK_HOUR_OFFSET			Pt_RESOURCE(57,14)
#define Pt_ARG_CLOCK_MINUTE_OFFSET			Pt_RESOURCE(57,15)
#define Pt_ARG_CLOCK_SECOND_OFFSET			Pt_RESOURCE(57,16)
#define Pt_ARG_CLOCK_FONT					Pt_RESOURCE(57,17)
#define Pt_CB_CLOCK_TIME_CHANGED			Pt_RESOURCE(57,18)

/* clock types */
#define Pt_CLOCK_DIGITAL		0	/* Digital display */
#define Pt_CLOCK_ANALOG			1	/* Analog display */
#define Pt_CLOCK_LED			2	/* LED-style (scaleable) digital display */

/* used for setting current time */
#define Pt_CLOCK_CURRENT		-1	/* For setting current time */

/* Clock flags */
#define Pt_CLOCK_TRACK_TIME		1 	/* Clock always reflects current time */
#define Pt_CLOCK_SHOW_SECONDS		2 	/* Enables display of seconds */
#define Pt_CLOCK_24_HOUR		4 	/* Enables 24-hour display (defeats AM/PM in digital) */
#define Pt_CLOCK_SHOW_NUMBERS		8	/* Shows numbers (analog only) */
#define Pt_CLOCK_SHOW_AMPM		16 	/* Enables display of AM/PM (digital only) */
#define Pt_CLOCK_PAD_HOURS		32	/* Pad hours field with 0 (digital only) */

/* Used in conjunction with the clock widget's change_flags variable */
#define Pt_CLOCK_HOUR_CHANGED		1
#define Pt_CLOCK_MINUTE_CHANGED		2
#define Pt_CLOCK_SECOND_CHANGED		4

/* callback structure */
typedef struct Pt_clock_change_callback
{
	short hour,minute,second;
	short old_hour,old_minute,old_second;

} PtClockTimeCallback_t;

/* widget instance structure */
typedef struct clock_widget
{
	PtBasicWidget_t basic;
	unsigned long flags;					/* Clock-specific flags */
	short hour,minute,second;				/* Maintains clock's time setting */
	short h_offset,m_offset,s_offset;		/* Maintains clock's offsets from time setting */
	char *sep1,*sep2;							/* Separators between time fields (digital display) */
	short type;								/* Clock type (Pt_CLOCK_ANALOG or Pt_CLOCK_DIGITAL) */
	const char *font;						/* Font used in display (analog and digital) */
	
	/* Clock color scheme */
	PgColor_t face_outline_color,face_color;
	PgColor_t hour_color,minute_color,second_color;
	PgColor_t sep1_color,sep2_color;
	
	/* Widget internal variables follow */

	short old_hour,old_minute,old_second;	/* Saves current time settings for next redraw */
	char change_flags;						/* Indicates fields that need updating, 0 = entire redraw */
	
	/* Geometry maintenance.

	   For Pt_CLOCK_ANALOG,
	     p[0] = center of clock face
	     p[1] = radius of clock face
	     p[2] = hour/second hand thickness
	     p[3] = unused
	     r[n] = unreferenced
		
	   For Pt_CLOCK_DIGITAL,
	     p[0] = right of hours field
	     p[1] = center of minutes field
	     p[2] = left of seconds field
	     p[3] = right of am/pm field
	     r[n] = unreferenced

	   For Pt_CLOCK_LED,
	     p[n] = unreferenced
	     r[0] = bounding box for hours field
	     r[1] = bounding box for minutes field
	     r[2] = bounding box for seconds field
	     r[3] = boundinx box for AM/PM field
	*/
	union _geometry
	{
		PhPoint_t p[4];
		PhRect_t r[4];
	} geom;
	
} PtClockWidget_t;

/* widget class pointer */
extern PtWidgetClassRef_t *PtClock;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtClock.h $ $Rev: 219996 $" )
#endif
