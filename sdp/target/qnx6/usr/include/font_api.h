/* Copyright 2009, QNX Software Systems. All Rights Reserved.
 * 
 * You must obtain a written license from and pay applicable license fees to 
 * QNX Software Systems before you may reproduce, modify or distribute this 
 * software, or any work that includes all or part of this software.  Free 
 * development licenses are available for evaluation and non-commercial purposes.  
 * For more information visit http://licensing.qnx.com or email licensing@qnx.com.
 * 
 * This file may contain contributions from others.  Please review this entire 
 * file for other proprietary rights or license notices, as well as the QNX 
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 */
/*!
    \file font_api.h
    \brief font server - Public interface definitions.
*/

#ifndef __FONTAPI_H_INCLUDED
#define __FONTAPI_H_INCLUDED

#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <font_types.h>
#include <font_defs.h>

#if defined(__QNXNTO__)
    #include <_pack64.h>
#else
    #if __WATCOMC__ > 1000
        #pragma pack(__push,1)
    #else
        #pragma pack(1)
    #endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define PHFONT_ENVVAR           "PHFONT"
#define PHFONT_FDNAME			"/dev/phfont"
#define PHFONT_MEM_ENVVAR		"PHFONTMEM"
#define PHFONT_MEM_ROUND(sz)	(((sz) + 3) & ~3)
#define DLL_FONT_SERVER			"server"
#define DLL_MAX_OPTION_NAME     20

#define PHFONT_LOAD_METRICS	0x01
#define PHFONT_LOAD_IMAGES	0x02

#define PHFONT_INFO_PLAIN	0x01
#define PHFONT_INFO_BOLD	0x02
#define PHFONT_INFO_ITALIC	0x04
#define PHFONT_INFO_BLDITC	0x08
#define PHFONT_INFO_FIXED	0x10
#define PHFONT_INFO_PROP	0x20
#define PHFONT_INFO_ALIAS	0x40
#define PHFONT_INFO_SERIF	0x80
#define PHFONT_INFO_SANSERIF	0x100
#define PHFONT_INFO_DECORATIVE	0x200
#define PHFONT_INFO_UNICODE		0x400
#define PHFONT_INFO_ORIENTAL	0x800

#define PHFONT_SCALABLE		0x01
#define PHFONT_BITMAP		0x02
#define PHFONT_PROP			0x10
#define PHFONT_FIXED		0x20
#define PHFONT_ALL_FONTS	0x33
#define PHFONT_DONT_SHOW_LEGACY 0x40

#define PHFONT_ALL_SYMBOLS	(-1L)
#define PHFONT_MAX_POS_LEN	255
#define PHFONT_MAX_INDEX_LEN	255

/* Extent/Render Flags */
#define PF_WIDE_CHARS			0x100
#define PF_CHAR_DRAW_POSITIONS	0x200
#define PF_WIDE_CHAR32			0x400
#define PF_FRACTIONAL			0x800
#define PF_COMPONENT			0x1000
#define PF_RECT					0x2000
#define PF_LCD_RGB				0x4000
#define PF_LCD_BGR				0x8000
#define PF_SIMPLE_METRICS		0x10000

/* Extent/Render Flags(2) */
#define PF_CONTINUE				0x100
#define PF_SHMEM_STRING			0x200
#define PF_CLIP_VALID			0x400

struct _doc_ctrl;

#define PHF_STATS 0x01
#define PFR_STATS 0x02
#define TTF_STATS 0x03

/* Start - common flags*/
#define PF_STYLE_BOLD 	0x0001
#define PF_STYLE_ITALIC 0x0002
#define PF_STYLE_BI 	(PF_STYLE_BOLD | PF_STYLE_ITALIC)
#define PF_STYLE_ULINE	0x0004
#define PF_STYLE_DULINE	0x0008

#define PF_STYLE_ANTIALIAS	0x0010

#define PF_BITMAP		0x0100
#define PF_SCALABLE		0x0200
/* End - common flags*/

/* fontserver API */

int PfLoadFontCx(struct _Pf_ctrl * context, const char *font, unsigned flags, FontName fontused);
int PfQueryFontCx(struct _Pf_ctrl * context, const char *font, FontQueryInfo *info);
int PfQueryFontInfoCx(struct _Pf_ctrl * context, const char *font, FontQueryInfo *info);
int PfQueryFontDescriptionInfoCx(struct _Pf_ctrl * context, const char *description, FontQueryInfo *info);
int PfQueryFontsCx(struct _Pf_ctrl * context, long symbol, unsigned flags, FontDetails list[], int n);
int PfExtentCx(struct _Pf_ctrl * context, pf_rect_t *extent, pf_point_t const *pos, const char *font, long adata, long bdata, const char *str, int len, int flags, pf_rect_t const *clip);
int PfExtent16dot16Cx(struct _Pf_ctrl * context, pf_rect_16dot16_t *extent, pf_point_16dot16_t const *pos, const char *font, long adata, long bdata, const char *str, int len, int flags, pf_rect_t const *clip);
pf_rect_t *PfExtentComponentsCx(struct _Pf_ctrl * context, pf_rect_t *extent, pf_point_t const *pos, const char *font, const char *str, int len, void (*func)(pf_rect_t const *, const char *, const char *, int));
int PfRenderCx(struct _Pf_ctrl * context, void *ctx, const char *font, long adata, long bdata, const char *str, int len, int flags, pf_point_t const *pos, pf_rect_t const *clip, void (*func)(void *,const pf_point_t *pos, const FontRender *));
int PfGlyphCx(struct _Pf_ctrl * context, const char *font, long symbol, FontRender *metrics, unsigned char *bitmap, int size, FontName fontused);
int PfLoadMetricsCx(struct _Pf_ctrl * context, const char *font);
int PfUnloadMetricsCx(struct _Pf_ctrl * context, const char *font);
int PfFontTypeCx(struct _Pf_ctrl * context, char const * font, char * pcBuffer, int iBufferLen);
int PfExtentTextCharPositionsCx(struct _Pf_ctrl * context, pf_rect_t * ptsExtent, pf_point_t const * ptsPos, char const * psz, const char * pckFont, long adata, long bdata,
                              int32_t const * piIndices, int32_t * piPenPositions, int32_t iArrayLen, uint32_t ulFlags,
                              int32_t iBytes, uint32_t uiExtentLen, pf_rect_t const * pktsClip);
