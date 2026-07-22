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
#ifndef __FS_QNX4_H_INCLUDED
#define __FS_QNX4_H_INCLUDED

#include <sys/dcmd_blk.h>
#include <sys/platform.h>
#include <sys/types.h>
#include <time.h>

#define QNX4FS_BLOCK_SIZE			512
#define QNX4FS_BOOT_BLOCK			1L
#define QNX4FS_ROOT_BLOCK			2L
#define QNX4FS_BITMAP_BLOCK			3L
#define QNX4FS_MAX_XTNTS_PER_XBLK	60
#define QNX4FS_LONG_NAME_MAX		48
#define QNX4FS_SHORT_NAME_MAX		16
#ifdef PATH_MAX
#define QNX4FS_PATHNAME_MAX			PATH_MAX
#else
#define QNX4FS_PATHNAME_MAX			1024
#endif

#define QNX4FS_FILE_USED			0x01
#define QNX4FS_FILE_MODIFIED		0x02
#define QNX4FS_FILE_BUSY			0x04
#define QNX4FS_FILE_LINK			0x08
#define QNX4FS_FILE_INODE			0x10
#define QNX4FS_FSYS_CLEAN			0x20
#define QNX4FS_FILE_GROWN			0x40

__BEGIN_DECLS

typedef _Uint8t		qnx4fs_ftype_t;
typedef _Uint16t	qnx4fs_nxtnt_t;
typedef _Uint16t	qnx4fs_mode_t;
typedef _Uint16t	qnx4fs_nlink_t;
typedef _Uint16t	qnx4fs_uid_t;
typedef _Uint16t	qnx4fs_gid_t;
typedef _Uint32t	qnx4fs_daddr_t;
typedef _Uint32t	qnx4fs_size_t;

typedef struct qnx4fs_xtnt {
	qnx4fs_daddr_t		xtnt_blk;
	qnx4fs_daddr_t		xtnt_size;
} qnx4fs_xtnt_t;

typedef struct qnx4fs_xblk {
	qnx4fs_daddr_t		xblk_next_xblk;
	qnx4fs_daddr_t		xblk_prev_xblk;
	_Uint8t				xblk_num_xtnts;
	char				xblk_spare[3];
	_Int32t				xblk_num_blocks;
	qnx4fs_xtnt_t		xblk_xtnts[QNX4FS_MAX_XTNTS_PER_XBLK];
	char				xblk_signature[8];
	qnx4fs_xtnt_t		xblk_first_xtnt;
} qnx4fs_xblk_t;

typedef union qnx4fs_dir_entry  {
	struct qnx4fs_inode_info {
		char				i_fname[QNX4FS_SHORT_NAME_MAX];
		qnx4fs_size_t		i_size;
		qnx4fs_xtnt_t		i_first_xtnt;
		qnx4fs_daddr_t		i_xblk;
		time_t				i_ftime;
		time_t				i_mtime;
		time_t				i_atime;
		time_t				i_ctime;
		qnx4fs_nxtnt_t		i_num_xtnts;
		qnx4fs_mode_t		i_mode;
		qnx4fs_uid_t		i_uid;
		qnx4fs_gid_t		i_gid;
		qnx4fs_nlink_t		i_nlink;
		char				i_zero[4];
		qnx4fs_ftype_t		i_type;
		_Uint8t				i_status;
	}		d_inode;
	struct qnx4fs_link_info {
		char				l_fname[QNX4FS_LONG_NAME_MAX];
		qnx4fs_daddr_t		l_inode_blk;
		_Uint8t				l_inode_ndx;
		char				l_spare[10];
		_Uint8t				l_status;
	}		d_link;
} qnx4fs_dir_entry_t;

__END_DECLS

__SRCVERSION("$URL: http://svn/product/branches/6.5.0/trunk/services/blk/fs/qnx4/public/sys/fs_qnx4.h $ $Rev: 219613 $")
#endif
