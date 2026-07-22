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
#ifndef __PD_DIRECT_H_INCLUDED
#define __PD_DIRECT_H_INCLUDED
#include <photon/PhT.h>
#include <photon/PhInternal.h>

#ifdef __cplusplus
extern "C" {
#endif
	typedef struct
pddirectcontext {
	PhDrawContext_t dc;
	pid_t	bypass_chid;
	PhDrawContext_t		*dflt_dc; /* The original dflt */
	} PdDirectContext_t;


typedef struct 
pdoffscreencontext {
	PhDrawContext_t		dc;	/* low level control... see PhDraw.c and PhInternal.h*/
	PgVidMemTag_t		id; /* Offscreen memory block tag.*/
	PhRid_t				target_rid;
	PhDim_t				dim;
	long unsigned		format;
	long unsigned		flags;
	void 				* volatile shared_ptr;
	unsigned long		shared_size;
	unsigned long 		pitch;
	PhConnectId_t		connect_id;
	} PdOffscreenContext_t;


typedef struct 
pdosccreatelockparams {
	uint32_t flags;
	int sig;
	uint32_t spare[5];
	} PdOSCCreateLockParams_t;

typedef struct 
pdosclockparams {
	uint32_t flags;
	struct timespec * time_out;
	uint32_t spare[6];
	} PdOSCLockParams_t;

/*
 *
 *  PROTOS
 *
 */
	extern PdOffscreenContext_t *
PdCreateOffscreenContext( 
	int unsigned const format, 
	int unsigned const width, 
	int unsigned const height,
	int unsigned const flags
	);

#ifdef _GF_GF_H_INCLUDED
extern PdOffscreenContext_t *PdCreateOffscreenContextGF( gf_surface_t surface );
#endif

	extern PdOffscreenContext_t * 
PdDupOffscreenContext( 
	PdOffscreenContext_t *o_osc , 
	unsigned long flags
	);

	extern void *
PdGetOffscreenContextPtr(
	PdOffscreenContext_t *osc
	);

	extern PdDirectContext_t * 
PdCreateDirectContext( 
	void 
	);

	extern PhDrawContext_t *
PdDirectStart( 
	void *dc 
	);

	extern PhDrawContext_t *
PdDirectStop( 
	PdDirectContext_t *dc
	);

	extern int 
PdReleaseDirectContext(
	PdDirectContext_t *dc
	);

	extern int 
PdIsOffscreenValid(
	PdOffscreenContext_t *osc
	);

	extern int 
PdCreateOffscreenLock(
	PdOffscreenContext_t *osc, 
	PdOSCCreateLockParams_t *params
	);

	extern int 
PdDestroyOffscreenLock(
	PdOffscreenContext_t *osc 
	);

	extern int 
PdReCreateOffscreenLock(
	PdOffscreenContext_t *osc, 
	PdOSCCreateLockParams_t *params
	);

	extern int 
PdLockOffscreen(
	PdOffscreenContext_t *osc, 
	PdOSCLockParams_t *params
	);

	extern int 
PdUnlockOffscreen(
	PdOffscreenContext_t *osc
	);

	extern int 
PdIsOffscreenLocked(
	PdOffscreenContext_t *osc
	);

#ifdef __cplusplus
	}
#endif

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PdDirect.h $ $Rev: 224590 $" )
#endif
