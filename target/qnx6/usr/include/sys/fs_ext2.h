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
/*
 * Copyright (c) 1997 Manuel Bouyer.
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#ifndef __FS_EXT2_H_INCLUDED
#define __FS_EXT2_H_INCLUDED

#if defined(__WATCOMC__) && !defined(_ENABLE_AUTODEPEND)
 #pragma read_only_file;
#endif

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#include <_pack64.h>

/*
 * Filesystem identification
 */
#define E2FS_MAGIC	0xef53	/* the ext2fs magic number */
#define E2FS_REV	0		/* revision level */

/*
 * Filesystem version codes
 */
#define E2FS_OLD_REV	0

/*
 * Filesystem clean flags
 */
#define E2FS_ISCLEAN	0x01	/* Unmounted cleanly */
#define E2FS_ERRORS		0x02	/* Errors detected */

/*
 * Error behabiour
 */
#define E2FS_ERROR_CONTINUE	1	/* Ignore the error */
#define E2FS_ERROR_RO		2	/* Remount as read-only */
#define E2FS_ERROR_PANIC	3	/* Die Die Die! */

/*
 * Offset of main superblock (in bytes)
 */
#define E2FS_SB_OFFSET		1024

/*
 * Default logical block sizes (in bytes)
 */
#define E2FS_SB_LOG_BLOCK_SIZE			1024
#define E2FS_SB_LOG_FRAG_SIZE			1024
#define E2FS_SB_LOG_BLOCK_SIZE_SHIFT	10
#define E2FS_SB_LOG_FRAG_SIZE_SHIFT	    10

/*
 * Constants for superblock structure
 */
#define E2FS_SB_PAD_SIZE	76

/*
 * Size of a group descriptor
 */
#define E2FS_GROUP_DES_SIZE	32

/*
 * Size of an inode
 */
#define E2FS_INODE_SIZE		128

/*
 * Location of important inodes
 */
#define E2FS_ROOT_INODE		2
#define E2FS_FIRST_INODE    11
 
/*
 * Max number of hard links to a file
 */
#define E2FS_MAX_HARD_LINKS	32000

/*
 * Filetypes embedded in directory entries
 */
#define E2FS_FILETYPE_UNKNOWN   0x00
#define E2FS_FILETYPE_REG       0x01
#define E2FS_FILETYPE_DIR       0x02
#define E2FS_FILETYPE_CHR       0x03
#define E2FS_FILETYPE_BLK       0x04
#define E2FS_FILETYPE_FIFO      0x05
#define E2FS_FILETYPE_SOCK      0x06
#define E2FS_FILETYPE_LNK       0x07
 
/*
 * Inode's [in]direct blocks
 */
#define E2FS_DIR_BLOCKS		12
#define E2FS_SIND_BLOCK		E2FS_DIR_BLOCKS
#define E2FS_DIND_BLOCK		(E2FS_SIND_BLOCK + 1)
#define E2FS_TIND_BLOCK		(E2FS_DIND_BLOCK + 1)
#define E2FS_NUM_BLOCKS		(E2FS_TIND_BLOCK + 1)

/*
 * Max file name length
 */
#define E2FS_MAX_FILENAME_LEN	255

/*
 * Max path name length (artificial limit)
 */
#ifdef PATH_MAX
#define E2FS_MAX_PATHNAME_LEN	PATH_MAX
#else
#define E2FS_MAX_PATHNAME_LEN	1024
#endif

/*
 * Max fast symlink length
 */
#define E2FS_MAX_FAST_SYM_LEN	60

/*
 * Preallocation stuff
 */
#define E2FS_PREALLOC_BLOCKS	8

/*
 * Feature set definitions
 */

/* Can mount R/W if we support these features */
#define E2FS_COMPAT_DIR_PREALLOC	0x0001

/* Can mount R/O if these features are present */
#define E2FS_RO_COMPAT_SPARSE_SB	0x0001
#define E2FS_RO_COMPAT_LARGE_FILES	0x0002
#define E2FS_RO_COMPAT_BTREE_DIR	0x0004

/* Fail mount if we don't support these features */
#define E2FS_INCOMPAT_COMPRESS		0x0001
#define E2FS_INCOMPAT_FILETYPE		0x0002

/* We don't do directory prealloc */
#define E2FS_COMPAT_FEATURES		0x0000

/* Die if unlisted features are present */
#define E2FS_INCOMPAT_FEATURES	    (E2FS_INCOMPAT_FILETYPE)

/* Only mount R/O if unlisted features are present */
#define E2FS_RO_FEATURES			(E2FS_RO_COMPAT_SPARSE_SB)

__BEGIN_DECLS

typedef struct ext2_dir {
	_Uint32t	d_inode;	/* inode number of entry */
	_Uint16t	d_reclen;	/* length of this record */
	_Uint16t	d_namlen;	/* length of string in d_name */
	char		d_name[E2FS_MAX_FILENAME_LEN + 1];/* name with length */
} ext2_dir_t;

