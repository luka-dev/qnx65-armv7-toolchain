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

#ifndef _PH_GEOM_H
#define _PH_GEOM_H

struct Ph_point { short x, y; };
struct Ph_dim { unsigned short w, h; };
struct Ph_lpoint { long x, y; };
struct Ph_rgb { unsigned short r, g, b; };
/* struct Ph_prect { PhPoint_t ul, lr; };		 */
struct Ph_rect { struct Ph_point ul, lr; };
struct Ph_area { struct Ph_point pos;
                 struct Ph_dim size; };
struct Ph_extent { struct Ph_rect rect;
                   unsigned short valid; };

/*  Support for the old-style rectangle/area definitions */
struct Ph_rectold { short xUL, yUL, xLR, yLR; };
struct Ph_areaold { short x, y, w, h; };
struct Ph_extentold { short xUL, yUL, xLR, yLR, valid; };
             

/*  Graphics specific add-ons. */
struct Ph_span   { short x1, x2, y; };
struct Ph_2short { short a, b; };
struct Ph_transMat {
	struct Ph_lpoint		xm, ym;
	struct Ph_point			xlat;
	unsigned			flags;
};

/* Renderlib specific add-ons... */
struct Ph_areahw {
	short x;
	short y;
	short w;
	short h;
};

struct Ph_rgb_bytes { unsigned short r, g, b; };

/* Fixed point geometry for phfont */
struct Ph_point_16dot16 { int32_t x_16dot16, y_16dot16; };
struct Ph_rect_16dot16 { struct Ph_point_16dot16 ul, lr; };


#endif   /*  _PH_GEOM_H */


#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PhGeom.h $ $Rev: 224590 $" )
#endif
