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
 *	PtOSContainer.h
 *		Header file for the PtOSContainer widget class 
 *

 */

#ifndef _PTOSCONTAINER_INCLUDED
#define _PTOSCONTAINER_INCLUDED
#include <photon/PdDirect.h>
#include <photon/PtContainer.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Public */

extern PtWidgetClassRef_t *PtOSContainer;

#define Pt_OSCONTAINER_ID		78

#define Pt_ARG_OSC_DRAW_BUFFER_SIZE		Pt_RESOURCE( 78, 2 )
#define Pt_ARG_OSC_PIXEL_FORMAT			Pt_RESOURCE( 78, 3 )
#define	Pt_ARG_OSC_FLAGS				Pt_RESOURCE( 78, 4 )

/* Os Container flags */

#define Pt_OSC_FLAGS_DYNAMIC_DRAW_BUFFER	0x00000001	/* Private */
#define	Pt_OSC_MEM_ON_DEMAND				0x00000002

typedef struct pt_os_container
{
	PtContainerWidget_t	container;
	PdOffscreenContext_t 	*osc;
	int type;
	int	flags;
	PhPoint_t cur_sticky;
	unsigned long draw_buffer_size;
	unsigned long pixel_format;
	int spare[1];
	short spare1;
} PtOSContainerWidget_t;

typedef union pt_os_container_union
{
	PtWidget_t		core;
	PtBasicWidget_t		basic;
	PtContainerWidget_t	container;
	PtOSContainerWidget_t 	oscontainer;
}PtOSContainerUnion_t;

#ifdef __cplusplus
}
#endif

#include <photon/PhPackPop.h>

#endif


#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtOSContainer.h $ $Rev: 219996 $" )
#endif
