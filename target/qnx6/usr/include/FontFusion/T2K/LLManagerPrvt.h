/*
 * LLManagerPrvt.h
 * $Header: /home/archive/Panorama/layout/LLManager/hdr/LLManagerPrvt.h,v 1.76 2009/04/06 08:44:02 ljoshi Exp $
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


#ifndef __LLMANAGERPRVT_HEADER__
#define __LLMANAGERPRVT_HEADER__

#ifndef LLM_LLCONFIG_HEADER
#include "LLConfig.h"
#else
#include LLM_LLCONFIG_HEADER
#endif 
#include LLM_OTFCOLOR_HEADER
#include LLM_LLMLIST_HEADER
#include LLM_LLMTYPES_HEADER

#ifdef ENABLE_MULTIPLE_INSTANCE
#define LLM_MULTI_INST_VAR static
#else
#define LLM_MULTI_INST_VAR 
#endif 

#ifdef ENABLE_GASP_SUPPORT


#define __glb_cond_000__ (BLACK_AND_WHITE_BITMAP == greyScaleLevel)
#else

#define __glb_cond_000__ (this->aliasMode == LLMNoAntialias)
#endif 

#ifdef ENABLE_DYNAMIC_COLOR
#ifndef ENABLE_LINES_STYLES
#define DECL_DRAWHLINEDYNAMIC(__layout)  void drawHLineDynamic_##__layout (uint16 yCoord, uint16 startx, uint16 width, uint8 lColorR, uint8 lColorG, uint8 lColorB);
#else
#define DECL_DRAWHLINEDYNAMIC(__layout)  void drawHLineDynamic_##__layout (uint16 yCoord, uint16 startx, uint16 width, uint8 lColorR, uint8 lColorG, uint8 lColorB, int drawStyle = 0);
#endif 
#define DECL_CLEARAREADYNAMIC(__layout)  void clearAreaDynamic_##__layout (void * memoryBuffer,int x1,int x2,int y1,int y2);
#define DECL_PLACEGLYPHONBUFFERDYNAMIC(__layout) 	void placeGlyphOnBufferDynamic_##__layout (int32 X, int32 Y);

#define DECL_COLOR_DRIVER(__layout)				\
	DECL_DRAWHLINEDYNAMIC(__layout)				\
	DECL_CLEARAREADYNAMIC(__layout)				\
	DECL_PLACEGLYPHONBUFFERDYNAMIC(__layout)

#define DECLARE_COLOR_DRIVERS	\
	DECL_COLOR_DRIVER(MONO)		\
	DECL_COLOR_DRIVER(GRAY)		\
	DECL_COLOR_DRIVER(888)		\
	DECL_COLOR_DRIVER(666)		\
	DECL_COLOR_DRIVER(565)		\
	DECL_COLOR_DRIVER(555)		\
	DECL_COLOR_DRIVER(332)		\
	DECL_COLOR_DRIVER(323)		\
	DECL_COLOR_DRIVER(233)		\
	DECL_COLOR_DRIVER(A888)	
#else
	#define DECLARE_COLOR_DRIVERS
#endif 

#ifndef ENABLE_DYNAMIC_COLOR
#define PLACE_GLYPH_ON_BUFFER( __x, __y )  this->placeGlyphOnBuffer(__x, __y)
#ifdef ENABLE_LINES_STYLES
#ifdef LLM_NO_COLOR_LCD_FILTERS
#define DRAW_H_LINE(yCoord, startx, width, __lcr, __lcg, __lcb, __style) this->drawHLine(yCoord, startx, width, 0, 0, 0, __style)
#else
#define DRAW_H_LINE(yCoord, startx, width, __lcr, __lcg, __lcb, __style) this->drawHLine(yCoord, startx, width, __lcr, __lcg, __lcb, __style)
#endif 
#else
#ifdef LLM_NO_COLOR_LCD_FILTERS
#define DRAW_H_LINE(yCoord, startx, width, __lcr, __lcg, __lcb, __style) this->drawHLine(yCoord, startx, 0, 0, 0, width)
#else
#define DRAW_H_LINE(yCoord, startx, width, __lcr, __lcg, __lcb, __style) this->drawHLine(yCoord, startx, __lcr, __lcg, __lcb, width)
#endif 
#endif 
#else
#define PLACE_GLYPH_ON_BUFFER( __x, __y )  (this->*placeGlyphOnBuffer)(__x, __y)
#ifdef ENABLE_LINES_STYLES
#define DRAW_H_LINE(yCoord, startx, width, __lcr, __lcg, __lcb, __style) (this->*drawHLine)(yCoord, startx, width, __lcr, __lcg, __lcb, __style)
#else
#define DRAW_H_LINE(yCoord, startx, width, __lcr, __lcg, __lcb, __style) (this->*drawHLine)(yCoord, startx, width, __lcr, __lcg, __lcb)
#endif 
#endif 

#define RealPoint(point) ((point) >> 16)

#define BlendAlpha128( foreColor, backColor, alpha) \
	((((uint32)(128 - alpha) * (backColor)) >> 7) + (((uint32)(alpha) * (foreColor)) >> 7 ))

#define BlendAlpha( ForeColor, BackColor, Alpha) \
	(((((uint32)(256 - Alpha) * (uint32)(BackColor)) + ((uint32)(Alpha) * (uint32)(ForeColor)) ) >> 8) & 0xff)

#define LLM_GET_COLOR_DIST( c1, c2)										\
( (LLM_GET_R(c1) - LLM_GET_R(c2)) * (LLM_GET_R(c1) - LLM_GET_R(c2)) +	\
  (LLM_GET_G(c1) - LLM_GET_G(c2)) * (LLM_GET_G(c1) - LLM_GET_G(c2)) +	\
  (LLM_GET_B(c1) - LLM_GET_B(c2)) * (LLM_GET_B(c1) - LLM_GET_B(c2)) )

#ifndef ABS
#define ABS(x)		(((x)<0)?-(x):(x))
#endif 

#define LLM_GET_COMP_DIST( c1, c2) ABS(((int16)c1) - ((int16)c2))

#define UNICODE_HYPHEN 0x002D
#define UNICODE_SPACE  0x0020
#define UNICODE_TAB    0x0009


#define UNICODE_LINE_BREAK_CR 0x000D
#define UNICODE_LINE_BREAK_LF 0x000A
#define UNICODE_LINE_BREAK_NL 0x0085

#define UNICODE_DOTTED_CIRCLE	0x25CC


#define UNICODE_THAI_YAMAKKAN     0x0E4E
#define UNICODE_THAI_MAI_HAN_AKAT 0x0E31
#define UNICODE_THAI_SARA_AA      0x0E32
#define UNICODE_THAI_SARA_AM      0x0E33
#define UNICODE_THAI_SARA_UEE     0x0E37
#define UNICODE_THAI_MAITAIKHU    0x0E47
#define UNICODE_THAI_NIKHAHIT     0x0E4D
#define UNICODE_THAI_SARA_U       0x0E38
#define UNICODE_THAI_PHINTHU      0x0E3A
#define UNICODE_THAI_YO_YING      0x0E0D
#define UNICODE_THAI_THO_THAN     0x0E10


#define UNICODE_ZWNJ			0x200C 
#define UNICODE_ZWJ				0x200D 
#define UNICODE_LRM				0x200E 
#define UNICODE_RLM				0x200F 
#define UNICODE_LRE				0x202A 
#define UNICODE_RLE				0x202B 
#define UNICODE_PDF				0x202C 
#define UNICODE_LRO				0x202D 
#define UNICODE_RLO				0x202E 
#define UNICODE_NNBSP			0x202F 
#ifdef ENABLE_FORMATTING_UNICODE_SUPPORT
#define UNICODE_FORMATTING_CHAR UNICODE_ZWNJ
#endif 

#ifdef ENABLE_BIDIR
	#define LLM_RUN_DNEXT( __rNode ) (__rNode)->data.dNext
	#define LLM_RUN_DPREV( __rNode ) (__rNode)->data.dPrev
	#define LLM_LINE_START_DRUN( __lNodeData ) (__lNodeData)->dRunStart
	#define LLM_LINE_END_DRUN( __lNodeData ) (__lNodeData)->dRunEnd
#else
	#define LLM_RUN_DNEXT( __rNode ) (__rNode)->next
	#define LLM_RUN_DPREV( __rNode ) (__rNode)->prev
	#define LLM_LINE_START_DRUN( __lNodeData ) (__lNodeData)->runStart
	#define LLM_LINE_END_DRUN( __lNodeData ) (__lNodeData)->runEnd
#endif 

#define LLM_GET_LINE_LINESTYLE(__val, __type)  (LLMLineStyle)(((__val) >> (__type)) & 0x03)
#define LLM_SET_LINE_LINESTYLE(__val, __type, __style)   __val = (uint8)((__val & ~(0x03 << __type))|((__style) << (__type)))

#ifdef ENABLE_PARAGRAPH_SPECIFIC_PROPERTIES
#define GET_REC_LINEGAP(__recNode)              __recNode->data.lineGap
#define GET_REC_BEFOREGAP(__recNode)            __recNode->data.beforeGap
#define GET_REC_AFTERGAP(__recNode)             __recNode->data.afterGap
#define GET_REC_LEFTINDENT(__recNode)			__recNode->data.leftIndent
#define GET_REC_RIGHTINDENT(__recNode)			__recNode->data.rightIndent
#define GET_REC_FIRSTINDENT(__recNode)         __recNode->data.firstLineIndent
#define GET_REC_INDENTSPACE(__recNode)			(__recNode->data.leftIndent + __recNode->data.rightIndent)
#define GET_REC_ALIGNMENT(__recNode)            __recNode->data.alignment
#else
#define GET_REC_LINEGAP(__recNode)              this->lineGap
#define GET_REC_BEFOREGAP(__recNode)            this->beforeRecordGap
#define GET_REC_AFTERGAP(__recNode)             this->afterRecordGap
#define GET_REC_LEFTINDENT(__recNode)			this->leftIndent
#define GET_REC_RIGHTINDENT(__recNode)			this->rightIndent
#define GET_REC_FIRSTINDENT(__recNode)         this->startX
#define GET_REC_INDENTSPACE(__recNode)			this->indentSpace
#define GET_REC_ALIGNMENT(__recNode)            this->lineAlignment
#endif 

#ifdef ENABLE_EXTRA_RUN_PROPS
#define GET_RUN_INTERCHARSPACE(__runNode)       __runNode->data.interCharSpace
#else
#define GET_RUN_INTERCHARSPACE(__runNode)       this->interCharSpace
#endif 

#define LLM_GET_HAS_EXTENDER(_runNode)			((_runNode)->data.flag1 &  0x04)
#define LLM_SET_HAS_EXTENDER(_runNode)			((_runNode)->data.flag1 |= 0x04)
#define LLM_UNSET_HAS_EXTENDER(_runNode)		((_runNode)->data.flag1 &= ~0x04)
#define LLM_GET_NEED_CALLBACK(_runNode)			((_runNode)->data.flag1 & 0x01)
#define LLM_SET_NEED_CALLBACK(_runNode, value)	((_runNode)->data.flag1 |= (value & 0x01))
#define LLM_GET_L_TO_R(_runNode)				((_runNode)->data.flag1 & 0x02)
#define LLM_SET_L_TO_R(_runNode, value)			((_runNode)->data.flag1 |= ((value & 0x01) << 1))

#ifdef ENABLE_LINEGAP
	#define UPDATE_RECORD_BASEY(__recNode)																							\
			__recNode->data.y = (uint16)(__recNode->data.lStart->data.baseY - __recNode->data.lStart->data.ascent + 1 -				\
										 GET_REC_BEFOREGAP(__recNode));																\
			__recNode->data.height = (uint16)(__recNode->data.lEnd->data.baseY +													\
														(__recNode->data.lEnd->data.height - __recNode->data.lEnd->data.ascent) -	\
														__recNode->data.y + 1 + GET_REC_AFTERGAP(__recNode));

#else
	#define UPDATE_RECORD_BASEY(__recNode)																							\
			__recNode->data.y = (uint16)(__recNode->data.lStart->data.baseY - __recNode->data.lStart->data.ascent + 1);				\
			__recNode->data.height = (uint16)(__recNode->data.lEnd->data.baseY +													\
											  (__recNode->data.lEnd->data.height - __recNode->data.lEnd->data.ascent) -	__recNode->data.y + 1 );
#endif 


#ifdef ENABLE_OTF
#define CHECK_FOR_REPOSDATA(tmpNode)										\
		    \
	if((fontInst.isOTF == 1) && (tmpNode->data.rData != NULL))			    \
	{																		\
		if(tmpNode->data.rData->isAbsolute == 0)							\
		{																	\
			this->xAdvanceWidth += tmpNode->data.rData->xAdvance;			\
			this->yAdvanceWidth += tmpNode->data.rData->yAdvance;			\
		}																	\
		else if(tmpNode->data.rData->isAbsolute == 1)						\
		{																	\
			this->xAdvanceWidth = tmpNode->data.rData->xAdvance;			\
			this->yAdvanceWidth = tmpNode->data.rData->yAdvance;			\
		}													\
	}
#else
#define CHECK_FOR_REPOSDATA(glpyhIndex) ;
#endif 

#ifndef ENABLE_TAB_PROCESSING
#define IsSpace(__gNode) (__gNode->data.gid == this->extenderVal.spaceGlyphID)
#else
#define IsSpace(__gNode) ((__gNode->data.gid == this->extenderVal.spaceGlyphID) ||		\
						  ((__gNode->data.uLink != NULL) &&								\
                           ((LLM_IS_WHITESPACE(__gNode->data.uLink->data.unicode)) ||	\
							(LLM_IS_SEGSEP(__gNode->data.uLink->data.unicode)))))
#endif 


#define LLM_GET_UNIDATA_REAL(__unicode)					(uint8)(((uniData[(__unicode) >> 1]) >> (((__unicode) & 1) << 2)) & 0xf)

#ifdef ENABLE_UDB_SUPPORT
#define LLM_GET_UNIDATA(__unicode) LLM_GET_UNIDATA_REAL(__unicode)
#else
#define  LLM_GET_UNIDATA(__unicode) getUniDataValue(__unicode)
#endif 


#define LLM_IS_WHITESPACE( __unicode )			(uint8)(LLM_GET_UNIDATA(__unicode) == 12 )

#define LLM_IS_SEGSEP( __unicode )				(uint8)(LLM_GET_UNIDATA(__unicode) == 11  )

#define LLM_IS_PARAGRAPH_SEPARATOR( __unicode )	(uint8)(LLM_GET_UNIDATA(__unicode) == 13  )

#define LLM_IS_WHITESPACE_UNIVAL( __uniVal )	((__uniVal) == 12 )
#define LLM_IS_STRONG_UNICODE( __uniVal )		(((__uniVal) == 1 ) || ((__uniVal) == 2 ) || ((__uniVal) == 5 ) || ((__uniVal) == 6 ))

#ifdef ENABLE_RUNTIME_METRICSCHECK
#define LLM_UNDERLINE_POS_UPDATE(_lineNode)														\
		if(_lineNode->data.underLinePos < (uint16)(fontInst.scaler->yUnderlinePosition >> 16))	\
		{																						\
			_lineNode->data.underLinePos = (uint16)(fontInst.scaler->yUnderlinePosition >> 16); \
		}
#else
#define LLM_UNDERLINE_POS_UPDATE(_lineNode)
#endif 

#define UPDATE_LLM_LINE( _lineNode, _runNode)																									\
				if((int16)_lineNode->data.ascent < (int16)_runNode->data.ascent)																\
				{																																\
					_lineNode->data.ascent = _runNode->data.ascent;																				\
				}																																\
																																				\
				if(((int)_lineNode->data.height - (int16)_lineNode->data.ascent) < ((int)_runNode->data.height - (int16)_runNode->data.ascent))	\
				{																																\
					_lineNode->data.height = (uint16)(_lineNode->data.ascent + (int16)_runNode->data.height - _runNode->data.ascent) ;			\
				}																																\
				LLM_UNDERLINE_POS_UPDATE(_lineNode)

#ifdef ENABLE_DYNAMIC_RUNCHECK
#define UPDATE_LLM_RUN( _runNode, _gNode)																									\
				if((int16)_runNode->data.ascent < (int16)_gNode->data.ascent)																\
				{																															\
					_runNode->data.ascent = _gNode->data.ascent;																			\
				}																															\
																																			\
				if(((int)_runNode->data.height - (int)_runNode->data.ascent) < ((int)_gNode->data.height - (int16)_gNode->data.ascent))		\
				{																															\
					_runNode->data.height = (uint16)((int16)_runNode->data.ascent + _gNode->data.height - (int16)_gNode->data.ascent) ;		\
				}
#endif 

#ifdef ENABLE_INTERCHAR_SPACING
#define SET_INTERCHARSPACE_FROM_RUN( __runNode ) this->interCharSpace = __runNode->data.interCharSpace
#else
#define SET_INTERCHARSPACE_FROM_RUN( __runNode )
#endif 

#ifdef ENABLE_LINEGAP
#define LLM_CALCULATE_LINE_BASEY(__lNode, __recNode)																											\
		if(__lNode != __recNode->data.lStart)																													\
		{																																					    \
			if(GET_REC_LINEGAP(__recNode) < 1)																												  	\
			{																																				    \
				__lNode->data.baseY = (uint32)(__lNode->prev->data.baseY + __lNode->prev->data.height  - __lNode->prev->data.ascent + __lNode->data.ascent);    \
			}																																				    \
			else																																			    \
			{																																				    \
				__lNode->data.baseY = (uint32)(__lNode->prev->data.baseY + GET_REC_LINEGAP(__recNode));														    \
			}																																    \
		}																																					    \
		else																																				    \
		{																																					    \
			if(__lNode != this->lHead)																															\
			{																																					\
				__lNode->data.baseY = (uint32)(__lNode->prev->data.baseY + __lNode->prev->data.height  - __lNode->prev->data.ascent + __lNode->data.ascent);	\
																																								\
				if(GET_REC_BEFOREGAP(__recNode) > 0)																											\
				{																																				\
					__lNode->data.baseY = (uint32)(__lNode->data.baseY + GET_REC_BEFOREGAP(__recNode));															\
				}																																\
																																								\
				if(__recNode != this->rHead)																													\
				{																																				\
					__lNode->data.baseY = __lNode->data.baseY + GET_REC_AFTERGAP(__recNode->prev);																\
				}																																	\
			}																																					\
			else																																				\
			{																																					\
				__lNode->data.baseY = (uint32)(this->startY + __lNode->data.ascent - 1);																		\
																																								\
				if(GET_REC_BEFOREGAP(__recNode) > 0)																											\
				{																																				\
					__lNode->data.baseY = (uint32)(__lNode->data.baseY + GET_REC_BEFOREGAP(__recNode));															\
				}																																	\
			}																																	\
		}
#else
#define LLM_CALCULATE_LINE_BASEY(__lNode, __recNode)																										\
		if(__lNode != this->lHead)																															\
		{																																					\
			__lNode->data.baseY = (uint32)(__lNode->prev->data.baseY + __lNode->prev->data.height  - __lNode->prev->data.ascent + __lNode->data.ascent);	\
		}																																					\
		else																																				\
		{																																					\
			__lNode->data.baseY = (uint32)(this->startY + __lNode->data.ascent - 1);																		\
		}
#endif 

#ifdef ENABLE_PARAGRAPH_SPECIFIC_PROPERTIES
#ifdef ENABLE_LINEGAP
#define UPDATE_RECORD_LINEGAP(__rec)							\
			__rec->data.lineGap = this->lineGap;				\
			__rec->data.beforeGap = this->beforeRecordGap;		\
			__rec->data.afterGap = this->afterRecordGap;
#else
#define UPDATE_RECORD_LINEGAP(__rec)
#endif 

#ifdef ENABLE_TABSTOP
#define UPDATE_RECORD_TABSTOP(__rec)									\
			__rec->data.tabstopArray = this->tabstopArray;				\
			__rec->data.tabstopArrayLength = this->tabstopArrayLength;
#else
#define UPDATE_RECORD_TABSTOP(__rec)
#endif 

#define UPDATE_RECORD_PROPS(__rec)									\
			__rec->data.alignment = this->lineAlignment;			\
			__rec->data.leftIndent = this->leftIndent;				\
			__rec->data.rightIndent = this->rightIndent;			\
			__rec->data.firstLineIndent = this->startX;				\
			UPDATE_RECORD_LINEGAP(__rec)							\
			UPDATE_RECORD_TABSTOP(__rec)
#else
#define UPDATE_RECORD_PROPS(__rec)
#endif 

#ifdef ENABLE_LLM_EXTENSION
#define RESET_FILTER()\
	this->fontStyle = LLMMaxFontStyles;\
	this->filterParam.filterTag = 0;\
	FF_CM_SetFilter(this->cache, 0, NULL, NULL);

#define LLM_RUN_STYLE oriStyle
#define FONTID_FROM_LLMFONT(_llmFont) (_llmFont - &(this->llmFontArray[0]))

#else
#define RESET_FILTER()
#define LLM_RUN_STYLE style
#endif 

#ifdef ENABLE_MAC_T1
#define LLM_CHECK_AND_LOAD_MAC_T1(__llm, __name, __cnt)																		\
																													\
	if(__cnt == 0)																									\
	{																												\
																					\
		if(__name != NULL)																				\
		{																											\
			FSRef __fsr;																							\
			Boolean __isD;																							\
			uint16 __rfn;																							\
																													\
			if(0 == FSPathMakeRef ((const UInt8 *)__name, &__fsr, &__isD))								\
			{																										\
				__rfn = FSOpenResFile ( &__fsr, 0 );																\
																													\
				if(__rfn > 0)																						\
				{																									\
					__llm->fontBuffer =  (uint8 *)ExtractPureT1FromMacPOSTResources( __llm->mem, __rfn, &__cnt );	\
					CloseResFile(__rfn);																			\
				}																						\
			}																							\
		}																								\
	}
#else
#define LLM_CHECK_AND_LOAD_MAC_T1(__llm, __name, __cnt)
#endif 

#ifdef ENABLE_BIDIR
	#define LLM_GNODE_DNEXT( __gNode ) (__gNode)->data.dNext
	#define LLM_GNODE_DPREV( __gNode ) (__gNode)->data.dPrev

	#define LLM_RUN_START_DGNODE( __rNode ) (__rNode)->data.dgStart
	#define LLM_RUN_END_DGNODE( __rNode ) (__rNode)->data.dgEnd

	#define LLM_RUN_DNEXT( __rNode ) (__rNode)->data.dNext
	#define LLM_RUN_DPREV( __rNode ) (__rNode)->data.dPrev

	#define LLM_LINE_START_DRUN( __lNodeData ) (__lNodeData)->dRunStart
	#define LLM_LINE_END_DRUN( __lNodeData ) (__lNodeData)->dRunEnd
#else
	#define LLM_GNODE_DNEXT( __gNode ) (__gNode)->next
	#define LLM_GNODE_DPREV( __gNode ) (__gNode)->prev
	
	#define LLM_RUN_START_DGNODE( __rNode ) __rNode->data.gStart
	#define LLM_RUN_END_DGNODE( __rNode ) __rNode->data.gEnd

	#define LLM_RUN_DNEXT( __rNode ) (__rNode)->next
	#define LLM_RUN_DPREV( __rNode ) (__rNode)->prev
	
	#define LLM_LINE_START_DRUN( __lNodeData ) (__lNodeData)->runStart
	#define LLM_LINE_END_DRUN( __lNodeData ) (__lNodeData)->runEnd
#endif 

#ifdef ENABLE_BIDIR
#define LLM_SET_GNODE_DPREVNEXT(__gNode, __gHead, __gTail)								\
	__gNode->data.dNext = __gNode->next;												\
	__gNode->data.dPrev = __gNode->prev;												\
																						\
	if(__gNode != *(__gHead))															\
	{																					\
		__gNode->prev->data.dNext = __gNode;											\
	}																					\
																						\
	if(__gNode != *(__gTail))															\
	{																					\
		__gNode->next->data.dPrev = __gNode;											\
	}
#else
#define LLM_SET_GNODE_DPREVNEXT(__gnode, __gHead, __gTail)
#endif 

#define LLM_ADD_AFTER_GID_NODE(__gNode, __tNode, __gHead, __gTail, __gStart, __gEnd, __memMan)						\
	__tNode = (GidListNode *)llmAddAfterNodeL((LLMListNode *)__gNode,												\
											  (LLMListNode **)__gHead,												\
											  (LLMListNode **)__gTail,												\
											  (LLMListNode **)__gStart,												\
											  (LLMListNode **)__gEnd,												\
											  __memMan);															\
	LLM_SET_GNODE_DPREVNEXT(__tNode, __gHead, __gTail)


#define LLM_ADD_BEFORE_GID_NODE(__gNode, __tNode, __gHead, __gTail, __gStart, __gEnd, __memMan)						\
	__tNode = (GidListNode *)llmAddBeforeNodeL((LLMListNode *)__gNode,												\
											   (LLMListNode **)__gHead,												\
											   (LLMListNode **)__gTail,												\
											   (LLMListNode **)__gStart,											\
											   (LLMListNode **)__gEnd,												\
											   __memMan);															\
	LLM_SET_GNODE_DPREVNEXT(__tNode, __gHead, __gTail)

#ifdef ENABLE_BIDIR
#define LLM_SET_GNODE_DPREVNEXT_FOR_DELETION(__gNode, __gHead, __gTail)					\
																						\
	if(__gNode != *(__gHead))															\
	{																					\
		__gNode->prev->data.dNext = __gNode->next;										\
	}																					\
																						\
	if(__gNode != *(__gTail))															\
	{																					\
		__gNode->next->data.dPrev = __gNode->prev;										\
	}
#else
#define LLM_SET_GNODE_DPREVNEXT_FOR_DELETION(__gnode, __gHead, __gTail)
#endif 

#ifdef ENABLE_BIDIR
#define CHECK_RECORD_L2R(__recNode,__lineNode)										\
if((__recNode->data.embedLevel == 0) && (__lineNode->data.isLtoR))					\
{																					\
	unreverseLineForBidi(__recNode, __lineNode, __recNode->data.lEnd);				\
	isLtoR = 1;																		\
}																					\
else if(__recNode->data.embedLevel)													\
{																					\
	unreverseLineForBidi(__recNode, __recNode->data.lStart, __recNode->data.lEnd);	\
	isLtoR = 2;																		\
}



#define REFORMAT_PARA_BIDI(__recNode,__lNode)								\
if(isLtoR)																	\
{																			\
	__recNode->data.embedLevel = LLM_FORMATBIDIRPARA(__recNode->data.lStart->data.runStart->data.gStart, __recNode->data.uEnd->prev->data.gLink, this->bidirControl);	\
	this->assignNodeToRunByLevel(__lNode);									\
	RunListNode * run = __recNode->data.lStart->data.runStart;				\
	RunListNode * endNode = __recNode->data.lEnd->data.runEnd->next;		\
	do																		\
	{																		\
		this->locateRunNodes(run);											\
		run->data.bLevel = run->data.gStart->data.bLevel;					\
		run = run->next;													\
	}while(run != endNode);													\
}
#endif 

#define LLM_DELETE_GID_NODE( __gNode, __tNode, __gHead, __gTail, __gStart, __gEnd, __memMan )		\
		LLM_SET_GNODE_DPREVNEXT_FOR_DELETION(__gNode, __gHead, __gTail)								\
																									\
		__tNode = (GidListNode *)llmDeleteNodeL((LLMListNode*)__gNode,								\
									  (LLMListNode **) __gHead,										\
									  (LLMListNode **) __gTail,										\
									  (LLMListNode **) __gStart,									\
									  (LLMListNode **) __gEnd,										\
									  __memMan);

#define SET_CUR_LAYOUT_PROPS_FROM_RUN( __runNode )								\
				if(this->curFontID != __runNode->data.fontID)					\
				{																\
					selectFont(__runNode->data.fontID);							\
				}													\
																				\
				if(this->fontSize != __runNode->data.size)						\
				{																\
					LLM_SET_SIZE_FROM_RUN(__runNode->data.size);				\
				}													\
																				\
				if(this->fontStyle != __runNode->data.LLM_RUN_STYLE)			\
				{																\
					this->setStyleVector((LLMFontStyle)__runNode->data.LLM_RUN_STYLE);	\
				}													\
																				\
				SET_INTERCHARSPACE_FROM_RUN(__runNode)

#define LLM_FF_ERRCODE_ASSERT	LLM_Assert(&this->llmEnv, this->errCode == 0, this->errCode)
#define LLM_ENV_SETJMP			CLIENT_SETJMP(this->llmEnv.jmpBuf)

struct CharListNode;

typedef struct LineRecListNode_t LineRecListNode;

typedef struct LineListNode_t LineListNode;

typedef struct RunListNode_t RunListNode;





typedef struct
{
	uint16 x;
	uint16 y;
	uint16 height;
	uint16 width;

	uint16 index;

#ifdef ENABLE_PARAGRAPH_SPECIFIC_PROPERTIES
#ifdef ENABLE_LINEGAP
	uint16 lineGap;
	uint16 beforeGap;
	uint16 afterGap;
#endif 

#ifdef ENABLE_TABSTOP
	const LLMTabstop * tabstopArray;
	uint16 tabstopArrayLength;
#endif 
#endif 

	LineListNode * lStart;
	LineListNode * lEnd;
	
	UniListNode * uStart;
	UniListNode * uEnd;
	UniListNode * pBreak;

	uint32 uniStart;
	uint16 lineStart;
	
#ifdef ENABLE_PARAGRAPH_SPECIFIC_PROPERTIES
	uint16 leftIndent;
	uint16 rightIndent;
	uint16 firstLineIndent;
	uint8 alignment;
#endif 

#ifdef ENABLE_BIDIR
	uint8 embedLevel;
#endif 
	
}LogicalLineRecord;



typedef struct
{
	uint16 x;
	uint16 width;
	uint16 ascent;
	uint16 height;
	uint16 numWords;

	
	uint16 index;
	uint32 baseY;	

	 
	RunListNode * runStart;
	RunListNode * runEnd;

#ifdef ENABLE_BIDIR
	RunListNode * dRunStart;
	RunListNode * dRunEnd;
#endif 

	
	LineRecListNode * rec;
	
	
	
	

#ifdef ENABLE_RUNTIME_METRICSCHECK
	uint16 underLinePos;
	uint16 underLineThickness;
#endif 
	
#ifdef ENABLE_BIDIR
	uint8 isLtoR;
#endif 

#ifdef ENABLE_SPACE_WRAP
	uint8 spaceFlag;
#endif 

	uint8 pad;
	
}LayoutLine;


struct LineListNode_t
{
	LineListNode * prev;
	LineListNode * next;
	LayoutLine data;
};

struct LineRecListNode_t
{
	LineRecListNode * prev;
	LineRecListNode * next;
	LogicalLineRecord data;
};


typedef struct
{
	uint16 x;
	uint16 width;
	uint16 height;
	int16 ascent;
	uint16 fontID;
	LLM_FONTSIZE_TYPE size;
	uint16 style;
#ifdef ENABLE_LLM_EXTENSION
	uint16 oriStyle;
#endif 

#ifndef LLM_NO_COLOR_LCD_FILTERS
	LLM_MEM_BUF_TYPE fColor;
	LLM_MEM_BUF_TYPE bColor;
#endif 

	UniListNode * uStart;
	UniListNode * uEnd;
	
	GidListNode * gStart;
	GidListNode * gEnd;

	LineListNode * line;

#ifdef ENABLE_BIDIR
	RunListNode * dPrev;
	RunListNode * dNext;
	
	GidListNode * dgStart;
	GidListNode * dgEnd;
#endif 

#ifdef LLM_NEED_SCRIPT
	uint16 script;
	uint16 lang;
#endif 

	uint16 numGlyphs;

#ifdef ENABLE_EXTRA_RUN_PROPS
#ifdef ENABLE_INTERCHAR_SPACING
	InterCharSpaceType interCharSpace;
#endif 
	int16 deltaY;
#ifdef ENABLE_ANCHOR_RUN
	int16 deltaX;
#endif 
#ifdef ENABLE_LINES_STYLES
	uint8 lineStyle;
#endif 
	
#ifdef ENABLE_LINE_COLOR
	LLM_MEM_BUF_TYPE lineColorArray[3];
#endif 
#endif 
	
	
	
	
	
	uint8 flag1;

#ifdef ENABLE_BIDIR
	uint8 bLevel;
#endif 

#ifdef ENABLE_CUSTOMRUN
	uint16 imageIndex;
	
	
	
	uint8 objType;
#endif 

#ifdef ENABLE_RUN_ANTIALIASED
	uint8 aliasingMode;
#endif 

}LLMRun;

struct RunListNode_t
{
	RunListNode * prev;
	RunListNode * next;

	LLMRun data;
};


struct LLMFeatureTag_t
{
	uint32 tag;
	int8   flag;
};






#ifdef ENABLE_LLM_UNICODE_RANGE

typedef struct
{
	uint16 uniStart;
	uint16 uniEnd;
	uint16 fontID;
}LLMUnicodeRange;

#endif 

typedef struct
{
	F16Dot16 minX;
	F16Dot16 maxAX;
	F16Dot16 maxRX;
	int16 ascent;
	int16 descent;
}LLMMeasureStringParams;

#ifdef ENABLE_DYNAMIC_COLOR




#define GET_FINAL_COLOR_VALUE(R,G,B,__layout,__format)	\
      ( LLM_GET_COLOR_##__layout##_##__format ((LLM_MEM_BUF_TYPE_##__layout)R , (LLM_MEM_BUF_TYPE_##__layout)G , (LLM_MEM_BUF_TYPE_##__layout)B))

#define GET_FINAL_COMP_DIST( c1, c2,__layout,__format) ABS(((int16)c1) - ((int16)c2))

#define GET_FINAL_COLOR_DIST( c1, c2,__layout,__format)																															\
	( (LLM_GET_R_##__layout##_##__format (c1) - LLM_GET_R_##__layout##_##__format (c2)) * (LLM_GET_R_##__layout##_##__format (c1) - LLM_GET_R_##__layout##_##__format (c2)) +	\
	  (LLM_GET_G_##__layout##_##__format (c1) - LLM_GET_G_##__layout##_##__format (c2)) * (LLM_GET_G_##__layout##_##__format (c1) - LLM_GET_G_##__layout##_##__format (c2)) +	\
	  (LLM_GET_B_##__layout##_##__format (c1) - LLM_GET_B_##__layout##_##__format (c2)) * (LLM_GET_B_##__layout##_##__format (c1) - LLM_GET_B_##__layout##_##__format (c2)) )



#endif 

#define LLM_GET_SIZE_ENUMERATE_FONT(__scaler)									\
	if(fontNameStrBuffer == NULL)												\
	{																			\
		if(__scaler->nameString8 != NULL)										\
		{																		\
			strLenSize += ((CLIENT_STRLEN((const char *)__scaler->nameString8)) + 2);	\
		}																		\
		else if (__scaler->nameString16 != NULL)								\
		{																		\
			for(i = 0; (__scaler->nameString16[i] != 0); i++);					\
			strLenSize += (i + 2);												\
		}																		\
		else																	\
		{																		\
			strLenSize ++;														\
		}														\
	}																			\
	else																		\
	{																			\
		if(__scaler->nameString8 != NULL)										\
		{																		\
			temp = __scaler->nameString8;										\
																				\
			for(i=0; (temp[i] != 0); i++)										\
			{																	\
				fontNameStrBuffer[strLenSize] = temp[i];						\
				strLenSize++;													\
			}														\
		}																		\
		else if(__scaler->nameString16 != NULL)									\
		{																		\
			for(i = 0; (__scaler->nameString16[i] != 0); i++)					\
			{																	\
				fontNameStrBuffer[strLenSize] = __scaler->nameString16[i];		\
				strLenSize++;													\
			}														\
		}														\
																				\
		fontNameStrBuffer[strLenSize] = '\0';									\
		strLenSize ++;															\
																				\
	}

#ifdef ENABLE_GASP_SUPPORT
#ifdef USE_FF_LINE_FILTER
#define  __llm_param_gray_sacle_macro_00__		\
	this->filterParam.lineParams.greyScaleLevel = this->greyScaleLevel;
#else
#define  __llm_param_gray_sacle_macro_00__
#endif 

#ifdef ENABLE_T2K_TV_EFFECTS
#define  __llm_param_gray_sacle_macro_01__	\
	this->filterParam.tvfilterParams.greyScaleLevel = this->greyScaleLevel;
#else
#define  __llm_param_gray_sacle_macro_01__
#endif 

#ifdef ENABLE_COLORBORDERS
#define   __llm_param_gray_sacle_macro_02__	\
	this->filterParam.borderParams.greyScaleLevel = this->greyScaleLevel;
#else
#define   __llm_param_gray_sacle_macro_02__
#endif 

#ifdef ENABLE_OUTLINEFILTER
#define  __llm_param_gray_sacle_macro_03__	\
	this->filterParam.outlineParams.greyScaleLevel = this->greyScaleLevel;
#else
#define  __llm_param_gray_sacle_macro_03__
#endif 

#define LLM_SETGRAYSCALE_FILTERPARAMS										\
	this->filterParam.boldParams.greyScaleLevel = this->greyScaleLevel;		\
	 __llm_param_gray_sacle_macro_00__	\
	 __llm_param_gray_sacle_macro_01__	\
	 __llm_param_gray_sacle_macro_02__	\
	 __llm_param_gray_sacle_macro_03__
#endif 

#ifdef ENABLE_ACCURATE_DYNAMIC_METRICS
#define LLM_GNODE_SET_AW_FROM_DEVICE(__aw) (((uint32)(__aw)) << 16)
#define LLM_GNODE_SET_AW_FROM_REAL(__aw) (__aw)
#define LLM_GNODE_GET_AW_DEVICE(__aw) (uint16)((__aw) >> 16)
#define LLM_GNODE_GET_AW_REAL(__aw) (__aw)
#else
#define LLM_GNODE_SET_AW_FROM_DEVICE(__aw) (__aw)
#define LLM_GNODE_SET_AW_FROM_REAL(__aw) (__aw >> 16)
#define LLM_GNODE_GET_AW_DEVICE(__aw) (__aw)
#define LLM_GNODE_GET_AW_REAL(__aw) (__aw << 16)
#endif 

#ifdef ENABLE_DYNAMIC_BIDI_CONTROL
#define LLM_DECL_FORMATBIDIRLINE void formatBidirLine(RunListNode ** , RunListNode ** , RunListNode ** , RunListNode ** , uint8 , LLMBidiControl )
#define LLM_DECL_FORMATBIDIRPARA uint8 formatBidirPara(GidListNode * , GidListNode * , LLMBidiControl)
#define LLM_FORMATBIDIRLINE(__rStart, __rEnd, __rHead, __rTail, __pLevel, __bCtrl)  formatBidirLine(__rStart, __rEnd, __rHead, __rTail, __pLevel, (LLMBidiControl)__bCtrl)
#define LLM_FORMATBIDIRPARA(__pStart, __pEnd, __bCtrl) formatBidirPara(__pStart, __pEnd, (LLMBidiControl)__bCtrl)
#else
#define LLM_DECL_FORMATBIDIRLINE void formatBidirLine(RunListNode ** , RunListNode ** , RunListNode ** , RunListNode ** , uint8)
#define LLM_DECL_FORMATBIDIRPARA uint8 formatBidirPara(GidListNode * , GidListNode *)
#define LLM_FORMATBIDIRLINE(__rStart, __rEnd, __rHead, __rTail, __pLevel, __bControl)  formatBidirLine(__rStart, __rEnd, __rHead, __rTail, __pLevel)
#define LLM_FORMATBIDIRPARA(__pStart, __pEnd, __bCtrl) formatBidirPara(__pStart, __pEnd)
#endif 

#ifndef ENABLE_MILLI_INTERCHAR_SPACE
#define GET_INT_INTERCHARSPACE(__val) (__val)
#define GET_FIXED_INTERCHARSPACE(__val) ((F16Dot16)(__val) << 16)
#else
#define GET_INT_INTERCHARSPACE(__val) (__val) >> 16)
#define GET_FIXED_INTERCHARSPACE(__val) (__val)
#endif 

#ifdef ENABLE_CACHE
#define LLM_FLUSH_CACHE FF_CM_Flush(this->cache, &this->errCode)
#define LLM_SET_FILTER_MANUALLY(__s)
#else
#define LLM_FLUSH_CACHE
#define LLM_SET_FILTER_MANUALLY(__s) FF_Set_T2K_Core_FilterReference(__s, (FF_T2K_FilterFuncPtr)LLMFilterFunction, (void *)&this->filterParam)
#endif 

#ifdef ENABLE_FRACTIONAL_SIZE
#define LLM_GET_INT_FONTSIZE(__val)	(uint16)((__val) >> 16)
#define LLM_GET_FIXED_FONTSIZE(__val) (__val)
#define LLM_SET_FROM_INT_FONTSIZE(__val) ((uint32)(__val) << 16)
#define LLM_SET_FROM_FRAC_FONTSIZE(__val) (__val)
#define LLM_SET_FRAC_SIZE_PROP(__s, __v) T2K_SetFracSizeMode((__s), (__v))
#define LLM_RENDER_COMMAND  (uint16)(GridFitCommands[this->gridfitMode] | T2K_SCAN_CONVERT | T2K_CODE_IS_GINDEX | this->fracPenCommand)
#define LLM_SET_SIZE_FROM_RUN(__val) setFracSize(__val)
#define LLM_GET_SIZE_FROM_RUN(__val) getFracSize()
#define LLM_GET_FRAC_PART(__val) (int8)((__val >> 10) & 0x3F) 
#ifdef ENABLE_Y_FRAC
#define LLM_RENDER_GLYPH_INTERNALLY(__id, __fx, __fy) renderCharInternally(__id, __fx, __fy)
#else
#define LLM_RENDER_GLYPH_INTERNALLY(__id, __fx, __fy) renderCharInternally(__id, __fx, 0)
#endif 
#else
#define LLM_GET_INT_FONTSIZE(__val)	(__val)
#define LLM_GET_FIXED_FONTSIZE(__val) ((uint32)(__val) << 16)
#define LLM_SET_FROM_INT_FONTSIZE(__val) (__val)
#define LLM_SET_FROM_FRAC_FONTSIZE(__val) ((__val) >> 16)
#define LLM_SET_FRAC_SIZE_PROP(__s, __v)
#define LLM_RENDER_COMMAND  (uint16)(GridFitCommands[this->gridfitMode] | T2K_SCAN_CONVERT | T2K_CODE_IS_GINDEX)
#define LLM_SET_SIZE_FROM_RUN(__val) setSize(__val)
#define LLM_GET_SIZE_FROM_RUN(__val) getSize()
#define LLM_GET_FRAC_PART(__val)
#define LLM_RENDER_GLYPH_INTERNALLY(__id, __fx, __fy) renderCharInternally(__id)
#endif 

#endif 




