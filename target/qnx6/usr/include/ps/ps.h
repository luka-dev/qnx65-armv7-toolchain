#ifndef _PS_PS_H_INCLUDED
#define _PS_PS_H_INCLUDED

#include <stdio.h>
#include <sys/types.h>
#include <sys/neutrino.h>
#include <inttypes.h>
#include <hw/pci.h>
#include <sys/usbdi.h>

/* a handle to an object is opaque as far as the client is concerned */

struct ps_handle;
typedef struct ps_handle ps_handle_t;

/* the object id is opaque as far as the user is concerned */
typedef struct ps_objid {
  uint64_t header;
  uint64_t objid;
} ps_objid_t;


/* Persistent Store Flags */
#define PS_OBJ_NOREMOVE       0x00000001

#define PS_OBJ_SIZE_EMPTY     0x00000010

/* End Flags              */

ps_objid_t *drv_ps_obj_id_from_pci_values(uint16_t did, 
                                          uint16_t vid, 
                                          uint8_t bus, 
                                          uint8_t func, 
                                          ps_objid_t *objid);
/* 
	returns a pointer to an opaque object ID using the provided info
	that includes 
		16bit PCI vendor ID
		16bit PCI device ID
		8bit  PCI bus Number
		8bit  PCI device func
*/

ps_objid_t *drv_ps_obj_id_from_pci(void *handle, 
                                   ps_objid_t *objid);
/* 
	returns a pointer to an opaque object ID using the provided info
	that includes an opaque handle to PCI
*/


ps_objid_t *drv_ps_obj_id_from_usb(struct usbd_device *device,
                                   ps_objid_t *objid);
/* 
	returns an opaque object ID using the provided info
	that includes an opaque handle to USB
*/


ps_objid_t *drv_ps_obj_id_from_addr32(uint32_t addr,
                                     ps_objid_t *objid);
/*
	returns an opaque object ID using the provided info
	that includes 
    AAAAAAAA = the base16 representation of the 32 bit address.
*/


ps_objid_t *drv_ps_obj_id_from_io32(uint32_t addr,
                                    ps_objid_t *objid);
/*
	returns an opaque object ID using the provided info
	that includes 
    AAAAAAAA = the base16 representation of the 32 bit input output
    port.
*/

ps_objid_t *drv_ps_obj_id_from_io64(uint64_t addr,
                                    ps_objid_t *objid);

ps_objid_t *drv_ps_obj_id_from_addr64(uint64_t addr,
                                      ps_objid_t *objid);

/* Open */

/* opens an object in the persistent store. This function
 * returns a handle to a persistent store object, which can be
 * used for subsequent operations like read/write etc. 
 * Upon failure, NULL is returned, and errno is set.
 * If the object does not exist it can be created with 
 * an appropriate flag.
 */

ps_handle_t *ps_obj_open(ps_objid_t *objid, uint32_t instance, size_t size,
			void *options, unsigned flags);

/* Arguments:
 *  objid  : persistent object id that is unique across
 *              all objects in the persistent store 
             this is the obj_id that is returned by
             one of the helper functions. Helper functions 
             need to be provided for each "realm" of users
             of the persistent store. Each "realm" has a distinct
             prefix, and hence guarantees uniqueness across
             all objects as long as the uniqueness is guaranteed 
             within each "realm"
 *  size   : size of the persistent object. This is the maximum size
 *           of the object. There are presently two options available. 
 *           a) create object to max size up front
 *           b) create object of zero size, but set its maximum size
 *  options: currently unused. Pass in NULL.
 *  flags  : currently the following flags are supported.
 *           PS_OBJ_NOREMOVE:   When this flag is set, the object will be
 *                              not be removed if it already exists.
 *                              rules:
 *                              flags == 0?
 *                                object does not exist
 *                                  create new object of given size
 *                                object exists & size == obj size
 *                                  return handle to object
 *                                object exists & size != obj size
 *                                  delete old object
 *                                  create new object
 *                                  return handle to new object
 *                              flags == PS_OBJ_NOREMOVE
 *                                object does not exist
 *                                  create new object of given size
 *                                object exists & size == obj size
 *                                  return handle to object
 *                                object exists & size != obj size
 *                                  return error
 *           PS_OBJ_SIZE_EMPTY: This is used to indicate that 
 *                              the object is created
 *                              initially with zero size. This
 *                              is not the preferred option
 *                              since there maybe unknown
 *                              latency if an object needs to
 *                              be "expanded" to accomodate a
 *                              write operation dynamically.
 *                              create the object of the given
 *                              "size" up front itself.
 */

/* End Create */


