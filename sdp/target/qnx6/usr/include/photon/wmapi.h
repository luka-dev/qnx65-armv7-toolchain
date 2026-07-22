/* Copyright 2009, QNX Software Systems. All Rights Reserved.
 * 
 * You must obtain a written license from and pay applicable license fees to 
 * QNX Software Systems before you may reproduce, modify or distribute this 
 * software, or any work that includes all or part of this software.  Free 
 * development licenses are available for evaluation and non-commercial purposes.  
 * For more information visit http://licensing.qnx.com or email licensing@qnx.com.
 * 
 * This file may contain contributions from others.  Please review this entire 
 * file for other proprietary rights or license notices, as well as the QNX 
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 */
/* 
 * wmapi.h
 *
 * Function prototypes for Window Manager Control api
 *
 */

#if !defined(__WmAPI_H__)
#define __WmAPI_H__
#ifdef __cplusplus
extern "C" {
#endif

#include <photon/PhT.h>
#include <photon/WmMsg.h>
#include <photon/WmReply.h>
#include <photon/WmNotify.h>

typedef struct Wm_context * WmApiContext_t;
typedef void WmCallbackF_t( WmApiContext_t, unsigned long, WmNotify_t const *, void * );

/* Menu display location */
#define MENU_POINT_UL 					1
#define MENU_POINT_UR 					2
#define MENU_POINT_LL 					3
#define MENU_POINT_LR 					4

/* Screen reserve location */
#define WM_RESERVE_LEFT					1
#define WM_RESERVE_RIGHT				2
#define WM_RESERVE_TOP					3
#define WM_RESERVE_BOT					4

/* Win action actions */
#define Pt_ACTION_CLOSE                 1
#define Pt_ACTION_MAX                   2
#define Pt_ACTION_MIN                   3
#define Pt_ACTION_HELP                  4
#define Pt_ACTION_RET                   5
#define Pt_ACTION_MENU                  6
#define Pt_ACTION_MOVE                  7
#define Pt_ACTION_MOVE_COMPLETE 		8
#define Pt_ACTION_MOVE_INIT             9
#define Pt_ACTION_COLLAPSE              10


WmApiContext_t WmCreateContext (void);
int WmDestroyContext (WmApiContext_t);
int WmGetFrameSize (WmApiContext_t, const PhRid_t, PhRect_t *);
int WmDisplayWindowMenu (WmApiContext_t, const PhRid_t, const int, const PhPoint_t *);
int WmPerformFrameAction  (WmApiContext_t, const PhRid_t, const int);
int WmGetCurWindow (WmApiContext_t, WmWindowDefinition_t *);
int WmSetCurWindow (WmApiContext_t, const PhRid_t);
int WmSetCurConsole (WmApiContext_t, const int, const unsigned long);
int WmGetCurConsole (WmApiContext_t, int *);
int WmAddWinMenuEntry (WmApiContext_t, const char*, const int, const char*, const char*);
int WmSetConnectionEventMask (WmApiContext_t, unsigned );
int WmSetScreenReserve (WmApiContext_t, const int, const int, PhArea_t *);
int WmSetScreenReserveAll (WmApiContext_t, PhRect_t const *, PhRect_t *);
int WmCancelScreenReserve (WmApiContext_t, const int);
int WmGetFocusList (WmApiContext_t, const int, int *, WmWindowDefinition_t **);

int WmSetCallback (WmApiContext_t context, unsigned mask, WmCallbackF_t *cb, void *cbdata );

#ifdef __cplusplus
}
#endif
#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/wmapi.h $ $Rev: 224590 $" )
#endif
