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
 *	PtDBContainer.h
 *		Header file for the PtDBContainer widget class 
 *

 */

#ifndef _PTDBCONTAINER_INCLUDED
#define _PTDBCONTAINER_INCLUDED
#include <photon/PmT.h>
#include <photon/PtContainer.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Public */

extern PtWidgetClassRef_t *PtDBContainer;

#define Pt_DBCONTAINER_ID		48

#define Pt_ARG_DB_IMAGE_TYPE				Pt_RESOURCE( 48, 0 )
#define Pt_ARG_DB_MEMORY_CONTEXT_TYPE		Pt_RESOURCE( 48, 1 )

/* Private */

/* Db Container flags */
#define Pt_DB_INLINE_IMAGE 0x00000001

typedef struct pt_db_container
	{
	PtContainerWidget_t	container;
	PmMemoryContext_t *mc;
	PhImage_t	image;
	PhImage_t	def_image;
	int			type;
	int			flags;
	int			spare[4];
	} PtDBContainerWidget_t;

typedef union pt_db_container_union
	{
	PtWidget_t				core;
	PtBasicWidget_t			basic;
	PtContainerWidget_t		container;
	PtDBContainerWidget_t 	dbcontainer;
	}PtDBContainerUnion_t;
#ifdef __cplusplus
}
#endif

#include <photon/PhPackPop.h>

#endif


#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtDBContainer.h $ $Rev: 219996 $" )
#endif
