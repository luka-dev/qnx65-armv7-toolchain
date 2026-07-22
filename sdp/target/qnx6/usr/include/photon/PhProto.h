/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
 * 
 * You must obtain a written license from and pay applicable license fees to QNX 
 * Software Systems before you may reproduce, modify or distribute this software, 
 * or any work that includes all or part of this software.   Free development 
 * licenses are available for evaluation and non-commercial purposes.  For more 
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *  
 * This file may contain contributions from others.  Please review this entire 
 * file for other proprietary rights or license notices, as well as the QNX 
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/ 
 * for other information.
 * $
 */



/*
 * PhProto.h	
 *		Prototypes for the Photon Ph and Pg libraries
 *

 */
#ifndef __PH_PROTO_H_INCLUDED
#define __PH_PROTO_H_INCLUDED

#include <sys/types.h>
#include <photon/PhT.h>
#include <photon/PmT.h>
#include <photon/PhWm.h>

#ifndef __PG_MACROS_H_INCLUDED
#include <photon/PgMacros.h>
#endif

#ifndef __PD_DIRECT_H_INCLUDED
#include <photon/PdDirect.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif
extern struct _Ph_ctrl * _Ph_;

/* Pg Graphics Context Related functions, these functions relate to the creation/destruction and state of a Photon GC */
extern PhGC_t *PgCreateGC(int);
extern int PgDestroyGC(PhGC_t *);

/* Default state functions for any Photon GC */
extern void PgDefaultText(PhGC_t *);
extern void PgDefaultStroke(PhGC_t *);
extern void PgDefaultFill(PhGC_t *);
extern void PgDefaultMode(PhGC_t *);
extern void PgDefaultAlpha(PhGC_t *);
extern void PgDefaultChroma(PhGC_t *);
extern void PgDefaultGC(PhGC_t *);
extern void PgDefaultBufGC (PhGC_t *GC);

/* State functions for any Photon GC */
extern void PgClearClippingsCx(PhGC_t *gc);
extern int PgSetMultiClipCx(PhGC_t *, int , PhRect_t const *);
extern int PgSetMultiClipTilesCx(PhGC_t *, PhTile_t const *);
extern PgColor_t PgSetStrokeColorCx(PhGC_t *, PgColor_t);
extern void PgSetStrokeXORColorCx(PhGC_t *, PgColor_t, PgColor_t);
extern void PgSetStrokeDitherCx(PhGC_t *, PgColor_t ,PgColor_t ,PgPattern_t);
extern void PgSetStrokeTransPatCx(PhGC_t *, PgPattern_t);
extern long PgSetStrokeFWidthCx(PhGC_t *, long);
extern int PgSetStrokeWidthCx(PhGC_t *, int);
extern int PgSetStrokeCapCx(PhGC_t *, int);
extern int PgSetStrokeJoinCx(PhGC_t *, int);
extern void PgSetStrokeDashCx(PhGC_t *, unsigned char const *,int ,long);
extern PgColor_t PgSetFillColorCx(PhGC_t *, PgColor_t);
extern const PgColorModel_t * PgSetColorModelCx (PhGC_t *, PgColorModel_t const *);
extern const PgColorModel_t * PgGetColorModelCx (PhGC_t *);
extern void PgSetFillXORColorCx(PhGC_t *, PgColor_t, PgColor_t);
extern void PgSetFillDitherCx(PhGC_t *, PgColor_t ,PgColor_t ,PgPattern_t);
extern void PgSetFillTransPatCx(PhGC_t *, PgPattern_t);
extern PgColor_t PgSetTextColorCx(PhGC_t *, PgColor_t);
extern void PgSetTextXORColorCx(PhGC_t *, PgColor_t, PgColor_t);
extern void PgSetTextDitherCx(PhGC_t *, PgColor_t ,PgColor_t ,PgPattern_t);
extern void PgSetTextTransPatCx(PhGC_t *, PgPattern_t);
extern void PgSetFontCx(PhGC_t *, char const *);
extern void PgSetUnderlineCx(PhGC_t *, PgColor_t ,PgColor_t ,int);
extern void PgSetExtendedTextFlagsCx (PhGC_t *gc, unsigned short flags);
extern int PgSetPaletteCx(PhGC_t *, PgColor_t const *,long, short ,short ,int, long);
extern unsigned long PgSetPlaneMaskCx(PhGC_t *, unsigned long);
extern int PgSetDrawModeCx(PhGC_t *, int);
extern void PgSetClippingCx(PhGC_t *, unsigned short, PhRect_t const *);
extern void PgSetUserClipCx(PhGC_t *, PhRect_t const *);
extern void PgSetUserClipAbsoluteCx(PhGC_t *, PhRect_t const *);
extern void PgSetTranslationCx(PhGC_t *, PhPoint_t const *,int);
extern void PgClearTranslationCx(PhGC_t *);
extern void PgSetChromaCx(PhGC_t *, PgColor_t const, long unsigned const);
extern void PgChromaOffCx(PhGC_t *);
extern void PgChromaOnCx(PhGC_t *);
extern void PgSetAlphaBlendCx(PhGC_t *, PgMap_t const * const, char unsigned const);
extern void PgSetAlphaCx(PhGC_t *, long const, PgMap_t const * const, PgGradient_t const * const, char unsigned const, char unsigned const);
extern void PgAlphaOffCx(PhGC_t *);
extern void PgAlphaOnCx(PhGC_t *);
extern PhPoint_t * PgGetTranslationCx(PhGC_t *, PhPoint_t *);
extern unsigned long PgSetControlFlagGCCx(PhGC_t * GC, unsigned long flags);

/* Photon Draw Context Related functions, these functions relate to the creation/destruction, state and manipulation of draw contexts */
/* Functions that work on an any Photon Draw Context */
extern PhGC_t *PgSetGCCx(void *, PhGC_t *);
extern PhGC_t *PgGetGCCx(void *);
#define PgBevelBoxCx( a, b, c, d, e, f, g, h, i, j, k) \
	PgDrawGradientBevelBoxCx(a, b, c, d, e, e, f, g, h, i, j, k)
