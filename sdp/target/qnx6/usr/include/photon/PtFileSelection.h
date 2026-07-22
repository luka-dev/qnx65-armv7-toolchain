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



#ifndef __PT_FILESELECTION_H_INCLUDED
#define __PT_FILESELECTION_H_INCLUDED

/*********************************************************************************
 *
 *	PtFileSelection.h
 *		Header file for the PtFileSelect and PtFileSelection convenience functions
 *

 *
 *********************************************************************************/

#ifndef __STAT_H_INCLUDED
#include <sys/stat.h>
#endif

#ifndef __PT_FILESEL_H_INCLUDED
#include <photon/PtFileSel.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*-------------------------------------------------
 * PtFileSelection convenience function flags which 
 * correspond to the Pt_ARG_FS_FLAGS resource of
 * the PtFileSel widget.
 *-------------------------------------------------*/
#define	Pt_FSR_DONT_SHOW_DIRS		0x00000001	/* don't display directories */
#define	Pt_FSR_DONT_SHOW_FILES		0x00000002	/* don't display files */
#define	Pt_FSR_SHOW_HIDDEN		Pt_FS_SHOW_HIDDEN  /* display hidden files and directories */
                                                           /* must be the same as Pt_FS_SHOW_HIDDEN */
							   /* for legacy. */
#define	Pt_FSR_SHOW_ERRORS		0x00000008	/* display directory entries which have errors */
#define	Pt_FSR_FREE_ON_COLLAPSE		0x00000010	/* free items on every collapse */
#define	Pt_FSR_TREE                     0x00000020	/* display in a tree, rather than single level */
#define	Pt_FSR_NO_SEEK_KEY		0x00000040	/* disable keyboard seeking */
#define	Pt_FSR_NO_ROOT_DISPLAY		0x00000080	/* do not show the root item in single level mode */
#define	Pt_FSR_CASE_INSENSITIVE		0x00400000	/* file pattern matching is case insensitive */
#define	Pt_FSR_NO_ERROR_POPUP		0x00800000	/* do not pop up an error dialog when unable to change dir */


#define Pt_FSR_ALL_FS_FLAGS ( Pt_FSR_DONT_SHOW_DIRS|Pt_FSR_DONT_SHOW_FILES|Pt_FSR_SHOW_HIDDEN|\
			      Pt_FSR_SHOW_ERRORS|Pt_FSR_FREE_ON_COLLAPSE|Pt_FSR_TREE|\
			      Pt_FSR_NO_SEEK_KEY|Pt_FSR_NO_ROOT_DISPLAY|Pt_FSR_CASE_INSENSITIVE|\
			      Pt_FSR_NO_ERROR_POPUP )

   
/*------------------------------------------------
 * More PtFileSelection convenience function flags
 *------------------------------------------------*/
#define Pt_FSR_NO_FCHECK		0x000100        /* Permit non-existent files/dirs to be selected. (The path must exist!) */
#define Pt_FSR_NO_FSPEC			0x000200	/* Do not display the filespec  */
#define Pt_FSR_NO_UP_BUTTON		0x000400	/* Do not display the 'up-directory' button */
#define Pt_FSR_NO_NEW			0x000800	/* Disable new directory creation via the "Insert" key */
#define Pt_FSR_NO_NEW_BUTTON		0x001000	/* Do not display the 'new-directory' button */
#define Pt_FSR_NO_SELECT_FILES		0x002000	/* Files are not selectable */
#define Pt_FSR_SELECT_DIRS		0x004000	/* Directories are selectable (Only the 'Open' button can select them!) */
#define Pt_FSR_CREATE_PATH		0x008000	/* Create directories as needed when typed in manually. */
#define Pt_FSR_NO_CONFIRM_CREATE_PATH	0x010000	/* Do not confirm directory creation */
#define Pt_FSR_NO_DELETE		0x020000	/* Disable deletions via the "Delete" key */
#define Pt_FSR_NO_CONFIRM_DELETE	0x040000	/* Do not confirm deletions */
#define Pt_FSR_RECURSIVE_DELETE		0x080000	/* Enable recursive deletion of directories */
#define Pt_FSR_CONFIRM_EXISTING  	0x100000	/* Confirm the selection of an existing file with an "Overwrite xxxx ?" message */
#define Pt_FSR_CENTER			0x200000	/* Center the file-selection dialog. Only used by the PtFileSelect */
							/* convenience functions. Takes presedence over "pos" specified as */
							/* an argument to PtFileSelection. */
#define Pt_FSR_MULTIPLE                 0x01000000      /* Enable multiple selection mode. Also the reason
							 * subtype in confirm_selection callbacks. */

