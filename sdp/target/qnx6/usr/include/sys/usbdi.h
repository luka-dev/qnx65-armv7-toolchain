/*
 * $QNXLicenseC:  
 * Copyright 2005, QNX Software Systems. All Rights Reserved.
 *
 * This source code may contain confidential information of QNX Software 
 * Systems (QSS) and its licensors.  Any use, reproduction, modification, 
 * disclosure, distribution or transfer of this software, or any software 
 * that includes or is based upon any of this code, is prohibited unless 
 * expressly authorized by QSS by written agreement.  For more information 
 * (including whether this source code file has been published) please
 * email licensing@qnx.com. $
*/

/*
 *  sys/usbdi.h
 *

 */

#include <inttypes.h>
#include <sys/types.h>
#include <sys/usb100.h>

#ifndef __USBDI_H_INCLUDED
#define __USBDI_H_INCLUDED

#define USBD_VERSION				0x0101
#define USBD_CONNECT_WAIT			60

#define USBD_CONNECT_WILDCARD		0xffffffff

#define URB_DIR_IN					0x00000001
#define URB_DIR_OUT					0x00000002
#define URB_DIR_NONE				0x00000003
#define URB_SHORT_XFER_OK			0x00000004
#define URB_ENQUEUE_HEAD			0x00000008
#define URB_ENQUEUE_TAIL			0x00000000
#define URB_ISOCH_ASAP				0x00000010

#define USBD_URB_STATUS_MASK			0xFF000000
#define USBD_STATUS_INPROG				0x00000000
#define USBD_STATUS_CMP					0x01000000
#define USBD_STATUS_CMP_ERR				0x02000000
#define USBD_STATUS_TIMEOUT				0x04000000
#define USBD_STATUS_ABORTED				0x08000000

#define USBD_USB_STATUS_MASK			0x00FFFFFF
#define	USBD_STATUS_CRC_ERR				0x00000001
#define	USBD_STATUS_BITSTUFFING			0x00000002
#define	USBD_STATUS_TOGGLE_MISMATCH		0x00000003
#define	USBD_STATUS_STALL				0x00000004
#define	USBD_STATUS_DEV_NOANSWER		0x00000005
#define	USBD_STATUS_PID_FAILURE			0x00000006
#define	USBD_STATUS_BAD_PID				0x00000007
#define	USBD_STATUS_DATA_OVERRUN		0x00000008
#define	USBD_STATUS_DATA_UNDERRUN		0x00000009
#define	USBD_STATUS_BUFFER_OVERRUN		0x0000000C
#define	USBD_STATUS_BUFFER_UNDERRUN		0x0000000E
#define	USBD_STATUS_NOT_ACCESSED		0x0000000F
#define USBD_STATUS_NO_MEM_FOR_TRANSFER 0x00000010
#define USBD_STATUS_ISOCH_MISSED_PERIOD 0x00000020


#define USBD_TIME_DEFAULT			0x00000000
#define USBD_TIME_INFINITY			0xFFFFFFFF

#define USBD_MAX_LINK_URB			64

#define USBD_HCD_CAP_CNTL			0x0001
#define USBD_HCD_CAP_INTR			0x0002
#define USBD_HCD_CAP_BULK			0x0004
#define USBD_HCD_CAP_ISOCH			0x0008
#define USBD_HCD_CAP_LOW_SPEED		0x0010
#define USBD_HCD_CAP_FULL_SPEED		0x0020
#define USBD_HCD_CAP_HIGH_SPEED		0x0040
#define USBD_HCD_CAP_BULK_SG		0x0200
#define USBD_HCD_CAP_ISOCH_STREAM	0x0400
#define USBD_HCD_CAP_CHAIN_CTRL		0x0800
#define USBD_HCD_CAP_CHAINED_URB	0x1000

__BEGIN_DECLS

struct usbd_connection;
struct usbd_desc_node;
struct usbd_device;
struct usbd_pipe;
struct usbd_urb;

typedef struct usbd_device_descriptor {
	_Uint8t					bLength;
	_Uint8t					bDescriptorType;
	_Uint16t				bcdUSB;
	_Uint8t					bDeviceClass;
	_Uint8t					bDeviceSubClass;
	_Uint8t					bDeviceProtocol;
	_Uint8t					bMaxPacketSize0;
	_Uint16t				idVendor;
	_Uint16t				idProduct;
	_Uint16t				bcdDevice;
	_Uint8t					iManufacturer;
	_Uint8t					iProduct;
	_Uint8t					iSerialNumber;
	_Uint8t					bNumConfigurations;
} usbd_device_descriptor_t;

