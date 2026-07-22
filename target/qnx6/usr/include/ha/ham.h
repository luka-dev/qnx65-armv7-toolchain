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





#ifndef _HA_HAM_H_INCLUDED
#define _HA_HAM_H_INCLUDED

#include <sys/platform.h>
#include <sys/neutrino.h>
#include <inttypes.h>
#include <signal.h>

#if defined(__PID_T)
typedef __PID_T     pid_t;
#undef __PID_T
#endif

__BEGIN_DECLS

/* General flags   */
#define HREARMAFTERRESTART 0x00000001  /* retains it across a restart       */

/* Condition Flags */
#define HCONDINDEPENDENT   0x00000002  /* Independent actions in condition  */
#define HCONDNOWAIT        0x00000004  /* No waitfors in this condition     */
#define HCONDOTHER         0x00000008  /* Other condition                   */
#define HCONDKEEPONEMPTY   0x00000010  /* retain if it becomes empty        */

/* special condition flags */
#define HCONDSTATEFROMSET  0x00001000  /* from state is a map               */
#define HCONDSTATETOSET    0x00002000  /* to state is a map                 */
#define HCONDSTATEFROMINV  0x00004000  /* invert from state map             */
#define HCONDSTATETOINV    0x00008000  /* invert to state map               */

/* Action flags    */
#define HACTIONDONOW       0x00000002   /* executes the action now          */
#define HACTIONBREAKONFAIL 0x00000004   /* break out of action list         */
#define HACTIONKEEPONFAIL  0x00000008   /* retain an action if it fails     */

/* Entity Flags    */
#define HENTITYKEEPONDEATH 0x00000002   /* un-attached entities stay        */

/* Flags from 0x00000001 to 0x00088888 are above */

/* Common Flags */
#define HRECURSE           0x00100000   /* apply rule recursively           */

#define HAMHBEATMIN        1000000000UL /* minimum hb interval (1000 msec)  */

struct __ham_lib_handle;
typedef struct __ham_lib_handle ham_entity_t;    /* handle to entity    */
typedef struct __ham_lib_handle ham_condition_t; /* handle to condition */
typedef struct __ham_lib_handle ham_action_t;    /* handle to action    */

/* Basic connect functions                           */
/* returns success(0) or failure(-1, with errno set) */
int ham_connect(unsigned __flags);
int ham_disconnect(unsigned __flags);
int ham_connect_nd(int __nd, unsigned __flags);
int ham_disconnect_nd(int __nd, unsigned __flags);
int ham_connect_node(const char *__nodename, unsigned __flags);
int ham_disconnect_node(const char *__nodename, unsigned __flags);

/* Get/Free handles    */
ham_entity_t *ham_entity_handle(int __nd, __const char *__ename, unsigned __flags);
ham_condition_t *ham_condition_handle(int __nd, __const char *__ename, __const char *__cname, unsigned __flags);
ham_action_t *ham_action_handle(int __nd, __const char *__ename, __const char *__cname, __const char *__aname, unsigned __flags);
ham_entity_t *ham_entity_handle_node(const char *__nodename, __const char *__ename, unsigned __flags);
ham_condition_t *ham_condition_handle_node(const char * __nodename, __const char *__ename, __const char *__cname, unsigned __flags);
ham_action_t *ham_action_handle_node(const char * __nodename, __const char *__ename, __const char *__cname, __const char *__aname, unsigned __flags);
int ham_entity_handle_free(ham_entity_t *__ehdl);
int ham_condition_handle_free(ham_condition_t *__chdl);
int ham_action_handle_free(ham_action_t *__ahdl);

/* Ham Functions       */
ham_entity_t *ham_attach_self(__const char *__ename, uint64_t __hp, int __hpdl, int __hpdh, unsigned __flags);
ham_entity_t *ham_attach(__const char *__ename, int __nd, pid_t __pid, __const char *__line, unsigned __flags);
ham_entity_t *ham_attach_node(__const char *__ename, const char * __nodename, pid_t __pid, __const char *__line, unsigned __flags);
int ham_detach_self(ham_entity_t *__ehdl, unsigned __flags);
int ham_detach(ham_entity_t *__ehdl, unsigned __flags);
int ham_detach_name(int __nd, __const char *__ename, unsigned __flags);
int ham_detach_name_node(const char  *__nodename, __const char *__ename, unsigned __flags);
ham_entity_t *ham_entity_node(const char *__ename, const char *__nodename, unsigned __flags);
ham_entity_t *ham_entity(const char *__ename, int __nd, unsigned __flags);

/* types of conditions */
/* cond types CONDSTATE and CONDRAISE are special 
   condition types, that are not used with the 
   ham_condition call, instead they will use 
   specialised ham_condition_* calls since they 
   associate extra data items with the condition */
#define CONDANY             0  /* any condition                         */
#define CONDDEATH           1  /* entity died                           */
#define CONDDETACH          2  /* entity detach                         */
#define CONDRESTART         3  /* entity restarted                      */
#define CONDHBEATMISSEDLOW  4  /* entity missed heartbeat severity low  */
#define CONDHBEATMISSEDHIGH 5  /* entity missed heartbeat severity high */
#define CONDABNORMALDEATH   6  /* something died abnormally (dumper)    */
#define CONDATTACH          7  /* entity joins                          */
#define CONDSTATE           8  /* entity reports state change           */
#define CONDRAISE           9  /* condition raised by entity            */
#define CONDMIN CONDANY        /* lowest condition value                */
#define CONDMAX CONDRAISE      /* highest condition value               */

