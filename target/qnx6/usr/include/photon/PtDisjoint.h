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
 *	PtDisjoint.h
 *		Header file for the PtLayout widget class
 *

 */
#ifndef __PT_DISJOINT_H_INCLUDED
	#define __PT_DISJOINT_H_INCLUDED

	#include <photon/PtContainer.h>

	#include <photon/PhPack.h>

	#ifdef __cplusplus
		extern "C" {
	#endif

	#define Pt_DISJOINT_ID 67

	extern PtWidgetClassRef_t *PtDisjoint;

	enum  /* Resources */
		{
		Pt_ARG_SYSINFO = Pt_RESOURCE(Pt_DISJOINT_ID,0),
		Pt_CB_SYSINFO
		};

	typedef struct pt_disjoint_widget PtDisjointWidget_t;
	struct pt_disjoint_widget
		{
		PtContainerWidget_t container;
		PhSysInfo_t	sysinfo;
		PtWidget_t *last_focus;
		PtWidget_t *default_widget;
		unsigned int		flags;
/*		PtCallbackList_t *sysinfo_cb_list; */
		};
	#ifdef __cplusplus
		}
	#endif

	#include <photon/PhPackPop.h>
#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtDisjoint.h $ $Rev: 219996 $" )
#endif
