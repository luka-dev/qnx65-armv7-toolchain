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



#ifndef __PT_PROTO_H_INCLUDED
#define __PT_PROTO_H_INCLUDED

/****************************************************************************
 *
 * PtProto.h	
 *		Prototypes for the Photon widget (Pt) library
 *

 *
 ****************************************************************************/


#ifndef __PT_T_H_INCLUDED
#include <photon/PtT.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

extern PtWidgetClassStyle_t * PtCreateClassStyle (char *name);
extern int PtSetStyleMembers ( PtWidgetClassStyle_t *style, ... );

extern PtChannelEventHandlerId_t *PtAddChannelEventHandler(
	unsigned long evmask, PtChannelEventHandlerF_t *fun, void *data
	);
extern void PtRemoveChannelEventHandler( PtChannelEventHandlerId_t *id );
extern void PtChannelEventHandler(PhChannelEv_t const *);

const char *PtAllocFontName( const char *name );
void PtFreeFontName( const char *name );
const char *PtRefFontName( const char *name );

#define	PtGiveFocus(w,e)	PtContainerGiveFocus( w, e )
extern PtWidget_t *PtGetParentWidget( void );
extern void PtImmortalizeWidget( PtWidget_t *widget );
extern int PtMortalizeWidget( PtWidget_t *widget );
extern int PtQuitMainLoop( void );
extern void PtPreventExit( void );
extern void PtAllowExit( void );
extern void PtExit( int );

extern void PtLoadWinFrameStyle ( char *style_dll );

/*
April 2000
*/

extern PtWidgetClassStyle_t *PtDupClassStyle (PtWidgetClassRef_t *wclass, char const *style_name, char const *new_name);
extern int PtAddClassStyle (PtWidgetClassRef_t * const ref, PtWidgetClassStyle_t * style);
extern PtWidgetClassStyle_t *PtFindClassStyle (PtWidgetClassRef_t *ref, char *style_name);
extern PtWidgetClassStyle_t *PtGetWidgetStyle (PtWidget_t *widget);
extern int PtSetWidgetStyle( PtWidget_t *widget, char *style_name );
extern int PtSetClassStyleMethods( PtWidgetClassStyle_t *style, int num_methods, PtStyleMethods_t *meth_array );
extern void *PtModalBlock( PtModalCtrl_t *ctrl, unsigned flags );
extern int PtModalUnblock( PtModalCtrl_t *ctrl, void *result );

/*
 March 2000
*/

extern void PtAddCallback( PtWidget_t *widget,	unsigned long cb_type,	int (*func) (PtWidget_t *, void *, PtCallbackInfo_t *),	void *data );
extern void PtAddCallbacks( PtWidget_t *widget, unsigned long cb_type, PtCallback_t const *cb_defs, unsigned int num);
extern void PtRemoveCallback( PtWidget_t *widget, unsigned long cb_type, int (*func)(PtWidget_t *, void *, PtCallbackInfo_t *), void *data );
extern void PtRemoveCallbacks( PtWidget_t *widget, unsigned long cb_type, PtCallback_t const *cblist, unsigned int num);
extern void PtAddEventHandler( PtWidget_t *widget, unsigned long event_mask, int (*func) (PtWidget_t *, void *, PtCallbackInfo_t *), void *data );
extern void PtAddEventHandlers( PtWidget_t *widget, PtRawCallback_t const *cblist, unsigned int num);
extern void PtRemoveEventHandler( PtWidget_t *widget, unsigned long event_mask, int (*func) (PtWidget_t *, void *, PtCallbackInfo_t *), void *data );
extern void PtRemoveEventHandlers( PtWidget_t *widget, PtRawCallback_t const *cblist, int num);
extern void PtAddFilterCallback( PtWidget_t *widget, unsigned long event_mask, int (*func) (PtWidget_t *, void *, PtCallbackInfo_t *),	void *data );
extern void PtAddFilterCallbacks( PtWidget_t *widget, PtRawCallback_t const *cblist, unsigned int num);
extern void PtRemoveFilterCallback( PtWidget_t *widget, unsigned long event_mask,int (*func) (PtWidget_t *, void *, PtCallbackInfo_t *), void *data );
extern void PtRemoveFilterCallbacks( PtWidget_t *widget, PtRawCallback_t const *cblist, int num);
extern void PtAddHotkeyHandler( PtWidget_t *widget, unsigned key_sym_cap, unsigned key_mods, short flags, void *data, int (*event_f) ( PtWidget_t *, void *, PtCallbackInfo_t * ));
extern void PtRemoveHotkeyHandler(	PtWidget_t *widget, unsigned key_sym_cap, unsigned key_mods, short flags, void *data, int (*event_f)( PtWidget_t *, void *, PtCallbackInfo_t * ));
extern int PtGetControlFlags(void);
extern void PtWidgetCheckAdjustDim( PtWidget_t *widget, PhDim_t *dim );
unsigned long PtResizeFlags( PtWidget_t *widget, const PhDim_t *hint );
extern void PtCalcWidgetDim( PtWidget_t *widget, const PhDim_t *hint, const PhDim_t *internal_dim, PhDim_t *dim );
extern PhArea_t *PtSetWidgetArea( PtWidget_t *widget, const PhPoint_t *pos, const PhDim_t *dim );
void PtGetPreferredDim( PtWidget_t *widget, unsigned short width, unsigned short height, PhDim_t *dim );

/*
 February 2000
*/
extern int PtEnter( int flags );
extern int PtLeave( int flags );
#if defined(__QNXNTO__)
	extern int PtCondWait( pthread_cond_t *cond );
	extern int PtCondTimedWait( pthread_cond_t *cond, const struct timespec *abstime );
#endif
extern PtWidget_t *PtWidgetOwner( PtWidget_t *widget);
extern PtBlockedList_t *PtBlockAllWindows( PtWidget_t *skip, unsigned short cursor, PgColor_t cursor_color );
extern PtBlockedList_t *PtBlockWindow( PtWidget_t *skip, unsigned short cursor, PgColor_t cursor_color );
extern void PtUnblockWindows( PtBlockedList_t * );
extern void PtMakeModal( PtWidget_t *widget, unsigned short cursor, PgColor_t cursor_color );


/*
 January 2000
*/
extern void PtInvalidateAnchors ( PtWidget_t *widget );
extern void PtConstrainWidget( PtWidget_t *widget );

