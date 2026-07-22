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
 *	PtTerm.h
 *		Header file for the PtTerminal widget class
 *

 */
#ifndef __PT_TERMINAL_H_INCLUDED
#define __PT_TERMINAL_H_INCLUDED

#include <limits.h>

#ifndef __PT_CONTAINER_H_INCLUDED
 #include <photon/PtContainer.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtTerminal public
 */

extern PtWidgetClassRef_t *const PtTerminal;

/* Resources */
#define Pt_TERM_RESOURCE( n ) Pt_RESOURCE( 50, n )

#define Pt_ARG_TERM_ROWS				Pt_TERM_RESOURCE(  0 )
#define Pt_ARG_TERM_COLS				Pt_TERM_RESOURCE(  1 )
#define Pt_ARG_TERM_SIZE				Pt_TERM_RESOURCE(  2 )
#define Pt_ARG_TERM_MINSIZE				Pt_TERM_RESOURCE(  3 )
#define Pt_ARG_TERM_MAXSIZE				Pt_TERM_RESOURCE(  4 )
#define Pt_ARG_TERM_RESIZE_FL			Pt_TERM_RESOURCE(  5 )
#define Pt_ARG_TERM_RESIZE_FUN			Pt_TERM_RESOURCE(  6 )
#define Pt_ARG_TERM_RESIZE_STR			Pt_TERM_RESOURCE(  7 )
#define Pt_ARG_TERM_CUR_ROW				Pt_TERM_RESOURCE(  8 )
#define Pt_ARG_TERM_CUR_COL				Pt_TERM_RESOURCE(  9 )
#define Pt_ARG_TERM_CUR_POS				Pt_TERM_RESOURCE( 10 )
#define Pt_ARG_TERM_PROTOCOL			Pt_TERM_RESOURCE( 11 )
#define Pt_ARG_TERM_ANSI_PROTOCOL		Pt_TERM_RESOURCE( 11 )
#define Pt_ARG_TERM_FONT				Pt_TERM_RESOURCE( 12 )
#define Pt_ARG_TERM_FONT_SIZE			Pt_TERM_RESOURCE( 13 )
#define Pt_ARG_TERM_FONT_LIST			Pt_TERM_RESOURCE( 14 )
#define Pt_ARG_TERM_FONT_INDEX			Pt_TERM_RESOURCE( 16 )
#define Pt_ARG_TERM_MARGINS				Pt_TERM_RESOURCE( 17 )
#define Pt_ARG_TERM_COLOR_TABLE			Pt_TERM_RESOURCE( 18 )
#define Pt_ARG_TERM_COLOR_MODE			Pt_TERM_RESOURCE( 19 )
#define Pt_ARG_TERM_CONSOLE				Pt_TERM_RESOURCE( 20 )
#define Pt_ARG_TERM_SCROLL				Pt_TERM_RESOURCE( 21 )
#define Pt_ARG_TERM_DRAW_MODES			Pt_TERM_RESOURCE( 22 )
#define Pt_ARG_TERM_OPTIONS				Pt_TERM_RESOURCE( 24 )
#define Pt_ARG_TERM_OPTMASK				Pt_TERM_RESOURCE( 25 )
#define Pt_ARG_TERM_APP					Pt_TERM_RESOURCE( 26 )
#define Pt_ARG_TERM_MINROWS				Pt_TERM_RESOURCE( 33 )
#define Pt_ARG_TERM_MINCOLS				Pt_TERM_RESOURCE( 34 )
#define Pt_ARG_TERM_MAXROWS				Pt_TERM_RESOURCE( 35 )
#define Pt_ARG_TERM_MAXCOLS				Pt_TERM_RESOURCE( 36 )
#define Pt_ARG_TERM_VISUAL_BELL			Pt_TERM_RESOURCE( 15 )
#define Pt_ARG_TERM_SCRLBK_LIMIT		Pt_TERM_RESOURCE( 37 )
#define Pt_ARG_TERM_SCRLBK_COUNT		Pt_TERM_RESOURCE( 38 )
#define Pt_ARG_TERM_SCRLBK_POS			Pt_TERM_RESOURCE( 39 )
#define Pt_ARG_TERM_CURSOR_FLAGS		Pt_TERM_RESOURCE( 42 )
#define Pt_ARG_TERM_SELECTION			Pt_TERM_RESOURCE( 43 )
#define Pt_ARG_TERM_CHARSETS			Pt_TERM_RESOURCE( 44 )

