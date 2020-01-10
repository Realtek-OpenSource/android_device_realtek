#ifndef _HDMI_CALLBACK_H_
#define _HDMI_CALLBACK_H_

#include <utils/Errors.h>
#include "HdmiConstDef.h"

namespace hdmi_hidl {

typedef struct hdmi_core_module_callback {

    void (*handle_core_event)(
            const struct hdmi_core_module_callback *callback,
            int32_t event,
            int32_t vic,
            int32_t mode,
            int32_t interfaceType);

} hdmi_core_module_callback_t;

};

#endif // _HDMI_CALLBACK_H_
