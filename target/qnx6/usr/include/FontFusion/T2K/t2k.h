/*
 * T2K.h
 *
 * $Header: /home/archive/FontFusion/FontFusion/core/t2k.h,v 1.19 2009/07/10 09:39:00 rpasricha Exp $
 *
 * Font Fusion Copyright (c) 1989-2009 all rights reserved by Bitstream Inc.
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

#ifndef __T2K_T2K__
#define __T2K_T2K__

#ifndef FF_FFCONFIG_HEADER
#include "config.h"
#else
#include FF_FFCONFIG_HEADER
#endif /* FF_FFCONFIG_HEADER */

#include FF_DTYPES_HEADER
#include FF_TSIMEM_HEADER
#include FF_T2KSTRM_HEADER
#include FF_TRUETYPE_HEADER
#include FF_GLYPH_HEADER

#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif  /* __cplusplus */





#ifdef T2K_DOCUMENTATION
-------------------------

Q&A Section:

Q1) What files do I need to look at?
A1) First you need to familiarize yourself with this file "T2K.H"."T2K.H" contains
	documentation, a coding example and the actual T2K API.
	Second you need to look at "CONFIG.H". "CONFIG.H" is the only file you normally
	need to edit. The file configures T2K for your platform, and it enables
	or disables optional features, and it allows you to build debug or non-debug versions.
	The file itself contains more information. Turn off features you do not need in order
	to minimize the size of the T2K font engine.
-------------------------
Q2) What is the basic principle for the usage of T2K API?
A2) The basic idea is that T2K was designed to be object oriented, even though the
	actual implementation is only using ANSI C. This means that you will be creating
	a number of objects when you use T2K. All classes have a constructor and destructor.
	It is important that you call the proper destructor when you are done with a particular
	object.
-------------------------
Q3) What is the best way of getting T2K going on a new platform?
A3) It is best to first configure "CONFIG.H" and then look at the
	coding example below at T2K_DOCUMENTATION_CODING_EXAMPLE.
	We recommend that you start "outside in".

First create and destroy a "Memhandler" object:
(This is the "outermost" object.)

	tsiMemObject *mem = NULL;

	mem = tsi_NewMemhandler( &errCode );
	CLIENT_ASSERT( errCode == 0 );

	/* Destroy the Memhandler object. */
	tsi_DeleteMemhandler( mem );

Next create an InputStream object.

	tsiMemObject *mem = NULL;
	InputStream *in = NULL;

	mem = tsi_NewMemhandler( &errCode );
	CLIENT_ASSERT( errCode == 0 );

		/* otherwise do this if you allocated the data */
		in = New_InputStream3( mem, data1, size1, &errCode );
		CLIENT_ASSERT( errCode == 0 );

		/* Destroy the InputStream object. */
		Delete_InputStream( in, &errCode  );

	/* Destroy the Memhandler object. */
	tsi_DeleteMemhandler( mem );

Next you would create the "sfntClass" object and then finally the "T2K" scaler object.
-------------------------
Q4) Ok, then what do I do with the T2K scaler object?
A4) First you need to set the "transformation" with the
	T2K_NewTransformation() call/method. Basically you specify the
	pointsize, x and y resolution, and a 2*2 transformation matrix,
	and true/false for if you want embedded bitmaps to be enabled.

	Then you call T2K_RenderGlyph() to actually get bitmap and/or outline data.
	After you are done with the output data you need to call T2K_PurgeMemory to
	free up memory.
-------------------------
Q5) So I call T2K_RenderGlyph(), but where do I get access to the bitmap data?
A5) You get access to the bitmap data through public fields in the T2K class/structure.
	Find the following fields:
	/* Begin bitmap data */
	long width, height;
	F26Dot6 fTop26Dot6, fLeft26Dot6;
	long rowBytes;
	unsigned char *baseAddr; /* unsigned char baseAddr[N], 	N = t->rowBytes * t->height */
	uint32 *baseARGB;
	/* End bitmap data */

	baseAddr is either a bit-array, or a byte array.
	baseARGB is a 32 bit array (ARGB) used for color bitmaps.
-------------------------
Q6) Can you give me a simple/naive example of how to actually draw a character?
A6) Ok, something like this should work:
/*
 *	Slow naive example on how to get bitmap data from the T2K scaler object.
 *  The example assumes a screen-coordinate system where the top leftmost position on the screen is 0,0.
 */
static void MyDrawCharExample( T2K *scaler, int x, int y )
{
	uint16 left, right, top, bottom;
	unsigned short R, G, B, alpha;
	uint32 *baseARGB = NULL;
	int xi, yi, xd;
	char *p;

	p = (char *)scaler->baseAddr;
	baseARGB = scaler->baseARGB;

	left	= 0 + x;
	top		= 0 + y;
	right	= scaler->width  + x;
	bottom	= scaler->height + y;


	if ( baseARGB == NULL && p == NULL )
		return; /*****/

	CLIENT_ASSERT( T2K_BLACK_VALUE == 126 );

	MoveTo( x, y );

	for ( yi = top; yi < bottom; yi++ ) {
		for ( xi = left; xi < right; xi++ ) {
			xd = xi - left;

#ifdef USE_COLOR
			if ( baseARGB != NULL ) {
				alpha = baseARGB[xd] >> 24;			/* Extract alpha */
				R = (baseARGB[xd] >> 16) & 0xff;	/* Extract Red */
				G = (baseARGB[xd] >>  8) & 0xff;	/* Extract Green */
				B = (baseARGB[xd] >>  0) & 0xff;	/* Extract Blue */
			} else {
				alpha = p[xd];
				alpha = alpha + alpha + (alpha>>5); /* map [0-126] to [0,255] */
				R = G = B = 0;						/* Set to Black */
			}

			if ( alpha ) {
				RGBColor colorA, colorB;		/* RGBColor contains 16 bit color info for R,G,B each */

				GetCPixel( xi, yi, &colorB );	/* Get the background color */
				alpha++; /* map to 0-256 */
				/* newAlpha = old_alpha + (1.0-old_alpha) * alpha */
				/* Blend foreground and background colors */
				R = (((long)(256-alpha) * (colorB.red	>> 8) 	+ alpha * R	)>>8);
				G = (((long)(256-alpha) * (colorB.green	>> 8) 	+ alpha * G )>>8);
				B = (((long)(256-alpha) * (colorB.blue	>> 8) 	+ alpha * B )>>8);

				CLIENT_ASSERT( R >= 0 && R <= 255 );

				colorA.red		= R << 8;	/* Map 8 bit data to 16 bit data */
				colorA.green	= G << 8;
				colorA.blue		= B << 8;
				RGBForeColor( &colorA );	/* Set the forground color/paint to colorA */
				MoveTo( xi, yi );			/* Paint pixel xi, yi with colorA */
				LineTo( xi, yi );
			}
#else
			/* Paint pixel xi, yi */
			if ( p[ xd>>3] & (0x80 >> (xd&7)) ) {
				MoveTo( xi, yi );
				LineTo( xi, yi );
			}
#endif
		}

		/* Advance to the next row */
		p += scaler->rowBytes;
		if ( baseARGB != NULL ) {
			baseARGB += scaler->rowBytes;
		}
	}
}
-------------------------
Q7) How do I draw a string with the above MyDrawCharExample()?
A7)

	F16Dot16 x, y;
	x = y = 12 << 16;

	while (characters to draw..)
		/* Render the character */
		T2K_RenderGlyph( scaler, charCode, 0, 0,
						 GREY_SCALE_BITMAP_HIGH_QUALITY,
						 T2K_SCAN_CONVERT, &errCode );
		CLIENT_ASSERT( errCode == 0 );
		/* Now draw the character */
		MyDrawCharExample( scaler, ((x + 0x8000)>> 16) + (scaler->fLeft26Dot6 >> 6),
								   ((y + 0x8000)>> 16) - (scaler->fTop26Dot6 >>6) );
		x += scaler->xAdvanceWidth16Dot16;	/* advance the pen forward */
		/* Free up memory */
		T2K_PurgeMemory( scaler, 1, &errCode );
		CLIENT_ASSERT( errCode == 0 );
	}
-------------------------
Q8) How do I get grey-scale or monochrome output?
A8) For monochrome output set 5th input parameter to T2K_RenderGlyph called greyScaleLevel equal to BLACK_AND_WHITE_BITMAP.
	To get grey-scale output set 5th input parameter to T2K_RenderGlyph called greyScaleLevel equal to GREY_SCALE_BITMAP_HIGH_QUALITY.
-------------------------
Q9) My output device support grey-scale. Should I use it?
A9) Yes for the best quality and end-user experience you should use grey-scale whenever possible.
-------------------------
Q10) How do I turn the T2K run-time hinting on or off?
A10) It is enabled by turning on the T2K_GRID_FIT bit in the 6th input parameterto T2K_RenderGlyph called cmd.
	 It is disabled by turning off the T2K_GRID_FIT bit in the 6th input parameterto T2K_RenderGlyph called cmd.
-------------------------
Q11) When should the T2K run-time hinting be on or off?
A11) For monochrome output your probably mostly want to turn it on.
	For a high quality display device such as a computer monitor you should probably turn it on.
	For a device such as a TV monitor you should turn it off.
-------------------------
Q12) I am using an interlacing TV as the output device. How do I make it look good?
A12) First turn off grid-fitting to get an image with less sharp transitions. (This also speeds up T2K).
	Then turn on T2K_TV_MODE if you use integer metrics and do not use fractional positioning to improve the quality.
	Then you most likely also want to experiment with a simple filter to make the image
	more blurry. A simple 3*3 convolution is probably sufficient. You should
	probably "average" more in the y-direction than the x-direction to avoid the
	interlacing flicker. Alternatively your HW may have alrady have this built in.
-------------------------
Q13) A T2K call/method returned an error. What should the code do?
A13) T2K automatically deletes all of its objects when it hits an error.
	This means that all references to T2K objects become invalid, and can no
	longer be used.
