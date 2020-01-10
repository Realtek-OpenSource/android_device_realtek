#ifndef _HDCP_CORE_H
#define _HDCP_CORE_H

#include <utils/Errors.h>
#include <utils/Mutex.h>
#include "HdmiConstDef.h"
// for HDCP hal wrapping, HDCP 1.4
#include "HDCPController.h"
// for HDCP 2.2
#include "HDMI_HDCP_API.h"
#include "HdmiCommon.h"
#include "HDCPCallback.h"

using namespace android;
using namespace hdmi_hidl;

namespace android_hdmi_hidl {

typedef struct _HDCP_CTRL {
    int32_t     mVersion;
    int32_t     mDelay;
    bool        mRunning;
} HDCP_CTRL;

//void hdcp_handle_event(const struct hdcp_module_callback* callback);

class HDCPCore : public hdcp_module_callback_t {

public:
    HDCPCore(HDCPCallback *pCb);
    ~HDCPCore();

    // new API
    status_t setHDCPVersionAsync(int32_t version, int32_t delaySec);
    status_t joinHDCPAsyncThread();
    status_t setReqHDCPVersion(int32_t version);

    int32_t getHDCPVersion();
    int32_t getSinkHDCPCapability();
    void updateHDCP1xState();
    void waitHDCPAuthState();

    static void handle_event(const struct hdcp_module_callback* callback);

    static bool             mHDCP22Enable;
    static bool             mHDCP14Enable;
    static int32_t          mSupportVersion;
    static HDCPCallback *   mCallback;

    static int32_t          mActualHDCPVersion;
    static int32_t          mReqHDCPVersion;
private:
    //int32_t               mCurrentHDCPVersion;
    //HDCPController *      mHDCPController;
    Mutex                   mLock;
    pthread_t               mHDCPThread;
    HDCP_CTRL               mHDCPCtrl;

    void enableHDCP14();
    void enableHDCP22(int32_t delaySec);

    void disableHDCP14();
    void disableHDCP22();

    bool hdmiEnabled();
    status_t setHDCPVersion(int32_t version, int32_t delaySec);

    static void *pthread_entry(void *ptr);

}; // HDCPCore

}; // android_hdmi_hidl

#endif
