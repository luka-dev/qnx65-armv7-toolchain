/*
 * Agridint.h
 * Font Fusion Copyright (c) 1989-1999 all rights reserved by Bitstream Inc.
 * http://www.bitstream.com/
 * http://www.typesolutions.com/
 * Author: Sampo Kaasila
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

#ifdef ENABLE_AUTO_GRIDDING_CORE

#ifndef __T2K_AGRINDINT__
#define __T2K_AGRINDINT__
#ifdef __cplusplus
extern "C" {            
#endif  

#ifndef false
#define false 0
#endif
#ifndef true
#define true 1
#endif

#ifndef FF_FFCONFIG_HEADER
#include "config.h"
#else
#include FF_FFCONFIG_HEADER
#endif 

#include FF_DTYPES_HEADER


#define SHORTMAX  32767
#define SHORTMIN -32768

#define kMaxLong 0x7FFFFFFF

#define TWO_PERCENT_OF_THE_EM (hData->unitsPerEm/50)
#define ONE_PERCENT_OF_THE_EM (hData->unitsPerEm/100)
#define TEN_PERCENT_OF_THE_EM (hData->unitsPerEm/10)

#define CVT_EXIT_MARKER 9999


#define HEIGHT_ENTRY_SIZE 2




#define MAX_HEIGHTS				67

#define MAX_SINGLE_HEIGHTS		(MAX_HEIGHTS-LC_L_DOT_BOTTOM_HEIGHT)
#define NUMNORMVALUES 10
#define USER_TMPS 3
#define FIRST_USER_CVT MAX_HEIGHTS

#define FIRSTTMP (FIRST_USER_CVT + USER_TMPS)


#define SECONDTMP (FIRSTTMP + 1)

#define THIRDTMP (FIRSTTMP + 2)
#define USED_TMPS		7
#define RESERVED_TMPS	8
#define NUMTEMPS (USED_TMPS+RESERVED_TMPS)
#define GLOBALNORMSTROKEINDEX THIRDTMP
#define FREEBASE (FIRSTTMP + NUMTEMPS + 24)








#define SMALLFRAC		int32
#define SMALLFRAC_ONE	0x4000
#define SMALLFRACVECMUL( dx1, dx2, dy1, dy2 ) (( (((SMALLFRAC)(dx1))*((SMALLFRAC)(dx2))) + (((SMALLFRAC)(dy1))*((SMALLFRAC)(dy2))) ) >> 14)


#define MAX_CVT_ENTRIES	96

typedef struct {
	uint8 type;
	uint8 direction;
	uint8 forwardTo;
	uint8 priority;
	int16 from;
	int16 to;
} tp_LinkType;

#define T2K_H_ZONES 5


typedef struct {
	uint32 magic0xA5A0F5A5;	
	int16 numberOfContours;	
	int16 *startPoint;		
	int16 *endPoint;		
	uint8 *onCurve;			
	int16 *oox; 
	int16 *ooy; 

	int16 isFigure; 

#ifdef ENABLE_ALL_AUTO_HANDG_CODE
	int16 *nextPt; 			
	int16 *prevPt;			
	int16 *searchPoints;	

	
	uint16 *flags;			
	int16 *realX;			
	int16 *realY;			
	
	int16 *forwardAngleOrthogonalPair; 	
	int16 *backwardAngleOrthogonalPair; 
	int16 *pointToLineMap;

	SMALLFRAC *cos_f;	
	SMALLFRAC *sin_f;	
	SMALLFRAC *cos_b;	
	SMALLFRAC *sin_b;	

	int linkCount;		
	int maxLinks;		
	tp_LinkType *links;	
	
#endif 

	
	F26Dot6 cvt[MAX_CVT_ENTRIES];	
	int16 ocvt[MAX_CVT_ENTRIES];	
	int16 unitsPerEm;				
	int32 xPixelsPerEm;				
	int32 yPixelsPerEm;				
	ag_FontCategory fontType;		

	
	F26Dot6 oy1, y1, y1Shift;
	F26Dot6 oy2, y2, y2Shift;
	F26Dot6 oy3, y3, y3Shift;
	F26Dot6 oy4, y4, y4Shift;
	int16  ooy1, ooy2, ooy3, ooy4;
	int32 mul[ T2K_H_ZONES ];
	int32 div[ T2K_H_ZONES ];
	int32 add[ T2K_H_ZONES ];
	int32 fmul[ T2K_H_ZONES ];
	int yBounds[T2K_H_ZONES];
	int fFastYAGDisabled;

	int maxPointCount;				
	
	ag_GlobalDataType gData;
	
	ag_HintMaxInfoType maxInfo;

#ifdef ENABLE_ALL_AUTO_HANDG_CODE

	
	F26Dot6	*ox;		
	F26Dot6	*oy;		
	uint8	*f;  		

	
	int32  ttCodeBaseMaxLength;	
	uint8 *ttCodeBase;			
	uint8 *ttcode;				
	
	int32  ttDataBaseMaxElements; 
	int16 *ttDataBase;			  
	int16 *ttdata;				  
	
	int32  hintFragmentMaxLength; 
	uint8 *hintFragment;		  
	int32  hintFragmentLength;	  
	
	int16 RP0, RP1, RP2;		
#endif 

#define STORE_maxMul			8
#define STORE_minMul			9
#define STORE_multiplier		10
#define STORE_mulRepeatCount	11
#define STORE_error				12
#define STORE_return			13
#define MAXSTORAGE				16

	int32  storage[MAXSTORAGE];

	int16 inX;	
	int16 inY;	
	int8 cvtHasBeenSetUp; 
	int8 hintInfoHasBeenSetUp; 
	tsiMemObject *mem;
	int strat98;
	uint32 magic0x0FA55AF0; 
} ag_DataType;



#define ag_pixelSize 64


#define ag_COS_5_DEG 16322

#define ag_COS_10_DEG 16135

#define ag_COS_15_DEG 15826

#define ag_COS_30_DEG 14189

#define ag_SIN_2_5_DEG 715


#define INC_HEIGHT	1

#define INC_LINK	3


#define INC_XDIR 1
#define INC_YDIR 2


#define X_IMPORTANT	0x0001
#define Y_IMPORTANT	0x0002
#define XEX			0x0004
#define YEX			0x0008
#define X_TOUCHED	0x0010
#define Y_TOUCHED	0x0020
#define HEIGHT		0x0040
#define INFLECTION	0x0080
#define CORNER		0x0100
#define X_ROUND		0x0200
#define Y_ROUND		0x0400

#define IN_XF		0x0800
#define IN_YF		0x1000

#define IN_XB		0x2000
#define IN_YB		0x4000

int16 ag_GetCvtNumber( ag_DataType *hData, int16 doX, int16 doY, int16 doD, int32 dist );
int16 ag_Height( register ag_DataType *hData, int pt );
int16 ag_Abs16( register int16 z );
int16 ag_GetXMaxCvtVal( ag_DataType *hData );
int16 ag_GetYMaxCvtVal( ag_DataType *hData );
F26Dot6 ag_ModifyHeightGoal( ag_DataType *hData, int16 cvtNumber, F26Dot6 currentValue );
F26Dot6 ag_ModifyWeightGoal( F26Dot6 goal, F26Dot6 currentValue );

void ag_SVTCA_X( ag_DataType *hData );
void ag_SVTCA_Y( ag_DataType *hData );

void ag_MDAPX( ag_DataType *hData, register ag_ElementType* elem, int16 round, int point );
void ag_MDAPY( ag_DataType *hData, register ag_ElementType* elem, int16 round, int point );

void ag_MIAPX( ag_DataType *hData, register ag_ElementType* elem, int16 round, int point, int16 cvtNumber);
void ag_MIAPY( ag_DataType *hData, register ag_ElementType* elem, int16 round, int point, int16 cvtNumber);

void ag_MDRPX( ag_DataType *hData, register ag_ElementType* elem, int16 cvtNumber, int16 move, int16 minDist, int16 round, int8 c1, int8 c2, int ptA, int ptB );
void ag_MDRPY( ag_DataType *hData, register ag_ElementType* elem, int16 cvtNumber, int16 move, int16 minDist, int16 round, int8 c1, int8 c2, int ptA, int ptB );

void ag_MoveDirectRelativePointInPositiveDirection( ag_DataType *hData, register ag_ElementType* elem, int16 cvtNumber, int from, int to, int16 doX );
void ag_MoveDirectRelativePointInNegativeDirection( ag_DataType *hData, register ag_ElementType* elem, int16 cvtNumber, int from, int to, int16 doX );

void ag_BiDirectionalLink( ag_DataType *hData, register ag_ElementType* elem, int16 cvtNumber, int16 minDist, int from, int to, int16 doX );
void ag_BiDirectionalLinkWithCvt( ag_DataType *hData, register ag_ElementType* elem, int16 cvtNumber, int from, int to, int16 doX );

void ag_IPPointX( ag_DataType *hData, register ag_ElementType* elem, int A, int B, int C );
void ag_IPPointY( ag_DataType *hData, register ag_ElementType* elem, int A, int B, int C );


void ag_XSmooth( register ag_DataType *hData, register ag_ElementType *elem );
void ag_YSmooth( register ag_DataType *hData, register ag_ElementType *elem );

void ag_IF( register ag_DataType *hData, ag_ElementType *elem, int16 storeIndex );
void ag_ELSE( register ag_DataType *hData, ag_ElementType *elem );
void ag_EIF( register ag_DataType *hData, ag_ElementType *elem );
void ag_JMPR( register ag_DataType *hData, ag_ElementType *elem, int32 positionOfTarget );

void ag_LINK( ag_DataType *hData, register ag_ElementType* elem, int16 *ooz, int16 doX, int16 doY, int16 minDist, int16 round, int8 c1, int8 c2, int from, int to );
void ag_ADJUST( ag_DataType *hData, register ag_ElementType* elem, int16 doX, int16 doY, int16 anchor, int16 from, int16 to );
void ag_ASSURE_AT_LEAST_EQUAL( ag_DataType *hData, ag_ElementType* elem, int16 doX, int16 prev, int16 point );
void ag_ASSURE_AT_MOST_EQUAL( ag_DataType *hData, ag_ElementType* elem, int16 doX, int16 prev, int16 point );
void ag_ASSURE_AT_MOST_EQUAL2( ag_DataType *hData, register ag_ElementType* elem, int16 doX, int16 prev, int16 point1, int16 point2 );

void ag_ADJUSTSPACING( register ag_DataType *hData, register ag_ElementType* elem, int32 lsbPoint, int32 minPoint, int32 maxPoint, int32 rsbPoint );

void ag_INIT_STORE( ag_DataType *hData );
void AG_CHECK_AND_TWEAK( ag_DataType *hData, ag_ElementType* elem, int16 doX, int16 cvtNumber, int16 ptA );

#ifdef ENABLE_AUTO_HINTING
	int ag_CheckArrayBounds( ag_DataType *hData );
	void ag_MovePushDataIntoInstructionStream( ag_DataType *hData, int32 ttcodePosition0, int32 ttdataPosition0 );
#endif 

int ag_DoGlyphProgram97( ag_ElementType* elem, ag_DataType *hData );

#ifdef __cplusplus
}
#endif  
#endif 

#endif 