#define Pt_FSR_ALL_FSR_FLAGS   ( Pt_FSR_NO_FCHECK | Pt_FSR_NO_FSPEC | Pt_FSR_NO_UP_BUTTON | Pt_FSR_NO_NEW | \
				 Pt_FSR_NO_NEW_BUTTON | Pt_FSR_NO_SELECT_FILES | Pt_FSR_SELECT_DIRS | \
				 Pt_FSR_CREATE_PATH | Pt_FSR_NO_CONFIRM_CREATE_PATH | Pt_FSR_NO_DELETE | \
				 Pt_FSR_NO_CONFIRM_DELETE | Pt_FSR_RECURSIVE_DELETE | Pt_FSR_CONFIRM_EXISTING | \
				 Pt_FSR_CENTER | Pt_FSR_MULTIPLE )

#define Pt_FSR_ALL_FLAGS  ( Pt_FSR_ALL_FS_FLAGS | Pt_FSR_ALL_FSR_FLAGS )


/*--------------------------------------
 * Pt_CB_FSR_DIR_CREATED reason subtypes
 *--------------------------------------*/

#define Pt_CB_FSR_DIR_MANUAL           	0		/* The directory was created on explicit command */
#define Pt_CB_FSR_DIR_AUTO             	1		/* The directory was created automatically */


/*-------------------------------
 * Resources: Basic Functionality
 *-------------------------------*/


#define Pt_CB_FSR_SELECTION				Pt_RESOURCE( 71,  0 )	/* File-selection cb */
#define Pt_CB_FSR_DISPLAY				Pt_RESOURCE( 71,  1 )	/* Display-confirmation cb */
#define Pt_CB_FSR_DIRECTORY   			Pt_RESOURCE( 71,  2 )	/* New directory notification cb */

#define Pt_ARG_FSR_FLAGS				Pt_RESOURCE( 71,  3 )	/* File-selection flags */
#define Pt_ARG_FSR_FILENAME				Pt_RESOURCE( 71,  4 )	/* (write only) Path which may terminate in a suggested filename */
#define Pt_ARG_FSR_COMMAND				Pt_RESOURCE( 71,  5 )	/* (write only) Command Resource: select/delete/make new dir */


/*-------------------
 * Resources: Strings
 *-------------------*/

#define Pt_ARG_FSR_LBL_OVR_TITLE 		Pt_RESOURCE( 71,  6 )	/* Title of the 'Overwrite'dialog */
#define Pt_ARG_FSR_LBL_OVR_MESSAGE		Pt_RESOURCE( 71,  7 )	/* 'Overwrite' message */
#define Pt_ARG_FSR_LBL_OVR_OK			Pt_RESOURCE( 71,  8 )	/* Label of the 'Overwrite' button */
#define Pt_ARG_FSR_LBL_OVR_CANCEL		Pt_RESOURCE( 71,  9 )	/* Label of the 'Don't Overwrite' button */

#define Pt_ARG_FSR_LBL_DIR_TITLE 		Pt_RESOURCE( 71, 10 )	/* Title of the 'Create Directory' dialog */
#define Pt_ARG_FSR_LBL_DIR_MESSAGE		Pt_RESOURCE( 71, 11 )	/* 'Create Directory' message */
#define Pt_ARG_FSR_LBL_DIR_OK			Pt_RESOURCE( 71, 12 )	/* Label of the 'Create Directory' button */
#define Pt_ARG_FSR_LBL_DIR_CANCEL		Pt_RESOURCE( 71, 13 )	/* Label of the 'Don't create directory' button  */
#define Pt_ARG_FSR_LBL_DIR_ERR_TITLE	Pt_RESOURCE( 71, 14 )	/* "Create New Directory" */
#define Pt_ARG_FSR_LBL_DIR_ERR_MESSAGE	Pt_RESOURCE( 71, 15 )	/* "Unable to create directory" */
#define Pt_ARG_FSR_LBL_DIR_ERR_OK     	Pt_RESOURCE( 71, 16 )	/* "&OK" */
#define Pt_ARG_FSR_LBL_DIR_BALLOON_UP	Pt_RESOURCE( 71, 17 )	/* Ballon help for the 'up-directory' button */
#define Pt_ARG_FSR_LBL_DIR_BALLOON_NEW	Pt_RESOURCE( 71, 18 )	/* Ballon help for the 'new-directory' button */

