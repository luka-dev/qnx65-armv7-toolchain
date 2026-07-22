#ifndef KD_QNX_INPUT_H_
#define KD_QNX_INPUT_H_

#ifndef KD_QNX_input
#define KD_QNX_input 1

/* Assigns focus for an i/o group, includes i/o groups which support stride
 * 
 * E.g. KD_QNX_OUTPUT_ASSIGN_KEYBOARD + index of keyboard * KD_IO_CONTROLLER_STRIDE
 * 
 * Note: Call with -1 to reset to default focus, which means i/o group will 
 * obey global i/o group focus on it's display
 * 
 * ALSO NOTE: When using KD_QNX_OUTPUT_ASSIGN_POINTER to assign pointer focus to
 * a window, general focus cannot be re-assign via mouse click.
 * 
 * outputs take a KDWindow
 */
#define KD_IOGROUP_ASSIGN_GROUP_QNX             (KD_IO_UNDEFINED + 0)
#define KD_STATE_ASSIGN_GROUP_AVAILABILITY_QNX  (KD_IOGROUP_ASSIGN_GROUP_QNX + 0)
#define KD_OUTPUT_ASSIGN_POINTER_QNX            (KD_IOGROUP_ASSIGN_GROUP_QNX + 1)
#define KD_OUTPUT_ASSIGN_JOGDIAL_QNX            (KD_IOGROUP_ASSIGN_GROUP_QNX + 2)
#define KD_OUTPUT_ASSIGN_KEYBOARD_QNX           (KD_IOGROUP_ASSIGN_GROUP_QNX + 3)
#define KD_OUTPUT_ASSIGN_MOUSE_QNX              (KD_IOGROUP_ASSIGN_GROUP_QNX + 4)
#define KD_OUTPUT_ASSIGN_TOUCH_QNX              (KD_IOGROUP_ASSIGN_GROUP_QNX + 5)

/* Assigns an i/o group to a display using display id, includes i/o groups which support stride
 * 
 * E.g. KD_QNX_OUTPUT_DISP_KEYBOARD + index of keyboard * KD_IO_CONTROLLER_STRIDE
 * 
 * Setting a focus to an i/o group using KD_QNX_IOGROUP_ASSIGN_GROUP i/o group 
 * to assign a focus to a window takes priority over display focus
 * 
 * Note: Call with -1 to reset default display focus
 * 
 * outputs take display ids 
 */
#define KD_IOGROUP_DISP_GROUP_QNX               (KD_IO_UNDEFINED + 0x500)
#define KD_STATE_DISP_GROUP_AVAILABILITY_QNX    (KD_IOGROUP_DISP_GROUP_QNX + 0)
#define KD_OUTPUT_DISP_POINTER_QNX              (KD_IOGROUP_DISP_GROUP_QNX + 1)
#define KD_OUTPUT_DISP_JOGDIAL_QNX              (KD_IOGROUP_DISP_GROUP_QNX + 2)
#define KD_OUTPUT_DISP_KEYBOARD_QNX             (KD_IOGROUP_DISP_GROUP_QNX + 3)
#define KD_OUTPUT_DISP_MOUSE_QNX                (KD_IOGROUP_DISP_GROUP_QNX + 4)
#define KD_OUTPUT_DISP_TOUCH_QNX                (KD_IOGROUP_DISP_GROUP_QNX + 5)

#define KD_EVENT_KEYBOARD_QNX                   (KD_EVENT_UNDEFINED_QNX + 1000)

typedef struct KDEventKeyboardQNX {
    KDint32     index;
    KDuint32    flags;
    KDuint32    modifiers;
    KDuint32    key_cap;
    KDuint32    key_scan;
    KDuint32    key_sym;
} KDEventKeyboardQNX;


/* Keyboard I/O group generates KDEventKeyboardQNX events, and supports
 * stride
 * 
 * E.g. KD_QNX_IOGROUP_KEYBOARD + index of keyboard * KD_IO_CONTROLLER_STRIDE
 */
#define KD_IOGROUP_KEYBOARD_QNX                 (KD_IO_UNDEFINED + 0x1000)
#define KD_STATE_KEYBOARD_AVAILABILITY_QNX      (KD_IOGROUP_KEYBOARD_QNX + 0)
#define KD_INPUT_KEYBOARD_FLAGS_QNX             (KD_IOGROUP_KEYBOARD_QNX + 1)
#define KD_INPUT_KEYBOARD_MODIFIERS_QNX         (KD_IOGROUP_KEYBOARD_QNX + 2)
#define KD_INPUT_KEYBOARD_KEY_CAP_QNX           (KD_IOGROUP_KEYBOARD_QNX + 3)
#define KD_INPUT_KEYBOARD_KEY_SCAN_QNX          (KD_IOGROUP_KEYBOARD_QNX + 4)
#define KD_INPUT_KEYBOARD_KEY_SYM_QNX           (KD_IOGROUP_KEYBOARD_QNX + 5)

#define KD_IOGROUP_MOUSE_QNX                    (KD_IO_UNDEFINED + 0x1500)

#define KD_IOGROUP_TOUCH_QNX                    (KD_IO_UNDEFINED + 0x2000)

/* iogroup idle event */
#define KD_IOGROUP_EVENT_IDLE                   (KD_IO_UNDEFINED + 0x2500)
#define KD_STATE_EVENT_IDLE                     (KD_IOGROUP_EVENT_IDLE + 0)

KD_API KDint32 KD_APIENTRY kdOutputSetpQNX(KDint32 startidx, KDuint32 numidxs, const void *buffer);

#endif /* KD_QNX_input */

#endif /* KD_QNX_INPUT_H_ */
