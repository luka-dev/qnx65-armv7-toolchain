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
/***********************************************************/
/*                                                         */
/*   Application Builder Library Header: PHOTON Version    */
/*                                                         */
/***********************************************************/

#ifndef _APPLIB_H_INCLUDED
#define _APPLIB_H_INCLUDED

#include <stdio.h>
#include <limits.h>
#include <photon/PtWidget.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*********************************/
/* Constants                     */
/*********************************/

/* menu item types */
#define AB_ITEM_COMMAND			0x0001
#define AB_ITEM_MENU			0x0002
#define AB_ITEM_TOGGLE			0x0004
#define	AB_ITEM_FUNCTION		0x0008
#define AB_ITEM_LINE			0x0010
#define AB_ITEM_COLUMN			0x0020
#define AB_ITEM_TOGGLE_EXCL		0x0040

/* menu item states */
#define	AB_ITEM_NORMAL			0x0000
#define AB_ITEM_DEFAULT			0x0100
#define AB_ITEM_DIM				0x0200
#define AB_ITEM_SET				0x0400

/* menu item accelerator flags */
#define AB_ITEM_ACCEL_CTRL		0x01
#define AB_ITEM_ACCEL_SHIFT		0x02
#define AB_ITEM_ACCEL_ALT		0x04
#define AB_ITEM_ACCEL_STRDUP	0x08

/* locations */
#define AB_LOC_DEFAULT			0
#define AB_LOC_BELOW_WGT		1
#define AB_LOC_ABOVE_WGT		2	
#define AB_LOC_RIGHT_WGT		3
#define AB_LOC_LEFT_WGT			4
#define AB_LOC_TOP_LEFT			5
#define AB_LOC_BOT_LEFT			6
#define AB_LOC_TOP_RIGHT		7
#define AB_LOC_BOT_RIGHT		8
#define AB_LOC_CENTER			9
#define AB_LOC_REL_CURSOR		10
#define AB_LOC_REL_MODULE		11 
#define AB_LOC_ABSOLUTE			12

/* realize flags */
#define AB_FUNC_PRE_REALIZE		0
#define AB_FUNC_POST_REALIZE	1
#define AB_FUNC_BOTH			2

/* menu actions */
#define	AB_ENABLE				1
#define	AB_DISABLE				2

/* module parent indicators */
#define	AB_PARENT				0
#define	AB_NO_PARENT			1

/* processing actions */
#define	AB_EXIT					1
#define	AB_DONE					2
#define AB_CONTINUE				3
#define AB_LOCKED			   -2

/* link types */
#define AB_RAPPL				1
#define AB_RMODULE  			2
#define AB_RWINDOW  			3
#define AB_RDIALOG  			4
#define AB_RMENU	 			5
#define AB_RHELP  				6
#define AB_RRULE  	 			7
#define	AB_CALLBACK				8
#define	AB_OK					9
#define	AB_CANCEL				10
#define	AB_RVIEW				11
#define AB_EDIT					12
#define AB_FILEMENU				13
#define AB_POPLIST				14
#define AB_KEYBOARD				15

/* callback reason codes */
#define ABR_PRE_REALIZE			1
#define ABR_POST_REALIZE		2
#define ABR_CODE				3
#define ABR_DONE				4
#define ABR_CANCEL				5

#define AB_LITEMS				1000
#define AB_MAX_ITEMS			1000
#define AB_PhAB(x)				( 10000 + x )


/* Flags for ApModalWait() */
#define Ap_MODAL_BLOCK_WINDOWS 0x10000

/*********************************/
/* Typedefs                      */
/*********************************/

typedef struct Ap_context ApContext_t;
typedef struct Ap_res_file ApResFile_t;
typedef struct AB_EVENT_LINK ApEventLink_t;
typedef struct Ap_FILE ApFILE_t;

/* class tables */

typedef struct AB_CLASS_LIST ApClassList_t;

typedef struct AB_CLASS_TABLE {
	const char			*class_text;
	PtWidgetClassRef_t	*const *wclass;
	} ApClassTab_t;

/* AB callback info structure */
typedef struct {
	short			reason;
	PtWidget_t		*widget;
	} ApInfo_t;

/* Callback function type */
typedef int ApCallbackF_t( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );

/* bitmap widget Structure */
typedef struct {
	short			nplanes;
	short			nbytes;
	PgColor_t	   *colors;
	char		  **data;
	} ApBitmap_t;

/* appbuilder widget structure */
typedef struct AB_WIDGET_STRUCTURE {
	PtWidget_t *wgt;
	} ApWidget_t;

/* menu item structure */
typedef struct AB_ITEM_STRUCT {
	int				ilevel;			/* item level 1=top, 2=second, etc	*/
	int				istate;			/* item state						*/
	char			iaccelerator;	/* keyboard equivalent key			*/
	const char		*iaccel_text;	/* keyboard text description		*/
	short			isep_type;		/* item separator type				*/
	const char		*itag;			/* item tag							*/
	const char 		*ivalue;		/* item text or object pointer		*/
	PhImage_t const	*image;			/* item image						*/
	} ApItem_t;

