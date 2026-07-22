/*
   $Header: /home/archive/FontFusion/FontFusion/core/rfork.h,v 1.3 2007/11/18 04:33:50 ljoshi Exp $

 * rfork.h
 * Font Fusion Copyright (c) 1989-2007 all rights reserved by Bitstream Inc.
 * $Header: /home/archive/FontFusion/FontFusion/core/rfork.h,v 1.3 2007/11/18 04:33:50 ljoshi Exp $
 * http://www.bitstream.com/
 * http://www.typesolutions.com/
 * Author: Lokesh
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

#ifndef __RFORK_HEADER__
#define __RFORK_HEADER__


#ifndef FF_FFCONFIG_HEADER
#include "config.h"
#else
#include FF_FFCONFIG_HEADER
#endif 

#include FF_DTYPES_HEADER
#include FF_TSIMEM_HEADER
#include FF_T2KSTRM_HEADER

#ifdef ENABLE_MAC_RFORK

#ifdef __cplusplus
extern "C" {
#endif  

typedef struct rforkClass_t
{
	uint32 numOffsets;
	uint32 * offsetArray;
	InputStream * in;
	InputStream * origIn;
	tsiMemObject *mem;

}rforkClass;


rforkClass * New_rforkClass( tsiMemObject *mem, InputStream * in);
int16 setStatusForRFork( rforkClass * rfork, int32 fontNum, InputStream * in);
void Delete_rforkClass(rforkClass * rfork);
int FF_RforkGetSubCount(InputStream * in,  uint32 tag);

#ifdef __cplusplus
}
#endif  

#endif 

#endif 


