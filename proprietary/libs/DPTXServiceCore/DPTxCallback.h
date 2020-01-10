#ifndef _DPTX_CALLBACK_H_
#define _DPTX_CALLBACK_H_

namespace dptx_hidl {

typedef struct dptx_core_module_callback {

    void (*handle_core_event)(
            const struct dptx_core_module_callback *callback,
            int32_t event,
            int32_t vic,
            int32_t type);

} dptx_core_module_callback_t;

};

#endif // _DPTX_CALLBACK_H_
