/*
 * strkconv.h
 * Font Fusion Copyright (c) 2000 all rights reserved by Bitstream Inc.
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

#ifndef __FF_STRKCONV__
#define __FF_STRKCONV__
#ifdef __cplusplus
extern "C" {            
#endif  

#ifdef ENABLE_STRKCONV

typedef struct
{
	

		
	uint8	*baseAddr;
	int		internal_baseAddr;
	int32	left, right, top, bottom;
	F26Dot6	fTop26Dot6, fLeft26Dot6;
	int32	rowBytes;
	
	
	tsiMemObject *mem;

	int16	*startPoint;
	int16	*endPoint;
	int16	numberOfContours;

	int32	*x;
	int32	*y;
	int8	*onCurve;
	
	int32	xmin, xmax;
	int32	ymin, ymax;
} ffStrkConv;



ffStrkConv *ff_NewStrkConv( tsiMemObject *mem, int16 numberOfContours,
							int16 *startPtr, int16 *endPtr,
							int32 *xPtr, int32 *yPtr,
							int8 *onCurvePtr );

void MakeStrkBits( ffStrkConv *t, int8 omitBitMap, FF_GetCacheMemoryPtr funcptr,
				   void *theCache, int bitRange255, uint8 *remapBits,
				   int32 xRadius,  int32 yRadius  );


void ff_DeleteStrkConv( ffStrkConv *t );

#endif 


#ifdef __cplusplus
}
#endif  
#endif 



