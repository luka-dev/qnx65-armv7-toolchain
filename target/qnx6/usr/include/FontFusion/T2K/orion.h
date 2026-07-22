/*
 * Orion.h
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

#ifndef __T2K_ORION__
#define __T2K_ORION__

#ifndef FF_FFCONFIG_HEADER
#include "config.h"
#else
#include FF_FFCONFIG_HEADER
#endif 

#include FF_SCODER_HEADER
#include FF_TRUETYPE_HEADER
#ifdef __cplusplus
extern "C" {            
#endif  


#define ORION_MAJOR_VERSION 1
#define ORION_MINOR_VERSION 0

#define NUM_ECOPYX (8)
#define NUM_EX (NUM_ECOPYX+8+1)

#define ORION_STATE_0 0

typedef struct
{
	
	tsiMemObject *mem;

	
	int		OrionState;
	int		num_eb1, num_e;
	int		num_eb2;	
	int16	*dx; 		
	int16	*dy; 		
	int8	*onCurve;	

	SCODER	**copy;		
	SCODER	**literal;	
	SCODER	*control;
	SCODER	*ep;
} OrionModelClass;


#ifdef ENABLE_WRITE
OrionModelClass *New_OrionModelClass( sfntClass *font );
void Save_OrionModelClass( OrionModelClass *t, OutputStream *out );
int KnownVectorInOrionModel( OrionModelClass *t, int16 dx, int16 dy, int8 onCurve );
#endif

OrionModelClass *New_OrionModelClassFromStream( tsiMemObject *mem, InputStream *in );


void Set_OrionState( OrionModelClass *t, int dx, int dy, int8 onCurve );


void Delete_OrionModelClass( OrionModelClass *t );



#ifdef __cplusplus
}
#endif  
#endif 



