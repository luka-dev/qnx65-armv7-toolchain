/*
 * Auxdata.h
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





#ifndef auxdata_h
#define auxdata_h

typedef struct blockHead_tag
{
	uint8 len[2];
	uint8 blockID[2];
	} blockHead_t;



#define IDWINFACENAME	1	
#define IDWINTYPEATT	2	
#define IDWINSTYLE		3	
#define IDPOSTNAME		4	
#define IDADDTYPEATT	5	
#define IDFULLFONTNAME	6	
#define IDPFMTYPEATT	7	
#define IDPAIRKERNDATA	8	
#define IDTRACKKERNDATA	9	




#define IDUSERDATA	0x8000



#define CS_WINDOWSANSI		0
#define CS_WINDOWSCUSTOM	1
#define CS_MACANSI			2
#define CS_MACCUSTOM		3
#define CS_UNICODE			4
#define CS_CUSTOM_TRANSLATE	5

typedef struct auxTypeAtt_tag
{
	uint8	panose[10];
	uint8	ascent[2];
	uint8	descent[2];
	uint8	height[2];
	uint8	internalLeading[2];
	uint8	externalLeading[2];
	uint8	aveCharWidth[2];
	uint8	maxCharWidth[2];
	uint8	weight[2];
	int8	italic;
	int8	charSet;
	int8	pitchAndFamily;
	int8	breakChar;
	uint8	overhang[2];
} auxTypeAtt_t;



typedef struct auxAddTypeAtt_tag
{
	uint8	underlinePos[2];
	uint8	underlineThickness[2];
	uint8	strikethroughPos[2];
	uint8	strikethroughThickness[2];
	uint8	subscriptXSize[2];
	uint8	subscriptYSize[2];
	uint8	subscriptXPos[2];
	uint8	subscriptYPos[2];
	uint8	superscriptXSize[2];
	uint8	superscriptYSize[2];
	uint8	superscriptXPos[2];
	uint8	superscriptYPos[2];
} auxAddTypeAtt_t;



typedef struct auxPfmTypeAtt_tag
{
	uint8	dfAscent[2];
	uint8	dfMaxWidth[2];
	uint8	dfWeight[2];
	uint8	etmSlant[2];
	uint8	etmLowerCaseDescent[2];
	uint8	lineGap[2];
	uint8	sTypoAscender[2];
	uint8	sTypoDescender[2];
	uint8	dfItalic;
	uint8	fixedPitch;
} auxPfmTypeAtt_t;



typedef struct auxPairKernHeader_tag
{
	uint8	nKernPairs[2];
	uint8	baseAdjustment[2];
	uint8	flags;
} auxPairKernHeader_t;




#define TWO_BYTE_KERN_PAIR_CHAR_CODES 1
#define TWO_BYTE_KERN_PAIR_ADJ_VALUES 2


typedef struct auxTrackKernHeader_tag
{
	uint8	nKernTracks[2];
} auxTrackKernHeader_t;




#define PUTAUXINT(chararray,ival) chararray[0] = (uint8)(ival >> 8);chararray[1] = (uint8)(ival & 0xFF);

#define GETAUXINT(chararray) (((uint16)chararray[0] << 8) + (uint16)chararray[1])


#endif 


