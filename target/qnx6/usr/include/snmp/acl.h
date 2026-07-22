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






#ifndef _ACL_H_INCLUDED
#define _ACL_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif

#include <_pack64.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
  aclTarget        INTEGER,
  aclSubject       INTEGER,
  aclResources     INTEGER,
  aclPrivileges    INTEGER,
  aclStorageType   StorageType,
  aclStatus        RowStatus
 */

#define ACLTARGET	1
#define ACLSUBJECT	2
#define ACLRESOURCES	3
#define ACLPRIVELEGES	4
#define ACLSTORAGETYPE	5
#define ACLSTATUS	6

#define ACLNONEXISTENT        0
#define ACLACTIVE             1
#define ACLNOTINSERVICE       2
#define ACLNOTREADY           3
#define ACLCREATEANDGO        4
#define ACLCREATEANDWAIT      5
#define ACLDESTROY            6

#define ACLPRIVELEGESGET		1
#define ACLPRIVELEGESGETNEXT		2
#define ACLPRIVELEGESGETRESPONSE	4
#define ACLPRIVELEGESSET		8
#define ACLPRIVELEGESBULK		32
#define ACLPRIVELEGESINFORM		64
#define ACLPRIVELEGESTRAP2		128

struct aclEntry {
    int		aclTarget;
    int		aclSubject;
    int		aclResources;
    int		aclPriveleges;
    int		aclStorageType;
    int		aclStatus;
    
    u_long	aclBitMask;

    struct aclEntry *reserved;
    struct aclEntry *next;
};

int read_acl_database(const char *filename);
/* 
 *Loads the Access Control List database file 
 */

struct aclEntry *
acl_getEntry(int target, int subject, int resources);
/*
 * Returns a pointer to the aclEntry with the
 * same target and subject and resources.
 * Returns NULL if that entry does not exist.
 */

void acl_scanInit(void);
/*
 * Initialized the scan routines so that they will begin at the
 * beginning of the list of aclEntries.
 *
 */


struct aclEntry *
acl_scanNext(void);
/*
 * Returns a pointer to the next aclEntry.
 * These entries are returned in no particular order,
 * but if N entries exist, N calls to acl_scanNext() will
 * return all N entries once.
 * Returns NULL if all entries have been returned.
 * acl_scanInit() starts the scan over.
 */

struct aclEntry *
acl_createEntry(int target, int subject, int resources);
/*
 * Creates a aclEntry with the given index
 * and returns a pointer to it.
 * The status of this entry is created as invalid.
 */

void acl_destroyEntry(int target, int subject, int resources);
/*
 * Free the aclEntry 
 */ 


#include <_packpop.h>

#ifdef __cplusplus
};
#endif
#endif



__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/socket/public/snmp/acl.h $ $Rev: 233581 $" )
