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
#ifndef __XML_PT_WIDGET_POPULATE_H_INCLUDED
#define __XML_PT_WIDGET_POPULATE_H_INCLUDED

/*--------------------------------------------------------
 * xmlphoton.h (part of exlib)
 *--------------------------------------------------------
 * Provides functions for populating PtTree, PtMenu, and PtComboBox widgets
 * with data from an XML document strutcure. Also provides a PtTreeTraverse
 * function in order to receive callbacks for each node in a PtTree widget.
 *
 * To use these functions, you must link with the following libraries:
 *		libtexpat.a
 *		libxml.a
 *--------------------------------------------------------
 */

#include <xmlnode.h>
#include <photon/PtWidget.h>

#define XML_COMBO_STYLE_TAGNAME		1
#define XML_COMBO_STYLE_TEXTDATA		2
#define XML_COMBO_STYLE_ATTRIBUTE		3

/*--------------------------------------------------------
 * Confirm callback function
 *--------------------------------------------------------
 *     node	- the current xml node
 *     tdata	- Tree item data for this node. The confirm function should set the
 *               appropriate members. The 'display_name' member is the 'display_name'
 *               parameter of XML_PtTreePopulate(), it is ignored if XML_PF_TAGNAME is set
 *               in the returned flags. The 'set_img' and the 'unset_img' members are always
 *               initialized to -1.
 *     depth	- the depth of this entry in the tree/menu (where 0 is the root-level).
 *     cbdata	- arbitrary callback data which was passed to XML_PtTreePopulate()
 *
 *	Returns: 0 to skip the node, or any of the "confirm callback return flags" (below).
 */

/*--------------------------------------------------------
 * Tree item data
 *--------------------------------------------------------
 */
typedef struct {
   char *display_name; /* buffer for the display-name */
   short set_img;      /* index of the set_image */
   short unset_img;    /* index of the unset image */
} xml_tree_data_t;

/*--------------------------------------------------------
 * Confirm callback return flags
 *--------------------------------------------------------
 */
#define XML_PF_ADD						0x0001	/* Add the node. */
#define XML_PF_CHILDREN					0x0002	/* Process the children of this node. */
#define XML_PF_ADD_IF_HAS_CHILDREN	0x0007	/* Add the node. Process its children. Remove node if it */
                                             				/* does not end up with any children or if it is excluded */
															/* by the duplicate-handling mechanism. */
#define XML_PF_TAGNAME					0x0008	/* Display the tagname (ignore the display_name buffer ) */
#define XML_PF_EXPAND					0x0010	/* Expand this node once all its children have been created. */
#define XML_PF_SORT						0x0020	/* Sort the children of this node alphabetically in the PtTree. */
															/* The sort is case sensitive. */
#define XML_PF_SORTI						0x0040	/* Case insensitive version of XML_PF_SORT. Takes precedence */
															/* over XML_PF_SORT if both sort-flags are specified. */
#define XML_PF_DUPI						0x0080	/* When the children of this node are processed, use a case */
															/* insensitive search for duplicates. */
															/* The default is a case sensitive search. */

typedef int (*XML_confirm_t) ( xml_node_t *node, xml_tree_data_t *tdata, int depth, void *cbdata );

/*--------------------------------------------------------
 * PtTreeItem user-data creation function
 *--------------------------------------------------------
 * 
 *     node   - the current XML node
 *     titem  - the PtTreeItem_t which will correspond to the XML node
 *     parent - the PtTreeItem_t which is the parent of titem
 *     cbdata - arbitrary callback data which was passed to XML_PtTreePopulate()
 *
 *  Returns: Pointer to user-data to be stored in the 'data' member of titem. 
 */

typedef void * (*XML_create_t) ( xml_node_t *node, PtTreeItem_t *titem, PtTreeItem_t *parent, void *cbdata );

/*--------------------------------------------------------
 * Duplicate callback function
 *--------------------------------------------------------
 *
 *      node   - the XML node which has a duplicate in the tree
 *      duplic - the duplicate tree item
 *      cbdata - arbitrary callback data which was passed to XML_PtTreePopulate() 
 */

/*--------------------------------------------------------
 * Duplicate callback return values
 *--------------------------------------------------------
 */ 			/*	XML_PF_ADD			1	 Add the duplicate node */
#define		XML_PF_EXCLUDE	2  /* Do not add the duplicate node */
#define		XML_PF_MERGE		3  /*  Merge the children of the duplicate node*/

