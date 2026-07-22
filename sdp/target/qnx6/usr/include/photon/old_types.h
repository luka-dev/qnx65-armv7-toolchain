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
typedef struct Ph_rect { short xUL, yUL, xLR, yLR; } PhRect_t;
typedef struct Ph_area { short x, y, w, h; } PhArea_t;
typedef struct Ph_extent { short xUL, yUL, xLR, yLR, valid; } PhExtent_t;

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/old_types.h $ $Rev: 224590 $" )
