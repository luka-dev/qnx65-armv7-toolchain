#ifndef __FS_ETFS_H_INCLUDED
#define __FS_ETFS_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#include _NTO_HDR_(_pack64.h)

/*
 * The following structures define the format of the ".filetable" file.
 * It consists of 64 byte entries. Each entry starts with two unsigned shorts.
 *   efid - This entry has extended information at index efid
 *   pfid - This entry belongs under another entry at index pfid
 *
 * These are simple indices to other 64 byte entries in the ".filetable".
 *
 * There are two general types of entry.
 *   File entry      - Top bit of efid is 0
 *   Extension entry - Top bit of efid is 1 (mask it off to index)
 *
 * The File entry is by far the most common and is used to hold file and
 * directory entries for the filesystem. Note that pfid is used to implement
 * the directory hierarchy. For a file entry the efid is currently used to
 * point to an extension entry to hold long filenames. The pfid of
 * an extension entry must point back to the original file entry. An
 * extension entry has a type field (tacked at the end so as not to mess up
 * alignment) which should allow new extension types to be implemented in
 * the future.
 */

#define ETFS_FNAME_SHORT_LEN	32
#define ETFS_FNAME_EXT_LEN		59
#define ETFS_FNAME_MAX_LEN		((ETFS_FNAME_SHORT_LEN) + (ETFS_FNAME_EXT_LEN))
#define ETFS_FTABLE_EXTENSION	0x8000

/* Speical reserved fid indexes. Keep lib/etfs and utils/m/mkxfs in sync. */
#define FID_ROOT		0
#define FID_FILETABLE	1
#define FID_BADBLKS		2
#define FID_COUNTS		3
#define FID_LOSTFOUND	4
#define FID_RESERVED	5
#define FID_RESERVE1	FID_LOSTFOUND
#define FID_RESERVE2	FID_RESERVED
#define FID_FIRSTFILE	6

struct etfs_ftable_file {
	_Uint16t	efid;			/* File id of extra info attached to this file */
	_Uint16t	pfid;			/* File id of parent to this file */
	_Uint32t	mode;			/* File mode */
	_Uint32t	uid;			/* User ID of owner */
	_Uint32t	gid;			/* Group ID of owner  */
	_Uint32t	atime;			/* Time of last access */
	_Uint32t	mtime;			/* Time of last modification */
	_Uint32t	ctime;			/* Time of last change */
	_Uint32t	size;			/* File size (always 0 for directories) */
	char		name[ETFS_FNAME_SHORT_LEN];
};


#define ETFS_FTABLE_TYPE_EXTNAME	0

struct etfs_ftable_extname {
	_Uint16t	efid;			/* File id of extra info attached to this file */
	_Uint16t	pfid;			/* File id of parent to this file */
	char		name[ETFS_FNAME_EXT_LEN];
	_Uint8t		type;			/* Type of extension */
} ;


/* Codes for tacode and dacode. Also return values for some of the devio_* calls. */
#define ETFS_TRANS_OK			0		/* A valid transaction */
#define ETFS_TRANS_ECC			1		/* A valid transaction which was corrected by the ECC */
#define ETFS_TRANS_ERASED		2		/* An erased block with an erase stamp */
#define ETFS_TRANS_FOXES		3		/* An erased block */
#define ETFS_TRANS_DATAERR		5		/* crc error (ECC could not correct) */
#define ETFS_TRANS_DEVERR		6		/* Device retuned a hardware error */
#define ETFS_TRANS_BADBLK		7		/* Bad blk marked at the factory (NAND flash only) */
#define ETFS_TRANS_MASK			0x0f	/* Mask for above status */

/*
 * The following bit is set in the return code when the flash media driver
 * (FMD) desires the block to be retired.  This bit does not actually signify
 * an error or a bad block.  The FMD may do this if it believes that the block
 * may be approaching the end of its "lifespan".  For example, if the block
 * has been experiencing a large number of ECC conditions, it may interpret 
 * that as a block soon to go bad.  This bit allows the FMD to signal the ETFS
 * library that the block should probably be retired soon.  It is up to the
 * ETFS library to decide when the block will actually be retired (if it will).
 * If set, it should only be used with the first four ETFS_TRANS_xxx codes.
 */
#define ETFS_TRANS_RETIRE		0x80	

/*
 * Hardware independant transaction data.
 * This is used as the interface between the mtd and the lib. It is also the
 * format used by the mketfs and etfsctl utilities to create and to
 * read/write filesystems in a hardware independant way.
 */
