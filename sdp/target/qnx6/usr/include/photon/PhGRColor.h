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


#if !defined(__LITTLEENDIAN__) && !defined(__BIGENDIAN__)

#  if   defined VARIANT_le
#    define __LITTLEENDIAN__
#  elif defined(VARIANT_be)
#    define __BIGENDIAN__
#  elif !defined(__QNXNTO__)
#    define __LITTLEENDIAN__
#  else
#    define __LITTLEENDIAN__
#    error Could not determine endian-ness of compile
#  endif

#endif

#ifndef GR_Color_t_defined
#define GR_Color_t_defined
#ifdef __LITTLEENDIAN__ 
typedef struct {
    unsigned    B:8, G:8, R:8, I:8;
} GR_ColorRGB_t;
#elif  __BIGENDIAN__
typedef struct {
    unsigned    I:8, R:8, G:8, B:8;
} GR_ColorRGB_t;
#else
#error  Neither __BIGENDIAN__ not __LITTLEENDIAN__ defined
#endif

typedef signed long GR_ColorLong_t;

typedef union {
	GR_ColorRGB_t  rgb;
	GR_ColorLong_t value;
} GR_Color_t;


/*  typedef	struct {
 *  	unsigned 	B:8, G:8, R:8, I:8;
 *  } GR_Color_t; */

typedef struct {	/* SAME AS GR_ColorCacheStruct except for Transp */
	unsigned long			P, S;				/* 0, 4 */
	unsigned char 			Dither[8];			/* 8 */
	GR_Color_t				UColor;				/* 16 */
	unsigned long			Flags;				/* 24 */
} GR_ColorCacheStruct; /* 24 bytes, 6K per palette */
#endif  /* GR_Color_t_defined */


__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PhGRColor.h $ $Rev: 224590 $" )
