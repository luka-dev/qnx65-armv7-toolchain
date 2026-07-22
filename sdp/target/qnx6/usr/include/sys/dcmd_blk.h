/*
 * $QNXLicenseC:
 * Copyright 2009, QNX Software Systems. All Rights Reserved.
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
#ifndef __DCMD_BLK_H_INCLUDED
#define __DCMD_BLK_H_INCLUDED

#include <devctl.h>
#include <fcntl.h>
#include <inttypes.h>
#include <sys/types.h>

#define DCMD_BLK_PARTENTRY			__DIOF(_DCMD_BLK,    1, struct partition_entry)
#define DCMD_BLK_FORCE_RELEARN		__DION(_DCMD_BLK,    2)
#define DCMD_BLK_PART_DESCRIPTION	__DIOF(_DCMD_BLK,    3, struct partition_description)

#define DCMD_FSYS_STATISTICS		__DIOF(_DCMD_FSYS,  11, struct fs_stats)
#define DCMD_FSYS_STATISTICS_CLR	__DIOF(_DCMD_FSYS,  12, struct fs_stats)
#define DCMD_FSYS_STATVFS			__DIOF(_DCMD_FSYS,  13, struct statvfs)
#define DCMD_FSYS_PREGROW_FILE		__DIOT(_DCMD_FSYS,  14, off64_t)
#define DCMD_FSYS_DIRECT_IO			__DIOT(_DCMD_FSYS,  15, struct fs_directio)
#define DCMD_FSYS_MOUNTED_ON		__DIOF(_DCMD_FSYS,  16, char[256])
#define DCMD_FSYS_MOUNTED_AT		__DIOF(_DCMD_FSYS,  17, char[256])
#define DCMD_FSYS_MOUNTED_BY		__DIOF(_DCMD_FSYS,  18, char[256])
#define DCMD_FSYS_OPTIONS			__DIOF(_DCMD_FSYS,  19, char[256])
#define DCMD_FSYS_FILE_FLAGS		__DIOTF(_DCMD_FSYS,	20,	struct fs_fileflags)
#define DCMD_FSYS_MAP_OFFSET		__DIOTF(_DCMD_FSYS, 21, union fs_blkmap)
#define DCMD_FSYS_LABEL				__DIOF(_DCMD_FSYS,  22, char[256])
#define DCMD_FSYS_FORCE_RELEARN		DCMD_BLK_FORCE_RELEARN

__BEGIN_DECLS

#define FS_PARTITION_PC		"pc\x00\x00"
#define FS_PARTITION_GPT	"gpt\x00"
struct partition_description {
	char			scheme[4];
	_Uint32t		index;
	_Uint64t		header;
	char			fsdll[16];
	char			reserved[96];
	union {
		struct part_pc_entry {
			_Uint8t		boot_ind;
			_Uint8t		beg_head;
			_Uint8t		beg_sector;
			_Uint8t		beg_cylinder;
			_Uint8t		os_type;
			_Uint8t		end_head;
			_Uint8t		end_sector;
			_Uint8t		end_cylinder;
			_Uint32t	part_offset;
			_Uint32t	part_size;
		}		pc;
		struct part_gpt_entry {
			_Uint8t		PartitionTypeGuid[16];
			_Uint8t		UniquePartitionGuid[16];
			_Uint64t	StartingLBA;
			_Uint64t	EndingLBA;
			_Uint64t	Attributes;
			_Uint16t	PartitionName[36];
		}		gpt;
	}				entry;
};

#define FS_DIO_READ			(O_RDONLY + 1)
#define FS_DIO_WRITE		(O_WRONLY + 1)
#define FS_DIO_SYNC			O_SYNC
struct fs_directio {
	off64_t		offset;
	uint32_t	nbytes;
	uint32_t	flags;
	paddr_t		paddr;
	caddr_t		vaddr;
};

#define FS_FLAGS_GENERIC	0
#define FS_FLAGS_FSYS		1
#define FS_FLAGS_BACKUP		0x0001
#define FS_FLAGS_HIDDEN		0x0002
#define FS_FLAGS_COMMITTING	0x2000
#define FS_FLAGS_CONTIGUOUS	0x4000
#define FS_FLAGS_DIRTY		0x8000
struct fs_fileflags {
	uint16_t	mask[2];
	uint16_t	bits[2];
	char		basetype[16];
};

#define FS_BMAP_FSYS		0x00
#define FS_BMAP_DEVICE		0x01
union fs_blkmap {
	struct {
		off64_t		logical;
		uint32_t	flags;
	} i;
	struct {
		off64_t		physical;
		uint32_t	nbytes;
	} o;
};

__END_DECLS

__SRCVERSION("$URL: http://svn/product/branches/6.5.0/trunk/services/blk/io-blk/public/sys/dcmd_blk.h $ $Rev: 231060 $")
#endif