typedef struct usbd_configuration_descriptor {
	_Uint8t					bLength;
	_Uint8t					bDescriptorType;
	_Uint16t				wTotalLength;
	_Uint8t					bNumInterfaces;
	_Uint8t					bConfigurationValue;
	_Uint8t					iConfiguration;
	_Uint8t					bmAttributes;
	_Uint8t					MaxPower;
} usbd_configuration_descriptor_t;

typedef struct usbd_string_descriptor {
	_Uint8t					bLength;
	_Uint8t					bDescriptorType;
	_Uint16t				bString[1];
} usbd_string_descriptor_t;

typedef struct usbd_interface_descriptor {
	_Uint8t					bLength;
	_Uint8t					bDescriptorType;
	_Uint8t					bInterfaceNumber;
	_Uint8t					bAlternateSetting;
	_Uint8t					bNumEndpoints;
	_Uint8t					bInterfaceClass;
	_Uint8t					bInterfaceSubClass;
	_Uint8t					bInterfaceProtocol;
	_Uint8t					iInterface;
} usbd_interface_descriptor_t;

typedef struct usbd_endpoint_descriptor {
	_Uint8t					bLength;
	_Uint8t					bDescriptorType;
	_Uint8t					bEndpointAddress;
	_Uint8t					bmAttributes;
	_Uint16t				wMaxPacketSize;
	_Uint8t					bInterval;
} usbd_endpoint_descriptor_t;

typedef struct usbd_audio_endpoint_descriptor {
	_Uint8t					bLength;
	_Uint8t					bDescriptorType;
	_Uint8t					bEndpointAddress;
	_Uint8t					bmAttributes;
	_Uint16t				wMaxPacketSize;
	_Uint8t					bInterval;
	_Uint8t					bRefresh;
	_Uint8t					bSyncAddress;
} usbd_audio_endpoint_descriptor_t;

typedef struct usbd_hid_descriptor {
	_Uint8t					bLength;
	_Uint8t					bDescriptorType;
	_Uint16t				bcdHID;
	_Uint8t					bCountryCode;
	_Uint8t					bNumDescriptors;
	_Uint8t					bReportDescriptorType;
	_Uint16t				wDescriptorLength;
} usbd_hid_descriptor_t;

typedef struct usbd_hub_descriptor {
	_Uint8t					bLength;
	_Uint8t					bDescriptorType;
	_Uint8t					bNbrPorts;
	_Uint16t				wHubCharacteristics;
	_Uint8t					bPwrOn2PwrGood;
	_Uint8t					bHubContrCurrent;
	_Uint8t					DeviceRemovable[1];
	_Uint8t					PortPwrCtrlMask[1];
} usbd_hub_descriptor_t;

typedef union usbd_descriptors {
	usb100_generic_descriptor_t			generic;
	usbd_device_descriptor_t			device;
	usbd_configuration_descriptor_t		configuration;
	usbd_string_descriptor_t			string;
	usbd_interface_descriptor_t			interface;
	usbd_endpoint_descriptor_t			endpoint;
	usbd_audio_endpoint_descriptor_t	audio;
	usbd_hid_descriptor_t				hid;
	usbd_hub_descriptor_t				hub;
} usbd_descriptors_t;

typedef struct usbd_device_ident {
	_Uint32t				vendor;
	_Uint32t				device;
	_Uint32t				dclass;
	_Uint32t				subclass;
	_Uint32t				protocol;
} usbd_device_ident_t;

typedef struct usbd_device_instance {
	_Uint8t					path;
	_Uint8t					devno;
	_Uint16t				generation;
	usbd_device_ident_t		ident;
	_Uint32t				config;
	_Uint32t				iface;
	_Uint32t				alternate;
} usbd_device_instance_t;

typedef struct usbd_funcs {
	_Uint32t		nentries;
	void			(*insertion)(struct usbd_connection *, usbd_device_instance_t *instance);
	void			(*removal)(struct usbd_connection *, usbd_device_instance_t *instance);
	void			(*event)(struct usbd_connection *, usbd_device_instance_t *instance, _Uint16t type);
} usbd_funcs_t;

#define _USBDI_NFUNCS ((sizeof(usbd_funcs_t) - sizeof(_Uint32t)) / sizeof(void *))

