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
#ifndef __FS_QNX6_H_INCLUDED
#define __FS_QNX6_H_INCLUDED

#include <sys/platform.h>
#include <sys/types.h>

#define QNX6FS_NAME_MAX			510
#define QNX6FS_SYMLINK_MAX		512
#ifdef PATH_MAX
#define QNX6FS_PATH_MAX			PATH_MAX
#else
#define QNX6FS_PATH_MAX			1024
#endif

#define QNX6FS_DIRECT_BLKS		16
#define QNX6FS_INDIRECT_LEVELS	3
#define QNX6FS_UNUSED_BLK		((_Uint32t)-1)

#define QNX6FS_INO_USED			0x01
#define QNX6FS_INO_MODIFIED		0x02

typedef struct q6_dinode {
	_Uint64t			i_size;
	_Uint32t			i_uid;
	_Uint32t			i_gid;
	_Uint32t			i_ftime;
	_Uint32t			i_mtime;
	_Uint32t			i_atime;
	_Uint32t			i_ctime;
	_Uint16t			i_mode;
	_Uint16t			i_nlink;
	_Uint32t			i_blocks[QNX6FS_DIRECT_BLKS];
	_Uint8t				i_indirect;
	_Uint8t				i_flags;
	_Uint8t				i_spare[26];
} q6_dinode_t;

typedef struct q6_iinode {
	_Uint64t			i_size;
	_Uint32t			i_blocks[QNX6FS_DIRECT_BLKS];
	_Uint8t				i_indirect;
	_Uint8t				i_flags;
	_Uint8t				i_spare[6];
} q6_iinode_t;

#define QNX6FS_DIR_EOF			0x00
#define QNX6FS_DIR_LONGNAME		0xFF
#define QNX6FS_DIR_DELETED		0
#define QNX6FS_DIR_SHORT_LEN	27

typedef struct q6_direntry {
	_Uint32t			d_inode;
	union {
		struct {
			_Uint8t		d_length;
			char		d_name[QNX6FS_DIR_SHORT_LEN];
		}				d_short;
		struct {
			_Uint8t		d_islfn;
			_Uint8t		d_spare1[3];
			_Uint32t	d_blkno;
			_Uint32t	d_cksum;
			_Uint8t		d_spare2[16];
		}				d_long;
	}					d_name;
} q6_direntry_t;

typedef struct q6_longname {
	_Uint16t			d_length;
	char				d_name[QNX6FS_NAME_MAX];
} q6_longname_t;

#define QNX6FS_SIGNATURE		0x68191122
#define QNX6FS_ROOT_INODE		1
#define QNX6FS_BOOTDIR_INODE	2
#define QNX6FS_FSYS_VERSION		4
#define QNX6FS_SBLK_SIZE		512
#define QNX6FS_SBLK_RSRV		4096
#define QNX6FS_BOOT_RSRV		8192
#define QNX6FS_BOOTDIR_SIZE		4096
#define QNX6FS_DEFAULT_RSRV		3
#define QNX6FS_MAX_NGROUPS		64

#define QNX6FS_SBLK_UNSTABLE	0x00000001
#define QNX6FS_SBLK_V3_LE_RSRV	0x00000002
#define QNX6FS_LFN_CKSUM		0x00000100
#define QNX6FS_SBLK_V3_BE_RSRV	0x40000000
#define QNX6FS_MASK_INCOMPAT	0x00FF0000
#define QNX6FS_MASK_READONLY	0x0000FF00

typedef struct q6_superblock {
	_Uint32t			s_signature;
	_Uint32t			s_chksum;
	_Uint64t			s_seqno;
	_Uint32t			s_fmttime;
	_Uint32t			s_wrtime;
	_Uint32t			s_flags;
	_Uint16t			s_version;
	_Uint16t			s_rsrvblks;
	_Uint8t				s_uuid[16];
	_Uint32t			s_blksize;
	_Uint32t			s_ninodes;
	_Uint32t			s_finodes;
	_Uint32t			s_nblocks;
	_Uint32t			s_fblocks;
	_Uint32t			s_ngroups;
	q6_iinode_t			s_inodes;
	q6_iinode_t			s_bitmap;
	q6_iinode_t			s_lnames;
	q6_iinode_t			s_iclaim;
	_Uint8t				s_spare[120];
} q6_superblock_t;

#define QNX6FS_BG_DEFRAG		0x4000
#define QNX6FS_SNAPSHOT_HOLD	0x8000

#define QNX6FS_BOOT_QUIET		0x01
#define QNX6FS_BOOT_CLS			0x02

typedef struct q6_boothdr {
	_Uint8t				b_jmp[3];
	_Uint8t				b_flags;
	_Uint32t			b_offset;
	_Uint32t			b_sblk0;
	_Uint32t			b_sblk1;
} q6_boothdr_t;

__SRCVERSION("$URL: http://svn/product/branches/6.5.0/trunk/services/blk/fs/qnx6/public/sys/fs_qnx6.h $ $Rev: 282669 $")
#endif
