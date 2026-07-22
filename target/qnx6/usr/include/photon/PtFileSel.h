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



#ifndef __PT_FILESEL_H_INCLUDED
#define __PT_FILESEL_H_INCLUDED

/*************************************************************************
 *
 *	PtFileSel.h
 *		Header file for the PtFileSel widget class
 *

 *
 *************************************************************************/

#ifndef __STAT_H_INCLUDED
#include <sys/stat.h>
#endif

#ifndef __PT_GENTREE_H_INCLUDED
#include <photon/PtGenTree.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

extern PtWidgetClassRef_t *const PtFileSel;

#define Pt_FILESEL_ID	47

/* resources */
#define Pt_ARG_FS_ROOT_DIR			Pt_RESOURCE( 47,  0 )
#define Pt_ARG_FS_IMAGES			Pt_RESOURCE( 47,  1 )
#define Pt_ARG_FS_FLAGS				Pt_RESOURCE( 47,  2 )
#define Pt_ARG_FS_REFRESH			Pt_RESOURCE( 47,  3 )
#define Pt_ARG_FS_FILE_SPEC         Pt_RESOURCE( 47,  4 )
#define Pt_ARG_FS_FORMAT		    Pt_RESOURCE( 47,  5 )
#define Pt_ARG_FS_LBL_NAME		    Pt_RESOURCE( 47,  6 )	/* Label of the "Name" column */
#define Pt_ARG_FS_LBL_SIZE		    Pt_RESOURCE( 47,  7 )	/* Label of the "Size" column */
#define Pt_ARG_FS_LBL_DATE		    Pt_RESOURCE( 47,  8 )	/* Label of the "Date" column */
#define Pt_ARG_FS_LBL_PERMISSIONS   Pt_RESOURCE( 47,  9 )	/* Label of the "Permissions" column */
#define Pt_ARG_FS_LBL_OWNER		    Pt_RESOURCE( 47, 10 )	/* Label of the "Owner" column */
#define Pt_ARG_FS_LBL_GROUP			Pt_RESOURCE( 47, 11 )	/* Label of the "Group" column */
#define Pt_CB_FS_STATE				Pt_RESOURCE( 47, 12 )
#define Pt_CB_FS_SELECTION			Pt_RESOURCE( 47, 13 )
#define Pt_CB_FS_BKGD_HANDLER	    Pt_RESOURCE( 47, 14 )

/* PtFileSel flags - fs_flags */
#define	Pt_FS_SHOW_DIRS				0x00000001	/* display directories */
#define	Pt_FS_SHOW_FILES			0x00000002	/* display files */
#define	Pt_FS_SHOW_HIDDEN			0x00000004	/* display hidden files/dirs */
#define	Pt_FS_SHOW_ERRORS			0x00000008	/* display errored files/dirs */
#define	Pt_FS_FREE_ON_COLLAPSE		0x00000010	/* display free items on a collapse */
#define	Pt_FS_SINGLE_LEVEL			0x00000020	/* display in a single level not a tree */
#define	Pt_FS_SEEK_KEY				0x00000040	/* display allow keyboard seeking */
#define	Pt_FS_NO_ROOT_DISPLAY		0x00000080	/* do not show the root item */
#define	Pt_FS_CASE_INSENSITIVE		0x20000000	/* file pattern matching is case insensitive */
#define	Pt_FS_ERROR_POPUP			0x10000000	/* popup an error dialog when unable to change dir */
   
#define Pt_FS_ALL_FLAGS (   Pt_FS_SHOW_DIRS | \
			    Pt_FS_SHOW_FILES | \
			    Pt_FS_SHOW_HIDDEN | \
			    Pt_FS_SHOW_ERRORS | \
			    Pt_FS_FREE_ON_COLLAPSE | \
			    Pt_FS_SINGLE_LEVEL | \
			    Pt_FS_SEEK_KEY | \
			    Pt_FS_NO_ROOT_DISPLAY | \
			    Pt_FS_CASE_INSENSITIVE | \
			    Pt_FS_ERROR_POPUP )


/* FileSel item structure, see the below values */
typedef struct Pt_filesel_item
{
	PtGenTreeItem_t	gen;
	short opened;	/* a value to say whether this dir was previously opened */
	short type;		/* a value to say whether this is a open dir, closed dir, file, link */
	short root;		/* a value to say whether this is the root item, 1 means it is */
	char *fullpath;	/* the fullpath of the item */
	char *otherinfo;	
	int tag;		/* TAG, DO NOT USE */
} PtFileSelItem_t;


/* PtFileSel directory values - opened - field */
#define Pt_FS_NEW_DIR	0	/* dir has not been opened */
#define Pt_FS_OLD_DIR	1	/* dir has been opened */


/* PtFileSel type value - type - field */
#define Pt_FS_DIR_OP	0
#define Pt_FS_DIR_CL	1
#define Pt_FS_DLINK_OP	2
#define Pt_FS_DLINK_CL	3
#define Pt_FS_FILE		4
#define Pt_FS_FLINK		5
#define Pt_FS_ERROR		6


/* FileSel callback structure */
typedef struct Pt_filesel_callback {

	unsigned sel_mode;
    PtFileSelItem_t *item;
    unsigned nitems; /* for SELECTION callbacks */
    short reason;

} PtFileSelCallback_t;



typedef struct Pt_fileselbkgd_callback {

    char *name;
    long spare[2];

} PtFileSelBkgdCallback_t;


/* state callback subtypes */
#define Pt_FS_STATE_START	 1
#define Pt_FS_STATE_END		 2


/* bkgd callback subtypes */
#define Pt_FS_NEW_ITEM		 1
#define Pt_FS_OLD_ITEM		-1


