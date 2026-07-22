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
 *	PtRawTree.h
 *		Header file for the PtRawTree widget class
 *

 */
#ifndef __PT_RAW_TREE_H_INCLUDED
#define __PT_RAW_TREE_H_INCLUDED

#ifndef __PT_GENTREE_H_INCLUDED
 #include <photon/PtGenTree.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtRawTree public
 */

extern PtWidgetClassRef_t *const PtRawTree;

#define Pt_RAW_TREE_ID 69

/* Resources */
#define Pt_ARG_RAWTREE_DRAW_F				Pt_RESOURCE( Pt_RAW_TREE_ID,  0 )
#define Pt_ARG_RAWTREE_STATE_F				Pt_RESOURCE( Pt_RAW_TREE_ID,  1 )
#define Pt_ARG_RAWTREE_SELECT_F				Pt_RESOURCE( Pt_RAW_TREE_ID,  2 )
#define Pt_ARG_RAWTREE_INFLATE_F			Pt_RESOURCE( Pt_RAW_TREE_ID,  3 )
#define Pt_ARG_RAWTREE_ITEMATTR_F			Pt_RESOURCE( Pt_RAW_TREE_ID,  4 )

typedef PtGenTreeDrawItemF_t PtRawTreeDrawItemF_t;
typedef PtGenTreeItemStateF_t PtRawTreeItemStateF_t;
typedef PtGenListSelectF_t PtRawTreeSelectF_t;
typedef PtGenListInflateF_t PtRawTreeInflateF_t;
typedef PtGenListGetItemAttrsF_t PtRawTreeGetItemAttrsF_t;

/*
 * PtRawTree private
 */

/* Widget structure */
typedef struct Pt_raw_tree_widget {
	PtGenTreeWidget_t			gtree;
	PtRawTreeDrawItemF_t    	*draw_item_f;
	PtRawTreeItemStateF_t   	*state_f;
	PtRawTreeSelectF_t  		*select_f;
	PtRawTreeInflateF_t 		*inflate_f;
	PtRawTreeGetItemAttrsF_t	*itemattr_f;
	}
		PtRawTreeWidget_t;

/* Widget union */
typedef union Pt_raw_tree_union {
	PtWidget_t			core;
	PtBasicWidget_t		basic;
	PtGenListWidget_t	glist;
	PtGenTreeWidget_t	gtree;
	PtRawTreeWidget_t	rtree;
	}
		PtRawTreeUnion_t;


#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtRawTree.h $ $Rev: 219996 $" )
#endif
