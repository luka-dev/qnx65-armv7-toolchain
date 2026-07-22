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
 *	PtMultiText.h
 *		Header file for the PtText widget class
 *

 */
#ifndef __PT_MULTITEXT_H_INCLUDED
#define __PT_MULTITEXT_H_INCLUDED

#ifndef __PT_TEXT_H_INCLUDED
 #include <photon/PtText.h>
#endif

#ifndef __PT_COMPOUND_H_INCLUDED
 #include <photon/PtCompound.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtMultiText public
 */

extern PtWidgetClassRef_t *PtMultiText;

#define Pt_MULTITEXT_ID	5

/* Resources */
#define Pt_ARG_MULTITEXT_RANGE_ATTRIBUTES	Pt_RESOURCE( 5, 0 )
#define Pt_ARG_MULTITEXT_WRAP_FLAGS			Pt_RESOURCE( 5, 1 )
#define Pt_ARG_MLTITXT_FLAGS				Pt_RESOURCE( 5, 2 ) /*deprecated*/
#define Pt_ARG_MULTITEXT_LINE_SPACING		Pt_RESOURCE( 5, 3 )
#define Pt_ARG_MULTITEXT_SEGMENTS			Pt_RESOURCE( 5, 4 )
#define Pt_ARG_MULTITEXT_NUM_LINES_VISIBLE	Pt_RESOURCE( 5, 5 )
#define Pt_ARG_MULTITEXT_NUM_LINES			Pt_RESOURCE( 5, 6 )
#define Pt_ARG_MULTITEXT_TOP_LINE			Pt_RESOURCE( 5, 7 )
#define Pt_ARG_MULTITEXT_Y_SCROLL_POS 		Pt_RESOURCE( 5, 7 )
#define Pt_ARG_MULTITEXT_BOTTOM_LINE		Pt_RESOURCE( 5, 8 )
#define Pt_ARG_MULTITEXT_X_SCROLL_POS 		Pt_RESOURCE( 5, 9 )
#define Pt_ARG_MULTITEXT_QUERY_LINE 		Pt_RESOURCE( 5, 10 )
#define Pt_ARG_MULTITEXT_QUERY_CHARACTER	Pt_RESOURCE( 5, 11 )
#define Pt_ARG_MULTITEXT_ROWS				Pt_RESOURCE( 5, 12 )
#define Pt_ARG_MULTITEXT_TABS				Pt_RESOURCE( 5, 13 )
#define Pt_CB_MULTITEXT_SCROLLUPDATE		Pt_RESOURCE( 5, 14 )
#define Pt_ARG_MULTITEXT_FLAGS				Pt_RESOURCE( 5, 15 )
/* MultiText Flags bits */
#define Pt_EMT_AUTOINDENT			0x00000010
#define Pt_EMT_FULL_LINES			0x00000020 
	/* only draw a line if its ascender and descender fit */
#define Pt_EMT_FORCED_SCROLL		0x00000040 
	/* will cause scroll down if there is blank space at the bottom  */
	/* of the widget and there are lines above the top of the widget. */
#define Pt_EMT_NO_TABS				0x00000080
#define Pt_EMT_FOCUSED					0x20000000
#define Pt_EMT_DISABLE_PURGE		0x40000000
#define Pt_EMT_SCROLL_TO_CURSOR		0x80000000 
 /* enables cursor tracking */

#define Pt_EMT_READ_ONLY_FLAGS			Pt_EMT_DISABLE_PURGE | Pt_EMT_FOCUSED

/* Wrap flag bits */
#define Pt_EMT_WORD					0x01 /* default (overrides char wrap) */
#define Pt_EMT_CHAR					0x02
#define Pt_EMT_NEWLINE				0x04

/* Segment flag bits */
#define	Pt_MT_RIGHT					0x00000001
#define	Pt_MT_CENTER				0x00000002
#define	Pt_MT_LEFT					0x00000004
#define Pt_MT_ALIGN_BITS			0x00000007
#define Pt_MERGE_PREV				0x40000000 /*internal use only */
#define Pt_MERGE_NEXT				0x80000000 /*internal use only */
/* +wrap flag bits not currently supported. */

/******************************************************/
/* Segment append types */
/* FOR PtMultiTextModifyText() CALL... */

/*New segment attribute flags  see PtMultiTextModifyText(); */
#define Pt_MT_FONT						0x0001
#define Pt_MT_FOREGROUND 		0x0002
#define Pt_MT_TEXT_COLOR 		0x0002
#define Pt_MT_BACKGROUND		0x0004
#define Pt_MT_BACKGROUND_COLOR	0x0004
#define Pt_MT_TAG				0x0008
#define Pt_MT_FLAGS				0x0010

/*****************************************************/

/* struct used to specify complex strings */
typedef struct
{
	char 		*string;
	char 		*font;
	PgColor_t	text_color;
	PgColor_t	background_color;
} PtMultiLines_t;	

typedef struct
{
	char *			font;
	PgColor_t		text_color;
	PgColor_t		background_color;
	int					flags;
	void *			tag;

} PtMultiTextAttributes_t;

typedef struct Pt_emt_text_segment
{
	PtMultiTextAttributes_t attrs;
	int 			first_char;
	int				num_chars;
	struct Pt_emt_text_segment *prev;
	struct Pt_emt_text_segment *next;
} PtMultiTextSegment_t;	