extern int PgContrastBevelBoxCx(void *, PhPoint_t *, PhPoint_t *,	PgColor_t, int, short, short, PgColor_t, PgColor_t, int);
extern int PgDrawGradientBevelBoxCx(void *, PhPoint_t *, PhPoint_t *, PgColor_t, PgColor_t, PgColor_t, PgColor_t,	short, short, PgColor_t, PgColor_t, int);
extern int PgDrawBorderCx(void *, PhRect_t const *, PgColor_t, PgColor_t, int);
extern int PgDrawArrowCx(void *, PhRect_t const *, short, PgColor_t, int);
extern int PgDrawPixelCx(void *, PhPoint_t const *);
extern int PgDrawIPixelCx(void *, int, int);
extern int PgDrawGridCx(void *, PhRect_t const *, PhPoint_t const *);
extern int PgDrawLineCx(void *, PhPoint_t const *, PhPoint_t const *);
extern int PgDrawILineCx(void *, int, int, int, int);
extern int PgDrawRectCx(void *, PhRect_t const *, unsigned int);
extern int PgDrawIRectCx(void *, int, int, int, int, unsigned int);
extern int PgDrawRoundRectCx(void *, PhRect_t const *, PhPoint_t const *, unsigned int);
extern int PgDrawBevelBoxCx(void *, PhRect_t const *, PgColor_t, short, int);
extern int PgDrawIBevelBoxCx(void *, int, int, int, int, PgColor_t, short, int);
extern int PgDrawEllipseCx(void *, PhPoint_t const *, PhPoint_t const *, unsigned int);
extern int PgDrawArcCx(void *, PhPoint_t const *, PhPoint_t const *, unsigned int, unsigned int, int);
extern int PgDrawPolygonCx(void *, PhPoint_t const *, int, PhPoint_t const *, int);
extern int PgDrawPixelArrayCx(void *, PhPoint_t const *, int, PhPoint_t const *);
extern int PgDrawSpanCx(void *, PgSpan_t const *, int, PhPoint_t const *, int);
extern int PgDrawBezierCx(void *, PhPoint_t const *, int, PhPoint_t const *, int);
extern int PgDrawTrendCx(void *, short const *, PhPoint_t const *, int, int, int, int, unsigned);
extern int PgDrawBitmapCx(void *, void const *, int, PhPoint_t const *, PhPoint_t const *, int, long);
extern int PgDrawImageCx(void *, void const *, int, PhPoint_t const *, PhDim_t const *, int, long);
extern int PgDrawPhImageCx(void *, PhPoint_t const *, PhImage_t const *, int);
extern int PgDrawTImageCx(void *, void const *, int, PhPoint_t const *, PhDim_t const *, int, long, void const *, int);
extern int PgDrawRepTImageCx(void *, void const *, int, PhPoint_t const *, PhPoint_t const *, int, PhPoint_t const *, PhPoint_t const *, long, void const *, int);
extern int PgDrawBeveledCx(void *, PhRect_t const *, PhPoint_t const *, PgColor_t, short, int);
extern int PgDrawRepBitmapCx(void *, void const *, int, PhPoint_t const *, PhPoint_t const *, int, PhPoint_t const *, PhPoint_t const *, long);
extern int PgDrawRepImageCx(void *, void const *, int, PhPoint_t const *, PhPoint_t const *, int, PhPoint_t const *, PhPoint_t const *, long);
extern int PgDrawRepPhImageCx(void *, PhImage_t const *, int, PhPoint_t const *, PhPoint_t const *, PhPoint_t const *);
extern int PgDrawTextCx(void *, char const *, int, PhPoint_t const *, int);
extern int PgDrawTextCharsCx(void *, char const *, int, PhPoint_t const *, int);
extern int PgDrawTextAreaCx(void *, char const *, int, PhRect_t const *, int);
extern int PgDrawMultiTextAreaCx(void *, char *, int, PhRect_t *, int, int, int);
#define PgDrawStringCx(dc, ptr, pos) PgDrawTextCx(dc, ptr, strlen(ptr),pos, 0);
extern int PgContextBlitAreaCx(void *, void const *, PhArea_t const *, void const *, PhArea_t const *);
extern int PgBlitCx(void *, const PhRect_t *, const PhPoint_t *);
extern int PgMultiBlitCx(void *, unsigned short, const PhRect_t *, const PhPoint_t *);
extern int PgContextBlitCx(void *, void const *, PhRect_t const *, void const *, PhRect_t const *);
extern int PgContextBlit(void const *, PhRect_t const *, void const *, PhRect_t  const *);
extern int PgSetDrawBufferSizeCx(void *, unsigned short);
extern int PgSetHardwarePaletteCx(void *, PgColor_t const *, long, short, short, int, long);
extern int PgReleasePaletteCx(void *, long);
extern int PgFFlushCx(void *, unsigned int);
extern int PgFlushCx(void *);
extern int PgSyncFlushCx(void *);
extern void PgClearDrawBufferCx(void *);
extern void PgSetRegionCx(void *, PhRid_t);
extern PhRid_t PgGetRegionCx(void *);
extern void PgSetTargetRidCx(void *, PhRid_t);
extern PhRid_t PgGetTargetRidCx(void *);
extern int PgDrawGradientCx(void *, PhPoint_t *, PhPoint_t *, long unsigned, long unsigned, long, PgColor_t, PgColor_t, PgColor_t, PgColor_t, long unsigned, char unsigned *);

int PgDeleteCursorCx(void *, int);
int PgSetCursorPosCx(void *, int, int, int);
int PgSetDragPosCx(void *, int, int, int, int, int);
int PgSetCursorCharCx(void *, int, PgColor_t, PgColor_t, int, int);
int PgSetCursorBitmapCx(void *, int, int, PgCursorDef_t const *);

void PgWaitVSyncCx(void *);
extern int PgSwapDisplayCx(void *, PdOffscreenContext_t *, unsigned long);