/*
 *	Callbacks
 */
#define Pt_CB_TERM_INPUT	Pt_TERM_RESOURCE( 27 )
#define Pt_CB_TERM_FONT		Pt_TERM_RESOURCE( 28 )
#define Pt_CB_TERM_RESIZE	Pt_TERM_RESOURCE( 29 ) /* Called BEFORE resizing */
#define Pt_CB_TERM_RESIZED	Pt_TERM_RESOURCE( 30 ) /* Called AFTER resizing */
#define Pt_CB_TERM_OPTIONS	Pt_TERM_RESOURCE( 31 )
#define Pt_CB_TERM_APP		Pt_TERM_RESOURCE( 32 )
#define Pt_CB_TERM_SCRLBK	Pt_TERM_RESOURCE( 40 )

/*
 *	Subtypes for the INPUT callback
 */

#define Pt_TERM_KEYBOARD_INPUT	1
#define Pt_TERM_MOUSE_INPUT		2
#define Pt_TERM_CTRLBRK_INPUT	3	/* The Break key */
#define Pt_TERM_PROTOCOL_INPUT	4	/* Response to an escape sequence */
#define Pt_TERM_PASTE_INPUT		5	/* String from clipboard, PtTerminal will free it */
#define Pt_TERM_PASTE_NF_INPUT	6	/* String from clipboard, PtTerminal won't free it */

/*	Constants for Pt_ARG_TERM_RESIZE_FL flags
 */
#define Pt_TERM_ANCHOR_PARENT_WIDTH		0x01
#define Pt_TERM_ANCHOR_PARENT_HEIGHT	0x02
#define Pt_TERM_ANCHOR_WINDOWS_ONLY		0x04
#define Pt_TERM_OPFONT					0x08
#define Pt_TERM_KBFONT					0x10
#define Pt_TERM_KBFORCE					0x20

/*	Constants for Pt_ARG_TERM_DRAW_MODES flags
 */
#define Pt_TERM_SCROLL_NOBLIT			0x01
#define Pt_TERM_SCROLL_NOHWCHK			0x02
#define Pt_TERM_SCROLL_RFSH				0x04
#define Pt_TERM_SCROLL_NOVISCHK			0x08
#define Pt_TERM_SCROLL_NOSPEEDCHK		0x10

/*	Constants for Pt_ARG_TERM_CURSOR_FLAGS flags
 */
#define Pt_TERM_CURSOR_NEVER		0x00
#define Pt_TERM_CURSOR_ON_FOCUS		0x01
#define Pt_TERM_CURSOR_ALWAYS		0x02
#define Pt_TERM_CURSOR_MASK			0x03 /* mask */
#define Pt_TERM_CURSOR_TIMER		0x04
#define Pt_TERM_CURSOR_NOSPEEDCHK	0x08

/* Constants for character colour and attribute encoding
 * for the arguments of 'pack attibutes' functions
 */
#define Pt_TERM_BLINK			0x01
#define Pt_TERM_HIGHLIGHT		0x02
#define Pt_TERM_INVERSE			0x04
#define Pt_TERM_UNDERLINE		0x08
#define Pt_TERM_HALF			0x10
#define Pt_TERM_INVIS			0x20

#define Pt_TERM_FG_SHIFT	0
#define Pt_TERM_BG_SHIFT	4
#define Pt_TERM_FG_MASK		( 7 << Pt_TERM_FG_SHIFT )
#define Pt_TERM_BG_MASK		( 7 << Pt_TERM_BG_SHIFT )
#define Pt_TERM_COLOR_MASK	( Pt_TERM_FG_MASK | Pt_TERM_BG_MASK )

/*
 *	Structure of resources
 */

typedef struct Pt_terminal_row_col {
	short r, c; /* Row, column */
	}
		PtTerminalRowCol_t;

typedef struct Pt_terminal_colors {
	unsigned char fg, bg, ul;
	/* Colour numbers for foreground, background and underlining */
	}
		PtTerminalColors_t;

typedef struct Pt_terminal_char_and_attr {
	unsigned short	attr;
	unsigned char	chr;
	}
		PtTerminalCharAndAttr_t;

