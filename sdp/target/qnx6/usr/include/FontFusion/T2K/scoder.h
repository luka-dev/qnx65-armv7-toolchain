/*
 * Scoder.h
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

#ifndef __T2K_SCODER__
#define __T2K_SCODER__
#ifdef __cplusplus
extern "C" {            
#endif  


#define No_of_chars 256                 

typedef struct {
	
	tsiMemObject	*mem;
	uint8			*numBitsUsed;
	uint32			numEntries, maxBits;
	uint8			*LookUpSymbol;	
	uint16			*LookUpBits;		
	
} SCODER;



void SCODER_SequenceLookUp( SCODER *t );







#ifdef ENABLE_WRITE
SCODER *New_SCODER( tsiMemObject *mem, int32 *count, int32 *codingCost);


void SCODER_Save( SCODER *t, OutputStream *out );


int SCODER_EncodeSymbol( SCODER *t, OutputStream *out, uint8 symbol );

#endif 


SCODER *New_SCODER_FromStream( tsiMemObject *mem, InputStream *in );



uint8 SCODER_ReadSymbol( SCODER *t, InputStream *in );



void Delete_SCODER( SCODER *t );

#ifdef __cplusplus
}
#endif  
#endif 