-------------------------
Q14) I noticed that there are a lot of asserts in the code...Why?
A14) Asserts are in the code to detect/prevent programmer errors. The idea is that an
	assert should never happen in real life. They are only there to catch programmer errors.
	In a release build you need to turn off asserts in "CONFIG.H" to increase speed and
	to reduce the code size. However in debug builds please leave it on, to ensure that
	everything is working as intended.
-------------------------
Q15) How do I decide what mapping table (character set) to use in a TrueType or T2K font?
A15) Use Set_PlatformID( scaler, ID ), and Set_PlatformSpecificID( scaler, ID )
	To use the Unicode mapping used by Windows do the following:
	Set_PlatformID( scaler, 3 );
	Set_PlatformSpecificID( scaler, 1 );
	You can insert the code right after the NewT2K constructor.
-------------------------
Q16) Can you explain the second parameter called code to T2K_RenderGlyph?
A16) Yes, this normally specifies the character code for the character you wish to render.
	However if you wish to use the glyph index instead then set the T2K_CODE_IS_GINDEX
	bit in the 6th input parameter to T2K_RenderGlyph called cmd. The glyph index is
	simply a number from 0 to N-1, assuming the font contains N glyphs.
	(N = T2K_GetNumGlyphsInFont( scaler );)
-------------------------
Q17) Does the outline winding direction matter in T2K?
A17) Yes Postscript outlines should use the correct winding direction and
	TrueType and T2K outlines also need to use the correct winding direction
	which is actually the opposite of the Postscript direction. It matters because
	the run-time-hinting process use this information to figure out where the
	black and white areas are. For TrueType and T2K the direction should be such
	that if you follow a contour in the direction of increasing point numbers
	then the black(inside) area should be on your right.
-------------------------
Q18) I need my fonts to be as small as possible. What should I do?
A18) You need to contact Type Solutions to have them translated to the T2K format or to apply
	font compression.
-------------------------
Q19) Can you explain ALGORITHMIC_STYLES in config.h?
A19) Yes it enables algorithmic styling.
	The 6th parameter to FF_New_sfntClass(); T2K_AlgStyleDescriptor *styling
	is normally set to NULL, but if ALGORITHMIC_STYLES is enabled you can set
	it equal to an algoritmic style descriptor. Here is an example using the
	algorithmic bolding provided by T2K.
		style.StyleFunc			=	tsi_SHAPET_BOLD_GLYPH;
		style.StyleMetricsFunc	=	tsi_SHAPET_BOLD_METRICS;
		style.params[0]			=	5L << 14;
		sfnt0 = FF_New_sfntClass( mem, fontType, 0, in, NULL, &style, &errCode );
	You can also write your own outline based style modifications and use them instead
	of the algorithmic bolding provided by T2K. Just model them after the Type Solutions
	code for algoritmic bolding in "SHAPET.c".
-------------------------
Q20) What is the story with USE_NON_ZERO_WINDING_RULE in config.h?
A20) The recommended setting is to leave it on.  This determines what
	kind of fill rule the T2K scan-converter will use. This enables
	a non-zero winding rule, otherwise the scan-converter will use an even-odd
	filling rule. For example the even-odd filling rule will turn an area
	where two strokes overlap (rare) into white, but the non zero winding
	rule will keep such areas black. For an embedded system where the fonts
	are well build and you do not have overlapping strokes you will get a
	small (proably less than 1%) speed-up by disabling this.
-------------------------
Q21) In the internal part of the options, there is an option called SAMPO_TESTING_T2K (!)
	which should be disabled. The only thing it does is to enable ENABLE_WRITE and ENABLE_PRINTF.
	But those two options are enabled unconditionally at the top of "dont touch" part. What is going on?
A21) :-) You should leave it off, since it is in the "dont touch" part.
	When T2K is built as a font engine T2K_SCALER is defined.(Not when built as a translator)
	ifdef T2K_SCALER
	actually does an  undef ENABLE_PRINTF and an undef ENABLE_WRITE
	Since the T2K font engine never does disk writes and does not use printf statements.
	However, when the code is undergoing testing at Type Solutions the
	T2K font engine may write to disk for logging purposes and use printf statements.
-------------------------
Q22) Are the functions used in the T2K_DOCUMENTATION_CODING_EXAMPLE part of t2k.h the only public APIs?
	Are there any other functions that might be useful to know?
A22) Yes, but the idea is that you should only use functions/methods visible in T2K.H.
	For instance T2K_MeasureTextInX() may be useful for quickly determining lengths of text string.
	If you find a need to use something else then let us know and if it makes sense
	we may bring out a public way to do it.
	Do not rely on any function/methods outside of T2K since they may change from release to release.
-------------------------
Q23) I found that when a string contains a space, T2K_RenderGlyph returns NULL baseAddr. Why is that?
	Do I have to check the existence of space characters and advance x position accordingly?
A23) There is no bitmap to draw! Makes sense :-).
	Dont check for space, etc. just check for baseAddr == NULL instead.
	In the future with T2KE check for ( baseARGB == NULL && baseAddr == NULL )
-------------------------
Q24) Are there functions for measuring widths and other metrics of strings
	(such as X11s XTextWidth, and XTextExtent)?
A24) I think the closest to XTextWidth is T2K_MeasureTextInX in T2K.H
	(It measures the linear un-hinted width, it can not measure the hinted width without actually
	rendering the characters).
	There is no equivalent to X11s XTExtExtent, since this sort of function typically would need
	to be implemented on top of the font-bit-map cache. T2K does not cache the output data,
	so T2K clients typically implement a cache on top of T2K so that the second time a character is
	requested it can come directly from the cache without invoking T2K. This sort of cache makes things
	go fast. String wide functions should be implemented so that they request information from the
	cache, to avoid T2K having to recompute everything several times.
	T2K also has two early experimental functions called T2K_GetIdealLineWidth(), T2K_LayoutString().
	They can help you to layout an entire line so that the total width is the ideal linear width, while
	still using run-time hinted individual characters and metrics. At least is attempts to do this
	by mostly putting the nonlinearities into the space characters between the words.
-------------------------
Q25) Can I edit T2K_BLACK_VALUE, and T2K_WHITE_VALUE so that I get a different range for the grey-scale?
A25) No, you should not edit anything in T2K.H. They are there so that you can put in an assert in your
	code so that you can automatically detect if they are ever changed by Type Solutions in the future.
-------------------------
Q26) What does T2K_TV_MODE do?
A26) It improves the results for situations where you do *not* use T2K_GRID_FIT (T2K hinting) and you do
	use gray-scale such as the TV-screen and you do use integer metrics.
	It compensates for the integralization of the advance width by adjusting the white sapce around the character
	*and* additionally it also ensures that we get left right symmetry in the gray-scale for simple symmetrical characters.
	If you use T2K_TV_MODE then turn off T2K_GRID_FIT.
	You should use T2K_TV_MODE when the following three conditions are true
	(1) You do not wish to use T2K_GRID_FIT (T2K hinting).
	(2) You are using gray-scale.
	(3) You are using integer metrics and not fractional positioning with fractional metrics. (Only one version of each character per size)
-------------------------
Q27) How do I get the type face name?
A27) You basically call T2K_SetNameString() (see below),
	at some point after you have called Set_PlatformID(), and Set_PlatformSpecificID().
	It sets the public fields nameString8 or nameString16 in the T2K object(structure).
	To use Microsoft Unicode mapping and names you can use:
	Set_PlatformID( scaler, 3 );
	Set_PlatformSpecificID( scaler, 1 );	/* 3,1 Picks Microsoft Unicode character mapping. */
	T2K_SetNameString( scaler, 0x0409, 4 );	/* Picks American English & the full font name */
-------------------------
Q28) How do I get native TrueType hint support in T2K?
A28) A: You need 2 additional .c and 2 .h files. (fnt.c/.h and t2ktt.c/.h)
	 B: You also need to #define ENABLE_NATIVE_TT_HINTS in config.h.
	 C: Then turn on T2K_NAT_GRID_FIT (T2K-native-grid-fitting) in the cmd parameter to T2K_RenderGlyph();
-------------------------
Q29) How do I slant the the text (make algorithmic italics)?
A29) Set the transformation matrix this may:
		trans.t00 = ONE16Dot16 * size;
		trans.t01 = ONE16Dot16 * sin( italic_angle) * size;
		trans.t10 = 0;
		trans.t11 = ONE16Dot16 * size;

	before calling T2K_NewTransformation().
	Size is a number such as 16.
	italic_angle is a number such as 12.0 degrees. In this case ONE16Dot16 * sin( 12.0 ) would be 13626.
----------------------
Q30) I need the actual outline spline data. How do I get it?
A30) Turn on the T2K_RETURN_OUTLINES to the cmd parameter to T2K_RenderGlyph().
	This will set the public field glyph in T2K.
	/*** Begin outline data */
	GlyphClass *glyph;
	/*** End outline data */
	GlyphClass has public fields with the outline data.

	Here are the relevant fields in GlyphClass:
	short	curveType;		/* 2 for TrueType (2nd degree B-spline) outlines and 3 for Type 1 (3rd Degree Bezier) */
	short	contourCount;	/* number of contours in the character */
	short	pointCount;		/* number of points in the characters + 0 for the sidebearing points */
	int16	*sp;			/* sp[contourCount] Start points */
	int16	*ep;			/* ep[contourCount] End points */
	int16	*oox;			/* oox[pointCount] Unscaled Unhinted Points, add two extra points for lsb, and rsb */
	int16	*ooy;			/* ooy[pointCount] Unscaled Unhinted Points, set y to zero for the two extra points */
							/* Do NOT include the two extra points in sp[], ep[], contourCount */
							/* Do NOT include the two extra points in pointCount */
	uint8 *onCurve;			/* onCurve[pointCount] indicates if a point is on or off the curve, it should be true or false */

	F26Dot6 *x, *y;			/* The actual points in device coordinates. */

	The character is made out of 'contourCount' contours.
	The outline coordinates are stored in F26Dot6 format in the x and y arrays. (6 fractional bits)
	Each contour starts with the point number sp[contour], and ends with with point number ep[contour].
	sp[0] should typically be zero. The letter A typically has 2 contours, B has 3, C has 1 etc.
	The contours are self closing.
	Each point is either an "on" or "off" curve point.
	A third degree Bezier is  on, off, off, on.
	A 2nd degree parabola is on, off, on.
	So a particular point n is described by x[n], y[n], onCurve[n].
	Please note that 2nd degree B-spline allow many consequtive off curve points.