typedef struct Pt_terminal_colour_mode {
	unsigned short (*pckattr)( unsigned char attr, unsigned char colour );
	void (*unpkattr)( PtTerminalColors_t *dst, unsigned short attr );
	void (*unpkbuf)( PtTerminalColors_t *dst, void const *buf );
	void (*inverse)( void *buf );
	unsigned short (*getattr)( void const *buf );
	void (*setattr)( void *buf, unsigned short attr );
	unsigned char (*getchr)( void const *buf );
	void (*setchr)( void *buf, unsigned char ch );
	unsigned short (*getca)( void const *buf, unsigned char *cp );
	void (*puts)( void *buf, unsigned char const *str, int len, unsigned short attr );
	void (*bufset)( void *buf, unsigned char ch, unsigned n, unsigned short attr );
	unsigned size; /* bytes per character cell: 1...4 */
	}
		PtTerminalColorMode_t;

/* 'Standard' values for the Pt_ARG_COLOR_MODE resource */
extern const PtTerminalColorMode_t
	Pt_TERM_FULLCOLOR_MODE[1],
	Pt_TERM_COLOR_MODE[1],
	Pt_TERM_CGA_MODE[1],
	Pt_TERM_MONO_MODE[1],
	Pt_TERM_NOATTR_MODE[1];

typedef struct Pt_terminal_selection {
	unsigned char	type,
					old_type;
	unsigned short	flags;
	PtTerminalRowCol_t first, last;
	}
		PtTerminalSelection_t;

/* Selection type */
#define Pt_TERM_SELECTION_NONE		0
#define Pt_TERM_SELECTION_BLOCK		1
#define Pt_TERM_SELECTION_STREAM	2

/* Selection flags */
#define Pt_TERM_SELECTION_TYPE_KEEP		0x01 /* Don't set "type" (write only) */
#define Pt_TERM_SELECTION_FIRST_KEEP	0x02 /* Don't set "first" (w/o) */
#define Pt_TERM_SELECTION_LAST_KEEP		0x04 /* Don't set "last" (w/o) */
#define Pt_TERM_SELECTION_ALWAYS		0x08 /* Mouse always selects */
#define Pt_TERM_SELECTION_NEVER			0x80 /* Force never selects */
#define Pt_TERM_SELECTING				0x10 /* We are selecting right now (r/o) */
#define Pt_TERM_WILL_SELECT				0x20 /* Next mouse movement will select (r/o) */
#define Pt_TERM_SELECTION_FLAGS_KEEP	0x40 /* Don't set "flags" (w/o) */

extern const char *PtTerminalName( int protocol );

typedef struct Pt_terminal_console_write {
	void const *buffer;
	unsigned short offset, nbytes;
	}
		PtTerminalConsoleWrite_t;

typedef struct {
	const unsigned short *table;
	unsigned char first, last;
	unsigned short padding;
	}
		PtTerminalCharset_t;

typedef struct {
	unsigned short from, to;
	}
		PtTerminalCharSubst_t;

typedef struct PtTerm_cs_xlat_data PtTerminalCsXlatData_t;

typedef struct {
	PtTerminalCharset_t const *AnsiCharset;
	PtTerminalCharset_t const *InternalCharset;
	PtTerminalCharset_t const *FontTranslation;
	PtTerminalCharSubst_t const *Subst;
	unsigned short NumSubst, padding;
	}
		PtTerminalCharsets_t;

/*
 * Pt_TERM_OPTIONS bit numbers.
 * Set by the escape sequences:
 *	in QNX emulation "\33/>#h" sets option #
 *	in ANSI emulation "\33[>#h" sets option #
 */
#define Pt_TERM_REPORT_CLICKS		 1
#define Pt_TERM_REPORT_RESIZE		 2
#define Pt_TERM_REPORT_ICON			 3
#define Pt_TERM_REPORT_TAGS			 4
#define Pt_TERM_REPORT_ACTIVE		 5
#define Pt_TERM_REPORT_RELEASE		 6
#define Pt_TERM_REPORT_CURSOR		 7

#define Pt_TERM_ALLOW_DYNAMIC		 8
#define Pt_TERM_ALLOW_MENU_DIALOG	 9
#define Pt_TERM_ALLOW_COLOR			10
#define Pt_TERM_ALLOW_VSCROLL		11
#define Pt_TERM_ALLOW_HSCROLL		12
#define Pt_TERM_ALLOW_AUTOSCROLL	13
#define Pt_TERM_ALLOW_AUTOWRAP		14
#define Pt_TERM_ALLOW_AUTOSELECT	15

