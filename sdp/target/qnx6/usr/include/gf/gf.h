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
/*! \file gf.h */
#ifndef _GF_GF_H_INCLUDED
#define _GF_GF_H_INCLUDED

#ifndef _MSC_VER
#ifndef _STDINT_H_INCLUDED
#include <stdint.h>
#endif

#ifndef _UNISTD_H_INCLUDED
#include <unistd.h>
#endif
#endif /* _MSC_VER */

#ifndef __QNXNTO__
#include <gfpr/gfpr.h>
#endif


__BEGIN_DECLS

/* Numeric value which identifies a managed surface uniquely on a device */
typedef _uint32	gf_sid_t;

/* 16.16 fixed point */ 
typedef _int32	gf_fixed_t;

/* Generic color represenation. Unless otherwise noted, this type is packed
 * native endian with the following components:
 * - Blue; 8-bit value occupying byte 0 (LSB)
 * - Green; 8-bit value occupying byte 1
 * - Red; 8-bit value occupying byte 2
 * - Alpha; 8-bit value occupying byte 3 (MSB). 255 = opaque, 0 = transparent */
typedef _uint32					gf_color_t;

typedef struct _gf_dev *		gf_dev_t;
typedef struct _gf_display *	gf_display_t;
typedef struct _gf_layer *		gf_layer_t;
typedef struct _gf_vcap *		gf_vcap_t;
typedef struct _gf_surface *	gf_surface_t;
typedef struct _gf_context *	gf_context_t;

#ifndef _WIN32
#include <_pack1.h>
#endif

typedef struct {
	_int32 x, y;
} gf_point_t;

typedef struct {
	_int32		ncolors;
	gf_color_t	*colors;
} gf_palette_t;

/* Supported pixel formats. Pixel formats are enumerated using the following
 * bitfields:
 * - Bits 0 - 6: Bits per pixel (GF_FORMAT_BPP) describes number of bits per
 *   pixel. Typically this value is 8, 16, 24 or 32
 * - Bits 7 - 9: Data formatting (GF_FORMAT_DATA) describes data organization,
 *   and the field is further subdivided as follows:
 *   - GF_FORMAT_PLANAR (bit 7) denotes planar organization (single plane for
 *     each channel)
 *   - GF_FORMAT_PACK (bits 8 - 9) denotes packed representation (channels
 *     packed into a short or long integer). Value of this field denotes
 *     endianness. Values for this field are 01 (GF_FORMAT_PKLE) for little-
 *     endian, 10 (GF_FORMAT_PKBE) for big-endian, or if both bits are set
 *     (GF_FORMAT_PACK) the packing is indeterminate.
 *   If all bits are 0, the data formatting is assumed to be a (potentially
 *   ordered) byte sequence.
 * - Bit 10: Alpha (GF_FORMAT_ALPHA) denotes the presence of an alpha channel
 * - Bits 11 - 23: Color space (GF_FORMAT_CSPACE) provides information on the
 *   color space of the data. Currently defined values include:
 *   - GF_FORMAT_PALETTE (bit 11 set): data are indices in a lookup table
 *   - GF_FORMAT_RGB (bit 12 set): RGB information embedded in data
 *   - GF_FORMAT_YUV (bit 13 set): YUV information embedded in data
 * - Bits 24 - 31: provides additional information whose meaning is dependent
 *   on the color space */

#define GF_FORMAT_BPP		0x0000007f
#define GF_FORMAT_DATA		0x00000380
#define GF_FORMAT_PLANAR	0x00000080
#define GF_FORMAT_PKLE		0x00000100
#define GF_FORMAT_PKBE		0x00000200
#define GF_FORMAT_PACK		(GF_FORMAT_PKLE | GF_FORMAT_PKBE)	
#define GF_FORMAT_ALPHA		0x00000400
#define GF_FORMAT_CSPACE	0x00fff800
#define GF_FORMAT_PALETTE	0x00000800
#define GF_FORMAT_RGB		0x00001000
#define GF_FORMAT_YUV		0x00002000
#define GF_FORMAT_SUBFORMAT	0xff000000

#define GF_FORMAT_BO_BGRA	0x00000000
#define GF_FORMAT_BO_ARGB	0x00000200	/* Byte order Big Endian */

/* packed YUV subformats */
#define GF_FORMAT_YUV_UYVY				0x01000000
#define GF_FORMAT_YUV_YUY2				0x02000000
#define GF_FORMAT_YUV_YVYU				0x03000000
#define GF_FORMAT_YUV_V422				0x04000000
#define GF_FORMAT_YUV_NV12				0x05000000	/* Y plane is immediately followed by packed UV plane */
#define GF_FORMAT_YUV_AYUV				0x06000000
#define GF_FORMAT_YUV_UYVY_INTERLACED	0x81000000
#define GF_FORMAT_YUV_YUY2_INTERLACED	0x82000000
#define GF_FORMAT_YUV_YVYU_INTERLACED	0x83000000
#define GF_FORMAT_YUV_V422_INTERLACED	0x84000000
#define GF_FORMAT_YUV_NV12_INTERLACED	0x85000000	/* Y plane is immediately followed by packed UV plane */
#define GF_FORMAT_YUV_AYUV_INTERLACED	0x86000000

/*
 * Planar YUV subformats.  Planar really means "data split across multiple
 * surfaces", hence NV12 is not considered planar, since the UV plane resides
 * in the same surface as the Y plane.
 */
#define GF_FORMAT_YUV_YVU9				0x01000000
#define GF_FORMAT_YUV_YV12				0x02000000
#define GF_FORMAT_YUV_420				0x03000000
#define GF_FORMAT_YUV_YVU9_INTERLACED	0x81000000
#define GF_FORMAT_YUV_YV12_INTERLACED	0x82000000
#define GF_FORMAT_YUV_420_INTERLACED	0x83000000

