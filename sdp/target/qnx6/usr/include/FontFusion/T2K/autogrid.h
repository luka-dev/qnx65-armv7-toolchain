/*
 * Autogrid.h
 * Font Fusion Copyright (c) 1989-1999 all rights reserved by Bitstream Inc.
 * http://www.bitstream.com/
 * http://www.typesolutions.com/
 * Author: Sampo Kaasila
 * This software is the property of Bitstream Inc. and it is furnished
 * under a license and may be used and copied only in accordance with the
 * terms of such license and with the inclusion of the above copyright notice.
 * This software or any other copies thereof may not be provided or otherwise
 * made available to any other person or entity except as allowed under license.
 * No title to and no ownership of the software or intellectual property
 * contained herein is hereby transferred. This information in this software
 * is subject to change without notice
 */

 


#ifndef ag_ROMAN
typedef int ag_FontCategory;
#define ag_ROMAN 1
#define ag_KANJI 2
#define ag_ROMAN_MONOSPACED 3
#endif


#ifndef __T2K_AUTOGRID__
#define __T2K_AUTOGRID__

#define CMD_AUTOGRID_ALL 		0
#define CMD_AUTOHINT 			1
#define CMD_FINDSTEMS			2
#define CMD_AUTOGRID_YHEIGHTS	3

#ifdef ENABLE_AUTO_GRIDDING_CORE

#ifdef __cplusplus
extern "C" {            
#endif  




#define IN
#define OUT
#define INOUT





#define ag_ASCENDER_HEIGHT		0
#define ag_CAP_HEIGHT			1
#define ag_FIGURE_HEIGHT		2
#define ag_X_HEIGHT				3
#define ag_UC_BASE_HEIGHT		4
#define ag_LC_BASE_HEIGHT		5
#define ag_FIGURE_BASE_HEIGHT	6
#define ag_DESCENDER_HEIGHT		7
#define ag_PARENTHESES_TOP		8
#define ag_PARENTHESES_BOTTOM	9
#define ag_MAX_HEIGHTS_IN		10


typedef struct {
	int16	flat;		
	int16	round;		
	int16	overLap;	
						
						
						
						
} ag_HeightType;



#define ag_MAXWEIGHTS		12

typedef struct {
	
	
	ag_HeightType	heights[ag_MAX_HEIGHTS_IN]; 
	
	int16 xWeight[ag_MAXWEIGHTS]; 
	int16 yWeight[ag_MAXWEIGHTS]; 
} ag_GlobalDataType;

typedef struct {
	uint16 maxZones;
	uint16 maxTwilightPoints;
	uint16 maxStorage;
	uint16 maxFunctionDefs;
	uint16 maxInstructionDefs;
	uint16 maxStackElements;
	uint16 maxSizeOfInstructions;
} ag_HintMaxInfoType;


typedef struct {
	
	int16	contourCount; 
	int16	pointCount;   
	int16	*sp;  		
	int16	*ep;  		
	int16	*oox;		
	int16	*ooy;		
						
						
	uint8 *onCurve;		
	
	int32	*x;			
	int32	*y;			
	int32	advanceWidth26Dot6;
	int32	advanceWidthInt;
} ag_ElementType;

typedef void *ag_HintHandleType;










extern int ag_HintInit( IN tsiMemObject *mem, IN int maxPointCount, IN int16 unitsPerEm, OUT ag_HintHandleType *hintHandle );


extern int ag_SetHintInfo( IN ag_HintHandleType hintHandle, IN ag_GlobalDataType *gData, ag_FontCategory fontType );


extern int ag_SetScale( IN ag_HintHandleType hintHandle, IN int32 xPixelsPerEm, IN int32 yPixelsPerEm, int8 *xWeightIsOne );

#ifdef ENABLE_AUTO_HINTING

extern int ag_GetGlobalHints(IN ag_HintHandleType hintHandle,
							 OUT uint8 **fpgm, OUT int32 *fpgmLength,
							 OUT uint8 **ppgm, OUT int32 *ppgmLength,
							 OUT int16 **cvt,  OUT int32 *cvtCount );

#endif 


#ifdef ENABLE_AUTO_GRIDDING_CORE

#define CMD_AUTOGRID_YHEIGHTS_DISABLED -100

extern int ag_AutoGridOutline( IN ag_HintHandleType hintHandle, INOUT ag_ElementType *elem, IN int16 cmd, IN int16 isFigure, IN int16 curveType, IN int16 grayScale, IN int16 numSBPoints );
#endif 

#ifdef ENABLE_AUTO_HINTING

extern int ag_AutoHintOutline( IN ag_HintHandleType hintHandle, IN ag_ElementType *elem, IN int16 isFigure, IN int16 curveType, OUT uint8 *hintFragment[], OUT int32 *hintLength );
#endif 				   		


extern int ag_AutoFindStems( IN ag_HintHandleType hintHandle, IN ag_ElementType *elem, IN int16 isFigure, IN int16 curveType, OUT int16 *xDist[], OUT int32 *xDistCount, OUT int16 *yDist[], OUT int32 *yDistCount ); 


extern int ag_GetHintMaxInfo( IN ag_HintHandleType hintHandle, OUT ag_HintMaxInfoType *p );


extern int ag_HintEnd( IN ag_HintHandleType hintHandle );





#ifdef __cplusplus
}
#endif  

#endif	

#endif 




