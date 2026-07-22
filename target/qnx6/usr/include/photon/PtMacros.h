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
#ifndef __PT_MACROS_H_INCLUDED
#define __PT_MACROS_H_INCLUDED

#include <string.h>

/* macros for obtaining information about widgets */

#if defined(__GNUC__)
 #define PtWidgetExtent(w,r)		({ PhRect_t  *res; if((int)(r)!=0) *(res=(r))=(w)->extent;    else res=&(w)->extent;    res; })
 #define PtWidgetArea(w,a)			({ PhArea_t  *res; if((int)(a)!=0) *(res=(a))=(w)->area;      else res=&(w)->area;      res; })
 #define PtWidgetDim(w,d)			({ PhDim_t   *res; if((int)(d)!=0) *(res=(d))=(w)->area.size; else res=&(w)->area.size; res; })
 #define PtWidgetPos(w,p)			({ PhPoint_t *res; if((int)(p)!=0) *(res=(p))=(w)->area.pos;  else res=&(w)->area.pos;  res; })
 #define PtSurfaceRect(s,r)		({ PhRect_t  *res; if((int)(r)!=0) *(res=(r))=*(PhRect_t*)(s)->points; else res=(PhRect_t*)(s)->points; res; })
 #define PtFindContainer(w)		({ PtWidget_t *res; if((int)(w)!=0) res=PtIsContainer(w)?(w):PtWidgetParent(w); else res=NULL; res; })
 #define PtCopyCanvas(w,r)			({ PhRect_t *res=(PhRect_t*)(r); if (PtCanvasIsValid(w)) *res=((PtWidget_t*)(w))->canvas; else res=_PtCalcCanvas(((PtWidget_t*)w),res); res; })
#else
 #define PtWidgetArea(w,a)			((a) ? (PhArea_t*)(memcpy((void*)(a),(void*)(&(w)->area),sizeof(PhArea_t))) : &(w)->area)
 #define PtWidgetDim(w,d)			((d) ? (PhDim_t*)(memcpy((void*)(d),(void*)(&(w)->area.size),sizeof(PhDim_t))) : &(w)->area.size)
 #define PtWidgetExtent(w,r)		((r) ? (PhRect_t*)(memcpy((void*)(r),(void*)(&(w)->extent),sizeof(PhRect_t))) : &(w)->extent)
 #define PtWidgetPos(w,p)			((p) ? (PhPoint_t*)(memcpy((void*)(p),(void*)(&(w)->area.pos),sizeof(PhPoint_t))) : &(w)->area.pos)
 #define PtSurfaceRect(s,r)		((PhRect_t*)((r) ? (memcpy((void*)(r),(void*)((s)->points),sizeof(PhRect_t))) : (s)->points))
 #define PtFindContainer(w)		(((w)?(PtIsContainer(w) ? (w) : PtWidgetParent(w)):NULL))
 #define PtCopyCanvas(w,r)			(PtCanvasIsValid(w) ? memcpy(((PhRect_t *)(r)),&((PtWidget_t *)(w))->canvas, sizeof(PhRect_t)) : _PtCalcCanvas(((PtWidget_t *)w),((PhRect_t *)r)))
#endif

#define PtReParentWidget(w,p)			PtReparentWidget(w,p)
#define PtMember(c,w,m)				(((c##Widget_t*)(w))->m)
#define PtWidgetParent(w)			(((PtWidget_t*)(w))->parent)
#define PtWidgetRid(w)				(((PtWidget_t*)(w))->rid)
#define PtWidgetFlags(w)			(((PtWidget_t*)(w))->flags)
#define PtWidgetIsRealized(w)		(PtWidgetFlags(w) & Pt_REALIZED)
#define PtFlagWidgetResize(w)		(((PtWidget_t*)(w))->flags |= Pt_WIDGET_RESIZE)
#define PtFlagWidgetRebuild(w)		(((PtWidget_t*)(w))->flags |= Pt_WIDGET_REBUILD)
#define PtWidgetClass(w)			(((PtWidget_t*)(w))->class_rec->class_ref)
#define PtWidgetIsClass(w,c)		(PtWidgetClass(w) == (c))
#define PtWidgetClassFlags(w)		(((PtWidget_t*)(w))->class_rec->flags)
#define PtIsBasic(w)				(PtWidgetClassFlags(w) & Pt_BASIC)
#define PtIsContainer(w)			(PtWidgetClassFlags(w) & Pt_CONTAINER)
#define PtIsDisjoint(w)				(PtWidgetClassFlags(w) & Pt_DISJOINT)
#define PtWidgetBrotherInFront(w)	(((PtWidget_t*)(w))->brother)
#define PtWidgetBrotherBehind(w)	(((PtWidget_t*)(w))->bro_behind)
#define PtWidgetChildFront(w)		(PtIsContainer(w) ? ((PtContainerWidget_t*)(w))->child_front : NULL)
#define PtWidgetChildBack(w)		(((PtWidget_t*)(w))->child)
#define PtResizeWidget(w)			PtMoveResizeWidget(w,0)