#define Pt_TERM_SHOW_SCROLLBARS		16

#define Pt_TERM_MASK_ESCAPE			17
#define Pt_TERM_WINDOW_INACTIVE		18
#define Pt_TERM_WINDOW_BUSY			19
#define Pt_TERM_DOUBLE_CLICK		20
#define	Pt_TERM_ALLOW_DND_INIT		21
#define	Pt_TERM_ALLOW_DND_DROP		22


/*
 * Pt_TERM_OPTIONS bit values.
 */

#define Pt_TERM_FLAG_REPORT_CLICKS		( 1uL << ( Pt_TERM_REPORT_CLICKS - 1 ) )
#define Pt_TERM_FLAG_REPORT_RESIZE		( 1uL << ( Pt_TERM_REPORT_RESIZE - 1 ) )
#define Pt_TERM_FLAG_REPORT_ICON		( 1uL << ( Pt_TERM_REPORT_ICON - 1 ) )
#define Pt_TERM_FLAG_REPORT_TAGS		( 1uL << ( Pt_TERM_REPORT_TAGS - 1 ) )
#define Pt_TERM_FLAG_REPORT_ACTIVE		( 1uL << ( Pt_TERM_REPORT_ACTIVE - 1 ) )
#define Pt_TERM_FLAG_REPORT_RELEASE		( 1uL << ( Pt_TERM_REPORT_RELEASE - 1 ) )
#define Pt_TERM_FLAG_REPORT_CURSOR		( 1uL << ( Pt_TERM_REPORT_CURSOR - 1 ) )

#define Pt_TERM_FLAG_ALLOW_DYNAMIC		( 1uL << ( Pt_TERM_ALLOW_DYNAMIC - 1 ) )
#define Pt_TERM_FLAG_ALLOW_MENU_DIALOG	( 1uL << ( Pt_TERM_ALLOW_MENU_DIALOG - 1 ) )
#define Pt_TERM_FLAG_ALLOW_COLOR		( 1uL << ( Pt_TERM_ALLOW_COLOR - 1 ) )
#define Pt_TERM_FLAG_ALLOW_VSCROLL		( 1uL << ( Pt_TERM_ALLOW_VSCROLL - 1 ) )
#define Pt_TERM_FLAG_ALLOW_HSCROLL		( 1uL << ( Pt_TERM_ALLOW_HSCROLL - 1 ) )
#define Pt_TERM_FLAG_ALLOW_AUTOSCROLL	( 1uL << ( Pt_TERM_ALLOW_AUTOSCROLL - 1 ) )
#define Pt_TERM_FLAG_ALLOW_AUTOWRAP		( 1uL << ( Pt_TERM_ALLOW_AUTOWRAP - 1 ) )
#define Pt_TERM_FLAG_ALLOW_AUTOSELECT	( 1uL << ( Pt_TERM_ALLOW_AUTOSELECT - 1 ) )

#define Pt_TERM_FLAG_SHOW_SCROLLBARS	( 1uL << ( Pt_TERM_SHOW_SCROLLBARS - 1 ) )

#define Pt_TERM_FLAG_MASK_ESCAPE		( 1uL << ( Pt_TERM_MASK_ESCAPE - 1 ) )
#define Pt_TERM_FLAG_WINDOW_INACTIVE	( 1uL << ( Pt_TERM_WINDOW_INACTIVE - 1 ) )
#define Pt_TERM_FLAG_WINDOW_BUSY		( 1uL << ( Pt_TERM_WINDOW_BUSY - 1 ) )
#define Pt_TERM_FLAG_DOUBLE_CLICK		( 1uL << ( Pt_TERM_DOUBLE_CLICK - 1 ) )
#define Pt_TERM_FLAG_ALLOW_DND_INIT		( 1uL << ( Pt_TERM_ALLOW_DND_INIT - 1 ) )
#define Pt_TERM_FLAG_ALLOW_DND_DROP		( 1uL << ( Pt_TERM_ALLOW_DND_DROP - 1 ) )

#define Pt_TERM_WSTRING_MAX 40