/* menu link data */
typedef struct AB_MENU_LINK {
	const char	*label;				/* menu label						*/
	const char	*title;				/* menu title						*/
	const char	*title_font;		/* menu title font					*/
	const char	*item_font;			/* menu item font					*/
	short		item_spacing;		/* menu item spacing				*/
	ApItem_t	*item_list;			/* array of item objects			*/
	ApContext_t	*context;
	ApEventLink_t const	*linkevt;	/* pointer to link events			*/
	unsigned	dsoff;
	unsigned	nlinks;
	unsigned	nitems;
	} ApMenuLink_t;

/* linked item list header */
typedef struct AB_LIST_HEADER {
	struct AB_LIST_HEADER	*next;	/* owll - next pointer				*/
	int						size;	/* size of data area				*/
	} ApListHdr_t;

/* event link data */
struct AB_EVENT_LINK { /* = ApEventLink_t */
	int				type;			/* type of link						*/
	int				cb_style;  		/* style (widget, event, hotkey)	*/
	ulong_t			key_cap;		/* key cap 							*/
	ulong_t			key_mods;		/* keyboard modifiers				*/
	ulong_t			event_mask;		/* raw event mask					*/
	void			*linkobj;		/* pointer to link					*/
	void const		*reserved;
	const char		*tag;			/* link tag identifier				*/
	long			cb_type;      	/* link callback type				*/
	ApCallbackF_t	*lfunction;		/* associated callback function     */
	int				lfunc_ind;		/* cb before/after indicator		*/
	int				loc_pos;		/* location position code			*/
	int				loc_row;		/* y offset	for location			*/
	int				loc_col;		/* x offset for location			*/
	void			*dsdata;		/* data associated to link			*/
	};
 	
/* database structure */
typedef struct AB_DBASE ApDBase_t;

typedef struct AB_WIDGET_INFO {
	const char *wgt_name;
	const char *wgt_class;
	int parent_index;
	int level;
	unsigned reserved[ 4 ];
	} ApDBWidgetInfo_t;

/* translation structure */
typedef struct AB_TRANSLATION ApTranslation_t, ApMsgDBase_t;

/* window link data */
typedef struct AB_WINDOW_LINK {
	const char			*mod_name;
	ApContext_t			*context;
	ApEventLink_t const	*linkevt;
	unsigned			dsoff;
	unsigned			nlinks;
	} ApWindowLink_t;

/* dialog link data */
typedef struct AB_DIALOG_LINK {
	const char			*mod_name;
	ApContext_t			*context;
	ApEventLink_t const	*linkevt;
	unsigned			dsoff;
	unsigned			nlinks;
	PtWidget_t			*wgt;
	} ApDialogLink_t;

/* picture link data */
typedef struct AB_PICTURE_LINK {
	const char			*mod_name;
	ApContext_t			*context;
	ApEventLink_t const	*linkevt;
	unsigned			dsoff;
	unsigned			nlinks;
	} ApPictureLink_t;

/* Global data structure */
typedef struct Ap_ctrl {
	PhPoint_t		Ap_winpos;
	PhPoint_t		Ap_winsize;
	int				Ap_winstate;
	int				Ap_names;
	PtWidget_t		*Ap_base_wgt;
	ApFILE_t		*Ap_resfp;
	long			Ap_resbase;
	char			Ap_lang[16];
	ApResFile_t		*Ap_resfiles;
	ApContext_t		*Ap_ctxt;
	ApResFile_t		*Ap_resfile;
	char			Ap_focus;
	ApClassList_t	*Ap_classtab;
	int				Ap_classtab_ctr;
	size_t			Ap_threshold;
	ApContext_t		*Ap_mainctxt;
	unsigned		Ap_reserved;
	}
		ApCtrl_t;

/* Application/DLL data */
struct Ap_context {
	ApClassTab_t const *Ap_classtab;
	int				Ap_version;
	ApWidget_t		*Ap_wgts;
	ApResFile_t		*Ap_resfile;
	unsigned short	Ap_count;
	unsigned short	Ap_extra;
	int				Ap_spare[ 3 ];
	};

/*********************************/
/* Externals                     */
/*********************************/

#if !defined(_APSHLIB)
	/* Defined by PhAB in abmain.c */
	extern ApContext_t AbContext;

	extern const char ApOptions[];
#endif

extern ApCtrl_t _Ap_;


/*********************************/
/* Prototypes                    */
/*********************************/