typedef enum {
	GF_FORMAT_INVALID = 0,
	GF_FORMAT_BYTE = 8,
	GF_FORMAT_PAL8 = 8 | GF_FORMAT_PALETTE,
	GF_FORMAT_PACK_ARGB1555 = 16 | GF_FORMAT_PACK | GF_FORMAT_ALPHA | GF_FORMAT_RGB,
	GF_FORMAT_PKLE_ARGB1555 = 16 | GF_FORMAT_PKLE | GF_FORMAT_ALPHA | GF_FORMAT_RGB,
	GF_FORMAT_PKBE_ARGB1555 = 16 | GF_FORMAT_PKBE | GF_FORMAT_ALPHA | GF_FORMAT_RGB,
	GF_FORMAT_PACK_RGB565 = 16 | GF_FORMAT_PACK | GF_FORMAT_RGB,
	GF_FORMAT_PKLE_RGB565 = 16 | GF_FORMAT_PKLE | GF_FORMAT_RGB,
	GF_FORMAT_PKBE_RGB565 = 16 | GF_FORMAT_PKBE | GF_FORMAT_RGB,
	GF_FORMAT_BGR888 = 24 | GF_FORMAT_RGB,
	GF_FORMAT_BGRA8888 = 32 | GF_FORMAT_ALPHA | GF_FORMAT_RGB | GF_FORMAT_BO_BGRA,
	GF_FORMAT_ARGB8888 = 32 | GF_FORMAT_ALPHA | GF_FORMAT_RGB | GF_FORMAT_BO_ARGB,
	GF_FORMAT_PACK_YUV_UYVY = 16 | GF_FORMAT_PACK | GF_FORMAT_YUV | GF_FORMAT_YUV_UYVY,
	GF_FORMAT_PKLE_YUV_UYVY = 16 | GF_FORMAT_PKLE | GF_FORMAT_YUV | GF_FORMAT_YUV_UYVY,
	GF_FORMAT_PKBE_YUV_UYVY = 16 | GF_FORMAT_PKBE | GF_FORMAT_YUV | GF_FORMAT_YUV_UYVY,
	GF_FORMAT_PACK_YUV_YUY2 = 16 | GF_FORMAT_PACK | GF_FORMAT_YUV | GF_FORMAT_YUV_YUY2,
	GF_FORMAT_PKLE_YUV_YUY2 = 16 | GF_FORMAT_PKLE | GF_FORMAT_YUV | GF_FORMAT_YUV_YUY2,
	GF_FORMAT_PKBE_YUV_YUY2 = 16 | GF_FORMAT_PKBE | GF_FORMAT_YUV | GF_FORMAT_YUV_YUY2,
	GF_FORMAT_PACK_YUV_YVYU = 16 | GF_FORMAT_PACK | GF_FORMAT_YUV | GF_FORMAT_YUV_YVYU,
	GF_FORMAT_PKLE_YUV_YVYU = 16 | GF_FORMAT_PKLE | GF_FORMAT_YUV | GF_FORMAT_YUV_YVYU,
	GF_FORMAT_PKBE_YUV_YVYU = 16 | GF_FORMAT_PKBE | GF_FORMAT_YUV | GF_FORMAT_YUV_YVYU,
	GF_FORMAT_PACK_YUV_V422 = 16 | GF_FORMAT_PACK | GF_FORMAT_YUV | GF_FORMAT_YUV_V422,
	GF_FORMAT_PKLE_YUV_V422 = 16 | GF_FORMAT_PKLE | GF_FORMAT_YUV | GF_FORMAT_YUV_V422,
	GF_FORMAT_PKBE_YUV_V422 = 16 | GF_FORMAT_PKBE | GF_FORMAT_YUV | GF_FORMAT_YUV_V422,
	GF_FORMAT_PACK_YUV_NV12 = 12 | GF_FORMAT_YUV | GF_FORMAT_YUV_NV12,
	GF_FORMAT_PACK_YUV_AYUV = 32 | GF_FORMAT_YUV | GF_FORMAT_YUV_AYUV,
	GF_FORMAT_PLANAR_YUV_YVU9 = 8 | GF_FORMAT_PLANAR | GF_FORMAT_YUV | GF_FORMAT_YUV_YVU9,
	GF_FORMAT_PLANAR_YUV_YV12 = 8 | GF_FORMAT_PLANAR | GF_FORMAT_YUV | GF_FORMAT_YUV_YV12,
	GF_FORMAT_PLANAR_YUV_420 = 8 | GF_FORMAT_PLANAR | GF_FORMAT_YUV | GF_FORMAT_YUV_420,

	/* interlaced formats */
	GF_FORMAT_PACK_YUV_UYVY_INTERLACED = 16 | GF_FORMAT_PACK | GF_FORMAT_YUV | GF_FORMAT_YUV_UYVY_INTERLACED,
	GF_FORMAT_PKLE_YUV_UYVY_INTERLACED = 16 | GF_FORMAT_PKLE | GF_FORMAT_YUV | GF_FORMAT_YUV_UYVY_INTERLACED,
	GF_FORMAT_PKBE_YUV_UYVY_INTERLACED = 16 | GF_FORMAT_PKBE | GF_FORMAT_YUV | GF_FORMAT_YUV_UYVY_INTERLACED,
	GF_FORMAT_PACK_YUV_YUY2_INTERLACED = 16 | GF_FORMAT_PACK | GF_FORMAT_YUV | GF_FORMAT_YUV_YUY2_INTERLACED,
	GF_FORMAT_PKLE_YUV_YUY2_INTERLACED = 16 | GF_FORMAT_PKLE | GF_FORMAT_YUV | GF_FORMAT_YUV_YUY2_INTERLACED,
	GF_FORMAT_PKBE_YUV_YUY2_INTERLACED = 16 | GF_FORMAT_PKBE | GF_FORMAT_YUV | GF_FORMAT_YUV_YUY2_INTERLACED,
	GF_FORMAT_PACK_YUV_YVYU_INTERLACED = 16 | GF_FORMAT_PACK | GF_FORMAT_YUV | GF_FORMAT_YUV_YVYU_INTERLACED,
	GF_FORMAT_PKLE_YUV_YVYU_INTERLACED = 16 | GF_FORMAT_PKLE | GF_FORMAT_YUV | GF_FORMAT_YUV_YVYU_INTERLACED,
	GF_FORMAT_PKBE_YUV_YVYU_INTERLACED = 16 | GF_FORMAT_PKBE | GF_FORMAT_YUV | GF_FORMAT_YUV_YVYU_INTERLACED,
	GF_FORMAT_PACK_YUV_V422_INTERLACED = 16 | GF_FORMAT_PACK | GF_FORMAT_YUV | GF_FORMAT_YUV_V422_INTERLACED,
	GF_FORMAT_PKLE_YUV_V422_INTERLACED = 16 | GF_FORMAT_PKLE | GF_FORMAT_YUV | GF_FORMAT_YUV_V422_INTERLACED,
	GF_FORMAT_PKBE_YUV_V422_INTERLACED = 16 | GF_FORMAT_PKBE | GF_FORMAT_YUV | GF_FORMAT_YUV_V422_INTERLACED,
	GF_FORMAT_PACK_YUV_NV12_INTERLACED = 12 | GF_FORMAT_YUV | GF_FORMAT_YUV_NV12_INTERLACED,
	GF_FORMAT_PACK_YUV_AYUV_INTERLACED = 32 | GF_FORMAT_YUV | GF_FORMAT_YUV_AYUV_INTERLACED,
	GF_FORMAT_PLANAR_YUV_YVU9_INTERLACED = 8 | GF_FORMAT_PLANAR | GF_FORMAT_YUV | GF_FORMAT_YUV_YVU9_INTERLACED,
	GF_FORMAT_PLANAR_YUV_YV12_INTERLACED = 8 | GF_FORMAT_PLANAR | GF_FORMAT_YUV | GF_FORMAT_YUV_YV12_INTERLACED,
	GF_FORMAT_PLANAR_YUV_420_INTERLACED = 8 | GF_FORMAT_PLANAR | GF_FORMAT_YUV | GF_FORMAT_YUV_420_INTERLACED,
} gf_format_t;

