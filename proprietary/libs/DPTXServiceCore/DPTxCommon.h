#ifndef _DPTX_COMMON_H_
#define _DPTX_COMMON_H_

typedef struct dptx_module_callback {

    /**
     * callback to handle dptx event
     */
    void (*handle_event)(
        const struct dptx_module_callback* callback,
        int32_t event);

} dptx_module_callback_t;

#endif
