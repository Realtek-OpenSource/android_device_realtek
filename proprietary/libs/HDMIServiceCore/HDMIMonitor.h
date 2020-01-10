#ifndef _HDMI_MONITOR_
#define _HDMI_MONITOR_

#include <pthread.h>
#include <sysutils/NetlinkEvent.h>
#include <utils/Vector.h>
#include <utils/Mutex.h>

#include "HdmiCommon.h"

using namespace android;

namespace android_hdmi_hidl {

typedef struct _HDMITX_STATUS {
    int32_t mWidth;
    int32_t mHeight;
    int32_t mFps;
    int32_t mProgressive;
} HDMITX_STATUS;

class HDMIMonitor {

    // define a simple EventQueue, but no one use it now.
    class EventQueue {
    public:
        EventQueue() {}
        ~EventQueue() {}

        Vector<int32_t> mQueue;
        Mutex           mLock;

        void            push(int32_t event);
        int32_t         peek();
        void            pop();
        int32_t         getSize();
    };

public:
    static HDMIMonitor * sInstance;

    static HDMIMonitor *Instance();
    virtual ~HDMIMonitor();

    void handleSwitchEvent(/*NetlinkEvent *evt*/);
    void onInitialize();
    void setCallback(hdmi_module_callback_t *callback);
    void setHDCPCallback(hdcp_module_callback_t *hdcpCallback);
    // public APIs to allow clients query HDMITx status
    bool getHDMIPlugged() { return mHDMITxPlugged; }
    //HDMITX_STATUS * getTxStatus () { return &mHDMITxStatus; }

private:
    HDMIMonitor();

    pthread_t                   mUeventThread;
    HDMITX_STATUS               mHDMITxStatus;
    bool                        mHDMITxPlugged;
    hdmi_module_callback_t *    mCallback;
    hdcp_module_callback_t *    mHDCPCallback;
#if 0
    EventQueue                  mEventQueue;
#endif
    // this is the thread to monitor netlink event
    static void *pthread_entry(void *ptr);
    int getHDMITxStatus(HDMITX_STATUS *pStatus);
    bool updateHDMITxState();
    void parse_info_str(char *info_str, HDMITX_STATUS *pStatus);
    int32_t readHDMIPlugged();
};

};

#endif
