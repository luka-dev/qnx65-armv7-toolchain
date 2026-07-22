/*
 * Tsimem.h
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

#ifndef __TSIMEM__
#define __TSIMEM__
#ifdef __cplusplus
extern "C" {            
#endif  

#ifndef FF_FFCONFIG_HEADER
#include "config.h"
#else
#include FF_FFCONFIG_HEADER
#endif 

#include FF_SYSHEAD_HEADER


#define T2K_FB_GLYPH		0
#define T2K_FB_POINTS		1
#define T2K_FB_IOSTREAM		2
#define T2K_FB_HINTS		3
#define T2K_FB_SC			4
#define T2K_FB_SC_BITMAP	5
#define T2K_FB_FILTER		6
#define T2K_MAX_FAST_BLOCKS	7

#ifdef ENABLE_CLIENT_ALLOC

typedef void * (* tsi_ClientAllocMethod) (size_t , void * );

typedef void (*  tsi_ClientDeAllocMethod) (void *, void * );

typedef void * (*  tsi_ClientReAllocMethod) (void *, size_t, void * );
#endif 

typedef struct
{
#ifdef ENABLE_MEM_VALIDATION
	
	uint32		stamp1;			
	int32		numPointers;	
	int32		maxPointers;	
	void		**base;
	uint32		ii;
#endif 	

	
	CLIENT_JMPBUF	env;			
#ifdef ENABLE_MEM_VALIDATION
#ifdef TRACK_RAM
	int32		totRAM;
	int32		maxRAM;
#endif 
#endif 

	
	void		*fast_base[T2K_MAX_FAST_BLOCKS];
	uint32		fast_size[T2K_MAX_FAST_BLOCKS];
	int			fast_free[T2K_MAX_FAST_BLOCKS];
	uint32		state;
#ifdef ENABLE_MEM_VALIDATION
	uint32		stamp2;			
#endif 

#ifdef ENABLE_CLIENT_ALLOC
	tsi_ClientAllocMethod allocPtr;
	tsi_ClientDeAllocMethod freePtr;
	tsi_ClientReAllocMethod reallocPtr;
	void * clientArgs;
#endif 

} tsiMemObject;



#ifndef ENABLE_CLIENT_ALLOC
tsiMemObject *tsi_NewMemhandler( int *errCode );
#else
tsiMemObject *tsi_NewMemhandler( int *errCode, tsi_ClientAllocMethod allocPtr, tsi_ClientDeAllocMethod freePtr, tsi_ClientReAllocMethod reallocPtr, void * clientArgs);
#endif 

void tsi_DeleteMemhandler( tsiMemObject *t );

#ifndef ENABLE_CLIENT_ALLOC
tsiMemObject *tsi_NewCustomSizeMemhandler( int *errCode, int max_pointers );
#else
tsiMemObject *tsi_NewCustomSizeMemhandler( int *errCode, int max_pointers, tsi_ClientAllocMethod allocPtr, tsi_ClientDeAllocMethod freePtr, tsi_ClientReAllocMethod reallocPtr,  void * clientArgs );
#endif 

void *tsi_AllocMem( register tsiMemObject *t, size_t size );
void *tsi_ReAllocMem( register tsiMemObject *t, void *p, size_t size );
void tsi_DeAllocMem( register tsiMemObject *t, void *p );

void tsi_EmergencyShutDown( tsiMemObject *t );


void tsi_Error( tsiMemObject *t, int errcode );


#define T2K_STATE_ALIVE	0xaa005501
#define T2K_STATE_DEAD	0x5500aaff


void *tsi_FastAllocN( register tsiMemObject *t, size_t size, int N );




#define tsi_FastDeAllocN( t, p, N ) { if ( p == t->fast_base[N] ) t->fast_free[N] = true; else tsi_DeAllocMem( t, p ); }
#define tsi_FastReleaseN( t, N ) tsi_DeAllocMem( t, t->fast_base[N] ), t->fast_base[N] = NULL, t->fast_size[N] = 0, t->fast_free[N] = true;
#define tsi_FastSizeN( t, N ) (t->fast_size[(N)])
void tsi_FreeFastMemBlocks( tsiMemObject *t );


#define tsi_Assert( t, cond, errcode ) if ( !(cond) ) tsi_Error( t, errcode )

#define T2K_ERR_MEM_IS_NULL			10000
#define T2K_ERR_TRANS_IS_NULL		10001
#define T2K_ERR_RES_IS_NOT_POS		10002
#define T2K_ERR_BAD_GRAY_CMD		10003
#define T2K_ERR_BAD_FRAC_PEN		10004
#define T2K_ERR_GOT_NULL_GLYPH		10005
#define T2K_ERR_TOO_MANY_POINTS		10006
#define T2K_ERR_BAD_T2K_STAMP		10007
#define T2K_ERR_MEM_MALLOC_FAILED	10008
#define T2K_ERR_BAD_MEM_STAMP		10009
#define T2K_ERR_MEM_LEAK			10010
#define T2K_ERR_NULL_MEM			10011
#define T2K_ERR_MEM_TOO_MANY_PTRS	10012
#define T2K_ERR_BAD_PTR_COUNT		10013
#define T2K_ERR_MEM_REALLOC_FAILED	10014
#define T2K_ERR_MEM_BAD_PTR			10015
#define T2K_ERR_MEM_INVALID_PTR		10016
#define T2K_ERR_MEM_BAD_LOGIC		10017
#define T2K_ERR_INTERNAL_LOGIC		10018
#define T2K_ERR_USE_PAST_DEATH		10019
#define T2K_ERR_NEG_MEM_REQUEST		10020
#define T2K_BAD_CMAP				10021
#define T2K_UNKNOWN_CFF_VERSION		10022
#define T2K_MAXPOINTS_TOO_LOW		10023
#define T2K_EXT_IO_CALLBACK_ERR		10024
#define T2K_BAD_FONT				10025
#define T2K_UNKNOWN_BTC_VERSION		10026

#ifdef __cplusplus
}
#endif  

#endif 