#define Pt_ARG_FSR_LBL_DEL_TITLE 		Pt_RESOURCE( 71, 19 )	/* Title of the 'Delete'dialog */
#define Pt_ARG_FSR_LBL_DEL_MESSAGE		Pt_RESOURCE( 71, 20 )	/* 'Delete' message */
#define Pt_ARG_FSR_LBL_DEL_OK			Pt_RESOURCE( 71, 21 )	/* Label of the 'Delete' button */
#define Pt_ARG_FSR_LBL_DEL_CANCEL		Pt_RESOURCE( 71, 22 )	/* Label of the 'Don't delete' button */
#define Pt_ARG_FSR_LBL_DEL_ERR_TITLE	Pt_RESOURCE( 71, 23 )	/* "Deletion Error" */
#define Pt_ARG_FSR_LBL_DEL_ERR_MESSAGE	Pt_RESOURCE( 71, 24 )	/* "Unable to delete" */
#define Pt_ARG_FSR_LBL_DEL_ERR_OK		Pt_RESOURCE( 71, 25 )	/* "&OK" */

#define Pt_ARG_FSR_LBL_LOCATION			Pt_RESOURCE( 71, 26 )	/* 'Location:' label */
#define Pt_ARG_FSR_LBL_NAME				Pt_RESOURCE( 71, 27 )	/* 'Name:' label */
#define Pt_ARG_FSR_LBL_FILTER      		Pt_RESOURCE( 71, 28 ) 	/* 'Filter:' label */

#define Pt_ARG_FSR_LBL_DEL_ALL			Pt_RESOURCE( 71, 29 )	/* Label of the 'Delete All' button */
#define Pt_ARG_FSR_LBL_SKIP			Pt_RESOURCE( 71, 30 ) 	/* Label of the 'Skip' button */


/*-------------------------
 * Resources: miscellaneous
 *-------------------------*/
#define Pt_ARG_FSR_FSPEC      		      	Pt_RESOURCE( 71, 200) /* fspec pattern */


typedef struct pt_fileselector_info {

	char *path;
	struct stat *lstatbuf;
	struct stat *statbuf;
	int nitems;
	char **multipath;
	PtFileSelItem_t **items;

} PtFileSelectorInfo_t;



typedef struct Pt_fileselection_info {

	short ret;

	char path[(PATH_MAX + NAME_MAX + 4) & (~3)];

	PhDim_t dim;			/* Desired/Terminal size of the file-selection dialog */

	PhPoint_t pos;			/* Desired/Terminal position of the file-selection dialog */

	char format[80];		/* Input/Terminal format of the file-selection dialog */

	char fspec[80];			/* On entry: Input root directory. On Exit:Terminal selected fspec */

	void *user_data;		/* Arbitrary user data to pass back to "confirm_display", "confirm_selection" and */
							/* "new_directory" functions. */

	int (*confirm_display)	( PtWidget_t *widget, void *data, PtCallbackInfo_t *cbinfo );
							/* Confirm the display of a directory item */

	int (*confirm_selection)( PtWidget_t *widget, void *data, PtCallbackInfo_t *cbinfo );
							/* Confirm a selection. */

	int (*new_directory)	( PtWidget_t *widget, void *data, PtCallbackInfo_t *cbinfo );
							/* Notification after a new directory has been created. */

	char *btn1;				/* label of the 'Open' button */

	char *btn2;				/* label of the 'Cancel' button */

	int num_args;			/* Number of args to set in the PtFileSelector/PtFileSel widgets */

	PtArg_t *args;			/* args for the PtFileSelector/PtFileSel widgets */
   
	PtFileSelectorInfo_t *minfo;	 /* Multiple selection info. */
   
	long spare[3];

} PtFileSelectionInfo_t;




/*-----------------------
 * PtFileSelect() buttons
 *-----------------------*/

#define Pt_FSDIALOG_BTN1			1
#define Pt_FSDIALOG_BTN2			2


/*----------------------------
 * PtFileSelect() legacy flags
 *----------------------------*/

#define Pt_FSDIALOG_NO_FCHECK		Pt_FSR_NO_FCHECK
#define Pt_FSDIALOG_NO_FSPEC		Pt_FSR_NO_FSPEC
#define Pt_FSDIALOG_NO_UP_BUTTON	Pt_FSR_NO_UP_BUTTON
#define Pt_FSDIALOG_SHOW_HIDDEN		Pt_FS_SHOW_HIDDEN


/*-----------------------------------------------------
 * Prototypes of the PtFileSelect convenience functions
 *-----------------------------------------------------*/

int PtFileSelect( PtWidget_t *parent, char const *title, PtFileSelectionInfo_t *info );


int PtFileSelection(PtWidget_t *parent, PhPoint_t const *pos, char const *title, char const *root_dir,
	char const *file_spec, char const *btn1, char const *btn2, char const *format, PtFileSelectionInfo_t *info, int flags);

int PtFSFreeInfo( PtFileSelectionInfo_t *info );

   
#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtFileSelection.h $ $Rev: 219996 $" )
#endif
