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
#ifndef PX_ASSOCIATION_H_INCLUDED
#define PX_ASSOCIATION_H_INCLUDED

#ifndef __PH_GLIB_H_INCLUDED
#include <photon/Pg.h>
#endif

#ifndef __PT_T_H_INCLUDED
#include <photon/PtT.h>
#endif

typedef struct px_association PxAssociation_t;
typedef struct px_association_ctrl PxAssociationCtrl_t;

typedef enum
{
	PX_MIMETYPE_UNKNOWN = 0,
	PX_MIMETYPE_APPLICATION,
	PX_MIMETYPE_AUDIO,
	PX_MIMETYPE_IMAGE,
	PX_MIMETYPE_MESSAGE,
	PX_MIMETYPE_MODEL,
	PX_MIMETYPE_MULTIPART,
	PX_MIMETYPE_TEXT,
	PX_MIMETYPE_VIDEO
} PxMimeType_t;

extern PxAssociationCtrl_t *PxAssociationsUpdate(PxAssociationCtrl_t *ctrl);
extern PxAssociation_t *PxAssociationGetByFullMime(PxAssociationCtrl_t *ctrl,char const *mime);
extern PxAssociation_t *PxAssociationGetByFile(PxAssociationCtrl_t *ctrl,char const *filename);
extern void PxAssociationGetIcons(PxAssociation_t *association,PhImage_t **small_icon,PhImage_t **large_icon);

extern pid_t PxAssociationOpen(
	PxAssociation_t *association,
	char const *filename,
	const PtSpawnOptions_t *opt,
	PtSpawnCbF_t *cb,
	void *data,
	PtSpawnCbId_t **csp);

extern pid_t PxAssociationView(
	PxAssociation_t *association,
	char const *filename,
	const PtSpawnOptions_t *opt,
	PtSpawnCbF_t *cb,
	void *data,
	PtSpawnCbId_t **csp);

extern pid_t PxAssociationEdit(
	PxAssociation_t *association,
	char const *filename,
	const PtSpawnOptions_t *opt,
	PtSpawnCbF_t *cb,
	void *data,
	PtSpawnCbId_t **csp);

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/phexlib/public/photon/PxAssociation.h $ $Rev: 224591 $" )
#endif