/*
	October 1999
*/

extern const char *PtMenuGetShortcutFont(void);
extern void PtMenuSetShortcutFont(const char *font);
extern const char *PtMenuGetKeyName(unsigned long key);
extern int PtMenuSetKeyName(unsigned long key, const char *name);


/*
	June 1999
*/
extern int PtGetAnchoredArea(PtWidget_t const *, PhArea_t *, int unsigned cflags );
extern void PtSuperClassCalcOpaque( PtWidgetClassRef_t *cref, PtWidget_t *widget );
extern int PtSuperClassLostFocus( PtWidgetClassRef_t *cref, PtWidget_t *widget, PhEvent_t *event );
extern void PtSuperClassGotFocus( PtWidgetClassRef_t *cref, PtWidget_t *widget, PhEvent_t *event );
extern int	PtCheckIntersection( PhRect_t const * const r1, PhRect_t const * const r2 );


/* Control surface API */

extern int PtSurfaceTestPoint(PtSurface_t *surface,PhPoint_t const *point);
extern PtSurface_t *PtSurfaceHit(PtWidget_t *widget,PhPoint_t const *point,ulong_t event_mask,PtSurface_t *surface);
extern PhRect_t *PtSurfaceCalcBoundingBox(PtSurface_t *surface);
extern PhRect_t *PtSurfaceCalcBoundingBoxById(PtWidget_t *widget,PtSurfaceId_t surface_id);
extern PhRect_t *PtSurfaceExtent(PtWidget_t *widget,PtSurface_t *surface,PhRect_t *extent);
extern PhRect_t *PtSurfaceExtentById(PtWidget_t *widget,PtSurfaceId_t surface_id,PhRect_t *extent);
extern PtSurface_t *PtCreateActionSurface(
  PtWidget_t *widget,
  PtSurfaceId_t surface_id,
  PtWidgetClassRef_t const *cref,
  ushort_t compound_action_id,
  ushort_t flags,
  ushort_t npoints,
  PhPoint_t *points,
  PtSurfaceDraw_f draw_f,
  PtSurfaceCalc_f calc_points_f );
extern PtSurface_t *PtCreateSurface(
  PtWidget_t *widget,
  PtSurfaceId_t surface_id,
  ushort_t flags,
  ushort_t npoints,
  PhPoint_t *points,
  long event_mask,
  PtSurfaceCallback_f event_f,
  PtSurfaceDraw_f draw_f,
  PtSurfaceCalc_f calc_points_f );
extern PtSurface_t *PtFindSurface(PtWidget_t *widget,PtSurfaceId_t surface_id);
extern PtSurface_t *PtFindSurfaceByAction(PtWidget_t *widget,PtWidgetClassRef_t const *cref,ushort_t action_id,PtSurface_t *surface);
extern void PtDestroySurface(PtWidget_t *widget,PtSurface_t *surface);
extern int PtDestroySurfaceById(PtWidget_t *widget,PtSurfaceId_t surface_id);
extern void PtDestroyAllSurfaces(PtWidget_t *widget);
extern int PtInsertSurface(PtWidget_t *widget,PtSurface_t *surface,PtSurfaceId_t brother_id,int behind);
extern int PtInsertSurfaceById(PtWidget_t *widget,PtSurfaceId_t surface_id,PtSurfaceId_t brother_id,int behind);
extern int PtSurfaceToFront(PtWidget_t *widget,PtSurface_t *surface);
extern int PtSurfaceToFrontById(PtWidget_t *widget,PtSurfaceId_t surface_id);
extern int PtSurfaceToBack(PtWidget_t *widget,PtSurface_t *surface);
extern int PtSurfaceToBackById(PtWidget_t *widget,PtSurfaceId_t surface_id);
extern void PtDrawSurfaces(PtWidget_t *widget,PhTile_t *damage);
extern PtWidgetAction_t const *PtSurfaceFindAction(PtWidget_t *widget,PtSurface_t *surface);
extern int PtCheckSurfaces(PtWidget_t *widget,PhPoint_t const *point,PhEvent_t *event);
extern void PtDamageSurface(PtWidget_t *widget,PtSurface_t *surface);
extern void PtDamageSurfaceById(PtWidget_t *widget,PtSurfaceId_t surface_id);
extern void PtDamageSurfaceByAction(PtWidget_t *widget,PtWidgetClassRef_t const *cref,ushort_t action_id);
extern void PtCalcSurface(PtWidget_t *widget,PtSurface_t *surface);
extern PtSurface_t *PtCalcSurfaceById(PtWidget_t *widget,PtSurfaceId_t surface_id);
extern void PtCalcSurfaceByAction(PtWidget_t *widget,PtWidgetClassRef_t const *cref,ushort_t action_id);
extern void PtCalcSurfaces(PtWidget_t *widget,uchar_t post);
extern int PtHideSurface(PtWidget_t *widget,PtSurface_t *surface);
extern int PtHideSurfaceById(PtWidget_t *widget,PtSurfaceId_t surface_id);
extern int PtHideSurfaceByAction(PtWidget_t *widget,PtWidgetClassRef_t const *cref,ushort_t action_id);
extern int PtShowSurface(PtWidget_t *widget,PtSurface_t *surface);
extern int PtShowSurfaceById(PtWidget_t *widget,PtSurfaceId_t surface_id);
extern int PtShowSurfaceByAction(PtWidget_t *widget,PtWidgetClassRef_t const *cref,ushort_t action_id);
extern int PtSurfaceSetVisible( PtWidget_t *widget, PtSurface_t *surface, int visible );
extern int PtSurfaceSetVisibleByAction( PtWidget_t *widget, PtWidgetClassRef_t const *cref, ushort_t action_id, int visible );
extern int PtSurfaceSetVisibleById( PtWidget_t *widget, PtSurfaceId_t surface_id, int visible );
extern int PtSurfaceAddData(PtWidget_t *widget,PtSurface_t *surface,void *data,long len);
extern int PtSurfaceAddDataById(PtWidget_t *widget,PtSurfaceId_t surface_id,void *data,long len);
extern int PtSurfaceRemoveData(PtWidget_t *widget,PtSurface_t *surface);
extern int PtSurfaceRemoveDataById(PtWidget_t *widget,PtSurfaceId_t surface_id);
extern void *PtSurfaceGetData(PtWidget_t *widget,PtSurface_t *surface);
extern void *PtSurfaceGetDataById(PtWidget_t *widget,PtSurfaceId_t surface_id);
extern int PtInvokeAction(PtWidget_t *widget,PtWidgetClassRef_t const *cref,ushort_t compound_action_id,uchar_t state,PhEvent_t *event);
extern void PtDisableSurface(PtWidget_t *widget,PtSurface_t *surface,ulong_t flags);
extern void PtEnableSurface(PtWidget_t *widget,PtSurface_t *surface,ulong_t flags);
extern void PtDisableSurfaceById(PtWidget_t *widget,PtSurfaceId_t surface_id,ulong_t flags);
extern void PtDisableSurfaceByAction(PtWidget_t *widget,PtWidgetClassRef_t const *cref,ushort_t action_id,ulong_t flags);
extern void PtEnableSurfaceById(PtWidget_t *widget,PtSurfaceId_t surface_id,ulong_t flags);
extern void PtEnableSurfaceByAction(PtWidget_t *widget,PtWidgetClassRef_t const *cref,ushort_t action_id,ulong_t flags);
extern PhRect_t *PtSurfaceRectById(PtWidget_t *widget,PtSurfaceId_t surface_id,PhRect_t *rect);
extern PtSurface_t *PtSurfaceInFront(PtWidget_t *widget);
extern PtSurface_t *PtSurfaceInBack(PtWidget_t *widget);
extern PtSurface_t *PtSurfaceBrotherInFront(PtWidget_t *widget,PtSurface_t *surface);
extern PtSurface_t *PtSurfaceBrotherBehind(PtWidget_t *widget,PtSurface_t *surface);