/* Close Object Hdl */

 /* 
 * when u are done with an object handle, u should call
 * ps_close with the handle obtained from the previous 
 * open call. An object that is closed is not deleted 
 * from the persistent store, and will be available for 
 * subsequent opens. Once closed, the handle is no longer valid.
 */
int ps_obj_close(ps_handle_t *hdl, unsigned flags);

/* Arguments:
 * hdl: opaque handle to object. This handle is one obtained
 *      via a prior call to ps_create_object.
 *  flags   : currently none defined, pass in NULL
 */

/* End Close Object Hdl */

/* Unlink Object */

/* Unlink removes the object in the store. Once removed
 * objects can no longer be accessed in the store. */

int ps_obj_unlink(ps_objid_t *objid, uint32_t instance, unsigned flags);

/* Arguments:
 *  objid   : path to an ps object in a given store.
 *  flags   : currently none defined, pass in NULL
 */

/* End Unlink Object */

/* Read Data */

 /* 
 * cannot read more data than there is
 * is assumed that buffer can hold "size" data
 * read from object at offset 
 * typically offset is 0
 * returns -1 on error or amount of data read.
 * flags can determine if read should happen only if 
 * "size" is available, or read whatever is there
 */

size_t ps_obj_read(ps_handle_t *hdl, void *buffer, size_t size, 
               off_t offset, unsigned flags);

/* Arguments:
 * hdl: opaque handle to object. This handle is one obtained
 *      via a prior call to ps_create_object.
 * buffer: user provided buffer to store data read.
 * size  : size of data to be read.
 * offset: offset to read from
 * flags : currently no flags
 */

/* Read Data */

/* Write Data */

 /* 
 * cannot write more than size of object, based on object
 * properties. If elastic, object will grow, else will honour
 * the specified size restrictions.
 * will write object for size from offset as specified.
 * offset must be within the legal size of the object.
 * all the restrictions are enforced by the remote storage
 * end.
 * returns -1 on error or amount of data written.
 * flags can specify if writes should happen _only_ if the "full"
 * write can succeed, or write whatever is possible.
 * typically offset is 0
 */

size_t ps_obj_write(ps_handle_t *hdl, void *buffer, size_t size, 
                off_t offset, unsigned flags);

/* Arguments:
 * hdl: opaque handle to object. This handle is one obtained
 *      via a prior call to ps_create_object.
 * buffer: user provided buffer to write data from.
 * size  : size of data to be written.
 * offset: offset to write into
 * flags : currently no flags
 */

/* End Write Data */

size_t ps_obj_load(ps_handle_t *hdl, void *buffer, size_t size, 
                unsigned flags);
/* ps_obj_load assumes objects are read in entirety. The size
   must be speciied along with the load call so that this is 
   validated to be correct with what is specified for the
   underlying object */

size_t ps_obj_store(ps_handle_t *hdl, void *buffer, size_t size, 
                unsigned flags);
/* ps_obj_store assumes objects are written in entirety. The size
   must be speciied along with the store call so that this is 
   validated to be correct with what is specified for the
   underlying object */

int ps_obj_loadable(ps_handle_t *hdl, unsigned flags);
/* this functions return 0 if the object has been written to
   at least once (i.e. the object contains loadable data) */

/* returns the number of stores currently configured */
int ps_store_num();

/* selects specific store */
/* st_type specifies the type of store, for now the following
   types are defined.
   STORE_TYPE_SHMEM     1
   STORE_TYPE_RAM       2
	 STORE_TYPE_FFS       3
   STORE_TYPE_FFS_RAW   4
   
   Once a store is selected, all active objects in the current
   store will be available in the new store, and the new store
   become the current store in use.
   
   Since multiple instances of a given store type can
   be loaded at once, st_inst specifies which instance
   is being referred to. */

int ps_store_sel(int st_type, int st_inst);

/* delete a specific store */
/* cannot delete the currently in-use store */
int ps_store_del(int st_type, int st_inst);

/* add a store */
int ps_store_add(int init_store, int st_type, int st_instance, 
                 char *prefix, uint32_t size, uint32_t addr, 
                 uint32_t offset);

/* depending on the type of store specific parameters need to 
   be specified. 

TYPE_SHMEM: st_type, st_instance are necessary
            prefix is optional. prefix is a string that will be
            use to create the store under /dev/shmem based on this
            prefix.
TYPE_RAM  : st_type, st_instance are necessary
            size and addr are also necessary

TYPE_FFS  : st_type, st_instance are necessary
            prefix is also necessary

TYPE_FFS_RAW : st_type, st_instance are necessary
               prefix, size, and offset are also necessary

init_store is to be set to 1, if the store is being 
initialised at the time it is being loaded. Initialisation
of a store will result in all objects in the store 
being effectively unavailable */

#endif

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ps/public/ps/ps.h $ $Rev: 219996 $" )
