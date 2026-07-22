/*
 * pclread.h
 *
 * $Header: /home/archive/FontFusion/FontFusion/core/pclread.h,v 1.6 2009/04/27 18:08:21 sflynn Exp $
 *
 * Font Fusion Copyright (c) 1989-2009 all rights reserved by Bitstream Inc.
 * http://www.bitstream.com/
 * http://www.typesolutions.com/
 * Author: Robert Eggers
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

#ifndef _PCLRead_H
#define _PCLRead_H
#ifdef __cplusplus
extern "C" {			
#endif  


#define MASTER_RESOLUTION	8782	
#define BASELINE			5380	
#define LEFT_REFERENCE		2980	

typedef struct
{
	uint8	structure;
	uint8	width;
	uint8	posture;
} style_t;

typedef struct
{
	uint8	vendor;
	uint8	version;
	uint16	value;
} typeface_t;

typedef struct
{
	uint16	size;			
	uint8	dformat,		
			font_type;		
	style_t	style;			
	uint16	baseline,		
			cell_width,		
			cell_height;	
	uint8	orientation,	
			spacing;		
	uint16	symbol_set,		
			pitch,			
			height,			
			x_height;		
	int8	width_type;		
	int8	stroke_weight;	
	typeface_t typeface;	 
							 
	uint8	serif_style,	
			quality;		
	int8	placement,		
			uline_dist;		 
	uint8	uline_height;	
	uint16	text_height,	
			text_width,		
			first_code,		
			last_code;		
	uint8	pitch_extend,	
			height_extend;	
	uint16	cap_height;		
	uint8	font_vendor_code;	
	uint32	font_number;	
							 
	int8	fontname[16];	
	uint16	scale_factor,	
			x_resolution,	
			y_resolution;	
	int16	mstr_uline_pos;	
	uint16	mstr_uline_hght,
			threshold;		
	int16	italic_angle;	
	uint16	scal_data_size;	
	int8	*scal_data;		
	uint16	nobtf;			
	int8	*copyright;		
	uint8	checksum;		
	uint16	total_size;		
} PC5HEAD;


#define GET_WORD(A)  ((uint16)((uint16)A[0] << 8) | ((uint8)A[1]))

typedef uint8 eo_char_t;


#define EEO_DOES_NOT_EXIST		2001	 
#define EEO_NESTED_COMP_CHAR	2002	 
#define EEO_ILL_COMP_CHAR_REF	2003	 
#define EEO_ILL_COMP_SUBCHAR	2004	 
#define EEO_NOT_A_PCL5_CHAR		2005	 
#define EEO_BAD_OUTL_DATA		2006	 
#define EEO_SPECS_OUT_OF_RANGE	2007	 
#define EEO_WIDTH_SPECS_NOTVAL	2008	 

#if 0
typedef struct
{
	uint16	gpsSize;
	int32	gpsOffset;
} indexToLoc_t;

typedef struct
{
	uint16	charCode;
	uint16	gIndex;
} codeToIndex_t;
#endif

typedef struct
{
	
	PC5HEAD			pcl5head;
	tsiMemObject	*mem;
	InputStream		*in;
#if 0
	indexToLoc_t	*indexToLoc;
	codeToIndex_t	*codeToIndex;
#endif
	uint16			outlineRes;
	uint16			metricsRes;
	int8			verticalEscapement;
	int32			lsbx;
	uint8			contourOpen;
	int32			awx;
	int32			awy;
	int16			eo_baseline;		
	int16			eo_left_reference;	

	
	GlyphClass		*glyph;

	int16			NumCharStrings;
	int32			upem;
	int32			maxPointCount;
	int32			ascent;
	int32			descent;
	int32			lineGap;
	int32			advanceWidthMax;
	F16Dot16		italicAngle;

	uint32	isFixedPitch;			
	uint16	firstCharCode;			
	uint16	lastCharCode;			

	int glyphExists;

} PCLClass;


#ifdef ENABLE_PCLETTO


typedef struct {

	uint16	format;
	uint16	default_GC;
	uint16	num_regions;

	struct {

		uint16	ul_cc;
		uint16	lr_cc;
		uint16	GC;

	} regions[1];

} GC_t;


typedef struct {

	struct {

		uint16	horiz;
		uint16	vert;

	} GID[1];

} VT_t;


typedef struct {

	uint16	format;
	int16	descender;

} VR_t;


typedef struct {

	uint8	format;
	uint8	num_ranges;

	struct {

		uint16	firstCode;
		uint16	lastCode;

	} range[1];

} VE_t;



typedef struct {

	tsiMemObject	*mem;

	uint8	exclude_char;	

	GC_t	*GC;	
	VT_t	*VT;	
	VR_t	*VR;	
	VE_t	*VE;	

} PCLettoClass;


PCLettoClass *New_PCLettoClass( tsiMemObject *mem );
void tsi_DeletePCLettoClass( PCLettoClass *t );

#endif	



#define		ESC_FNDESC		 1
#define		ESC_CCHARID		 2
#define		ESC_CHDESC		 3
#define		NO_ESCAPE		 0
#define		ESC_UNKN		-1
#define		ESC_EOF			-2

PCLClass *tsi_NewPCLClass( tsiMemObject *mem, InputStream *in, int32 fontNum );
void tsi_DeletePCLClass( PCLClass *t );

GlyphClass *tsi_PCLGetGlyphByIndex( PCLClass *t, uint16 index, uint16 *aWidth, uint16 *aHeight );
uint16 tsi_PCLGetGlyphIndex( PCLClass *t, uint32 charCode );

uint8 *GetPCLNameProperty( PCLClass *t, uint16 languageID, uint16 nameID );

void BuildPCLMetricsEtc( PCLClass *t, uint16 NumCharStrings );

uint16 FF_GetAW_PCLClass( void *param1, register uint16 index );

#ifdef __cplusplus
}
#endif  
#endif 



