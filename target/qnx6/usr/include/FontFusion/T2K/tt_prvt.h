/*
 * TT_PRVT.H
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


#ifndef __T2K_TT_PRVT__
#define __T2K_TT_PRVT__
#ifdef __cplusplus
extern "C" {            
#endif  




#define tag_FontHeader          0x68656164      


#define tag_BFontHeader         0x62686564      

#define tag_HoriHeader          0x68686561      
#define tag_VertHeader          0x76686561      
#define tag_IndexToLoc          0x6c6f6361      
#define tag_MaxProfile          0x6d617870      
#define tag_ControlValue        0x63767420      
#define tag_MetricValue         0x6d767420      
#define tag_PreProgram          0x70726570      
#define tag_GlyphData           0x676c7966      
#define tag_HorizontalMetrics   0x686d7478      
#define tag_VerticalMetrics     0x766d7478      
#define tag_CharToIndexMap      0x636d6170      
#define tag_Kerning             0x6b65726e      
#define tag_Gasp                0x67617370      
#define tag_HoriDeviceMetrics   0x68646d78      
#define tag_Encryption          0x63727970      
#define tag_NamingTable         0x6e616d65      
#define tag_FontProgram         0x6670676d      
#define tag_VDMX                0x56444D58      
#define tag_LTSH                0x4C545348      
#define tag_fvar                0x66766172      

#define tag_FontVariation       0x66766172      
#define tag_GlyphVariation      0x67766172      
#define tag_CVTVariation        0x63766172      

#define tag_TTCollectionID      0x74746366      

#define tag_CFF                 0x43464620      
#define tag_DSIG                0x44534947      

#define tag_EBLC                0x45424C43      
#define tag_bloc                0x626c6f63      

#define tag_EBDT                0x45424454      
#define tag_bdat                0x62646174      

#define tag_EBSC                0x45425343      

#define tag_post                0x706f7374      
#define tag_PCLT                0x50434C54      
#define tag_OS_2                0x4f532f32      


#define tag_sloc                0x736c6f63      
#define tag_ffst                0x66667374      
#define tag_ffhm                0x6666686d      
#ifdef ENABLE_SBITS_COMPRESSION
#define tag_symb                0x73796d62      
#endif 

#define tag_GPOS                0x47504f53      
#define tag_GSUB                0x47535542      




typedef struct {
    uint32   leftRightIndex; 
    int16    value; 
} kernPair0Struct;


typedef struct {
    
    tsiMemObject *mem;

    
    uint16 nPairs;
    uint16 searchRange;
    uint16 entrySelector;
    uint16 rangeShift;
    kernPair0Struct *pairs;
} kernSubTable0Data;


typedef struct {
    
    tsiMemObject *mem;

    
    uint16    version;
    int32     length;
    uint16    coverage;
    void     *kernData;
} kernSubTable;


typedef struct {
    
    tsiMemObject *mem;

    
    uint16  version;
    int32   nTables;
    kernSubTable **table; 
} kernClass;


typedef struct {
    uint16 rangeMaxPPEM;
    uint16 rangeGaspBehavior;
} gaspRangeType;


typedef struct {
    
    tsiMemObject *mem;

    
    uint16    version;
    uint16    numRanges;
    gaspRangeType    *gaspRange; 
} gaspClass;


typedef struct {
    
    uint32  offset;
    uint32  length;
} CFF_Class;


typedef struct {
    
    uint32  offset;
    uint32  length;
} DSIGClass;


typedef struct {
    uint32  tag;
    uint32  checkSum;
    uint32  offset;
    uint32  length;
} sfnt_DirectoryEntry;


typedef struct {
    
    tsiMemObject *mem;

    
    int32   version;             
    uint16  numOffsets;          
    uint16  searchRange;         
    uint16  entrySelector;       
    uint16  rangeShift;          
    sfnt_DirectoryEntry *table;  
} sfnt_OffsetTable;



typedef struct {
    uint16    platformID;
    uint16    specificID;
    uint32    offset;
} sfnt_platformEntry;

typedef struct {
    
    tsiMemObject *mem;

    int16 version;
    int16 numEncodingTables;

    uint32 numGlyphs;

    sfnt_platformEntry **platform;
    uint8 *cmapData;
    int32 length;

    int16  preferedEncodingTable;
    uint16 preferedFormat;

    uint16 selectedPlatformID;
    uint16 selectedPlatformSpecificID;

    uint16 bytesConsumed;

#define NUM_FIGURES 10
    uint16 figIndex[NUM_FIGURES];

    
} cmapClass;


typedef struct {
    
    tsiMemObject *mem;
    uint32 version;

    
    uint32 directoryCount;
    uint32 *tableOffsets;
} ttcfClass;



typedef struct {
    
    tsiMemObject *mem;

    
    int32       version;             
    int32       fontRevision;        
    uint32      checkSumAdjustment;
    uint32      magicNumber;         
    uint16      flags;
    uint16      unitsPerEm;          

    int32       created_bc;
    int32       created_ad;
    int32       modified_bc;
    int32       modified_ad;

    
    int16       xMin;
    int16       yMin;
    int16       xMax;
    int16       yMax;

    uint16      macStyle;               
    uint16      lowestRecPPEM;          

    
    
    
    int16       fontDirectionHint;

    int16       indexToLocFormat;        
    int16       glyphDataFormat;         
} headClass;


typedef struct {
    
    tsiMemObject *mem;


    
    int32    version;            
    int16    Ascender;
    int16    Descender;
    int16    LineGap;

    uint16   advanceWidthMax;
    int16    minLeftSideBearing;
    int16    minRightSideBearing;
    int16    xMaxExtent;

    int16    caretSlopeRise;
    int16    caretSlopeRun;

    int16    caretOffset;
    int16    reserved2;
    int16    reserved3;
    int16    reserved4;
    int16    reserved5;

    int16    metricDataFormat;
    uint16   numberOfHMetrics;
} hheaClass;


typedef struct {
    
    tsiMemObject *mem;

    
    int32 numGlyphs;        
    int32 numberOfHMetrics; 
    int16  *lsb; 
    uint16 *aw;  
} hmtxClass;


typedef struct {
    
    tsiMemObject *mem;

    
    int32 version;          
    int32 N;                
    uint16 defaultWidth;    
    uint16 reserved;        
    uint16 *gIndex;         
    uint16 *aw;             
} ffhmClass;


typedef struct {
    
    tsiMemObject *mem;

    
    int32   version;                
    uint16  numGlyphs;              
    uint16  maxPoints;              
    uint16  maxContours;            
    uint16  maxCompositePoints;     
    uint16  maxCompositeContours;   
    uint16  maxElements;            
    uint16  maxTwilightPoints;      
    uint16  maxStorage;             
    uint16  maxFunctionDefs;        
    uint16  maxInstructionDefs;     
    uint16  maxStackElements;       
    uint16  maxSizeOfInstructions;  
    uint16  maxComponentElements;   
    uint16  maxComponentDepth;      
} maxpClass;


typedef struct {
    
    tsiMemObject *mem;

    
    uint32 *offsets;
    int32   n;
    int16   indexToLocFormat;
} locaClass;


#ifdef ENABLE_T2KS


typedef struct {
    uint16 gIndex;
    uint16 delta;
    int32  offset;
} T2K_sloc_entry;


typedef struct {
    
    tsiMemObject *mem;

    uint32 version;
    uint16 num_sloc_entries;
    T2K_sloc_entry *sloc;
    uint32 numCorrections;

    uint32 correctionOffset;
    

} slocClass;

typedef struct {
    
    tsiMemObject *mem;
    
    
    int16   majorVersion;            
    int16   minorVersion;            

    
    int16   numAxes;
    int16   minRadius;
    int16   maxRadius;
    int16   gIndexFirstRoman;
    int16   gIndexLastRoman;
} ffstClass;


slocClass *FF_New_slocClass( tsiMemObject *mem, InputStream *in );
void FF_Delete_slocClass( slocClass *t );
uint32 FF_SLOC_MapIndexToOffset( slocClass *t, InputStream *in, int32 gIndex );

#endif 


#ifdef ENABLE_OTF


typedef struct {

    uint16 ClassFormat;    
    uint16 StartGlyph;
    uint16 GlyphCount;

    
    uint16  *ClassValuesArray;

} ClassDefFormat1_table;


typedef struct {

    uint16 Start;
    uint16 End;
    uint16 Class;

} ClassRangeRecord;


typedef struct {

    uint16  ClassFormat;    
    uint16  ClassRangeCount;

    
    ClassRangeRecord *ClassRange;

} ClassDefFormat2_table;


typedef struct {

    uint16  CoverageFormat; 
    uint16  GlyphCount;

    
    uint16 *GlyphArray;

} CoverageFormat1_table;


typedef struct {

    uint16 Start;
    uint16 End;
    uint16 StartCoverageIndex;

} CoverageRangeRecord;


typedef struct {

    uint16  CoverageFormat; 
    uint16  RangeCount;

    
    CoverageRangeRecord *RangeRecord;

} CoverageFormat2_table;


typedef struct {

    uint16  PointCount;

    
    uint16 *PointIndex;

} AttachPoint_table;


typedef struct {

    uint16  Coverage;
    uint16  GlyphCount;

    
    uint16  *AttachPoint;

} AttachList_table;


typedef struct {

    uint16  StartSize;
    uint16  EndSize;
    uint16  DeltaFormat;    

    
    uint16 *DeltaValues;

} Device_table;


typedef struct {

    uint16  CaretValueFormat;   
    int16   Coordinate;

} CaretValueFormat1_table;


typedef struct {

    uint16  CaretValueFormat;   
    uint16  CaretValuePoint;

} CaretValueFormat2_table;


typedef struct {

    uint16  CaretValueFormat;   
    int16   Coordinate;

    uint16  DeviceTable;

} CaretValueFormat3_table;


typedef struct {

    uint16  CaretCount;

    
    uint16 *CaretValue;

} LigGlyph_table;


typedef struct {

    uint16  Coverage;
    uint16  LigGlyphCount;

    
    uint16 *LigGlyph;

} LigCaretList_table;




typedef struct {

    int32   Version;    

    uint16  GlyphClassDef;
    uint16  AttachList;
    uint16  LigCaretList;
    uint16  MarkAttachClassDef;

} GDEFHeader_table;

#endif



#ifdef __cplusplus
}
#endif  

#endif 



