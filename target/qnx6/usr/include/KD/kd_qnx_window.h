#ifndef KD_QNX_WINDOW_H_
#define KD_QNX_WINDOW_H_

#ifndef KD_QNX_window
#define KD_QNX_window 1

#define KD_EVENT_WINDOW_CREATE_QNX              (KD_EVENT_UNDEFINED_QNX + 0)
#define KD_EVENT_WINDOW_REALIZE_QNX             (KD_EVENT_UNDEFINED_QNX + 1)
#define KD_EVENT_WINDOW_PROPERTY_QNX            (KD_EVENT_UNDEFINED_QNX + 2)
#define KD_EVENT_WINDOW_CLOSE_QNX               (KD_EVENT_UNDEFINED_QNX + 3)

#define KD_WINDOWPROPERTY_CLASS_QNX             1001
#define KD_WINDOWPROPERTY_ID_STRING_QNX         1002
#define KD_WINDOWPROPERTY_DISPLAY_QNX           1003
#define KD_WINDOWPROPERTY_POSITION_QNX          1004
#define KD_WINDOWPROPERTY_SOURCE_POSITION_QNX   1005
#define KD_WINDOWPROPERTY_SOURCE_SIZE_QNX       1006
#define KD_WINDOWPROPERTY_SURFACE_SIZE_QNX      1007
#define KD_WINDOWPROPERTY_ALPHA_QNX             1008
#define KD_WINDOWPROPERTY_DELEGATE_POINTER_QNX  1009
#define KD_WINDOWPROPERTY_DELEGATE_QNX          1010
#define KD_WINDOWPROPERTY_SOURCE_ALPHA_QNX      1011
#define KD_WINDOWPROPERTY_SENSITIVE_QNX         1012
#define KD_WINDOWPROPERTY_MANAGED_QNX           1013
#define KD_WINDOWPROPERTY_SWAP_INTERVAL_QNX     1014
#define KD_WINDOWPROPERTY_POINTER_FOCUS_QNX     1015
#define KD_WINDOWPROPERTY_BRIGHTNESS_QNX        1016
#define KD_WINDOWPROPERTY_CONTRAST_QNX          1017
#define KD_WINDOWPROPERTY_HUE_QNX               1018
#define KD_WINDOWPROPERTY_SATURATION_QNX        1019
#define KD_WINDOWPROPERTY_LEVEL_QNX             1020
#define KD_WINDOWPROPERTY_FREEZE_QNX            1021

#define KD_WINDOW_BOTTOM_QNX                    (struct KDWindow *)0
#define KD_WINDOW_LOWER_QNX                     (struct KDWindow *)1
#define KD_WINDOW_RAISE_QNX                     (struct KDWindow *)2
#define KD_WINDOW_TOP_QNX                       (struct KDWindow *)3

struct KDEvent;

typedef struct KDEventWindowCreateQNX {
    struct KDWindow *window;
    KDint32          valid;
    KDint32          flags;
    KDint32          egl_config;
    void            *userptr;
} KDEventWindowCreateQNX;

typedef struct KDEventWindowRealizeQNX {
    struct KDWindow *window;
    int              sid;
} KDEventWindowRealizeQNX;

typedef struct KDEventWindowPropertyQNX {
    struct KDWindow *window;
    KDint32          pname;
} KDEventWindowPropertyQNX;

typedef struct KDEventWindowCloseQNX {
    struct KDWindow *window;
} KDEventWindowCloseQNX;

KD_API struct KDWindow *KD_APIENTRY kdDuplicateWindowQNX(struct KDWindow *window, void *eventuserptr);

KD_API KDint32 KD_APIENTRY kdPostWindowEventQNX(struct KDEvent *event, struct KDWindow *window);

KD_API KDint32 KD_APIENTRY kdSetWindowOrderQNX(struct KDWindow *window, struct KDWindow *above);

#endif /* KD_QNX_window */

#endif /* KD_QNX_WINDOW_H_ */