-------------------------
Q31) I do not suppose you have any sample code which actually goes
	through the process of getting and evaluating the outline data?
A31) To see how T2K breaks down the outlines into parabolas (or 3rd degree beziers) and straight lines you can look at:
	Make2ndDegreeEdgeList() for parabols and
	Make3rdDegreeEdgeList() for 3rd degree beziers inside T2KSC.c.

	Once you have a parabola (described by three points A,B,C) it is described in parametric form by
	(1-t)*(1-t)*A + 2 *t *(1-t)*B + t*t*C
	Once you have a 3rd degree Bezier (described by 4 points A,B,C,D) it is described in parametric form by
	(1-t)*(1-t)*(1-t)*A + 3*(1-t)*(1-t)*t*B + 3*(1-t)*t*t * C+ t*t*t * D

	In both cases t starts being equal to zero at point A and then it goes to one by the last point.
-------------------------
Q32) Can you explain the glyph specific metrics in more detail ?
A32) Here is a lower case letter "g" showing the meanings of glyph specific metrics.

        t2k->fTop26Dot6 (26.6) This is the vertical line below, from base line to the top of the bitmap.
         <----> t2k->fLeft26Dot6 (26.6)
           ^     ***********    ^ t2k->heigth (integer number of scanlines) (32.0)
           |   *             *  |
           |   *             *  |
           |   *             *  |
           |   *             *  |
           |   *             *  |
---------O v----************----|---O------------------
         ^                   *  |   ^
pen pos- |                   *  |   |- next pen position.
                             *  |
               *             *  |
                 ***********    v

               <------------->   t2k->width (integer number of pixels) (32.0)
          <------------------------->   t2k->xAdvanceWidth16Dot16 (16.16)

	So for horzontal text put the left top corner of the bitmap at
	[((x + 0x8000)>> 16) + (scaler->fLeft26Dot6 >> 6), ((y + 0x8000)>> 16) - (scaler->fTop26Dot6 >>6)]

	then advance the pen:
	 x += scaler->xAdvanceWidth16Dot16;
	 y += scaler->yAdvanceWidth16Dot16;

	and for vertical text put the left top corner of the bitmap at
	[((x + 0x8000)>> 16) + (scaler->vert_fLeft26Dot6 >> 6), ((y + 0x8000)>> 16) - (scaler->vert_fTop26Dot6 >>6)]
	then advance the pen:
	 x += scaler->vert_xAdvanceWidth16Dot16;
	 y += scaler->vert_yAdvanceWidth16Dot16;
-------------------------
Q33) How do I use my own memory allocator and deallocator with T2K?
A33) CONFIG.H allows you to remap allocation, reallocation and deletion to anything you want. See the 3 first defines.
-------------------------
Q34) What is the persistence of some of the different T2K data structures needs to be?
	In particular: Does the input stream need to be allocated for as long as the font is
	active and allocated?  I would like to be able to do this within the initialization stage:

	memHandler_ = tsi_NewMemHandler( &err );
	inStream = New_InputStream3( memHandler_, data, length, &err );
	font_ = New_sfntClass( memHandler_, fontType, inStream, NULL, &err );
	...
	scaler_ = NewT2K( font_->mem, font_, &err );
	...
	Delete_InputStream( inStream, &err );

	That is, I want to delete the input stream and continue to use the font.
	Is this feasible, or does the font continue to refer to the input
	stream even after the sfntClass and the T2K structures have been built?
A34) The various object have to be deleted in the reverse order of creation.
	This means that the InputStream object can only be deleted *after* you
	have deleted the T2K and sfntClass abject.
-------------------------
Q35) >- Does the transformation need to exist as an external (application-
	managed) structure after calling T2K_NewTransformation?  If not, I would
	like to be able to do this within the font initialization stage:
		trans_ = new T2K_TRANS_MATRIX;
		trans_->t00 = ONE16Dot16 * pointSize;
		trans_->t01 = 0;
		trans_->t10 = 0;
		trans_->t11 = ONE16Dot16 * pointSize;
		T2K_NewTransformation( scaler_, true, 72, 72, trans_, true, &err );
		delete trans_; ?
A35) The T2K_TRANS_MATRIX structure can be deleted right after T2K_NewTransformation().
-------------------------
Q36) Our application will typically have between three and a dozen
	fonts open and active at the same time. Am I correct to assume this is not
	going to cause any problems within T2K?
A36) This is OK. You should have one tsiMemObject per font.
	You can choose to keep multiple fonts open simultansously and you can also decide to have one or multiple T2K scalers simultaneously,
	or you could decide to only allow one font open at a time.
	You can also decide to either use memory based fonts when you create the InputStream class or you can choose to use disk based fonts.
	These choices are a tradeoff between memory use and speed.
-------------------------
Q37) I turn on the T2K_RETURN_OUTLINES bit flag to T2K_RenderGlyph and I am using the t2k->glyph structure.
	Unfortunately my code can only handle 3rd degree Bezieers. What can I do when t2k->glyph->curveType == 2?
A37) First we encourage you to see if your current code can handle the 2nd degree curves directly
	since they can be rendered quicker than 3rd degree curves.
	If not, then this is how you go between them:
	(1) First we need to find all straight lines and parabolas:
		The function Make2ndDegreeEdgeList() function from T2KSC.c shows how that is done:
	(2) Now each Parabola (== 2nd degree Bezieer) is described by the points A,B,C.
		Each 3rd degree Bezieer is described by points P1,P2,P3,P4.

		To map points [A,B,C] to [P1,P2,P3,P4] do this:
			P1 = A;
			P2 = (2B + A)/3;
			P3 = (2B + C)/3;
			P4 = C;
-------------------------
Q38) What should I do if T2K returns an error?
A38) Once you get an error from T2K it frees up ALL memory.
	This means that you need to set all references to T2K to NULL and not call any T2K delete routines etc.
	Basically you have to start from the beginning again as if T2K never existed when you get an error.
-------------------------
Q39) Now, if an error is encountered, is it just that particuliar
	T2K that must be "restarted", or all the T2K objects?
A39) Not all T2K objects just all objects that shared the same tsiMemObject have to be restarted.
	You should have one tsiMemObject per font.
-------------------------
Q40) How do I make a colored bordered character?
A40) Just invoke invoked T2K_CreateBorderedCharacter (in T2KEXTRA.c) right after T2K_RenderGlyph().
	After this you can find the 32 bit colored bordred character in t2kscaler->baseARGB. The format is ARGB, 8 bits each.
-------------------------
Q41) How do I drive LCD displays?
A41) There are two categories of LCD modes that you can use. Bitstream recommends you use the new one to get the best result.

	(I) For the old LCD mode:
		Here are step by step instructions:

		A: Enable the ENABLE_LCD_OPTION in config.h.
		B: Use FF_NewColorTable to get the RGB colors for LCD display. These colors
			will be indexed by any bitmap produced by T2K. If your platform is using a Color
			Lookup Table, you will need to set these colors in that table.
			This is how you extract the actual RGB colors from the T2K color table:

			ff_ColorTableType *pColorTable;

			/* for black text on white Set Rb = Gb = Bb = 0xff, and Rf = Gf = Bf = 0. */
			pColorTable = FF_NewColorTable( mem, Rb, Gb, Bb, Rf, Gf, Bf );

			/* For all the indeces in the bitmap you get the color by doing this. */
			/* pColorTable->N will contain # elements in the array */
			/* pColorTable->ARGB[0] contains the first ARGB value */
			ARGB = pColorTable->ARGB[ byte index from the bitmap ];
			B = (ARGB & 0xff); ARGB >>= 8;
			G = (ARGB & 0xff); ARGB >>= 8;
			R = (ARGB & 0xff);

			/* When done free up the color-table, but please do not call this per-character for speed reasons. */
			FF_DeleteColorTable( mem, pColorTable);

		C: Do not invoke either FF_SetBitRange255() or FF_SetRemapTable(). If you need to shift
			the range, we recommend using a filter function.
		D: When you invoke T2K_NewTransformation() set the xRes to 3 times the yRes, since
			if you look close at the screen there are 3 times as many colored pixels in
			the x direction as there are in the y direction. This tells T2K we have a non-square
			aspect ratio where the x resolution is 3 times higher than the y resolution.
		E: Then set T2K_LCD_MODE_4 in the cmd parameter and GREY_SCALE_BITMAP_HIGH_QUALITY
			in the greyScalelevel paramter to the function T2K_RenderGlyph().
		F: You now have an indexed color bitmap. When you draw the bitmap you need to take into
			account that the bitmap contains indices for the colored pixels.

	(II) For the new LCD mode:
		Here are step by step instructions:

		A: Enable the ENABLE_EXTENDED_LCD_OPTION in config.h
		B: Use FF_NewColorTable to get the RGB colors for LCD display. These colors
			will be indexed by any bitmap produced by T2K. If your platform is using a Color
			Lookup Table, you will need to set these colors in that table.
			This is how you extract the actual RGB colors from the T2K color table:

			ff_ColorTableType *pColorTable;

			/* for black text on white Set Rb = Gb = Bb = 0xff, and Rf = Gf = Bf = 0. */
			pColorTable = FF_NewColorTable( mem, Rb, Gb, Bb, Rf, Gf, Bf );

			/* For all the indeces in the bitmap you get the color by doing this. */
			/* pColorTable->N will contain # elements in the array */
			/* pColorTable->ARGB[0] contains the first ARGB value */
			ARGB = pColorTable->ARGB[ byte index from the bitmap ];
			B = (ARGB & 0xff); ARGB >>= 8;
			G = (ARGB & 0xff); ARGB >>= 8;
			R = (ARGB & 0xff);

			/* When done free up the color-table, but please do not call this per-character for speed reasons. */
			FF_DeleteColorTable( mem, pColorTable);

		C: Do not invoke either FF_SetBitRange255() or FF_SetRemapTable(). If you need to shift
			the range, we recommend using a filter function.
		D: There are four LCD modes in this new LCD category. They are horizontal left-to-right RGB,
			horizontal left-to-right BGR ,vertical top-to-down RGB and vertical Top-to-down BGR.
			So turn on the approriate bitflag in cmd. For example, if you need horizontal left-to-right RGB mode,
			set T2K_EXT_LCD_H_RGB in the cmd parameter. Set GREY_SCALE_BITMAP_HIGH_QUALITY in the greyScalelevel
			paramter to the function T2K_RenderGlyph().
		E: You now have an indexed color bitmap. When you draw the bitmap you need to take into
			account that the bitmap contains indices for the colored pixels.
		F: Unlike the old LCD mode, you do NOT have to set the xRes to 3 times in the T2K_NewTransformation().
