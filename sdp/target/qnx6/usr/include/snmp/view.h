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






#ifndef _VIEW_H_INCLUDED
#define _VIEW_H_INCLUDED

#ifdef __ASN1_H_INCLUDED
#include <snmp/asn1.h>
#endif

#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif

#ifndef _SNMP_H_INCLUDED
#include <snmp/snmp.h>
#endif

#include <_pack64.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
          viewIndex        INTEGER,                     -- first INDEX
          viewSubtree      OBJECT IDENTIFIER,           -- second INDEX
          viewMask         OCTET STRING
          viewType         INTEGER,
          viewStorageType  StorageType,
          viewStatus       RowStatus,
 */

#define VIEWINDEX	1
#define VIEWSUBTREE	2
#define VIEWMASK	3
#define VIEWTYPE	4
#define VIEWSTORAGETYPE	5
#define VIEWSTATUS	6

#define VIEWNONEXISTENT        0
#define VIEWACTIVE             1
#define VIEWNOTINSERVICE       2
#define VIEWNOTREADY           3
#define VIEWCREATEANDGO        4
#define VIEWCREATEANDWAIT      5
#define VIEWDESTROY            6

#define VIEWINCLUDED	1
#define VIEWEXCLUDED	2

struct viewEntry {
    int		viewIndex;
    char	viewName[64];
    int		viewNameLen;
    oid		viewSubtree[32];
    int		viewSubtreeLen;
    u_char	viewMask[32];
    int		viewMaskLen;
    int		viewType;
    int		viewStorageType;
    int		viewStatus;

    u_long	viewBitMask;

    struct viewEntry *reserved;
    struct viewEntry *next;
};

int read_view_database(const char *filename);
/*
 * Load the view database file
 */

struct viewEntry *
view_getEntry(int viewIndex, oid *viewSubtree ,int viewSubtreeLen );
/*
 * Returns a pointer to the viewEntry with the
 * same viewParty and viewSubtree
 * Returns NULL if that entry does not exist.
 */

void view_scanInit(void);
/*
 * Initialized the scan routines so that they will begin at the
 * beginning of the list of viewEntries.
 *
 */


struct viewEntry *
view_scanNext(void);
/*
 * Returns a pointer to the next viewEntry.
 * These entries are returned in no particular order,
 * but if N entries exist, N calls to view_scanNext() will
 * return all N entries once.
 * Returns NULL if all entries have been returned.
 * view_scanInit() starts the scan over.
 */

struct viewEntry *
view_createEntry(int viewIndex, oid *viewSubtree, int viewSubtreeLen);
/*
 * Creates a viewEntry with the given index
 * and returns a pointer to it.
 * The status of this entry is created as invalid.
 */

void view_destroyEntry( int viewindex, oid *viewSubtree, int viewSubrtreeLen);
/*
 * Free the viewEntry
 */

#include <_packpop.h>

#ifdef __cplusplus 
};
#endif
#endif


__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/socket/public/snmp/view.h $ $Rev: 233581 $" )