long PfGetOutlineCx(struct _Pf_ctrl * context, char const * pkucFont, unsigned long ulSymbol, pf_metrics_t * ptsMetrics, pf_point_t ** pptsPoints, int ** ppiLoops);
long PfGetCacheStatsCx(struct _Pf_ctrl * context, FontStats * ptsStats, unsigned long ulFlags);
int PfSetRenderingDPICx(struct _Pf_ctrl * context, uint32_t res_x, uint32_t res_y);

long PfDynamicLoadCx(struct _Pf_ctrl * context, char const * pkcFontFile, FontDescription pszDescription);
long PfDynamicUnloadCx(struct _Pf_ctrl * context, long lDynamicFontID);
long PfDynamicFontIDCx(struct _Pf_ctrl * context, char const * path);

char const * PfFontDescriptionCx(struct _Pf_ctrl * context, FontID * ptsID);
uint32_t PfFontSizeCx(struct _Pf_ctrl * context, FontID * ptsID);
uint32_t PfFontFlagsCx(struct _Pf_ctrl * context, FontID * ptsID);
long PfFreeFontCx(struct _Pf_ctrl * context, FontID * ptsID);
char const * PfFontBaseStemCx(struct _Pf_ctrl * context, FontID * ptsID);

FontID * PfFindFontCx(struct _Pf_ctrl * context, char const * pkcDescription, uint32_t kulFlags, uint32_t kulSize);
FontID * PfDecomposeStemToIDCx(struct _Pf_ctrl * context, char const * pkszStem);
char * PfGenerateFontNameCx(struct _Pf_ctrl * context, char const * pkcDescription, uint32_t kuiFlags, uint32_t kuiSize, char * pcBuff);
char * PfConvertFontIDCx(struct _Pf_ctrl * context, FontID * ptsID, char * szTag);
FontID * PfConvertPixelsToPointSizeCx(struct _Pf_ctrl * context, char const * description, int flags, uint32_t pixel_height);

struct _Pf_ctrl *PfAttachCx(const char *device, long size);
void PfDetachCx(struct _Pf_ctrl * context);

int PfGlyphsCx(struct _Pf_ctrl * context, wchar_t * pwc, uint32_t num_glyphs, FontID * font, FontRender ** render, pf_metrics_t ** metric, char *(*func_alloc)(int), void (*func_free)(char *));
int PfGlyphOpenTypeDataCx(struct _Pf_ctrl * context, FontID * font, uint32_t tag, unsigned char ** ppTable, uint32_t * pSize);
int PfGetGlyphIndexCx(struct _Pf_ctrl * context, wchar_t wc, FontID * font, uint32_t * pIndex);

/* Server DLL API */
typedef struct fontdll_ref * fontdll_t;

/* Font DLL API */
fontdll_t PfAttachLocalDll(char const * options, char const * option_name);
fontdll_t PfAttachLocalDllArgv( int argc, const char *argv[], const char *schema );

int PfDetachLocalDll(fontdll_t dll);
int PfSetOptionsDll(fontdll_t dll, char const * options, char const * option_name);

/* Font DLL context API */
struct _Pf_ctrl * PfAttachDllCx(fontdll_t dll, long size);
int PfAllocRenderCx(struct _Pf_ctrl * context, long size);
int PfAllocDetailsCx(struct _Pf_ctrl * context, char const ** name, long * size);
int PfAssignDllCx(struct _Pf_ctrl * context, fontdll_t dll);

/* Sleuth DLL API */
int PfAttachSleuthMonitorDll(fontdll_t dll, int prio);

/* Server DLL API */
int PfAttachServerDll(fontdll_t dll, int prio, char const * device);
int PfRestartServerDll(fontdll_t dll);
int PfWaitOnServerDll(fontdll_t dll);
int PfSetServerMode( fontdll_t dll, int mode );

/*
 * Provides access to internal render routine for compatibility with the following
 * deprecated routines:  PfRenderText, PfRenderWideText, PfFractionalRenderText.
 * In the future, when the above mentioned routines are expunged, this routine
 * will be removed.
 */
typedef int (*internal_render_cb_t)(struct _Pf_ctrl *, void *,const char *, long, long, const char *, int, pf_point_t const *, void (*)(void *,const pf_point_t *, const FontRender *), void (*)(const pf_point_t *,const FontRender*),pf_rect_t const *, int);

internal_render_cb_t font_RenderCb(struct _Pf_ctrl * context);

#ifdef __cplusplus
};
#endif

#if defined(__QNXNTO__)
    #include <_packpop.h>
#else
    #if __WATCOMC__ > 1000
        #pragma pack(__pop)
    #else
        #pragma pack()
    #endif
#endif

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/font/public/font_api.h $ $Rev: 224585 $" )
#endif