-------------------------
Q42) What is the difference between T2K_TV_MODE_2 and T2K_TV_MODE, and also between T2K_LCD_MODE and T2K_LCD_MODE_2?
A42) The _2 modifier activates a special light-weight y hint strategy which improves the quality. It for instance makes the
	antialiased bitmap pattern on top and bottom of an 'o' symmetrical.
	It is recommended for both TV and LCD output for the best quality.
	The regular LCD and TV modes already also make such characters left-right symmetrical for optimal quality.
	For best quality, T2K_LCD_MODE_4 is recommended because it employs native hints.
-------------------------
Q43) What is a tsiMemObject object, what does it do?
A43) It is an object that handles all memory allocation, deallocation and reallocation.
	The reason we have it done by one object instead of direct calls to the OS is that
	the tsiMemObject object does a lot of error checking. This creates a more stable product.
	For instance it puts special markers both before and after allocated memory so that we
	can detect any attemps to write outside the allocated memory. It also detecs any memory
	leaks and attempts to free no-pointers or or already freed memory and other memory errors.
	Basically the tsiMemObject provides a solid foundations for the product.
-------------------------
Q44) Why do we need one tsiMemObject per font?
A44) We could have shared this. But it seems we get a slight performance advantage using only one per font.
	The current implementation of tsiMemObject also has a maximum limit on the number of pointers it can allocate.
-------------------------
Q45) What is a InputStream object, what does it do?
A45) The InputStream object provides a level of abstraction for the core. Basically
	the InputStream object exposes certain methods that T2K uses to access the data.
	This means that T2K does not need to know if the data is in memory, on the disk, or a across a network, etc.
	This provides a cleaner design. The InputStream object also checks for out-of bounds read attempts.
	This error checking together with the nice abstraction InputStream provides produces a more solid and robust design
	and therefore a better product.
-------------------------
Q46) What does a sfntClass do?
A46) The sfntClass is an internal class that represents a font. It is shared by all supported font formats.
-------------------------
Q47) What is a T2K class, what does it do?
A47) The T2K object represents an instance of the font scaler. Main task for the fonts scaler is to produce
	good looking bitmap images for characters at differnt sizes and tranformations like rotation.
-------------------------
Q48) T2K_NewTransformation transform which item to what?
A48) T2K_NewTransformation is a method that informs the T2K object about the current transformation and size is.
-------------------------
Q49) What does T2K_RenderGlyph() do?
A49) It produces the bitmap image that we want.
-------------------------
Q50) I am using one of the Font Fusion stroke fonts and the output is too light! Can you make a heavier/bolder font?
A50) The good news is that that a Font Fusion stroke font has variable weight!!!
	This is one of the benefits of our stroke fonts, this means that a single
	font can have many many different looks :-)

	You are probably just using the default weight which is pretty light.
	The default is at 0.5 in 16.16 space.
	The weight is variable between 0.0 and 1.0 in 16.16 space.

	For instance try this:
	if ( T2K_GetNumAxes( scaler ) == 1 ) {
		T2K_SetCoordinate( scaler, 0, 0x10000*7/10 ); /* instead of default 0x10000/2 */
	}
	You can do this setting right after T2K_NewTransformation();

	You can tune the number to whatever looks best in your circumstance.
-------------------------
Q51) I am still confused about anti-aliasing and how to blend letters with a random background image.
A51) Instead of setting greyScaleLevel to the function T2K_RenderGlyph to
	BLACK_AND_WHITE_BITMAP  set it to GREY_SCALE_BITMAP_MEDIUM_QUALITY
	and FontFusion will return a gray-scale bitmap. This is the same as an alpha mask.

	Think of an alpha value and a bitmap filled with alpha values (an alpha mask)
	conceptually as a partially transparent glass window. Also think of the
	alpha value as conceptually going between 0.0 (fully transparent) to
	1.0 (fully opaque).

	When the alpha value is 0.0 you see everything behind the window (the background),
		but not the foreground.
	When the alpha value is 1.0 you only see the foreground color (or image).
	When the alpha value is 0.5 you see a blend consisting of 50% the background and 50% the foreground.
	To perfectly blend the foreground and background you need to pixel by
		pixel blend the background pixel values and foreground pixel values
		according to this linear formula

	newPixelColor = alpha*foregoundPixelColor + (1.0-alpha) * backgroundPixelColor

	When FontFusion operates in its normal grayscale mode then a value of
	T2K_BLACK_VALUE (126) in the alphamask returned by FontFusion corresponds
	to alpha == 1.0, and 0 corresponds to alpha == 0.
	Q&A6 also contains pseudo code that illustrates this.
-------------------------
Q52) What next?
A52) Go try the code. Good Luck! :-)
-------------------------

#endif /* T2K_DOCUMENTATION */


#ifdef T2K_DOCUMENTATION_CODING_EXAMPLE
	/* First configure T2K, please see "CONFIG.H" !!! */

	/* This shows a pseudo code example for how to use the T2K scaler. */
	tsiMemObject *mem = NULL;
	InputStream *in = NULL;
	sfntClass *font = NULL;
	T2K *scaler = NULL;
	int errCode;
	T2K_TRANS_MATRIX trans;
	T2K_AlgStyleDescriptor style;

	/* Create a Memhandler object. Use ONE per font. */
	mem	= tsi_NewMemhandler( &errCode );
	CLIENT_ASSERT( errCode == 0 );
		/* Point data1 at the font data */
		If ( TYPE 1 ) {
			if ( PC Type 1 ) {
				/* Only call for .pfb files and NOT for .pfa files. */
				data1 = ExtractPureT1FromPCType1( data1, &size1, &errCode );
				/* data1 is not allocated just munged by this call ! */
			} else if ( Mac Type 1 ) {
				short refNum = OpenResFile( pascalName ); /* Open the resource with some Mac call */
				data1 = (unsigned char *)ExtractPureT1FromMacPOSTResources( mem, refNum, &size1 );
				CloseResFile( refNum ); /* Close the resource file with some Mac call */
				/* data1 IS allocated by the T2kMemory layer! */
			}
		}
		/* Please make sure you use the right New_InputStream call depending on who allocated data1,
		  and depending on if the font is in ROM/RAM or on the disk/server etc. */
		/* Create an InputStream object for the font data */
		in = New_InputStream( mem, data1, size1, &errCode ); /* if data allocated by the T2kMemory layer */
		CLIENT_ASSERT( errCode == 0 );
		**** OR ****
		in = New_InputStream3( mem, data1, size1, &errCode ); /* otherwise do this if you allocated the data  */
		**** OR *****
		/* Allows you to leave the font on the disk, or remote server for instance (!) */
		in = New_NonRamInputStream( mem, fpID, ReadFileDataFunc, length, &errCode  );

		CLIENT_ASSERT( errCode == 0 );
			/* Create an sfntClass object. (No algorithmic styling) */
			short fontType = FONT_TYPE_TT_OR_T2K; /* Or, set equal to FONT_TYPE_1 for type 1, FONT_TYPE_2 for CFF fonts */
			font = New_sfntClass( mem, fontType, in, NULL, &errCode );
			**** OR ****
			/* alternatively do this for formats that support multiple logical fonts within one file */
			font = FF_New_sfntClass( mem, fontType, logicalFontNumber, in, NULL, NULL, &errCode );

			/* Or if you wish to use algorithmic styling do this instead
			 * T2K_AlgStyleDescriptor style;
			 *
			 * style.StyleFunc 			= 	tsi_SHAPET_BOLD_GLYPH;
			 * style.StyleMetricsFunc	=	tsi_SHAPET_BOLD_METRICS;
			 * style.params[0] = 5L << 14; (* 1.25 *)
			 * font = New_sfntClass( mem, fontType, in, &style, &errCode );
			 */
			CLIENT_ASSERT( errCode == 0 );
				/* Create a T2K font scaler object.  */
				scaler = NewT2K( font->mem, font, &errCode );
				CLIENT_ASSERT( errCode == 0 );
					/* 12 point */
					trans.t00 = ONE16Dot16 * 12;
					trans.t01 = 0;
					trans.t10 = 0;
					trans.t11 = ONE16Dot16 * 12;
					/* Set the transformation */
					T2K_NewTransformation( scaler, true, 72, 72, &trans, true, &errCode );
					CLIENT_ASSERT( errCode == 0 );
					loop {
						/* Create a character */
						T2K_RenderGlyph( scaler, charCode, 0, 0,
											BLACK_AND_WHITE_BITMAP,
											T2K_NAT_GRID_FIT | T2K_SCAN_CONVERT,
											&errCode );
						CLIENT_ASSERT( errCode == 0 );
						/* Now draw the char */
						/* Free up memory */
						T2K_PurgeMemory( scaler, 1, &errCode );
						CLIENT_ASSERT( errCode == 0 );
					}
				/* Destroy the T2K font scaler object. */
				DeleteT2K( scaler, &errCode );
				CLIENT_ASSERT( errCode == 0 );
			/* Destroy the sfntClass object. */
			FF_Delete_sfntClass( font, &errCode );
			CLIENT_ASSERT( errCode == 0 );
		/* Destroy the InputStream object. */
		Delete_InputStream( in, &errCode  );
		CLIENT_ASSERT( errCode == 0 );
	/* Destroy the Memhandler object. */
	tsi_DeleteMemhandler( mem );

