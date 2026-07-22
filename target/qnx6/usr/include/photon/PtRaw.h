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
 *	PtRaw.h
 *		Header file for the PtRaw widget class
 *

 */
#ifndef __PT_RAW_H_INCLUDED
#define __PT_RAW_H_INCLUDED

#ifndef __PT_BASIC_H_INCLUDED
 #include <photon/PtBasic.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtRaw public
 */

extern PtWidgetClassRef_t *PtRaw;

/* Resources */
#define Pt_ARG_RAW_DRAW_F			Pt_RESOURCE( 24, 0 )
#define Pt_ARG_RAW_CONNECT_F		Pt_RESOURCE( 24, 1 )
#define Pt_ARG_RAW_EXTENT_F			Pt_RESOURCE( 24, 2 )
#define Pt_ARG_RAW_INIT_F			Pt_RESOURCE( 24, 3 )
#define Pt_ARG_RAW_CALC_OPAQUE_F	Pt_RESOURCE( 24, 4 )


/*
 * PtRaw private
 */

/* Widget structure */
typedef struct Pt_raw_widget {
	PtBasicWidget_t		basic;
	void				(*draw_f)( PtWidget_t *, PhTile_t *damage );
	int					(*init_f)( PtWidget_t * );
	int					(*extent_f)( PtWidget_t * );
	int					(*connect_f)( PtWidget_t * );
	void				(*calc_opaque_f)( PtWidget_t * );

} PtRawWidget_t;

/* Widget union */
typedef union Pt_raw_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtRawWidget_t				raw;
} PtRawUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtRaw.h $ $Rev: 219996 $" )
#endif