extern int PtInvokeChildRealizing( PtWidget_t *child );
extern void PtInvokeChildUnrealizing( PtWidget_t *child );
/*
 * April 9 1999
 */
 
extern	PtDataHdr_t *PtUnlinkData( PtDataHdr_t **ptr, PtDataHdr_t *node );
extern	PtDataHdr_t *PtUnlinkWidgetData( PtWidget_t *widget, PtDataHdr_t *node );

/*
 * March 15 1999
 */
 
extern	PtWidget_t *PtNextTopLevelWidget( PtWidget_t *widget );
extern	long PtCRC( char const *buffer, int nbytes );
extern  long PtCRCValue( long, unsigned char );
extern 	PtRegId_t * PtAppAddRegProc(PtAppContext_t app, int type, PtRegCallbackProc_t proc, void *data);
extern 	void PtAppRemoveRegProc(PtAppContext_t app, PtRegId_t *reg_id );

/*
 * Wed May 13 1998
 */
 
extern int PtGetControlFlags( void );
extern	int PtAddData( PtDataHdr_t **ptr, long type, long subtype, void *data, long len, PtDataRemoveF_t *remove_f );
extern	int PtRemoveData( PtDataHdr_t **ptr, long type, long subtype );
extern	void * PtFindNextData( PtDataHdr_t **ptr, PtDataHdr_t *data, long type, long subtype, long *len, PtDataHdr_t **_node );
extern	void * PtFindData( PtDataHdr_t **ptr, long type, long subtype, long *len, PtDataHdr_t **_node );

/*
 *Tue Apr 21  1998
 */

extern int PtBlit( PtWidget_t *widget, PhRect_t const *, PhPoint_t const * );
extern int PtClippedBlit( PtWidget_t *widget, PhTile_t const *, PhPoint_t const *, PhTile_t const * );
extern const PhGrafxInfo_t *PtGetGraphicsInfo( PtWidget_t *widget );
extern void PtContainerRegister( PtWidget_t *widget );
extern void PtContainerDeregister( PtWidget_t *widget );
extern int PtApplyAnchors( PtWidget_t *widget );

/*
 * April 14, 1998
 */
 
extern int PtAddWidgetData( PtWidget_t *widget, PtWidgetClassRef_t *type, long subtype, void *data );
extern int PtRemoveWidgetData( PtWidget_t *widget, PtWidgetClassRef_t *type, long subtype );
extern void * PtFindNextWidgetData( PtWidget_t *widget, PtDataHdr_t *data, PtWidgetClassRef_t *type, long subtype, PtDataHdr_t **_node );
extern void * PtFindWidgetData( PtWidget_t *widget, PtWidgetClassRef_t *type, long subtype, PtDataHdr_t **_node );

/*
 * July 14, 1997
 */

extern PtWidget_t * PtSuperConstrainer( PtWidget_t *widget );
extern void PtInvokeChildMovedResized( PtWidget_t *child, PhArea_t *oarea, PhRect_t *oextent );
extern void PtInvokeChildCreated( PtWidget_t *child );
extern void PtInvokeChildDestroyed( PtWidget_t *child );
extern int PtInvokeChildSettingResource( PtWidget_t *child, PtArg_t const *argt );
extern int PtInvokeChildGettingResource( PtWidget_t *child, PtArg_t *argt );
extern int PtInvokeChildGettingFocus( PtWidget_t *child, PhEvent_t *event );
extern int PtInvokeChildLosingFocus( PtWidget_t *child, PhEvent_t *event );
extern void PtInvokeSyncWidget( PtWidget_t * );
 
/*
 * July 2, 1997
 */

extern int PtChildType( PtWidget_t *parent, PtWidget_t *child );
extern PtWidget_t * PtFindGuardian( PtWidget_t *child, int superior_only );
extern void PtInvokeChildRealized( PtWidget_t *child );
extern void PtInvokeChildUnRealized( PtWidget_t *child );

/*
 * June 23, 1997
 */
 
extern int PtResizeEventMsg( PtAppContext_t app, int msg_size );
extern int PtWidgetInsert( PtWidget_t *widget, PtWidget_t *new_sibling, int behind );
extern int PtCalcAbsPosition(PtWidget_t *widget, PhPoint_t const *pos, PhDim_t const *dim, PhPoint_t *new_pos);
extern int PtComboBoxListOpen( PtWidget_t *widget);
extern int PtComboBoxListClose( PtWidget_t *widget);
	extern PhRect_t *
PtChildBoundingBox( PtWidget_t *widget, PhRect_t *canvas, PhRect_t *render );
	extern void 
