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



#ifndef _PX_HELP_INCLUDED
#define _PX_HELP_INCLUDED

/* PxHelp.h
 * Photon Help System
 * Aug 95


 */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Defines
 */

#define HELPMSG	0xbeef
#define HELPMSG_SUBTYPE_ERROR	0x0
#define HELPMSG_SUBTYPE_OK	0x1
#define HELPMSG_SUBTYPE_URL	0x2
#define HELPMSG_SUBTYPE_TOC	0x3
#define HELPMSG_SUBTYPE_TREE 	0x4
#define HELPMSG_SUBTYPE_QUIT 	0x5
#define HELPMSG_SUBTYPE_SEARCH 	0x6

#define HELPCMD "helpviewer"
#define HELPPATH "/usr/photon/bin/helpviewer"
/*#define HELPPATH "/src/photon/helpviewer1.1/helpviewer/src/default/helpviewer" */
#define HELPROOT "/usr/help/product/"
#define MSGSIZE sizeof( HelpMsg )
#define MSG2SIZE sizeof( HelpMsg2 )

#define HELP_SEARCH_MODE_TITLE		0
#define HELP_SEARCH_MODE_TEXT		1
#define HELP_SEARCH_MODE_DISPLAYED	2

#define HELP_SEARCH_SCOPE_ALL		0
#define HELP_SEARCH_SCOPE_SELECTED	1

#define HELP_SEARCH_METHOD_EXACT	0
#define HELP_SEARCH_METHOD_WORD		1
#define HELP_SEARCH_METHOD_SUBSTRING	2
#define HELP_SEARCH_METHOD_SUBSTRING_CASE	3

/*
 * Structures
 */
#ifndef _PT_HELP_INCLUDED

typedef struct
{
	unsigned short type;
	unsigned short subtype;
	char string[1];
} HelpMsg;

typedef struct
{
	unsigned short type;
	unsigned short subtype;
	int arg1;
	int arg2;
	int arg3;
	char string[1];
} HelpMsg2;

#endif

/*
 * Globals
 */

/*
 * Prototypes
 */

extern void PxHelpQuit( void );
extern int PxHelpUrl( char * url  );
extern void PxHelpUrlRoot( char * url );
extern int PxHelpTopic( char * topic );
extern void PxHelpTopicRoot( char * topic );
extern int PxHelpTopicTree( char * path );
extern int PxHelpSearch( char * string, int mode, int scope, int method );

#ifdef __cplusplus
};
#endif
#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/phexlib/public/photon/PxHelp.h $ $Rev: 219996 $" )
#endif