/* Draw functions that insert iov_t's into the supplied DC's command buffer */
extern int PgDrawPolygonCxv(void *, PhPoint_t const *, int, PhPoint_t const *, int);
extern int PgDrawPixelArrayCxv(void *, PhPoint_t const *, int, PhPoint_t const *);
extern int PgDrawSpanCxv(void *, PgSpan_t const *, int, PhPoint_t const *, int);
extern int PgDrawBezierCxv(void *, PhPoint_t const *, int, PhPoint_t const *, int);
extern int PgDrawTrendCxv(void *, short const *, PhPoint_t const *, int, int, int, int, unsigned);
extern int PgDrawBitmapCxv(void *, void const *, int, PhPoint_t const *, PhPoint_t const *, int, long);
extern int PgDrawImageCxv(void *, void const *, int, PhPoint_t const *, PhDim_t const *, int, long);
extern int PgDrawPhImageCxv(void *, PhPoint_t const *, PhImage_t const *, int);
extern int PgDrawPhImageRectCxv(void *, PhPoint_t const *, PhImage_t const *, PhRect_t const *, int);
extern int PgDrawTImageCxv(void *, void const *, int, PhPoint_t const *, PhDim_t const *, int, long, void const *, int);
extern int PgDrawRepTImageCxv(void *, void const *, int, PhPoint_t const *, PhPoint_t const *, int, PhPoint_t const *, PhPoint_t const *, long, void const *, int);
extern int PgDrawRepBitmapCxv(void *, void const *, int, PhPoint_t const *, PhPoint_t const *, int, PhPoint_t const *, PhPoint_t const *, long);
extern int PgDrawRepImageCxv(void *, void const *, int, PhPoint_t const *, PhPoint_t const *, int, PhPoint_t const *, PhPoint_t const *, long);
extern int PgDrawRepPhImageCxv(void *, PhImage_t const *, int, PhPoint_t const *, PhPoint_t const *, PhPoint_t const *);
extern int PgDrawTextCxv(void *, char const *, int,PhPoint_t const *, int);
#define PgDrawStringCxv(dc, ptr, pos) PgDrawTextCxv(dc, ptr, strlen(ptr), pos, 0);

/* Functions that work on the "current" Photon GC */
#define PgSetMultiClip(a, b) \
	PgSetMultiClipCx(PgGetGC(), a, b)
#define PgSetMultiClipTiles(a) \
	PgSetMultiClipTilesCx(PgGetGC(), a)
#define PgSetStrokeColor(a) \
	PgSetStrokeColorCx(PgGetGC(), a)
#define PgSetStrokeXORColor(a, b) \
	PgSetStrokeXORColorCx(PgGetGC(), a, b)
#define PgSetStrokeDither(a, b, c) \
	PgSetStrokeDitherCx(PgGetGC(), a, b, c)
#define PgSetStrokeTransPat(a) \
	PgSetStrokeTransPatCx(PgGetGC(), a)
#define PgSetStrokeFWidth(a) \
	PgSetStrokeFWidthCx(PgGetGC(), a)
#define PgSetStrokeWidth(a) \
	PgSetStrokeWidthCx(PgGetGC(), a)
#define PgSetStrokeCap(a) \
	PgSetStrokeCapCx(PgGetGC(), a)
#define PgSetStrokeJoin(a) \
	PgSetStrokeJoinCx(PgGetGC(), a)
#define PgSetStrokeDash(a, b, c) \
	PgSetStrokeDashCx(PgGetGC(), a, b, c)
#define PgSetFillColor(a) \
	PgSetFillColorCx(PgGetGC(), a)
#define PgSetColorModel(a) \
	PgSetColorModelCx(PgGetGC(), a)
#define PgGetColorModel() \
	PgGetColorModelCx(PgGetGC())
#define PgSetFillXORColor(a, b) \
	PgSetFillXORColorCx(PgGetGC(), a, b)
#define PgSetFillDither(a, b, c) \
	PgSetFillDitherCx(PgGetGC(), a, b, c)
#define PgSetFillTransPat(a) \
	PgSetFillTransPatCx(PgGetGC(), a)
#define PgSetTextColor(a) \
	PgSetTextColorCx(PgGetGC(), a)
#define PgSetTextXORColor(a, b) \
	PgSetTextXORColorCx(PgGetGC(), a, b)
#define PgSetTextDither(a, b, c) \
	PgSetTextDitherCx(PgGetGC(), a, b, c)
#define PgSetTextTransPat(a) \
	PgSetTextTransPatCx(PgGetGC(), a)
#define PgSetFont(a) \
	PgSetFontCx(PgGetGC(), a)
#define PgSetUnderline(a, b, c) \
	PgSetUnderlineCx(PgGetGC(), a, b, c)
#define PgSetExtendedTextFlags(a) \
	PgSetExtendedTextFlagsCx(PgGetGC(), a)
#define PgSetPlaneMask(a) \
	PgSetPlaneMaskCx(PgGetGC(), a)
#define PgSetDrawMode(a) \
	PgSetDrawModeCx(PgGetGC(), a)
#define PgSetClipping(a, b) \
	PgSetClippingCx(PgGetGC(), a, b)
#define PgSetUserClip(a) \
	PgSetUserClipCx(PgGetGC(), a)
#define PgSetUserClipAbsolute(a) \
	PgSetUserClipAbsoluteCx(PgGetGC(), a)
#define PgSetTranslation(a, b) \
	PgSetTranslationCx(PgGetGC(), a, b)
#define PgClearTranslation() \
	PgClearTranslationCx(PgGetGC())
#define PgSetChroma(a, b) \
	PgSetChromaCx(PgGetGC(), a, b)
#define PgChromaOff() \
	PgChromaOffCx(PgGetGC())
#define PgChromaOn() \
	PgChromaOnCx(PgGetGC())
#define PgSetAlphaBlend(a, b) \
	PgSetAlphaBlendCx(PgGetGC(), a, b)
#define PgSetAlpha(a, b, c, d, e) \
	PgSetAlphaCx(PgGetGC(), a, b, c, d, e)