PpPrintWidget( PpPrintContext_t *pc, PtWidget_t *widget, PhPoint_t const *trans, PhRect_t const *clip_rect, ulong_t opt );
	extern void
PtSuperClassChildCreated( PtWidgetClassRef_t *cref, PtWidget_t *widget, PtWidget_t *child );
	extern void
PtSuperClassChildDestroyed( PtWidgetClassRef_t *cref, PtWidget_t *widget, PtWidget_t *child );
	extern void
PtSuperClassChildRealized( PtWidgetClassRef_t *cref, PtWidget_t *widget, PtWidget_t *child );
	extern void
PtSuperClassChildUnrealized( PtWidgetClassRef_t *cref, PtWidget_t *widget, PtWidget_t *child );
	extern int
PtSuperClassChildGettingFocus( PtWidgetClassRef_t *cref, PtWidget_t *widget, PtWidget_t *child, PhEvent_t *event );
	extern int
PtSuperClassChildLosingFocus( PtWidgetClassRef_t *cref, PtWidget_t *widget, PtWidget_t *child, PhEvent_t *event );
	extern void
PtSuperClassChildMovedResized( PtWidgetClassRef_t *cref, PtWidget_t *widget, PtWidget_t *child, PhArea_t *current_area, PhRect_t *current_extent, PhArea_t *old_area, PhRect_t *old_extent );
	extern int
PtSuperClassChildSettingResources( PtWidgetClassRef_t *cref, PtWidget_t *widget, PtWidget_t *child, PtArg_t const *argt);
	extern int
PtSuperClassChildGettingResources( PtWidgetClassRef_t *cref, PtWidget_t *widget, PtWidget_t *child, PtArg_t *argt);
	extern PtWidget_t * 
PtGlobalFocusPrevContainer( PtWidget_t *widget, PhEvent_t *event );
	extern PtWidget_t * 
PtGlobalFocusPrev( PtWidget_t *widget, PhEvent_t *event );
	extern PtWidget_t * 
PtGlobalFocusNext( PtWidget_t *widget, PhEvent_t *event );
	extern PtWidget_t *
PtGlobalFocusNextContainer( PtWidget_t *widget, PhEvent_t *event );
	extern PtWidget_t * 
PtFindFocusChild( PtWidget_t *widget );
	extern PtWidget_t *
PtCompoundRedirect( PtWidget_t *widget, PtWidgetClassRef_t *a_class );

/*
 * Sept. /96 --^
 */

/*extern PtWidget_t * PtGlobalFocusNextFrom( PtWidget_t *widget, PhEvent_t *event ); */
/*extern PtWidget_t * PtGlobalFocusPrevFrom( PtWidget_t *widget, PhEvent_t *event ); */

extern PtWidget_t * PtFindConditionalWidget( PtWidget_t *widget, int direction, int(*skip)(PtWidget_t *, void *) );
extern PtWidget_t * PtFindWidget( PtWidget_t *widget, int direction );
extern int PtBeep( void ); 
extern int PtIsFocused( PtWidget_t *widget );

/*
 * July /96 --^
 */

extern void PtSetAnchorOffsets( PtWidgetList_t *wlp );
extern PtResourceRec_t const * PtFindResource (long type, PtWidgetClass_t const *a_class);
extern PtWidget_t *PtAllocWidget( PtWidgetClass_t *aclass );
extern void PtCompoundCallbackRedirect( PtWidget_t *widget, PtWidget_t *child, PtResourceRec_t const *rr, PtArg_t const *argt );
extern PtWidget_t * PtValidParent( PtWidget_t *widget, PtWidgetClassRef_t *a_class );
extern int PtWidgetVisibleExtent( PtWidget_t *widget, PhRect_t *rect );
extern void PtInvalidateSystemInfo( PtWidget_t *widget );
extern void PtFepEvent( PtWidget_t *widget, PhEvent_t *event, PhRect_t const *cursor_rel_rect, long type, const char *font );
#define PtEmitFepEvent(widget,event,cursor_rel_rect,type) PtFepEvent(widget,event,cursor_rel_rect,type,NULL)
extern int PtFepRequest( PhKeyEvent_t const *key_event );
extern int PtFepCmd( PtWidget_t *widget, long cmd, long sub_cmd, char const * data );

/*
 * June 6+/96 --^
 */

extern void PtBkgdHandlerProcess(void);
extern PhSysInfo_t *PtQuerySystemInfo( PtWidget_t *widget, PhSysInfo_t *sysinfo );
/*
 * April 22/96 --^
 */

extern PtWidget_t *PtFindDisjoint( PtWidget_t *widget );
extern int PtResizePolicy( PtWidget_t *widget );
/*
 * April 96 --^
 */

extern PtWidget_t *PtHit( PtWidget_t *widget, unsigned level, PhRect_t const *rect );
extern int PtSuperClassInitFrom( PtWidgetClassRef_t *, PtWidget_t *);
extern int PtSuperClassRawEvent( PtWidgetClassRef_t *, PtWidget_t *, PhEvent_t * );
extern int PtSuperClassRawEventFrom( PtWidgetClassRef_t *, PtWidget_t *, PhEvent_t * );
extern int PtSuperClassGetResources( PtWidgetClassRef_t *, PtWidget_t *, int, PtArg_t *arg_list);
extern int PtSuperClassSetResources( PtWidgetClassRef_t *, PtWidget_t *, int, PtArg_t const *arg_list);
extern int PtSuperClassConnectFrom( PtWidgetClassRef_t *, PtWidget_t * );

/*
 * March 96 --^
 */

extern PtWidget_t * PtAppInit( PtAppContext_t *,int *, char **, int , PtArg_t const *);
extern PhRect_t *PtWidgetCanvas( PtWidget_t *widget, PhRect_t *rect);
extern void PtLabelPos(PtWidget_t *,PhPoint_t const *,PhPoint_t *);
extern int PtLabelRepairString(PtWidget_t *,int ,char const *);

extern void PtAnchorWidget(PtWidget_t *, int);
extern int PtCalcAnchorOffsets(PtWidget_t *);

