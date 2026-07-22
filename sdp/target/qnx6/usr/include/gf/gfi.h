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
#ifndef _MSC_VER

#ifndef _GF_GFI_H_INCLUDED
#define _GF_GFI_H_INCLUDED

#ifndef _STDINT_H_INCLUDED
#include <stdint.h>
#endif

#include <_pack64.h>

#define	GFI_INPUT_GROUP_DEFAULT	1

typedef struct _gfi_group	*gfi_group_t;
typedef struct _gfi_layer	*gfi_layer_t;

/* "flags" argument to gfi_layer_set_attrs */
#define	GFI_ATTR_PTR_SENSITIVE		0x00000001
#define	GFI_ATTR_PTR_TRANSPARENT	0x00000002
#define	GFI_ATTR_KEY_SENSITIVE		0x00000004
#define	GFI_ATTR_KEY_TRANSPARENT	0x00000008

/* "flags" argument to gfi_layer_get_event */
#define	GFI_GET_EVENT_NONBLOCK		0x00000001

#define GFI_EVENT_TYPE_PTR		1
#define GFI_EVENT_TYPE_KEY		2

#define GFI_PTR_BUTTON_1		0x00000001
#define GFI_PTR_BUTTON_2		0x00000002
#define GFI_PTR_BUTTON_3		0x00000004
#define GFI_PTR_BUTTON_4		0x00000008
#define GFI_PTR_BUTTON_5		0x00000010
#define GFI_PTR_BUTTON_6		0x00000020
#define GFI_PTR_BUTTON_7		0x00000040
#define GFI_PTR_BUTTON_8		0x00000080
#define GFI_PTR_BUTTON_RIGHT		GFI_PTR_BUTTON_1
#define GFI_PTR_BUTTON_MIDDLE		GFI_PTR_BUTTON_2
#define GFI_PTR_BUTTON_LEFT		GFI_PTR_BUTTON_3

typedef struct gfi_event {
	_Int32t		type;
	_Int32t		msec;
	union {
		struct {
			_Int32t		x;		/* Absolute display co-ord */
			_Int32t		y;		/* Absolute display co-ord */
			_Uint32t	buttons;	/* GFI_PTR_BUTTON_* */
			_Uint32t	flags;
		} ptr;
		struct {
			_Uint32t	modifiers;	/* See KEYMOD_* in <sys/keycodes.h> */
			_Uint32t	cap;
			_Uint32t	sym;
			_Uint32t	scan;
			_Uint32t	flags;		/* See KEY_* in <sys/keycodes.h> */
		} key;
	} u;
} gfi_event_t;

__BEGIN_DECLS

int gfi_group_attach(gfi_group_t *input_group, int group_no, unsigned flags);
void gfi_group_detach(gfi_group_t input_group);
int gfi_layer_attach(gfi_layer_t *input_layer,
    gfi_group_t input_group, unsigned flags, int layer_z_pos);
void gfi_layer_detach(gfi_layer_t input_layer);
int gfi_layer_set_attrs(gfi_layer_t layer,
    int x1, int y1, int x2, int y2, unsigned flags);
int gfi_layer_get_event(gfi_layer_t layers[],
    int nlayers, gfi_event_t *event, unsigned flags);
int gfi_emit_event(gfi_group_t input_group, gfi_event_t *ev, int layer_z_pos);
int gfi_set_keyboard_focus(gfi_group_t input_group, int layer_z_pos);
int gfi_set_device_state(gfi_group_t ig, short type, int state);
int gfi_set_ptr_mode( gfi_layer_t layer, int flags );
int gfi_set_ptr_matrix3( gfi_layer_t layer, 
		int64_t An, int64_t Bn, int64_t Cn, int64_t Dn, 
		int64_t En, int64_t Fn, int64_t Divider );
int gfi_set_ptr_matrix4( gfi_layer_t layer, 
	int scr_xoffset, int scr_yoffset, int scr_xscale, int scr_yscale, 
	int coord_xoffset, int coord_yoffset, int coord_xscale, int coord_yscale,
	int swap );

__END_DECLS

#include <_packpop.h>

#endif /* _GF_GFI_H_INCLUDED */
#endif /* _MSC_VER */

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/gf/public/gf/gfi.h $ $Rev: 224586 $" )