typedef int (*XML_duplicate_t) ( xml_node_t *node, PtTreeItem_t *duplic, void *cbdata );

/*--------------------------------------------------------
 * Tree-traverse callback function
 *--------------------------------------------------------
 *
 *        titem		- the current tree item
 *        cbdata	- arbitrary callback data passed to XML_PtTreePopulate() or PtTreeTraverse() 
 */

typedef void (*treetraverse_t) ( PtTreeItem_t *titem, void *cbdata );

/*--------------------------------------------------------
 * XML_PtTreePopulate flags
 *--------------------------------------------------------
 *
 * XML_PF_SORT		Sort the children of troot alphabetically.
 *						The sort is case sensitive.
 *						If confirm_fn is NULL, then the tree-nodes will be sorted at every level,
 *						otherwise, the confirm_fn decides the sorting policy at each level
 *						via the flag it returns.
 * XML_PF_SORTI		Case insensitive version of XML_PF_SORT.
 *						If both sort-flags are specified, then XML_PF_SORTI takes precedence.
 * XML_PF_DUPI		When the children of xroot are processed, use a case insensitive search
 *						for duplicates. The default is a case sensitive search.
 *						If confirm_fn is NULL, then this flag will be in effect at
 *						every level, otherwise, the confirm_fn decides the case sensitivity
 *						of the duplicate search at each level via the flag it returns.
*/
/* =========================================================
 * Widget Population Functions
 * =========================================================
 */

int XML_PtTreePopulate(PtWidget_t *tree, PtTreeItem_t *troot, xml_node_t *xroot,
	XML_confirm_t confirm_fn, XML_duplicate_t duplic_fn, XML_create_t create_fn, 
	treetraverse_t destroy_fn, int flags, char *display_name, int starting_depth, void *cbdata);

	/* 'tree' is the PtTree widget to update.
	 * 'troot' is the item in the tree widget to update (can be NULL).
	 * 'xroot' is the root xml node.
	 * 'confirm_fn' is a callback to confirm whether to add a particular node
	 * (see XML_confirm_t function, above). If it's NULL, then all nodes are added.
	 * 'duplic_fn' is a callback which is called when a duplicate tree item is
	 * detected (see XML_duplicate_t and "Duplicate callback return values" above).
	 * 'create_fn' is a callback which is called when a new tree node is being
	 * added, so that you can associate arbitrary user-data to the tree node.
	 * (see XML_create_t, above).
	 * The normal user data to be put into this node is a pointer to the XML node,
	 * which is done by having the 'create_fn' return the 'node' parameter.
	 * 'destroy_fn' is a callback which is called when the tree node is being
	 * destroyed, so that you can deallocate any memory associated with the
	 * user-data for that node.
	 * 'flags' are made up of the XML_PtTreePopulate flags. above.
	 * 'display_name' is a character buffer for the display_name that will be
	 * returned to confirm_fn in the 'display_name' member of xml_tree_data_t.
	 * 'starting_depth' should be 0 ('depth' parameter for the root of the tree).
	 * 'cbdata' is arbitrary callback data which will be passed to each of the
	 * callback functions.
	 * Returns:  0 on success, -1 on error. 
	 */

int XML_PtListPopulate(PtWidget_t *widget, xml_nodelist_t *nodelist,
	xml_node_t *selected_node, int style, const char *attribute);
	
	/* Fills a PtList or PtComboBox with the elements of the given 'nodelist'.
	 * 'widget' is a pointer to the PtComboBox.
	 * 'nodelist' is the list which has been previously initialized, and filled with a number of nodes.
	 * 'selected_node' is a pointer to the node in the 'nodelist' which is to be selected.
	 * Set 'style' to one of the following XML_COMBO_STYLE_* constants:
	 *		XML_COMBO_STYLE_TAGNAME		uses each node's tag-name as the combo-box entry.
	 *		XML_COMBO_STYLE_TEXTDATA		uses each node's text data as the combo-box entry.
	 *		XML_COMBO_STYLE_ATTRIBUTE	uses each node's specified attribute as the combo-box entry.
	 * 'attribute' is a string specifying the attribute to use, if XML_COMBO_STYLE_ATTRIBUTE is used.
	 * Returns -1 if an error is detected. Otherwise, it returns the element of 'nodelist' which is
	 * originally selected in the ComboBox (0-based). 
	 */

