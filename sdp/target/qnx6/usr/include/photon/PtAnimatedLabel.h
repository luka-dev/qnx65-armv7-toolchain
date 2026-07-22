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
#ifndef __Pt_ANIMATED_LABEL_H_INCLUDED
#define __Pt_ANIMATED_LABEL_H_INCLUDED

#include <photon/PtLabel.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtAnimatedLabel Public
 */

extern PtWidgetClassRef_t	*PtAnimatedLabel;

#define Pt_ANIMATEDLABEL_ID		101

/* Resources */
#define Pt_ARG_FRAME_DATA		Pt_RESOURCE( 101, 0 )
#define Pt_ARG_NUM_FRAMES		Pt_RESOURCE( 101, 1 )
#define Pt_ARG_FRAME_INTERVAL	Pt_RESOURCE( 101, 2 )
#define Pt_ARG_CURRENT_FRAME	Pt_RESOURCE( 101, 3 )

/* 
 * PtAnimatedLabel Private
 */

/* Widget Structure */
typedef struct Pt_animated_label {
	PtLabelWidget_t         label;
	PhImage_t				*frame_data, *frame;
	int						num_frames;
	int						frame_interval;
	int						current_frame;
	int						repeat;
} PtAnimatedLabelWidget_t;

/* Widget Union */
typedef union Pt_animated_label_union {
	PtWidget_t              core;
	PtBasicWidget_t         basic;
	PtLabelWidget_t         label;
	PtAnimatedLabelWidget_t anim;
} PtAnimatedLabelUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif /* __Pt_ANIMATED_LABEL_H_INCLUDED */

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtAnimatedLabel.h $ $Rev: 224590 $" )
#endif
