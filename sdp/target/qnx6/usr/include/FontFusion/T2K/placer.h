/*
 * placer.h
 * $Header: /home/archive/Panorama/layout/otf/hdr/placer.h,v 1.22 2009/01/13 10:29:55 ljoshi Exp $
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

#ifndef __PLACER_HEADER__
#define __PLACER_HEADER__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef LLM_LLCONFIG_HEADER
#include "LLConfig.h"
#else
#include LLM_LLCONFIG_HEADER
#endif 
#include FF_DTYPES_HEADER
#include FF_TSIMEM_HEADER
#include FF_T2KSTRM_HEADER
#include LLM_OTFCOMMON_HEADER
#include LLM_GDEF_HEADER
#include FF_T2K_HEADER
#include LLM_LLMLIST_HEADER


#define LLM_MAX_UNI_SET 8
#define LLM_MAX_GID_SET 7
	
typedef enum
{
	GidCharOne2One,
	GidCharOne2Many,
	GidCharMany2One,
	GidCharMany2Many,

}GidListNodeType;


typedef struct
{
	
	tsiMemObject    *mem;

#ifdef ENABLE_OTF

	
	const otfClass *otf;

	
	const T2K    *scaler;

	
	void * llManager;
	
	
	LLMEnv * llmEnv;

#ifdef ENABLE_EXTRA_OUTARRAY
	
	uint8 * outLoc;
#endif 

	GidListNode ** gStart;
	GidListNode ** gEnd;
	GidListNode ** gHead;
	GidListNode ** gTail;

	UniListNode * uStart;
	UniListNode * uEnd;
	UniListNode ** uHead;
	UniListNode ** uTail;


	GidListNode * cNode;
	LLMMemMan * gListMan;
	LLMMemMan * uListMan;

	LLMFeatureTag * defGsubTags;

	
	uint16 curIndex;

	
	uint16 lookupFlag;
	
#ifdef LLM_USE_SEAT_BELTS
	
	uint8 lookupSyllableMask;
#endif 

	
	uint8 isAltered;

	uint8 complexMatchIndex;
	LLMGid matchPatternGidSet[LLM_MAX_GID_SET];

#endif 

} PlaceHolder;



void
createPlaceHolder(PlaceHolder * ph,
				  UniListNode * uStart,
				  UniListNode * uEnd,
				  GidListNode ** gStart,
				  GidListNode ** gEnd);



void
deletePlaceHolder(PlaceHolder * ph);

#ifdef ENABLE_OTF

void
setFontInfo (PlaceHolder * ph,  const otfClass * otf, const T2K    *scaler);



void
replaceCurGlyph(PlaceHolder * ph, LLMUnicode glyph);


void
skipCurGlyph(PlaceHolder * ph);



void
replaceOneByNumGlyph (PlaceHolder * ph, LLMGid *glyph, uint16 num);
	

void
replaceNumGlyphByNum(PlaceHolder * ph, uint16 numGlyphs, LLMGid * glyphArray, uint16 numNewGlyphs);	



void
skipNumGlyph (PlaceHolder * ph, uint16 num);



LLMGid
getCurGlyph(PlaceHolder *ph);
	
	
void
removeCurGlyph(PlaceHolder *ph);


const GidListNode *
getBackGlyphSeq(PlaceHolder *ph, uint16 backOffset, uint16 count);


const GidListNode *
getAheadGlyphSeq(PlaceHolder *ph, uint16 aheadOffset, uint16 count);



const GidListNode *
getCurGlyphSeq(PlaceHolder *ph);



uint8
ensureAvailableChars(PlaceHolder * ph, uint16 length);



uint8
ensureCoveredChars(PlaceHolder *ph, uint16 length);

LLMGid
peekNextChar(PlaceHolder * ph);


LLMGid
peekLastChar(PlaceHolder * ph);



void
replaceNumGlyphByOne (PlaceHolder * ph, LLMGid glyph, uint16 num);


int
matchPattern(PlaceHolder * ph, otfClass * otf, uint16 compCount, InputStream * in, GidListNode * gStart, GidListNode * gEnd);



int
moveFromCurPosition(PlaceHolder * ph, uint16 offset);


#ifdef ENABLE_OTF_GDEF

int
getLastClassTypeGlyph(PlaceHolder *ph, otfClass * otf, LLMGid *glyphID, ClassType classType );
#endif 



uint16
getCurPosition(PlaceHolder * ph);

void
moveToIndex(PlaceHolder *ph, uint16 index);



void
rewindPlaceHolder(PlaceHolder * ph);


int
matchBackPattern(PlaceHolder * ph, uint16 backOffset, uint16 compCount, InputStream * in);

int
matchAheadPattern(PlaceHolder * ph, uint16 aheadOffset, uint32 compCount, InputStream * in);



int
applyAndGetAnchor(PlaceHolder *ph, AnchorTable *anchorTable,
				  LLMGid glypgID , F16Dot16 *xValue, F16Dot16 *yValue,
				  InputStream * in);



void
applyValueRecord(PlaceHolder *ph, ValueRecord * valueRecord, InputStream *in);




ReposData * getCurReposData(PlaceHolder *ph);


void
setApplyAndMoveByNum( PlaceHolder *ph, uint16 num);


GidListNodeType
getGidNodeType(GidListNode * gNode, GidListNode * gStartNode, GidListNode * gEndNode,
			   UniListNode * uStartNode, UniListNode * uEndNode, LLMListNode ** resNode);

#endif 


int getNumGids(PlaceHolder * ph);

GidListNodeType
getMappingInfoG (GidListNode * gSeed,
				 UniListNode * uStart, UniListNode * uEnd,
				 GidListNode * gStart, GidListNode * gEnd,
				 UniListNode ** uNode1, UniListNode ** uNode2,
				 GidListNode ** gNode1, GidListNode ** gNode2);

GidListNodeType
getMappingInfoU (UniListNode * uSeed,
				 UniListNode * uStart, UniListNode * uEnd,
				 GidListNode * gStart, GidListNode * gEnd,
				 UniListNode ** uNode1, UniListNode ** uNode2,
				 GidListNode ** gNode1, GidListNode ** gNode2);

GidListNodeType
setMappingInfo(UniListNode * uStart, UniListNode * uEnd,
			   GidListNode * gStart, GidListNode * gEnd);

#ifdef __cplusplus
}
#endif

#endif 



