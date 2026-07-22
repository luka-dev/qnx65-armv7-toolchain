/*
	$Header: /home/archive/FontFusion/FontFusion/core/dtypes.h,v 1.11 2008/03/11 16:12:55 sflynn Exp $

 * Dtypes.h
 * Font Fusion Copyright (c) 1989-2007 all rights reserved by Bitstream Inc.
 * http://www.bitstream.com/
 * http://www.typesolutions.com/
 * Author: Sampo Kaasila
 *
 * This software is the property of Bitstream Inc. and it is furnished
 * under a license and may be used and copied only in accordance with the
 * terms of such license and with the inclusion of the above copyright notice.
 * This software or any other copies thereof may not be provided or otherwise
 * made available to any other person or entity except as allowed under license.
 * No title to and no ownership of the software or intellectual property
 * contained herein is hereby transferred. This information in this software
 * is subject to change without notice
 */

#ifndef __T2K_DTYPES__
#define __T2K_DTYPES__
#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif  /* __cplusplus */


#ifndef FF_FFCONFIG_HEADER
#include "config.h"
#else
#include FF_FFCONFIG_HEADER
#endif /* FF_FFCONFIG_HEADER */

/* 32 bits: These types should always be 32 bits wide. These definitions should work
 * correctly on 32 bit systems. On 64 Bit systems or some platforms this may have to
 * be changed so as to have 32 bits wide length only.
 * (LL)P64: Windows. No change may be needed.
 * LP64   : Sun, SGI, Unix, Mac OS X - Tiger. Here these should be changed to int and
 *          unsigned int respectively
 */

/* Define __INT32_DEFINED__ if int32 is already defined by the platform. */
#ifndef __INT32_DEFINED__
typedef signed long int32;
#endif /* __INT32_DEFINED__ */

/* Define __UINT32_DEFINED__ if uint32 is already defined by the platform. */
#ifndef __UINT32_DEFINED__
typedef unsigned long uint32;
#endif /* __UINT32_DEFINED__ */

/* 16 bits */
/* Define __INT16_DEFINED__ if int16 is already defined by the platform. */
#ifndef __INT16_DEFINED__
typedef signed short int16;
#endif /* __INT16_DEFINED__ */

/* Define __UINT16_DEFINED__ if uint16 is already defined by the platform. */
#ifndef __UINT16_DEFINED__
typedef unsigned short uint16;
#endif /* __UINT16_DEFINED__ */

/* 8 bits */
/* Define __INT8_DEFINED__ if int8 is already defined by the platform. */
#ifndef __INT8_DEFINED__
typedef signed char int8;
#endif /* __INT8_DEFINED__ */

/* Define __UINT8_DEFINED__ if uint8 is already defined by the platform. */
#ifndef __UINT8_DEFINED__
typedef unsigned char uint8;
#endif /* __UINT8_DEFINED__ */

/* Special: 32 bits */
typedef int32 F26Dot6;
typedef int32 F16Dot16;

/* This class should be of same length as the address length of the base platform. This value is valid
 * for 32 bit systems. Change may be needed for other platforms.
 * (LL)P64: Windows. Here the typedef should be changed to unsigned long long.
 * LP64   : Sun, SGI, Unix, Mac OS X - Tiger.  No change may be needed.
 */
typedef unsigned long int uintptr_w;


#ifdef ENABLE_32BIT_CACHE_TAG
typedef uint32 fontCode_t;
#else
typedef uint16 fontCode_t;
#endif /* ENABLE_32BIT_CACHE_TAG */


typedef long Fract;
typedef long Fixed;


#define ONE16Dot16 0x10000


#if !defined(__cplusplus) && !defined(false)
#define false 0
#endif


#if !defined(__cplusplus) && !defined(true)
#define true 1
#endif


typedef void *(*FF_GetCacheMemoryPtr)( void *theCache, uint32 length );


#ifdef ENABLE_COMMON_DEFGLYPH
typedef void *(*FF_SearchDefGlyph)(void *theCache, uint16 cmd);
#endif/*ENABLE_COMMON_DEFGLYPH*/

#ifdef ENABLE_SMARTSCALE
typedef void (*FF_CmDeleteCurrentChar)(void *theCache);
#endif

#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif /* _T2K_DTYPES__ */


/*********************** R E V I S I O N   H I S T O R Y **********************
 *
 *     $Header: /home/archive/FontFusion/FontFusion/core/dtypes.h,v 1.11 2008/03/11 16:12:55 sflynn Exp $
 *                                                                           *
 *     $Log: dtypes.h,v $
 *     Revision 1.11  2008/03/11 16:12:55  sflynn
 *     Added a typedef for the SmartScale feature.
 *
 *     Revision 1.10  2007/11/06 13:19:58  himanshu
 *     Adding support for variable include file name.
 *
 *     Revision 1.9  2007/05/09 06:05:08  ljoshi
 *     Making int32, uint32, int16, uint16, iint8 and uint8 inside macros to avoid redefinition errors.
 *
 *     Revision 1.8  2007/03/27 13:51:05  sflynn
 *     Modified to check for __cplusplus when defining true and false.
 *
 *     Revision 1.7  2007/01/04 22:08:03  sflynn
 *     Modified FF_SearchDefGlyph() to handle T2K_SKIP_SCAN_BM option.
 *
 *     Revision 1.6  2006/06/02 18:11:24  sflynn
 *     Modified to support configurable 16\32 bit cache tag.
 *
 *     Revision 1.5  2006/05/24 18:16:21  sflynn
 *     Added "signed" to int32 and int16 typedefs.
 *
 *     Revision 1.4  2006/04/28 17:49:29  sflynn
 *     no message
 *
 *     Revision 1.8  2005/09/26 18:21:45  Shawn_Flynn
 *     The following typedefs were changed:
 *          F26Dot6  - int32
 *          F16Dot16 - int32
 *     The following typedef was added for 64 bit pointer support:
 *          uintptr_w - unsigned long int
 *
 *     Revision 1.7  2005/09/15 19:28:20  Shawn_Flynn
 *     Added typedef for default glyph search routine.
 *
 *     Revision 1.6  2002/12/16 19:53:41  Shawn_Flynn
 *     Cleaned up for dtypED process.
 *
 *     Revision 1.5  2002/03/06 21:29:38  Reggers
 *     Updated copyright header
 *     Revision 1.4  2002/03/06 17:56:20  Reggers
 *     Made all atomic data types typedefs instead of #defines
 *     Revision 1.3  1999/09/30 15:11:09  jfatal
 *     Added correct Copyright notice.
 *     Revision 1.2  1999/05/17 15:56:38  reggers
 *     Inital Revision
 *                                                                           *
******************************************************************************/