#endif /* T2K_DOCUMENTATION_CODING_EXAMPLE */


/************************************************************/
/************************************************************/
/************************************************************/
/************************************************************/
/************************************************************/
/************************************************************/
/***** HERE THE ACTUAL NON-DOCUMENTATION CONTENTS BEGIN *****/
/************************************************************/
/************************************************************/
/************************************************************/
/************************************************************/
/************************************************************/

/*A private T2K internal use only class used for adaptive dropoutcontrol */
typedef struct
{
	tsiMemObject	*mem;
	int32			xPPEm, yPPEm;
	int32			length;
	uint8			*noNeedForXDropout; /* x BitArray */
	uint8			*noNeedForYDropout; /* y BitArray */
} dropoutAdaptationClass;


typedef struct
{
	F16Dot16		t00, t01;
	F16Dot16		t10, t11;
} T2K_TRANS_MATRIX;

/* Only for use use by an external bitmap cache. */
#define FF_Set_T2K_Core_CacheReference( t2k, reference ) (t2k->theCache = (reference))
#define FF_Set_T2K_Core_CacheMemFuncReference( t2k, funcptr ) (t2k->GetCacheMemory = (funcptr))

/* For use by an external fontmanager. */
typedef void *(*FF_FM_RenderGlyphPtr)( void *theFM, fontCode_t fontCode, void **ppScaler, int32 code, int8 xFracPenDelta, int8 yFracPenDelta, uint8 greyScaleLevel, uint16 cmd, int *errCode );
#define FF_Set_T2K_Core_FMReference( t2k, reference ) (t2k->theFM = (reference))
#define FF_Set_T2K_Core_FMRenderGlyphReference( t2k, funcptr ) (t2k->FMRenderGlyph = (funcptr))

#define FF_T2K_FM_Exists() (t2k->FMRenderGlyph != NULL)
#define FF_T2K_FM_RenderGlyph( theFM, fontCode, scaler, code, xFracPenDelta, yFracPenDelta, greyScaleLevel, cmd, errCode ) \
		(t2k->FMRenderGlyph( ((FF_FM_Class *)theFM), (fontCode), (T2K)scaler, (code), (xFracPenDelta), (yFracPenDelta), (greyScaleLevel), (cmd), (errCode) ))

/* Only for use use by an external bitmap cache. */
typedef void *(*FF_T2K_FilterFuncPtr)( void *t2k, void *filterParamsPtr);

/* If set, the RenderGlyph method in T2K will call this before returning the bitmap. */
#define FF_Set_T2K_Core_FilterReference( t2k, funcptr, params ) (t2k->BitmapFilter = (funcptr), t2k->filterParamsPtr = (params) )

/* public getter functions */
#define T2K_FontHasKerningData( t ) ((t)->font != NULL && (t)->font->kern != NULL)
#define T2K_GetNumGlyphsInFont( t ) GetNumGlyphs_sfntClass( (t)->font )


#ifdef DRIVE_8BIT_LCD
typedef struct
{
	uint16	 N;
	uint32	ARGB[122];
} ff_ColorTableType;

/* external direct use of this function is deprecated. */
ff_ColorTableType *FF_GetColorTable( void );

/*
 * The ff_ColorTableType constructor
 * The foreground, and background color values need to be in the range 0-255
 */
ff_ColorTableType *FF_NewColorTable( tsiMemObject *mem, uint16 Rb, uint16 Gb, uint16 Bb, uint16 Rf, uint16 Gf, uint16 Bf );

/*
 * The ff_ColorTableType destructor
 */
void FF_DeleteColorTable( tsiMemObject *mem, ff_ColorTableType *t );

/**
 * Method to change the mapping of color table
 */
void FF_ModifyColorTable(ff_ColorTableType *t, uint16 Rb, uint16 Gb, uint16 Bb, uint16 Rf, uint16 Gf, uint16 Bf);

#endif /* DRIVE_8BIT_LCD */

/*
 * This is the structure/class for the T2K scaler.
 */
typedef struct tag_T2K
{
	/* private */
	int32			stamp1;
	tsiMemObject	*mem;

	F16Dot16		t00, t01;
	F16Dot16		t10, t11;

	dropoutAdaptationClass	*tAdapt;

	int				is_Identity;
	void			*theCache;					/* Private reference to the cache, for the memory callback. */

	FF_GetCacheMemoryPtr	GetCacheMemory;		/* Private reference to the the memory callback function from the cache. */

#ifdef ENABLE_COMMON_DEFGLYPH
	FF_SearchDefGlyph  searchDefGlyf;			/*For searching the default list from the core when the gid = 0*/
	void *defGlyfFoundInCache;
#endif/*ENABLE_COMMON_DEFGLYPH*/

	int	okForBitCreationToTalkToCache;			/* Private field for cache usage for bitmaps */
	int	okForFilterToTalkToCache;				/* Private field, set to false for LCD mode since there is one additional filtering step */
	int	internal_baseAddr, internal_baseARGB;	/* Private fields to indicate who allocated the memory. */
	void			*theFM;						/* Private reference to the fm (not used by T2K), use getter and setter functions above */

	FF_FM_RenderGlyphPtr	FMRenderGlyph;		/* Private reference to the fm RenderGlyph function (not used by T2K), use getter and setter functions above */
	FF_T2K_FilterFuncPtr	BitmapFilter;		/* Private reference to bitmap filter function, use setter function avove to set */

	void			*filterParamsPtr;			/* Private reference to bitmap filter 2nd parameter, use setter function avove to set */
	int				 bitRange255;				/* Private boolean variable for remapping the bitmap range */
	uint8			*remapBits;					/* Private table lookup reference for bitmap remapping */

	/* public */
	uint8			*nameString8;				/* Set by T2K_SetNameString */
	uint16			*nameString16;				/* Set by T2K_SetNameString */

	int32			numberOfLogicalFonts;		/* Number of logical fonts inside, normally == 1. */
	uint32			isFixedPitch;				/* 0 = proportional, non 0 = monospace */
	uint32			firstCharCode;				/* lowest code point, character code in font */
	uint32			lastCharCode;				/* highest code point, character code in font */

	/*** Begin font wide HORIZONTAL Metrics data */
	int				horizontalFontMetricsAreValid;
	F16Dot16		xAscender,	yAscender;
	F16Dot16		xDescender,	yDescender;
	F16Dot16		xLineGap,	yLineGap;
	F16Dot16		xMaxLinearAdvanceWidth, yMaxLinearAdvanceWidth;
	F16Dot16		caretDx, caretDy; /* [0,K] for vertical */

	F16Dot16		xUnderlinePosition, yUnderlinePosition;	/* 0 if unknown */
	F16Dot16		xUnderlineThickness, yUnderlineThickness;			/* 0 if unknown */
	/*** End font wide HORIZONTAL Metrics data */

	/*** Begin font wide VERTICAL Metrics data */
	int				verticalFontMetricsAreValid;
	F16Dot16		vert_xAscender, vert_yAscender;
	F16Dot16		vert_xDescender, vert_yDescender;
	F16Dot16		vert_xLineGap, vert_yLineGap;
	F16Dot16		vert_xMaxLinearAdvanceWidth, vert_yMaxLinearAdvanceWidth;
	F16Dot16		vert_caretDx, vert_caretDy; /* [0,K] for vertical */
	/*** End font wide VERTICAL Metrics data */

	/*** Begin glyph specific HORIZONTAL Metrics data */
	int				horizontalMetricsAreValid;
	F16Dot16		xAdvanceWidth16Dot16, yAdvanceWidth16Dot16;
	F16Dot16		xLinearAdvanceWidth16Dot16, yLinearAdvanceWidth16Dot16;
	F26Dot6			fTop26Dot6, fLeft26Dot6;			/* For positioning the top left corner of the bitmap. */
	/*** End glyph specific HORIZONTAL Metrics data */

	/*** Begin glyph specific VERTICAL Metrics data */
	int				verticalMetricsAreValid;
	F16Dot16		vert_xAdvanceWidth16Dot16, vert_yAdvanceWidth16Dot16;
	F16Dot16		vert_xLinearAdvanceWidth16Dot16, vert_yLinearAdvanceWidth16Dot16;
	F26Dot6			vert_fTop26Dot6, vert_fLeft26Dot6;	/* For positioning the top left corner of the bitmap. */
	/*** End glyph specific VERTICAL Metrics data */

	/*** Begin outline data */
	GlyphClass		*glyph;
	uint32			glyphIndex;
	/*** End outline data */

	/*** Begin bitmap data */
	int32			width, height;
	int32			rowBytes;
	uint8			*baseAddr; /* unsigned char baseAddr[N], 	N = t->rowBytes * t->height */
	uint32			*baseARGB;
	int				embeddedBitmapWasUsed; /* This is a public field set by T2K_RenderGlyph() */
	uint8			bitDepth;
	/*** End bitmap data */

	/* private */
	int32			xPixelsPerEm, yPixelsPerEm;
	F16Dot16		xPixelsPerEm16Dot16, yPixelsPerEm16Dot16;
#ifdef ENABLE_EXTRA_PRECISION
	float			xMul, yMul;
#else
	F16Dot16		xMul, yMul;
#endif /* ENABLE_EXTRA_PRECISION */
	T2KScaleInfo	xScale, yScale;
	F26Dot6			oneHalfFUnit;
	int32			ag_xPixelsPerEm, ag_yPixelsPerEm;
	int8			xWeightIsOne;
	int				fontCategory;
	int				enableSbits;	/* This is a private field set by T2K_NewTranformation */
	uint16			upem;			/* Unit per Em */

	sfntClass		*font;
	/* Hide the true data Types from our client */
	void			*hintHandle; /* ag_HintHandleType hintHandle */
	/* void *globalHintsCache; Moved into sfntClass */

	/*** Begin BtX specific members ***/
	int				expandXOutlinesBy3;		/* Triple outline in X direction */
	int				expandYOutlinesBy3;		/* Triple outline in Y direction */
	int				force_same_bm_size;		/* Force bitmap size */
	/*** End BtX specific members ***/

#ifdef DRIVE_8BIT_LCD
#define colorIndexTableSize 2197
	uint8			colorIndexTable[colorIndexTableSize];
#endif	/* DRIVE_8BIT_LCD */

#ifdef LAYOUT_CACHE_SIZE
	uint32			tag[LAYOUT_CACHE_SIZE];
	int16			kernAndAdvanceWidth[ LAYOUT_CACHE_SIZE ];

#ifdef ENABLE_KERNING
	int16			kern[ LAYOUT_CACHE_SIZE ];
#endif /* ENABLE_KERNING */

#endif /* LAYOUT_CACHE_SIZE */

#ifdef ENABLE_FRACTIONAL_SIZE
	uint16 bFracSize;
#endif /* ENABLE_FRACTIONAL_SIZE */
	
#ifdef ENABLE_SMARTSCALE
	int				bSmartScaleEnable;
	FF_CmDeleteCurrentChar deleteCurrentChar; 
#endif

#ifdef ALGORITHMIC_STYLES
#ifdef ENABLE_POSTHINT_ALGORITHMIC_STYLES
	int				isFlippingTx;
#ifdef ENABLE_BASELINE_SHIFT
	int				bBaselineShift;
#endif
#endif
#endif

	int32			stamp2;

} T2K;

