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
 *	PtTty.h
 *		Header file for the PtTty widget class
 *

 */
#ifndef __PT_TTY_H_INCLUDED
#define __PT_TTY_H_INCLUDED

#ifndef __PT_TERMINAL_H_INCLUDED
#include <photon/PtTerm.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtTty public
 */

extern PtWidgetClassRef_t *const PtTty;


/*
 * Functions
 */

extern const char *PtTtyShell( void );

/* Resources */
#define Pt_TTY_RESOURCE( n ) Pt_RESOURCE( 51, n )

#define Pt_ARG_TTY_FDS				Pt_TTY_RESOURCE(  0 )
#define Pt_ARG_TTY_RFD				Pt_TTY_RESOURCE(  1 )
#define Pt_ARG_TTY_PATH				Pt_TTY_RESOURCE(  2 )
#define Pt_ARG_TTY_PSEUDO			Pt_TTY_RESOURCE(  3 )
#define Pt_ARG_TTY_INPUT			Pt_TTY_RESOURCE(  4 )
#define Pt_ARG_TTY_PRI				Pt_TTY_RESOURCE(  5 )
#define Pt_ARG_TTY_FLAGS			Pt_TTY_RESOURCE(  6 )
#define Pt_ARG_TTY_DEVSIZE			Pt_TTY_RESOURCE(  7 )
#define Pt_ARG_TTY_BUFLEN			Pt_TTY_RESOURCE(  8 )
#define Pt_ARG_TTY_BUFFER			Pt_TTY_RESOURCE(  9 )
#define Pt_ARG_TTY_CMD				Pt_TTY_RESOURCE( 12 )
#define Pt_ARG_TTY_ARGV				Pt_TTY_RESOURCE( 13 )
#define Pt_ARG_TTY_PID				Pt_TTY_RESOURCE( 14 )
#define Pt_ARG_TTY_EXIT_STATUS		Pt_TTY_RESOURCE( 15 )
#define Pt_ARG_TTY_FDSET			Pt_TTY_RESOURCE( 16 )
#define Pt_ARG_TTY_SPAWN_OPTIONS	Pt_TTY_RESOURCE( 19 )
#define Pt_ARG_TTY_INPUT_WRITTEN	Pt_TTY_RESOURCE( 20 )
#define Pt_ARG_TTY_WFD				Pt_TTY_RESOURCE( 21 )
#define Pt_ARG_TTY_SFD				Pt_TTY_RESOURCE( 22 )

/*
 *	Callbacks
 */
#define Pt_CB_TTY_OUTPUT		Pt_TTY_RESOURCE( 10 )
#define Pt_CB_TTY_DEVSIZE		Pt_TTY_RESOURCE( 11 )
#define Pt_CB_TTY_TERMINATED	Pt_TTY_RESOURCE( 18 )

/*
 *	Callback data structures
 */

typedef struct Pt_tty_output {
	int length;
	const char *buffer;
	}
		PtTtyOutput_t;


/*
 *	Flag values for thr Pt_ARG_TTY_FLAGS resource
 */

#define Pt_TTY_TERMRESIZE	0x0001
#define Pt_TTY_DEVRESIZE	0x0002
#define Pt_TTY_DEVLIMIT		0x0004
#define Pt_TTY_DEVFORCE		0x0008
#define Pt_TTY_SETENV		0x0040
#define Pt_TTY_ARGV0		0x0080
#define Pt_TTY_BUF_PRIVATE	0x0010

extern const PtSpawnOptions_t PtTtyDefaultSpawnOptions;

typedef PtSpawnOptions_t PtTtySpawnOptions_t;

/*
 * PtTty private
 */

/* Base widget classes union */
typedef union Pt_tty_base {
	PtWidget_t			core;
	PtBasicWidget_t		basic;
	PtContainerWidget_t	cntr;
	PtTerminalWidget_t	term;
	}
		PtTtyBase_t;

/* Widget structure */
typedef struct Pt_tty_widget {
	PtTtyBase_t	base;					/* Base class object */

					/* The resources: */
	char *path;							/* Pt_ARG_TTY_PATH */
	int rfd;							/* Pt_ARG_TTY_RFD */
	int wfd;							/* Pt_ARG_TTY_WFD */
	int sfd;							/* Pt_ARG_TTY_SFD */
	int pri;							/* Pt_ARG_TTY_PRI */
	unsigned short flags;				/* Pt_ARG_TTY_FLAGS */
	unsigned short fdset;				/* Pt_ARG_TTY_FDSET */
	PtTerminalRowCol_t dsize;			/* Pt_ARG_DEV_SIZE */
	pid_t pid;							/* Pt_ARG_TTY_PID */
	int xstat;							/* Pt_ARG_TTY_EXIT_STATUS */
	void *buffer;						/* Pt_ARG_TTY_BUFFER */
	PtTtySpawnOptions_t const *opts;	/* Pt_ARG_TTY_SPAWN_OPTIONS */
	unsigned short blen;				/* Pt_ARG_TTY_BUFLEN */
	unsigned short written;				/* Pt_ARG_TTY_INPUT_WRITTEN */

					/* Private parts: */
	unsigned llen, loff;
	char *lbuf;
	PtSpawnCbId_t *scb;
	}
		PtTtyWidget_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif /* __PT_TTY_H_INCLUDED */

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtTty.h $ $Rev: 219996 $" )
#endif
