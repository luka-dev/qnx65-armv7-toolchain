/***********************************************************
	Copyright 1989 by Carnegie Mellon University

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
/*
 * snmp_api.h - API for access to snmp.
 */

#ifndef _SNMP_API_H_INCLUDED 
#define _SNMP_API_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif

#ifndef _SNMP_H_INCLUDED
#include <snmp/snmp.h>
#endif

#ifndef _NETINET_IN_H_
#include <netinet/in.h>
#endif

#include <sys/select.h>

#include <_pack64.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sockaddr_in  ipaddr;

struct snmp_session {
    u_char  *community;	/* community for outgoing requests. */
    int	    community_len;  /* Length of community name. */
    int	    retries;	/* Number of retries before timeout. */
    long    timeout;    /* Number of uS until first timeout, then exponential backoff */
    char    *peername;	/* Domain name or dotted IP address of default peer */
    u_short remote_port;/* UDP port number of peer. */
    u_short local_port; /* My UDP port number, 0 for default, picked randomly */
    /* Authentication function or NULL if null authentication is used */
    u_char    *(*authenticator)();
    int	    (*callback)();  /* Function to interpret incoming data */
    /* Pointer to data that the callback function may consider important */
    void    *callback_magic;  
    int	    version;       /*SNMP version session is for SNMP_VERSION_1 or 
                             SNMP_VERSION_2 */ 
    oid	    *srcParty;   /*The source party being used for this session*/  
    int	    srcPartyLen; /*The length fothe source party being used for this 
                           session in number of oid elements eg(.1.3.6 len 3)*/
    oid	    *dstParty;   /*The destination party being used for this session*/
    int	    dstPartyLen; /*The length of the destination party (same as src party
                           format)*/
    oid	    *context;    /*The context being used for this session*/
    int	    contextLen; /*The length of the context (same as srcparty format)*/
};

/*
 * Set fields in session and pdu to the following to get a default or unconfigured value.
 */
#define SNMP_DEFAULT_COMMUNITY_LEN  0	/* to get a default community name */
#define SNMP_DEFAULT_RETRIES	    -1
#define SNMP_DEFAULT_TIMEOUT	    -1
#define SNMP_DEFAULT_REMPORT	    0
#define SNMP_DEFAULT_REQID	    0
#define SNMP_DEFAULT_ERRSTAT	    -1
#define SNMP_DEFAULT_ERRINDEX	    -1
#define SNMP_DEFAULT_ADDRESS	    0
#define SNMP_DEFAULT_PEERNAME	    NULL
#define SNMP_DEFAULT_ENTERPRISE_LENGTH	0
#define SNMP_DEFAULT_TIME	    0
#define SNMP_DEFAULT_VERSION	    -1

extern int snmp_errno;
/* Error return values */
#define SNMPERR_GENERR		-1
#define SNMPERR_BAD_LOCPORT	-2  /* local port was already in use */
#define SNMPERR_BAD_ADDRESS	-3
#define SNMPERR_BAD_SESSION	-4
#define SNMPERR_TOO_LONG	-5

#define non_repeaters	errstat
#define max_repetitions errindex

struct snmp_pdu {
    int	    version;

    ipaddr  address;	/* Address of peer */
    oid	    *srcParty;
    int	    srcPartyLen;
    oid	    *dstParty;
    int	    dstPartyLen;
    oid	    *context;
    int     contextLen;

    u_char  *community;	/* community for outgoing requests. */
    int	    community_len;  /* Length of community name. */

    int	    command;	/* Type of this PDU */

    long  reqid;	/* Request id */
    long  errstat;	/* Error status (non_repeaters in GetBulk) */
    long  errindex;	/* Error index (max_repetitions in GetBulk) */

    /* Trap information */
    oid	    *enterprise;/* System OID */
    int	    enterprise_length;
    ipaddr  agent_addr;	/* address of object generating trap */
    int	    trap_type;	/* trap type */
    int	    specific_type;  /* specific type */
    u_long  time;	/* Uptime */

    struct variable_list *variables;
};