#define UN_SOPPORTED_HACK
#ifdef  UN_SOPPORTED_HACK
#define IS_BOLD( t2kscaler ) ( t2kscaler && t2kscaler->font != NULL && t2kscaler->font->head != NULL && (t2kscaler->font->head->macStyle & 1) != 0 )
#endif

#ifdef T2K_SCALER
/*
 * The T2K scaler constructor.
 * For all T2K functions *errCode will be set to zero if no error was encountered
 * If you are not using any algorithmic styling then set styling = NULL
 */
T2K *NewT2K( tsiMemObject *mem, sfntClass *font, int *errCode );

#ifdef ENABLE_T2K_CLONING
T2K *NewT2KClone( const T2K * const, int *errCode );
#endif

/* Two optional functions to set prefered platform and/or prefered platform specific ID */
/* Invoke right after NewT2K(), t is of type (T2K *) */
#define Set_PlatformID( t2k, ID ) 			((t2k)->font->preferedPlatformID = (ID))
#define Set_PlatformSpecificID( t2k, ID ) 	((t2k)->font->preferedPlatformSpecificID = (ID))

/*
 * Please note that the using the gray scale native range [0..126] is the fastest.
 * By doing FF_SetBitRange255( t2k, true); you can change the range to [0..255].
 * FF_SetBitRange255( t2k, false ); would set the range back to the default [0.126]
 * which is the fastest.
 * This function is optional and can be called any time before T2K_RenderGlyph.
 */
#define FF_SetBitRange255( t2k, booleanvalue )	((t2k)->bitRange255 = (booleanvalue))

/*
 * Please note that the using the gray scale native range [0..126] is the fastest.
 * This function allows you remap that range to what you want instead.
 * Basically T2K just does newBitValue = lookupTable[oldBitValue];
 * Please note that this also allows you to gamma correct the output.
 * If you wish to just linearly scale the range to [0..255], then please
 * use the slightly faster above FF_SetBitRange255( t2k, true);
 * This function is optional and can be called any time before T2K_RenderGlyph.
 * The lookup table you provide must have entries in the range [0..126] inclusive.
 * the lookupTable is of type (unsigned char *)
 */
#define FF_SetRemapTable( t2k, lookupTable )	((t2k)->remapBits = (lookupTable))


#ifdef ENABLE_SBIT

#ifdef ENABLE_BDF
#define T2K_CHECK_FOR_BDF(__font)   || ((__font)->bdf != NULL)
#else
#define T2K_CHECK_FOR_BDF(__font) 
#endif /* ENABLE_BDF */


#ifdef ENABLE_WINFNT
#define T2K_CHECK_FOR_WINFNT(__font)  || (__font)->winFnt != NULL
#else
#define T2K_CHECK_FOR_WINFNT(__font)
#endif /* ENABLE_WINFNT */

#define T2K_FontSbitsExists( t2k ) ((t2k)->font->bloc != NULL T2K_CHECK_FOR_WINFNT(t2k->font) T2K_CHECK_FOR_BDF(t2k->font))


/* Query method for checking if the sbits are enabled */
#define T2K_FontSbitsAreEnabled( t2k )	((t2k)->enableSbits != 0 )

/*
 * Query method to see if a particaluar glyph exists in sbit format for the current size.
 * If you need to use characterCode then map it to glyphIndex by using T2K_GetGlyphIndex() first.
 */
int T2K_GlyphSbitsExists( T2K *t, uint16 glyphIndex, int *errCode  );

/* Method for setting an embedded bitmap depth to be returned if available. */
void T2K_SetEBBitDepth( T2K *t, uint8 bitDepth );

#endif /* ENABLE_SBIT */

/*
 * Set the transformation and x and y resolution.
 *
 * x & y point size is passed embedded in the Transformation as trans = pointSize * old-Transformation
 *
 *
 * t is a pointer to the T2K object.
 * doSetUpNow: 	  Determines if some setup work should be done now or later. Recommended setting is == true
 * xRes and yRes: This is the resolution of the output device in dots per inch. A Windows PC uses 96 for this for example.
 * trans:         is a pointer to the transformation matrix.
 * enableSbits:   enables emedded bitmaps if they exist.
 * errCode:       is a pointer to the returned errorCode.
 *
 */
void T2K_NewTransformation(T2K *t, int doSetUpNow, int32 xRes, int32 yRes, T2K_TRANS_MATRIX *trans,
						   int enableSbits, int *errCode );


/* New experimental stuff for T2KE format */
int32 T2K_GetNumAxes(T2K *t);
F16Dot16 T2K_GetAxisGranularity(T2K *t, int32 n);
F16Dot16 T2K_GetCoordinate(T2K *t, int32 n );
void T2K_SetCoordinate(T2K *t, int32 n, F16Dot16 value );
/* End experimental stuff */

/*
 * Modifies the greyScaleLevel and cmdIn paramers for T2K_RenderGlyph
 * according to the wishes of the gasp table if it exists and also dependend on
 * if ENABLE_GASP_TABLE_SUPPORT is defined. You can use it like this:
 * T2K_GaspifyTheCmds( scaler, &greyScaleLevel, &cmd );
 * T2K_RenderGlyph( scaler, charCode, 0, 0, greyScaleLevel, cmd, &errCode );
 */
void T2K_GaspifyTheCmds( T2K *t, uint8 *greyScaleLevelPtr, uint16 *cmdInPtr );

#ifdef ENABLE_FRACTIONAL_SIZE
/*
 * Sets the fractional size mode of scaler. T2K_NewTranformation should be called after setting this property.
 */
#define T2K_SetFracSizeMode( t2k, bSet) ((t2k)->bFracSize = (uint16)(bSet))

/*
 * Returns the Fractional Size state of the scaler.
 */
#define T2K_GetFracSizeMode( t2k ) (t2k)->bFracSize
#endif /* ENABLE_FRACTIONAL_SIZE */

/*
 * Sets the Fractional Size property.
 */
/*
 * Sets the bSmartScaleEnable flag in t2k scaler to enable Smart-scaling of characters
 */
#ifdef ENABLE_SMARTSCALE
#define T2K_SetSmartScale( t2k, bSet ) (t2k->bSmartScaleEnable = bSet)
#endif

/*
 * Sets baseline shift flag in t2k scaler;  
 */
#ifdef ENABLE_BASELINE_SHIFT
#define T2K_SetBaselineShift( t2k, bSet ) (t2k->bBaselineShift = bSet)
#endif

/* Bits for the cmd field below */
#define T2K_GRID_FIT		0x0001
#define T2K_SCAN_CONVERT	0x0002
#define T2K_RETURN_OUTLINES	0x0004
#define T2K_CODE_IS_GINDEX	0x0008 /* Otherwise it is the charactercode */
#define T2K_USE_FRAC_PEN	0x0010
#define T2K_SKIP_SCAN_BM	0x0020 /* Everything works as normal, however we do _not_ generate the actual bitmap */
#define T2K_TV_MODE			0x0040 /* Ideal for TV if you use integer metrics, and gray-scale (please turn off T2K_GRID_FIT) */
#define T2K_NAT_GRID_FIT	0x0080 /* Enables native TrueType hint/gridding support */
#define T2K_LCD_MODE		0x0100 /* Ideal for LCD screens */
#define T2K_Y_ALIGN			0x0200 /* Ideal with T2K_LCD_MODE, and T2K_TV_MODE */
#define T2K_VERTICAL		0x0400 /* Enables vertical printing */
#define T2K_VERT_SUB		0x0800 /* Enables vertical substitution */

#define T2K_TV_MODE_2	( T2K_TV_MODE  | T2K_Y_ALIGN )

#define T2K_LCD_MODE_2	( T2K_LCD_MODE | T2K_Y_ALIGN )
#define T2K_LCD_MODE_3	( T2K_LCD_MODE | T2K_GRID_FIT )
#define T2K_LCD_MODE_4	( T2K_LCD_MODE | T2K_NAT_GRID_FIT )

#define EXT_HOR_RGB  0x1000  /* This means R G B */
#define EXT_HOR_BGR  0x2000  /* This means B G R */
#define EXT_VER_RGB  0x4000
/* This means R
              G
              B */

#define EXT_VER_BGR  0x8000
/* This means B
              G
              R */

#define T2K_EXT_LCD_H_RGB ( T2K_LCD_MODE | T2K_NAT_GRID_FIT | EXT_HOR_RGB ) /* This means R G B */
#define T2K_EXT_LCD_H_BGR ( T2K_LCD_MODE | T2K_NAT_GRID_FIT | EXT_HOR_BGR ) /* This means B G R */
#define T2K_EXT_LCD_V_RGB ( T2K_LCD_MODE | T2K_NAT_GRID_FIT | EXT_VER_RGB )
/* This means R
              G
              B */