/* macros for obtaining information about control surfaces */

#define PtSurfaceId(s)				((s)->surface_id)
#define PtSurfaceIsHidden(s)		((s)->flags & Pt_SURFACE_HIDDEN)
#define PtSurfaceIsShown(s)			(!PtSurfaceIsHidden(s))
#define PtSurfaceIsDisabled(s)		((s)->flags & Pt_SURFACE_DISABLED)
#define PtSurfaceIsEnabled(s)		(!PtSurfaceIsDisabled(s))
#define PtSurfaceActionId(s)		(((s)->flags & Pt_SURFACE_RAW) ? -1 : (s)->action.standard.action_id)
#define PtWidgetActiveSurface(w)	((w)->surface_ctrl.active_surface)

/* macros for invoking superclass methods */

#define PtSuperClassResourceChanged(c,w,t)	{ if((c)->wclass->resource_changed_f) (c)->wclass->resource_changed_f(w,t); }
#define PtSuperClassExtent(c,w)				PtSuperClassSizing(c,w)
#define PtSuperClassSizing(c,w)				((c)->wclass->styles[0]->sizing_f(w))
#define PtSuperClassInit(c,w)				((c)->wclass->init_f ? (c)->wclass->init_f(w) : Pt_CONTINUE)
#define PtSuperClassConnect(c,w)			((c)->wclass->connect_f ? (c)->wclass->connect_f(w) : Pt_CONTINUE)
#define PtSuperClassRealized(c,w)			{ if((c)->wclass->realized_f) (c)->wclass->realized_f(w); }
#define PtSuperClassDraw(c,w,d)				{ (c)->wclass->styles[0]->draw_f(w,d); PtDefaultGC(PgGetGC()); }
#define PtSuperClassCalcBorder(c,w,r)		((c)->wclass->styles[0]->calc_border_f(w,r))
#define PtCalcBorder(w,r)					(w)->style->calc_border_f(w,r)

#if defined(__cplusplus)
	#define PtSetArg( _arg, _type, _value, _len ) \
		PtSetArg( _arg, _type, (long)(_value), (long)(_len) )
#else
	#if defined(_NO_INLINE_DO_WHILE0)
		#define PtSetArg( arg, _type, _value, _len ) 	\
			( (arg)->type = (long)(_type),   			\
			(arg)->value = (long)(_value),				\
			(arg)->len = (long)(_len) )
	#else
		#define PtSetArg( arg, _type, _value, _len )	\
			do {										\
				PtArg_t *__ptargtptr = (arg);	 		\
				__ptargtptr->type = (long)(_type);  	\
				__ptargtptr->value = (long)(_value);	\
				__ptargtptr->len = (long)(_len);		\
			} while( 0 )
	#endif
#endif

#define Pt_ARG( _type, _value, _len )					\
	{ (_type), (long)(_value), (long)(_len) }

#define PtSetResource(a,b,c,d)	_PtSetResource(a,b,(long)(c),(long)(d))
#define PtGetResource(a,b,c,d)	_PtGetResource(a,b,(long)(c),(long)(d))

#define PtAppSetResource(a,b,c)	_PtAppSetResource(a,(long)(b),(long)(c))
#define PtAppGetResource(a,b,c)	_PtAppGetResource(a,(long)(b),(long)(c))

#define PtCanvasIsValid(w)			(((PtWidget_t*)(w))->eflags & Pt_CANVAS_VALID)
#define PtInvalidateCanvas(w)		(((PtWidget_t*)(w))->eflags &= ~Pt_CANVAS_VALID)
#define PtValidateCanvas(w)		(((PtWidget_t*)(w))->eflags |= Pt_CANVAS_VALID)

#define PtGetCanvas(w)				(PtCanvasIsValid(w) ? &((PtWidget_t *)(w))->canvas : _PtCalcCanvas(w,NULL))

#define PtTranslateRect(rect,point) 	PhTranslateRect(rect,point)
#define PtDeTranslateRect(rect,point)	PhDeTranslateRect(rect,point) 

#define PtTranslatePoint(point,delta)	PhTranslatePoint(point,delta)
#define PtDeTranslatePoint(point,delta) PhDeTranslatePoint(point,delta)

#define PtRectIntersect(r1,r2)			PhRectIntersect(r1,r2)
#define PtRectUnion(r1,r2)				PhRectUnion(r1,r2)

#ifndef __QNXNTO__
#define PtGetRcvidPid( rcvid )	(rcvid)
#endif


#endif /* __PT_MACROS_H_INCLUDED */

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtMacros.h $ $Rev: 227171 $" )
#endif