typedef struct Pt_emt_text_line
{
	unsigned int			first_char;
	unsigned int 			byte_offset;
	ushort_t				num_chars;
	PhRect_t				extent;
	PtMultiTextSegment_t 	*segment;
	struct Pt_emt_text_line *prev;
	struct Pt_emt_text_line *next;
} PtMultiTextLine_t;

/* Callback structure */
typedef struct
{
	PtTextCallback_t	tc;
	PtMultiTextAttributes_t const *attributes;
	PtMultiTextSegment_t *seg;
	void *extended_data;
} PtMultiTextCallback_t;

/* Struct used to specify actions or request data */
typedef PtMultiTextCallback_t PtMultiTextControl_t;

/* Callback structure (pt_cb_multitext_scrollupdate ) */
typedef struct
	{
	int	cur_insert;
	int num_lines;
	int num_lines_visible;
	int top_line_num;
	int visible_width;
	int max_line_width;
	int scroll_pos_x;
	} PtEMTScrollUpdateCallback_t;
/* Reason_subtype bits */
#define Pt_MT_UPDATE_Y_SCROLLBAR	1
#define Pt_MT_UPDATE_X_SCROLLBAR	2
#define Pt_MT_UPDATE_POS_ONLY 		4

/* Struct information FROM the widget is provided in */
/* ie in recipient in PtGetResources. */
typedef PtMultiTextControl_t PtMultiTextInfo_t;

/* Struct for querying position info */
typedef struct
{
	int character_number;
	int line_number;
	PtMultiTextLine_t *line;
	PtMultiTextSegment_t *segment;
	char *character;
} PtMultiTextQuery_t;

/*
 * PtMultiText private
 */
/* Widget structure */
typedef struct
{
	PtTextWidget_t			text;
	PtMultiTextSegment_t	*segment; 	/*first segment */
	PtMultiTextLine_t		*line; 		/*first line */
	PtMultiTextLine_t		*top_line;
	int						top_line_num;
	PtMultiTextLine_t		*bottom_line;
	PtMultiTextLine_t		*last_line;
	int						num_bytes;
	int						num_chars;
	unsigned				num_lines;
	short					visible_lines;
	ushort_t				wrap_flags;
	ulong_t					flags;
	ushort_t				rows;
	PtMultiTextLine_t		*cursor_row;
	unsigned				cursor_line_num;
	PtMultiTextSegment_t	*cursor_seg;
	char					*old_text;
	struct{ 
		PtMultiTextLine_t 	*first, *last; 
		PhTile_t			*trans_damage;
	} 						reserved0;	/* damaged; */
	PhRect_t 				reserved1; 	/* blit_rect; */
	PhPoint_t				reserved2;	/* blit_delta; */
	PgColor_t				nofocus_highlight_color;
	int						*tabs;
	int						num_tabs;
	short					scroll_pos_x;
	int						max_x;
	PtMultiTextLine_t		*max_x_line;
} PtMultiTextWidget_t;

/* Widget union */
typedef union Pt_multitext_union {
	PtWidget_t				core;
	PtBasicWidget_t			basic;
	PtLabelWidget_t			label;
	PtTextWidget_t			text;
	PtMultiTextWidget_t		multitext;
} PtMultiTextUnion_t;

/* Widget structure */
typedef struct
{
	PtCompoundWidget_t		compound;
	PtWidget_t 				*mtext;
	PtWidget_t 				*y_scrollbar;
	PtWidget_t 				*x_scrollbar;
	PtWidget_t 				*spacer;
	short					display_y_scrollbar;
	short					display_x_scrollbar;
	int						flags;
	PtCallbackList_t		*lost_focus_cb, *got_focus_cb;	
} PtMTextWidget_t;

/* MultiText Compound flags */
#define Pt_CMT_SCROLL_CB_ACTIVE	0x40000000 /* (r/o) */ 
#define Pt_CMT_IN_UPDATE		0x80000000 /* (r/o) */ 

/* Widget union */
typedef union Pt_mtext_union {
	PtWidget_t				core;
	PtBasicWidget_t			basic;
	PtContainerWidget_t		container;
	PtCompoundWidget_t		compound;
	PtMTextWidget_t			mtext;
} PtMTextUnion_t;

/*+
 * MultiText Proto's
 */ 
extern void
	PtMultiTextModifyText( PtWidget_t *, int start, int end, int cur_insert, 
		char const *text, int characters , PtMultiTextAttributes_t const *, int attr_mask);
extern void
	PtMultiTextModifyAttributes( PtWidget_t *, int start, int end
		, PtMultiTextAttributes_t const *, int attr_mask);
extern PtMultiTextAttributes_t * 
	PtMultiTextGetAttributes( PtWidget_t *multitext, 
		int offset, PtMultiTextAttributes_t *attr, int *start, int *end);
extern PtMultiTextAttributes_t *
	PtMultiTextCreateAttributes( PtMultiTextAttributes_t *);
extern int 
	PtMultiTextInfo( PtWidget_t *, int query_type, int *offset, int *line_num,
		PtMultiTextLine_t *, int *start, int *end, int *length, 
		PtMultiTextSegment_t *, PtMultiTextAttributes_t *);

#define Pt_MT_QUERY_CHAR	0
#define Pt_MT_QUERY_LINE	1

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif


#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtMultiText.h $ $Rev: 219996 $" )
#endif
