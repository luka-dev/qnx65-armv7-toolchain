/*
	$Header: /home/archive/FontFusion/FontFusion/core/util.h,v 1.4 2008/08/29 16:14:08 sflynn Exp $

 * UTIL.H
 * Font Fusion Copyright (c) 1989-2008 all rights reserved by Bitstream Inc.
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

#ifndef __T2K_UTIL__
#define __T2K_UTIL__
#ifdef __cplusplus
extern "C" {            
#endif  

uint8 *ReadFileIntoMemory( tsiMemObject *mem, const int8 *fname, uint32 *size );
void WriteDataToFile( const int8 *fname, void *dataIn, uint32 size );



void util_SortShortArray( int16 *a, int32 n );

F16Dot16 util_FixMul( F16Dot16 mA, F16Dot16 mB );

F16Dot16 util_FixDiv( F16Dot16 mA, F16Dot16 mB );

F16Dot16 util_FixSin( F16Dot16 in );

#define util_FixCos( in ) util_FixSin( (90*0x10000 - (in)) )
void TESTFIXDIV( void );


int32 util_ShortFracMul( int32 mA, int16 mB );

F16Dot16 util_FixMul26Dot6( F16Dot16 mA, F16Dot16 mB );


F16Dot16 util_EuclidianDistance( register F16Dot16 a, register F16Dot16 b );


void util_ComputeIntersection( int16 line1_pt1_x, int16 line1_pt1_y, int16 line1_pt2_x, int16 line1_pt2_y,
                               int16 line2_pt1_x, int16 line2_pt1_y, int16 line2_pt2_x, int16 line2_pt2_y,
                               int16 *x, int16 *y );
#ifdef ALGORITHMIC_STYLES
#ifdef ENABLE_POSTHINT_ALGORITHMIC_STYLES
void util_ComputeIntersection26Dot6( F26Dot6 line1_pt1_x, F26Dot6 line1_pt1_y, F26Dot6 line1_pt2_x, F26Dot6 line1_pt2_y,
							   F26Dot6 line2_pt1_x, F26Dot6 line2_pt1_y, F26Dot6 line2_pt2_x, F26Dot6 line2_pt2_y,
							   F26Dot6 *x, F26Dot6 *y );
#endif
#endif


#ifdef ENABLE_HASH_CLASS
typedef struct {
	uint16 key;
	uint16 value;
} hashEntry;

typedef struct {
	uint8  *name;
	uint16  charCode;
	uint16  glyphIndex;
} UE_hashEntry;


typedef int (*FF_STRS_ARE_EQUAL_FUNC_PTR)( void *privptr, int8 *str, uint16 n);

typedef struct {
	
	tsiMemObject *mem;
	int32 x;
	int32 numItems;
	int32 maxItems;
	int32 enum_x;
	int32 m; 
	FF_STRS_ARE_EQUAL_FUNC_PTR stringsAreEqual;
	void *privPtr; 
	hashEntry *hash;
	
	UE_hashEntry *UE_hash;
	int32 first_UE_code;
	int32 num_UE_codes;
	
	
} hashClass;


hashClass *New_hashClass( tsiMemObject *mem, int32 maxItems, FF_STRS_ARE_EQUAL_FUNC_PTR stringsAreEqual, void *privPtr );

int get_using_uint16_hashClass( hashClass *t, uint16 key, uint16 *value );

int get_using_str_hashClass( hashClass *t, int8 *keystr, uint16 *value );

void put_hashClass( hashClass *t, uint16 key, uint16 value, int8 *keyStr  );

void rewind_enum_hashClass( hashClass *t );

int next_enum_hashClass( hashClass *t, uint16 *key, uint16 *value );

void Delete_hashClass( hashClass *t );

#ifdef ACTICATE_HASHCLASS_TESTUNIT
void TEST__hashClass( tsiMemObject *mem );
#endif
#endif 


#ifdef __cplusplus
}
#endif  
#endif 