typedef struct ext2_v1_dir {
	_Uint32t	d_inode;	/* inode number of entry */
	_Uint16t	d_reclen;	/* length of this record */
	_Uint8t		d_namlen;	/* length of string in d_name */
	_Uint8t		d_filetype;	/* type of file */
	char		d_name[E2FS_MAX_FILENAME_LEN + 1];/* name with length */
} ext2_v1_dir_t;

typedef struct ext2_SB {
	_Uint32t	s_icount;			/* Inode count */
	_Uint32t	s_bcount;			/* blocks count */
	_Uint32t	s_rbcount;			/* reserved blocks count */
	_Uint32t	s_fbcount;			/* free blocks count */
	_Uint32t	s_ficount;			/* free inodes count */
	_Uint32t	s_first_dblock;		/* first data block */
	_Uint32t	s_log_bsize;		/* block size = 1024*(2^e2fs_log_bsize) */
	_Uint32t	s_fsize;			/* fragment size */
	_Uint32t	s_bpg;				/* blocks per group */
	_Uint32t	s_fpg;				/* frags per group */
	_Uint32t	s_ipg;				/* inodes per group */
	_Uint32t	s_mtime;			/* mount time */
	_Uint32t	s_wtime;			/* write time */
	
	_Uint16t	s_mnt_count;		/* mount count */
	_Uint16t	s_max_mnt_count;	/* max mount count */
	_Uint16t	s_magic;			/* magic number */
	_Uint16t	s_state;			/* file system state */
	_Uint16t	s_beh;				/* behavior on errors */
	_Uint16t	s_minor_rev;		/* minor revision level */
	
	_Uint32t	s_lastfsck;			/* time of last fsck */
	_Uint32t	s_fsckintv;			/* max time between fscks */
	_Uint32t	s_creator;			/* creator OS */
	_Uint32t	s_rev;				/* revision level */
	
	_Uint16t	s_ruid;				/* default uid for reserved blocks */
	_Uint16t	s_rgid;				/* default gid for reserved blocks */
	
	/* V1 fields */
	_Uint32t	s_first_ino;			/* first non-reserved inode */
	_Uint16t	s_inode_size;			/* size of inode structure */
	_Uint16t	s_block_group_nr;		/* block grp number of this sblk*/
	_Uint32t	s_features_compat;		/*  OK to mount if unknown */
	_Uint32t	s_features_incompat;	/* not OK to mount if unknown */
	_Uint32t	s_features_compat_ro;	/* OK to mount ro if unknown */

	_Uint32t	s_reserved[102];
} ext2_SB_t;

/*
 * Group Descriptor
 *
 *	Right after the superblock is the list of group descriptors.
 *	Each descriptor describes a block group, each has its own
 *	bitmaps and tables. The superblock and group descriptors are
 *	replicated at the beginning of every block group.
 */
typedef struct ext2_group {
	_Uint32t	g_b_bitmap;	/* blocks bitmap block */
	_Uint32t	g_i_bitmap;	/* inodes bitmap block */
	_Uint32t	g_i_tables;	/* inodes table block  */
	
	_Uint16t	g_b_free;	/* number of free blocks */
	_Uint16t	g_i_free;	/* number of free inodes */
	_Uint16t	g_dirs;		/* number of directories */

	_Uint8t		g_reserved[14];	/* 18 */
} ext2_group_t;

typedef struct ext2_inode {
	_Uint16t	i_mode;		/*   0: IFMT, permissions; see below. */
	_Uint16t	i_uid;		/*   2: Owner UID */
	_Uint32t	i_size;		/*   4: Size (in bytes) */
	_Uint32t	i_atime;	/*   8: Acces time */
	_Uint32t	i_ctime;	/*  12: Create time */
	_Uint32t	i_mtime;	/*  16: Modification time */
	_Uint32t	i_dtime;	/*  20: Deletion time */
	_Uint16t	i_gid;		/*  24: Owner GID */
	_Uint16t	i_nlink;	/*  26: File link count */
	_Uint32t	i_nblock;	/*  28: Blocks count */
	_Uint32t	i_flags;	/*  32: Status flags (chflags) */

	_Uint32t	i_reserved1; /* 36 */

	_Uint32t	i_blocks[E2FS_NUM_BLOCKS]; /* 40: disk blocks */
	_Uint32t	i_gen;		/* 100: generation number (file version) */
	_Uint32t	i_facl;		/* 104: file ACL (not implemented) */
	_Uint32t	i_dacl;		/* 108: dir ACL (not implemented) */
	_Uint32t	i_faddr;	/* 112: fragment address */

	_Uint8t		i_nfrag;	/* 116: fragment number */
	_Uint8t		i_fsize;	/* 117: fragment size */

	_Uint16t	i_reserved2;	/* 118 */
	_Uint32t	i_reserved3[2];	/* 120 */
} ext2_inode_t;

__END_DECLS

#include <_packpop.h>

__SRCVERSION("$URL: http://svn/product/branches/6.5.0/trunk/services/blk/fs/ext2/public/sys/fs_ext2.h $ $Rev: 219613 $")
#endif