#define PgAlphaOff() \
	PgAlphaOffCx(PgGetGC())
#define PgAlphaOn() \
	PgAlphaOnCx(PgGetGC())
#define PgGetTranslation(a) \
	PgGetTranslationCx(PgGetGC(), a)

/* Functions that work on the "current" Draw Context */
#define PgSetGC(a) \
	PgSetGCCx(PhDCGetCurrent(), a)
#define PgGetGC() \
	PgGetGCCx(PhDCGetCurrent())
#define PgBevelBox( a, b, c, d, e, f, g, h, i, j) \
	PgDrawGradientBevelBoxCx(PhDCGetCurrent(), a, b, c, d, d, e, f, g, h, i, j)
#define PgContrastBevelBox(a, b, c, d, e, f, g, h, i)\
	PgContrastBevelBoxCx(PhDCGetCurrent(), a, b, c, d, e, f, g, h, i)
#define PgDrawGradientBevelBox(a, b, c, d, e, f, g, h, i, j, k) \
	PgDrawGradientBevelBoxCx(PhDCGetCurrent(), a, b, c, d, e, f, g, h, i, j, k)
#define PgDrawBorder(a, b, c, d) \
	PgDrawBorderCx(PhDCGetCurrent(), a, b, c, d)
#define PgDrawArrow(a, b, c, d) \
	PgDrawArrowCx(PhDCGetCurrent(), a, b, c, d)
#define PgDrawPixel(a) \
	PgDrawPixelCx(PhDCGetCurrent(), a)
#define PgDrawIPixel(a, b) \
	PgDrawIPixelCx(PhDCGetCurrent(), a, b)
#define PgDrawGrid(a, b)\
	PgDrawGridCx(PhDCGetCurrent(), a, b)
#define PgDrawLine(a, b) \
	PgDrawLineCx(PhDCGetCurrent(), a, b)
#define PgDrawILine(a, b, c, d) \
	PgDrawILineCx(PhDCGetCurrent(), a, b, c, d)
#define PgDrawRect(a, b) \
	PgDrawRectCx(PhDCGetCurrent(), a, b)
#define PgDrawIRect(a, b, c, d, e) \
	PgDrawIRectCx(PhDCGetCurrent(), a, b, c, d, e)
#define PgDrawRoundRect(a, b, c) \
	PgDrawRoundRectCx(PhDCGetCurrent(), a, b, c)
#define PgDrawBevelBox(a, b, c, d) \
	PgDrawBevelBoxCx(PhDCGetCurrent(), a, b, c, d)
#define PgDrawIBevelBox(a, b, c, d, e, f, g) \
	PgDrawIBevelBoxCx(PhDCGetCurrent(), a, b, c, d, e, f, g)
#define PgDrawEllipse(a, b, c) \
	PgDrawEllipseCx(PhDCGetCurrent(), a, b, c)
#define PgDrawArc(a, b, c, d, e) \
	PgDrawArcCx(PhDCGetCurrent(), a, b, c, d, e)
#define PgDrawPolygon(a, b, c, d) \
	PgDrawPolygonCx(PhDCGetCurrent(), a, b, c, d)
#define PgDrawPixelArray(a, b, c) \
	PgDrawPixelArrayCx(PhDCGetCurrent(), a, b, c)
#define PgDrawSpan(a, b, c, d) \
	PgDrawSpanCx(PhDCGetCurrent(), a, b, c, d)
#define PgDrawBezier(a, b, c, d) \
	PgDrawBezierCx(PhDCGetCurrent(), a, b, c, d)
#define PgDrawTrend(a, b, c, d, e, f, g) \
	PgDrawTrendCx(PhDCGetCurrent(), a, b, c, d, e, f, g)
#define PgDrawBitmap(a, b, c, d, e, f) \
	PgDrawBitmapCx(PhDCGetCurrent(), a, b, c, d, e, f)
#define PgDrawImage(a, b, c, d, e, f) \
	PgDrawImageCx(PhDCGetCurrent(), a, b, c, d, e, f)
#define PgDrawPhImage(a, b, c) \
	PgDrawPhImageCx(PhDCGetCurrent(), a, b, c)
#define PgDrawTImage(a, b, c, d, e, f, g, h) \
	PgDrawTImageCx(PhDCGetCurrent(), a, b, c, d, e, f, g, h)
#define PgDrawRepTImage(a, b, c, d, e, f, g, h, i, j) \
	PgDrawRepTImageCx(PhDCGetCurrent(), a, b, c, d, e, f, g, h, i, j)
#define PgDrawBeveled(a, b, c, d, e) \
	PgDrawBeveledCx(PhDCGetCurrent(), a, b, c, d, e)
#define PgDrawRepBitmap(a, b, c, d, e, f, g, h) \
	PgDrawRepBitmapCx(PhDCGetCurrent(), a, b, c, d, e, f, g, h)
#define PgDrawRepImage(a, b, c, d, e, f, g, h) \
	PgDrawRepImageCx(PhDCGetCurrent(), a, b, c, d, e, f, g, h)
#define PgDrawRepPhImage(a, b, c, d, e) \
	PgDrawRepPhImageCx(PhDCGetCurrent(), a, b, c, d, e)
#define PgDrawText(a, b, c, d) \
	PgDrawTextCx(PhDCGetCurrent(), a, b, c, d)
#define PgDrawTextChars(a, b, c, d) \
	PgDrawTextCharsCx(PhDCGetCurrent(), a, b, c, d)
#define PgDrawTextArea(a, b, c, d) \
	PgDrawTextAreaCx(PhDCGetCurrent(), a, b, c, d)
#define PgDrawString(a, b) \
	PgDrawStringCx(PhDCGetCurrent(), a, b)
#define PgDrawMultiTextArea(a, b, c, d, e, f) \
	PgDrawMultiTextAreaCx(PhDCGetCurrent(), a, b, c, d, e, f)
#define PgBlit(a, b) \
	PgBlitCx(PhDCGetCurrent(), a, b)
