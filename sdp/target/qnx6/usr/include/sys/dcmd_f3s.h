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
** File: dcmd_f3s.h
**
** Description:
**
** This file contains the devctl definitions for the f3s resource manager for
** Neutrino.
** POSIX standard devctl dcmds are supported by the flash file system,
** these commands are added for special flash file system needs.
**
** Ident: $Id: dcmd_f3s.h 219996 2009-05-04 18:47:03Z keith $
*/

/*
** Include Loop Prevention
*/

#ifndef __DCMD_F3S_H_INCLUDED
#define __DCMD_F3S_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

/*
** Constant Definitions
*/

#define _DCMD_F3S _DCMD_MEM

/*
** Enum Definitions
*/

typedef enum f3s_devctl_e
{
  F3S_ERASE,      /* erase message */
  F3S_FORMAT,     /* format message */
  F3S_RECLAIM,    /* reclaim message */
  F3S_ARRAYINFO,  /* array info message */
  F3S_PARTINFO,   /* partition info message */
  F3S_UNITINFO,   /* unit info message */
  F3S_MOUNT,      /* mount message */
  F3S_UMOUNT,     /* umount message */
  F3S_EXIT,       /* exit message */
  F3S_BREAK,      /* break message */
  F3S_DEFRAG,     /* defrag message */
  F3S_GETCMP,     /* get compression flag */
  F3S_SETCMP,     /* set compression flag */
  F3S_CLRCMP,     /* clear compression flag */
  F3S_LOCK,       /* lock message */
  F3S_UNLOCK,     /* unlock message */
  F3S_UNLOCKALL,  /* unlock all message */
  F3S_LOCKDOWN,   /* enter lockdown mode */  
  F3S_ULOCKDOWN,  /* Leave lockdown mode */
  F3S_RECLAIMCTL, /* runtime control of reclaims */
  F3S_GEOINFO	  /* Get the flash geometry */		  
}
f3s_devctl_t;

/*
** Structure Definitions
*/

typedef struct f3s_erase_s
{
  _Uint32t status;  /* erase status */
  _Uint32t offset;  /* offset of first unit expressed in bytes */
  _Uint32t limit;   /* limit of last unit expressed in bytes */
}
f3s_erase_t;

typedef struct f3s_format_s
{
  _Uint32t status;       /* format status */
  _Uint32t offset;       /* offset of first unit expressed in bytes */
  _Uint32t limit;        /* limit of last unit expressed in bytes */
  _Uint32t unit_spare;   /* number of spare units */
  _Uint32t align_pow2;   /* alignment power of two */
  _Uint32t xip_pow2;     /* xip power of two */
  _Uint32t name_length;  /* length of name */
/*unit8_t name;             root name */
}
f3s_format_t;

typedef struct f3s_reclaim_s
{
  _Uint32t status;  /* reclaim status */
  _Uint32t limit;   /* lower limit of free size wanted expressed in bytes */
}
f3s_reclaim_t;

typedef struct f3s_arrayinfo_s
{
  _Uint32t status;      /* info status */
  _Uint32t total_size;  /* total size of array expressed in bytes */
  _Uint32t unit_size;   /* size of a chip expressed in bytes */
  _Uint32t chip_size;   /* size of a unit expressed in bytes */
}
f3s_arrayinfo_t;

typedef struct f3s_partinfo_s
{
  _Uint32t status;       /* info status */
  _Uint32t total_size;   /* total size of partition expressed in bytes */
  _Uint32t unit_size;    /* size of a unit expressed in bytes */
  _Uint32t spare_size;   /* spare size within partition expressed in bytes */
  _Uint32t retire_size;  /* retired size within partition expressed in bytes */
  _Uint32t head_size;    /* overhead size expressed in bytes */
  _Uint32t pad_size;     /* alignment padding size expressed in bytes */
  _Uint32t free_size;    /* free size in partition expressed in bytes */
  _Uint32t stale_size;   /* stale size in partition expressed in bytes */
  _Uint32t resv_size;    /* reserved size in partition expressed in bytes */
}
f3s_partinfo_t;

typedef struct f3s_unitinfo_s
{
  _Uint32t status;       /* info status */
  _Uint32t offset;       /* offset of unit in partition */
  _Uint32t unit_size;    /* size of a unit expressed in bytes */
  _Uint32t erase_count;  /* count of erasures on unit */
}
f3s_unitinfo_t;

typedef struct f3s_name_s
{
  _Uint32t status;       /* mount status */
  _Uint32t mount_flags;  /* flags for mount */
  _Uint32t name_length;  /* length of name */
/*unit8_t name;             root name */
}
f3s_name_t;

typedef struct f3s_break_s
{
  _Uint32t status;  /* break status */
  _Uint32t offset;  /* offset of first unit expressed in bytes */
}
f3s_break_t;

typedef struct f3s_defrag_s
{
  _Uint32t status;  /* defrag status */
  _Uint32t size;    /* size of extents expressed in bytes */
}
f3s_defrag_t;

typedef struct f3s_cmdcmp_s
{
  _Uint32t status;    /* cmdcmp status */
  _Uint32t cmp_flag;  /* compression flag */
}
f3s_cmdcmp_t;

