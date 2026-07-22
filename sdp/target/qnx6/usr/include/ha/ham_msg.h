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






#ifndef __HAMMSG_H_INCLUDED
#define __HAMMSG_H_INCLUDED

#include <sys/platform.h>
#include <sys/neutrino.h>
#include <inttypes.h>
#include <limits.h>

#define MONITORDEV "/proc/ham"     // where is the monitor
#define HMAXNDSTRLEN 256           // max length of node name 
#define HAMBASICQOS "~loadbalance" // we use load balance as the basic QOS

// a command line in the script
typedef char Actline[_POSIX_PATH_MAX];
// a name
typedef char Hname[_POSIX_PATH_MAX];

struct guardian_connect_info {
	int chid;
	int value;
};

// exchanged between the client ha_lib and the ham

typedef struct __hbeat {
	uint64_t hp;    // period for heartbeat
	int    hpdl;    // missed heartbeats to proclaim death (low mark)
	int    hpdh;    // missed heartbeats to proclaim death (high mark)
	int    chid;    // channel to notify client if guardian takes over
} __Hbeat;    

// Entities are either processes that are already 
// running or things that the HAM starts upon 
// entity creation

// self attached
typedef struct _hentselfmsg {
	Hname path;     // entity name
	pid_t pid;      // attach to this pid
	__Hbeat hb;     // Heart Beat
    // HAT v1_0_0 does not have fields below
	int nd;         // which node are we on, as viewed by the other end
	unsigned flags; // entity flags
} HEntSelfMsg;

// externally attached
typedef struct _hentothermsg {
	Hname path;     // entity name
	pid_t pid;      // pid
	Actline line;   // if pid > 0, dont start it now 
    // HAT v1_0_0 does not have flags field
	unsigned flags; // entity flags
} HEntOtherMsg;

// these entities are created without specifying
// a process to attach to. This allows arbitrary
// orderings for publish/subscribe

typedef struct _hentmsg {
	Hname path;     // entity name
	unsigned flags; // entity flags
} HEntMsg;

// an entity is changing state
// we do not validate state changes, 
// but we enable transition actions
// this triggers a "CONDSTATECHANGE" with 
// the specific entity
typedef struct _hentcondstatemsg {
	Hname path;         // entity name
	pid_t pid;          // pid of entity
	unsigned tostate;   // state transitioning into
	unsigned flags;     // flags
} HEntCondStateMsg;

// a condition is raised about an entity
// could be by the entity itself or by anyone
typedef struct _hentcondraiseemsg {
	Hname path;         // entity name
	pid_t pid;          // pid of entity
	unsigned rtype;     // condition being raised
	unsigned rclass;    // class for condition
	unsigned rseverity; // severity associated with condition
	unsigned flags;     // flags
} HEntCondRaiseMsg;

// a condition message about a state change by an entity
// triggered by a hentstatemsg
typedef struct _hcondstate {
	Hname path;         // entity/condition name
	unsigned fromstate; // old state (from transition)
	unsigned tostate;   // new state (to transition)
	unsigned flags;     // flags
} HCondStateMsg;

#define HCONDSTATEMASK    0x0000F000 // flags associated with cond state
#define HCONDRAISEMASK    0x00000000 // flags associated with cond raise

// a condition message about a condition raised by an entity
// could be by the entity itself or by anyone
// triggered by a hentcondraisemsg
typedef struct _hcondraiseemsg {
	Hname path;         // entity/condition name
	unsigned rtype;     // condition being raised
	unsigned rclass;    // class for condition
	unsigned rseverity; // severity associated with condition
	unsigned flags;     // flags
} HCondRaiseMsg;

// condition message
typedef struct _hcondhmsg {
	Hname path;         // Entity/Condition name
	int type;           // Condition type  
	unsigned flags;     // flags
} HCondMsg;    

typedef struct _hpevent {
	int chid;           // chid to send it to
	int pulsecode;      // pulse code
	int value;          // pulse value
	pid_t pid;          // pid to send it to
    // HAT v1_0_0 does not have nd field
	int nd;             // nd on which pid is resident
                      // this nd is the nd as viewed by the HAM 
                      // for the node this event is being sent to
} HPEvent; 

typedef struct _hsevent {
	int signum;  // signal number
	pid_t pid;   // whom to send the signal to
	int code;    // code 
	int value;   // sig value
    // HAT v1_0_0 does not have nd field
	int nd;      // nd on which pid is resident
               // this nd is the nd as viewed by the HAM 
               // for the node this event is being sent to
} HSEvent;

typedef struct _hwaitfor {
	Hname path;
	int delay;
} HWaitfor;

typedef struct _hactionlog {
	char message[_POSIX_PATH_MAX];
	int verbosity;
	int attachprefix;
} HActionLog;

