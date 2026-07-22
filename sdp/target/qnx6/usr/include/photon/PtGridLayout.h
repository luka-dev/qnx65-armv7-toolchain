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
#ifndef	__PT_GRID_LAYOUT_H_INCLUDED
#define	__PT_GRID_LAYOUT_H_INCLUDED

/* layout flags */
#define	Pt_EQUAL_COLS	0x0001
#define	Pt_EQUAL_ROWS	0x0002

typedef struct pt_grid_layout_info {
	unsigned 	n_cols;
	unsigned	flags;
	PhRect_t	margin;		
	short		h_spacing;
	short		v_spacing;
} PtGridLayoutInfo_t;

/* data flags */
enum PtGridLayoutDataFlags {
	Pt_H_GRAB 				= 0x0001,
	Pt_V_GRAB 				= 0x0002,
	Pt_GRAB_BOTH 			= Pt_H_GRAB | Pt_V_GRAB,
	
	Pt_H_ALIGN_BEGINNING	= 0x0000, 
	Pt_H_ALIGN_CENTER		= 0x1000, 
	Pt_H_ALIGN_END			= 0x2000, 
	Pt_H_ALIGN_FILL			= 0x3000,
	__Pt_H_ALIGN_MASK		= 0x3000,
	
	Pt_V_ALIGN_BEGINNING 	= 0x0000, 
	Pt_V_ALIGN_CENTER		= 0x0100, 
	Pt_V_ALIGN_END			= 0x0200, 
	Pt_V_ALIGN_FILL			= 0x0300,
	__Pt_V_ALIGN_MASK		= 0x0300,
	
	Pt_ALIGN_BEGINNING_BOTH	= Pt_H_ALIGN_BEGINNING | Pt_V_ALIGN_BEGINNING,
	Pt_ALIGN_CENTER_BOTH	= Pt_H_ALIGN_CENTER | Pt_V_ALIGN_CENTER,
	Pt_ALIGN_END_BOTH		= Pt_H_ALIGN_END | Pt_V_ALIGN_END,
	Pt_ALIGN_FILL_BOTH		= Pt_V_ALIGN_FILL | Pt_H_ALIGN_FILL,
};

#define	Pt_H_ALIGNMENT( f ) ( f & __Pt_H_ALIGN_MASK )
#define	Pt_V_ALIGNMENT( f )	( f & __Pt_V_ALIGN_MASK )
#define Pt_SET_H_ALIGNMENT( f, m ) ( f & (~__Pt_H_ALIGN_MASK) | (m & __Pt_H_ALIGN_MASK) )
#define Pt_SET_V_ALIGNMENT( f, m ) ( f & (~__Pt_V_ALIGN_MASK) | (m & __Pt_V_ALIGN_MASK) )

typedef struct pt_grid_layout_data {
	short		flags;
	short		h_span, v_span;
	PhDim_t		hint;
	short		h_weight, v_weight;
	PhRect_t	margin;
} PtGridLayoutData_t;

extern const PtLayoutDefinition_t *PtGridLayout;
extern const PtGridLayoutInfo_t PtGridLayoutInfoDflts;
extern const PtGridLayoutData_t PtGridLayoutDataDflts;

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtGridLayout.h $ $Rev: 224590 $" )
#endif