extern PhRect_t * PtSetExtentFromArea( PtWidget_t *, PhArea_t const *,PhRect_t *);
extern int PtInit(char const *);
extern int PtStartPen(PtWidget_t *);
extern int PtSetStruct( char *, PtResourceRec_t const*, PtArg_t const *);
extern PhArea_t *PtSetAreaFromExtent( PtWidget_t *, PhRect_t const *, PhArea_t *);
extern PhArea_t *PtSetAreaFromCanvas(PtWidget_t *, PhRect_t const *, PhArea_t * );
extern PhArea_t *PtSetAreaFromWidgetCanvas( PtWidget_t *, PhRect_t const *, PhArea_t *);
extern int PtGetStruct(char *, PtResourceRec_t const *mod, PtArg_t *);
extern int PtSetValue(PtWidget_t *,PtResourceRec_t const *,PtArg_t const *);
extern int PtSetResources(PtWidget_t *,int ,PtArg_t const *);
extern int _PtSetResource(PtWidget_t *,long ,long ,long);
extern int _PtGetResource(PtWidget_t *,long ,long ,long);
extern int PtCoreSetResources(PtWidget_t *widget, int num, PtArg_t const *args, PtResourceRec_t const *rrec);
extern int PtCompoundSetResources(PtWidget_t *widget, int num, PtArg_t const *args, PtResourceRec_t const *rrec);
extern int PtGetResources(PtWidget_t *,int ,PtArg_t *);
extern int PtCoreGetResources(PtWidget_t *,int ,PtArg_t *);
extern int PtCompoundGetResources(PtWidget_t *,int ,PtArg_t *);
extern int PtNullWidget_f(PtWidget_t *);
extern PtWidget_t *PtSetParentWidget(PtWidget_t *);
extern PhPoint_t *PtWidgetOffset(PtWidget_t *,PhPoint_t *);
extern PtWidgetClass_t *PtCreateWidgetClass(PtWidgetClassRef_t *,unsigned int ,unsigned int ,PtArg_t const *);
extern PtWidget_t *PtWidgetSkip(PtWidget_t *,PtWidget_t *);
extern PtWidget_t *PtWidgetDrawSkip(PtWidget_t *,PtWidget_t *);
extern PtWidget_t *PtInflateBalloon( PtWidget_t *win, PtWidget_t *widget, int balloon_position, char const *message, char const *font, PgColor_t fill, PgColor_t text_color);
extern PtWidget_t *PtWidgetAbove(PtWidget_t *root,PtWidget_t *current);
extern PtWidget_t *PtWidgetDrawAbove(PtWidget_t *,PtWidget_t *);
extern PtWidget_t *PtWidgetFamily(PtWidget_t *,PtWidget_t *);
extern PtWidget_t *PtWidgetDrawFamily(PtWidget_t *,PtWidget_t *);
extern PtWidget_t *PtCreateWidget(PtWidgetClassRef_t *,PtWidget_t *,unsigned int ,PtArg_t const *);
extern PtWidget_t *PtExtentWidget(PtWidget_t *);
extern int PtRealizeWidget(PtWidget_t *);
extern int PtDrawWidget(unsigned int ,PtWidget_t *);
extern int PtDrawClippedWidget(unsigned int ,PtWidget_t *,int ,PhRect_t const *);
extern int PtDrawHierarchy( PtWidget_t *wp, const PhTile_t *expose_tiles, PhTile_t **updated_tiles );
extern int PtUnrealizeWidget(PtWidget_t *);
extern int PtRemoveWidget( void );
extern int PtRemoveWidgetInstance(PtWidget_t *);
extern int PtDestroyWidget(PtWidget_t *);
extern int PtEventHandler(PhEvent_t *);
extern PhGC_t *PtSetGC(PhGC_t *);
extern void PtDefaultGC(PhGC_t *);
extern int PtForceUpdate(void );
extern int PtHoldWidget(PtWidget_t *);
extern int PtReleaseWidget(PtWidget_t *);
extern int PtReRealizeWidget(PtWidget_t *);
extern int PtMoveResizeWidget(PtWidget_t *,unsigned);
extern void PtRemoveDamage(PtWidget_t *widget, PhPoint_t const *unused, PhTile_t *tile_list, int n_unused);
extern int PtStartFlux(PtWidget_t *);
extern int PtEndFlux(PtWidget_t *);
extern int PtIsFluxing(PtWidget_t *);
extern int PtHold(void );
extern int PtFlush(void );
extern int PtRelease(void );
extern int PtSyncWidget(PtWidget_t *);
extern int PtUpdate(void );
extern int PtDamageCleanWidget(PtWidget_t *);
extern int PtDamageWidget(PtWidget_t *);
extern void PtDamageExposed(PtWidget_t *,PhTile_t *);
extern int PtDamageTiles(PtWidget_t *,PhTile_t const *);
extern int PtDamageExtent(PtWidget_t *,PhRect_t const *);
extern int PtWidgetIsClassMember(PtWidget_t *,PtWidgetClassRef_t *);
extern PtWidget_t *PtFindChildClass(PtWidgetClassRef_t *,PtWidget_t *);
extern PtWidget_t *PtFindChildClassMember(PtWidgetClassRef_t *,PtWidget_t *);
extern int PtWidgetIsClear(PtWidget_t *);
extern int PtWidgetIsObscured(PtWidget_t *);
extern int PtWidgetToFront(PtWidget_t *);
extern int PtWidgetToBack(PtWidget_t *);

extern void PtDestroyDoomedWidgets( void );

