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
 *	PtRawList.h
 *		Header file for the PtRawList widget class
 *

 */
#ifndef __PT_RAW_LIST_H_INCLUDED
#define __PT_RAW_LIST_H_INCLUDED

#ifndef __PT_GENLIST_H_INCLUDED
 #include <photon/PtGenList.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtRawList public
 */

extern PtWidgetClassRef_t *const PtRawList;

#define Pt_RAW_LIST_ID 68

/* Resources */
#define Pt_ARG_RAWLIST_DRAW_F				Pt_RESOURCE( Pt_RAW_LIST_ID,  0 )
#define Pt_ARG_RAWLIST_MOUSE_F				Pt_RESOURCE( Pt_RAW_LIST_ID,  1 )
#define Pt_ARG_RAWLIST_KEY_F				Pt_RESOURCE( Pt_RAW_LIST_ID,  2 )
#define Pt_ARG_RAWLIST_SELECT_F				Pt_RESOURCE( Pt_RAW_LIST_ID,  3 )
#define Pt_ARG_RAWLIST_INFLATE_F			Pt_RESOURCE( Pt_RAW_LIST_ID,  4 )
#define Pt_ARG_RAWLIST_BACKGROUND_F			Pt_RESOURCE( Pt_RAW_LIST_ID,  5 )
#define Pt_ARG_RAWLIST_ITEMATTR_F			Pt_RESOURCE( Pt_RAW_LIST_ID,  7 )
#define Pt_ARG_RAWLIST_GFLAGS				Pt_RESOURCE( Pt_RAW_LIST_ID,  6 )

typedef PtGenListDrawF_t PtRawListDrawF_t;
typedef PtGenListMouseF_t PtRawListMouseF_t;
typedef PtGenListKeyF_t PtRawListKeyF_t;
typedef PtGenListSelectF_t PtRawListSelectF_t;
typedef PtGenListInflateF_t PtRawListInflateF_t;
typedef PtGenListDrawBackgroundF_t PtRawListDrawBackgroundF_t;
typedef PtGenListGetItemAttrsF_t PtRawListGetItemAttrsF_t;

/*
 * PtRawList private
 */

/* Widget structure */
typedef struct Pt_raw_list_widget {
	PtGenListWidget_t			glist;
	PtRawListDrawF_t    		*draw_f;
	PtRawListMouseF_t   		*mouse_f;
	PtRawListKeyF_t     		*key_f;
	PtRawListSelectF_t  		*select_f;
	PtRawListInflateF_t 		*inflate_f;
	PtRawListDrawBackgroundF_t	*background_f;
	PtRawListGetItemAttrsF_t	*itemattr_f;
	}
		PtRawListWidget_t;

/* Widget union */
typedef union Pt_raw_list_union {
	PtWidget_t			core;
	PtBasicWidget_t		basic;
	PtGenListWidget_t	glist;
	PtRawListWidget_t	rlist;
	}
		PtRawListUnion_t;


#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtRawList.h $ $Rev: 219996 $" )
#endif