/*-------------------------------
 * number of translatable strings
 *-------------------------------*/ 
#define Pt_FS_LBL_NUM_STRINGS	6


/*---------------------------
 * Number of internal widgets
 *---------------------------*/
#define Pt_FS_NUM_WIDGETS		7


/* Widget structure */
typedef struct Pt_filesel_widget
{
	PtGenTreeWidget_t	gen;
	ulong_t 			fs_flags;		/* file selector flags */
	char 				*root_path;		/* the root path or startng path */
	char 				*file_spec;		/* file spec for file display */
	
	PtFileSelItem_t 	*refresh;		/* item to be refreshed */
	PhImage_t			*images[7];		/* images to diplay in the widget */

	/* internal stuff */
	PtWidget_t 			*w[Pt_FS_NUM_WIDGETS];	/* Internal widgets */
	char 				*format;
	char 				*full_format;
	char 				*pat[10];
	short				pat_ctr;

	short 				img_count;
	int 				user_divider;

	char *gcache, *ocache;				/* caching for the uid and gid, to speed up lookups */
	short uid_cache, gid_cache;

	char *istrings[Pt_FS_LBL_NUM_STRINGS];	/* Translatable strings */


	PhEvent_t			*event;			/* This is a temporary kludge to allow */
									/* the key-event which causes a state-callback*/
									/* to be returned to the callback. Once this pointer*/
									/* is removed, set the 'spare' dimension back to [3]*/
	long 				spare[2];

} PtFileSelWidget_t;



/* Widget union */
typedef union Pt_FileSel_union
{
	PtWidget_t				core;
	PtBasicWidget_t			basic;
	PtGenListWidget_t		list;
	PtGenTreeWidget_t		gtree;
	PtFileSelWidget_t		fs;
} PtFileSelUnion_t;


/* convenience functions, based on the gen-tree convenience functions */
#define PtFSRootItem( fs ) \
    ( (PtFileSelItem_t*) PtGenTreeRootItem( (PtWidget_t *)fs ) )

#define PtFSAddFirst( fs, items, parent ) \
	PtGenTreeAddFirst( (PtWidget_t *)fs, (PtGenTreeItem_t *)(items), (PtGenTreeItem_t *)(parent))

#define PtFSAddAfter( fs, items, brother ) \
	PtGenTreeAddAfter( (PtWidget_t *)fs, (PtGenTreeItem_t *)(items), (PtGenTreeItem_t *)(brother))

#define PtFSAllItems( fs, buffer ) \
	( (PtFileSelItem_t**) PtGenTreeAllItems((PtWidget_t *)fs, (PtGenTreeItem_t**)(buffer)))

#define PtFSFolderExpand( fs, item, event ) \
	PtGenTreeExpand( (PtWidget_t *)fs, &(item)->gen, event )

#define PtFSFolderCollapse( fs, item, event ) \
	PtGenTreeCollapse( (PtWidget_t *)fs, &(item)->gen, event )

#define PtFSRemoveItem( fs, item ) \
    PtGenTreeRemoveItem( (PtWidget_t *)fs, &(item)->gen )

#define PtFSRemoveList( fs, item ) \
    PtGenTreeRemoveList( (PtWidget_t *)fs, &(item)->gen )

#define PtFSRemoveChildren( item ) \
    ( (PtFileSelItem_t*) PtGenTreeRemoveChildren( (PtGenTreeItem_t*) (item) ) )

#define PtFSItemIndex( fs, item ) \
    PtGenTreeItemIndex( (PtWidget_t *)fs, (PtGenTreeItem_t*)(item) )

#define PtFSShow( fs, item ) \
    PtGenTreeShow( (PtWidget_t *)fs, (PtGenTreeItem_t*)(item) )

#define PtFSGoto( fs, item ) \
    PtGenTreeGoto( (PtWidget_t *)fs, (PtGenTreeItem_t*)(item) )

#define PtFSSelectedItems( fs, buffer ) \
    ((PtFileSelItem_t**) PtGenTreeSelectedItems( (PtWidget_t *)fs, (PtGenTreeItem_t**)(buffer) )) 

#define PtFSGetCurrent( fs ) \
    ( (PtFileSelItem_t*) PtGenTreeGetCurrent( (PtWidget_t *)fs ) )

#define PtFSSelect( fs, item ) \
    PtGenTreeSelect( (PtWidget_t *)fs, (PtGenTreeItem_t*) (item) )

#define PtFSUnselect( fs, item ) \
    PtGenTreeUnselect( (PtWidget_t *)fs, (PtGenTreeItem_t*) (item) )

#define PtFSUnselectNonBrothers( fs, item ) \
    PtGenTreeUnselectNonBrothers( (PtWidget_t *)fs, (PtGenTreeItem_t*) (item) )

#define PtFSExpandParents( fs, item, event ) \
    PtGenTreeExpandParents( (PtWidget_t *)fs, (PtGenTreeItem_t*) (item), event )

#define PtFSDamageItem( fs, item) \
    PtGenTreeDamageItem( (PtWidget_t *)fs, (PtGenTreeItem_t*) (item) )

#define PtFSClearSelection(fs)  PtGenTreeClearSelection((PtWidget_t *) fs)

#define PtFSGetSelIndexes PtGenTreeGetSelIndexes

#define PtFSSetSelIndexes PtGenTreeSetSelIndexes

PtFileSelItem_t * PtFSAllocItem(PtWidget_t *fs, int type, char const *info);

void PtFSFreeItems( PtFileSelItem_t *item );

void PtFSFreeAllItems( PtWidget_t *const widget );


#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtFileSel.h $ $Rev: 219996 $" )
#endif
