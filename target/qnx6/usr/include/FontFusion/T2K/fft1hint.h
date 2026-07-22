/*
 * FFT1HINT.H

 * $Header: /home/archive/FontFusion/FontFusion/core/fft1hint.h,v 1.4 2008/03/18 17:35:49 sflynn Exp $

 * Font Fusion Copyright (c) 1989-2008 all rights reserved by Bitstream Inc.
 * http://www.bitstream.com/
 * http://www.typesolutions.com/
 * Author: Mike Dewsnap
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

#ifndef __FFHINT__
#define __FFHINT__


#ifdef __cplusplus
extern "C" {			
#endif  

#ifdef ENABLE_NATIVE_T1_HINTS

#define MAXBLUEVALUES	14
#define MAXSNAPVALUES	12
#define FLOATING		0
#define BOTTOM_ALIGNED	1
#define TOP_ALIGNED		2

#define WIDTH_CHUNK		20
#define DEPTH_CHUNK		10
#define POOL_HINTARRAY	0
#define POOL_HINTPIX	1
#define POOL_OFFSETPTR	2
#define POOL_INTORUS	3
#define POOL_MULTPTR	4

typedef struct blueZone_tag
{
	F26Dot6		minPix;			
	F26Dot6		maxPix;			
	F26Dot6		refPix;			
} blueZone_t;


typedef struct stemSnap_tag
{
	F26Dot6		minPix;			
	F26Dot6		maxPix;			
	F26Dot6		refPix;			
} stemSnap_t;


typedef struct
{
	uint32		offsetHintArray;	
	uint32		offsetHintPix;		
	uint32		offsetOffsetPtr;	
	uint32		offsetIntOrus;		
	uint32		offsetMultPtr;		
	
	int16		num_hints_ml;
	int16		num_hints;
	
	
	
	
} hints_t;


typedef struct
{
	int16	*hint_array;
	int16	num_hints_ml;
	int16	num_hints;
} extraStroke_t;



typedef struct
{
	int16	*EdgeThresh;
	int16	*EdgeDelta;
	int16	*EdgeIndex;
	int16	numEdges_ml;
	int16	numEdges;
} extraEdge_t;

typedef struct  
{
	tsiMemObject *mem;
	void * memPool;
	uint32 currentPtr;		
	uint32 prevPtr;			
	uint32 totalBytes;		
}FFT1HintMempool_t;

typedef struct
{
		

	

	
	tsiMemObject *mem;

	
	int32		xPixelsPerEm;
	int32		yPixelsPerEm;
	F16Dot16	xScale;
	F16Dot16	yScale;
	F26Dot6		xpos;
	F26Dot6		ypos;
	int32		upem;

	

	blueZone_t	pBlueZones[MAXBLUEVALUES];	
	int32		bluevalues[MAXBLUEVALUES];	
	int32		numBlueValues;				
	int32		BlueFuzz;
	F16Dot16	BlueScale;
	int32		BlueShift;
	F26Dot6		BlueShiftPix;

	

	stemSnap_t	pSnapV[MAXSNAPVALUES];		
	stemSnap_t	pSnapH[MAXSNAPVALUES];		
	int32		snapHWVals[MAXSNAPVALUES];	
	int32		snapVWVals[MAXSNAPVALUES];	
	int32		numSnapV;					
	int32		numSnapH;					
	int32		numSnapVZones;				
	int32		numSnapHZones;				
	int32		StdHW;						
	int32		StdVW;						
	int16		numHintSets;				

	

	int16		*hintmarkers_x_ptr;
	int16		hintmarkers_x_ml;
	int16		num_hintmarkers_x;

	int16		*hintmarkers_y_ptr;
	int16		hintmarkers_y_ml;
	int16		num_hintmarkers_y;

	int16		*xgcount_ptr;
	int16		xgcount_ml;
	int16		num_xgcount;

	int16		*ygcount_ptr;
	int16		ygcount_ml;
	int16		num_ygcount;

	int16		*xbgcount_ptr;
	int16		xbgcount_ml;
	int16		numxbgcount;

	int16		*ybgcount_ptr;
	int16		ybgcount_ml;
	int16		numybgcount;

	int16		*xOrus_ptr;
	int16		xOrus_num_ml;
	int16		numxOrus;				

	int16		*yOrus_ptr;
	int16		yOrus_num_ml;
	int16		numyOrus;				

	int16		*nxIntOrus_ptr;
	int16		xInt_num_ml;
	int16		numxIntOrus;			

	int16		*nyIntOrus_ptr;
	int16		yInt_num_ml;
	int16		numyIntOrus;			

	

	hints_t			*x_hints;
	hints_t			*y_hints;

	extraStroke_t	*x_strokes;
	extraStroke_t	*y_strokes;

	int16			num_x_hint_sets_ml;
	int16			num_y_hint_sets_ml;

	extraEdge_t		*x_edges;
	extraEdge_t		*y_edges;

	F26Dot6		onepix;
	F26Dot6		pixrnd;
	F26Dot6		pixfix;
	int32		suppressOvershoots;

	int16		*extraXStrokeOrus_ptr;
	int16		extraXStrokeOrus_ml;
	int16		numextraXStroke;

	int16		*extraYStrokeOrus_ptr;
	int16		extraYStrokeOrus_ml;
	int16		numextraYStroke;

	int16		*extraXStrokeGlyphCount_ptr;
	int16		extraXStrokeGlyphCount_ml;
	int16		numextraXStrokeGlyphCount;

	int16		*extraYStrokeGlyphCount_ptr;
	int16		extraYStrokeGlyphCount_ml;
	int16		numextraYStrokeGlyphCount;

	int16		num_tcb;

	int16		numextraXEdge;
	int16		numextraYEdge;
	int16		extraEdgeX_ml;
	int16		extraEdgeY_ml;

	int16		*extraXEdgeThresh_ptr;
	int16		*extraYEdgeThresh_ptr;
	int16		*extraXEdgeDelta_ptr;
	int16		*extraYEdgeDelta_ptr;
	int16		*extraXEdgeIndex_ptr;
	int16		*extraYEdgeIndex_ptr;
	int16		*extraXEdgeGlyphCount_ptr;
	int16		*extraYEdgeGlyphCount_ptr;
	FFT1HintMempool_t		*pool[5];	

} FFT1HintClass;



FFT1HintClass *New_FFT1HintClass( tsiMemObject *mem, int16 units_per_em);

void SetScale_FFT1HintClass( FFT1HintClass *t, int32 xPixelsPerEm, int32 yPixelsPerEm );

void SetupGlobalHints( FFT1HintClass *t, int32 numBlues, int32 BlueFuzz, F16Dot16 BlueScale,
						int32 BlueShift, int32 *BlueArray,
						int32 StdVW, int32 StdHW, int32 *StemVArray, int32 *StemHArray,
						int32 numVArray, int32 numHArray);

void ApplyHints_FFT1HintClass( FFT1HintClass *t, int16 count, int16 extracount, GlyphClass *glyph );

void FFT1HintClass_releaseMem(FFT1HintClass *t);

void Delete_FFT1HintClass( FFT1HintClass *t );

#else 
typedef void FFT1HintClass;
#endif

#ifdef __cplusplus
}
#endif  
#endif 