struct etfs_trans {
	_Uint32t	fid;		/* File id */
	_Uint32t	cluster;	/* Cluster offset in file */
	_Uint16t	nclusters;	/* Number of contiguious clusters for this transaction */
	_Uint8t		tacode;		/* Code for transaction area */
	_Uint8t		dacode;		/* Code for data area */
	_Uint32t	sequence;	/* Sequence for this transaction */
};


/* The etfs high level code may base some decisions on the type of media */
#define ETFS_MEMTYPE_NAND		0	/* NAND flash */
#define ETFS_MEMTYPE_NOR		1	/* NOR flash */
#define ETFS_MEMTYPE_RAM		2	/* RAM, SDRAM */
#define ETFS_MEMTYPE_DISK		3	/* Disk (although not designed for disk) */

/* Return values from the ecc() callout below */
#define ETFS_ECC_GOOD			0
#define ETFS_ECC_CORRECTED		1
#define ETFS_ECC_ERROR			2

/*
 * The device is composed of blks. A blk consists of pages.
 *
 * |PPPPPPPPPPPPPPPP|PPPPPPPPPPPPPPPP|PPPPPPPPPPPPPPPP|...
 *       blk 0           blk 1             blk 2
 *
 * You can only erase an entire blk at one time.
 *
 * Each page consists of two parts. A data area and a spare area.
 *
 * ddddddddddddddddS
 *
 * In NAND the data and spare are bound together as part of the device.
 * In NOR and RAM there is no spare area so we create our own.
 * The spare area is used to hold the transaction information. The upper level
 * code has no knowledge of the format of this area. It is not even necessary
 * for the data and the spare to be together - but they must be in the same blk.
 *
 * dddddddddS dddddddddS ddddddddS   OR  S S S dddddddd dddddddd dddddddd
 *
 * The ecc is only needed for NAND to overcome its single bit error tendencies.
 */
struct etfs_devio {
	unsigned		memtype;		/* Type of device */
	unsigned		clustersize;	/* Size of a cluster */
	unsigned		sparesize;		/* Size of a spare area after a cluster */
	unsigned		clusters2blk;	/* Clusters in a block */
	unsigned		numblks;		/* Number of blks */
	unsigned		numrblks;		/* Total Number of blocks allocated to the raw area */
	unsigned		blksize;		/* Size of an erase blk */
	unsigned		flags;			/* Driver capability flags */
	char			id[16];			/* A name for the device */
	void			*cio;			/* Points to a device specific io struct defined in the driver */
	volatile int	preempt;		/* If no zero higher level wants us to preempt */
	int				reserved[16];	/* Future expansion */

	unsigned		(*crc16)(_Uint8t *buf, int len);
	unsigned		(*crc32)(_Uint8t *buf, int len);
	int				(*ecc)(_Uint8t *buf, _Uint8t (*vec)[3], int nvec, int correct);
	int				(*ecc32)(_Uint8t *buf, _Uint8t (*vec)[3], int nvec, int correct);
	int				(*ecc64)(_Uint8t *buf, _Uint8t (*vec)[3], int nvec, int correct);
	int				(*ecc128)(_Uint8t *buf, _Uint8t (*vec)[3], int nvec, int correct);
	int				(*ecc256)(_Uint8t *buf, _Uint8t (*vec)[3], int nvec, int correct);
	void			(*log)(int severity, const char *fmt, ...);
};
#define ETFS_DEVIO_FLAG_NOWEAR	0x0001


/*
 * Device io routines provided by the mtd and called by the etfs lib
 */
/* Returns -1 on error */
int		devio_options(struct etfs_devio *dev, char *str);
int		devio_init(struct etfs_devio *dev);
int		devio_sync(struct etfs_devio *dev);

/* Returns ETFS_TRANS_XXX */
int		devio_readtrans(struct etfs_devio *dev, unsigned cluster, struct etfs_trans *trp);
int		devio_readcluster(struct etfs_devio *dev, unsigned cluster, _Uint8t *data, struct etfs_trans *trp);
int		devio_postcluster(struct etfs_devio *dev, unsigned cluster, _Uint8t *data, struct etfs_trans *trp);
int		devio_eraseblk(struct etfs_devio *dev, unsigned blk);
int		devio_retireblk(struct etfs_devio *dev, unsigned blk);

/*
 * Startup/Run routine provided by the etfs lib and called by the device mtd
 */
int		etfs_main(int argc, char *argv[]);

#include _NTO_HDR_(_packpop.h)

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/etfs/public/fs/etfs.h $ $Rev: 227581 $" )
#endif
