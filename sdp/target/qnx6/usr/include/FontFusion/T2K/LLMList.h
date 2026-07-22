/*
 * LLMCharList.h
 * $Header: /home/archive/Panorama/layout/LLManager/hdr/LLMList.h,v 1.17 2009/04/16 11:52:32 ljoshi Exp $
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


#ifndef __LLMCHARLIST_HEADER__
#define __LLMCHARLIST_HEADER__

#ifdef __cplusplus
extern "C" {
#endif


#ifndef LLM_LLCONFIG_HEADER
#include "LLConfig.h"
#else
#include LLM_LLCONFIG_HEADER
#endif 
#include FF_DTYPES_HEADER
#include FF_T2K_HEADER

#include LLM_OTFCOMMON_HEADER
#include LLM_LLMMEMMAN_HEADER

typedef struct LLMListNode_t LLMListNode;
typedef struct GidListNode_t GidListNode;
typedef struct UniListNode_t UniListNode;
typedef struct LLMFeatureTag_t LLMFeatureTag;

#ifdef ENABLE_ACCURATE_DYNAMIC_METRICS
#define LLM_AW_TYPE		F16Dot16
#else
#define LLM_AW_TYPE		uint16
#endif 


struct LLMListNode_t
{
	LLMListNode * prev;
	LLMListNode * next;
};

typedef struct
{

	UniListNode * uLink;

	LLMGid gid;
	uint16 x;
	uint16 width;
	uint16 height;
	int16 ascent;
	int16  fLeft;
	LLM_AW_TYPE aw;
	LLMFeatureTag * gsubTags;

	
	ReposData * rData;

#ifdef ENABLE_BIDIR
	GidListNode * dNext;
	GidListNode * dPrev;

	uint8  bLevel;
	uint8  bType;
	uint8  unidata;
#endif 

	
#ifdef ENABLE_MANUAL_POSITIONING
	uint8  relData;
#endif 
	
#ifdef ENABLE_FRACTIONAL_SIZE
	int8 fracX;
#ifdef ENABLE_Y_FRAC
	int8 fracY;
#endif 
#endif 
	
}GidListNodeData;

struct GidListNode_t
{
	
	GidListNode * prev;
	GidListNode * next;
	GidListNodeData data;
};

#define SET_SYLLABLE_START(_cNode) ((_cNode)->data.syllFlags = (uint16)((_cNode)->data.syllFlags | 0x01))
#define SET_SYLLABLE_END(_cNode) ((_cNode)->data.syllFlags = (uint16)((_cNode)->data.syllFlags | 0x02))
#define SET_SYLLABLE_START_END(_cNode) ((_cNode)->data.syllFlags = (uint16)0x03)
#define RESET_SYLLABLE_START_END(_cNode) ((_cNode)->data.syllFlags = (uint16)0x00)
#define GET_SYLLABLE_START(_cNode) ((_cNode)->data.syllFlags & 0x01)
#define GET_SYLLABLE_END(_cNode) ((_cNode)->data.syllFlags & 0x02)

#define LLMADDNODEL(__h, __t, __m)	llmAddNodeL((LLMListNode **)(void *)__h,  (LLMListNode **)(void *)__t, __m)
	
#define LLMADDAFTERNODEL(__n, __h, __t, __s, __e, __m)		\
		llmAddAfterNodeL(	(LLMListNode  *)(void *)__n,	\
							(LLMListNode **)(void *)__h,	\
							(LLMListNode **)(void *)__t,	\
							(LLMListNode **)(void *)__s,	\
							(LLMListNode **)(void *)__e,	\
							__m)

#define LLMADDBEFORENODEL(__n, __h, __t, __s, __e, __m)		\
		llmAddBeforeNodeL(	(LLMListNode  *)(void *)__n,	\
							(LLMListNode **)(void *)__h,	\
							(LLMListNode **)(void *)__t,	\
							(LLMListNode **)(void *)__s,	\
							(LLMListNode **)(void *)__e,	\
							__m)

#define LLMDELETENODEL(__n, __h, __t, __s, __e, __m)		\
		llmDeleteNodeL(		(LLMListNode  *)(void *)__n,	\
							(LLMListNode **)(void *)__h,	\
							(LLMListNode **)(void *)__t,	\
							(LLMListNode **)(void *)__s,	\
							(LLMListNode **)(void *)__e,	\
							__m)

typedef struct
{
	GidListNode * gLink;
	LLMUnicode unicode;
	uint16 index;
	
	
	
	uint16 syllFlags;
}UniListNodeData;

struct UniListNode_t
{
	
	UniListNode * prev;
	UniListNode * next;
	UniListNodeData data;
};








GidListNode * addGidListNode(GidListNode ** head, GidListNode ** tail, LLMMemMan * memMan);
GidListNode * addBeforeGidListNode(GidListNode * pNode, GidListNode ** pHead, GidListNode ** pTail, GidListNode **pStart, GidListNode **pEnd, LLMMemMan * memMan);
GidListNode * addAfterGidListNode(GidListNode * pNode, GidListNode ** pHead, GidListNode ** pTail, GidListNode **pStart, GidListNode **pEnd, LLMMemMan * memMan);


LLMListNode * llmAddNodeL(LLMListNode ** head, LLMListNode ** tail, LLMMemMan * memMan);
LLMListNode * llmAddAfterNodeL(LLMListNode * pNode, LLMListNode ** pHead, LLMListNode ** pTail, LLMListNode ** pStart, LLMListNode ** pEnd, LLMMemMan * memMan);
LLMListNode * llmAddBeforeNodeL(LLMListNode * pNode, LLMListNode ** pHead, LLMListNode ** pTail, LLMListNode ** pStart, LLMListNode ** pEnd, LLMMemMan * memMan);
LLMListNode * llmDeleteNodeL(LLMListNode * pNode, LLMListNode ** pHead, LLMListNode ** pTail, LLMListNode ** pStart, LLMListNode ** pEnd, LLMMemMan * memMan);


#ifdef __cplusplus
}
#endif


#endif 