#if defined __BIGENDIAN__
	#define GF_FORMAT_PKHE_ARGB1555				GF_FORMAT_PKBE_ARGB1555
	#define GF_FORMAT_PKHE_RGB565				GF_FORMAT_PKBE_RGB565
	#define GF_FORMAT_PKHE_YUV_UYVY				GF_FORMAT_PKBE_YUV_UYVY
	#define GF_FORMAT_PKHE_YUV_YUY2				GF_FORMAT_PKBE_YUV_YUY2
	#define GF_FORMAT_PKHE_YUV_YVYU				GF_FORMAT_PKBE_YUV_YVYU
	#define GF_FORMAT_PKHE_YUV_V422				GF_FORMAT_PKBE_YUV_V422
	#define GF_FORMAT_PKHE_YUV_UYVY_INTERLACED	GF_FORMAT_PKBE_YUV_UYVY_INTERLACED
	#define GF_FORMAT_PKHE_YUV_YUY2_INTERLACED	GF_FORMAT_PKBE_YUV_YUY2_INTERLACED
	#define GF_FORMAT_PKHE_YUV_YVYU_INTERLACED	GF_FORMAT_PKBE_YUV_YVYU_INTERLACED
	#define GF_FORMAT_PKHE_YUV_V422_INTERLACED	GF_FORMAT_PKBE_YUV_V422_INTERLACED
#else
	#define GF_FORMAT_PKHE_ARGB1555				GF_FORMAT_PKLE_ARGB1555
	#define GF_FORMAT_PKHE_RGB565				GF_FORMAT_PKLE_RGB565
	#define GF_FORMAT_PKHE_YUV_UYVY				GF_FORMAT_PKLE_YUV_UYVY
	#define GF_FORMAT_PKHE_YUV_YUY2				GF_FORMAT_PKLE_YUV_YUY2
	#define GF_FORMAT_PKHE_YUV_YVYU				GF_FORMAT_PKLE_YUV_YVYU
	#define GF_FORMAT_PKHE_YUV_V422				GF_FORMAT_PKLE_YUV_V422
	#define GF_FORMAT_PKHE_YUV_UYVY_INTERLACED	GF_FORMAT_PKLE_YUV_UYVY_INTERLACED
	#define GF_FORMAT_PKHE_YUV_YUY2_INTERLACED	GF_FORMAT_PKLE_YUV_YUY2_INTERLACED
	#define GF_FORMAT_PKHE_YUV_YVYU_INTERLACED	GF_FORMAT_PKLE_YUV_YVYU_INTERLACED
	#define GF_FORMAT_PKHE_YUV_V422_INTERLACED	GF_FORMAT_PKLE_YUV_V422_INTERLACED
#endif

#define	GF_DEV_FLUSHRECT_DRVR	0x0001
#define	GF_DEV_LAYER_FLUSHRECT_DRVR	0x0002

typedef struct {
	_uint32		ndisplays;
	_uint32		flags;
	const char	*description;
	_uint32		vendor_id;
	_uint32		device_id;
	_int32		index;
	intptr_t	reserved[3];
} gf_dev_info_t;

typedef struct {
	_uint32		total_mem;
	_uint32		avail_mem;
	intptr_t	reserved[4];
} gf_mem_info_t;

typedef struct {
	_uint32		nlayers;
	_uint32		main_layer_index;
	_uint16		xres;
	_uint16 	yres;
	gf_format_t	format;
	_int32		refresh;
	intptr_t	reserved[6];
} gf_display_info_t;

typedef struct {
	gf_sid_t	sid;
	_int32		w, h;
	gf_format_t	format;
	_uint32		stride;
	_uint8		*vaddr;
	_uint64		paddr;
	gf_palette_t	palette;
	_uint32		flags;
	intptr_t	reserved[6];
} gf_surface_info_t;

typedef struct {
	gf_format_t		format;
	_uint32			caps;
	_uint32			alpha_valid_flags;
	_uint32			alpha_combinations;
	_uint64			order_caps;
	_uint32			chromakey_caps;
	_int32			src_max_height;
	_int32			src_max_width;
	_int32			src_max_viewport_height;
	_int32			src_max_viewport_width;
	_int32			dst_max_height;
	_int32			dst_max_width;
	_int32			dst_min_height;
	_int32			dst_min_width;
	_int32			max_scaleup_x;
	_int32			max_scaleup_y;
	_int32			max_scaledown_x;
	_int32			max_scaledown_y;
	_uint32			output_mask;
	_uint32			vcap_mask;
	intptr_t		reserved[6];
} gf_layer_info_t;

