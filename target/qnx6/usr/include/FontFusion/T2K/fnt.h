/*
 * Fnt.h
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

#ifndef FNT_H
#define FNT_H


#if 1

#ifndef FF_FFCONFIG_HEADER
#include "config.h"
#else
#include FF_FFCONFIG_HEADER
#endif 

#include FF_T2KSTRM_HEADER
#include FF_TT_PRVT_HEADER
#endif

#ifdef __cplusplus
extern "C" {            
#endif  



typedef int16 ShortFrac;	

#define ONESHORTFRAC		(1 << 14)
#define FIXONEHALF			0x00008000
#define FIXROUND( x )		(int16)(((x) + FIXONEHALF) >> 16)

typedef void (*voidFunc)(void);
typedef void (*fs_FuncType)(void*);

typedef int16	LoopCount;
typedef int32	ArrayIndex;

#define GLOBAL_PROTO
#define LOCAL_PROTO	static
#define FUNCTION

#define fnt_pixelSize	0x40L
#define fnt_pixelShift	6

#define MAXBYTE_INSTRUCTIONS	256

#define VECTORTYPE					ShortFrac
#define ONEVECTOR					ONESHORTFRAC
#define VECTORMUL(value, component)	ShortFracMul(value, component)
#define VECTORDOT(a,b)				ShortFracDot(a,b)
#define VECTORMULDIV(a,b,c)			ShortMulDiv(a,b,c)
#define ONESIXTEENTHVECTOR			((ONEVECTOR) >> 4)

#define SHORTMUL(a,b)				(int32)((a) * (b))

#define SROUND( x, n, d, halfd ) \
	if ( x > -1 ) { \
		x = (SHORTMUL(x, n) + halfd)/d; \
	} else { \
		x = -((SHORTMUL(-x, n) + halfd) / d); \
	}

#define ONEFIX		( 1L << 16 )
#define ONCURVE		1
#define btsbool		int

#define ACTIVATE_DROPOUTCONTROL	0x10000
#define SMART_DROPOUT			0x20000
#define INCLUDE_STUBS			0x40000


#define NO_ERR						0x0000
#define UNDEFINED_INSTRUCTION_ERR	0x1101
#define TRASHED_MEM_ERR				0x1102


typedef struct VECTOR
{
	VECTORTYPE x;
	VECTORTYPE y;
} VECTOR;

typedef struct
{
	F26Dot6		*x;			
	F26Dot6		*y;			
	F26Dot6		*ox;		
	F26Dot6		*oy;		
	int16		*oox;		
	int16		*ooy;		
	uint8		*onCurve;	
	int16		nc;			
	int16		padWord;	
	int16		*sp;		
	int16		*ep;		
	uint8		*f;			
} fnt_ElementType;

typedef struct
{
	int32	start;			
	uint16	length;			
	uint16	pgmIndex;		
} fnt_funcDef;


typedef struct
{
	int32	start;
	uint16	length;
	uint8	pgmIndex;
	uint8	opCode;
} fnt_instrDef;

typedef struct
{
	Fract	x;
	Fract	y;
} fnt_FractPoint;





typedef struct fnt_LocalGraphicStateType fnt_LocalGraphicStateType_t;
typedef struct fnt_GlobalGraphicStateType fnt_GlobalGraphicStateType_t;

#define REENTRANT_ALLOC 1
#if REENTRANT_ALLOC
#define GSP_DECL0 fnt_LocalGraphicStateType_t *pLocalGS
#define GSP_DECL1 GSP_DECL0,
#else
#define GSP_DECL0 void
#define GSP_DECL1
#endif



typedef void	(*FntFunc)(GSP_DECL0);
typedef void	(*InterpreterFunc)(GSP_DECL1 uint8*, uint8*);
typedef void	(*FntMoveFunc)(GSP_DECL1 fnt_ElementType*, ArrayIndex, F26Dot6);
typedef F26Dot6	(*FntRoundFunc)(GSP_DECL1 F26Dot6, F26Dot6);
typedef F26Dot6	(*FntProjFunc)(GSP_DECL1 F26Dot6, F26Dot6);
typedef F26Dot6 (*GetCVTEFunc)(GSP_DECL1 ArrayIndex n);
typedef F26Dot6 (*GetSWidFunc)(GSP_DECL0);



typedef void	(*TraceFuncType)(fnt_LocalGraphicStateType_t *);
typedef F26Dot6	(*ScaleFuncType)(fnt_GlobalGraphicStateType_t *, F26Dot6);

typedef struct
{



	F26Dot6			wTCI;				
	F26Dot6			sWCI;	 			
	F26Dot6			scaledSW; 			
	int32			scanControl;		
	int32			instructControl;	

	F26Dot6			minimumDistance;	
	FntRoundFunc	RoundValue;			
	F26Dot6			periodMask; 		
	Fract			period45;			
	int16			period;				
	int16			phase;				
	int16			threshold;			

	int16			deltaBase;
	int16			deltaShift;
	int16			angleWeight;
	int16			sW;					
	int8			autoFlip;			
	int8			pad;

} fnt_ParameterBlock;					

#define MAXANGLES		20
#define ROTATEDGLYPH	0x100
#define STRETCHEDGLYPH	0x200
#define NOGRIDFITFLAG	1
#define DEFAULTFLAG		2

typedef enum
{
	PREPROGRAM,
	FONTPROGRAM,
	MAXPREPROGRAMS
} fnt_ProgramIndex;

typedef struct fnt_GlobalGraphicStateType
{
	F26Dot6*	stackBase; 			
	F26Dot6*	store; 				
	F26Dot6*	controlValueTable;	

	uint16		pixelsPerEm; 		
	uint16		pointSize; 			
	Fixed		fpem;				
	F26Dot6		engine[4]; 			

	fnt_ParameterBlock	defaultParBlock;	
	fnt_ParameterBlock	localParBlock;

	



	FntFunc*		function;			
	fnt_funcDef*	funcDef;			
#ifdef USE_SEAT_BELTS
	uint8*			funcDefLimitPtr;	
#endif 
	fnt_instrDef*	instrDef;			

	ScaleFuncType	ScaleFunc;			

	uint8*	pgmList[MAXPREPROGRAMS];	

	

	Fixed		fixedScale; 			
	int32		nScale; 				
	int32		dScale; 				
	int32		dScaleDiv2;			
	int16		dShift; 				
	int8		identityTransformation; 	
	int8		non90DegreeTransformation; 
	Fixed		xStretch; 			
	Fixed		yStretch;

	

	fnt_FractPoint*	anglePoint;
	int16*			angleDistance;

	int8 init;					
	uint8 pgmIndex;				
	LoopCount instrDefCount;	

	int32					cvtCount;
	maxpClass				*maxp;

#ifdef XDEBUG
	uint16					glyphIndex_old;
	btsbool					glyphProgram_Old;
#endif

} fnt_GlobalGraphicStateType;




typedef struct fnt_LocalGraphicStateType
{
	uint8	*insPtr;					
	int		opCode;						

	fnt_ElementType *CE0, *CE1, *CE2; 	
	VECTOR	proj; 						
	VECTOR	free;						
	VECTOR	oldProj; 					
	F26Dot6	*stackPointer;

#ifdef OLD
	uint8 *insPtr;						
#endif

	fnt_ElementType				*elements;
	fnt_GlobalGraphicStateType	*globalGS;

	TraceFuncType TraceFunc;			

	ArrayIndex	Pt0, Pt1, Pt2;			
	int16		roundToGrid;
	LoopCount	loop;					

#ifdef OLD
	uint8	opCode;						
	uint8	padByte;
	int16	padWord;
#endif 

	

	VECTORTYPE	pfProj;		

	FntMoveFunc		MovePoint;
	FntProjFunc		Project;
	FntProjFunc		OldProject;
	InterpreterFunc	Interpreter;
	GetCVTEFunc		GetCVTEntry;
	GetSWidFunc		GetSingleWidth;

	CLIENT_JMPBUF	env;		

} fnt_LocalGraphicStateType;



GLOBAL_PROTO int fnt_Execute(fnt_ElementType *elements, uint8 *ptr, uint8 *eptr,
							 fnt_GlobalGraphicStateType *globalGS, fs_FuncType TraceFunc);



GLOBAL_PROTO void fnt_Init(fnt_GlobalGraphicStateType *globalGS);

GLOBAL_PROTO F26Dot6 fnt_RoundToGrid(GSP_DECL1 F26Dot6 xin, F26Dot6 engine);

#ifdef __cplusplus
}
#endif  

#endif	


