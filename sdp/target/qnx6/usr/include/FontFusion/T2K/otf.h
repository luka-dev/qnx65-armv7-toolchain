/*
 * otf.h
 * $Header: /home/archive/Panorama/layout/otf/hdr/otf.h,v 1.15 2009/04/29 10:52:01 ljoshi Exp $
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

#ifndef __OTF_HEADER__
#define __OTF_HEADER__

#ifndef LLM_LLCONFIG_HEADER
#include "LLConfig.h"
#else
#include LLM_LLCONFIG_HEADER
#endif 
#include FF_T2K_HEADER
#include LLM_OTFSCRIPT_HEADER
#include LLM_OTFLANGSYS_HEADER
#include LLM_OTFFEATURE_HEADER
#ifndef ENABLE_OPENTYPE_SUPPORT
#include LLM_OTFBASETAG_HEADER
#endif 



#define ENABLE_GDEF_CACHING
#define ENABLE_GDEF_EXTENDEDCACHING

#ifdef ENABLE_OTF

typedef enum
{
#ifdef ENABLE_OTF_GPOS
	LLM_GPOS_INDEX = 0,
#endif 

#ifdef ENABLE_OTF_GSUB
	LLM_GSUB_INDEX = 1,
#endif 

	LLM_GSUB_GPOS_MAX_INDEX = 2
} LLM_GSUBPOS_INDEX;

#define LLM_GET_GSUB gsubpos[LLM_GSUB_INDEX]
#define LLM_GET_GPOS gsubpos[LLM_GPOS_INDEX]



#define LLMMakeTag(t1, t2, t3, t4) ( (((uint32)t1 & 0xff) << 24) | \
	                              (((uint32)t2 & 0xff) << 16) | \
								  (((uint32)t3 & 0xff) << 8) | \
								  (((uint32)t4 & 0xff) ))


#define tag_JSTF				LLMMakeTag('J','S','T','F')  
#define tag_GDEF                LLMMakeTag('G','D','E','F')  
#define tag_BASE                LLMMakeTag('B','A','S','E')  


#if defined(ENABLE_OTF_GSUB) || defined(ENABLE_OTF_GPOS)




typedef struct FeatureRecord_t
{
   uint16 lookupCount;

   
	uint8 isApplied;

   
    uint8 isAppliedBack;

   
    uint16 * lookupIndex;

   
    const OTFFeatureTag * featureTag;

} FeatureRecord;


typedef struct
{

	uint16 featureCount;
    FeatureRecord * featureRecord;

}FeatureList;


typedef struct {

	
	const OTFLangsysTag * languageTag;

	
	uint16 featureCount;
	FeatureRecord ** featureRecords;
	uint16 reqFeatureIndex;

} LangSysRecord;



typedef struct {

	
	const OTFScriptTag * scriptTag;

	
	LangSysRecord defaultLangSys;
	uint16 langSysCount;
	LangSysRecord * langSysRecord;

	
	uint16 offset;

}ScriptTable;



typedef struct {

	uint16 scriptCount;
	ScriptTable * scriptTable;

}ScriptList;


typedef struct
{
	
	uint32 offset;

	uint16 lookupType;
	
	uint16 lookupFlag;

	
	uint8 isPresent;

	uint16 subTableCount;

	
	uint16 * subTable;

} LookupTable;


typedef struct {

	
	uint16 lookupCount;

	
	LookupTable * lookupTable;

} LookupList;


typedef struct
{
	uint32 selfOffset;
	uint16 scriptListOffset;
	uint16 featureListOffset;
	uint16 lookupListOffset;
	uint16 gdefOffset;

	
	InputStream * lookupIn;

	
	ScriptList * scriptList;
	FeatureList *featureList;
	LookupList * lookupList;

	
	ScriptTable * aciveScript;
	LangSysRecord * activeLang;

}gsubposClass;


typedef  gsubposClass gposClass;

#ifdef ENABLE_OTF_GSUB
typedef  gsubposClass gsubClass;
#endif 

#endif 

#ifdef ENABLE_OTF_GDEF
#ifdef ENABLE_GDEF_EXTENDEDCACHING
typedef struct otfGdefRange_t
{
	uint16 start;
	uint16 end;
	uint16 classType;
}OTFGdefRange;
#endif 


typedef struct {

	
	InputStream * in;

	uint16 glyphClassDef;
	uint16 attachList;
	uint16 ligCaretList;
	uint16 markAttachClassDef;

	
	uint32 selfOffset;
	
#ifdef ENABLE_GDEF_CACHING
	uint16 classFormat;
	uint16 startGlyph;
	uint16 glyphCount;
#ifdef ENABLE_GDEF_EXTENDEDCACHING
	OTFGdefRange *range;
#endif 
#endif 

} gdefClass;

#endif 

#ifdef ENABLE_OTF_JSTF



typedef struct {

	
	uint32 selfOffset;

	
	uint16 jstfPriorityCnt;

	
	uint16 * jstfPriority;

}JstfLangSys;



typedef struct
{

	
	const OTFLangsysTag * langsysTag;

	
	JstfLangSys  jstfLangSys;

} JstfLangSysRecord;



typedef struct
{
	uint16 glyphCount;

	
	uint16 * extenderGlyphID;

}ExtenderGlyphTable;


typedef struct
{
	
	ExtenderGlyphTable * extenderGlyphTable;

	
	JstfLangSys * defJstfLangSys;

	
	uint16 jstfLangSysCount;

	
	JstfLangSysRecord * jstfLangSysRecord;

}JstfScriptTable;


typedef struct
{
	
	JstfScriptTable jstfScriptTable;

	
	const OTFScriptTag * scriptTag;

}JSTFScriptRecord;



typedef struct {


	
	JSTFScriptRecord * jstfScriptRecord;

	
	uint16 jstfScriptCount;

	
	InputStream * in;

	
	uint32 selfOffset;

	
	JstfScriptTable * activeScript;
	JstfLangSys * activeLang;

} jstfClass;

#endif 

#ifdef ENABLE_OTF_BASE


typedef struct
{
	
	uint16 baseTagCount;

	

} BaseTagList;


typedef struct
{

	
	uint32 selfOffset;

	
	uint16 defaultIndex;

	
	uint16 baseCoordCount;

	
	uint16 * baseCoord;

}BaseValues;


typedef struct
{
	
	const OTFFeatureTag * featureTag;

	
	uint16 minCoord;

	
	uint16 maxCoord;

} FeatMinMaxRecord;


typedef struct
{

	

	
	uint32 selfOffset;

	
	uint16 minCoord;

	
	uint16 maxCoord;

	
	uint16 featMinMaxCount;

	
	FeatMinMaxRecord * featMinMaxRecord;

}MinMax;


typedef struct
{
	
	const OTFLangsysTag * languageTag;

	
	MinMax minMax;

}BaseLangSysRecord;


typedef struct
{

	
	BaseValues * baseValues;

	
	MinMax * defaultMinMax;

	
	uint16 baseLangSysCount;

	
	BaseLangSysRecord * baseLangSysRecord;

}BaseScript;


typedef struct
{
	
	const OTFScriptTag * scriptTag;

	BaseScript * baseScript;

}BaseScriptRecord;


typedef struct
{
	

	
	uint16 baseTagCount;

	
	 OTFBaseTag ** baseTagArray;

	
	uint16 baseScriptCount;

	
	BaseScriptRecord * baseScriptRecord;

}AxisTable;


typedef struct
{
	
	AxisTable * horizAxis;
	AxisTable * vertAxis;

	
	uint32 selfOffset;

	
	InputStream * in;

}baseClass;

#endif 


typedef struct
{

	uint16* gidArray;
	uint16 length;
	void* args;

	
	int (* method)(uint16 *gidArray, uint16 length, void * args);

}AltCallback;


typedef struct
{
	
	gsubposClass *gsubpos[LLM_GSUB_GPOS_MAX_INDEX];

#ifdef ENABLE_OTF_GDEF
	
	gdefClass * gdef;
#endif 

#ifdef ENABLE_OTF_JSTF
	
	jstfClass * jstf;
#endif 

#ifdef ENABLE_OTF_BASE
	
	baseClass *base;
#endif 

	
	InputStream		*in;

	
	tsiMemObject	*mem;

#ifdef ENABLE_ALTGLYPH_CALLBACK
	
	AltCallback * altCallback;
#endif 

}otfClass;

#endif 
#endif 



