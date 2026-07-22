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
#ifndef __PF_H_INCLUDED
#define __PF_H_INCLUDED

#include <stdlib.h>
#include <photon/PhT.h>
#include <limits.h>
#include <inttypes.h>
#include <font_api.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

struct _doc_ctrl;

extern struct _Pf_ctrl	*PfAttach(const char *device, long size);
extern void		PfDetach(struct _Pf_ctrl *pf);
extern int		PfLoadFont(const char *font, unsigned flags, FontName fontused);
extern int		PfQueryFont(const char *font, FontQueryInfo *info);
extern int		PfQueryFonts(long symbol, unsigned flags, FontDetails list[], int n);
extern PhRect_t	*	PfExtentText(PhRect_t *extent, PhPoint_t const *pos, const char *font, const char *str, int len);
extern PhRect_t	*	PfExtentComponents(PhRect_t *extent, PhPoint_t const *pos, const char *font, const char *str, int len, void (*func)(PhRect_t *, const char *, const char *, int));
extern PhRect_t	*	PfFractionalExtentText(PhRect_t *extent, PhPoint_t const *pos, const char *font, long xsize, long ysize, const char *str, int len);
extern int		PfRenderTextCtx(void *ctx,const char *font, const char *str, int len, PhPoint_t const *pos, PhRect_t const *clip, void (*func)(void *,const PhPoint_t *, const FontRender *));
extern int		PfFractionalRenderTextCtx(void *ctx, const char *font, long xsize, long ysize, const char *str, int len, PhPoint_t const * pos, PhRect_t const *clip, void (*func)(void *,const PhPoint_t *, const FontRender *));
extern int		PfGlyph(const char *font, long symbol, FontRender *metrics, unsigned char *bitmap, int size, FontName fontused);
extern int		PfLoadMetrics(const char *font);
extern int		PfUnloadMetrics(const char *font);
extern int		PfTextWidth(const char *font, const char *str, int len);
extern int		PfTextWidthBytes(const char *font, const char *str, int len);
extern int		PfTextWidthChars(const char *font, const char *str, int len);
extern int 		PfExtentTextCharPositions(PhRect_t * ptsExtent, PhPoint_t const * ptsPos, char const * psz, const char * pckFont, int32_t const * piIndices, int32_t * piPenPositions, int32_t iArrayLen, uint32_t ulFlags, int32_t iBytes, uint32_t uiExtentLen, PhRect_t const * pktsClip);
extern int 		PfExtentFractTextCharPositions(PhRect_t * ptsExtent, PhPoint_t const * ptsPos, char const * psz, const char * pckFont, int32_t const * piIndices, int32_t * piPenPositions, int32_t iArrayLen, uint32_t ulFlags, int32_t iBytes, uint32_t uiExtentLen, PhRect_t const * pktsClip, uint32_t uiXscale, uint32_t uiYscale);
extern long		PfDynamicLoad(char const * pkcFontFile, char * pszDescription);
extern long		PfDynamicUnload(long lDynamicFontID);
extern int		PfQueryFontInfo(const char *font, FontQueryInfo *info);

long PfGetOutline(char const * pkucFont, unsigned long ulSymbol, pf_metrics_t * ptsMetrics, PhPoint_t ** pptsPoints, int ** ppiLoops);

extern PhRect_t	*	PfExtentWideText(PhRect_t *extent, PhPoint_t const *pos, const char *font, const uint16_t *str, int len);
extern int		PfRenderWideTextCtx(void *ctx,const char *font, const uint16_t *str, int len, PhPoint_t const *pos, PhRect_t const *clip, void (*func)(void *,const PhPoint_t *, const FontRender *));
extern int		PfWideTextWidth(const char *font, const uint16_t *str, int len);
extern int		PfWideTextWidthBytes(const char *font, const uint16_t *str, int len);
extern int		PfWideTextWidthChars(const char *font, const uint16_t *str, int len);

extern long	PfGetCacheStats(FontStats * ptsStats, unsigned long ulFlags);

#define PfTextWidth(font, str, len) PfTextWidthChars(font, str, len)
#define PfWideTextWidth(font, str, len) PfWideTextWidthChars(font, str, len)

/* API */
FontID * PfFindFont(char const * pkcDescription, uint32_t kulFlags, uint32_t kulSize);
char * PfConvertFontID(FontID * ptsID);
char const * PfFontDescription(FontID * ptsID);
uint32_t PfFontSize(FontID * ptsID);
uint32_t PfFontFlags(FontID * ptsID);
FontID * PfDecomposeStemToID(char const * pkszStem);
char const * PfFontBaseStem(FontID * ptsID);
long PfFreeFont(FontID * ptsID);

/* Convenience API */
char * PfGenerateFontName(char const * pkcDescription, uint32_t kuiFlags, uint32_t kuiSize, char * pcBuff);

int PfExtentTextToRect(PhRect_t * ptsExtent, char const * pkszFont, PhRect_t * ptsRect, char const * pkszString, int iLen);

int PfFontType(char const * font, char * pcBuffer, int iBufferLen);
int PfExtent(PhRect_t *extent, PhPoint_t const *pos, const char *font, long adata, long bdata, const char *str, int len, int flags, PhRect_t const * clip);
int PfExtent16dot16(PhRect16dot16_t *extent, PhPoint16dot16_t const *pos, const char *font, long adata, long bdata, const char *str, int len, int flags, PhRect_t const * clip);
int PfRender(void *ctx, const char *font, long adata, long bdata, const char *str, int len, int flags, PhPoint_t const *pos, PhRect_t const *clip, void (*func)(void *,const PhPoint_t *pos, const FontRender *));
int PfSetRenderingDPI(uint32_t res_x, uint32_t res_y);
struct _Pf_ctrl * PfDefaultContext(void);

/* Deprecated routines */
int PfRenderCtx(void *ctx, const char *font, long adata, long bdata, const char *str, int len, int flags, PhPoint_t const *pos, PhRect_t const *clip, void (*func)(void *,const PhPoint_t *pos, const FontRender *));
extern int PfFractionalRenderText(const char *font, long xsize, long ysize, const char *str, int len, PhPoint_t const * pos, PhRect_t const *clip, void (*func)(const PhPoint_t *, const FontRender *));
extern int PfRenderText(const char *font, const char *str, int len, PhPoint_t const *pos, PhRect_t const *clip, void (*func)(const PhPoint_t *, const FontRender *));
extern int PfRenderWideText(const char *font, const uint16_t *str, int len, PhPoint_t const *pos, PhRect_t const *clip, void (*func)(const PhPoint_t *, const FontRender *));

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/Pf.h $ $Rev: 224590 $" )
#endif