#define T2K_EXT_LCD_V_BGR ( T2K_LCD_MODE | T2K_NAT_GRID_FIT | EXT_VER_BGR )
/* This means B
              G
              R */


/* For the greyScaleLevel field below */
#define BLACK_AND_WHITE_BITMAP				0
#define GREY_SCALE_BITMAP_LOW_QUALITY		1
#define GREY_SCALE_BITMAP_MEDIUM_QUALITY	2
#define GREY_SCALE_BITMAP_HIGH_QUALITY		3 /* Recommended for grey-scale */
#define GREY_SCALE_BITMAP_HIGHER_QUALITY	4
#define GREY_SCALE_BITMAP_EXTREME_QUALITY	5

/* When doing grey-scale the scan-converter returns values in the range T2K_WHITE_VALUE -- T2K_BLACK_VALUE */
#define T2K_BLACK_VALUE 126
#define T2K_WHITE_VALUE 0

/* The Caller HAS to deallocate outlines && t->baseAddr with T2K_PurgeMemory( t, 1 ) */
/* fracPenDelta should be between 0 and 63, 0 represents the normal pixel alignment,
   16 represents a quarter pixel offset to the right,
   32 represents a half pixel offset of the character to the right,
   and -16 represents a quarter/4 pixel shift to the left. */
/* For Normal integer character positioning set fracPenDelta == 0 */
/* IPenPos = Trunc( fracPenPos );  FracPenDelta = fPenPos - IPenPos */
/* The bitmap data is relative to  IPenPos, NOT fracPenPos */
/*
 * The T2K call to render a character.
 *
 * t:             is a pointer to the T2K object itself.
 * code: 	      If the bit T2K_CODE_IS_GINDEX is set in 'cmd' it is the glyphIndex, otherwise it is the characterCode for the character we are rendering.
 * xFracPenDelta, yFracPenDelta: Normally set to zero. Can be used with non-zero values if fractional character positioning is used.
 * cmd:           Describes to T2K what is to be done with various bitflags. See commetns that define the bitflags in T2K.H.
 * errCode:       is a pointer to the returned errorCode.
 *
 */
void T2K_RenderGlyph(T2K *t, uint32 code, int8 xFracPenDelta, int8 yFracPenDelta,
					 uint8 greyScaleLevel, uint16 cmd, int *errCode );


#define MAX_PURGE_LEVEL 2
/*
 * Call after you are done with the output data from T2K_RenderGlyph().
 * Normally set level = 1.
 */
void T2K_PurgeMemory( T2K *t, int level, int *errCode );

#ifdef ENABLE_FF_CURVE_CONVERSION
/*
 * Call right after T2K_RenderGlyph used with the T2K_RETURN_OUTLINES bit set,
 * and before you call T2K_PurgeMemory().
 * This method creates a t->glyph with outlines of type curveTypeOut
 * independent of what the original curve type is.
 *
 * Valid values for curveTypeOut out are:
 * 1 : This returns a glyph composed of just straight line segments (a polyline).
 * 2 : This returns a glyph composed of 2nd order B-splines (parabolas) (and straight lines).
 * 3 : This returns a glyph composed of 3rd order Beziers (qubics) (and straight lines).
 *
 * The resulting outlines are in glyph->x/y/onCurve/sp/ep/contourCount and not in oox/ooy.
 *
 */
void T2K_ConvertGlyphSplineType( T2K *t, int16 curveTypeOut, int *errCode );

#endif /* ENABLE_FF_CURVE_CONVERSION */

/*
 * Sets t->nameString8 or t->nameString16 depending on if the name is encoded
 * as a byte string or as a 16-bit Unicode string.
 * Call after Set_PlatformID(), and Set_PlatformSpecificID()
 *
 */
void T2K_SetNameString( T2K *t, uint16 languageID, uint16 nameID, int *errCode );


/*
 * The T2K destructor.
 */
void DeleteT2K( T2K *t, int *errCode );

#endif /* T2K_SCALER */

/* Transforms xInFUnits into 16Dot16 x and y values */
void T2K_TransformXFunits( T2K *t, int16 xValueInFUnits, F16Dot16 *x, F16Dot16 *y);

/* Transforms yInFUnits into 16Dot16 x and y values */
void T2K_TransformYFunits( T2K *t, int16 yValueInFUnits, F16Dot16 *x, F16Dot16 *y);


#ifdef ENABLE_KERNING
typedef struct
{
	uint16	left;	/* left character code */
	uint16	right;	/* right character code */
	int16	xKern;	/* value in FUnits */
	int16	yKern;	/* value in FUnits */
} T2K_KernPair;

/*
 * Return value is a pointer to T2K_KernPair with *pairCountPtr entries.
 * The entries consist of all kern pairs between the the character with
 * the charCode character code combined with itself and all the members
 * of baseSet. (A character should only appear once in baseSet)
 * The caller *has* to deallocate the pointer, if != NULL, with
 * tsi_DeAllocMem( t->mem, pointer );
 */
T2K_KernPair *T2K_FindKernPairs(T2K *t, uint16 *baseSet, int baseLength, uint32 charCode,
								int *pairCountPtr );

#endif /* ENABLE_KERNING */

/*
 * Maps the characterCode to the glyph index.
 */
uint32 T2K_GetGlyphIndex( T2K *t, uint32 charCode, int *errCode );

#ifdef ENABLE_LINE_LAYOUT

#ifdef LINEAR_LAYOUT_EXAMPLE
	/* This is a pseudo-code example */
	totalWidth = T2K_MeasureTextInX( scaler, string16, kern, numChars);
	for ( i = 0;  (charCode = string16[i]) != 0; i++ ) {
		F16Dot16 xKern, yKern;

		/* Create a character */
		T2K_RenderGlyph( scaler, charCode, 0, 0,
						 BLACK_AND_WHITE_BITMAP,
						 T2K_NAT_GRID_FIT | T2K_SCAN_CONVERT,
						 &errCode );
		CLIENT_ASSERT( errCode == 0 );
		T2K_TransformXFunits( scaler, kern[i], &xKern, &yKern );

		bm->baseAddr		= (int8*)scaler->baseAddr;
		bm->rowBytes		= scaler->rowBytes;
		bm->bounds.left		= 0;
		bm->bounds.top		= 0;
		bm->bounds.right	= scaler->width;
		bm->bounds.bottom	= scaler->height;

		MyDrawChar( graf, x + ( (scaler->fLeft26Dot6+(xKern>>10))>>6), y - (scaler->fTop26Dot6+(yKern>>10)>>6), bm );
		/* We keep x as 32.16 */
		x16Dot16 += scaler->xLinearAdvanceWidth16Dot16 + xKern; x += x16Dot16>>16; x16Dot16 &= 0x0000ffff;
		/* Free up memory */
		T2K_PurgeMemory( scaler, 1, &errCode );
		CLIENT_ASSERT( errCode == 0 );
	}


#endif /* LINEAR_LAYOUT_EXAMPLE */

/* Returns the total pixel width fast, and computes the kern values */
uint32 T2K_MeasureTextInX(T2K *t, const uint16 *text, int16 *xKernValuesInFUnits, uint32 numChars );


#define T2K_X_INDEX		0
#define T2K_Y_INDEX		1
#define T2K_NUM_INDECES	2

typedef struct
{
	/* input */
	uint16		charCode;
	uint16		glyphIndex;
	F16Dot16	AdvanceWidth16Dot16[ T2K_NUM_INDECES ];
	F16Dot16	LinearAdvanceWidth16Dot16[ T2K_NUM_INDECES ];
	F26Dot6		Corner[ T2K_NUM_INDECES ];		/* fLeft26Dot6, fTop26Dot6 */
	int32		Dimension[ T2K_NUM_INDECES ];	/* width, height */
} T2KCharInfo;


typedef struct
{
	/* output */
	F16Dot16	BestAdvanceWidth16Dot16[ T2K_NUM_INDECES ];
} T2KLayout;


/*
 * Before calling create a T2KCharInfo for each character on the line and initialize
 * all the fields. You can use the above T2K_GetGlyphIndex() to get the glyphIndex.
 * Computes the ideal lineWidth. The computation takes kerning into account.
 * Initializes out
 */
void T2K_GetIdealLineWidth( T2K *t, const T2KCharInfo cArr[], int32 lineWidth[], T2KLayout out[] );

/*
 * You have to call T2K_GetIdealLineWidth() first to initalize out before calling this function.
 * Computes out so that the LineWidthGoal is satisfied while taking kerning into account.
 * Note: This is an early version of the function.
 */
void T2K_LayoutString( const T2KCharInfo cArr[], const int32 LineWidthGoal[], T2KLayout out[] );

#endif /* ENABLE_LINE_LAYOUT */

/*
 * If you have already rendered the glyph then this call is faster
 * than T2K_GetGlyphIndex() and should be used instead.
 * This avoids mapping the character code to glyphIndex twice.
 */
#define T2K_GetGlyphIndexFast( t2kScaler ) ( (t2kScaler)->glyphIndex )

/*
 * Returns the font type from an input stream
 */
int16 FF_FontTypeFromStream(InputStream *in, int *errCode);
int16 ff_FontTypeFromStream(InputStream *in);

/*
 * Enumerates the characters in the font resource
 */
void T2K_ListChars(void * userArg, T2K *scaler, int ListCharsFn(void * userArg, void *scaler, uint16 code), int *errCode);

/*
 * Converts PSName to CharCode (Type1 and Type2(CFF) fonts only!!)
 */
int FF_PSNameToCharCode(T2K *t, int8 *PSName, int *errCode);

/*
 * Returns a pointer to memory buffer containing any arbitrary TrueType table
 */
uint8 *FF_GetTTTablePointer(T2K *t, int32 tag, uint8 **ppTbl, size_t *bufSize, int *errCode );

/*
 * Forces the unloading of the current TrueType cmap and loads the cmap
 * currently selected by Set_PlatformID( scaler, ID ), and Set_PlatformSpecificID( scaler, ID )
 * This function presumes you have already used those setter macros. The values
 * set by those macros will be ignored if a character has forced the load of the
 * TrueType cmap, unless you call this function!
 */
