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
 *  PtCompound.h
 *      Header file for the PtCompound widget class
 *

 */
#ifndef __PT_COMPOUND_H_INCLUDED
#define __PT_COMPOUND_H_INCLUDED

#ifndef __PT_CONTAINER_H_INCLUDED
 #include <photon/PtContainer.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtCompound public
 */

extern PtWidgetClassRef_t *PtCompound;

#define Pt_COMPOUND_ID		34

/* Resources */
/* NONE */

/*
 * PtCompound private
 */

typedef struct anode{
	struct anode *next;
	PtWidget_t *compound;
	PtCallbackList_t *cb_list;
} cbnode_t;
/* Widget structure */
typedef struct pt_compound_widget_t{
	PtContainerWidget_t	container;
	cbnode_t 			*redirected_cbs;
} PtCompoundWidget_t;

/* Widget union */
typedef struct Pt_compound_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtContainerWidget_t			container;
	PtCompoundWidget_t			compound;
} PtCompoundUnion_t;

typedef struct Pt_compound_class {
    PtContainerClass_t		container;
    ushort_t				num_subordinates;
    ushort_t				num_blocked_resources;
    ushort_t				*subordinates;
    ulong_t					*blocked_resources;
} PtCompoundClass_t;

#define Pt_SET_NUM_SUBORDINATES			( Pt_ARG_IS_NUMBER( PtCompoundClass_t, num_subordinates ) )

#define Pt_SET_SUBORDINATES				( Pt_ARG_IS_POINTER(PtCompoundClass_t,subordinates) ) 

#define Pt_SET_NUM_BLOCKED_RESOURCES	( Pt_ARG_IS_NUMBER(PtCompoundClass_t,num_blocked_resources) ) 

#define Pt_SET_BLOCKED_RESOURCES		( Pt_ARG_IS_POINTER(PtCompoundClass_t,blocked_resources) ) 

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtCompound.h $ $Rev: 219996 $" )
#endif
