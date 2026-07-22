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



#ifndef __AOI_CORE_H__
#define __AOI_CORE_H__

#include <inttypes.h>
#include <sys/cdefs.h>

struct AOICtrl;
typedef struct AOICtrl AOICtrl_t;
struct AOIStream;
typedef struct AOIStream AOIStream_t;
struct AODataFormat;
typedef struct AODataFormat AODataFormat_t;
struct AOMetadataParser_t;
typedef struct AOMetadataParser_t AOMetadataParser;
struct AOMetadata;
typedef struct AOMetadata AOMetadata_t;

#include <aoi/aoi_interfaces.h>

__BEGIN_DECLS

typedef struct
{
	char *name;
	int32_t version;
	void *interface;
} AOInterface_t;

/* core functionality */
const AOICtrl_t *AoAdd(const char *dll);
const AOICtrl_t *AoAddStatic(AOInterface_t *interfaces);
int32_t AoAddDirectory(const char *path,const char *pattern);
int32_t AoRemove(const AOICtrl_t *ctrl);
int32_t AoHold(const AOICtrl_t *cctrl);
int32_t AoRelease(const AOICtrl_t *ctrl);
int32_t AoHoldAll(void);
int32_t AoReleaseAll(void);
AOInterface_t *AoGetAOInterface(const AOICtrl_t *ctrl, const int32_t nth);
void *AoGetInterface(const AOICtrl_t *ctrl,const char *ifname,const int32_t minver,const int32_t nth);
int32_t AoHasInterface(const AOICtrl_t *ctrl,const char *ifname,const int32_t minver,const int32_t nth);
const AOICtrl_t *AoIterate(const char *iname,const int32_t version,int32_t * const cookie);
const AOICtrl_t *AoIterateHoldGet(const char *iname,const int32_t version,int32_t *cookie,void **iface);
const AOICtrl_t *AoFindName(const char *name,const char *oiface,int32_t version);
int32_t AoAddUnloadSignal(int sig);

/* convenience functions */
const AOICtrl_t *AoFindMime(const char *mimetype,int32_t *rating,const char *oiface,int32_t version);
const AOICtrl_t *AoFindExt(const char *ext,int32_t *rating,const char *oiface,int32_t version);
const AOICtrl_t *AoFindStreams(AOIStream_t *stream,int32_t *rating,const char *oiface,int32_t version);
const AOICtrl_t *AoFindFormats(const AODataFormat_t *fmt,int32_t *rating,const char *oiface,int32_t version);
AOIStream_t *AoOpenFilespec(const char *fspec,const char *mode);
AOMetadataParser *AoFindMetadataParser(AOIStream_t *sobj,AOMetadata_t **metadata);

__END_DECLS

#endif


#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/aoi/public/aoi/aoi_core.h $ $Rev: 280224 $" )
#endif