typedef struct {
	int			enabled;
	unsigned		reserved[3];
	struct {
		int		x1;
		int		y1;
		int		x2;
		int		y2;
	} src_vp;
	struct {
		int		x1;
		int		y1;
		int		x2;
		int		y2;
	} dst_vp;
	struct {
		unsigned	mode;
		int		m1;
		int		m2;
		unsigned	map_sid;
		unsigned	reserved[4];
	} blending;
	struct {
		unsigned	mode;
		unsigned	color0;
		unsigned	color1;
		unsigned	mask;
		unsigned	reserved[4];
	} chroma;
	unsigned		reserved1[8];
} gf_layer_state_t;

typedef enum {
	GF_CURSOR_BITMAP 
} gf_cursor_type_t;

typedef struct {
	gf_cursor_type_t type;
	gf_point_t	hotspot;
	union {
		struct {
			_int32			w, h;
			_int32			stride;
			gf_color_t		color0;
			const _uint8	*image0;
			const _uint8	*image1;
			gf_color_t		color1;
		} bitmap;
	} cursor;
} gf_cursor_t;

typedef struct {
	_uint32		mode;
	gf_color_t	color0;
	gf_color_t	color1;
	gf_color_t	mask;
	intptr_t	reserved[4];
} gf_chroma_t;

typedef struct {
	_uint32			mode;
	_uint32			map_x_offset, map_y_offset;
	gf_surface_t	map;
	_uint8			m1, m2;
	_uint16			padding;
	intptr_t	reserved[4];
} gf_alpha_t;

typedef struct {
	_uint32		flags;
	gf_format_t	primary_format;
	_uint32		xres, yres;
	_uint32		refresh[7];
	intptr_t	reserved[4];
} gf_modeinfo_t;

#ifndef _WIN32
#include <_packpop.h>
#endif

/* core API function prototypes */

/* device related */
extern int gf_dev_attach(gf_dev_t * pdev, const char *fname,gf_dev_info_t *info);
extern int gf_dev_select_zone(gf_dev_t gdev, uint32_t zone);
extern int gf_dev_register_thread(gf_dev_t gdev);
extern void gf_dev_detach(gf_dev_t gfx);
extern int gf_dev_get_error(gf_dev_t gdev);
extern int gf_dev_get_meminfo(gf_dev_t gdev, gf_mem_info_t * info);

/* display related */
extern int gf_display_query(gf_dev_t gdev, unsigned display_index, gf_display_info_t *info);
extern int gf_display_attach(gf_display_t * pdisplay, gf_dev_t gdev,unsigned display_index,gf_display_info_t *info);
extern void gf_display_detach(gf_display_t display);
extern int gf_display_set_layer_order(gf_display_t display, const unsigned order[], unsigned flags);
extern int gf_display_get_layer_order(gf_display_t display, int max_layers, unsigned order[]);
extern int gf_display_set_dpms(gf_display_t display, unsigned mode);
extern int gf_display_snapshot(gf_display_t display, int output,
    int x1, int y1, int x2, int y2, gf_surface_t surface);
extern int gf_display_query_mode(gf_display_t display, int index, gf_modeinfo_t *mode);
extern int gf_display_set_mode(gf_display_t display,
    int xres, int yres, int refresh, gf_format_t format, unsigned flags);
extern int gf_display_set_external_chroma(gf_display_t display,
    gf_chroma_t *chroma);
extern int gf_display_set_color_lut16(gf_display_t display, const uint16_t *redLUT,
    const uint16_t *greenLUT, const uint16_t *blueLUT);
extern int gf_display_wait_vsync(gf_display_t display);

/* layer related */
extern int gf_layer_query(gf_layer_t layer, int format_index, gf_layer_info_t *info);
extern int gf_layer_attach(gf_layer_t * player, gf_display_t display, unsigned layer_index, unsigned flags); 
extern void gf_layer_detach(gf_layer_t layer);
extern void gf_layer_enable(gf_layer_t layer);
extern void gf_layer_disable(gf_layer_t layer);
extern void gf_surface_init_array(gf_surface_t surface);
extern void gf_layer_set_chroma(gf_layer_t layer, const gf_chroma_t *chroma);
extern void gf_layer_set_blending(gf_layer_t layer, const gf_alpha_t *alpha);
extern void gf_layer_set_surfaces(gf_layer_t layer, gf_surface_t surfs[], unsigned nsurfs); 
extern void gf_layer_set_src_viewport(gf_layer_t layer,int x1,int y1,int x2,int y2);
extern void gf_layer_set_dst_viewport(gf_layer_t layer,int x1,int y1,int x2,int y2);
extern void gf_layer_set_brightness(gf_layer_t layer, int brightness);
extern void gf_layer_set_contrast(gf_layer_t layer, int contrast);
extern void gf_layer_set_saturation(gf_layer_t layer, int saturation);
extern void gf_layer_set_hue(gf_layer_t layer, int hue);
extern void gf_layer_set_filter(gf_layer_t layer, unsigned filter);
extern void gf_layer_set_outputs(gf_layer_t layer, uint32_t mask);
extern int gf_layer_update(gf_layer_t layer, unsigned flags);
extern int gf_layer_update_multi(gf_layer_t layer[], unsigned nlayers, unsigned flags);
extern unsigned gf_layer_choose_format(gf_layer_t layer, gf_format_t format[], size_t nformat, const unsigned *criteria); 
extern int gf_layer_query_state(gf_layer_t layer, gf_layer_state_t *state);
extern int gf_layer_flushrect(gf_layer_t layer, int x1, int y1, int x2, int y2);
extern void gf_layer_set_edge(gf_layer_t layer, unsigned edge);

