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
 * PhSystem.h	
 *		Definition of the Ph_EV_SYSTEM event structure
 *

 */
#ifndef __PhSYSTEM_H_INCLUDED
#define __PhSYSTEM_H_INCLUDED

#include <photon/PhPack.h>

#ifdef __cplusplus
	extern "C" {
#endif

typedef union {
	struct {
		short				zero;
	} Shutdown;
	struct {
		PhConnectId_t		pid;
	} Newmanager;
	struct {
		PhRid_t				rid;		/* Region that is changed */
		PhPoint_t			origin;
		PhRect_t			rect;
		ulong_t				flags;		/* Flags on the region */
		ulong_t				fields;		/* Fields that where modified (~0=open, 0=close, other=change) */
		unsigned short		input_group;
	} RegionChange;
	struct {
		PhPoint_t			p;
	} CON_SwitchAbs;
	struct {
		PhPoint_t			p;
	} CON_SwitchRel;
	struct {
		unsigned short		a;
	} GR_Rotate;
	struct {
		PhPoint_t			res;		/* Try this visual resolution (0,0) to ignore */
		short				diff;		/* -1 zoom in, 0 none, 1 zoom out */
	} GR_Zoom;
	struct {
		PhRid_t				rid;
		PhRect_t			rect;		/* Area bounded by this region */
	} PTR_Region;
	struct {
		short				PressTime;
		short				ReleaseTime;
	} MOUSE_DClick;
	struct {
		short				Threshold;
		short				Power;
	} MOUSE_Accel;
} PhSystemEvent_t;


/*
 * General SYSTEM messages
 */
/*#define Ph_SYSTEM_GENERAL					0x0000 */
#define	Ph_SYSTEM_SHUTDOWN				0x0001
#define	Ph_SYSTEM_NEWMANAGER			0x0002
#define	Ph_SYSTEM_ROTATE				0x0003
#define Ph_SYSTEM_REGION_CHANGE			0x0004

/*
 * Window manager / console messages
 */
/*#define Ph_SYSTEM_CON						0x0100 */
#define	Ph_SYSTEM_CON_SWITCHABS			0x0101
#define	Ph_SYSTEM_CON_SWITCHREL			0x0102

/*
 * Graphics driver system messages
 */
/*#define Ph_SYSTEM_GRAPHIC					0x0200 */
#define	Ph_SYSTEM_GRAPHIC_ROTATE		0x0201
#define	Ph_SYSTEM_GRAPHIC_ZOOM			0x0202

/* #define Ph_SYSTEM_PTR					0x0300 */
#define Ph_SYSTEM_PTR_REGION_CHANGE		0x0301			/* A Graphics region was changed */


/* #define Ph_SYSTEM_MOUSE					0x0340 */
#define	Ph_SYSTEM_MOUSE_DCLICK			0x0341
#define	Ph_SYSTEM_MOUSE_ACCEL			0x0342

/* #define	Ph_SYSTEM_TOUCH					0x360 */

/* #define	Ph_SYSTEM_KEYBOARD				0x380 */
#ifdef __cplusplus
}
#endif

#include <photon/PhPackPop.h>

#endif


#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PhSystem.h $ $Rev: 219996 $" )
#endif
