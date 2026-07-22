/*
 * otfscript.h
 * $Header: /home/archive/Panorama/layout/otf/hdr/otfscript.h,v 1.14 2008/06/11 02:44:32 ljoshi Exp $
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

#ifndef __OTFSCRIPT_HEADER__
#define __OTFSCRIPT_HEADER__

#ifdef __cplusplus
extern "C" {
#endif 

#ifndef LLM_LLCONFIG_HEADER
#include "LLConfig.h"
#else
#include LLM_LLCONFIG_HEADER
#endif 
#include FF_DTYPES_HEADER

#if defined(ENABLE_LLE) && defined(ENABLE_OTF)


typedef enum {
	 LLM_SCR_NONE   = 0xFF	,
	 LLM_SCR_ARABIC =  0	,
	 LLM_SCR_ARMENIAN		,
	 LLM_SCR_BALINESE		,
	 LLM_SCR_BENGALI		,
	 LLM_SCR_BOPOMOFO		,
	 LLM_SCR_BRAILLE		,
	 LLM_SCR_BUGINESE		,
	 LLM_SCR_BUHID			,
	 LLM_SCR_BYZANTINE_MUSIC,
	 LLM_SCR_CANADIAN		,
	 LLM_SCR_CHEROKEE		,
	 LLM_SCR_CJK			,
	 LLM_SCR_COPTIC			,
	 LLM_SCR_CYRILLIC		,
	 LLM_SCR_DEFAULT		,
	 LLM_SCR_DEVANAGARI		,
	 LLM_SCR_ETHIOPIC		,
	 LLM_SCR_GEORGIAN		,
	 LLM_SCR_GLAGOLITIC		,
	 LLM_SCR_GREEK			,
	 LLM_SCR_GUJARATI		,
	 LLM_SCR_GURMUKHI		,
	 LLM_SCR_JAMO			,
	 LLM_SCR_HANGUL			,
	 LLM_SCR_HANUNOO		,
	 LLM_SCR_HEBREW			,
	 LLM_SCR_HIRAGANA		,
	 LLM_SCR_KANNADA		,
	 LLM_SCR_KATAKANA		,
	 LLM_SCR_KHMER			,
	 LLM_SCR_LAO			,
	 LLM_SCR_LATIN			,
	 LLM_SCR_LIMBU			,
	 LLM_SCR_MALAYALAM		,
	 LLM_SCR_MONGOLIAN		,
	 LLM_SCR_MYANMAR		,
	 LLM_SCR_NKO			,
	 LLM_SCR_OGHAM			,
	 LLM_SCR_ORIYA			,
	 LLM_SCR_PHAG			,
	 LLM_SCR_PHOENICIAN		,
	 LLM_SCR_PRIVATE		,
	 LLM_SCR_RUNIC			,
	 LLM_SCR_SINHALA		,
	 LLM_SCR_SYLOTI			,
	 LLM_SCR_SYRIAC			,
	 LLM_SCR_TAGALOG		,
	 LLM_SCR_TAGBANWA		,
	 LLM_SCR_TAILE			,
	 LLM_SCR_TAILU			,
	 LLM_SCR_TAMIL			,
	 LLM_SCR_TELUGU			,
	 LLM_SCR_THAANA			,
	 LLM_SCR_THAI			,
	 LLM_SCR_TIBETAN		,
	 LLM_SCR_TIFINAGH		,
	 LLM_SCR_YI				,
	 
	 LLM_MAX_OTF_SCRIPT_ID

}LLMScriptName;



typedef struct {

	uint32 tag;
#ifdef ENABLE_OTFTAGS_STRINGS
	char * name;
#endif 
	LLMScriptName id;

} OTFScriptTag;

int
LLMisScriptRtoL(LLMScriptName scriptName);

int
LLMisScriptComplex(LLMScriptName scriptName);

#ifdef LLM_USE_SEAT_BELTS	
uint8
LLMgetScriptSyllableLookupMask(LLMScriptName scriptName);
#endif 
	

const OTFScriptTag *
getScriptFromTag(uint32 tag);



const OTFScriptTag *
getScriptFromID(LLMScriptName id);

#endif 

#ifdef __cplusplus
}
#endif 

#endif 