typedef struct usbd_hcd_info {
	_Uint16t				vusb;
	_Uint16t				vusbd;
	char					controller[8];
	_Uint32t				capabilities;
	_Uint8t					ndev;				/* number of currently connected devices */
	_Uint8t					cindex;
	_Uint16t				vhcd;
	_Uint32t				max_td_io;			/* max bytes per HC TD */
	_Uint8t					_reserved[12];
} usbd_hcd_info_t;

typedef struct usbd_port_attachment {
	_Uint8t					upstream_devno;
	_Uint8t					upstream_port;
	_Uint8t					upstream_port_speed;
	_Uint8t					upstream_hc;
	_Uint8t					_reserved[4];
} usbd_port_attachment_t;

typedef struct usbd_bus_topology {
	usbd_port_attachment_t	ports[64];
} usbd_bus_topology_t;

typedef struct _usbd_urb_sg_elem {
    paddr_t 			urb_sg_address;
	uint32_t			urb_sg_status;
    u_long 				urb_sg_count;
} usbd_urb_sg_elem_t;

typedef struct _usbd_urb_sg_list {
	uint16_t			sg_elm_count;
	uint16_t			reserved[3];
	usbd_urb_sg_elem_t  *sg_list;
} usbd_urb_sg_list_t;

typedef struct usbd_isoch_frame_request {
    _uint32                 frame_len;
    _uint32                 frame_status;
} usbd_isoch_frame_request_t;

typedef struct usbd_urb_isoch_stream_xfer {
	uint16_t					nframes;
	uint16_t					reserved[1];
	usbd_isoch_frame_request_t *frame_list;
} usbd_urb_isoch_stream_xfer_t;

typedef struct usbd_connect_parm {
	const char					*path;
	_Uint16t					vusb;
	_Uint16t					vusbd;
	_Uint32t					flags;
	_Int32t						argc;
	char						**argv;
	_Uint32t					evtbufsz;
	usbd_device_ident_t			*ident;
	usbd_funcs_t				*funcs;
	_Uint16t					connect_wait;
	_Uint8t						evtprio;
	_Uint8t						_reserved[13];
} usbd_connect_parm_t;

#define USBD_CONNECT_FLAG_NO_DESCRIPTOR_CACHE	0x00000001

extern int					usbd_connect(usbd_connect_parm_t *parm, struct usbd_connection **connection);
extern int					usbd_disconnect(struct usbd_connection *connection);
extern int					usbd_hcd_ext_info(struct usbd_connection *connection, _Uint32t cindex, usbd_hcd_info_t *info);
extern int					usbd_hcd_info(struct usbd_connection *connection, usbd_hcd_info_t *info);
extern int					usbd_topology(struct usbd_connection *connection, usbd_bus_topology_t *tp);
extern int					usbd_topology_ext(struct usbd_connection *connection, _Uint8t busno, usbd_bus_topology_t *tp);

extern int					usbd_attach(struct usbd_connection *connection, usbd_device_instance_t *instance, size_t extra, struct usbd_device **device);
extern int					usbd_detach(struct usbd_device *device);
extern int					usbd_select_config(struct usbd_device *device, _Uint8t config);
extern int					usbd_select_interface(struct usbd_device *device, _Uint8t iface, _Uint8t alternate);
extern int					usbd_hub_event(struct usbd_device *device, _Uint8t port, _Uint32t dir, _Uint8t speed);

extern int					usbd_open_pipe(struct usbd_device *device, usbd_descriptors_t *desc, struct usbd_pipe **pipe);
extern int					usbd_close_pipe(struct usbd_pipe *pipe);
extern int					usbd_reset_pipe(struct usbd_pipe *pipe);
extern int					usbd_abort_pipe(struct usbd_pipe *pipe);
extern int					usbd_reset_device(struct usbd_device *device);

extern struct usbd_urb		*usbd_alloc_urb(struct usbd_urb *link);
extern struct usbd_urb 		*usbd_urb_link( struct usbd_urb *urb );
extern int 					usbd_set_urb_link( struct usbd_urb *urb, struct usbd_urb *link );
extern void 				*usbd_urb_transfer_handle( struct usbd_urb *urb );
extern struct usbd_urb		*usbd_free_urb(struct usbd_urb *urb);
extern void					*usbd_alloc(size_t size);
extern void					usbd_free(void *ptr);
extern paddr_t				usbd_mphys(const void *ptr);

extern void					*usbd_alloc_cached(size_t size);
extern void					usbd_free_cached(void *ptr);
extern paddr_t				usbd_mphys_cached(const void *ptr);

