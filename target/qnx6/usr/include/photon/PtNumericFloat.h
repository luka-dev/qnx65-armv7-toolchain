/* Copyright 2009, QNX Software Systems. All Rights Reserved.
 * 
 * You must obtain a written license from and pay applicable license fees to 
 * QNX Software Systems before you may reproduce, modify or distribute this 
 * software, or any work that includes all or part of this software.  Free 
 * development licenses are available for evaluation and non-commercial purposes.  
 * For more information visit http://licensing.qnx.com or email licensing@qnx.com.
 * 
 * This file may contain contributions from others.  Please review this entire 
 * file for other proprietary rights or license notices, as well as the QNX 
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 */
/* PtNumericFloat.h - widget header file */

#ifndef __PT_NUMERIC_FLOAT_H_INCLUDED
#define __PT_NUMERIC_FLOAT_H_INCLUDED
	
#include <photon/PtNumeric.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/* widget instance structure */
typedef struct numeric_float_widget{
	PtNumericWidget_t		numeric;
	double					increment;
	double					min;
	double					max;
	double					value;
	int						precision;
/*	PtCallbackList_t		*changed; */
	long 					spare[2];
	double					d_spare;
}	PtNumericFloatWidget_t;

typedef struct PtNumericFloatCallback{
	double numeric_value;
}	PtNumericFloatCallback_t;

extern PtWidgetClassRef_t *PtNumericFloat;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif




#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtNumericFloat.h $ $Rev: 224590 $" )
#endif