/* Video Capture related */
extern int gf_vcap_attach(gf_vcap_t *pvcap, gf_dev_t gdev, unsigned vcap_index, unsigned flags); 
extern void gf_vcap_detach(gf_vcap_t vcap);
extern void gf_vcap_enable(gf_vcap_t vcap);
extern void gf_vcap_disable(gf_vcap_t vcap);
extern void gf_vcap_set_input_source(gf_vcap_t vcap, int source_index);
extern void gf_vcap_set_input_dimensions(gf_vcap_t vcap, int width, int height);
extern void gf_vcap_set_input_viewport(gf_vcap_t vcap, int x1, int y1, int x2, int y2);
extern void gf_vcap_set_output_dimensions(gf_vcap_t vcap, int width, int height);
extern void gf_vcap_set_sync_values(gf_vcap_t vcap, int h_offset, int v_offset, int h_total, int v_total);
extern void gf_vcap_set_flags(gf_vcap_t vcap, unsigned flags);
extern void gf_vcap_set_brightness(gf_vcap_t vcap, int brightness);
extern void gf_vcap_set_contrast(gf_vcap_t vcap, int contrast);
extern void gf_vcap_set_saturation(gf_vcap_t vcap, int saturation);
extern void gf_vcap_set_hue(gf_vcap_t vcap, int hue);
extern void gf_vcap_bind_to_layer(gf_vcap_t vcap, gf_layer_t layer);
extern int gf_vcap_update(gf_vcap_t vcap, unsigned flags);
 
/* surface related */
extern int gf_surface_create(gf_surface_t *psurface, gf_dev_t gfx,int w,int h,gf_format_t format,const gf_palette_t *palette,unsigned flags);
extern int gf_surface_create_layer(gf_surface_t *psurface, gf_layer_t *layers,int nlayers,int surface_index,int w,int h,gf_format_t format,const gf_palette_t *palette,unsigned flags);
extern int gf_surface_attach(gf_surface_t *psurface, gf_dev_t gfx,int w,int h,int stride,gf_format_t format,const gf_palette_t *palette,uint8_t *ptr,unsigned flags);
extern int gf_surface_reattach(gf_surface_t surface, int w, int h, int stride, const gf_palette_t *palette, uint8_t *ptr, unsigned flags);
extern int gf_surface_attach_by_sid(gf_surface_t * psurface, gf_dev_t gfx, gf_sid_t sid);
extern gf_surface_info_t *gf_surface_get_info(gf_surface_t surface,gf_surface_info_t *info);
extern void gf_surface_free(gf_surface_t surface);
extern unsigned gf_surface_sidlist(gf_dev_t gdev, unsigned * list);
extern int gf_surface_get_dev(gf_surface_t surface, gf_dev_t * pdev);

/* context related */
extern int gf_context_create(gf_context_t * pcontext);
extern void gf_context_init(gf_context_t context);
extern void gf_context_free(gf_context_t context);
extern gf_color_t gf_context_set_fgcolor(gf_context_t context,gf_color_t color);
extern void gf_context_set_fgcolor_native(gf_context_t context,unsigned color);
extern gf_color_t gf_context_set_bgcolor(gf_context_t context,gf_color_t color);
extern void gf_context_set_bgcolor_native(gf_context_t context,unsigned color);
extern int gf_context_set_clipping(gf_context_t context,unsigned x1,unsigned y1,unsigned x2,unsigned y2);
extern void gf_context_disable_clipping(gf_context_t context);
extern unsigned gf_context_set_penwidth(gf_context_t context,unsigned w);
extern _uint8 gf_context_set_rop(gf_context_t context,_uint8 rop);
extern void gf_context_set_pattern(gf_context_t context,const _uint8 *pattern,unsigned x_offset,unsigned y_offset,unsigned flags); 
extern void gf_context_disable_pattern(gf_context_t context);
extern void gf_context_set_chroma(gf_context_t context,const gf_chroma_t *chroma);
extern void gf_context_disable_chroma(gf_context_t context);
extern void gf_context_set_alpha(gf_context_t context,gf_alpha_t const *alpha);
extern void gf_context_disable_alpha(gf_context_t context);
extern void gf_context_set_transform(gf_context_t context,const gf_fixed_t *xform_matrix);
extern void gf_context_disable_transform(gf_context_t context);
extern void gf_context_set_translation(gf_context_t context,int tx,int ty);
extern void gf_context_disable_translation(gf_context_t context);
extern void gf_context_set_linedash(gf_context_t context,_uint32 line_pat,unsigned line_pat_offset,int line_repeat,unsigned flags);
extern void gf_context_disable_linedash(gf_context_t context);
extern void gf_context_set_linejoin(gf_context_t context,int line_join);
extern void gf_context_set_capstyle(gf_context_t context, int cap_style);
extern void gf_context_set_antialias(gf_context_t context,unsigned flags);
extern void gf_context_disable_antialias(gf_context_t context,unsigned flags);
extern void gf_context_set_filter(gf_context_t context,unsigned filter);
extern int gf_context_set_surface(gf_context_t context,gf_surface_t surface);
extern void gf_context_set_polyfill(gf_context_t context, int polyfill);
extern void gf_context_set_planemask(gf_context_t context, unsigned planemask);
extern void gf_context_disable_planemask(gf_context_t context);
extern int gf_context_unset_surface(gf_context_t context);
extern int gf_context_set_flushrect(gf_context_t context, 
	unsigned x1, unsigned y1,
	unsigned x2, unsigned y2);
extern void gf_context_disable_flushrect(gf_context_t context);
extern void gf_context_set_dst_alpha(gf_context_t context, const gf_alpha_t *alpha);
extern void gf_context_disable_dst_alpha(gf_context_t context);
extern int gf_context_get_surface(gf_context_t context, gf_surface_t * psurface);

/* rendering function */
extern int gf_draw_begin(gf_context_t context);
extern void gf_draw_end(gf_context_t context);
/*
extern void gf_draw_elliptical_arc(gf_context_t context, const gf_point_t *ptc,
									int rh, int rv, fxpt_real rot_angle, 
									fxpt_real s_angle, fxpt_real e_angle, int nflag);*/
