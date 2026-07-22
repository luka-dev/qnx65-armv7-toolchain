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

 *	PtCalendar.h

 *		Header file for the PtCalendar widget class

 *



 */

#ifndef __PT_CALENDAR_H_INCLUDED

#define __PT_CALENDAR_H_INCLUDED



#ifndef __PT_BASIC_H_INCLUDED

 #include <photon/PtBasic.h>

#endif



#include <photon/PhPack.h>



#ifdef __cplusplus

extern "C" {

#endif



#define Pt_CALENDAR_ID	56



/* widget resources */

#define Pt_ARG_CALENDAR_DATE			Pt_RESOURCE( 56,  0 )

#define Pt_ARG_CALENDAR_TIME_T			Pt_RESOURCE( 56, 17 )

#define Pt_ARG_CALENDAR_FONT1			Pt_RESOURCE( 56,  1 )

#define Pt_ARG_CALENDAR_COLOR1			Pt_RESOURCE( 56,  2 )

#define Pt_ARG_CALENDAR_FONT2			Pt_RESOURCE( 56,  3 )

#define Pt_ARG_CALENDAR_COLOR2			Pt_RESOURCE( 56,  4 )

#define Pt_ARG_CALENDAR_FONT3			Pt_RESOURCE( 56,  5 )

#define Pt_ARG_CALENDAR_COLOR3			Pt_RESOURCE( 56,  6 )

#define Pt_ARG_CALENDAR_FONT4			Pt_RESOURCE( 56,  7 )

#define Pt_ARG_CALENDAR_COLOR4			Pt_RESOURCE( 56,  8 )

#define Pt_ARG_CALENDAR_FONT5			Pt_RESOURCE( 56,  9 )

#define Pt_ARG_CALENDAR_COLOR5			Pt_RESOURCE( 56, 10 )

#define Pt_ARG_CALENDAR_YEAR_BTN_COLOR	Pt_RESOURCE( 56, 18 )

#define Pt_ARG_CALENDAR_MONTH_BTN_COLOR	Pt_RESOURCE( 56, 19 )

#define Pt_ARG_CALENDAR_SEL_COLOR		Pt_RESOURCE( 56, 11 )

#define Pt_ARG_CALENDAR_WDAY_NAMES		Pt_RESOURCE( 56, 12 )

#define Pt_ARG_CALENDAR_MONTH_NAMES		Pt_RESOURCE( 56, 13 )

#define Pt_ARG_CALENDAR_FLAGS			Pt_RESOURCE( 56, 14 )

#define Pt_ARG_CALENDAR_HIGHLIGHT		Pt_RESOURCE( 56, 15 )

#define Pt_CB_CALENDAR_SELECT			Pt_RESOURCE( 56, 16 )





/* calendar flags */

#define Pt_CALENDAR_YEAR_BTNS	1 	/* show the year buttons */

#define Pt_CALENDAR_MONTH_BTNS	2	/* show the month buttons */

#define Pt_CALENDAR_SHOW_PREV	4	/* show the end of the last month */

#define Pt_CALENDAR_SHOW_NEXT	8	/* show the beginning of the next month */

#define Pt_CALENDAR_SHOW_GRID	16	/* show a grid around all dates */



typedef struct _Date 

{

	signed char day;    /* 0..30 */

	signed char month;  /* 0..11 */

	signed short year;  /* -32767 to +32767 */

} PtCalendarDate_t;



/* Callback Structure */

typedef struct Pt_calendar_select_callback 

{

	int type;

	PtCalendarDate_t date;

	time_t time;

} PtCalendarSelectCallback_t;



/* Types for Calendar Select Callback */

#define Pt_CALENDAR_DATE_SELECTED			1

#define Pt_CALENDAR_WDAY_SELECTED			2

#define Pt_CALENDAR_MONTH_SELECTED			3

#define Pt_CALENDAR_YEAR_SELECTED			4



/* widget instance structure */

typedef struct calendar_widget{

	PtBasicWidget_t		basic;

	unsigned long		flags;

	PtCalendarDate_t	date;

	char *				font1;

	char *				font2;

	char *				font3;

	char *				font4;

	char *				font5;

	PgColor_t			color1;

	PgColor_t			color2;

	PgColor_t			color3;

	PgColor_t			color4;

	PgColor_t			color5;

	PgColor_t			select_color;

	unsigned long		highlight;

	char				**wday_array;

	char				**month_array;

	short				year;

	char				month;

	char				day;

	char				wday_offset;

	char				msize;

	char				prev_msize;

	char				zero;

	short				width;

	short				height;

	short				xoff;

	short				yoff;

	short				charh1;

	short				charw1;

	short				chary1;

	short				charh2;

	short				charw2;

	short				chary2;

	short				charh3;

	short				charw3;

	short				chary3;

	short				charh4;

	short				charw4;

	short				chary4;

	short				charh5;

	short				charw5;

	short				chary5;

	short				start_row;

	short				start_col;

	short 				day_count, month_count;

	time_t				cal_time_t;

	PgColor_t			year_btn_color, month_btn_color;

	} PtCalendarWidget_t;



/* widget class pointer */

extern PtWidgetClassRef_t *PtCalendar;



#ifdef __cplusplus

};

#endif



#include <photon/PhPackPop.h>



#endif



#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtCalendar.h $ $Rev: 219996 $" )
#endif