extern int 					usbd_alloc_sg_list( _uint32 sg_count, usbd_urb_sg_elem_t **sg_elems );
extern int 					usbd_free_sg_list( usbd_urb_sg_elem_t *sg_elems );
extern int 					usbd_free_isochronous_frame_list( usbd_isoch_frame_request_t *frame_list );
extern int 					usbd_alloc_isochronous_frame_list( _uint32 nframes, usbd_isoch_frame_request_t **frame_list );

extern int					usbd_descriptor(struct usbd_device *device, int set, _Uint8t type, _Uint16t rtype, _Uint8t index, _Uint16t langid, _Uint8t *desc, size_t len);
extern int					usbd_feature(struct usbd_device *device, int set, _Uint16t feature, _Uint16t rtype, _Uint16t index);
extern int					usbd_status(struct usbd_device *device, _Uint16t rtype, _Uint16t index, void *addr, _Uint32t len);

extern int					usbd_setup_vendor(struct usbd_urb *urb, _Uint32t flags, _Uint16t request, _Uint16t rtype, _Uint16t value, _Uint16t index, void *addr, _Uint32t len);
extern int					usbd_setup_isochronous(struct usbd_urb *urb, _Uint32t flags, _Int32t frame, void *addr, _Uint32t len);
extern int					usbd_setup_bulk(struct usbd_urb *urb, _Uint32t flags, void *addr, _Uint32t len);
extern int					usbd_setup_interrupt(struct usbd_urb *urb, _Uint32t flags, void *addr, _Uint32t len);
extern int 					usbd_setup_sg_bulk(struct usbd_urb *urb, _uint32 flags, usbd_urb_sg_elem_t *sg_elems, int sg_count );
extern int 					usbd_setup_isochronous_stream(struct usbd_urb *urb, _uint32 flags, _int32 sframe, void *addr, _uint32 len, usbd_isoch_frame_request_t *frame_list, int nframes);
extern int					usbd_io(struct usbd_urb *urb, struct usbd_pipe *pipe, void (*func)(struct usbd_urb *, struct usbd_pipe *, void *), void *handle, _Uint32t timeout);
extern int 					usbd_chain_io(struct usbd_urb *urb, struct usbd_urb *chain_to, struct usbd_pipe *pipe, void (*func)(struct usbd_urb *, struct usbd_pipe *, void *), void *handle, _uint32 timeout);

extern int					usbd_urb_status(struct usbd_urb *urb, _Uint32t *status, _Uint32t *length);

extern int					usbd_get_frame(struct usbd_device *device, _Int32t *fnum, _Int32t *flen);

extern usbd_descriptors_t	*usbd_parse_descriptors(struct usbd_device *device, struct usbd_desc_node *root, _Uint8t type, int index, struct usbd_desc_node **node);
extern char					*usbd_string(struct usbd_device *device, _Uint8t index, int langid);

extern void								usbd_args_lookup(struct usbd_connection *connection, int *argc, char ***argv);
extern const char						*usbd_args_module(struct usbd_connection *connection, char *module);
extern struct usbd_device				*usbd_device_lookup(struct usbd_connection *connection, usbd_device_instance_t *instance);
extern void								*usbd_device_extra(struct usbd_device *device);
extern _Uint8t							usbd_pipe_endpoint(struct usbd_pipe *pipe);
extern struct usbd_device				*usbd_pipe_device(struct usbd_pipe *pipe);
extern usbd_device_descriptor_t			*usbd_device_descriptor(struct usbd_device *device, struct usbd_desc_node **node);
extern usbd_hub_descriptor_t			*usbd_hub_descriptor(struct usbd_device *device, struct usbd_desc_node **node);
extern usbd_string_descriptor_t			*usbd_languages_descriptor(struct usbd_device *device, struct usbd_desc_node **node);
extern usbd_configuration_descriptor_t	*usbd_configuration_descriptor(struct usbd_device *device, _Uint8t config, struct usbd_desc_node **node);
extern usbd_interface_descriptor_t		*usbd_interface_descriptor(struct usbd_device *device, _Uint8t config, _Uint8t iface, _Uint8t alternate, struct usbd_desc_node **node);
extern usbd_endpoint_descriptor_t		*usbd_endpoint_descriptor(struct usbd_device *device, _Uint8t config, _Uint8t iface, _Uint8t alternate, _Uint8t endpoint, struct usbd_desc_node **node);

__END_DECLS

#endif

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/usbdi/public/sys/usbdi.h $ $Rev: 231932 $" )
