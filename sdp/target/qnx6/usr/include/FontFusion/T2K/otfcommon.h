/*
 * otfcommon.h
 * $Header: /home/archive/Panorama/layout/otf/hdr/otfcommon.h,v 1.25 2009/04/29 10:53:13 ljoshi Exp $
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

#ifndef __OTFCOMMON_HEADER__
#define __OTFCOMMON_HEADER__

#ifndef LLM_LLCONFIG_HEADER
#include "LLConfig.h"
#else
#include LLM_LLCONFIG_HEADER
#endif 
#include FF_DTYPES_HEADER
#include FF_TSIMEM_HEADER
#include FF_T2KSTRM_HEADER
#include FF_TRUETYPE_HEADER
#include FF_ORION_HEADER
#include FF_UTIL_HEADER
#include FF_AUTOGRID_HEADER
#include FF_GHINTS_HEADER
#include LLM_OTF_HEADER
#include LLM_LLMTYPES_HEADER

#ifdef ENABLE_OTF

#ifdef __cplusplus
extern "C" {
#endif 

#ifndef TRUE
#define TRUE 1
#endif 

#ifndef FALSE
#define FALSE 0
#endif 


#define LLM_NULL_OFFSET 0


#define LLM_MAX_NESTING 5

#define IncCheckNesting( nestValue)  \
    \
  nestValue ++;                      \
  if (nestValue > LLM_MAX_NESTING)       \
  {                                  \
      return FALSE;                  \
  }



#ifdef ENABLE_OTF_DEBUG
#define validAssert(condition) CLIENT_ASSERT(condition)
#else
#define validAssert( condition )    \
	if(!(condition))                \
	{                               \
	    return 0;                   \
	}
#endif 


#define GetStringFromTag( tag, string)		\
											\
	string[0] = (char)((tag >> 24) & 0xff);	\
	string[1] = (char)((tag >> 16) & 0xff);	\
	string[2] = (char)((tag >> 8 ) & 0xff);	\
	string[3] = (char)((tag      ) & 0xff);	\
	string[4] = 0;


typedef enum {

	enXPlacement = 0x0001,
	enYPlacement = 0x0002,
	enXAdvance   = 0x0004,
	enYAdvance   = 0x0008,
	enXPlaDevice = 0x0010,
	enYPlaDevice = 0x0020,
	enXAdvDevice = 0x0040,
	enYAdvDevice = 0x0080,
	enValueFormatReserved   = 0xF000
}ValueFormat;



#define hasXPlacement(valueFormat) ((valueFormat) & enXPlacement)
#define hasYPlacement(valueFormat) ((valueFormat) & enYPlacement)
#define hasXAdvance(valueFormat)   ((valueFormat) & enXAdvance)
#define hasYAdvance(valueFormat)   ((valueFormat) & enYAdvance)
#define hasXPlaDevice(valueFormat) ((valueFormat) & enXPlaDevice)
#define hasYPlaDevice(valueFormat) ((valueFormat) & enYPlaDevice)
#define hasXAdvDevice(valueFormat) ((valueFormat) & enXAdvDevice)
#define hasYAdvDevice(valueFormat) ((valueFormat) & enYAdvDevice)

#define LLM_Assert( t, cond, errcode )			\
if ( FALSE == cond )							\
{												\
	llm_Error( t, errcode );					\
}


typedef enum {

	LLMLookUpFlagMaskRightToLeft    = 0x0001,
	LLMLookUpFlagIgnoreBaseGlyphs   = 0x0002,
	LLMLookUpFlagIgnoreLigatures    = 0x0004,
	LLMLookUpFlagIgnoreMarks        = 0x0008,
	LLMLookUpFlagLookupFlagReserved = 0x00F0,
	LLMLookUpFlagMarkAttachmentType = 0xFF00,
	
	
	LLMLookUpFlagIgnoreMask			= LLMLookUpFlagIgnoreBaseGlyphs | LLMLookUpFlagIgnoreLigatures | LLMLookUpFlagIgnoreMarks

}LLMLookupFlagBit;



#define isLFRightToLeft(__flag)			((__flag) & LLMLookUpFlagRightToLeft)
#define isLFIgnoreBaseGlyphs(__flag)	((__flag) & LLMLookUpFlagIgnoreBaseGlyphs)
#define isLFIgnoreLigatures(__flag)		((__flag) & LLMLookUpFlagIgnoreLigatures)
#define isLFIgnoreMasks(__flag)			((__flag) & LLMLookUpFlagIgnoreMarks)
#define isLFReserved(__flag)			((__flag) & LLMLookUpFlagLookupFlagReserved)
#define isLFMarkAttachmentType(__flag)	((__flag) & LLMLookUpFlagMarkAttachmentType)



typedef struct
{
	
	uint16 valueFormat;

	
	int16 xPlacement;
	int16 yPlacement;

	
	int16 xAdvance;
	int16 yAdvance;

	
	uint16 xPlaDevice;
	uint16 yPlaDevice;

	
	uint16 xAdvDevice;
	uint16 yAdvDevice;

	
	uint32 selfOffset;

}ValueRecord;


typedef struct {

	uint16 format; 

	
	int16 xCoordinate;
	int16 yCoordinate;

	
	uint16 component1;

	
	uint16 component2;

	
	uint32 selfOffset;

}AnchorTable;



typedef struct
{

	
	
	F16Dot16 xPos;
	F16Dot16 yPos;

	
	
	F16Dot16 xAdvance;
	F16Dot16 yAdvance;

	
	
	

	
	
	
	
	uint8 isAbsolute;
	

	
	uint8 type;

	
	LLMGid glyphID;

}ReposData;


#define setGsubScriptLang( otf, script, lang) setGsubposScriptLang (otf, script, lang, 1)
#define setGposScriptLang( otf, script, lang) setGsubposScriptLang (otf, script, lang, 0)


void
LoadOTFTables ( otfClass *otf , sfntClass * font, void * ph);


void
DeleteOTFTables ( otfClass *otf );

otfClass *
CreateOtfClass ( tsiMemObject *mem , InputStream *in);

void
DeleteOtfClass ( otfClass * otf, tsiMemObject *mem);

#ifdef ENABLE_OTF_GPOS

uint8
getValueRecordLength(uint16 valueFormat);



int
getAnchorTable(InputStream * in, AnchorTable *anchorTable);



int
getValueRecord(InputStream * in, uint16 valueFormat, ValueRecord *valueRecord);


int
getDeviceValue(InputStream *in, int32 ppemSize, int16 * value);

int
LLM_GetContourCoords (void * llManager, LLMGid, uint16 index, uint16 * xValue, uint16 * yValue);

void
LLM_TransformXFunits( void *, int16, F16Dot16 *, F16Dot16 *);

ReposData *
LLM_NewReposData(void * manager);
	
void
LLM_DeleteReposData(void * manager, ReposData ** reposData);
#endif 
	
uint16
LLM_GetGid( void * manager, LLMUnicode unicode);

T2K *
LLM_GetUpdatedScaler(void * manager);

#ifdef ENABLE_SHAPING
const FeatureRecord *
getFeatureRecord ( otfClass * otf, const LangSysRecord * langRecord, uint32 tag, uint8 isGSUB);

const LangSysRecord *
getLangSysRecord ( otfClass *, uint32 scriptTag, uint32 tag, uint8 isGSUB);
#endif 

#ifdef ENABLE_CHECK_TAG_CASE
uint32
LLM_getNormalizedTag(uint32);

uint32
LLM_getNormalizedTagToCaps(uint32);
#endif 
	
void llm_Error(LLMEnv *t, int errcode);
	
#define LLM_DECL_LLOKUP_METHOD_TYPE																\
	typedef uint16 (* applyLookupTypeMethod) (otfClass *, InputStream *, PlaceHolder *, uint16);

#define LLM_GSUB_LOOKUP_METHOD applyLookupTypeMethod
#define LLM_GPOS_LOOKUP_METHOD applyLookupTypeMethod	


#define LLM_REFER_GSUB_LOOKUP(__type)	gsubLookupType##__type
#define LLM_DEFINE_GSUB_LOOKUP(__type)	static uint16 gsubLookupType##__type (otfClass *otf, InputStream * in, PlaceHolder * ph, uint16 nestingLevel)
#define LLM_REFER_GPOS_LOOKUP(__type)	gposLookupType##__type
#define LLM_DEFINE_GPOS_LOOKUP(__type)	static uint16 gposLookupType##__type (otfClass *otf, InputStream * in, PlaceHolder * ph, uint16 nestingLevel)
#define LLM_OTF_LOOKUPARRAY(__type) LLMLookupApplyMethodArray##__type
#define LLM_OTF_CALL_GSUB_LOOKUP(__ltype, __otf, __in, __ph, __nLevel) LLM_OTF_CALL_LOOKUP(GSUB, __ltype, __otf, __in, __ph, __nLevel)
#define LLM_OTF_CALL_GPOS_LOOKUP(__ltype, __otf, __in, __ph, __nLevel) LLM_OTF_CALL_LOOKUP(GPOS, __ltype, __otf, __in, __ph, __nLevel)	
#define LLM_OTF_CALL_LOOKUP(__type, __ltype, __otf, __in, __ph, __nLevel) LLMLookupApplyMethodArray##__type[__ltype - 1](__otf, __in, __ph, __nLevel)

#ifdef ENABLE_OTF_VALIDATION
#define LLM_REFER_VAL_GSUB_LOOKUP(__type)	validateGSUBLookupType##__type
#define LLM_DEFINE_VAL_GSUB_LOOKUP(__type)	static int validateGSUBLookupType##__type (InputStream * in, PlaceHolder * ph, uint16 nestingLevel)
#define LLM_REFER_VAL_GPOS_LOOKUP(__type)	validateGPOSLookupType##__type
#define LLM_DEFINE_VAL_GPOS_LOOKUP(__type)	static int validateGPOSLookupType##__type (InputStream * in, PlaceHolder * ph, uint16 nestingLevel)
#endif 
	
#ifdef ENABLE_CHECK_TAG_CASE
#define LLM_NORMALIZE_TAG(__t)	__t = LLM_getNormalizedTag(__t)
#define LLM_NORMALIZE_TAG_TO_CAPS(__t) __t = LLM_getNormalizedTagToCaps(__t)
#else
#define LLM_NORMALIZE_TAG(__t)
#define LLM_NORMALIZE_TAG_TO_CAPS(__t)
#endif 

	
#ifdef ENABLE_LLM_SELF_VALIDATION
void
LLM_validateStaticData();
#endif 

	
#ifdef __cplusplus
}
#endif 
#endif 

#endif 