typedef struct Pt_terminal_app_state {
	struct PtTerminal_app_state_bins {
		/* Binary part - memcmp can be used for comparing */
		unsigned version;
		PhArea_t area;
		PtTerminalRowCol_t size;
		unsigned iconic: 1, infront: 1;
		}
			b;
	/* Strings - guaranteed to never contain garbage after '\0' */
	char title[ Pt_TERM_WSTRING_MAX + 1 ];
	char l_msg[ Pt_TERM_WSTRING_MAX + 1 ];
	char icon[ Pt_TERM_WSTRING_MAX + 1 ];
	char reserved;
	}
		PtTerminalAppState_t;

/*
 *	Callback data structures
 */

typedef struct Pt_terminal_input {
	unsigned length;
	const char *string;
	PtTerminalRowCol_t position;
	}
		PtTerminalInput_t;

typedef struct Pt_terminal_size_change {
	PtTerminalRowCol_t old_size, new_size;
	}
		PtTerminalSizeChange_t;

typedef struct Pt_terminal_option_change {
	unsigned long old_opts, new_opts;
	}
		PtTerminalOptionChange_t;

typedef struct Pt_terminal_font_change {
	const char *old_font, *new_font;
	}
		PtTerminalFontChange_t;

typedef struct Pt_terminal_scrlbk_cb_t {
	short old_count;
	short old_pos;
	short new_count;
	short new_pos;
	}
		PtTerminalScrlbkCb_t;

/*
 * PtTerminal private
 */

/* Base widget classes union */
typedef union Pt_terminal_base {
	PtWidget_t			core;
	PtBasicWidget_t		basic;
	PtContainerWidget_t	cntr;
	}
		PtTerminalBase_t;

#define Pt_TERM_MAX_COLS 1000
#define Pt_TERM_MAX_ROWS 1000

struct Pt_terminal_tabs {
    int tab_bits[
		(	Pt_TERM_MAX_COLS
		+	sizeof(int) * CHAR_BIT
		-	1
			)
		/	( sizeof(int) * CHAR_BIT )
		];
	};

typedef unsigned PtTerm_MapUnit_t;

struct Pt_terminal_history {
	unsigned short bg;
	char *buf;
	};

struct Pt_terminal_scroll_state;

