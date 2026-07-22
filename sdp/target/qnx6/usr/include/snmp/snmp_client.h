/*
 * snmp_client.h
 */
/***********************************************************
	Copyright 1988, 1989 by Carnegie Mellon University

                      All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the name of CMU not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

CMU DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
CMU BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.
******************************************************************/

#ifndef _SNMP_CLIENT_H_INCLUDED
#define _SNMP_CLIENT_H_INCLUDED

#ifndef __ASN1_H_INCLUDED
#include <snmp/asn1.h>
#endif

#ifndef __SNMP_API_H_INCLUDED
#include <snmp/snmp_api.h>
#endif

#include <_pack64.h>

#ifdef __cplusplus
extern "C" {
#endif

struct synch_state {
    int	waiting;
    int status;
/* status codes */
#define STAT_SUCCESS	0
#define STAT_ERROR	1
#define STAT_TIMEOUT 2
    int reqid;
    struct snmp_pdu *pdu;
};

extern struct synch_state snmp_synch_state;

struct snmp_pdu	*
snmp_pdu_create(int command);

struct snmp_pdu *
snmp_fix_pdu(struct snmp_pdu *pdu, int command);

struct snmp_pdu *
snmp_clone_pdu(struct snmp_pdu *pdu);

char *
snmp_errstring(int errstat);

int 
ms_party_init(u_long destaddr, oid *src, int *srclen, oid *dst, int *dstlen, oid *context, int *contextlen);

int 
snmp_synch_response(struct snmp_session *ss, struct snmp_pdu *pdu, struct snmp_pdu **response);

void 
snmp_synch_setup(struct snmp_session *session);

void 
snmp_add_null_var(struct snmp_pdu *pdu, oid *name, int name_length);

#include <_packpop.h>

#ifdef __cplusplus
};
#endif
#endif


__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/socket/public/snmp/snmp_client.h $ $Rev: 233581 $" )