extern int PtInvokeCallbackList(PtCallbackList_t *,PtWidget_t *,PtCallbackInfo_t *);
extern int PtInvokeCallbackType( PtWidget_t *widget, long type, PtCallbackInfo_t *cbinfo );
extern int PtDestroyCallbackList(PtCallbackList_t **);
extern void PtClipStart(PhRect_t const *);
extern int PtClipAdd(PtWidget_t *,PhRect_t const *);
extern int PtClipRemove(void );
extern void PtWindowToBack(PtWidget_t *);
extern void PtWindowToFront(PtWidget_t *);
extern int PtWindowFocus(PtWidget_t *);
extern int PtForwardWindowEvent(PhWindowEvent_t const *);
extern int PtForwardWindowConfig(WmConfig_t const *, int);
extern int PtForwardWindowMenuRead ( int flags );
extern WmConfig_t *PtGetWindowConfig(WmConfig_t *);
extern int PtForwardWindowTaskEvent(PhConnectId_t, PhWindowEvent_t const *);
extern int PtWindowConsoleSwitch(PhRid_t);
extern int PtConsoleSwitch(int);
extern void PtGetAbsPosition(PtWidget_t *,short *,short *);
extern PtWidget_t * PtGetParent(PtWidget_t *,PtWidgetClassRef_t *);
extern int PtTranslateCoord(PtWidget_t *,PhPoint_t const *,PhPoint_t *);
extern PhRect_t *PtPositionRect( PhRect_t *rect, PhPoint_t const * );
extern int PtLabelSetColor( PtWidget_t *);
extern int PtContainerHold(PtWidget_t *);
extern int PtContainerInit( PtWidget_t *);
extern int PtContainerRelease(PtWidget_t *);
extern PtWidget_t *PtContainerBox(PtWidget_t *,PtWidget_t *,PhRect_t const *);
extern PtWidget_t *PtContainerHit(PtWidget_t *,unsigned int ,PhRect_t const *);
extern PtWidget_t *PtContainerGiveFocus(PtWidget_t *,PhEvent_t *);
extern PtWidget_t *PtContainerFindFocus(PtWidget_t *);
extern PtWidget_t *PtContainerNullFocus(PtWidget_t *,PhEvent_t *);
extern PtWidget_t *PtContainerRelinquishFocus(PtWidget_t *,PhEvent_t *);
extern PtWidget_t *PtContainerFocusNext(PtWidget_t *,PhEvent_t *);
extern PtWidget_t *PtContainerFocusPrev(PtWidget_t *,PhEvent_t *);
extern PtWidget_t *PtFindFocusChild( PtWidget_t *widget ); 
extern PtWidget_t *PtFindFocusNextFrom( PtWidget_t *widget );
extern PtWidget_t *PtGlobalFocusNextFrom( PtWidget_t *widget, PhEvent_t *event );
extern PtWidget_t *PtFindFocusPrevFrom( PtWidget_t *widget );
extern PtWidget_t *PtGlobalFocusPrevFrom( PtWidget_t *widget, PhEvent_t *event );
extern PtWidget_t *PtContainerNext( PtWidget_t *widget );
extern PtWidget_t *PtContainerPrev( PtWidget_t *widget );
extern PtWorkProcId_t * PtAppAddWorkProc(PtAppContext_t ,PtWorkProc_t ,void *);
extern void PtAppRemoveWorkProc(PtAppContext_t ,PtWorkProcId_t *);
extern PtInputId_t * PtAppAddInput(PtAppContext_t ,pid_t ,PtInputCallbackProc_t ,void *);
extern PtInputId_t * PtAppAddInputRemote(PtAppContext_t, int, pid_t, PtInputCallbackProc_t, void *);
extern void PtAppRemoveInput(PtAppContext_t ,PtInputId_t *);
extern void PtAppProcessEvent(PtAppContext_t );
extern void PtProcessEvent(void );
extern void PtAppMainLoop(PtAppContext_t );
extern void PtMainLoop(void );
extern int PtGraphicSetStroke(PtWidget_t *);
extern unsigned PtGraphicFillGC( PtWidget_t *widget, unsigned flags );
extern void PtGraphicExtendMargin(PtWidget_t *);
extern void PtLabelPos(PtWidget_t *,PhPoint_t const *,PhPoint_t *);
extern int PtLabelRepairString(PtWidget_t *,int ,char const *);
extern PhRect_t *PtLabelWidgetCanvas(PtWidget_t *,PhRect_t *);
extern int PtAttemptResize(PtWidget_t *,PhRect_t const *,PhRect_t const *);
extern int PtResizeCanvas(PtWidget_t *, PhDim_t const * );
extern PhDim_t *PtWidgetMinimumSize( PtWidget_t *, PhDim_t * );
extern PhDim_t *PtWidgetPreferredSize( PtWidget_t *, PhDim_t * );
extern int PtDestroyRawCallbacks( PtWidget_t * );
extern int PtDestroyHotkeyCallbacks( PtWidget_t * );
extern int PtCalcRegion(unsigned int *,PtWidget_t *,PhRegion_t *,PhRect_t *);
extern void PtCoreChangeRegion(unsigned int ,PtWidget_t *);
extern PhRect_t *PtWidgetCanvas(PtWidget_t *,PhRect_t *);
extern PhPoint_t *PtWindowPosition(PtWidget_t *,PhPoint_t *);
extern int PtWindowSetInfo(unsigned int ,PtWidget_t *);
extern void PtFrameSize(ulong_t ,int ,int *,int *,int *,int *);
extern int PtClearWidget( PtWidget_t * );
extern void PtAddCallback( PtWidget_t *, unsigned long callback_type, PtCallbackF_t *callback, void *);
extern void PtAddCallbacks( PtWidget_t *, unsigned long callback_type, PtCallback_t const *callbacks, unsigned int );
extern void PtRemoveCallback( PtWidget_t *, unsigned long callback_type, PtCallbackF_t *callback, void *data );
extern void PtRemoveCallbacks( PtWidget_t *, unsigned long callback_type, PtCallback_t const *callbacks, unsigned int );
extern void PtAddEventHandler( PtWidget_t *, unsigned long event_mask, PtCallbackF_t *callback,  void *data );
extern void PtAddEventHandlers( PtWidget_t *, PtRawCallback_t const *, unsigned int );
extern void PtRemoveEventHandler( PtWidget_t *, unsigned long , PtCallbackF_t *callback, void *);
extern void PtRemoveEventHandlers( PtWidget_t *, PtRawCallback_t const *, int );
extern void PtAddHotkeyHandler( PtWidget_t *, unsigned , unsigned , short, void *, PtCallbackF_t *event_f );
extern void PtRemoveHotkeyHandler( PtWidget_t *, unsigned , unsigned , short, void *, PtCallbackF_t *event_f );
extern void *PtGetCallbackList( PtWidget_t *widget, long cb_type );
extern int PtRemoveCallbackList( PtWidget_t *widget, long cb_type );
extern int PtRectIntersect( PhRect_t *, PhRect_t const *);
extern int PtRectUnion( PhRect_t *, PhRect_t const *);
extern int PtReattach( char * );
extern int PtAskQuestion( PtWidget_t *, char const *, char const *, char const *, char const *, char const *, char const *, int );
extern int PtMessageBox( PtWidget_t *, char const *, char const *, char const *, char const *);
extern int PtAlert( PtWidget_t *, PhPoint_t const *, char const *, PhImage_t const *, char const *, char const *, int, char const **, char const **, int, int, int );
extern int PtPrompt( PtWidget_t *, PhPoint_t const *, char const *, PhImage_t const *, char const *, char const *, int, char const **, char const **, int, int, short, char *, char const *, PhDim_t const *, int );
extern int PtNotice( PtWidget_t *, PhPoint_t const *, char const *, PhImage_t const *, char const *, char const *, char const *, char const *, int );
extern int PtPassword( PtWidget_t *, PhPoint_t const *, char const *, PhImage_t const *, char const *, char const *, char const **, char const **, char const *, int (*)(void *,char const *), void *, char const *, int );
extern void PtSetCustomCursor(PtWidget_t *,PhCursorDef_t const *);
extern PhCursorDef_t *PtCreateCustomCursor(PtWidget_t *,PhDim_t const *,PhPoint_t const *,void const *,void const *,PgColor_t,PgColor_t);
extern void PtSyncPhoton( void );
extern int PtModalStart( void );
extern void PtModalEnd( void );
extern void PtPositionMenu( PtWidget_t *, PhEvent_t *);
extern int PtListAddItems( PtWidget_t *widget, const char **items, int item_count, unsigned int position ) ;
extern int PtListItemExists( PtWidget_t *widget, const char *item );
extern int PtListItemPos( PtWidget_t *widget, const char *item );
extern int PtListReplaceItemPos( PtWidget_t *widget, const char **new_items, int item_count, int position );
extern int PtListReplaceItems( PtWidget_t *widget, const char **old_items, const char **new_items, int item_count );
extern int PtListDeleteItems( PtWidget_t *widget, const char **items, int item_count );
extern int PtListDeletePositions( PtWidget_t *widget, int const *pos_list, int pos_count );
extern int PtListRemovePositions( PtWidget_t *widget, unsigned short const *pos_list, int pos_count );
extern int PtListDeleteItemPos( PtWidget_t *widget, int item_count, int position );
extern int PtListDeleteAllItems( PtWidget_t *widget );
extern int PtReParentWidget( PtWidget_t *widget, PtWidget_t *parent );
extern int PtExtentWidgetFamily( PtWidget_t *widget );
extern int PtWidgetTree( PtWidget_t *root, PtWidget_t **cur, int D );
extern int PtWidgetTreeTraverse( PtWidget_t *root, PtWidget_t **cur, int D, int (*skip_cond_f)(PtWidget_t *, void *), void * );
extern PtWidget_t * PtWidgetHelpHit( PtWidget_t *widget, PhPoint_t const *pos );
extern int _PtAnchorParent( PtWidget_t *widget, PhDim_t const *new_dim, int flag );
extern long PtWindowGetState( PtWidget_t *widget );
extern PtWidget_t *PtValidParent( PtWidget_t *, PtWidgetClassRef_t * );
extern int PtSendEventToWidget( PtWidget_t *, PhEvent_t * );
extern int PtTimerArm( PtWidget_t *, unsigned int );
extern int PtCBoxAddItems( PtWidget_t *widget, char const **items, int item_count, unsigned int position ) ;
extern int PtCBoxItemExists( PtWidget_t *widget, char const *item );
extern int PtCBoxItemPos( PtWidget_t *widget, char const *item );
extern int PtCBoxReplaceItemPos( PtWidget_t *widget, char const **new_items, int item_count, int position );
extern int PtCBoxReplaceItems( PtWidget_t *widget, char const **old_items, const char **new_items, int item_count );
extern int PtCBoxDeleteItems( PtWidget_t *widget, char const **items, int item_count );
extern int PtCBoxDeletePositions( PtWidget_t *widget, unsigned int const *pos_list, int pos_count );
extern int PtCBoxDeleteItemPos( PtWidget_t *widget, int item_count, int position );
extern int PtCBoxDeleteAllItems( PtWidget_t *widget );
extern int PtCBoxSelectPos( PtWidget_t *widget, int pos );
extern int PtCBoxUnselectPos( PtWidget_t *widget, int pos );