struct variable_list {
    struct variable_list *next_variable;    /* NULL for last variable */
    oid	    *name;  /* Object identifier of variable */
    int	    name_length;    /* number of subid's in name */
    u_char  type;   /* ASN type of variable */
/*    int type;	 */
    union { /* value of variable */
	long	*integer;
	u_char	*string;
	oid	*objid;
	u_char  *bitstring;
	struct counter64 *counter64;
    } val;
    int	    val_len;
};

struct snmpd_conf_data{
   char *main_config_fname;      /*snmpd.conf file location*/
   char *party_conf_fname;       /*party.conf file location*/
   char *view_conf_fname;        /*view.conf file location*/
   char *context_conf_fname;     /*context.conf file location*/
   char *acl_conf_fname;         /*acl.conf file location*/
   char *sysContact;             /*system.sysContact string*/
   char *sysLocation;            /*system.sysLocation string*/
   char *sysName;                /*system.sysName string*/
   char *private_community;      /*private level community string name to use*/
   char *public_community;       /*public level community string name to use*/
   char *trap_sink;              /*destination host to send trap messages*/
   char *trap_community;         /*community name to use for trap messages*/
   int conf_authentraps;         /*enable authentication traps (1 enable 2 disable)*/
};


void init_snmp(void);

/*
 * struct snmp_session *snmp_open(session)
 *	struct snmp_session *session;
 * 
 * Sets up the session with the snmp_session information provided
 * by the user.  Then opens and binds the necessary UDP port.
 * A handle to the created session is returned (this is different than
 * the pointer passed to snmp_open()).  On any error, NULL is returned
 * and snmp_errno is set to the appropriate error code.
 */
struct snmp_session *snmp_open(struct snmp_session *session);

/*
 * int snmp_close(session)
 *     struct snmp_session *session;
 * 
 * Close the input session.  Frees all data allocated for the session,
 * dequeues any pending requests, and closes any sockets allocated for
 * the session.  Returns 0 on error, 1 otherwise.
 */
int snmp_close(struct snmp_session *session);


/*
 * int snmp_send(session, pdu)
 *     struct snmp_session *session;
 *     struct snmp_pdu	*pdu;
 * 
 * Sends the input pdu on the session after calling snmp_build to create
 * a serialized packet.  If necessary, set some of the pdu data from the
 * session defaults.  Add a request corresponding to this pdu to the list
 * of outstanding requests on this session, then send the pdu.
 * Returns the request id of the generated packet if applicable, otherwise 1.
 * On any error, 0 is returned.
 * The pdu is freed by snmp_send() unless a failure occured.
 */
int snmp_send(struct snmp_session *session, struct snmp_pdu *pdu);


/*
 * void snmp_read(fdset)
 *     fd_set  *fdset;
 * 
 * Checks to see if any of the fd's set in the fdset belong to
 * snmp.  Each socket with it's fd set has a packet read from it
 * and snmp_parse is called on the packet received.  The resulting pdu
 * is passed to the callback routine for that session.  If the callback
 * routine returns successfully, the pdu and it's request are deleted.
 */
void snmp_read(fd_set *fdset);


/*
 * void
 * snmp_free_pdu(pdu)
 *     struct snmp_pdu *pdu;
 * 
 * Frees the pdu and any malloc'd data associated with it.
 */
void snmp_free_pdu(struct snmp_pdu *pdu);

/*
 * int snmp_select_info(numfds, fdset, timeout, block)
 * int *numfds;
 * fd_set   *fdset;
 * struct timeval *timeout;
 * int *block;
 *
 * Returns info about what snmp requires from a select statement.
 * numfds is the number of fds in the list that are significant.
 * All file descriptors opened for SNMP are OR'd into the fdset.
 * If activity occurs on any of these file descriptors, snmp_read
 * should be called with that file descriptor set.
 *
 * The timeout is the latest time that SNMP can wait for a timeout.  The
 * select should be done with the minimum time between timeout and any other
 * timeouts necessary.  This should be checked upon each invocation of select.
 * If a timeout is received, snmp_timeout should be called to check if the
 * timeout was for SNMP.  (snmp_timeout is idempotent)
 *
 * Block is 1 if the select is requested to block indefinitely, rather than time out.
 * If block is input as 1, the timeout value will be treated as undefined, but it must
 * be available for setting in snmp_select_info.  On return, if block is true, the value
 * of timeout will be undefined.
 *
 * snmp_select_info returns the number of open sockets.  (i.e. The number of sessions open)
 */