size_t				ApShmemThreshold( size_t );
void				*ApShmemAlloc( size_t size );
void				ApShmemFree( void *mem );
void			   	*ApAlloc( int n, int size, char const *location );
int					ApInitialize( int argc, char *argv[], ApContext_t *context );
int					ApAddContext( ApContext_t *context, const char *exe_path );
int					ApRemoveContext( ApContext_t *context );
const char			*ApExePath( ApContext_t *context );
ApContext_t			*ApSetContext( ApContext_t * );
void			    ApError( PtWidget_t *widget, int errvalue, char const *app, char const *msg, char const *location );
char				*ApNLErase( char *string );
int					ApAddClass( char const *class_name, PtWidgetClassRef_t *const *wclass );
int					ApRemoveClass( char const *class_name, PtWidgetClassRef_t *const *wclass );
int					ApAppendTranslation( char const *fname, char const *lang_ext );
ApDBase_t			*ApOpenDBase( ApEventLink_t const *ld );
ApDBase_t			*ApOpenDBaseFile( char const *path );
ApDBase_t			*ApOpenExecDBaseFile( char const *exec, char const *modname );
int          		ApCloseDBase( ApDBase_t *dbase );
ApDBWidgetInfo_t	*ApGetDBWidgetInfo( ApDBase_t const *dbase, unsigned index, ApDBWidgetInfo_t *info );
PtWidget_t			*ApCreateDBWidget( ApDBase_t const *dbase, char const *wname, PtWidget_t *parent, PhPoint_t const *pos, int nargs, PtArg_t const *args );
PtWidget_t			*ApCreateDBWidgetFamily( ApDBase_t const *dbase, char const *wname, PtWidget_t *parent, PhPoint_t const *pos, int nargs, PtArg_t const *args );
int					ApCopyDBWidget( ApDBase_t const *from_dbase, char const *wname, ApDBase_t *to_dbase, char const *tname );
int					ApDeleteDBWidget( ApDBase_t *dbase, char const *wname );
int					ApSaveDBaseFile( ApDBase_t const *dbase, char const *path );
ApBitmap_t		   	*ApGetBitmapRes( ApDBase_t const *db, char const *wname );
void				ApFreeBitmapRes( ApBitmap_t *bitmap );
PhImage_t		   	*ApGetImageRes( ApDBase_t const *db, char const *wname );
char			   	*ApGetTextRes( ApDBase_t const *db, char const *wname );
void				ApResClose( void );
ApTranslation_t		*ApAppendTranslationDB( ApTranslation_t *xlat, const char *fname, const char *lang_ext );
int				   	ApSetTranslation( char const *lang_ext );
PtWidget_t			*ApCreateModule( ApEventLink_t const *ld, PtWidget_t *w, PtCallbackInfo_t *cbinfo );
PtWidget_t			*ApWidget( PtCallbackInfo_t *cbinfo );
int					ApName( PtWidget_t *widget );
char *				ApInstanceName( PtWidget_t *widget );
PtWidget_t		   	*ApGetWidgetPtr( PtWidget_t *link_instance, int data_value );
PtWidget_t		   	*ApGetInstance( PtWidget_t *widget );
PtWidget_t			*ApLinkWindow( PtWidget_t *widget, ApEventLink_t const *l, PtCallbackInfo_t *cbinfo );

void				ApModuleLocation( ApEventLink_t *ld, int loc_type, int x_offset, int y_offset );
void				ApModuleFunction( ApEventLink_t *ld, int (*function)(), int realize_flags );
void				ApModuleParent( ApEventLink_t *ld, int parent, PtWidget_t *widget );

int					ApModifyItemState( ApMenuLink_t *menu, int state, ... );
int					ApModifyItemAccel( ApMenuLink_t *menu, int item_no, const char *new_text, int new_flags );
int					ApModifyItemText( ApMenuLink_t *menu, int item_no, char const *new_text );
char *				ApGetItemText( ApMenuLink_t *menu, int item_no );

ApMsgDBase_t		*ApLoadMessageDB( ApMsgDBase_t *db, const char *name );
void				ApCloseMessageDB( ApMsgDBase_t *db );
char *				ApGetMessage( ApMsgDBase_t *db, const char *tag );
void				ApTranslateStringsDB( ApMsgDBase_t *db, PtWidget_t *widget, const char *tag );
void				ApTranslateStrings( PtWidget_t *widget, const char *tag );

int					ApModalWait( PtWidget_t *widget, int flags );


#define				ApGetWidgetInfo		ApGetDBWidgetInfo
#define				ApCopyWidget		ApCopyDBWidget
#define				ApDeleteWidget		ApDeleteDBWidget

PtWidget_t			*ApCreateWidget( ApDBase_t const *dbase, char const *wname, int x, int y, int nargs, PtArg_t const *args );
PtWidget_t			*ApCreateWidgetFamily( ApDBase_t const *dbase, char const *wname, int x, int y, int nargs, PtArg_t const *args );

#ifdef __cplusplus
}
#endif

#include <photon/PhPackPop.h>

#include <photon/AwFileSelect.h>
#include <photon/AwMessage.h>

#endif


#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ap/public/Ap.h $ $Rev: 224582 $" )
#endif
