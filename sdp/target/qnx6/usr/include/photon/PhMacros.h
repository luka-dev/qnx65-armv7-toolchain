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
#ifndef __PH_MACROS_H_INCLUDED
#define __PH_MACROS_H_INCLUDED

#if defined(__cplusplus) || defined(__GNUC__) || defined(__INTEL_COMPILER)

static __inline__ PhRect_t *PhGetRects( PhEvent_t *event ) {
	return (PhRect_t *)( event + 1 );
	}

static __inline__ void *PhGetData( PhEvent_t *event ) {
	return PhGetRects(event) + event->num_rects;
	}

static __inline__ int PhRectWidth( PhRect_t const *r ) {
	return r->lr.x - r->ul.x + 1;
	}

static __inline__ int PhRectHeight( PhRect_t const *r ) {
	return r->lr.y - r->ul.y + 1;
	}

static __inline__ void PhRectDim( PhRect_t const *rect, PhDim_t *dim ) {
	dim->w = rect->lr.x - rect->ul.x + 1;
	dim->h = rect->lr.y - rect->ul.y + 1;
	}

static __inline__ void PhAreaToRect( PhArea_t const *area, PhRect_t *rect ) {
	rect->lr.x = ( rect->ul.x = area->pos.x ) + area->size.w - 1;
	rect->lr.y = ( rect->ul.y = area->pos.y ) + area->size.h - 1;
	}

static __inline__ void PhRectToArea( PhRect_t const *rect, PhArea_t *area ) {
	area->size.w = rect->lr.x - ( area->pos.x = rect->ul.x ) + 1;
	area->size.h = rect->lr.y - ( area->pos.y = rect->ul.y ) + 1;
	}

static __inline__ void PhTranslateRect( PhRect_t *rect, PhPoint_t const *point ) {
	short p;
	rect->ul.x += ( p = point->x ); rect->lr.x += p;
	rect->ul.y += ( p = point->y ); rect->lr.y += p;
	}

static __inline__ void PhDeTranslateRect( PhRect_t *rect, PhPoint_t const *point ) {
	short p;
	rect->ul.x -= ( p = point->x ); rect->lr.x -= p;
	rect->ul.y -= ( p = point->y ); rect->lr.y -= p;
	}

static __inline__ void PhDetranslateRect( PhRect_t *rect, PhPoint_t const *point ) {
	short p;
	rect->ul.x -= ( p = point->x ); rect->lr.x -= p;
	rect->ul.y -= ( p = point->y ); rect->lr.y -= p;
	}

static __inline__ void PhTranslatePoint( PhPoint_t *point, PhPoint_t const *delta ) {
	point->x += delta->x;
	point->y += delta->y;
	}

static __inline__ void PhDeTranslatePoint( PhPoint_t *point, PhPoint_t const *delta ) {
	point->x -= delta->x;
	point->y -= delta->y;
	}

static __inline__ void PhDetranslatePoint( PhPoint_t *point, PhPoint_t const *delta ) {
	point->x -= delta->x;
	point->y -= delta->y;
	}
#else

#define PhGetRects(_e)		((PhRect_t*)((_e) + 1))
#define PhGetData(_e)		((void*)(PhGetRects(_e) + (_e)->num_rects))

#define PhRectWidth( r ) \
	( (r)->lr.x - (r)->ul.x + 1 )

#define PhRectHeight( r ) \
	( (r)->lr.y - ( r )->ul.y + 1 )

#define PhRectDim( rect, dim ) \
	do{\
		PhRect_t const *_r = rect;				\
		PhDim_t *_d = dim;						\
		_d->w = _r->lr.x - _r->ul.x +1; \
		_d->h = _r->lr.y - _r->ul.y +1; \
	}while(0)

#define PhAreaToRect( area, rect ) 				\
	do { 										\
		PhRect_t *_r = rect; 					\
		PhArea_t const *_a = area;				\
		_r->lr.x = ( _r->ul.x = _a->pos.x ) + _a->size.w -1;	\
		_r->lr.y = ( _r->ul.y = _a->pos.y ) + _a->size.h -1;	\
		} while(0)

#define PhRectToArea( rect, area ) 				\
	do { 								\
		PhRect_t const *_r = rect;				\
		PhArea_t *_a = area; 					\
		_a->size.w = _r->lr.x - (_a->pos.x = _r->ul.x) +1;	\
		_a->size.h = _r->lr.y - (_a->pos.y = _r->ul.y) +1;	\
		} while(0)

#define PhTranslateRect(rect,point) 	\
	do {								\
		PhRect_t *_r = rect;				\
		PhPoint_t _p = *(point);			\
		_r->ul.x += _p.x;					\
		_r->ul.y += _p.y;					\
		_r->lr.x += _p.x;					\
		_r->lr.y += _p.y;					\
	} while(0)


#define PhDetranslateRect(rect,point) PhDeTranslateRect(rect,point)
#define PhDeTranslateRect(rect,point) 	\
	do {								\
		PhRect_t *_r = rect;				\
		PhPoint_t _p = *(point);			\
		_r->ul.x -= _p.x;					\
		_r->ul.y -= _p.y;					\
		_r->lr.x -= _p.x;					\
		_r->lr.y -= _p.y;					\
	} while(0)

#define PhTranslatePoint(point,delta) {		\
	PhPoint_t *_p = point,_d = *(delta);	\
	_p->x += _d.x;							\
	_p->y += _d.y; }



#define PhDetranslatePoint(point,delta) PhDeTranslatePoint(point,delta)
#define PhDeTranslatePoint(point,delta) {	\
	PhPoint_t *_p = point,_d = *(delta);	\
	_p->x -= _d.x;							\
	_p->y -= _d.y; }

#endif

#define PhRegionQuery( rid, region, rect, data, data_len ) \
	PhRegionInfo( rid, region, rect, 1, data, data_len )

#endif /* __PH_MACROS_H_INCLUDED */

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PhMacros.h $ $Rev: 224590 $" )
#endif
