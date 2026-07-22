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
 *	PtGroup.h
 *		Header file for the PtGroup widget class
 *

 */
#ifndef __PT_GROUP_H_INCLUDED
#define __PT_GROUP_H_INCLUDED

#ifndef __PT_CONTAINER_H_INCLUDED
 #include <photon/PtContainer.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/* 
 * PtGroup public
 */

extern PtWidgetClassRef_t *PtGroup;

#define Pt_GROUP_ID		11

/* Resources */
#define Pt_ARG_GROUP_FLAGS		 	Pt_RESOURCE( 11, 0 )
#define Pt_ARG_GROUP_HORZ_ALIGN	 	Pt_RESOURCE( 11, 1 )
#define Pt_ARG_GROUP_ORIENTATION	Pt_RESOURCE( 11, 2 )
#define Pt_ARG_GROUP_SPACING		Pt_RESOURCE( 11, 3 )
#define Pt_ARG_GROUP_VERT_ALIGN		Pt_RESOURCE( 11, 4 )
#define Pt_ARG_GROUP_ROWS_COLS	 	Pt_RESOURCE( 11, 5 )
#define Pt_ARG_GROUP_SPACING_X		Pt_RESOURCE( 11, 6 )
#define Pt_ARG_GROUP_SPACING_Y		Pt_RESOURCE( 11, 7 )
#define	Pt_ARG_CELL_HORZ_ALIGN		Pt_RESOURCE( 11, 8 )
#define	Pt_ARG_CELL_VERT_ALIGN		Pt_RESOURCE( 11, 9 )

/* flag bits */
#define Pt_GROUP_EXCLUSIVE				0x00000001
#define Pt_GROUP_EQUAL_SIZE				0x00000002
#define Pt_GROUP_NO_SELECT_ALLOWED  	0x00000004
#define Pt_GROUP_NO_KEYS				0x00000008
#define Pt_GROUP_NO_KEY_WRAP_HORIZONTAL	0x00000010
#define Pt_GROUP_NO_KEY_WRAP_VERTICAL	0x00000020
#define Pt_GROUP_NO_KEY_WRAP			(Pt_GROUP_NO_KEY_WRAP_HORIZONTAL | Pt_GROUP_NO_KEY_WRAP_VERTICAL )
#define Pt_GROUP_EQUAL_SIZE_HORIZONTAL	0x00000100
#define Pt_GROUP_EQUAL_SIZE_VERTICAL	0x00000200
#define Pt_GROUP_STRETCH_HORIZONTAL		0x00000400
#define Pt_GROUP_STRETCH_VERTICAL		0x00000800
#define Pt_GROUP_STRETCH				(Pt_GROUP_STRETCH_VERTICAL|Pt_GROUP_STRETCH_HORIZONTAL)
#define Pt_GROUP_STRETCH_FILL			0x00001000


/* vertical alignment */
#define Pt_GROUP_VERT_NONE			-1
#define Pt_GROUP_VERT_CENTER		0
#define Pt_GROUP_VERT_TOP 			1
#define Pt_GROUP_VERT_BOTTOM		2

/* horizontal alignment */
#define Pt_GROUP_HORZ_NONE			-1
#define Pt_GROUP_HORZ_CENTER		0
#define Pt_GROUP_HORZ_LEFT			1
#define Pt_GROUP_HORZ_RIGHT			2

/* orientation */
#define Pt_GROUP_HORIZONTAL			0
#define Pt_GROUP_VERTICAL			1
#define Pt_GROUP_ASIS				2

/*
 * PtGroup private
 */

/* Widget structure */
typedef struct Pt_group_widget {
	PtContainerWidget_t			container;
	ulong_t						group_flags;
	ushort_t					orientation;
	ushort_t					spacing_x;
	ushort_t					vert_align;
	ushort_t					horz_align;
	ushort_t					number_of_opts; /*matrix size */
	ushort_t					spacing_y;
} PtGroupWidget_t;

/* Widget union */
typedef union Pt_group_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtContainerWidget_t			container;
	PtGroupWidget_t				group;
} PtGroupUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtGroup.h $ $Rev: 219996 $" )
#endif