#define PgMultiBlit(a, b, c) \
	PgMultiBlitCx(PhDCGetCurrent(), a, b, c)
#define PgSetDrawBufferSize(a) \
	PgSetDrawBufferSizeCx(PhDCGetCurrent(), a)
#define PgFFlush(a) \
	PgFFlushCx(PhDCGetCurrent(), a)
#define PgFlush() \
	PgFlushCx(PhDCGetCurrent())
#define PgSyncFlush() \
	PgSyncFlushCx(PhDCGetCurrent())
#define PgClearDrawBuffer() \
	PgClearDrawBufferCx(PhDCGetCurrent())
#define PgSetRegion(a) \
	PgSetRegionCx(PhDCGetCurrent(), a)
#define PgGetRegion() \
	PgGetRegionCx(PhDCGetCurrent())
#define PgSetTargetRid(a) \
	PgSetTargetRidCx(PhDCGetCurrent(), a)
#define PgGetTargetRid(a) \
	PgGetTargetRidCx(PhDCGetCurrent(), a)
#define PgDeleteCursor(a) \
	PgDeleteCursorCx(PhDCGetCurrent(), a)
#define PgSetCursorPos(a, b, c) \
	PgSetCursorPosCx(PhDCGetCurrent(), a, b, c)
#define PgSetDragPos(a, b, c, d, e) \
	PgSetDragPosCx(PhDCGetCurrent(), a, b, c, d, e)
#define PgSetCursorChar(a, b, c, d, e) \
	PgSetCursorCharCx(PhDCGetCurrent(), a, b, c, d, e)
#define PgSetCursorBitmap(a, b, c) \
	PgSetCursorBitmapCx(PhDCGetCurrent(), a, b, c)
#define PgWaitVSync() \
	PgWaitVSyncCx(PhDCGetCurrent())
#define PgSwapDisplay(a, b) \
	PgSwapDisplayCx(PhDCGetCurrent(), a, b)
#define PgDrawGradient(a, b, c, d, e, f, g, h, i, j, k) \
	PgDrawGradientCx(PhDCGetCurrent(), a, b, c, d, e, f, g, h, i, j, k)




extern int PgSetPalette(PgColor_t const *,long, short ,short ,int, long);
extern int PgContextBlitArea(void const *, PhArea_t const * const, void const *, PhArea_t const * const);

/* Draw functions that insert iov_t's into the draw stream (old mx functions) */
#define PgDrawPolygonv(a, b, c, d) \
	PgDrawPolygonCxv(PhDCGetCurrent(), a, b, c, d)
#define PgDrawPixelArrayv(a, b, c) \
	PgDrawPixelArrayCxv(PhDCGetCurrent(), a, b, c)
#define PgDrawSpanv(a, b, c, d) \
	PgDrawSpanCxv(PhDCGetCurrent(), a, b, c, d)
#define PgDrawBezierv(a, b, c, d) \
	PgDrawBezierCxv(PhDCGetCurrent(), a, b, c, d)
#define PgDrawTrendv(a, b, c, d, e, f, g) \
	PgDrawTrendCxv(PhDCGetCurrent(), a, b, c, d, e, f, g)
#define PgDrawBitmapv(a, b, c, d, e, f) \
	PgDrawBitmapCxv(PhDCGetCurrent(), a, b, c, d, e, f)
#define PgDrawImagev(a, b, c, d, e, f) \
	PgDrawImageCxv(PhDCGetCurrent(), a, b, c, d, e, f)
#define PgDrawPhImagev(a, b, c) \
	PgDrawPhImageCxv(PhDCGetCurrent(), a, b, c)
#define PgDrawPhImageRectv(a, b, c, d) \
	PgDrawPhImageRectCxv(PhDCGetCurrent(), a, b, c, d)
#define PgDrawTImagev(a, b, c, d, e, f, g, h) \
	PgDrawTImageCxv(PhDCGetCurrent(), a, b, c, d, e, f, g, h)
#define PgDrawRepTImagev(a, b, c, d, e, f, g, h, i, j) \
	PgDrawRepTImageCxv(PhDCGetCurrent(), a, b, c, d, e, f, g, h, i, j)
#define PgDrawRepBitmapv(a, b, c, d, e, f, g, h) \
	PgDrawRepBitmapCxv(PhDCGetCurrent(), a, b, c, d, e, f, g, h)
#define PgDrawRepImagev(a, b, c, d, e, f, g, h) \
	PgDrawRepImageCxv(PhDCGetCurrent(), a, b, c, d, e, f, g, h)
#define PgDrawRepPhImagev(a, b, c, d, e) \
	PgDrawRepPhImageCxv(PhDCGetCurrent(), a, b, c, d, e)
#define PgDrawTextv(a, b, c, d) \
	PgDrawTextCxv(PhDCGetCurrent(), a, b, c, d)
#define PgDrawStringv(a, b) \
	PgDrawStringCxv(PhDCGetCurrent(), a, b)
	
/* Old mx functions, these are deprecated and to be removed at a later date (likely when the major version number of the library
 * gets bumped from .3 to .4)
 */
#define PgDrawPolygonmx		PgDrawPolygonv
#define PgDrawPixelArraymx	PgDrawPixelArrayv
#define PgDrawSpanmx		PgDrawSpanv
#define PgDrawBeziermx		PgDrawBezierv
#define PgDrawTrendmx		PgDrawTrendv
#define PgDrawBitmapmx		PgDrawBitmapv
#define PgDrawImagemx		PgDrawImagev
#define PgDrawPhImagemx		PgDrawPhImagev
#define PgDrawPhImageRectmx	PgDrawPhImageRectv
#define PgDrawTImagemx		PgDrawTImagev
#define PgDrawRepTImagemx	PgDrawRepTImagev
#define PgDrawRepBitmapmx	PgDrawRepBitmapv
#define PgDrawRepImagemx	PgDrawRepImagev
#define PgDrawRepPhImagemx	PgDrawRepPhImagev
#define PgDrawTextmx		PgDrawTextv
#define PgDrawStringmx		PgDrawStringv