/* special condition types */
#define CONDSTATEANY         0x00000000 /* ANY state                       */
#define CONDRAISETYPEANY     0x00000000 /* ANY type     : raised condition */
#define CONDRAISECLASSANY    0x00000000 /* ANY class    : raised condition */
#define CONDRAISESEVERITYANY 0x00000000 /* ANY severity : raised condition */

/* attach to a condition         */
ham_condition_t *ham_condition(ham_entity_t *__ehdl, int __type, __const char *__cname, unsigned __flags);
/* attach to a special condition */
ham_condition_t *ham_condition_state(ham_entity_t *__ehdl, __const char *__cname, unsigned __fromstate, unsigned __tostate, unsigned __flags);
ham_condition_t *ham_condition_raise(ham_entity_t *__ehdl, __const char *__cname, unsigned __Rtype, unsigned __Rclass, unsigned __Rseverity, unsigned __flags);
/* remove a condition            */
int ham_condition_remove(ham_condition_t *__chdl, unsigned __flags);

/* action operations             */
ham_action_t *ham_action_restart(ham_condition_t *__chdl, __const char *__aname, __const char *__path, unsigned __flags);
ham_action_t *ham_action_execute(ham_condition_t *__chdl, __const char *__aname, __const char *__path, unsigned __flags);
ham_action_t *ham_action_waitfor(ham_condition_t *__chdl, __const char *__aname, __const char *__path, int __delay, unsigned __flags);
ham_action_t *ham_action_notify_pulse(ham_condition_t *__chdl, __const char *__aname, int __nd, int __topid, int __chid, int __pulsecode, int __value, unsigned __flags);
ham_action_t *ham_action_notify_signal(ham_condition_t *__chdl, __const char *__aname, int __nd, pid_t __topid, int __signum, int __code, int __value, unsigned __flags);
ham_action_t *ham_action_notify_pulse_node(ham_condition_t *__chdl, __const char *__aname, const char *__nodename, int __topid, int __chid, int __pulsecode, int __value, unsigned __flags);
ham_action_t *ham_action_notify_signal_node(ham_condition_t *__chdl, __const char *__aname, const char *__nodename, pid_t __topid, int __signum, int __code, int __value, unsigned __flags);
ham_action_t *ham_action_heartbeat_healthy(ham_condition_t *__chdl, __const char *__aname, unsigned __flags);
ham_action_t *ham_action_log(ham_condition_t *__chdl, __const char *__aname, __const char *__msg, unsigned __attachprefix, int __verbosity, unsigned __flags);

/* remove an action              */
int ham_action_remove(ham_action_t *__ahdl, unsigned __flags);

/* terminate                     */
int ham_stop(void);
int ham_stop_nd(int __nd);
int ham_stop_node(const char *__nodename);
int ham_heartbeat(void);
/* trigger a special condition   */
int ham_entity_condition_state(ham_entity_t *__ehdl, unsigned __tostate, unsigned __flags);
int ham_entity_condition_raise(ham_entity_t *__ehdl, unsigned __Rtype, unsigned __Rclass, unsigned __Rseverity, unsigned __flags);

/* verbosity operations          */
#define VERBOSE_SET_INCR 1  /* increment verbosity              */
#define VERBOSE_SET_DECR 2  /* decrement verbosity              */
#define VERBOSE_SET      3  /* set verbosity (specific value)   */
#define VERBOSE_GET      4  /* get verbosity                    */
	
/* Control Commands */
#define HENABLE         1  /* enable item                           */
#define HDISABLE        2  /* disable item                          */
#define HADDFLAGS       3  /* add flag                              */
#define HREMOVEFLAGS    4  /* remove flag                           */
#define HSETFLAGS       5  /* set flag to specific                  */
#define HGETFLAGS       6  /* get flag                              */

int ham_verbose(const char *__nodename, int __command, int __value);

/* control operations              */
int ham_entity_control(ham_entity_t *__ehdl, int __command, unsigned __flags);
int ham_condition_control(ham_condition_t *__chdl, int __command, unsigned __flags);
int ham_action_control(ham_action_t *__ahdl, int __command, unsigned __flags);

/* action fail operations          */
int ham_action_fail_execute(ham_action_t *__ahdl, __const char *__aname, __const char *__path, unsigned __flags);
int ham_action_fail_waitfor(ham_action_t *__ahdl, __const char *__aname, __const char *__path, int __delay, unsigned __flags);
int ham_action_fail_notify_pulse(ham_action_t *__ahdl, __const char *__aname, int __nd, int __topid, int __chid, int __pulsecode, int __value, unsigned __flags);
int ham_action_fail_notify_signal(ham_action_t *__ahdl, __const char *__aname, int __nd, pid_t __topid, int __signum, int __code, int __value, unsigned __flags);
int ham_action_fail_notify_pulse_node(ham_action_t *__ahdl, __const char *__aname, __const char *__nodename, int __topid, int __chid, int __pulsecode, int __value, unsigned __flags);
int ham_action_fail_notify_signal_node(ham_action_t *__ahdl, __const char *__aname, __const char *__nodename, pid_t __topid, int __signum, int __code, int __value, unsigned __flags);
int ham_action_fail_log(ham_action_t *__ahdl, __const char *__aname, __const char *__message, unsigned __attachprefix, int __verbosity, unsigned __flags);

/* remove an action fail operation */
int ham_action_fail_remove(ham_action_t *__ahdl, __const char *__aname, unsigned __flags);

__END_DECLS

#endif

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/services/ham/public/ha/ham.h $ $Rev: 219613 $" )