extern void gf_draw_wu_line(gf_context_t context, gf_point_t *p1, gf_point_t *p2);
extern int gf_draw_rect(gf_context_t context,int x1,int y1,int x2,int y2);
extern int gf_draw_span(gf_context_t context,int x1,int x2,int y);
extern int gf_draw_spanlist(gf_context_t context,unsigned nspans,int x1[],int x2[],int y[]);
extern int gf_draw_cubic_bezier(gf_context_t context, gf_point_t *ctrlPts);
extern void gf_quad_to_cubic(gf_point_t *pt);
extern int gf_draw_poly_fill(gf_context_t context,const gf_point_t *pts,size_t npoints);
extern int gf_draw_polyline(gf_context_t context,const gf_point_t *pts,size_t npoints,uint32_t flags);
extern int gf_draw_blit1(gf_context_t context,int sx1,int sy1,int sx2,int sy2,int dx,int dy);
extern int gf_draw_blit2(gf_context_t context, 
							gf_surface_t ssurface,gf_surface_t dsurface,
							int sx1,int sy1,int sx2,int sy2,
							int dx,int dy);
extern int gf_draw_blitscaled(
		gf_context_t context,gf_surface_t ssurface,gf_surface_t dsurface,
		int sx1,int sy1,int sx2,int sy2,
		int dx1,int dy1,int dx2,int dy2);
extern int gf_draw_flush(gf_context_t context);
extern int gf_draw_finish(gf_context_t context);
extern int gf_draw_bitmap(gf_context_t context, const uint8_t *image,
		unsigned stride, unsigned bit0_offset,
		int x, int y, unsigned w, unsigned h, unsigned flags);
extern int gf_draw_image(gf_context_t context, const uint8_t *pixels,
		gf_format_t format, unsigned stride, int x, int y,
		unsigned w, unsigned h, unsigned flags);

/* h/w cursor manipulation */
extern int gf_cursor_set(gf_display_t display,unsigned cursor_index,const gf_cursor_t *cursor);
extern int gf_cursor_enable(gf_display_t display,unsigned cursor_index);
extern int gf_cursor_disable(gf_display_t display,unsigned cursor_index);
extern int gf_cursor_set_pos(gf_display_t display,unsigned cursor_index,int x,int y);

/* I2C bus access */
int gf_i2c_read(gf_dev_t gdev,
    int busno, int slaveaddr, uint8_t *idata, int ibytes);
int gf_i2c_write(gf_dev_t gdev,
    int busno, int slaveaddr, uint8_t *odata, int obytes);
int gf_i2c_writeread(gf_dev_t gdev, int busno,
    int slaveaddr, uint8_t *odata, int obytes, uint8_t *idata, int ibytes);

__END_DECLS

/* Version consists of 3 bytes.  e.g. 2.5.1 would be 0x0020501 */
#define GF_VERSION			0x00010100

#define GF_SID_INVALID				(~0)

#define GF_DEVICE_INDEX(n)			(n < 64 ? (const char*)(n) : "")

/* gf_layer_attach() flag manifests */
#define GF_LAYER_ATTACH_PASSIVE		0x00000001
#define GF_LAYER_ATTACH_NODEFAULTS	0x00000002
#define GF_LAYER_ATTACH_NOAUTODISABLE	0x00000004

/* gf_layer_update() flag manifests */
#define GF_LAYER_UPDATE_NO_WAIT_VSYNC	0x00000001
#define GF_LAYER_UPDATE_NO_WAIT_IDLE	0x00000002

/* gf_layer_set_filter() flag manifests */
#define GF_LAYER_FILTER_NONE		0x00000001
#define GF_LAYER_FILTER_FASTER		0x00000002
#define GF_LAYER_FILTER_BETTER		0x00000003

/* gf_layer_set_edge() flag manifests */
#define GF_LAYER_EDGE_NONE			0x00000001
#define GF_LAYER_EDGE_CLAMP			0x00000002
#define GF_LAYER_EDGE_WRAP			0x00000003

/* gf_vcap_set_flags() flag manifests */
#define GF_VCAP_FLAG_DEINTERLACE_WEAVE		0x00000001
#define GF_VCAP_FLAG_DEINTERLACE_BOB		0x00000002
#define GF_VCAP_FLAG_DEINTERLACE_ODD_ONLY	0x00000004
#define GF_VCAP_FLAG_DEINTERLACE_EVEN_ONLY	0x00000008

/* gf_vcap_update() flag manifests */
#define GF_VCAP_UPDATE_NO_WAIT_VSYNC		0x00000001

/* gf_draw_polyline() flag manifests */
#define GF_DRAW_POLYLINE_CLOSED			0x00000001

/* gf_draw_bitmap() flag manifests */
#define GF_DRAW_BITMAP_BACKFILL			0x00000001

/* gf_context_set_linejoin() line joint manifests */
#define GF_CONTEXT_LINEJOIN_BUTT		0
#define GF_CONTEXT_LINEJOIN_BEVEL		1
#define GF_CONTEXT_LINEJOIN_ROUND		2
#define GF_CONTEXT_LINEJOIN_MITER		3

/* gf_context_set_capstyle() thick line cap styles */
#define GF_CONTEXT_CAPSTYLE_BUTT		0
#define GF_CONTEXT_CAPSTYLE_ROUND		1
#define GF_CONTEXT_CAPSTYLE_SQUARE		2

/* gf_context_set_polyfill() polygon winding rules */
#define GF_CONTEXT_POLYFILL_EVENODD		0
#define GF_CONTEXT_POLYFILL_NONZERO		1
#define GF_CONTEXT_POLYFILL_CONVEX		2
#define GF_CONTEXT_POLYFILL_MONOTONE		3

/* gf_context_set_linedash() flag manifests */
#define GF_CONTEXT_LINEDASH_BACKFILL	0x00000001

/* gf_context_set_pattern() flag manifests */
#define GF_CONTEXT_PATTERN_BACKFILL		0x00000020
#define GF_CONTEXT_PATTERN_8X1			0x80000000	/* Unsupported! */

