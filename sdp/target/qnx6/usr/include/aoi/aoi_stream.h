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



#ifndef __AOSTREAM_H__
#define __AOSTREAM_H__

#include <aoi/aoi_core.h>
#include <aoi/aoi_dataformat.h>

__BEGIN_DECLS

struct AOStreamer;
typedef struct AOStreamer AOStreamer;

enum
{
  AO_STREAMER_EOF           = 0,    /* end of file       */
  AO_STREAMER_ERROR         = -1,   /* error             */
  AO_STREAMER_RETRY         = -2,   /* transient error, please retry */
  AO_STREAMER_COT           = -3,   /* change of track with discontinuity  */
  AO_STREAMER_EOT           = -4,   /* end of track without discontinuity  */
};

struct AOIStream
{
	const char *filespec;
	const AOStreamer *streamer;
	const AOICtrl_t *ctrl;
	void *ctx;
};

#define AOSTREAMER_VERSION 100
/*
 * The AddOn Streamer interface 
 *
 * All functions, except Open(), return -1 on error.
 */
struct AOStreamer
{
	/* Open the filename given, with the mode given, and return a context pointer. */
	AOIStream_t *(*Open)(const char *name,const char *mode);

	/* Close the stream and free any data we allocated. */
	int32_t (*Close)(AOIStream_t *sobj);

	/* Read num bytes if we're at the beginning of the stream, returning how */
	/* many bytes we could read.  Return -1 if we were no longer at the start */
	/* of the stream. */
	int64_t (*Sniff)(void *ctx,void *buf,int64_t num);

	/* Read num bytes from the stream. Return -1 on error. */
	int64_t (*Read)(void *ctx,void *buf,int64_t num);

	/* Write num bytes to the stream. Return -1 on error. */
	int64_t (*Write)(void *ctx,const void *buf,int64_t num);

	/* Seek to the given position in the stream.  Return -1 if we can't seek, */
	/* otherwise returns new position. */
	int64_t (*Seek)(void *ctx,int64_t offset,int32_t whence);

	/* Return the current position in the stream. */
	int64_t (*Tell)(void *ctx);

	/* Return the length of the stream, -1 if not known. */
	int64_t (*Length)(void *ctx);

	/* If there's any additional information about the stream,  */
	/* info is filled in,  ilen is set, and 0 is returned. (Otherwise -1 is */
	/* returned.) */
	int32_t (*SideInfo)(void *ctx,char **sinfo,int32_t *slen);
};

#define AOSTREAMER_FD_OPEN_VERSION 100

/*
 * The AOStreamerFdOpen interface is used to allow an alternate streamer
 * to take over an input stream (is used for playback of DRM content)
 */
typedef struct {
	/* return EOK if successfully took over stream (if not, no harm is done) */
	AOIStream_t *(*FdOpen)(const char *name, const char *mode, int fd);
} AOStreamerFdOpen;

#define AOSTREAMER_CLONE_VERSION 100

/*
 * The AOStreamerClone interface allows the creation of a "clone" stream
 * that refers to the same file or object, but allows independent access
 */
typedef struct {
	AOIStream_t *(*Clone)(AOIStream_t *stream);
} AOStreamerClone;

__END_DECLS

#endif


#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/aoi/public/aoi/aoi_stream.h $ $Rev: 279929 $" )
#endif
