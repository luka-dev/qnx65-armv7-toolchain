#ifndef __XML_NODE_H_INCLUDED
#define __XML_NODE_H_INCLUDED

#include <sys/stat.h>
#include <sys/types.h>

#ifdef __cplusplus
	extern "C" {
#endif

/* =============================================================

 libxmlnode.a

 The libxmlnode.a API is used to create/load/save XML files.

 It also includes a number of functions which allow you to edit the nodes of data
 in memory, move the data inside (or between) documents, search for nodes, or
 delete various parts of the document.

 This header file defines the functions available.

 All functions are parameter-checked for NULL/invalid settings.
 As such, explicit result checking is not always required.

 ============================================================= */

struct xml_node;
typedef struct xml_node xml_node_t;
struct xml_document;
typedef struct xml_document xml_document_t;
struct xml_element;
typedef struct xml_element xml_element_t;
struct xml_text;
typedef struct xml_text xml_text_t;
struct xml_attt;
typedef struct xml_attr xml_attr_t;
struct nodelist;
typedef struct xml_nodelist xml_nodelist_t;
struct xml_apinfo;
typedef struct xml_apinfo xml_apinfo_t;
struct xml_callback;
typedef struct xml_callback xml_callback_t;
struct xml_find;
typedef struct xml_find xml_find_t;
struct xml_file_info;
typedef struct xml_file_info xml_file_info_t;
struct xml_parse_info;
typedef struct xml_parse_info xml_parse_info_t;

typedef int (*xml_error_cb_f)(xml_node_t *node, const char *filename, int error_code, int line, int column, void *cbdata);
	/* for error_code, see xmlparse.h definitions of XML_ERROR_* and XML_WARNING_* */
typedef int (*xml_node_cb_f)(xml_node_t *callback_node, xml_node_t *child_node, int handle, void *cbdata, int reason);
typedef int (*xml_find_cb_f)(xml_node_t *callback_node, void *cbdata);
typedef int (*xml_file_confirm_cb_f)(xml_file_info_t *file_info, void *cbdata);
typedef void (*xml_file_create_cb_f)(xml_node_t *callback_node, xml_file_info_t *file_info, void *cbdata);
typedef int (*xml_nodelist_cb_f)(xml_node_t *callback_node, int data, int element_number, void *cbdata);

/* =============================================================
 API Constant definitions
 ============================================================= */

#define RESULT_SUCCESS			 			0
#define RESULT_FAILURE						-1

#define ERR_NO_ANSWER						-1
#define ERR_NO_DOCUMENT					-2

#define XML_TYPE_CLEAR			 			0
#define XML_TYPE_DOCUMENT				1
#define XML_TYPE_ELEMENT					2
#define XML_TYPE_TEXT						3
#define XML_TYPE_COMMENT				4
#define XML_TYPE_CBLOCK					5
#define XML_TYPE_ATTR						6
#define XML_TYPE_PROC_INST				7
#define XML_TYPE_DOCUMENT_NO_CB		8

#define XML_CB_NODE_MODIFIED	 		0x01
#define XML_CB_NODE_DELETED	 			0x02
#define XML_CB_CHILD_ADDED		 		0x04
#define XML_CB_CHILD_MODIFIED	 		0x08
#define XML_CB_CHILD_DELETED	 		0x10
#define XML_CB_ALL_NODE			 		0x03
#define XML_CB_ALL_CHILD			 		0x1C
#define XML_CB_ALL				 				0x7F
#define XML_CB_RESERVED					0x80

#define XML_ATTRIBUTE_UNSAVED			0x01

#define XML_SAVE_DEFAULT					0x00
#define XML_SAVE_UNSAVED_ATTR			0x01
#define XML_SAVE_NO_SHORTFORM		0x02

#define XML_NODE_FIND_ADD				0x0001		/* This node is to be added to the nodelist */
#define XML_NODE_FIND_SKIP		 		0X0002		/* This node should not be added to the nodelist */
#define XML_NODE_FIND_NO_CHILDREN	0x0004		/* Do not search children of this node */

#define XML_DIR_SHOW_HIDDEN				0x01			/* Also show .* files */
#define XML_DIR_NO_DEEP_DIRS				0x02			/* Does not show directory names at deepest level */

#define XML_DC_ADD							0x01
#define XML_DC_CHILDREN					0x02

/* =============================================================
 Common API functions...
 ============================================================= */

/* == Setting up an XML document ======================================= */

xml_node_t *XML_DocumentInit(const char *name);
	/* This function is called to create a new document.
	 Allocates memory for a new document and sets its members to default values.
	 The 'name' string is used internally only, to identify the document. It will not be
	 saved in any way in the XML file.
	 Returns a pointer to the new document.
	*/
xml_node_t *XML_DocumentInitNoCB(const char *name);
	/* Same as XML_DocumentInit but callbacks are disabled for the entire document.
	 Returns a pointer to the new document.
	*/
int XML_DocumentLoad(xml_node_t *load_node, const char *filename, const char *starting_tag, xml_error_cb_f error_function, void *cbdata);
	/* Load an XML file into the specified 'load_node'.
	 All previous children of the 'load_node' will be destroyed before loading takes place.
	 The tags in 'filename' will be ignored until the 'starting_tag' tag is detected.
	 If 'starting_tag' is NULL, the entire document is loaded.
	 'error_function' is a callback function, which is called when an error is detected
	 while parsing the XML file. If the callback function returns -1, the loading will stop,
	 otherwise, the file will continue to be parsed with all errors generating a callback.
	 If 'error_function' is NULL, errors are printed to the screen.
	 Returns -1 if an error is detected while loading the file, and 0 otherwise.
	 */
int XML_DocumentLoadWithout(xml_node_t *load_node, const char *filename, const char *starting_tag, const char *ignore_tag, xml_error_cb_f error_function, void *cbdata);
	/* Load an XML file into the specified 'load_node'.
	 All previous children of the 'load_node' will be destroyed before loading takes place.
	 The tags in 'filename' will be ignored until the 'starting_tag' tag is detected.
	 If 'starting_tag' is NULL, the entire document is loaded.
	 If 'ignore_tag' is NULL, the entire document is loaded, otherwise any tag matching 'ignore_tag' will be completely ignored and not loaded.
	 'error_function' is a callback function, which is called when an error is detected
	 while parsing the XML file. If the callback function returns -1, the loading will stop,
	 otherwise, the file will continue to be parsed with all errors generating a callback.
	 If 'error_function' is NULL, errors are printed to the screen.
	 Returns -1 if an error is detected while loading the file, and 0 otherwise.
	 */
int XML_DocumentSave(xml_node_t *save_node, const char *filename, int IndentSpaces, int flags);
	/* Saves the specified node and its sub-nodes as an XML file.
	 If 'filename' is NULL and 'save_node' points to a previously-loaded document,
	 the loaded filename will be used in saving back to disk.
	 Otherwise, 'filename' must be specified.
	 'IndentSpaces' indicates how much to indent sub-blocks in the formatted XML file. It
	 should be a small value (usually 4, 3, or 2).
	 Setting 'IndentSpaces' to 0 causes the XML file to be completely flat (no indentation).
	 For 'flags', see the XML_SAVE_* definitions.
	 Returns -1 on error, 0 otherwise.
	 */
int XML_DocumentDestroy(xml_node_t *document);
	/* This function is called to completely remove the specified document from memory.
	 Calls XML_DocumentClear() to remove all nodes from the document, and frees
	 all memory allocated with the document.
	 Be sure to clear all pointers to nodes within this document, and pointers
	 to the document itself, as they will no longer be valid after calling this function.
	 */

/* == Adding nodes; determining children and ancestors. ========================= */

xml_node_t *XML_NodeAddToNode(xml_node_t *parent_node, const char *tag_name);
	/* Adds a new node of the given 'tag_name', as a child of the specified 'parent_node'.
	 Returns a pointer to the new node on success, NULL on failure.
	 */
xml_node_t *XML_NodeGetParent(xml_node_t *child_node);
	/* Returns the parent node of the specified 'child_node'.
	 Returns NULL if this node is the document itself, or if the 'child_node' has been
	 copied or unlinked.
	 */
xml_node_t *XML_GetAncestorNamed(xml_node_t *child_node, const char *ancestor_name);
	/* If the given 'child_node' has an ancestor with the given 'ancestor_name',
	 a pointer to the ancestor will be returned.
	 Returns NULL if such an ancestor is not found.
	 */
xml_node_t *XML_GetChildNamed(xml_node_t *parent_node, const char *child_name);
	/* If the given 'parent_node' has an immediate child with the given 'child_name',
	 a pointer to the chld will be returned.
	 If 'child_name' is NULL, the first child node will be returned.
	 Returns NULL if such an child is not found.
	 */

/* == Checking a node's tag name ======================================= */

int XML_NodeNameEquals(xml_node_t *node, const char *compare_to);
	/* Performs a comparison between the 'node' name and the 'compare_to' string.
	 Returns 1 if they are an exact match, or 0 otherwise.
	 Returns 1 if both the node name and 'compare_to' are NULL.
	 */
const char *XML_NodeNameGet(xml_node_t *node);
	/* This function returns a pointer to the name of the specified 'node'.
	 Returns NULL if the node has no name.
	 */

/* == Working with attributes =========================================== */

int XML_NodeAttributeEquals(xml_node_t *node, const char *name, const char *compare_to);
	/* Performs a comparison between the attribute named 'name' and the 'compare_to' string.
	 Returns 1 if they are an exact match, or 0 otherwise.
	 Returns 1 if both 'name' and 'compare_to' are NULL.
	 Returns 0 otherwise.
	 */
int XML_NodeAttributeEqualsInherited(xml_node_t *node, const char *name, const char *compare_to);
	/* Performs a comparison between the attribute named 'name' and the 'compare_to' string.
	 If the node does not have such an attribute, its ancestors are searched for the
	 same attribute until a match is found.
	 Returns 1 if they are an exact match, or 0 otherwise.
	 Returns 1 if both 'name' and 'compare_to' are NULL.
	 Returns 0 otherwise.
	 */
const char *XML_NodeAttributeGet(xml_node_t *parent_node, const char *name);
	/* Returns a pointer to the value of the attribute named 'name' for the given 'parent_node'.
	 Returns NULL if the attribute does not exist.
	 */
const char *XML_NodeAttributeGetInherited(xml_node_t *node, const char *name);
	/* Returns a pointer to the value of the attribute named 'name' for the given 'parent_node'.
	 If the node does not have such an attribute, its ancestors are searched for the
	 same attribute until one is found.
	 Returns NULL if the attribute does not exist.
	 */
int XML_NodeAttributeGetAsInteger(xml_node_t *parent_node, const char *name);
	/* Gets the attribute specified using XML_NodeAttributeGetValue.
	 Converts the value to integer, and returns the value.
	 Returns 0 if the value is not numeric.
	 */
xml_attr_t *XML_NodeAttributeSet(xml_node_t *parent_node, const char *name, const char *value);
	/* Changes the attribute named 'name' of a given 'parent_node', to the specified 'value'.
	 If no such attribute is present, a new attribute will be added to the node with
	 this name and value.
	 Returns a pointer to the new attribute node, or NULL on failure.
	 */
xml_attr_t *XML_NodeAttributeSetFromInteger(xml_node_t *node, const char *name, int number);
	/* Creates/changes the attribute called 'name' to the string representation of 'number'.
	 Returns a pointer to the new attribute node, or NULL on failure.
	 */
xml_attr_t *XML_NodeAttributeNext(xml_node_t *node, xml_attr_t *previous_attribute);
	/* Returns the next available attribute, in the given 'node'.
	 If 'previous_attribute' is NULL, the first attribute is returned.
	 If no further attributes are available, the function returns NULL.
	 */
int XML_NodeAttributeRemove(xml_node_t *parent_node, const char *name);
	/* Removes the attribute named 'name' for the given 'parent_node'.
	 Returns 0 on success, -1 otherwise.
	 */

/* == Setting a node's textual data  ====================================== */

int XML_NodeTextEquals(xml_node_t *node, const char *compare_to);
	/* Performs a comparison between the node's raw data (as a string) and the
	 'compare_to' string.
	 Returns 1 if they are an exact match, or 0 otherwise.
	 Returns 1 if both 'compare_to' the raw data are NULL.
	 */
const char *XML_NodeTextGet(xml_node_t *node);
	/* Returns a pointer to the raw data stored for the given node.
	 Raw data can be divided with sub-nodes between, so only the
	 first recognized raw data is returned by this function.
	 To access the remaining data, you must search the the node by hand.
	 NULL is returned on failure.
	 */
int XML_NodeTextGetAsInteger(xml_node_t *node);
	/* Returns the integer value of the raw data stored for the given node.
	 Raw data can be divided with sub-nodes between, so only the
	 first recognized raw data is returned by this function.
	 To access the remaining data, you must search the the node by hand.
	 0 is returned on failure.
	 */
int XML_NodeTextSet(xml_node_t *node, const char *buffer, int len);
	/* Changes the raw data (text) for a given 'node' to the specified 'buffer' and 'length'.
	 The first raw data in the 'node' will be destroyed and overwritten with the new 'buffer'.
	 If 'len' is 0, the lengh of the string 'buffer' is used.
	 Returns 0 on success, -1 otherwise.
	 */
int XML_NodeTextSetFromInteger(xml_node_t *node, int number);
	/* Creates/changes the attribute called 'name' to the integer 'number' specified.
	 Returns 0 on success, -1 otherwise.
	 */

/* == Searching for nodes ============================================= */

xml_nodelist_t *XML_NodeListInit(void);
	/* This function creates a new 'xml_nodelist_t' which can be used in the Find* functions,
	 or in some Tree* functions.
	 Returns a pointer to the newly allocated empty list.
	 */
int XML_FindNodeWithName(xml_node_t *basenode, const char *name, int depth, xml_nodelist_t *nodelist);
	/* Supply the 'name' which must match the node's name to be considered a match.
	 if 'name' is NULL, the node's name doesn't matter, so that all tags within 'node' are
	 considered to be a match).
	 See the detailed description (below) for further information on the XML_Find* functions.
	 */
int XML_FindNodeWithAttribute(xml_node_t *basenode, const char *name, const char *value, int depth, xml_nodelist_t *nodelist);
	/* Supply an attribute 'name' and 'value' which must be present for a node, for that
	 node to be considered a match.
	 If 'name' is NULL, then all nodes with an attribute with the given value will be considered a match.
	 if 'value' is NULL, then all nodes with the given attribute name will be considered a match.
	 See the detailed description (below) for further information on the XML_Find* functions.
	 */
int XML_NodeListDestroy(xml_nodelist_t *nodelist);
	/* This function first calls XML_NodeListClear, to deallocate all memory in the list.
	 Then it deallocates the 'nodelist' itself.
	 Be sure to remove all references to the 'nodelist' after calling this function.
	 Returns the number of matches in the list before being destroyed.
	 */

/* =============================================================
 Uncommon and Internal API functions...
 ============================================================= */

/* == XML_Node* LOAD/SAVE functions ===================================== */

int XML_NodeLoad(xml_node_t *load_node, const char *filename, const char *starting_tag, const char *ignore_tag, xml_error_cb_f error_function, void *cbdata);
	/* Load an XML file into the specified 'load_node'.
	 All previous children of the 'load_node' will be destroyed before loading takes place.
	 The tags in 'filename' will be ignored until the 'starting_tag' tag is detected.
	 If 'starting_tag' is NULL, the entire document is loaded.
	 If 'ignore_tag' is NULL, the entire document is loaded, otherwise any tag matching 'ignore_tag' will be completely ignored and not loaded.
	 'error_function' is a callback function, which is called when an error is detected
	 while parsing the XML file. If the callback function returns -1, the loading will stop,
	 otherwise, the file will continue to be parsed with all errors generating a callback.
	 If 'error_function' is NULL, errors are printed to the screen.
	 Returns -1 if an error is detected while loading the file, and 0 otherwise.
	 */
int XML_NodeLoadFP(xml_node_t *load_node, FILE *fp, const char *filename, const char *starting_tag, const char *ignore_tag, xml_error_cb_f error_function, void *cbdata);
	/* Load an XML file into the specified 'load_node'.
	 All previous children of the 'load_node' will be destroyed before loading takes place.
	 'fp' must be a previously opened file pointer.
	 'filename' is only used if the 'load_node' is a document which is to be saved to 'filename'
	 at a later time. It can be NULL if this functionality is not required.
	 The tags in the open 'fp' will be ignored until the 'starting_tag' tag is detected.
	 If 'starting_tag' is NULL, the entire document is loaded.
	 If 'ignore_tag' is NULL, the entire document is loaded, otherwise any tag matching 'ignore_tag' will be completely ignored and not loaded.
	 'error_function' is a callback function, which is called when an error is detected
	 while parsing the XML file. If the callback function returns -1, the loading will stop,
	 otherwise, the file will continue to be parsed with all errors generating a callback.
	 If 'error_function' is NULL, errors are printed to the screen.
	 Returns -1 if an error is detected while loading the file, and 0 otherwise.
	 */
int XML_NodeSave(xml_node_t *save_node, FILE *fp, int last_item, int *level, int IndentSpaces, int flags);
	/* This function saves the given 'save_node' to the file pointer (fp) specified, as standard XML.
	 Set 'last_item' to 0 when calling this function.
	 Set 'level' to 0 when calling this function, and pass a pointer to it.
	 For 'flags', see the XML_SAVE_* definitions.
	 Returns 0 on success, -1 on failure, and may change 'level'.
	 */
#ifndef __MINGW32__
int XML_NodeLoadFromDirectory(xml_node_t *node, const char *directory, xml_file_confirm_cb_f file_confirm_fn, xml_file_create_cb_f file_create_fn, int depth, int flags, void *cbdata);
	/* Loads the given node with the directory structure found under 'directory'.
	 The 'file_confirm_fn' callback is called for each item in the directory structure.
	 The 'file_confirm_fn' function must return any of the XML_DC_* definitions.
	 The 'file_confirm_fn' callback is called for each item which is added.
	 'flags' is determined by the XML_DIR_* definitions.
	 Returns -1 on error, 0 on success.
	 */
#endif
int XML_NodeElementSave(xml_node_t *element, FILE *fp, int last_item, int *level, int IndentSpaces, int flags);
	/* This function is usually called internally by XML_NodeSave.
	 Stores the given node element, to the file pointer (fp) specified as standard XML.
	 Returns 0 on success, -1 on failure, and may change 'level'.
	 */
int XML_NodeParseFile(xml_node_t *load_node, FILE *fp, const char *filename, const char *starting_tag, const char *ignore_tag, xml_error_cb_f error_function, void *cbdata);
	/* Called by XML_DocumentLoad and XML_NodeLoad internally. */
int XML_ParseRawData(int reason, int buflen, char *buf, void *apinfo);
	/* Called by XML_parse internally. */

/* == XML_NodeAdd* functions =========================================== */

xml_node_t *XML_NodeAddToNodeTop(xml_node_t *parent_node, const char *tag_name);
	/* Adds a new node of the given 'tag_name', as a child of the specified 'parent_node'.
	 Ensures that the new node is the first child node under 'parent_node'.
	 Returns a pointer to the new node on success, NULL on failure.
	 */
xml_node_t *XML_NodeAddBeforeNode(int node_type, xml_node_t *node, const char *name);
	/* Adds a new node of the given 'name' and 'node_type', before the specified node.
	 Ensures that it still occurs after all attribute nodes.
	 Returns a pointer to the new node on success, NULL on failure.
	 */
xml_node_t *XML_NodeAddAfterNode(int node_type, xml_node_t *node, const char *name);
	/* Adds a new node of the given 'name' and 'node_type', after the specified node.
	 Returns a pointer to the new node on success, NULL on failure.
	 */
xml_node_t *XML_NodeAddIntoText(xml_text_t *text_node, const char *tag_name, int offset);
	/* Adds a new node of the given 'tag_name', into the 'text_node', at the given 'offset'.
	 The 'text_node' will be split into two separate nodes, with the new node between them.
	 The pointer to the original 'text_node' will still be valid, for the first portion of text.
	 If 'offset' is 0, the new node is simply added before the given 'text_node'.
	 If 'offset' exceeds the length of data in 'text_node', the new node is simply added after
	 the given 'text_node'.
	 Returns a pointer to the new node on success, NULL on failure.
	 */
xml_node_t *XML_PIAddToNode(xml_node_t *node, const char *target, const char *data);
	/* Adds a Processing Instruction of type 'target' string with a 'data' string
	 to the specified 'node'.
	 Returns a pointer to the new node on success, NULL on failure.
	 */

/* == XML_Node* ALLOCATION functions ===================================== */

xml_node_t *XML_NodeInit(int node_type, const char *name);
	/* This function is usually called internally.
	 This function is called to create a new node, of the specified 'node_type' (see XML_TYPE_*).
	 Applies the given 'name' to the node, if the node_type supports a name.
	 Allocates memory for the new node and sets its members to default values.
	 Returns a pointer to the new node, or NULL on error.
	 */
xml_node_t *XML_NodeCopy(xml_node_t *node);
	/* This function copies the given 'node' entirely, including its sub-nodes, attributes, and
	 data. It does not copy callback information stored in the nodes.
	 The returned node is not linked to any parent or siblings, so the XML_LinkNodeToNode
	 function can be used to insert the new node where required.
	 Returns a pointer to the new node, or NULL on error.
	 */
int XML_NodeReplaceByNode(xml_node_t *original_node, xml_node_t *replacement_node);
	/* Removes the 'original_node' entirely from the tree, and destroys it and its children.
	 Inserts 'replacement_node' in its place and makes all necessary links to the tree.
	 'replacement_node' will be unlinked from its native tree.
	 both 'original_node' and 'replacement_node' must be of type XML_TYPE_ELEMENT.
	 Returns -1 on error, 0 on success.
	 */
int XML_NodeClear(xml_node_t *node);
	/* This function is usually called internally.
	 Clears the contents of the given 'node'.
	 All sub-nodes are automatically destroyed.
	 The node memory is still allocated, but its contents are cleared.
	 Returns 0 if the contents were cleared, -1 otherwise.
	 */
int XML_NodeDestroy(xml_node_t *node);
	/* This function is usually called internally.
	 Destroys the given 'node', and completely removes it from the node structure.
	 All sub-nodes are also destroyed.
	 Be sure to clear all pointers to the node as they will be invalidated following this call.
	 Returns 0 if the node has been destroyed, -1 otherwise.
	 */

/* == XML_Node* PARENT/ANCESTOR functions ================================= */

int XML_NodeHasAncestorNamed(xml_node_t *node, const char *ancestor_name);
	/* Returns 1 if the given 'node' has an ancestor with the given 'ancestor_name'.
	 If 'ancestor_name' is NULL and 'node' has at least one parent, 1 will be returned.
	 Returns 0 otherwise.
	 */
int XML_NodeHasAncestorNode(xml_node_t *node, xml_node_t *ancestor_node);
	/* Returns 1 if the given 'node' has an 'ancestor_node' as one of its ancestors.
	 If 'ancestor_node' is NULL and 'node' has at least one parent, 1 will be returned.
	 Returns 0 otherwise.
	 */

/* == XML_Node* CHILD/SIBLING functions ==================================== */

xml_node_t *XML_NodeHasChildren(xml_node_t *parent_node);
	/* If the given 'parent_node' has any children, the first child node is returned.
	 Returns NULL if 'node' has no children.
	 */
xml_node_t *XML_NodeLastChild(xml_node_t *parent_node);
	/* Returns the last child of the specified 'parent_node'.
	 Returns NULL if 'node' has no children.
	 */
xml_node_t *XML_GetFirstSubNode(xml_node_t *parent_node);
	/* Given a particular 'parent_node', returns the first child node.
	 Returns NULL if 'parent_node' has no children.
	 */
xml_node_t *XML_GetNextSubNode(xml_node_t *parent_node, xml_node_t *previous_sub_node);
	/* Given a particular 'parent_node', returns the child following 'previous_sub_node'.
	 Returns NULL if 'parent_node' has no children, or if 'previous_sub_node' is not a child
	 of this node, or if there are no children beyond 'previous_sub_node'.
	 */
xml_node_t *XML_NodePriorSibling(xml_node_t *child_node);
	/* Returns the sibling prior to the 'node' specified.
	 Returns NULL if 'node' is the first child.
	 */
xml_node_t *XML_NodeFirstNonAttribute(xml_node_t *parent_node);
	/* Returns the first child of 'parent_node' which is not an attribute.
	 Returns NULL if 'node' has no children, or if all of its children are attributes.
	 */
xml_node_t *XML_NodeLastAttribute(xml_node_t *parent_node);
	/* Returns the last child of 'parent_node' which is an attribute.
	 Returns NULL if 'node' has no children, or if none of its children are attributes.
	 */
xml_node_t *XML_GetFirstNode(xml_node_t *parent_node);
	/* Returns the first element of the specified 'parent_node'.
	 Returns NULL if 'parent_node' has no child nodes.
	 */
xml_node_t *XML_GetNextNode(xml_node_t *previous_node);
	/* Returns the element subsequent to 'previous_node').
	 Returns NULL if 'previous_node' is the last element.
	 */

/* == XML_NodeList* functions ===========================================
	 A NodeList is simply a list of pointers to nodes.
	 Each entry also has an integer, which is used in Tree functions for various purposes.
	 Create a new list by using XML_NodeListInit, then you can either call a function which will
	 fill the NodeList, or fill the NodeList yourself, using XML_NodeListAdd.
	 Clear the NodeList by calling XML_NodeListClear.
	 Destroy the NodeList by calling XML_NodeListDestroy.

	 Here are a couple of examples of when to use a NodeList:
	 When doing a Find* function, pass a NodeList, which will be filled with the nodes
	 that match the requested search criteria.
	 When doing a XML_TreeFindTreeInList, pass a list of nodes to search for the given tree.
	 When doing a XML_NodeAttributeRemoveFromMany, pass a list of nodes from which you
	 want to remove the specified attribute.
*/

int XML_NodeListClear(xml_nodelist_t *nodelist);
	/* This function clears all data allocated for the specified 'nodelist'.
	 The 'nodelist' itself is not deallocated, so it can be re-used without XML_NodeListInit.
	 This function is to be called whenever you're using a Find* function, to clear all
	 previous Find* results.
	 Frees any memory previously associated with the 'nodelist' buffer.
	 Returns the number of elements removed.
	 */
int XML_NodeListAdd(xml_nodelist_t *nodelist, xml_node_t *node, int data);
	/* Adds a match to the given 'nodelist', which references the specified 'node'.
	 The 'data' value is put into the structure to correspond with this 'node'.
	 This function is normally called internally by the Find* functions, but can be used to
	 create your own list of nodes as required.
	 Returns the (0-based) index of the added list element on success, -1 on failure.
	 */
int XML_NodeListSetData(xml_nodelist_t *nodelist, xml_node_t *node, int data);
	/* This function searches for the given 'node' in the specified 'nodelist'.
	 If it is present, its 'data' element is set to the 'data' provided.
	 Returns 0 on success, -1 on failure.
	 */
int XML_NodeListCallback(xml_nodelist_t *nodelist, xml_nodelist_cb_f function, void *cbdata);
	/* Calls the specified callback 'function' for each element of 'nodelist'.
	 If the callback function returns -1, the entry will be removed from the nodelist
	 after all callbacks have been called.
	 Returns 0 on success, -1 on failure.
	 */
int XML_NodeListCopy(xml_nodelist_t *destination, xml_nodelist_t *source);
	/* Copies 'source' xml_nodelist_t structure to the specified 'destination' xml_nodelist_t structure.
	 Returns 0 on success, -1 on failure.
	 */
int XML_NodeListRemoveNodes(xml_nodelist_t *nodelist);
	/* This function removes any nodes in 'nodelist' which have a 'node' value of NULL.
	 The 'matches' value is decremented for each node which is removed.
	 Returns the number of nodes removed.
	 */

/* == XML_FindNode* functions ===========================================
	 The XML_NodeFind* functions all have the same handling instructions.
	 The specifics for each function can be found under the individual function headings.

	 Supply a 'basenode' to search, under which its sub-nodes will be searched.

	 Get the 'nodelist' variable by calling XML_NodeListInit.
	 The functions fill the 'nodelist' with pointers to the nodes which match the pattern.
	 'nodelist' contains 'matches' which is an integer, showing the number of matches found.
	 'nodelist' contains 'node', an array of pointers to the matching nodes.
	 'nodelist' contains 'data', an array of integers which are each set to 0 by these functions.
	 'nodelist' contains 'depth', an integer used internally, which should not be changed.

	 If 'nodelist' has data in it already, only those nodes are checked. Thus, the Find
	 functions are used to filter data to only those nodes that match a number of conditions.

	 The 'depth' parameter determines how deep into the tree structure the search should go.
	 If 'depth' is -1, all nodes and sub-nodes will be searched.
	 If 'depth' is 0, only the nodes itself will be searched.
	 If 'depth' is 1, only the nodes directly under 'node' will be searched.
	 Note: when searching under the document pointer itself, the document node counts
	 as one level of depth for the search. You may have to increase your 'depth' value
	 by one to get the desired search results.

	 To clear a previous search, call XML_NodeListClear before calling these functions.
	 To narrow a previous search, don't call XML_NodeListClear before calling these functions.

	 The functions returns the number of matches in the 'nodelist'.
*/

int XML_FindNodeByCondition(xml_node_t *node, int depth, xml_nodelist_t *nodelist, xml_find_cb_f function, void *cbdata);
	/* Does a generic search of the given 'node' and its children, and considers the node to be
	 a match if the specified 'function' returns the XML_NODE_FIND_ADD flag in its callback result.
	 If the callback 'function' returns the XML_NODE_FIND_SKIP flag, the node will not be added.
	 If the callback 'function' returns a value with the XML_NODE_FIND_NO_CHILDREN flag set,
	 then no children of the given node will be further check for matches.
	 This function is also called by the supplied XML_FindNodeWith* functions, described below.
	 */
int XML_FindNodeWithValue(xml_node_t *basenode, const char *buffer, int len, int depth, xml_nodelist_t *nodelist);
	/* Supply a 'buffer' and 'length' of data which must be matched on a node, for that
	 node to be considered a match.
	 If 'buffer' is NULL, then all nodes with text data will be considered a match.
	 if 'len' is 0, then all nodes with 0-length text data will be considered a match.
	 */
int XML_FindNodeWithoutAttribute(xml_node_t *basenode, const char *name, const char *value, int depth, xml_nodelist_t *nodelist);
	/* Supply an attribute 'name' and 'value' which must not be present for a node, for that
	 node to be considered a match.
	 If 'name' is NULL, then all nodes with an attribute with the given value will not be
	 considered a match.
	 if 'value' is NULL, then all nodes with the given attribute name will not be considered a match.
	 Returns -1 if an error is detected, or 0 otherwise.
	 */
int XML_FindCallbackName(xml_node_t *node, void *cbdata);
int XML_FindCallbackValue(xml_node_t *node, void *cbdata);
int XML_FindCallbackAttribute(xml_node_t *node, void *cbdata);
	/* These are the callbacks for the supplied XML_FindNodeWith* functions, above. */

/* == XML_NodeAttribute* functions ======================================== */

xml_attr_t *XML_NodeAttributeGetNode(xml_node_t *parent_node, const char *name);
	/* Returns a pointer to the attribute node named 'name' for the given 'parent_node'.
	 Returns NULL if the attribute does not exist.
	 */
xml_attr_t *XML_NodeAttributeAdd(xml_node_t *parent_node, const char *name, const char *value);
	/* Adds an attribute named 'name' for the given 'parent_node', with the specified 'value'.
	 Returns a pointer to the new attribute node, or NULL on failure.
	 */
xml_attr_t *XML_NodeAttributeSetUnsaved(xml_node_t *node, const char *name, const char *value);
	/* Same functionality as XML_NodeAttributeSet, except that it is a special attribute which
	 will not be saved with the XML file, and it will not generate any callbacks due to its
	 addition, modification, or removal.
	 This type of attribute can be used as required by an application, to perhaps hold
	 the status of a given node, or to specify commands to be executed later.
	 Returns a pointer to the new unsaved attribute node, or NULL on failure.
	 */
xml_attr_t *XML_NodeAttributeAddInternal(xml_node_t *node, const char *name, const char *value);
	/* This function is called internally. Do not call this function directly. */
int XML_NodeAttributeRemoveFromMany(xml_nodelist_t *nodelist, const char *name);
	/* For each of the nodes specified in 'nodelist', any attribute called 'name' will
	 be removed from the node.
	 Returns 0 on success, -1 on error.
	 */

/* == XML_NodeName* functions ========================================== */

int XML_NodeNameSet(xml_node_t *node, const char *name);
	/* This function is seldom used since node names are usually static.
	 Changes the name of the specified node to the specified 'name'.
	 returns 0 on success, -1 on failure.
	 */
int XML_NodeDeleteByName(xml_node_t *parent_node, const char *child_name);
	/* For each of the sub-nodes within 'parent_node' which has the name 'child_name',
	 the node is completely destroyed and removed from the document.
	 */

/* == XML_NodeText* functions =========================================== */

xml_node_t *XML_NodeTextAddToNode(xml_node_t *node, const char *buffer, int len);
	/* Adds text data to the end of the given node (but not leading whitespace).
	 Returns a pointer to the new text data, or NULL on failure.
	 */
xml_node_t *XML_NodeDataAddToNode(int xml_data_type, xml_node_t *node, const char *buffer, int len);
	/* This function is usually called internally.
	 Adds a data node to the end of the given node.
	 The 'xml_data_type' must be either XML_TYPE_TEXT, XML_TYPE_COMMENT, or
	 XML_TYPE_CBLOCK.
	 Returns a pointer to the new data node, or NULL on failure.
	 */

/* == XML_Node* LINK/UNLINK functions ====================================== */

xml_node_t *XML_NodeUnlink(xml_node_t *node);
	/* Unlinks a given node from the tree, so that it is no longer part of the tree.
	 Use the XML_LinkNodeToNode function to re-attach the node where desired,
	 either in the same document, or in another.
	 Returns a pointer to the unlinked node on success, NULL otherwise.
	 */
int XML_NodeLinkToNode(xml_node_t *existing_node, xml_node_t *unlinked_node);
	/* Links a given 'unlinked_node' to become the last immediate child of the given
	 'existing_node', where 'unlinked_node' has been previously unlinked, or copied
	 from elsewhere. See the XML_NodeUnlink function.
	 Returns 0 on success, -1 otherwise.
	 */

/* == XML_NodeCallback* functions ========================================== */
int XML_NodeCallbackAdd(xml_node_t *node, xml_node_cb_f function, int max_depth, void *cbdata, int flags);
	/* Adds a callback to the given 'node', so that when it (or its children) are modified,
	 deleted, or added (see 'flags'), the specified 'function' is called.
 	 For 'flags', see the XML_CB_* constants. These define which events will cause a
 	 callback for the given 'node'.
 	 When monitoring children, only children which are no more than 'max_depth' generations
 	 removed will be monitored.
 	 If 'max_depth' is -1, all children will be monitored (if children are specified in 'flags')
 	 If 'max_depth' is 0, no children will be monitored (regardless of the settings in 'flags')
	 The following 'cb_function' will be generated:
			int function(xml_node_t *callback_node, xml_node_t *child_node, int handle,
				void *cbdata, int reason);
 	 Returns a handle to the callback if it is successfully added (1+).
	 Returns 0 if the callback cannot be added.
	 */
int XML_NodeCallbackRemove(xml_node_t *node, int handle);
	/* Removes the callbacks for the specified 'node' which have the same 'handle' as the
	 one which is specified.
	 If 'handle' is 0, all callbacks will be removed from the specified 'node'.
	 Returns 0 when at least one callback is removed, -1 otherwise.
	 */
int XML_NodeCallbackActivate(xml_node_t *node, int reason);
	/* Called internally when a change is detected to a node, to activate any callbacks
	 which are registered.
	 Returns 0 if at least one callbacks was activated, -1 otherwise.
	 */

/* == XML_Size* functions ============================================== */

int XML_SizeNumberOfTags(xml_node_t *node);
	/* Returns the number of tags (XML_TYPE_ELEMENT) present within the given 'node',
	 including all of its children.
	 */

/* == XML_String* functions ============================================= */

char *XML_StringEncodeURI(const char *source);
	/* Encodes the given 'source' string into URI-encoded form, and returns a newly allocated
	 string with this encoded data.
	 The 'source' data is unchanged.
	 Be sure to deallocate the returned string elsewhere.
	 */
char *XML_StringDecodeURI(const char *source);
	/* Decodes the given 'source' string from URI-encoded form to a standard string, and
	 returns a newly allocated string with this decoded data.
	 The 'source' data is unchanged.
	 Be sure to deallocate the returned string elsewhere.
	 */
char *XML_StringTrimWhiteSpace(char *string);
	/* Changes the given string, so that it has no leading or trailing whitespace.
	 Returns a pointer to the portion of the string which contains data.
	 */
int XML_StringExpressionCompare(const char *expression, const char *text);
	/* Does a string comparison of 'expression' to 'text'.
	 Returns 0 if the two values match exactly.
	 */
char *XML_StringEncodeSpecial(const char *data);
	/* Puts &ret and &tab codes into the 'data' buffer specified.
	 Returns a pointer to the new buffer, which must be freed by your application.
	 */
int XML_StringDecodeSpecial(char *data);
	/* Removes &ret and &tab codes from the given 'data' string.
	 Returns 0 on succes, -1 on error.
	 */

/* == XML_UserData* functions ========================================== */

void *XML_UserDataGet(xml_node_t *node);
	/* Returns the userdata (void*) for the specified 'node'. */
int XML_UserDataSet(xml_node_t *node, void *userdata);
	/* Sets the userdata (void*) for the specified 'node' to the specified 'userdata'.
	 No callbacks are generated by setting userdata on a node.
	 userdata is not preserved when copying a node.
	 Returns 0 on success, -1 on failure.
	 */

/* =============================================================
 API structure definitions
 ============================================================= */

struct xml_node
{
	int type;
	xml_node_t *parent;
	xml_node_t *sibling;
	xml_callback_t *callback;
	unsigned int hash;
	void *userdata;
	xml_node_t *children;
};

struct xml_document
{
	int type;
										/* A document's 'parent' and 'sibling' variables can be used as required in your application. */
	void *parent;					/* 'parent' is always set to NULL when the document is created. */
	xml_node_t *sibling;			/* 'sibling' is always set to NULL when the document is created. */
	xml_callback_t *callback;
	unsigned int hash;
	void *userdata;
	xml_node_t *children;
	char *name;
	char *filename;
};

struct xml_element
{
	int type;
	xml_node_t *parent;
	xml_node_t *sibling;
	xml_callback_t *callback;
	unsigned int hash;
	void *userdata;
	xml_node_t *children;
	char *name;
};

struct xml_text					/* or Comment or CDATASection */
{
	int type;
	xml_node_t *parent;
	xml_node_t *sibling;
	xml_callback_t *callback;
	unsigned int hash;
	void *userdata;
	char *buffer;
	int len;
};

struct xml_attr					/* or Processing Instruction */
{
	int type;
	xml_node_t *parent;
	xml_node_t *sibling;
	xml_callback_t *callback;
	unsigned int hash;
	void *userdata;
	char *name;
	char *value;
	int flags;
};

struct xml_nodelist
{
	xml_node_t **node;			/* pointer to an array of *xml_node_t (initially NULL) */
	int *data;						/* used in narrowing previous searches, and in tree walking */
	int matches;					/* number of nodes which match these specifications (initially 0) */
	int depth;						/* used in recursive searches. (initially 0) */
};

struct xml_apinfo
{
	xml_node_t *node;
	int node_type;
};

struct xml_callback
{
	int handle;
	int flags;
	int max_depth;
	xml_node_cb_f function;
	void *cbdata;
	xml_callback_t *next;
};

struct xml_find
{
	int number;
	const char *string1;
	const char *string2;
	int positive_negative;
	unsigned int hash;
};

struct xml_file_info
{
	char filename[1024];
	int directory;
	off_t size;
	mode_t mode;
	time_t time;
	int application_defined;
};

struct xml_parse_info
{
	void *parser;
	const char *filename;
	xml_error_cb_f error_function;
	void *cbdata;
	xml_node_t **node;
	const char *starting_tag;
	int finished;
	int ignore_depth;
	const char *ignore_tag;
};

/* ============================================================= */

#ifdef __cplusplus
	}
#endif

#endif


#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/xml/public/xmlnode.h $ $Rev: 219996 $" )
#endif
