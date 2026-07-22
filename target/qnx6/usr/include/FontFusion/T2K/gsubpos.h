/*
 * gsubpos.h
 * $Header: /home/archive/Panorama/layout/otf/hdr/gsubpos.h,v 1.15 2009/04/29 10:50:55 ljoshi Exp $
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

#ifndef __GSUBPOS_HEADER__
#define __GSUBPOS_HEADER__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef LLM_LLCONFIG_HEADER
#include "LLConfig.h"
#else
#include LLM_LLCONFIG_HEADER
#endif 
#include FF_T2K_HEADER
#include FF_TRUETYPE_HEADER
#include LLM_PLACER_HEADER
#include FF_TT_PRVT_HEADER
#include LLM_OTF_HEADER


#ifdef ENABLE_LLE



#if defined(ENABLE_OTF_GSUB) || defined(ENABLE_OTF_GPOS)

#define deleteGSUB(font) deleteGSUBPOS(font, 1)
#define deleteGPOS(font) deleteGSUBPOS(font, 0)


int
loadGSUB(otfClass *t);

int
loadScriptRecord(otfClass * font, InputStream *in, uint8 isGSUB);

int
loadScriptTable(gsubposClass * gsubpos, ScriptTable * script, InputStream * in);

int
loadLangSysTable(gsubposClass * gsubpos, LangSysRecord * langSysRecord, InputStream * in);

int
loadFeature(FeatureRecord * feature, InputStream * in);

int
loadFeatureRecord (otfClass * font, InputStream *in, uint8 isGSUB);

int
loadLookupTable(LookupTable * lookupTable, InputStream * in);

int
loadLookupRecord(otfClass * font, InputStream *in, uint8 isGSUB);


int
applyGSUBLookup(otfClass * font, PlaceHolder * ph);

void
applyGPOSLookup(otfClass * font, PlaceHolder * ph);

void
setGsubposScriptLang( otfClass *t, LLMScriptName script, LLMLangName lang, uint16 isGSUB );

void
applyFeature(FeatureRecord *feature, otfClass * font, PlaceHolder * ph);


uint16
getCoverageCount (InputStream * in);


int getCoverageIndex (InputStream *in, LLMGid glyphID);



void
applyGSUBLookupListFromIndex ( otfClass * font, PlaceHolder * ph, uint16 index );



void
applyGPOSLookupListFromIndex ( otfClass * font, PlaceHolder * ph, uint16 index );


int
loadGPOS(otfClass *t);


void
deleteGSUBPOS(otfClass * font, int isGSUB);

void
deleteScriptRecord(gsubposClass *gSubPos);

void
deleteFeatureRecord(gsubposClass *gSubPos);

void
deleteLookupRecord(gsubposClass *gSubPos);


void
markLookupsFromActiveLang(otfClass *font, uint8 isGSUB);

#ifdef ENABLE_OTF_JSTF

void
backupEnableFlags(otfClass * font, uint8 isGSUB);


void
restoreEnableFlags(otfClass * font, uint8 isGSUB);
#endif 


#define markGSUBLookupsFromActiveLang(font) markLookupsFromActiveLang(font, 1)
#define markGPOSLookupsFromActiveLang(font) markLookupsFromActiveLang(font, 0)


void
applyGsubFeature ( const LangSysRecord * langSysRecord, const LLMFeatureTag * gsubTags, otfClass * font, PlaceHolder * ph);

void
applyGposFeature ( const LangSysRecord * langSysRecord, const LLMFeatureTag * gposTags, otfClass * font, PlaceHolder * ph);

#endif 
#endif 

#ifdef __cplusplus
}
#endif

#endif 




