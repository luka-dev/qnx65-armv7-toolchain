/*
 * gdef.h
 * $Header: /home/archive/Panorama/layout/otf/hdr/gdef.h,v 1.12 2008/07/08 08:28:27 ljoshi Exp $
 * Font Fusion Copyright (c) 1989-2004 all rights reserved by Bitstream Inc.
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

#ifndef __GDEF_HEADER__
#define __GDEF_HEADER__


#ifndef LLM_LLCONFIG_HEADER
#include "LLConfig.h"
#else
#include LLM_LLCONFIG_HEADER
#endif 
#include FF_DTYPES_HEADER
#include FF_TSIMEM_HEADER
#include FF_T2KSTRM_HEADER
#include FF_TRUETYPE_HEADER
#include FF_GLYPH_HEADER
#include LLM_OTFSCRIPT_HEADER
#include LLM_OTF_HEADER


#ifdef __cplusplus
extern "C" {
#endif




typedef enum
{

	DefaultClass	= 0x01,	
	BaseClass		= 0x02,	
	LigatureClass	= 0x04,	
	MarkClass		= 0x08,	
	ComponentClass	= 0x10,	
	InvalidClass	= 0x20  

}ClassType;


uint16
getClassTypeFromIn(InputStream *in, LLMGid glyphID);

#ifdef ENABLE_OTF_GDEF

int
loadGDEF (otfClass *t);


void
deleteGDEF (otfClass *t);

ClassType
getClassType (const otfClass * font, LLMGid glyphID);
	

uint16
getMarkAttachClassType(const otfClass * font, LLMGid glyphID);

#endif 


#ifdef __cplusplus
}
#endif 

#endif 



