/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable
 * license fees to QNX Software Systems before you may reproduce,
 * modify or distribute this software, or any work that includes
 * all or part of this software.   Free development licenses are
 * available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email
 * licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review
 * this entire file for other proprietary rights or license notices,
 * as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information. $
 */
#ifndef __FS_DOS_H_INCLUDED
#define __FS_DOS_H_INCLUDED

#include <sys/dcmd_blk.h>
#include <sys/platform.h>
#include <sys/types.h>
#include <time.h>

#define DOSFS_BPB_BLOCK			0
#define DOSFS_LONG_NAME_MAX		255
#define DOSFS_SHORT_NAME_MAX	12
#ifdef PATH_MAX
#define DOSFS_PATHNAME_MAX		PATH_MAX
#else
#define DOSFS_PATHNAME_MAX		1024
#endif

#define DOSFS_RDONLY		0x01
#define DOSFS_HIDDEN		0x02
#define DOSFS_SYSTEM		0x04
#define DOSFS_VOLLABEL		0x08
#define DOSFS_DIR			0x10
#define DOSFS_ARCHIVE		0x20
#define DOSFS_LFN			0x0F

#define DOSFS_SFN_NAME		8
#define DOSFS_SFN_EXT		3

#define DOSFS_LFN_SEQNO		0x1F
#define DOSFS_LFN_FINAL		0x40
#define DOSFS_LFN_CHARS		13

#define DOSFS_LCASE_BASE	0x08
#define DOSFS_LCASE_EXT		0x10

__BEGIN_DECLS

typedef union dosfs_dir_entry  {
	struct dosfs_sfn_info {
		_Uint8t			d_name[DOSFS_SFN_NAME];
		_Uint8t			d_ext[DOSFS_SFN_EXT];
		_Uint8t			d_mode;
		_Uint8t			d_ntattr;
		_Uint8t			d_ntftime;
		_Uint16t		d_ftime;
		_Uint16t		d_fdate;
		_Uint16t		d_adate;
		_Uint16t		d_cluster_hi;
		_Uint16t		d_mtime;
		_Uint16t		d_mdate;
		_Uint16t		d_cluster;
		_Uint32t		d_size;
	}		d_sfn;
	struct dosfs_lfn_info {
		_Uint8t			d_sequence;
		uchar_t			d_name_0_4[10];
		_Uint8t			d_mode;
		_Uint8t			d_zero1[1];
		_Uint8t			d_crc;
		uchar_t			d_name_5_10[12];
		_Uint8t			d_zero2[2];
		uchar_t			d_name_11_12[4];
	}		d_lfn;
} dosfs_dir_entry_t;

__END_DECLS

__SRCVERSION("$URL: http://svn/product/branches/6.5.0/trunk/services/blk/fs/dos/public/sys/fs_dos.h $ $Rev: 219613 $")
#endif