void FF_ForceCMAPChange(T2K *t, int *errCode);

/*
 * returns true if the glyph exists, false otherwise
 */
int FF_GlyphExists( T2K *t, uint32 code, uint16 cmd, int *errCode );

/*
 * returns the number of bytes of the input character code that was used
 * to resolve to a glyph index.
 */
#define T2K_GetBytesConsumed(t) ( ((T2K*)(t))->font->cmap == NULL ? 2 : ((T2K*)(t))->font->cmap->bytesConsumed )

#ifdef ENABLE_T1_FORCE_ENCODING

/* 
 * Returns the current Type1 encoding type used to encode the T1 font.
 */
#define T2K_GetT1Encoding(t) tsi_GetT1Encoding(t->T1)

/* 
 * Forces the encoding on Type1 font. Returns 0 on Failure else 1.
 * Its recommended to force the custom encoded font to some other standard encoding because the names 
 * inside the custom fonts may not be the standard names. The method can be slow and is expected to be
 * called only once during the lifetime of the font.
 */
#define T2K_ForceT1Encoding(t, encType) tsi_ForceT1Encoding(t->T1, encType)
#endif /* ENABLE_T1_FORCE_ENCODING */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __T2K_T2K__ */


/*********************** R E V I S I O N   H I S T O R Y **********************
 *
 *     $Header: /home/archive/FontFusion/FontFusion/core/t2k.h,v 1.19 2009/07/10 09:39:00 rpasricha Exp $
 *                                                                           *
 *     $Log: t2k.h,v $
 *     Revision 1.19  2009/07/10 09:39:00  rpasricha
 *     Implementation to enable baseline shift dynamically
 *
 *     Revision 1.18  2009/06/24 08:45:53  rpasricha
 *     Macro Name changed
 *
 *     Revision 1.17  2009/06/23 12:54:52  rpasricha
 *     Float-Point calculation for advance width
 *
 *     Revision 1.16  2009/05/12 10:37:23  rpasricha
 *     Determination of Flipping Transformation
 *
 *     Revision 1.15  2009/04/09 15:12:37  sflynn
 *     Added "#define T2K_VERT_SUB  0x0800"
 *
 *     Revision 1.14  2009/02/05 20:07:09  sflynn
 *     Added RenderGlyph() option T2K_VERTICAL (0x0400) for vertical writing.
 *
 *     Revision 1.13  2008/11/05 12:41:42  ljoshi
 *     Adding support for ENABLE_FRACTIONAL_SIZE.
 *
 *     Revision 1.12  2008/03/11 16:19:54  sflynn
 *     Added T2K structure members to support the SmartScale feature.
 *
 *     Revision 1.11  2008/02/12 20:10:25  sflynn
 *     Updated for 32-bit character code support.
 *
 *     Revision 1.10  2008/01/11 05:46:22  ljoshi
 *     Adding support for forced Type1 encoding.
 *
 *     Revision 1.9  2007/11/13 14:40:19  ritesh
 *     Ritesh: Added the support for the windows fnt font format.
 *
 *     Revision 1.8  2007/11/06 13:19:58  himanshu
 *     Adding support for variable include file name.
 *
 *     Revision 1.7  2007/05/09 05:00:49  ljoshi
 *     Updation of examples with macros for library functions.
 *
 *     Revision 1.6  2006/06/02 18:14:20  sflynn
 *     Modified to support configurable 16\32 bit cache tag.
 *
 *     Revision 1.5  2006/04/28 17:49:29  sflynn
 *     no message
 *
 *     Revision 1.47  2005/10/06 19:29:25  Shawn_Flynn
 *     Routine T2K_FontSbitsExists() was changed to support BDF fonts.
 *
 *     Revision 1.46  2005/09/15 19:31:34  Shawn_Flynn
 *     Added support for common default glyph use.
 *
 *     Revision 1.45  2005/05/19 15:23:15  Shawn_Flynn
 *     Added BtX2 specific members to the T2K scaler structure.
 *
 *     Revision 1.44  2005/04/29 14:59:42  Shawn_Flynn
 *     Cleaned up corrected and added information (A41) for the new extended
 *     LCD modes.
 *
 *     Revision 1.43  2005/04/21 17:36:35  Shawn_Flynn
 *     Modified to support the new ENABLE_EXTENDED_LCD_OPTION mode.
 *
 *     Revision 1.42  2005/03/02 20:46:04  Shawn_Flynn
 *     Added name to T2K structure definition for forward referencing:
 *         typedef struct tag_T2K
 *
 *     Revision 1.41  2004/10/29 15:30:46  Shawn_Flynn
 *     Added T2K structure member 'bitDepth'.
 *     Changed T2K_SetEBBitDepth() from a macro to a function prototype.
 *
 *     Revision 1.40  2004/09/29 16:55:54  Shawn_Flynn
 *     Added prototype for FF_SetEBBitDepth() for multi-bit-per-pixel bitmaps.
 *
 *     Revision 1.39  2004/04/26 19:14:44  Shawn_Flynn
 *     Added prototype for new FF_ModifyColorTable() routine.
 *
 *     Revision 1.38  2004/04/06 19:27:57  Shawn_Flynn
 *     Added conditional prototype statement for NewT2KClone() function.
 *
 *     Revision 1.37  2003/03/14 15:40:21  Shawn_Flynn
 *     Cleaned up compiler warnings.
 *
 *     Revision 1.36  2003/01/07 20:24:07  Shawn_Flynn
 *     dtypED.
 *
 *     Revision 1.35  2001/05/07 20:28:04  shawn
 *     Added macro 'T2K_GetBytesConsumed()' for mixed one and two
 *         byte encodings.
 *     Revision 1.34  2001/05/03 16:05:25  reggers
 *     Removed unused parameter from ff_FontTypeFromStream.
 *     Revision 1.33  2001/05/02 21:25:16  reggers
 *     Map new functions to FF_ prefix rather than T2K_ prefix.
 *     Revision 1.32  2001/05/01 18:30:21  reggers
 *     Added T2K_GlyphExists()
 *     Revision 1.31  2001/04/27 20:33:32  reggers
 *     Added new API function T2K_ForceCMAPChange()
 *     Revision 1.30  2001/04/27 19:35:45  reggers
 *     Added new API function GetTTTablePointer for loading any TrueType
 *     Table into RAM memory.
 *     Revision 1.29  2001/04/26 20:45:20  reggers
 *     Cleanup relative to PSName conversion. Added errCode parameter,
 *     Revision 1.28  2001/04/24 21:57:10  reggers
 *     Added GASP table support (Sampo).
 *     Revision 1.27  2001/04/19 17:37:55  reggers
 *     Expose API for converting PSName to ccode.
 *     Revision 1.26  2000/12/18 18:42:18  reggers
 *     Added new Q&A for alpha blending pixel by pixel.
 *     Revision 1.25  2000/10/26 17:01:15  reggers
 *     Changes for SBIT: use cache based on setting of
 *     scaler->okForBitCreationToTalkToCache. Able to handle caching
 *     SBITs now.
 *     Revision 1.24  2000/10/18 20:58:21  reggers
 *     Protoype for internal ff_FontTypeFromStream()
 *     Revision 1.23  2000/10/18 17:41:49  reggers
 *     Added error handling to FF_FontTypeFromStream()
 *     Revision 1.22  2000/09/13 16:59:40  reggers
 *     Added FF_NewColorTable() and FF_DeleteColorTable() (Sampo)
 *     Revision 1.21  2000/07/13 14:35:10  reggers
 *     Updated comment: Q41, relative to LCD mode and usage.
 *     Revision 1.20  2000/06/14 21:30:52  reggers
 *     Update comment.
 *     Revision 1.19  2000/05/26 18:20:21  reggers
 *     Removed FILTER_THOUGHTS.
 *     Revision 1.18  2000/05/11 13:37:17  reggers
 *     Added support for outline curve conversion. (Sampo)
 *     Revision 1.17  2000/05/08 18:01:54  reggers
 *     Changes for setjmp error code handling.
 *     Revision 1.16  2000/04/13 18:14:26  reggers
 *     Updated list chars for user argument or context pass through.
 *     Revision 1.15  2000/04/06 16:23:38  reggers
 *     Added Q&A comments to help users setting stroke thickness
 *     of FFS fonts.
 *     Revision 1.14  2000/03/27 22:17:10  reggers
 *     Updates for new LCD mode and functionality
 *     Revision 1.13  2000/03/10 19:18:26  reggers
 *     Enhanced for enumeration of character codes in font.
 *     Revision 1.12  1999/11/04 20:20:32  reggers
 *     Added code for getting fixed/proportional setting, firstCharCode and
 *     lastCharCode.
 *     Revision 1.11  1999/10/29 15:06:57  jfatal
 *     T2K_GetGlyphIndex() is moved out of #ifdef ENABLE_LINE_LAYOUT
 *     Revision 1.10  1999/10/18 17:01:22  jfatal
 *     Changed all include file names to lower case.
 *     Revision 1.9  1999/09/30 15:10:39  jfatal
 *     Added correct Copyright notice.
 *     Revision 1.8  1999/09/27 21:42:19  reggers
 *     Fix for T2K_GetGlyphIndexFast macro.
 *     Revision 1.7  1999/09/20 16:40:51  reggers
 *     Removed single quote items in comment blocks that bothered both
 *     compilers (cc and gcc) on Linux.
 *     Revision 1.6  1999/08/27 20:08:35  reggers
 *     Latest changes from Sampo
 *     Revision 1.5  1999/07/19 16:15:32  sampo
 *     Added prototype of FF_FontTypeFromStream() (SNIFFER.c)
 *     Revision 1.4  1999/07/16 17:52:04  sampo
 *     Sampo work. Drop #8 July 16, 1999
 *     Revision 1.3  1999/05/18 18:09:02  sampo
 *     Changed scaler pointer param in FF_FM_RenderGlyphPtr type def
 *     to T2K ** type.
 *     Revision 1.2  1999/05/17 15:57:57  reggers
 *     Inital Revision
 *                                                                           *
******************************************************************************/
