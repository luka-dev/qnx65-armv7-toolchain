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
 *  sh/platform.h
 *

 */

#ifndef _SH_PLATFORM_H_INCLUDED
#define _SH_PLATFORM_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#error sh/platform.h should not be included directly.
#endif

#if defined(__QNXNTO__)

#define __JMPBUFSIZE	16
typedef	double			__jmpbufalign;

#else
#error Not configured for target
#endif


/* The sh4a math optimizations are only in gcc-3.4 or better */

#if defined __GNUC__ && ( __GNUC__ >= 4 || (__GNUC__ >= 3 && __GNUC_MINOR__ >= 4))

#if defined __SH4A__ && defined __FAST_MATH__

/* use gccs built-ins */

#define _FAST_SIN(val) __builtin_sin(val)
#define _FAST_COS(val) __builtin_cos(val)
#define _FAST_SINL(val) __builtin_sinl(val)
#define _FAST_COSL(val) __builtin_cosl(val)
#define _FAST_SINF(val) __builtin_sinf(val)
#define _FAST_COSF(val) __builtin_cosf(val)

#endif
#endif


#endif


__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/c/public/sh/platform.h $ $Rev: 273413 $" )