/* gf_context_set_antialias() flag manifests */
#define GF_CONTEXT_ANTIALIAS_LINES	0x00000001
#define GF_CONTEXT_ANTIALIAS_POLYFILL	0x00000002
#define	GF_CONTEXT_ANTIALIAS_SOFT		0x00000004

/* gf_context_set_filter() type manifests */
#define GF_CONTEXT_FILTER_NONE		0x00000001
#define GF_CONTEXT_FILTER_FASTER	0x00000002
#define GF_CONTEXT_FILTER_BETTER	0x00000003

/* gf_surface_create_*() flag manifests */
#define GF_SURFACE_CREATE_2D_ACCESSIBLE			0x00000001
#define GF_SURFACE_CREATE_3D_ACCESSIBLE			0x00000002
#define GF_SURFACE_CREATE_CPU_LINEAR_ACCESSIBLE	0x00000004
#define GF_SURFACE_CREATE_CPU_FAST_ACCESS		0x00000008
#define GF_SURFACE_CREATE_PHYS_CONTIG			0x00000010
#define GF_SURFACE_CREATE_PAGE_ALIGNED			0x00000020
#define GF_SURFACE_CREATE_ALPHA_MAP			0x00000040
#define GF_SURFACE_CREATE_SHAREABLE			0x00000080
#define GF_SURFACE_CREATE_VG_ACCESSIBLE		0x00000100
#define GF_SURFACE_CREATE_MULTISAMPLED		0x00000200

/* gf_display_set_dpms() mode manifests */
#define GF_DPMS_ON						0x00000000
#define GF_DPMS_STANDBY					0x00000001
#define GF_DPMS_SUSPEND					0x00000002
#define GF_DPMS_OFF						0x00000004

/* gf_surface_info_t flag manifests */
#define	GF_SURFACE_DISPLAYABLE			0x00000001
#define	GF_SURFACE_CPU_LINEAR_READABLE	0x00000002
#define	GF_SURFACE_CPU_LINEAR_WRITEABLE	0x00000004
#define	GF_SURFACE_2D_READABLE			0x00000008
#define	GF_SURFACE_3D_READABLE			0x00000010
#define	GF_SURFACE_2D_TARGETABLE		0x00000020
#define	GF_SURFACE_3D_TARGETABLE		0x00000040
#define	GF_SURFACE_SCALER_DISPLAYABLE	0x00000080
#define	GF_SURFACE_VMI_TARGETABLE		0x00000100
#define GF_SURFACE_DMA_SAFE				0x00000200
#define GF_SURFACE_PAGE_ALIGNED			0x00000400
#define GF_SURFACE_MULTISAMPLED			0x00000800
#define GF_SURFACE_BYTES_REVERSED		0x00001000
#define GF_SURFACE_NON_CACHEABLE		0x00002000
#define GF_SURFACE_WT_CACHEABLE			0x00004000
#define GF_SURFACE_PHYS_CONTIG			0x00008000
#define GF_SURFACE_DRIVER_NOT_OWNER		0x00010000
#define GF_SURFACE_ALPHA_MAP			0x00020000
#define GF_SURFACE_VG_READABLE			0x00040000
#define GF_SURFACE_VG_TARGETABLE		0x00080000

/* gf_layer_info_t caps manifests */
#define GF_LAYER_CAP_FILTER				0x00000001
#define GF_LAYER_CAP_SCALE_REPLICATE	0x00000002
#define GF_LAYER_CAP_PAN_SOURCE			0x00000004
#define GF_LAYER_CAP_SIZE_DEST			0x00000008
#define GF_LAYER_CAP_PAN_DEST			0x00000010
#define GF_LAYER_CAP_EDGE_CLAMP			0x00000020
#define GF_LAYER_CAP_EDGE_WRAP			0x00000040
#define GF_LAYER_CAP_DISABLE			0x00000080
#define GF_LAYER_CAP_SET_BRIGHTNESS		0x00000100
#define GF_LAYER_CAP_SET_CONTRAST		0x00000200
#define GF_LAYER_CAP_SET_SATURATION		0x00000400
#define GF_LAYER_CAP_ALPHA_WITH_CHROMA	0x00000800
#define GF_LAYER_CAP_PAN_DEST_NEGATIVE	0x00002000
#define GF_LAYER_CAP_SET_HUE			0x00004000
#define GF_LAYER_CAP_MAIN_DISPLAY		0x80000000

/* gf_layer_info_t chromakey_caps manifests */
#define GF_LAYER_CHROMAKEY_CAP_SRC_SINGLE	0x00000001
#define GF_LAYER_CHROMAKEY_CAP_SRC_RANGE	0x00000002
#define GF_LAYER_CHROMAKEY_CAP_SRC_MASK		0x00000004
#define GF_LAYER_CHROMAKEY_CAP_DST_SINGLE	0x00000100
#define GF_LAYER_CHROMAKEY_CAP_DST_RANGE	0x00000200
#define GF_LAYER_CHROMAKEY_CAP_DST_MASK		0x00000400
#define GF_LAYER_CHROMAKEY_CAP_SHOWTHROUGH	0x00000800
#define GF_LAYER_CHROMAKEY_CAP_BLOCK		0x00001000

/* gf_layer_info_t alpha_combinations manifests */
#define GF_ALPHA_CAP_SPP_WITH_GLOBAL	0x00000001
#define GF_ALPHA_CAP_GLOBAL_WITH_DPP	0x00000002
#define GF_ALPHA_CAP_SPP_WITH_DPP		0x00000004
#define GF_ALPHA_CAP_GLOBAL_WITH_GLOBAL	0x00000008

/* gf_layer_choose_format criteria manifests */
#define GF_NONE							0
#define GF_2D_RENDERABLE				1
#define GF_RED_SIZE						2
#define GF_GREEN_SIZE					3
#define GF_BLUE_SIZE					4
#define GF_ALPHA_SIZE					5

/* gf_modeinfo_t flags manifests */
#define	GF_MODE_GENERIC				0x00020000

#define GF_TRUE							~0
#define GF_FALSE						0