typedef void (*XML_activate_t)(PtWidget_t *widget, xml_node_t *node, int depth, void *cbdata);

PtWidget_t *XML_PtMenuPopulate(const char *menu_title, PtWidget_t *parent, xml_node_t *node,
	XML_confirm_t confirm_fn, XML_activate_t activate_fn, char *display_name,
	int starting_depth, void *cbdata);
	
	/* 'menu_title' is the title that will appear at the top of the new menu. If it is NULL,
	 * no title will be added to the menu.
	 * 'parent' is the parent widget for the menu.
	 * 'node' is the root xml node
	 * 'confirm_fn' is a callback to confirm whether to add a particular node (see XML_PtTreePopulate.h)
	 * 'activate_fn' is the function to be called when the menu item is selected (see XML_Activate_t).
	 * Set 'depth' to -1 to recurse the entire tree.
	 * 'display_name' is a buffer, which is sent as a parameter to the confirmation function to be filled.
	 * The buffer must be a global string in your application, since it will be referenced at any
	 * time the menu is referenced, not only when XML_PtMenuPopulate is called.
	 * 'starting_depth' should be 0 ('depth' parameter for the root of the menu).
	 * 'cbdata' is arbitrary callback data to be sent to the callbacks.
	 * The function returns a pointer to the Menu widget, or NULL on error.
	 * You must set the position of the widget manually, after this function returns.
	 */

/*--------------------------------------------------------
 * Tree traversal flags
 *--------------------------------------------------------
 */
#define XML_TV_NOROOT	0x0001   /* Do not call the traverse_fn for troot (ignored if troot == NULL) */
#define XML_TV_NOBRO	0x0002   /* Do not visit the brothers of troot (ignored if troot == NULL) */

/*--------------------------------------------------------
 * PtTreeTraverse()
 *--------------------------------------------------------
 *
 * Returns:
 *            0 - ok
 *           -1 - traverse_fn==NULL or (tree==NULL && troot==NULL) or tree is empty.
 */

int PtTreeTraverse(
			PtWidget_t *tree, 				/* the PtTree widget to traverse */
												/* if tree == NULL, then "troot" will be traversed */
			PtTreeItem_t *troot, 			/* The tree-item to traverse, If troot == NULL, */
												/* then traversal will start with the first root */
			     								/* item in "tree". */
			treetraverse_t traverse_fn,	/* Function to call for each node. */
			int flags,							/* Tree traversal flags. (See above.) */
			void *cbdata						/* Arbitrary cb data returned to traverse_fn */
			);

/* ===  Example code using XML_PtMenuPopulate ================================
 *
 *	void menucallback(PtWidget_t *widget, xml_node_t *node, void *data)
 *	{
 *		// Menu item has been selected
 *		printf("Item selected: %s\n", XML_NodeNameGet(node));
 *	}
 *	
 *	int confirmmenu(xml_node_t *node, xml_tree_data_t *data, void *cbdata)
 *	{
 *		int ret=XML_PF_ADD | XML_PF_CHILDREN;
 *		if(node==NULL || data==NULL) return(0);
 *		strncpy(data->display_name, XML_NodeNameGet(node), 254);
 *		data->display_name[255]=0;
 *		return(ret);
 *	}
 *	
 *	int TestMenu( PtWidget_t *widget, ApInfo_t *apinfo, PtCallbackInfo_t *cbinfo )
 *	{
 *		PtWidget_t *menu;
 *		PhPoint_t pos, window;
 *		short x, y;
 *		xml_node_t *node;
 *		char name_buffer[256];
 *
 *		node=XML_DocumentInit();				// Note: Loading the document beforehand would be more efficient
 *		if(XML_DocumentLoad(node, "xml_filename", NULL, NULL, NULL)!=-1)
 *		{
 *			menu=XML_PtMenuPopulate(NULL, ABW_MainWindow, node, confirmmenu, menucallback, -1, name_buffer, NULL);
 *			PtGetAbsPosition(widget, &x, &y);
 *			pos.x=x-4; pos.y=y+26;
 *		
 *			PtSetResource(menu, Pt_ARG_POS, &pos, 0);
 *			PtRealizeWidget(menu);
 *		}
 *
 *		XML_DocumentDestroy(node); node=NULL;
 *		return( Pt_CONTINUE );
 *	} 
 */

#endif

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/phexlib/public/photon/xmlphoton.h $ $Rev: 224591 $" )