typedef union __action {
	HPEvent pulse;
	HSEvent signal;
	Actline line;
	HWaitfor waitfor;
	HActionLog log;
} __Action;

// types of actions
#define ACTION_RESTART      1  // special action restart
                               // there can be only one restart action
                               // under a given condition
#define ACTION_EXEC         2  // execute
#define ACTION_NOTIFYPULSE  3  // notify with a pulse
#define ACTION_NOTIFYSIGNAL 4  // notify with a signal
#define ACTION_WAITFOR      5  // Wait for 
#define ACTION_HBEATHEALTHY 6  // Reset HeartBeat state to healthy
#define ACTION_LOG          7  // Insert log message into Ham log stream

// action message
typedef struct _hactmsg {
	Hname path;         // entity/condition/action name
	__Action action;    // action
	int type;           // Action type
	unsigned flags;     // flags
} HActMsg;

// remove action
typedef struct _hactremmsg {
	Hname path;         // Entity/condition/action name
} HActRemMsg;

typedef struct _hactfailmsg {
	Hname path;         // entity/condition/action name
	Hname actfailname;  // name of action fail
	__Action action;    // action
	int type;           // Action type
	unsigned flags;     // flags
	int etype;          // entity type (normal/global)
} HActFailMsg;

// remove action
typedef struct _hactfailremmsg {
	Hname path;        // Entity/condition/action name
	Hname actfailname; // name of action fail
} HActFailRemMsg;

// remove condition
// also removes all actions inside condition
typedef struct _hcondremmsg {
	Hname path;        // Entity/condition name
} HCondRemMsg;

#define ENTITY_ITEM    1 // Item Type: entity
#define CONDITION_ITEM 2 // Item Type: condition
#define ACTION_ITEM    3 // Item Type: action

// activate/deactivate item
typedef struct _hitemstatemsg {
	Hname path;        // which item
	int item_type;     // type of item (entity/condition/action)
	int operation;     // type of operation
	int norecurse;     // will not recurse if set
} HItemStateMsg;

// manage flags
typedef struct _hitemflagsmmsg {
	Hname path;        // which item
	int item_type;     // type of item to which call is made
	int operation;     // type of operation
	unsigned flags;    // this can be travelling either way
} HItemFlagsMsg;

// send verbosity control
typedef struct _hverbositymsg {
	int operation;     // type of operation
	int value;         // value: this could be travelling either way
} HVerbosityMsg;

// Messages exchanged between ham and lib using devctl

#define HAM_TERMINATECODE          0  // terminate
#define HAM_GUARDATTACHCODE        1  // guardian attach 
#define HAM_GUARDDETACHCODE        2  // guardian detach
	                                    //             
#define HAM_ATTACHSELFCODE         3  // attach entity self
#define HAM_ATTACHCODE             4  // attach entity 
#define HAM_DETACHSELFCODE         5  // detach self entity
#define HAM_DETACHCODE             6  // detach entity
#define HAM_REATTACHSELFCODE       7  // re-attach
#define HAM_ADDCONDCODE            8  // Add Condition
#define HAM_REMOVECONDCODE         9  // Remove Condition
#define HAM_ADDACTIONCODE          10 // Add action 
#define HAM_ADDACTIONRESTARTCODE   11 // Special action restart 
#define HAM_REMOVEACTIONCODE       12 // Remove an action
// HAT v1_0_0 everything above
#define HAM_ITEMSTATECODE          13 // Change state of an item
#define HAM_VERBOSITYCODE          14 // verbosity operation
#define HAM_ITEMFLAGSCODE          15 // item flags operation
#define HAM_ADDACTIONFAILCODE      16 // Add action fail
#define HAM_REMOVEACTIONFAILCODE   17 // Remove action fail
#define HAM_ENTITYCODE             18 // new entity (unattached)
#define HAM_ENTITYCONDSTATECODE    19 // entity reports state change
#define HAM_ENTITYCONDRAISECODE    20 // entity raises a condition
#define HAM_ENTITYCONDSTATEPIDCODE 21 // entity reports state change for pid
#define HAM_ENTITYCONDRAISEPIDCODE 22 // entity raises a condition for pid
#define HAM_ADDCONDRAISECODE       23 // Add condition for a condition raise
#define HAM_ADDCONDSTATECODE       24 // Add condition for a state change

