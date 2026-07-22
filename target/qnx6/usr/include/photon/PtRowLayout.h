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
#ifndef	__PT_ROW_LAYOUT_H_INCLUDED
#define	__PT_ROW_LAYOUT_H_INCLUDED

/* PtRowLayoutInfo_t flags */
#define	Pt_ROW_WRAP			0x0001
#define	Pt_ROW_PACK			0x0002
#define	Pt_ROW_JUSTIFY		0x0004

/* PtRowLayoutData_t flags */
#define	Pt_ROW_WRAP_BEFORE	0x0001
#define	Pt_ROW_WRAP_AFTER	0x0002
#define	Pt_ROW_FILL			0x0004

typedef struct pt_row_layout_info {
	short		type;				/* Pt_LAYOUT_{HORIZONTAL|VERTICAL} */
	short		flags;
	PhRect_t	margin;
	short		h_spacing;
	short		v_spacing;
} PtRowLayoutInfo_t;

typedef struct pt_row_layout_data {
	PhDim_t		hint;
	short		flags;
} PtRowLayoutData_t;

extern const PtLayoutDefinition_t *PtRowLayout;
extern const PtRowLayoutInfo_t PtRowLayoutInfoDflts;
extern const PtRowLayoutData_t PtRowLayoutDataDflts;

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtRowLayout.h $ $Rev: 224590 $" )
#endif