int snmp_select_info(int *numfds, fd_set *fdset, struct timeval *timeout, int *block);

/*
 * void snmp_timeout();
 * 
 * snmp_timeout should be called whenever the timeout from snmp_select_info expires,
 * but it is idempotent, so snmp_timeout can be polled (probably a cpu expensive
 * proposition).  snmp_timeout checks to see if any of the sessions have an
 * outstanding request that has timed out.  If it finds one (or more), and that
 * pdu has more retries available, a new packet is formed from the pdu and is
 * resent.  If there are no more retries available, the callback for the session
 * is used to alert the user of the timeout.
 */
void snmp_timeout(void);


/*
 * This routine must be supplied by the application:
 *
 * u_char *authenticator(pdu, length, community, community_len)
 * u_char *pdu;		The rest of the PDU to be authenticated
 * int *length;		The length of the PDU (updated by the authenticator)
 * u_char *community;	The community name to authenticate under.
 * int	community_len	The length of the community name.
 *
 * Returns the authenticated pdu, or NULL if authentication failed.
 * If null authentication is used, the authenticator in snmp_session can be
 * set to NULL(0).
 */

/*
 * This routine must be supplied by the application:
 *
 * int callback(operation, session, reqid, pdu, magic)
 * int operation;
 * struct snmp_session *session;    The session authenticated under.
 * int reqid;			    The request id of this pdu (0 for TRAP)
 * struct snmp_pdu *pdu;	    The pdu information.
 * void *magic			    A link to the data for this routine.
 *
 * Returns 1 if request was successful, 0 if it should be kept pending.
 * Any data in the pdu must be copied because it will be freed elsewhere.
 * Operations are defined below:
 */

int read_main_config_file(struct snmpd_conf_data *info);
void print_variable(oid *objid, int objidlen, struct variable_list *variable);
void sprint_variable(char *buf, oid *objid, int objidlen, struct variable_list *variable);
void sprint_value(char *buf, oid *objid, int objidlen, struct variable_list *variable);
void print_value(oid *objid, int objidlen, struct variable_list *variable);
int read_objid(char *input, oid *output, int *out_len);
void sprint_objid(char *buf, oid *objid, int objidlen);
void print_objid(oid *objid, int objidlen);
int has_access(u_char msg_type,int target,int subject,int resources);

#define RECEIVED_MESSAGE   1
#define TIMED_OUT	   2

struct snmp_stats
{
 unsigned int in_pkts;
 unsigned int out_pkts;
 unsigned int bd_vers;
 unsigned int bd_comm_names;
 unsigned int bd_comm_uses;
 unsigned int in_asn_par_err;
 unsigned int too_big;
 unsigned int no_s_name;
 unsigned int bd_vals;
 unsigned int in_read_only;
 unsigned int gen_err;
 unsigned int in_tot_req_vars;
 unsigned int tot_set_vars;
 unsigned int in_get_req;
 unsigned int in_get_nxt;
 unsigned int in_set_req;
 unsigned int in_get_resp;
 unsigned int in_trps;
 unsigned int out_too_big;
 unsigned int out_no_s_name;
 unsigned int out_bd_vals;
 unsigned int out_gen_err;
 unsigned int out_get_req;
 unsigned int out_get_nxt;
 unsigned int out_set_req;
 unsigned int out_get_resp;
 unsigned int out_trps;
 int ena_auth_trps;
}; 
 
extern int snmp_dump_packet;

#include <_packpop.h>

#ifdef __cplusplus
};
#endif
#endif


__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/socket/public/snmp/snmp_api.h $ $Rev: 233581 $" )