extern int PhDCInit(void *, int, long , int (*flush)(PhDrawContext_t *dc, int Subtype), int (*modify)(PhDrawContext_t *dc, int acquire, void *data));
extern int PhDCPurge(void *);
extern int PhDCSetFlags( void *, int, int);
extern PhDrawContext_t * PhDCGetCurrent( void );
extern PhDrawContext_t *PhDCSetCurrent(void *);
extern PhDrawContext_t *PhDCCreate(int, long, int (*flush)(PhDrawContext_t *dc, int Subtype), int (*modify)(PhDrawContext_t *dc, int acquire, void *data));
int PdLockDefaultDC(int);
int PdLockCurrentDC(int);
int PdUnlockDefaultDC(void);
int PdUnlockCurrentDC(void);

int PdDefaultFlush(PhDrawContext_t *dc, int force);
PhDrawContext_t * PdSetDefaultDC(PhDrawContext_t *dc);

extern int PhDCRelease(void *);
extern int PhDCGetType(void  *);

extern int PdGetDevices (PhRid_t *, uint32_t);
extern PhRid_t PdSetTargetDevice (void *, PhRid_t);

/* Offscreen Contexts. This is a DC that represents an area of memory allocated by io-graphics to use
 * for rendering.  Similar to Memory Contexts, except that io-graphics still does the rendering
 * and uses hardware acceleration when possible.  Generally they are in video ram, but they can
 * be in system ram if the driver decides to put it there.
 */
extern int PdSetOffscreenTranslationCx (void *, PdOffscreenContext_t *, PhPoint_t *);
#define PdSetOffscreenTranslation(a, b) \
	PdSetOffscreenTranslationCx(PhDCGetCurrent(), a, b)


extern PgSurface_t * PgCreateSurface (const PhRid_t, const unsigned int, const PhDim_t *, const unsigned int);
extern int PgDestroySurface (PgSurface_t *);
extern PgSurface_t * PgDupSurface (PhRid_t const, PgSurface_t const *, unsigned int const);
extern PgSurface_t * PgGetFirstSurface (PhRid_t const device, PgSurface_t *);
extern PgSurface_t * PgGetLastSurface (PhRid_t const device, PgSurface_t *);
extern PgSurface_t * PgGetNextSurface (PgSurface_t const *, PgSurface_t *);
extern PgSurface_t * PgGetPrevSurface (PgSurface_t const *, PgSurface_t *);
extern PhConnectId_t PgGetSurfaceMgr(PgSurface_t const *);
extern PhRid_t PgGetSurfaceRid(PgSurface_t const *);
extern PgSurfaceProps_t * PgGetSurfaceProps (PgSurface_t *, PgSurfaceProps_t *);
extern PgSurface_t * PdGetOffscreenSurface(PdOffscreenContext_t *);
extern int PgGetSurfaceGFSid (PgSurface_t * surf, uint32_t * sid);


/* Memory Contexts.  This is a DC that doesn't communication with io-graphics.  All DC operations
 * are done locally by the application with out hardware acceleration.  These use PhImage_t's as the
 * memory buffers to draw into.
 */
extern PmMemoryContext_t * __PmCreateMC( PhImage_t *image, PhDim_t *dim, PhPoint_t *pos,
	struct _doc_ctrl *(*mc_open)( struct _doc_ctrl *c, PhImage_t *img, PhPoint_t *pos, PhDim_t *dim ),
	int (*mc_render)( struct _doc_ctrl *c, void *buf, int len, int nclips, PhRect_t *clip_list  ), 
	int (*mc_clear)( struct _doc_ctrl *c, unsigned long color ), 
	int (*mc_getimage)( struct _doc_ctrl *c, PhImage_t *img ), 
	int (*mc_close)( struct _doc_ctrl *c ) 
	);
extern void PmMemReleaseMC(PmMemoryContext_t *);
extern int PmMemFlush(PmMemoryContext_t *, PhImage_t *);
extern PhDrawContext_t * PmMemStart(PmMemoryContext_t *);
extern PhDrawContext_t * PmMemStop(PmMemoryContext_t *);
extern struct _Ph_g_info * PmMemGetGin(PmMemoryContext_t *);
extern int PmMemGetType(PmMemoryContext_t *);
extern int PmMemGetMaxBufSize(PmMemoryContext_t *);
extern void PmMemSetMaxBufSize(PmMemoryContext_t *, int);
extern int PmMemGetChunkSize(PmMemoryContext_t *);
extern void PmMemSetChunkSize(PmMemoryContext_t *, int);
extern void PmMemSetType(PmMemoryContext_t *, int);

/* Photon Graphics Service Messages */
extern int PgWaitHWIdle(void);
extern void PgWaitDrawComplete(void);
extern unsigned long PgReadScreenSize(PhRect_t const *);
extern PhImage_t *PgReadScreen(PhRect_t const *, void *);
extern int PgColorMatch(int, PgColor_t const *, PgColor_t *);
extern int PgGetPalette(PgColor_t *);

extern PgColor_t PgGetOverlayChromaColor(void);
extern PgVideoChannel_t *PgCreateVideoChannel(unsigned, unsigned);
extern void PgDestroyVideoChannel(PgVideoChannel_t *);
extern int PgGetScalerCapabilities(PgVideoChannel_t *, int, PgScalerCaps_t *);
extern int PgConfigScalerChannel(PgVideoChannel_t *, PgScalerProps_t *);
extern int PgNextVideoFrame(PgVideoChannel_t *);

extern int PgGetVideoMode(PgDisplaySettings_t *);
extern int PgGetVideoModeInfo(unsigned short, PgVideoModeInfo_t *);
extern int PgGetVideoModeList(PgVideoModes_t *);
extern int PgSetVideoMode(PgDisplaySettings_t *);

extern int PgGetGraphicsHWCaps(PgHWCaps_t *);