// Between ham and guardian
#define DCMD_HAM_GUARDATTACH __DIOT(_DCMD_MISC, HAM_GUARDATTACHCODE, struct guardian_connect_info)
#define DCMD_HAM_GUARDDETACH __DIOT(_DCMD_MISC, HAM_GUARDDETACHCODE, pid_t)
// between client lib and ham
#define DCMD_HAM_ATTACHSELF __DIOT(_DCMD_MISC, HAM_ATTACHSELFCODE, HEntSelfMsg)
#define DCMD_HAM_DETACHSELF __DIOT(_DCMD_MISC, HAM_DETACHSELFCODE, pid_t)
#define DCMD_HAM_ATTACH __DIOT(_DCMD_MISC, HAM_ATTACHCODE, HEntOtherMsg)
#define DCMD_HAM_DETACH __DIOT(_DCMD_MISC, HAM_DETACHCODE, Hname)
#define DCMD_HAM_REATTACHSELF __DIOT(_DCMD_MISC, HAM_REATTACHSELFCODE, pid_t)
#define DCMD_HAM_ADDCOND __DIOT(_DCMD_MISC, HAM_ADDCONDCODE, HCondMsg)
#define DCMD_HAM_REMOVECOND __DIOT(_DCMD_MISC, HAM_REMOVECONDCODE, HCondRemMsg)
#define DCMD_HAM_ADDACTION __DIOT(_DCMD_MISC, HAM_ADDACTIONCODE, HActMsg)
#define DCMD_HAM_ADDACTIONRESTART __DIOT(_DCMD_MISC, HAM_ADDACTIONRESTARTCODE, HActMsg)
#define DCMD_HAM_REMOVEACTION  __DIOT(_DCMD_MISC, HAM_REMOVEACTIONCODE, HActRemMsg)
#define DCMD_HAM_ITEMSTATE __DIOT(_DCMD_MISC, HAM_ITEMSTATECODE, HItemStateMsg)
#define DCMD_HAM_ADDACTIONFAIL __DIOT(_DCMD_MISC, HAM_ADDACTIONFAILCODE, HActFailMsg)
#define DCMD_HAM_REMOVEACTIONFAIL __DIOT(_DCMD_MISC, HAM_REMOVEACTIONFAILCODE, HActFailRemMsg)
// Control mesages
#define DCMD_HAM_TERMINATE  __DIOT(_DCMD_MISC, HAM_TERMINATECODE, pid_t)
#define DCMD_HAM_VERBOSITY __DIOTF(_DCMD_MISC, HAM_VERBOSITYCODE, HVerbosityMsg)
#define DCMD_HAM_ITEMFLAGS __DIOTF(_DCMD_MISC, HAM_ITEMFLAGSCODE, HItemFlagsMsg)
// unattached entity
#define DCMD_HAM_ENTITY __DIOT(_DCMD_MISC, HAM_ENTITYCODE, HEntMsg)
// trigger special conditions
#define DCMD_HAM_ENTITYCONDSTATE __DIOT(_DCMD_MISC, HAM_ENTITYCONDSTATECODE, HEntCondStateMsg)
#define DCMD_HAM_ENTITYCONDRAISE __DIOT(_DCMD_MISC, HAM_ENTITYCONDRAISECODE, HEntCondRaiseMsg)
#define DCMD_HAM_ENTITYCONDSTATEPID __DIOT(_DCMD_MISC, HAM_ENTITYCONDSTATEPIDCODE, HEntCondStateMsg)
#define DCMD_HAM_ENTITYCONDRAISEPID __DIOT(_DCMD_MISC, HAM_ENTITYCONDRAISEPIDCODE, HEntCondRaiseMsg)
// attach to special conditions 
#define DCMD_HAM_ADDCONDSTATE  __DIOT(_DCMD_MISC, HAM_ADDCONDSTATECODE, HCondStateMsg)
#define DCMD_HAM_ADDCONDRAISE  __DIOT(_DCMD_MISC, HAM_ADDCONDRAISECODE, HCondRaiseMsg)

// Ham to client
#define _HAMREATTACHPULSECODE          _PULSE_CODE_MINAVAIL+1 
// client to Ham
#define _HAMHBEATPULSECODE             _PULSE_CODE_MINAVAIL+2    
// death of some daemon in the system
#define _HAMPROCDAEMONDEATHPULSECODE   _PULSE_CODE_MINAVAIL+3       
// hb timer pulse
#define _HAMHBEATTIMERPULSECODE        _PULSE_CODE_MINAVAIL+4 
// Dumper pulse code
#define _HAMDUMPERDEATHCODE            _PULSE_CODE_MINAVAIL+5 
// Pulse to Guardian for Ham death
#define _GUARDIANPROCHAMDEATHPULSECODE _PULSE_CODE_MINAVAIL+6 
// Pulse to Guardian from Ham to kill it
#define _GUARDIANHAMKILLPULSECODE      _PULSE_CODE_MINAVAIL+7 
// HAM to HB Thread to start polling
#define _HAMHBTHREADSTARTPOLL          _PULSE_CODE_MINAVAIL+8 
// Path Event Name Space Pulse 
#define _HAMPATHSPACECODE              _PULSE_CODE_MINAVAIL+9 

#endif
