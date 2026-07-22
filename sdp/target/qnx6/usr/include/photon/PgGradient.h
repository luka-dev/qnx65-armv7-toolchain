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

#ifndef __PH_GLIB_PG_GRADIENT_H_INCLUDED
#define __PH_GLIB_PG_GRADIENT_H_INCLUDED


/*---------------------------------------
 * Gradient image construction parameters
 *---------------------------------------*/

#define Pg_GRAD_BYTES_PER_PIXEL	3
#define Pg_GRAD_IMAGE_TYPE		Pg_IMAGE_DIRECT_888


/*---------------
 * Gradient types
 *---------------*/

#define Pg_GRAD_BOXY			0x80000000
#define Pg_GRAD_NOGRADIENT		0	/* Unset/remove gradient */
#define Pg_GRAD_VECTOR			1	/* General vector gradient */
#define Pg_GRAD_RADIAL			2	/* Radial gradient */
#define Pg_GRAD_HORIZONTAL		3	/* Gradient vector points East to West or West to East */
#define Pg_GRAD_VERTICAL		4	/* Gradient vector points North to South or South to North */
#define Pg_GRAD_FAST_VECTOR		5	/* General vector gradient. Use the fast version of PgGetColor() */
									/* do not check if (x,y) is within the gradient band. */

#define Pg_GRAD_DIAGF			6
#define Pg_GRAD_DIAGB			7
#define Pg_GRAD_4POINT			8
#define Pg_GRAD_BOX_DIAGF		Pg_GRAD_DIAGF |Pg_GRAD_BOXY
#define Pg_GRAD_BOX_DIAGB		Pg_GRAD_DIAGB |Pg_GRAD_BOXY
#define Pg_GRAD_BOX_4POINT		Pg_GRAD_4POINT|Pg_GRAD_BOXY

/*-----------------------
 * Color-transition types
 *-----------------------*/

#define Pg_GRAD_TABLE		  100	/* Use the transition-table provided by the user */
#define Pg_GRAD_LINEAR		    0	/* Linear  */
#define Pg_GRAD_HILL			1	/* Normal curve */
#define Pg_GRAD_HILL2			2	/* Think of a camel */
#define Pg_GRAD_EXP				3	/* Exponential */


/*--------------------------------------------------------------------------------------------------------
 * PgGradientControl_t describes a gradient in a more convenient way. It can be computed from PgGradient_t
 *--------------------------------------------------------------------------------------------------------*/


typedef struct _Pg_gradientcontrol {

	int gradient_type;		/* Pg_GRAD_NOGRADIENT, Pg_GRAD_VECTOR, Pg_GRAD_RADIAL etc. */

	PhPoint_t start_point;	/* The start-point of the gradient vector / the center for radial gradients */
            				/* the start-point is recomputed if a rotation is specified. */

  	int ncolors;			/* number of isochrome points = length of the gradient vector in pixels */
  	PgColor_t *colors;		/* The isochrome colors: colors[0]=start_color .... colors[ncolors-1]=end_color */
							/* This is the "gradient palette". */
	       
	int *lookup;			/* Lookup table. Contains indecies into the colors[] array. */
	int lookup_size;		/* Number of entries in the lookup table */
	int xlookup;			/* 1- the lookup table is indexed by X distance (from the normal line at the start point) */
							/* 0- the lookup table is indexed by Y distance */

	int top_color_index;	/* Index of the color above the gradient band (0 or ncolors-1) */
	int bottom_color_index;	/* Index of the color below the gradient band (0 or ncolors-1) */

    double slope;			/* Slope of the normal line */
    double intercept;		/* Intercept of the normal line at the start point */
    double intercept1;		/* Intercept of the normal line at the end point */

	double *intabove;		/* Intercept of the top line in the gradient band (&intercept or &intercept1) */
	double *intbelow;		/* Intercept of the bottom line in the gradient band (&intercept or &intercept1) */

	double vslope;			/* Slope of the gradient vector itself == -1/slope */
	double vintercept;		/* Intercept of the gradient vector */

} PgGradientControl_t;


/*-----------------------------------------------
 * PgGradientPixel_t is used to construct images.
 *-----------------------------------------------*/

typedef union _Pg_gradientpixel {
  PgColor_t pixel;
  struct {
		char r;
		char g;
		char b;
		char junk;
  } color;
} PgGradientPixel_t;


/*-----------
 * Debug flag
 *-----------*/

/*#define GRD_DEBUG 1 */


/*----------------------------------------------------------------------------------------------
 *										Gradient related functions
 *----------------------------------------------------------------------------------------------*/


#if 0

/* This function will need to set corresponding parameters in the current graphics context.*/

void *PgSetGradient(					int gradient_type,		int transition_type, int rotation,
										PhPoint_t *start_point,	PhPoint_t *end_point,
										PgColor_t start_color,	PgColor_t end_color,
										int table_size,			char *transition_table );

#endif


PgGradientControl_t *PgCreateGradient(	int gradient_type,		int transition_type, int rotation,
										PhPoint_t *start_point,	PhPoint_t *end_point,
										PgColor_t start_color,	PgColor_t end_color,
										int table_size,			char *transition_table );


PhImage_t *PgGradientMakeImage(PgGradientControl_t *gradient, PhPoint_t *ul, PhPoint_t *lr, PhImage_t *input_image, void *(*myalloc) (size_t));

void PgGradientRotatePalette(PgGradientControl_t *gradient);

PgColor_t PgGradientGetColor(PgGradientControl_t *gradient, int x, int y);

void PgGradientLinear(PgColor_t *colors, int ncolors, PgColor_t start_color, PgColor_t end_color);

PgColor_t PgGradientPercent(PgColor_t color1, PgColor_t color2, int percent);

void PgGradientGetAngles(PhPoint_t *start, PhPoint_t *end, int *min_angle, int *max_angle, int *magic_angle);

extern void PgCalcColorContrast(PgColor_t flat_color, int contrast, PgColor_t *light, PgColor_t *dark);



#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PgGradient.h $ $Rev: 224590 $" )
#endif