/* Misc Pg funcs -- aren't graphical service messages, and aren't draw stream (DC or GC based) */
/* -- Text Extenting Functions */
extern void PgExtentInit(void);
extern PhRect_t *PgExtentText(PhRect_t *,PhPoint_t const *,char const *,char const *,unsigned int);
extern PhRect_t *PgExtentMultiText(PhRect_t *, PhPoint_t *, char *, char *, unsigned, int);
extern PhRect_t *PgExtentTextChars(PhRect_t *, PhPoint_t const *, char const *, char const *, unsigned);
extern PhRect_t *PgExtentTextBytes(PhRect_t *, PhPoint_t const *, char const *, char const *, unsigned);

/* -- Color Functions */
extern PgColor_t PgHSV(unsigned int ,int ,int);
extern PgColor_t PgHSV2RGB(PgColorHSV_t);
extern PgColorHSV_t PgRGB2HSV(PgColor_t);
extern PgColorCMYK_t PgRGB2CMYK(PgColor_t);
extern void PgBackgroundShadings(PgColor_t, PgColor_t *, PgColor_t *);
extern char const *PgCMChannelName(PgColorModel_t const *, uchar_t);
extern PgPalette_t *PgCreatePgPalette(char const *, ushort_t, PgColorModel_t const *);
extern void PgReleasePgPalette(PgPalette_t *);
extern PgPalette_t *PgLoadPgPalette(char const *);
extern int PgWritePgPalette(PgPalette_t const *, char const *);

/* -- Shared Memory Functions */
extern int PgShmemAttach(char const *, unsigned long , void *);
extern int PgShmemDetach(void *);
extern void *PgShmemCreate(unsigned long , char const *);
extern int PgShmemDestroy(void *);
extern void PgShmemCleanup();
extern int PgShmemCtrl(void *, int);

/* Photon Image Functions */
extern void PhReleaseImage(PhImage_t *);
extern PhImage_t *PhCreateImage(PhImage_t *, short, short, int, PgColor_t const *, int, int );
extern int PhMakeGhostBitmap(PhImage_t *);
extern int PhMakeTransparent(PhImage_t *, PgColor_t);
extern int PhMakeTransBitmap(PhImage_t *, PgColor_t);

/* Photon Cursor Functions */
extern void PhMoveCursorRel(int, int, int);
extern void PhMoveCursorAbs(int, int, int);
extern int PhQueryCursor(unsigned short, PhCursorInfo_t *);

/* Photon Drag and Drop Functions */ 
extern int PhInitDnd(PhRid_t, unsigned short, PhPoint_t const *, unsigned, unsigned short , unsigned short,	unsigned long, PhDndCursors_t const *, unsigned short, void const *, unsigned );
extern int PhInitDndv(
		PhRid_t rid, unsigned short flags, PhPoint_t const *pos, unsigned ig,
		unsigned short button_state, unsigned short button_mask,
		unsigned long handle, PhDndCursors_t const *cursors,
		unsigned short data_format, unsigned nparts, iov_t *iov
		);
extern int PhCancelDnd(PhRid_t, unsigned, PhPoint_t const *, unsigned, unsigned long);
extern int PhAckDnd( PhEvent_t *event, unsigned subtype, PhCursorDescription_t *cur );
extern int PhInitDrag(PhRid_t, unsigned, const PhRect_t *, const PhRect_t *, unsigned int, const PhDim_t *, const PhDim_t *, const PhDim_t *, const PhPoint_t *, const PhCursorDescription_t *);
extern int PhCancelDrag( PhRid_t rid, unsigned input_group, unsigned flags );

/* Photon Rectangle Functions */
extern int PhRectIntersect(PhRect_t *, PhRect_t const *);
extern int PhRectUnion(PhRect_t *, PhRect_t const *);

/* Photon Tile Functions */
extern PhTile_t *   PhAddTiles( PhTile_t *, PhTile_t *);
extern PhTile_t * 	PhAddMergeTiles(PhTile_t *, PhTile_t *, int *);
extern PhTile_t *	PhClipTilings(PhTile_t *, PhTile_t const * const, PhTile_t **);
extern PhTile_t *	PhCoalesceTiles(PhTile_t *);
extern PhTile_t *	PhCopyTiles(PhTile_t const * const);
extern PhTile_t *	PhDeTranslateTiles(PhTile_t *, PhPoint_t const * const);
extern void			PhFreeTiles(PhTile_t *);
extern PhTile_t *	PhGetTile(void);
extern PhTile_t *	PhIntersectTilings(PhTile_t const * const, PhTile_t const *, unsigned short * const);
extern PhTile_t * 	PhMergeTiles(PhTile_t *);
extern PhTile_t *	PhRectsToTiles(PhRect_t const *, int const);
extern PhTile_t * 	PhSortTiles(PhTile_t *);
extern PhRect_t *	PhTilesToRects(PhTile_t const *, int * const);
extern PhTile_t *	PhTranslateTiles(PhTile_t *, PhPoint_t const * const);
extern PhTile_t *	PhResetTileList(PhTile_t *, PhRect_t const * const);
extern PhTile_t *	PhClipRects( PhRect_t const * const, PhRect_t const * const);
extern void			PhTilesBoundingRect( const PhTile_t *, PhRect_t * );
extern void			PhRectsBoundingRect( const PhRect_t *, int, PhRect_t * );

/* Photon Region Functions */
extern PhRid_t PhRegionOpen(unsigned, PhRegion_t const *, PhRect_t const *, void const *);
extern int PhRegionClose(PhRid_t);
extern int PhRegionChange(unsigned long, unsigned long, PhRegion_t const *, PhRect_t const *, void const *);
extern int PhBlit(PhRid_t, const PhRect_t *, const PhPoint_t *);
extern int PhMultiBlit(PhRid_t, unsigned short, const PhRect_t [], const PhPoint_t *);
extern int PhQueryRids(unsigned, PhRid_t, unsigned, unsigned, unsigned, PhRid_t, const PhRect_t *, PhRid_t *, int);
extern int PhRegionInfo(PhRid_t, PhRegion_t *, PhRect_t *, unsigned int, void *, unsigned int);
extern PhRegionDataHdr_t *PhRegionGetData(PhRid_t, short, PhRegionDataHdr_t *, size_t);
extern PhRegionDataHdr_t *PhRegionDataFindType(PhRegion_t const *, PhRegionDataHdr_t const *, ushort_t);
extern PhRegionDataHdr_t *PhRegionDataNext(PhRegion_t const *, void const *, PhRegionDataHdr_t const *);