extern char *PtFontSelection(PtWidget_t *widget, PhPoint_t const *pos, char const *title, char const *font, long symbol, unsigned flags, char const *sample);
extern int PtPrintSelection(PtWidget_t *widget, PhPoint_t const *pos, const char *title, PpPrintContext_t *context, unsigned flags);
extern int PtCustomPrintSelection(PtWidget_t *widget, PhPoint_t const *pos, const char *title, PtArg_t *custom_args, int num_custom_args );

extern int PtAppAddSignalProc(PtAppContext_t context, sigset_t const *sig, PtSignalProc_t proc, void *data);
extern int PtAppRemoveSignalProc(PtAppContext_t context, sigset_t const *sig);
extern int PtAppRemoveSignal( PtAppContext_t app, sigset_t const *setp, PtSignalProc_t proc, void *data );

extern int PtChannelCreate( void );
extern pid_t PtAppCreatePulse( PtAppContext_t app, int priority );
extern struct Pt_Pulse *_PtFindPulse( PtAppContext_t app, pid_t i );

extern pid_t PtGetRcvidPidNd( int rcvid, int *nd );
#if defined(__QNXNTO__)
	int PtPulseArm( PtAppContext_t app, pid_t pulse, struct sigevent *msg );
	extern pid_t (PtGetRcvidPid)( int rcvid );
#else
	extern pid_t _PtGetPulsePid( PtAppContext_t app, pid_t pulse );
#endif

extern int PtAppDeletePulse( PtAppContext_t app, pid_t pulse );
extern PtPulseMsgId_t *PtPulseArmPid( PtAppContext_t app, pid_t pulse, pid_t pid, PtPulseMsg_t *msg );
extern PtPulseMsgId_t *PtPulseArmFd( PtAppContext_t app, pid_t pulse, int fd, PtPulseMsg_t *msg );
extern void PtPulseDisarm( PtPulseMsgId_t * );
extern int PtPulseDeliver( pid_t rcvid, PtPulseMsg_t const *pulse );
extern int PtAppPulseTrigger( PtAppContext_t app, pid_t pulse );

