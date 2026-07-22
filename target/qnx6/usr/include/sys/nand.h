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



/*
 *  nand.h   Non-portable low-level nand flash lib definitions
 *

 */
#ifndef __NAND_H_INCLUDED
#define __NAND_H_INCLUDED

#ifndef _INTTYPES_H_INCLUDED
 #include <inttypes.h>
#endif

#include <_pack64.h>
#include <pthread.h>

#define NO_ERROR			0
#define CORRECTED_ERROR		1
#define ECC_ERROR			2
#define UNCORRECTABLE_ERROR	3

#define NAND_SPARESIZE	16
#define NAND_DATASIZE	512
#define NAND_PAGESIZE	528
#define NAND_SIGNATURE	"dlaaldfe"

#define RECLAIM_CNT(x)		((x) & 0x3f)
#define RECLAIM_BADBLK		0x80
#define RECLAIM_SPAREBLK	0x40
#define RECLAIM_SKIP(x)   	((x) & (RECLAIM_BADBLK|RECLAIM_SPAREBLK))

/* spare.status */
#define NAND_GOOD		0xFF	/* Good. */
#define NAND_BAD		0x00	/* Marked at the factory. */

/*
   Values which are used to force a block back into circulation for erasure
   The MIN keeps blocks from bouncing back and forth.
*/
#define FORCE_PERCENTAGE	80		/* Must have erase cnt less than 80% of average */
#define FORCE_MIN			100		/* Must be at least # erases below current reclaim blk */

/*
** The flash is organized as N blocks with each block containing M pages.
** Each page is 528 bytes. The first 512 bytes is used to hold user data
** while the spare 16 bytes is used by the driver. The 6th byte into the
** spare area is set to non-FF by the factory to indicate bad blocks. The
** other bytes in this spare area are used for ECC, logical to physcial
** mappings etc.
** 
** Size   Blocks  Pages/Block  Total 528 byte pages
**   8M    1024       16           16K
**  16M    1024       32           32K
**  32M    2048       32           64K
**  64M    4096       32          128K
** 128M    8192       32          256K
**
**
** An erase operation is on an entire block (typically 32 pages).
*/

struct nandspare {
	uint8_t		ecc1[3];	/* ECC for first 256 bytes */
	uint8_t		ecc3[2];	/* ECC for first 256 bytes */
	uint8_t		status;		/* FF if good, 00 if bad */
	uint8_t		map[7];		/* 38 bit cycle, 18 bit fsys logical block */
	uint8_t		ecc2[3];	/* ECC for second 256 bytes */
} ;

struct nandpage {
	uint8_t				data[NAND_DATASIZE];
        struct nandspare	spare;
} ;

struct nandctrl {
	char				*name;			/* Name of program */
	uint32_t			sequence;
	uint32_t			addrcycles;		/* Address cycles */
	uint32_t			pages2block;	/* Pages per block (16 or 32) */
	uint32_t			numblks;		/* 1024, 2048, 4096, ... */
	uint32_t			numebadblks;
	uint32_t			numlbadblks;
	uint32_t			totspares;
	uint32_t			numspares;
	uint32_t			numpages;		/* Total number of pages */
	uint16_t			*pagemap;		/* Logical fsys blk to page mapping */
	uint32_t			pagemapsize;	/* Number of bytes in pagemap */
	uint32_t			pagemapbits;	/* bitwidth of each item in pagemap */
	uint32_t			pagemapmask;	/* (1 << pagemapbits) -1 */
	uint32_t			notmapped;		/* (1 << pagemapbits) -1 */
	uint32_t			pagemask;		/* Mask for pages per block */
	uint32_t			updatebb;
	uint32_t			numrawblks;		/* Number of blks at the start of the device. */

	uint32_t            numreclaim;
	uint8_t				*reclaim;
	uint32_t			reclaimblk;		/* An erased block used for reclaiming */

	uint32_t			numfree;
	uint32_t			bitmapblk;
	uint32_t			*bitmap;

	uint32_t			erasecnt;
	uint16_t			*erasecnts;

	uint8_t				addr[4];
	struct nandpage		*pagedata;		/* Pointer to a working page buffer */
	struct nandpage		*verify;

	uint32_t			stat_retries;
	uint32_t			stat_tretries;
	uint32_t			stat_blkc;
	uint32_t			stat_tblkc;

	pthread_mutex_t		*mutex;
	uintptr_t			enable;
	uintptr_t			io_data;
	uintptr_t			io_command;
	uintptr_t			io_address;
	uintptr_t			io_status;
	uintptr_t			io_rdy;
	uintptr_t			HIT_flcmncr;
	uintptr_t			HIT_flcmdcr;
	uintptr_t			HIT_flcmcdr;
	uintptr_t			HIT_fladr;
	uintptr_t			HIT_fldatar;
	uintptr_t			HIT_fltrcr;
	uintptr_t			HIT_fldtcntr;
	uintptr_t			HIT_flbsycnt;
	uintptr_t			HIT_flintdmacr;
	uintptr_t			HIT_fldtfifo;
    uint32_t			lastcmd;
	uint32_t			lastpage;

	struct options {
		int			erase;
		int			verbose;
		int			verify;
		int			parttype;
		uint32_t	numrawblks;
		uint32_t    timeout;
		uint64_t	base;
		int			shift;
		/* Forced failure simulation is only in the nand-ram driver */
		int			readfailure;	/* Simulate 1/readfailure on read */
		int			postfailure;	/* Simulate 1/postfailure on post */
		int			erasefailure;	/* Simulate 1/erasefailure on erase */
	} op;
} ;


/*
** Routines which higher level code (like the CAM block driver) use.
*/
int      nand_init(struct nandctrl *ncp);
int      nand_size(struct nandctrl *ncp);
int      nand_spares(struct nandctrl *ncp);
int      nand_erase(struct nandctrl *ncp, int erase);
int      nand_partition(struct nandctrl *ncp, int type);
int      nand_reclaim(struct nandctrl *ncp);
int      nand_read(struct nandctrl *ncp, unsigned lblk, uint8_t *data, unsigned npages);
int      nand_write(struct nandctrl *ncp, unsigned lblk, uint8_t *data, unsigned npages);

/*
** Routines which directly interface with the NAND chip.
*/
int      nandio_init1(struct nandctrl *ncp);
int      nandio_init2(struct nandctrl *ncp);
int      nandio_reset(struct nandctrl *ncp);
int      nandio_idread(struct nandctrl *ncp, struct nandpage *data);
int      nandio_readpage(struct nandctrl *ncp, unsigned page, struct nandpage *data);
int      nandio_readspare(struct nandctrl *ncp, unsigned page, struct nandpage *data);
int      nandio_postpage(struct nandctrl *ncp, unsigned page, struct nandpage *data);
int      nandio_writespare(struct nandctrl *ncp, unsigned page, struct nandpage *data);
int      nandio_eraseblk(struct nandctrl *ncp, unsigned blk);

/*
** Internal routines which may be used for debugging
*/
void     nand_setecc(struct nandpage *pdp);
int      nand_getecc(struct nandpage *pdp);
int      nand_geteccspare(struct nandpage *pdp);


/*
** Debug routines
*/
void     nand_checktables(struct nandctrl *ncp, int instance);
void     nand_printtables(struct nandctrl *ncp, int instance);

#include <_packpop.h>

#endif

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/flash-nand/public/sys/nand.h $ $Rev: 219996 $" )
