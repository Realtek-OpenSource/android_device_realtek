#ifndef _MONITOR_
#define _MONITOR_

#include <stdio.h>
#include <pthread.h>
#include <sysutils/NetlinkEvent.h>
#include <utils/Vector.h>
#include <utils/Mutex.h>

#include "AudioCommon.h"

using namespace android;

typedef struct hdmi_rx_event_info {
    int32_t         mEventType;
    const char *    mMsg;
    int32_t         mValue;
} hdmi_rx_event_info_t;

namespace android_hdmirx_audio {

typedef struct hdmirx_module_callback {

    void (*handle_event)(
        const struct hdmirx_module_callback* callback,
        int32_t event);

} hdmirx_module_callback_t;

class Monitor {

public:
    static Monitor * sInstance;

    static Monitor *Instance();
    virtual ~Monitor();

    void handleSwitchEvent(hdmi_rx_event_info_t *event);
    void onInitialize();
    void setCallback(hdmirx_module_callback_t *callback);

private:
    Monitor();

    pthread_t                   mUeventThread;
    hdmirx_module_callback_t *  mCallback;
    hdmirx_audio_info_t         mAudioInfo;

    // this is the thread to monitor netlink event
    static void *               pthread_entry(void *ptr);

};

};

#endif