typedef struct f3s_unitlock_s
{
  _Uint32t status;  /* lock status */
  _Uint32t offset;  /* offset of first unit expressed in bytes */
  _Uint32t limit;   /* limit of last unit expressed in bytes */
}
f3s_unitlock_t;

typedef struct f3s_unitunlock_s
{
  _Uint32t status;  /* unlock status */
  _Uint32t offset;  /* offset of first unit expressed in bytes */
  _Uint32t limit;   /* limit of last unit expressed in bytes */
}
f3s_unitunlock_t;

typedef struct f3s_arrayunlock_s
{
  _Uint32t status;  /* unlock status */
}
f3s_arrayunlock_t;

typedef struct f3s_lockdown_s
{
  _Uint32t status;
  _Uint32t offset;
  _Uint32t limit;
}
f3s_lockdown_t;

typedef struct f3s_reclaimctl_s
{
  _Int16t super_count;     /* Number of overwrite hops */
  _Int16t stale_percent;   /* Percentage of stale/free */
  _Int16t reclaim_enable;  /* 1 or 0, to enable reclaims */
  _Int16t reserved;        /* To pad the structure */
}f3s_reclaimctl_t;

struct geo_list
{
  _Uint16t unit_num;       /* Number of sectors in run */
  _Uint16t unit_pow2;      /* Sector size for this run */
};

/* This structure will only return a maximum of 16
 * geometries.  In the future when flash parts 
 * have more than 16, there will be an extended
 * form of this devctl.
 */
typedef struct f3s_geoinfo_s
{
  _Uint32t status;
  _Paddr64t base;			/* phys base address */
  _Uint32t size;			/* Size of flash */
  _Uint16t chipwidth;		/* width of a single chip, in bytes */
  _Uint16t interleave;		/* Number of chips in parallel on data bus */
  _Uint16t num_geo;         /* Number of entries in the geo array */
  struct geo_list geo[16];	/* Maximum of 16 distinct geos */
}f3s_geoinfo_t;

/*
** Macros Definitions
*/

#define DCMD_F3S_ERASE     __DIOT(_DCMD_F3S, F3S_ERASE, f3s_erase_t)
#define DCMD_F3S_FORMAT    __DIOT(_DCMD_F3S, F3S_FORMAT, f3s_format_t)
#define DCMD_F3S_RECLAIM   __DIOT(_DCMD_F3S, F3S_RECLAIM, f3s_reclaim_t)
#define DCMD_F3S_ARRAYINFO __DIOTF(_DCMD_F3S, F3S_ARRAYINFO, f3s_arrayinfo_t)
#define DCMD_F3S_PARTINFO  __DIOTF(_DCMD_F3S, F3S_PARTINFO, f3s_partinfo_t)
#define DCMD_F3S_UNITINFO  __DIOTF(_DCMD_F3S, F3S_UNITINFO, f3s_unitinfo_t)
#define DCMD_F3S_MOUNT     __DIOT(_DCMD_F3S, F3S_MOUNT, f3s_name_t)
#define DCMD_F3S_UMOUNT    __DIOT(_DCMD_F3S, F3S_UMOUNT, f3s_name_t)
#define DCMD_F3S_EXIT      __DIOT(_DCMD_F3S, F3S_EXIT, f3s_name_t)
#define DCMD_F3S_BREAK     __DIOT(_DCMD_F3S, F3S_BREAK, f3s_break_t)
#define DCMD_F3S_DEFRAG    __DIOT(_DCMD_F3S, F3S_DEFRAG, f3s_defrag_t)
#define DCMD_F3S_GETCMP    __DIOTF(_DCMD_F3S, F3S_GETCMP, f3s_cmdcmp_t)
#define DCMD_F3S_SETCMP    __DIOT(_DCMD_F3S, F3S_SETCMP, f3s_cmdcmp_t)
#define DCMD_F3S_CLRCMP    __DIOT(_DCMD_F3S, F3S_CLRCMP, f3s_cmdcmp_t)
#define DCMD_F3S_LOCK      __DIOT(_DCMD_F3S, F3S_LOCK, f3s_unitlock_t)
#define DCMD_F3S_UNLOCK    __DIOT(_DCMD_F3S, F3S_UNLOCK, f3s_unitunlock_t)
#define DCMD_F3S_UNLOCKALL __DIOT(_DCMD_F3S, F3S_UNLOCKALL, f3s_arrayunlock_t)
#define DCMD_F3S_LOCKDOWN  __DIOT(_DCMD_F3S, F3S_LOCKDOWN, f3s_lockdown_t)
#define DCMD_F3S_ULOCKDOWN __DIOT(_DCMD_F3S, F3S_ULOCKDOWN, f3s_lockdown_t)
#define DCMD_F3S_RECLAIMCTL __DIOTF(_DCMD_F3S, F3S_RECLAIMCTL, f3s_reclaimctl_t)
#define DCMD_F3S_GEOINFO    __DIOTF(_DCMD_F3S, F3S_GEOINFO, f3s_geoinfo_t)

#endif /* __DCMD_F3S_H_INCLUDED */

/*
** End
*/

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/fs-flash3/public/sys/dcmd_f3s.h $ $Rev: 219996 $" )
