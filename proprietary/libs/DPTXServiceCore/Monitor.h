#ifndef _MONITOR_
#define _MONITOR_

#include <pthread.h>
#include <sysutils/NetlinkEvent.h>
#include <utils/Vector.h>
#include <utils/Mutex.h>

#include "DPTxCommon.h"

using namespace android;

namespace android_dptx_hidl {

class Monitor {

public:
    static Monitor * sInstance;

    static Monitor *Instance();
    virtual ~Monitor();

    void handleSwitchEvent(/*NetlinkEvent *evt*/);
    void onInitialize();
    void setCallback(dptx_module_callback_t *callback);
    bool getPlugged() { return mPlugged; }

private:
    Monitor();

    pthread_t                   mUeventThread;
    bool                        mPlugged;
    dptx_module_callback_t *    mCallback;

    // this is the thread to monitor netlink event
    static void *               pthread_entry(void *ptr);

    bool                        updateDPTxState();
    int32_t                     readPlugged();
};

};

#endif
