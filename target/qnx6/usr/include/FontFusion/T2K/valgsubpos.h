/*
 * valgsubpos.h
 * $Header: /home/archive/Panorama/layout/otf/hdr/valgsubpos.h,v 1.9 2008/03/05 10:14:15 ljoshi Exp $
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

#ifndef __VALGSUBPOS_HEADER__
#define __VALGSUBPOS_HEADER__


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
#include LLM_PLACER_HEADER


#ifdef ENABLE_LLE
#ifdef ENABLE_OTF_VALIDATION


#if defined(ENABLE_OTF_GSUB) || defined(ENABLE_OTF_GPOS)

#ifdef __cplusplus
extern "C" {
#endif

typedef int (* validateLookupTypeMethod) (InputStream *, PlaceHolder * ph, uint16 nestingLevel);





int
isScriptListValid ( gsubposClass *t, InputStream * in, PlaceHolder * ph);

int
isFeatureListValid ( gsubposClass *t, InputStream * in, PlaceHolder * ph);



int
validateLoadedGSUBPOS(ScriptList *scriptList, FeatureList *featureList, LookupList *lookupList);


int validateGSUB(otfClass *t, PlaceHolder * ph);

int validateSequence(InputStream *in);
int validateSubRuleSet(InputStream * in);
int validateSubClassRuleSet(InputStream * in);
int validateChainSubRuleSet(InputStream * in);
int validateLig(InputStream * in);
int validateSubRule(InputStream * in);
int validateSubClassRule(InputStream * in);
int validateChainSubRule(InputStream * in);
int validateChainSubClassRuleSet(InputStream * in);
int validateChainSubClassRule(InputStream * in);
int validateCoverage (InputStream * in, PlaceHolder * ph);




int validateGPOS(otfClass *t, PlaceHolder * ph);

#ifdef __cplusplus
}
#endif 

#endif 
#endif 

#endif 

#endif 