/* gf_chroma_t mode manifests */
#define GF_CHROMA_OP_SRC_MATCH			0x00000001
#define GF_CHROMA_OP_DST_MATCH			0x00000002
#define GF_CHROMA_OP_DRAW				0x00000004
#define GF_CHROMA_OP_NO_DRAW			0x00000008

/* Alpha Blending multiplier origins */
#define GF_ALPHA_M1_SRC_PIXEL_ALPHA		0x00010000	/* M1 from source pixel alpha component */
#define GF_ALPHA_M1_DST_PIXEL_ALPHA		0x00020000	/* M1 from destination pixel alpha component */
#define GF_ALPHA_M1_GLOBAL				0x00040000	/* M1 from the global M1 */
#define GF_ALPHA_M1_MAP					0x00080000	/* "M1" comes from the Alpha map */
#define GF_ALPHA_M2_SRC_PIXEL_ALPHA		0x01000000	/* "M2" comes from the source pixels alpha component */
#define GF_ALPHA_M2_DST_PIXEL_ALPHA		0x02000000	/* "M2" comes from the destination pixels alpha component */
#define GF_ALPHA_M2_GLOBAL				0x04000000	/* "M2" comes from the global multiplier 2 */
#define GF_ALPHA_M2_MAP					0x08000000	/* "M2" comes from the Alpha map */
#define GF_ALPHA_MERGE					0x20000000	/* Experimental - unsupported */

/* Alpha Blending Source Factor */
#define GF_BLEND_SRC_0					0x00000000	/* (0,0,0,0) */
#define GF_BLEND_SRC_M1					0x00000100	/* (M1,M1,M1,M1) */
#define GF_BLEND_SRC_1mM1				0x00000200	/* (1-M1,1-M1,1-M1,1-M1) */
#define GF_BLEND_SRC_1mD 				0x00000300	/* (1-M2,1-Rd,1-Gd,1-Bd) */
#define GF_BLEND_SRC_M2					0x00000400	/* (M2,M2,M2,M2) */
#define GF_BLEND_SRC_D					0x00000500	/* (M2,Rd,Gd,Bd) */
#define GF_BLEND_SRC_1					0x00000600	/* (1,1,1,1) */
#define GF_BLEND_SRC_A1M1				0x00000700	/* (1,M1,M1,M1) */
#define GF_BLEND_SRC_1mM2				0x00000800	/* (1-M2,1-M2,1-M2,1-M2) */
#define GF_BLEND_SRC_1mA1M1				0x00000900	/* (1-1,1-M1,1-M1,1-M1) */
#define GF_BLEND_SRC_A1M2				0x00000A00	/* (1,M2,M2,M2) */
#define GF_BLEND_SRC_1mA1M2				0x00000B00	/* (1-1,1-M2,1-M2,1-M2) */
#define GF_BLEND_SRC_A0M1				0x00000C00	/* (0,M1,M1,M1) */
#define GF_BLEND_SRC_1mA0M1				0x00000D00	/* (1-0,1-M1,1-M1,1-M1) */
#define GF_BLEND_SRC_A0M2				0x00000E00	/* (0,M2,M2,M2) */
#define GF_BLEND_SRC_1mA0M2				0x00000F00	/* (1-0,1-M2,1-M2,1-M2) */

/* Alpha Blending Destination Factor */
#define GF_BLEND_DST_0					0x00000000	/* (0,0,0,0) */
#define GF_BLEND_DST_M1					0x00000001	/* (M1,M1,M1,M1) */
#define GF_BLEND_DST_1mM1				0x00000002	/* (1-M1,1-M1,1-M1,1-M1) */
#define GF_BLEND_DST_1mS 				0x00000003	/* (1-M1,1-Rs,1-Gs,1-Bs) */
#define GF_BLEND_DST_M2					0x00000004	/* (M2,M2,M2,M2) */
#define GF_BLEND_DST_S					0x00000005	/* (M1,Rs,Gs,Bs) */
#define GF_BLEND_DST_1					0x00000006	/* (1,1,1,1) */
#define GF_BLEND_DST_A1M1				0x00000007	/* (1,M1,M1,M1) */
#define GF_BLEND_DST_1mM2				0x00000008	/* (1-M2,1-M2,1-M2,1-M2) */
#define GF_BLEND_DST_1mA1M1				0x00000009	/* (1-1,1-M1,1-M1,1-M1) */
#define GF_BLEND_DST_A1M2				0x0000000A	/* (1,M2,M2,M2) */
#define GF_BLEND_DST_1mA1M2				0x0000000B	/* (1-1,1-M2,1-M2,1-M2) */
#define GF_BLEND_DST_A0M1				0x0000000C	/* (0,M1,M1,M1) */
#define GF_BLEND_DST_1mA0M1				0x0000000D	/* (1-0,1-M1,1-M1,1-M1) */
#define GF_BLEND_DST_A0M2				0x0000000E	/* (0,M2,M2,M2) */
#define GF_BLEND_DST_1mA0M2				0x0000000F	/* (1-0,1-M2,1-M2,1-M2) */

/* Alpha Tests Pixels are written in destination */
#define GF_TEST_NEVER					0x00000000	/* Never */
#define GF_TEST_ALWAYS					0x00000001	/* Always */
#define GF_TEST_LESS_THAN				0x00000002	/* if M1 < M2 */
#define GF_TEST_LESS_THAN_OR_EQUAL		0x00000003	/* if M1 <= M2 */
#define GF_TEST_EQUAL					0x00000004	/* if M1 == M2 */
#define GF_TEST_GREATER_THAN_OR_EQUAL	0x00000005	/* if M1 >= M2 */
#define GF_TEST_GREATER_THAN			0x00000006	/* if M1 > M2*/
#define GF_TEST_NOT_EQUAL				0x00000007	/* if M1 != M2 */

#ifndef _GF_GF_ROP_H_INCLUDED
#include <gf/gf_rop.h>
#endif

#ifndef _GF_GF_ERRNO_H_INCLUDED
#include <gf/gf_errno.h>
#endif

#endif /* _GF_GF_H_INCLUDED */

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/gf/public/gf/gf.h $ $Rev: 257167 $" )