/* Widget structure */
typedef struct Pt_terminal_widget {
	PtTerminalBase_t	base;				/* Base class object */
	const char			*font;				/* Pt_ARG_TERM_FONT */
	const char			**fonts;			/* Pt_ARG_TERM_FONT_LIST */
	short				nfonts;				/* Pt_ARG_TERM_FONT_LIST length */
	short				fidx;				/* Pt_ARG_TERM_FONT_INDEX */
	PhDim_t				fsize;				/* Pt_ARG_TERM_FONT_SIZE */
	PhPoint_t			foff;				/* Offsets for drawing characters */
	PtTerminalColorMode_t
						cm;					/* Pt_ARG_COLOR_MODE */
	PgColor_t			*ctab;				/* Pt_ARG_COLOR_TABLE */
	short				ctlen;				/* Pt_ARG_COLOR_TABLE length */
	unsigned short		resize_fl;			/* Pt_ARG_TERM_RESIZE_FL */

	unsigned long		uflags;				/* Pt_ARG_TERM_OPTIONS	*/
	unsigned long		umask;				/* Pt_ARG_TERM_OPTMASK	*/
	PtTerminalAppState_t appst;				/* Pt_ARG_TERM_APP		*/

	PtTerminalSelection_t selection;		/* Pt_ARG_TERM_SELECTION */

	/* Terminal 'state entry': */
	PtTerminalRowCol_t	size;				/* Pt_ARG_TERM_SIZE */
	PtTerminalRowCol_t	minsize;			/* Pt_ARG_TERM_MINSIZE */
	PtTerminalRowCol_t	maxsize;			/* Pt_ARG_TERM_MAXSIZE */
	PtTerminalRowCol_t	curpos;				/* Pt_ARG_TERM_CUR_POS */
	const char
		*(*resize_fun)(char*, const char*);	/* Pt_ARG_TERM_RESIZE_FUN */
	char				*resize_str;		/* Pt_ARG_TERM_RESIZE_STR */
	PhRect_t			margs;				/* Pt_ARG_TERM_MARGINS */
	short				vbell;				/* Pt_ARG_TERM_VISUAL_BELL */
	short				hslimit;			/* Pt_ARG_TERM_SCROLLBACK_LIMIT */
	short				hspos;				/* Pt_ARG_TERM_SCROLLBACK_POS */
	unsigned short		hscount;			/* Pt_ARG_TERM_SCROLLBACK_COUNT */
	unsigned long		lowspeed;			/* Pt_ARG_TERM_LOWSPEED */
	unsigned char		draw_modes,			/* Pt_ARG_TERM_DRAW_MODES */
						draw_state;

	unsigned short		damage_ulr, damage_ulc,
						damage_lrr, damage_lrc,
						damage_llen;
	char				*screen;			/* Screen buffer */

	PtTerm_MapUnit_t	*damage_map;

	/* Used for mouse events compression: */
	PtTerminalRowCol_t mousepos;
	short mousebut;

	unsigned short		hscur;
	struct Pt_terminal_history
						*hslines;

	/* Minimal DIM: */
	PhDim_t mindim;

	/* Used by the cursor timer: */
	unsigned short cflags;

	unsigned short reserved1;

	/* Flags for scrolling optimization: */
	unsigned short scmax;					/* Pt_ARG_TERM_SCROLL */
	PtTerminalCsXlatData_t *csdata;			/* Pt_ARG_TERM_CHARSETS */
	struct Pt_terminal_scroll_state *scstat;

	/* Fields for the protocol engine: */
	unsigned short flags;
	unsigned short beep_freq;
	unsigned short beep_dur;
	unsigned short save_flags;
	int strpos;
	unsigned parm[10];
	unsigned char g[4];
	struct Pt_terminal_tabs tabs;
	char attr, color, fill_color;
	unsigned char cursor_hidden;
	unsigned short attribute;
	unsigned short background;
	unsigned char esc_flag;
	unsigned char gl, gr;
	unsigned char cursor_type;
	unsigned char lastch;
	unsigned char top_region;
	unsigned char bottom_region;
	unsigned char ichar;
	unsigned char parmidx;
	unsigned char save_row;
	unsigned char save_col;
	unsigned char save_gl, save_gr;
	unsigned char save_attr;
	unsigned char save_color;
	unsigned char attr_save;
	unsigned char color_save;
	unsigned char fill_color_save;
	unsigned char erase_char;
	unsigned char xpos;
	char string[ Pt_TERM_WSTRING_MAX + 1 ];
	unsigned char ansi_mode;
	unsigned char underline_color;
	unsigned char half_color;
	}
		PtTerminalWidget_t;


/*
 * Functions
 */

PtTerminalWidget_t *PtTerminalWidget( PtWidget_t * );
extern int PtTerminalPutc( PtWidget_t *widget, char character );
extern int PtTerminalPuts( PtWidget_t *widget, const char *string );
extern int PtTerminalPut(  PtWidget_t *widget, const char *buffer, size_t nchars );
extern int PtTerminalFontInfo( const char *fn, PhDim_t *size, PhPoint_t *offs );
struct termios;
void PtTerminalGetKeys( int protocol, struct termios *buf );
unsigned PtTerminalMbToKeys( PtWidget_t *widget, char *string );
void PtTerminalPaste(
		PtWidget_t *widget, char *buf, unsigned len,
		PhEvent_t *event, int subtype
		);
void PtTerminalPasteClipboard( PtWidget_t *widget, PhEvent_t *event );
void PtTerminalPasteSelection( PtWidget_t *widget, PhEvent_t *event );
char *PtTerminalGetSelection( PtWidget_t *widget );
void PtTerminalCopy( PtWidget_t *widget, PhEvent_t *event );
int PtTerminalSelectWord( PtWidget_t *widget, PtTerminalRowCol_t const *pos );

PtTerminalCsXlatData_t *PtTerminalCreateCsXlat( PtTerminalCharsets_t const *csets );
const PtTerminalCharsets_t *PtTerminalDefaultCharsets( void );

/* Deprecated: */
#define PtTerminalFont( fn, size, offs ) ( PtTerminalFontInfo( fn, size, offs ) ? NULL : strdup(fn) )

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif /* __PT_TERMINAL_H_INCLUDED */


#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtTerm.h $ $Rev: 219996 $" )
#endif
