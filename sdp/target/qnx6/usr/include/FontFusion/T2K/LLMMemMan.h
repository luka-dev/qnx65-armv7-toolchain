/*
 * LLMCharList.h
 * $Header: /home/archive/Panorama/layout/LLManager/hdr/LLMMemMan.h,v 1.6 2007/11/12 04:47:57 himanshu Exp $
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


#ifndef __LLMMEMMAN_HEADER__
#define __LLMMEMMAN_HEADER__

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


typedef struct LLMMemChunk_t LLMMemChunk;
typedef struct LLMMemMan_t LLMMemMan;

struct LLMMemMan_t
{
	
	LLMMemChunk * head;
	tsiMemObject * mem;
	uint32 nodeSize;
};

LLMMemMan * createMemMan(tsiMemObject * mem, uint32 nodeSize, uint32 initNumChunks);
void deleteMemMan (LLMMemMan * memMan);
void resetMemMan (LLMMemMan * memMan);
uint8 * newMemListNode(LLMMemMan * memMan);
int  deleteMemListNode(LLMMemMan * memMan, uint8 * node);

#ifdef __cplusplus
}
#endif


#endif 



