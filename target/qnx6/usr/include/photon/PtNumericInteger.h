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
/* PtNumericInteger.h - widget header file */

#ifndef __PT_NUMERIC_INTEGER_H_INCLUDED
#define __PT_NUMERIC_INTEGER_H_INCLUDED
	
#include <photon/PtNumeric.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

#define Pt_NUMERIC_INTEGER_ID                        54 

/* widget resources */
#define Pt_ARG_NUMERIC_INTEGER_FLAGS                 Pt_RESOURCE( 54, 1 )
#define Pt_ARG_NUMERIC_INTEGER_RADIX                 Pt_RESOURCE( 54, 2 )

/* PtNumeric Flags */
#define Pt_NUMERIC_INTEGER_USE_ARITHMETIC      0x01
#define Pt_NUMERIC_INTEGER_USE_UPPER_CASE      0x02

/* widget instance structure */
typedef struct numeric_integer_widget{
	PtNumericWidget_t	numeric;
	int			increment;
	long			min;
	long			max;
	long			value;
/*	PtCallbackList_t	*changed; */
	ushort_t		flags;
	ushort_t		radix;
	long 			spare[1];
}	PtNumericIntegerWidget_t;

typedef struct PtNumericIntegerCallback{
	int numeric_value;
}	PtNumericIntegerCallback_t;

extern PtWidgetClassRef_t *PtNumericInteger;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif




#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtNumericInteger.h $ $Rev: 224590 $" )
#endif