typedef int PtFdProcF_t( int fd, void *data, unsigned mode );
typedef PtFdProcF_t *PtFdProc_t;

extern int PtAppAddFd( PtAppContext_t app, int fd, unsigned mode, PtFdProc_t fun, void *data );

extern int PtAppAddFdPri( PtAppContext_t app, int fd, unsigned mode, PtFdProc_t fun, void *data, int priority );

extern int PtAppSetFdMode( PtAppContext_t app, int fd, unsigned mode );

extern int PtAppRemoveFd( PtAppContext_t app, int fd );


extern pid_t PtSpawn(
	const char *cmd, const char *const *argv, const char *const *env,
	const PtSpawnOptions_t *opt, PtSpawnCbF_t *cb, void *data,
	PtSpawnCbId_t **idp
	);
extern void PtSpawnSetCallback( PtSpawnCbId_t *id, PtSpawnCbF_t *fun, void *data );
extern void PtSpawnDeleteCallback( PtSpawnCbId_t *id );
extern int PtSpawnWait(
	const char *cmd, const char **argv, const char **env,
	const PtSpawnOptions_t *opt, pid_t *pidp
	);

extern int PtWaitPid( pid_t pid );

int PtClassOverride( int const *class_id, int num_class, void (*class_create_f(int class_id, PtWidgetClassRef_t *, void *)), void *data);
long PtClassSetOveride( PtWidgetClassRef_t *class_ref, long res, long new_resource );
int PtClassOverrideResources( PtWidgetClassRef_t *class_ref, PtResourceRec_t *new_res, int n );
int PtClassOverrideResource( PtWidgetClassRef_t *class_ref, PtResourceRec_t *new_res );
int PtClassAddResourcesOnTheFly( PtWidgetClassRef_t *class_ref, int nres, PtResourceRec_t *new_res, int extra_len );
int PtSuperClassSetOnlyOverriddenResources( PtWidgetClassRef_t *cref, PtWidget_t *widget, int num, PtArg_t const *argt );
int PtSuperClassGetOnlyOverriddenResources( PtWidgetClassRef_t *cref, PtWidget_t *widget, int num, PtArg_t *argt );
int PtSuperClassSetNonOverriddenResources( PtWidgetClassRef_t *cref, PtWidget_t *widget, int num, PtArg_t const *argt );
int PtSuperClassGetNonOverriddenResources( PtWidgetClassRef_t *cref, PtWidget_t *widget, int num, PtArg_t *argt );


extern int PtAddClassData( PtWidgetClassRef_t *class_ref, long type, long subtype, void *data );
extern int PtRemoveClassData( PtWidgetClassRef_t *class_ref, long type, long subtype );
extern void * PtFindNextClassData( PtWidgetClassRef_t *class_ref, PtDataHdr_t *data, long type, long subtype, PtDataHdr_t **_node );
extern void * PtFindClassData( PtWidgetClassRef_t *class_ref, long type, long subtype, PtDataHdr_t **_node );

extern void PtBasicHighlight(PtWidget_t *);

extern int PtBasicSetFill(PtWidget_t *);
extern int PtBasicSetColor(PtWidget_t *);
extern void PtBasicActivate(PtWidget_t *,PtCallbackInfo_t *);
extern PhRect_t *PtBasicWidgetCanvas(PtWidget_t *,PhRect_t *);
extern int PtExcludeClip(PtWidget_t *,PhRect_t const *,PhRect_t const *);
extern void PtExcludeUnclip(void);
extern PhRect_t *_PtCalcCanvas(PtWidget_t *,PhRect_t *);
extern PhRect_t *PtCalcCanvas(PtWidget_t *,PhRect_t *);

extern int PtSetMultiClipTiles( PhTile_t *);
extern int PtSetMultiClip(int, PhRect_t const *);
extern PhTile_t *PtGetVisibleTiles( PtWidget_t *widget );
extern PhTile_t *PtGetContainerVisibility( PtWidget_t * );
extern PhTile_t *PtGetClearTiles( PtWidget_t *widget  );
extern PhTile_t *PtGetContainerClearTiles( PtWidget_t * );

extern int PtGenTreeNSelectedItems( PtWidget_t *widget );

extern PtWidget_t *PtCreateDialog(PtDialogInfo_t *);

extern int PtSetStyleMember( PtWidgetClassStyle_t *style, int index, void *value);
extern void *PtGetStyleMember( PtWidgetClassStyle_t *style, int index);

extern int PtAppSetResources(int n_args,PtArg_t const *args);
extern int PtAppGetResources(int n_args,PtArg_t *args);
extern int _PtAppSetResource(long type,long value,long len);
extern int _PtAppGetResource(long type,long value,long len);
extern void PtAppAddCallback(unsigned long cb_type,int (*func)(void*,PtCallbackInfo_t*),void *data);
extern void PtAppRemoveCallback(unsigned long cb_type,int (*func)(void*,PtCallbackInfo_t*),void *data);
extern void PtAppAddHotkeyHandler(	
	unsigned key_sym_cap,
	unsigned key_mods,
	short flags,
	void *data,
	int (*event_f)(void *,PtCallbackInfo_t *));
extern void PtAppRemoveHotkeyHandler(
	unsigned key_sym_cap, 
	unsigned key_mods,
	short flags,
	void *data,
	int (*event_f)(void *,PtCallbackInfo_t *));
extern void PtAppAddEventHandler(
	unsigned long event_mask, 
	int (*func)(void *,PtCallbackInfo_t *), 
	void *data);
extern void PtAppRemoveEventHandler( 
	unsigned long event_mask, 
	int (*func)(void *,PtCallbackInfo_t *), 
	void *data);
extern void PtAppAddFilterCallback(
	unsigned long event_mask,
	int (*func)(void *,PtCallbackInfo_t *),
	void *data);
extern void PtAppRemoveFilterCallback(
	unsigned long event_mask, 
	int (*func)(void *,PtCallbackInfo_t *), 
	void *data);

extern int PtInvokeAppCallbackList(PtAppCallbackList_t *callback,PtCallbackInfo_t *cbinfo);

#ifdef __cplusplus
};
#endif /* __cplusplus */

#include <photon/PhPackPop.h>

#endif /* __PT_PROTO_H_INCLUDED */


#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtProto.h $ $Rev: 219996 $" )
#endif
