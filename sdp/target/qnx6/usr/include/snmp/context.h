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






#ifndef _CONTEXT_H_INCLUDED
#define _CONTEXT_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif

#ifndef _SNMP_H_INCLUDED
#include <snmp/snmp.h>
#endif

#ifndef _SYS_TIME_H_
#include <sys/time.h>
#endif

#include <_pack64.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
    contextIdentity         Context,
    contextIndex            INTEGER,
    contextViewIndex        INTEGER,
    contextLocalEntity      OCTET STRING,
    contextLocalTime        OBJECT IDENTIFIER,
    contextDstPartyIndex    INTEGER,
    contextSrcPartyIndex    INTEGER,
    contextProxyContext     OBJECT IDENTIFIER
    contextStorageType      StorageType,
    contextStatus           RowStatus
 */

#define CONTEXTIDENTITY         1
#define CONTEXTINDEX            2
#define CONTEXTLOCAL		3
#define CONTEXTVIEWINDEX        4
#define CONTEXTLOCALENTITY      5
#define CONTEXTLOCALTIME        6
#define CONTEXTDSTPARTYINDEX    7
#define CONTEXTSRCPARTYINDEX    8
#define CONTEXTPROXYCONTEXT     9
#define CONTEXTSTORAGETYPE      10
#define CONTEXTSTATUS           11

#define CONTEXTNONEXISTENT 	0
#define CONTEXTACTIVE		1
#define CONTEXTNOTINSERVICE	2
#define CONTEXTNOTREADY		3
#define CONTEXTCREATEANDGO	4
#define CONTEXTCREATEANDWAIT	5
#define CONTEXTDESTROY		6


#define CURRENTTIME	1
#define RESTARTTIME	2
#define CACHETIME	3	/* not implemented */

struct contextEntry {
    oid		contextIdentity[32];
    int		contextIdentityLen;
    int		contextIndex;
    char	contextName[64];	/* friendly name */
    int		contextLocal;
    int		contextViewIndex;
    u_char	contextLocalEntity[64];
    int		contextLocalEntityLen;
    int		contextLocalTime;
    int		contextDstPartyIndex;
    int		contextSrcPartyIndex;
    oid		contextProxyContext[32];
    int		contextProxyContextLen;
    int		contextStorageType;
    int		contextStatus;
    
    u_long	contextBitMask;

    struct contextEntry *reserved;
    struct contextEntry *next;
    struct timeval tv;
};

int read_context_database(const char *filename);
/*
 * Load the context database file
 */

struct contextEntry *
context_getEntry(oid *contextID, int contextIDLen);
/*
 * Returns a pointer to the contextEntry with the
 * same identity as contextID.
 * Returns NULL if that entry does not exist.
 */

void context_scanInit(void);
/*
 * Initialized the scan routines so that they will begin at the
 * beginning of the list of contextEntries.
 *
 */


struct contextEntry *
context_scanNext(void);
/*
 * Returns a pointer to the next contextEntry.
 * These entries are returned in no particular order,
 * but if N entries exist, N calls to context_scanNext() will
 * return all N entries once.
 * Returns NULL if all entries have been returned.
 * context_scanInit() starts the scan over.
 */

struct contextEntry *
context_createEntry(oid *contextID, int contextIDLen);
/*
 * Creates a contextEntry with the given index
 * and returns a pointer to it.
 * The status of this entry is created as invalid.
 */

void context_destroyEntry(oid *contextID, int contextIDLen);
/*
 * Free the contextEntry
 */

#include <_packpop.h>

#ifdef __cplusplus
};
#endif
#endif


__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/socket/public/snmp/context.h $ $Rev: 233581 $" )
