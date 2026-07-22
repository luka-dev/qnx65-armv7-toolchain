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






#ifndef _PARTY_H_INCLUDED
#define _PARTY_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif

#ifndef _SYS_TIME_H_
#include <sys/time.h>
#endif

#ifndef _ASN1_H_INCLUDED
#include <snmp/asn1.h>
#endif

#include <_pack64.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
    partyIdentity        Party,
    partyIndex           INTEGER,
    partyTDomain         OBJECT IDENTIFIER,
    partyTAddress        TAddress,
    partyMaxMessageSize  INTEGER,
    partyLocal           TruthValue,
    partyAuthProtocol    OBJECT IDENTIFIER,
    partyAuthClock       Clock,
    partyAuthPrivate     OCTET STRING,
    partyAuthPublic      OCTET STRING,
    partyAuthLifetime    INTEGER,
    partyPrivProtocol    OBJECT IDENTIFIER,
    partyPrivPrivate     OCTET STRING,
    partyPrivPublic      OCTET STRING,
    partyStorageType     StorageType,
    partyStatus          RowStatus 
 */

#define PARTYIDENTITY		1
#define PARTYINDEX		2
#define PARTYTDOMAIN		3
#define PARTYTADDRESS		4
#define PARTYMAXMESSAGESIZE	5
#define PARTYLOCAL		6
#define PARTYAUTHPROTOCOL	7
#define PARTYAUTHCLOCK		8
#define PARTYAUTHPRIVATE	9
#define PARTYAUTHPUBLIC		10
#define PARTYAUTHLIFETIME	11
#define PARTYPRIVPROTOCOL	12
#define PARTYPRIVPRIVATE	13
#define PARTYPRIVPUBLIC		14
#define PARTYCLONEFROM          15
#define PARTYSTORAGETYPE	16
#define PARTYSTATUS		17


#define PARTYNONEXISTENT 	0
#define PARTYACTIVE		1
#define PARTYNOTINSERVICE	2
#define PARTYNOTREADY		3
#define PARTYCREATEANDGO	4
#define PARTYCREATEANDWAIT	5
#define PARTYDESTROY		6


#define DOMAINSNMPUDP 1
/* extern oid snmpUdpDomain; */
/* no others defined yet */

#define NOAUTH		1
/* extern oid noAuth[]; */

#define NOPRIV		3
/* extern oid noPriv[]; */
#define DESPRIVPROT	4
/* extern oid dESPrivProt[]; */
#define SNMPV2MD5AUTHPROT  6
/* extern oid snmpv2MD5AuthProt[]; */

struct partyEntry {
    oid		partyIdentity[32];
    int		partyIdentityLen;
    int		partyIndex;
    char	partyName[64];	/* friendly name */
    int		partyTDomain;
    u_char	partyTAddress[16];
    int		partyTAddressLen;
    int		partyMaxMessageSize;
    int		partyLocal;
    int		partyAuthProtocol;
    u_long	partyAuthClock;
    u_long	partyLastTimeStamp;	/* not in MIB */
    long	partyAuthNonce;
    u_char	partyAuthPrivate[16];
    int		partyAuthPrivateLen;
    u_char	partyAuthPublic[32];
    int		partyAuthPublicLen;
    u_long	partyAuthLifetime;
    int		partyPrivProtocol;
    u_char	partyPrivPrivate[16];
    int		partyPrivPrivateLen;
    u_char	partyPrivPublic[32];
    int		partyPrivPublicLen;
    int		partyStorageType;
    int		partyStatus;
    
    u_long	partyBitMask;

    struct partyEntry *reserved;
    struct partyEntry *next;
    struct timeval tv;
};

int read_party_database(const char *filename);
/*
 * Load the party database file
 */

struct partyEntry *
party_getEntry(oid *partyID, int partyIDLen);
/*
 * Returns a pointer to the partyEntry with the
 * same identity as partyID.
 * Returns NULL if that entry does not exist.
 */

void
party_scanInit(void);
/*
 * Initialized the scan routines so that they will begin at the
 * beginning of the list of partyEntries.
 *
 */

struct partyEntry *
party_scanNext(void);
/*
 * Returns a pointer to the next partyEntry.
 * These entries are returned in no particular order,
 * but if N entries exist, N calls to party_scanNext() will
 * return all N entries once.
 * Returns NULL if all entries have been returned.
 * party_scanInit() starts the scan over.
 */

struct partyEntry *
party_createEntry(oid *partyID, int partyIDLen);
/*
 * Creates a partyEntry with the given index
 * and returns a pointer to it.
 * The status of this entry is created as invalid.
 */

void party_destroyEntry(oid *partyID, int partyIDLen);
/*
 * Free the partyEntry
 */

#include <_packpop.h>

#ifdef __cplusplus
};
#endif
#endif



__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/socket/public/snmp/party.h $ $Rev: 233581 $" )