/* Photon Server Functions */
extern struct _Ph_ctrl *PhAttach(char const *, PhChannelParms_t const *);
extern struct _Ph_ctrl *PhReattach(struct _Ph_ctrl *);
extern struct _Ph_ctrl *PhReattachRaw(struct _Ph_ctrl *);
extern int PhDetach(struct _Ph_ctrl *);
extern int PhInfo(struct _Ph_ctrl *, unsigned int, void *, int);
extern struct _Ph_ctrl *PhOpen(char const *, PhChannelParms_t const *);
extern PhSysInfo_t * PhQuerySystemInfo(PhRid_t, PhRect_t const *, PhSysInfo_t *);
extern PhConnectId_t PhGetConnectId(void);
extern PhConnectId_t PhGetConnectInfo(PhConnectId_t, PhConnectInfo_t *);
extern int PhChannelAttach(int, int, struct sigevent const *);
extern int PhNotify (const struct sigevent *);
extern int PhTimerArm(PhRid_t, long, unsigned);
extern int PhSetChannelSensitivity( unsigned long mask );

/* Photon Event Functions */
extern int _PhEventCtrl(unsigned, void const *, unsigned);
extern int PhEventEmitmx(PhEvent_t const *, PhRect_t const *, int, iov_t *);
extern int PhEventEmit(PhEvent_t const *, PhRect_t const *, void const *);
extern int PhEmitmx(PhEvent_t const *, PhRect_t const *, int, iov_t *);
extern int PhEmit(PhEvent_t const *, PhRect_t const *, void const *);
extern int PhChannelEventmx( PhChannelEv_t const *event, int sparts, iov_t *smx );
extern int PhChannelEvent( PhChannelEv_t const *event, void const *data );
extern int PhEventNext(void *, unsigned);
extern int PhEventPeek(void *, unsigned);
extern int PhEventArm(void);
extern int PhEventRead(pid_t, void *, unsigned);
extern unsigned PhGetMsgSize(PhEvent_t const *);
extern int PhInputGroup(PhEvent_t const *);
extern int PhTo8859_1(PhKeyEvent_t const *);
extern int PhKeyToMb(char *, PhKeyEvent_t const *);

/* Photon Service Functions */
extern int _PhRegisterService(unsigned);
extern int _PhDeregisterService(unsigned);
extern int PhServiceCommMx(PhConnectId_t, int unsigned const, int unsigned const, iov_t	*, int, iov_t *, int);
extern int PhByPassServiceCommMx(PhConnectId_t, pid_t, int unsigned const, int unsigned const, iov_t *, int , iov_t *, int);
extern int PhSendServiceRequestMx(int unsigned const, int unsigned const, iov_t *, int, iov_t *, int);
extern int PhReplyToServiceRequestMx(PhConnectId_t, int unsigned const, iov_t *, int, iov_t *, int);
extern int PhReplyToServiceRequest(PhConnectId_t, int unsigned const, void const * const, int unsigned const, void *, int);
extern int PhReplyToServiceHdrRequest(PhConnectId_t, int unsigned const, int unsigned const, int unsigned const, void const * const, int unsigned const, void *, int);
extern int PhSendServiceHdrRequest(int, int, int, int, void const *, int unsigned const, void *, int);
extern int PhSendServiceRequest(int unsigned const, int unsigned const, void const * const, int unsigned const, void *, int);
extern int PhSendGraphicsService(int unsigned const, iov_t *, int, iov_t *, int);

/* Photon Window Functions */
extern PhRid_t PhWindowOpen(unsigned, const PhRegion_t *, const PhRect_t *, const PhWindowInfo_t *);
extern int PhWindowChange(unsigned, unsigned, const PhRegion_t *, const PhRect_t *, const PhWindowInfo_t *);
extern int PhWindowClose(PhRid_t);
extern int PhWindowEvent(const PhWindowEvent_t *);
extern int PhWindowQueryVisible(unsigned, PhRid_t, unsigned, PhRect_t *);

/* Photon Clipboard Functions */
/* the following five functions are being deprecated */
extern int PhClipboardCopy(unsigned short, int, PhClipHeader const *);
extern void *PhClipboardPasteStart(unsigned short);
extern PhClipHeader *PhClipboardPasteType(void *, PhClipType);
extern PhClipHeader *PhClipboardPasteTypeN(void *, int);
extern void PhClipboardPasteFinish(void *);

/* use these functions instead */
extern int32_t PhClipboardWrite(unsigned short, uint32_t, PhClipboardHdr const *);
extern PhClipboardHdr *PhClipboardRead(unsigned short, PhClipType);
extern int PhClipboardCopyString(unsigned short, const char *);
extern char *PhClipboardPasteString(unsigned short);

/* Photon Library Misc */
extern unsigned PhLibVersion(void);

/* 
 * LAYERS 
 */
int PgGetLayerCaps(int layer, int format_index, PgLayerCaps_t *const caps);
int PgSetLayerArg(int layer, int arg, void *data, int data_len);
PdOffscreenContext_t *PgCreateLayerSurface(int layer, int surface, 
        int format_index, unsigned short width, unsigned short height,
        unsigned long flags);
int PgSetLayerSurface(int layer, int surface, PdOffscreenContext_t *osc);
int PgLockLayer(int layer);
int PgUnlockLayer(int layer);

PhRid_t PgCreateDriverRegion(PdOffscreenContext_t *osc, 
        PhPoint_t *const origin, PhRect_t *const rect, PhRid_t parent);

/*
 * Power Management
 */
int PgSetDPMSMode(int mode);

/*
 * PHOOK
 */
int PgPHookRegister(char const * phook);

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PhProto.h $ $Rev: 236523 $" )
#endif
