#ifndef __XML_TREE_H_INCLUDED
#define __XML_TREE_H_INCLUDED

#ifdef __cplusplus
	extern "C" {
#endif

/* =============================================================

 libxmltree.a

 The libxmltree.a API is used to work with tree structures with the XML node structure.
 This header file defines the functions available.

 All functions are parameter-checked for NULL/invalid settings.
 As such, explicit result checking is not always required.

 =============================================================*/

struct xml_tl_element;
typedef struct xml_tl_element xml_tl_element_t;
struct xml_treelist;
typedef struct xml_treelist xml_treelist_t;

typedef void (*xml_treelist_cb_f)(xml_tl_element_t *treelist_element, int element_number, void *cbdata);

/* =============================================================
 API Constant definitions
 =============================================================*/

#define XML_TREEMODE_EXPLICIT	 0
#define XML_TREEMODE_WALK_UP	 1

#define MERGE_STANDARD			0x00			/* No options are to be used */
#define MERGE_FILTER_ORIGINAL	0x02			/* Filter first block by attribute */
#define MERGE_KEEP_CHILDREN		0x04			/* Copy each matching node's children as well */
#define MERGE_KEEP_MULTIPLE		0x08			/* Keep the 'xmlmultiple' attributes at end of function */

/*
 A TreeList is simply a list of Tree entries that will be compared with a node's tree.
 Each entry consists of a Name, and any number of Attributes.
 Create a new list by using XML_TreeListInit, then you can either call a function which will
 fill the TreeList, or fill the TreeList yourself, using XML_TreeListAddName or
 XML_TreeListAddAttribute.
 Clear the TreeList by calling XML_TreeListClear.
 Destroy the TreeList by calling XML_TreeListDestroy.

 Here are a couple of examples of when to use a TreeList:
 Create a new TreeList, and pass it to XML_TreeGetTags to fill the list with the entries
 required to get from a basenode, to the specified node.
 When doing a XML_TreeFindTreeInList, pass a TreeList to search for the tree structure
 you have created.
 Use XML_TreeCompose to fill in the required tree elements specified in the TreeList,
 if they are not already there.
*/

xml_treelist_t *XML_TreeListInit(void);
	/* This function initializes a new xml_treelist_t variable, and returns a pointer to it.
	 'xml_treelist_t' is a list of tags to be walked through to find a particular node.
	 Its elements are created using the XML_TreeAddName and XML_TreeAddAttribute
	 functions.
	 The xml_treelist_t is used in most Tree* functions, as defined below.
	 Returns NULL if the xml_treelist_t cannot be created.
	 */
xml_tl_element_t *XML_TreeListAddName(xml_treelist_t *tree, const char *node_name, xml_node_t *srcnode);
	/* Adds an element to 'tree', specifying the 'node_name' that must be matched.
	 A pointer to the xml_tl_element_t element is returned, and can be used in calling the
	 XML_TreeAddAttribute function.
	 Add elements from the most detail (innermost node) to least.
	 'srcnode' is the source node from which this tree entry was generated (used in
	 XML_TreeCompose function to set a node's userdata).
	 Returns NULL if the element cannot be added.
	 */
int XML_TreeListAddAttribute(xml_tl_element_t *tree_element, const char *attribute_name, const char *attribute_value);
	/* Given a pointer to a previously-added xml_tl_element_t 'tree_element', an 'attribute_name' and
	 'attribute_value' is also added. Thus, for the tree element to match a given tree, the
	 name and any number of tree attributes must also be matched.
	 Returns 0 on success, -1 on failure.
	 */
int XML_TreeListRemoveLast(xml_treelist_t *tree);
	/* This function removes the last entry in 'tree'.
	 Returns 0 if an item was removed, -1 otherwise.
	 */
int XML_TreeListCallback(xml_treelist_t *treelist, xml_treelist_cb_f function, void *cbdata);
	/* Calls the specified callback 'function' for each element of 'treelist'.
	 Returns 0 on success, -1 on failure.
	 */
int XML_TreeListClear(xml_treelist_t *tree);
	/* This function clears all previous entries in the 'tree' xml_treelist_t structure.
	 The 'tree' variable is still available for use.
	 Returns 0 on success, -1 on failure.
	 */
int XML_TreeListDestroy(xml_treelist_t *tree);
	/* This function calls XML_TreeClear to erase all previous entries in the 'tree'.
	 It then deletes all allocated memory associated with 'tree'.
	 Be sure to remove all references to 'tree' after calling this function.
	 Returns 0 on success, -1 on failure.
	 */

/* == XML_NodeTree* functions ========================================== */

int XML_TreeGetTags(xml_treelist_t *tree, xml_node_t *node, xml_node_t *basenode);
	/* For the given 'node', 'tree' is cleared, and filled with the node's name, and each
	 of its ancestor's names, up to (but not including) the 'basenode' node.
	 If 'basenode' is NULL or if 'basenode' is not an ancestor of 'node', all tags will be
	 filled, up to the root of the node tree.
	 Returns 0 on success, -1 on failure.
	 */
xml_node_t *XML_TreeGetNode(xml_node_t *basenode, xml_treelist_t *tree, const char *const *attributes_to_match, int num_attributes);
	/* Searches through the given 'tree' (arranged deepest to oldest ancestor node),
	 starting at 'basenode', and returns a pointer to the first node which is in the tree
	 at that position.
	 The list of strings in 'attributes_to_match' are those attributes which matter, when
	 determining whether two nodes are the same.
	 'num_attributes' must be set to the number of entries in the 'attributes_to_match' array.
	 If 'num_attributes' is 0, no attributes will be considered when determining a match.
	 If 'num_attributes' is -1, all attributes will be considered when determining a match.
	 Returns NULL if no such node is found.
	 */
xml_node_t *XML_TreeCompose(xml_node_t *basenode, xml_treelist_t *tree, const char *const *attributes_to_match, int num_attributes);
	/* Ensures that each element of the 'tree' is present within 'basenode'.
	 If any node is missing, it and its child sub-nodes are created.
	 The list of strings in 'attributes_to_match' are those attributes which matter, when
	 determining whether two nodes are the same.
	 'num_attributes' must be set to the number of entries in the 'attributes_to_match' array.
	 If 'num_attributes' is 0, no attributes will be considered when determining a match.
	 If 'num_attributes' is -1, all attributes will be considered when determining a match.
	 If 'num_attributes' is -2, no attributes will be considered when determining a match, and
	 no attributes from the treelist will be copied while composing the new tree.
	 A pointer to the innermost node is returned on success, or NULL on failure.
	 */
xml_node_t *XML_TreeDetailsMatch(xml_node_t *node, xml_tl_element_t *entry, const char *const *attributes_to_match, int num_attributes);
	/* This function is called internally by XML_TreeGetNode and XML_TreeCompose.
	 Searches 1 level deep within the given 'node' to see if the node contains a
	 sub-node which matches the xml_tl_element_t 'entry'.
	 The list of strings in 'attributes_to_match' are those attributes which matter, when
	 determining whether two nodes are the same.
	 'num_attributes' must be set to the number of entries in the 'attributes_to_match' array.
	 If 'num_attributes' is 0, no attributes will be considered when determining a match.
	 If 'num_attributes' is -1, all attributes will be considered when determining a match.
	 One exception is that if the tree 'entry' has a name of "xml..", the search will go up one
	 level, and attributes will not be checked to be considered a match.
	 Returns a pointer to the first sub-node which matches the 'entry'.
	 */
xml_node_t *XML_TreeFindTreeInList(xml_treelist_t *tree, xml_nodelist_t *list, int mode, const char *const *attributes_to_match, int num_attributes);
	/* This function searches for a particular 'tree', by searching each node in 'list'.
	 If 'mode' is TREE_MODE_WALK_UP, then not finding a match in the initial search
	 causes the function to go to the parent of each node in the 'list'.
	 The list must be created with 'data' values showing how many levels of ancestor
	 are to be searched, for each node in the list.
	 The search continues until a match is found, or until no nodes in the list permit
	 further parental searching.
	 Set list values, with data. The data should be equal to the number of levels
	 to search up for the individual list entries, if 'mode' is TREE_MODE_WALK_UP.
	 The list of strings in 'attributes_to_match' are those attributes which matter, when
	 determining whether two nodes are the same.
	 'num_attributes' must be set to the number of entries in the 'attributes_to_match' array.
	 If 'num_attributes' is 0, no attributes will be considered when determining a match.
	 If 'num_attributes' is -1, all attributes will be considered when determining a match.
	 Set the data to -1 to search all the way up the tree.
	 Returns a pointer to the innermost tree node, or NULL if it cannot be found.
	 */
xml_treelist_t *XML_TreeFromDelimitedString(const char *source_string, xml_treelist_t *treelist, const char *tag_name, const char *attribute_name, char delimiter);
	/* Creates a xml_treelist_t of items for the specified 'delimiter' separated 'string'.
	 Pass a pointer to a 'treelist' which has been previously initialized with XML_TreeListInit.
	 The resultant 'treelist' will normally be passed to XML_TreeCompose or XML_TreeGetNode,
	 following this function.
	 Set 'tag_name' to the name of each entry in the treelist, or NULL to fill the treelist names
	 with the values from the delimited string.
	 Set 'attribute_name' to the attribute's name which is to be set with the value from the
	 delimited string. 'attribute_name' is ignored if 'tag_name' is NULL.
	 Returns a pointer to 'treelist' on success, NULL on failure.
	 */
int XML_TreeToDelimitedString(xml_treelist_t *treelist, char *result_string, const char *attribute_name, char delimiter, int backward);
	/* Fills the given 'result_string' with a delimited string, created from the given 'treelist'.
	 If 'attribute_name' is NULL, then the tag-names of each node in the 'treelist' is used
	 as the string.
	 If 'attribute_name' is not NULL, then the attribute specified will be used as the string.
	 Pass a pointer to a 'treelist' which has been previously initialized with XML_TreeListInit, and
	 filled with the tree to be string-delimited.
	 If 'delimiter' is 0, then no delimiters are added.
	 'backward' should be 0. Otherwise, the treelist will be parsed in the opposite direction.
	 Returns -1 on failure, 0 on success.
	 */

/* == XML_NodeTreeMerge* functions ========================================= */

int XML_TreeMerge(xml_node_t *node, xml_node_t *merge_node, const char *attribute_name, const char *const *attributes_to_match, int num_attributes);
	/* Takes an existing 'node', and imports the elements in 'merge_node' which have
	 an 'attribute_name' which matches the one specified.
	 The attribute can have a value 'append' or 'replace', which will determine whether
	 the merged node is added to existing nodes, or whether it replaces any other node
	 with the same name as the one being added.
	 The list of strings in 'attributes_to_match' are those attributes which matter, when
	 determining whether two nodes are the same.
	 'num_attributes' must be set to the number of entries in the 'attributes_to_match' array.
	 If 'num_attributes' is 0, no attributes will be considered when determining a match.
	 If 'num_attributes' is -1, all attributes will be considered when determining a match.
	 Returns the number of merges that were successful.
	 */
xml_node_t *XML_TreeMergeAll(const char *name, xml_nodelist_t *nodelist, xml_find_cb_f condition_function, void *condition_cbdata, const char *const *attributes_to_match, int num_attributes, int flags);
	/* From the given 'nodelist', a new tree is created from the trees pointed to by the list.
	 A pointer to this new tree is returned.
	 For 'flags', see the MERGE_* definitions.

	 A parent node called 'name' will be created under which all merged nodes appear.
	 Going backward through the 'nodelist', from the last item, to the first item,
	 each node's tree is entirely passed to XML_TreeCompose, to ensure that items
	 in the trees at the beginning of the list overwrite those at the end of the list.
	 Such a combination can be used to merge many trees together to form a complete
	 tree, where the first node in the list is the most detailed information, and the nodes
	 at the end of the tree are more default values that show through if they have not
	 been explicitly overridden.

	 The 'condition_function' should return 0 for each node that is to be prevented from
	 being considered in the merge.
	 The 'condition_function' filter is not performed on the base tree (last in the list) unless
	 the MERGE_FILTER_ORIGINAL flag is set.
	 If 'condition_function' is NULL, all nodes are added to the tree.
	 The 'condition_cbdata' pointer will be passed to the 'condition_function' as a parameter.
	 If any node in the trees pointed to by 'nodelist' contains an attribute showing
	 (xmlremoved="true"), that branch of the tree will be completely removed from the
	 returned tree, before the next tree is overlayed.

	 The list of strings in 'attributes_to_match' are those attributes which matter, when
	 determining whether two nodes are the same.
	 'num_attributes' must be set to the number of entries in the 'attributes_to_match' array.
	 If 'num_attributes' is 0, no attributes will be considered when determining a match.
	 If 'num_attributes' is -1, all attributes will be considered when determining a match.
	 If 'num_attributes' is -3, all attributes will be considered when determining a match, except unsaved attributes.

	 For each NODE_TYPE_ELEMENT node which is added, its 'userdata' is set so that the
	 new node points to the (most recent) node that created the node.
	 Memory will be allocated in this function, so be sure to keep the returned pointer,
	 and use XML_NodeLinkToNode to combine it with an existing tree, or save it directly.

	 If a node being merged has an attribute called xmlmultiple="true",
	 then multiple entries of that type are allowed in the final document. As long as
	 'num_attributes' is -1, or 'attributes_to_match' includes 'xmlmultiple', then the attribute
	 (xmlmultiple) will be removed from the final merged document. And multiple entries
	 will simply be added instead of changed when another layer is merged over the first.
	 Since the attribute must be matched, the old 'xmlmultiple' will be removed, and the
	 new one will be considered a new branch (also see MERGE_KEEP_MULTIPLE).

	 Returns NULL if there are no items in nodelist, or if the tree cannot be created.
	 */

/* =============================================================
 API structure definitions
 =============================================================*/

struct xml_treelist
{
	xml_tl_element_t **tag;		/* pointer to an array of *xml_tl_element_t (initially NULL) */
	int size;							/* number of elements in the array. */
};

struct xml_tl_element
{
	char *node_name;				/* node's name (tag) */
	char **attr_name;				/* array of strings of attribute names */
	char **attr_value;				/* array of strings of attribute values */
	int attrs;							/* number of attributes in the array */
	xml_node_t *srcnode;		/* node from which this tree element was generated */
};

/* ============================================================= */

#ifdef __cplusplus
	}
#endif

#endif


#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/xml/public/xmltree.h $ $Rev: 219996 $" )
#endif
