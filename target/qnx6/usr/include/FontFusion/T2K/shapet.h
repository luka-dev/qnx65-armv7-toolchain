/*
	$Header: /home/archive/FontFusion/FontFusion/core/shapet.h,v 1.5 2008/11/19 22:19:38 sflynn Exp $

 * Shapet.h
 * Font Fusion Copyright (c) 1989-2008 all rights reserved by Bitstream Inc.
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

#ifndef __T2K_SHAPET__
#define __T2K_SHAPET__
#ifdef __cplusplus
extern "C" {            
#endif  

#ifndef FF_FFCONFIG_HEADER
#include "config.h"
#else
#include FF_FFCONFIG_HEADER
#endif 

#include FF_DTYPES_HEADER
#include FF_TSIMEM_HEADER
#include FF_GLYPH_HEADER

#ifdef ALGORITHMIC_STYLES

#ifdef ENABLE_POSTHINT_ALGORITHMIC_STYLES
void tsi_SHAPET_BOLD_GLYPH(void  *t2k, tsiMemObject *mem, int16 fontType, int16 UPEM, F16Dot16 params[] );
#else
void tsi_SHAPET_BOLD_GLYPH( GlyphClass *glyph, tsiMemObject *mem, int16 fontType, int16 UPEM, F16Dot16 params[] );
#endif

void tsi_SHAPET_BOLD_METRICS( hmtxClass *hmtx, tsiMemObject *mem, int16 UPEM, F16Dot16 params[] );

#endif 

typedef struct
{
	
	tsiMemObject *mem;
	
} SHAPETClass;


#ifdef __cplusplus
}
#endif  
#endif 


