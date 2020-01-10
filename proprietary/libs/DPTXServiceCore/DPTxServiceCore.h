#ifndef _REALTEK_DPTX_SERVICE_CORE_H_
#define _REALTEK_DPTX_SERVICE_CORE_H_

#include <utils/threads.h>
#include <utils/Mutex.h>
#include <utils/Vector.h>
#include <utils/Errors.h>
#include <hardware/hardware.h>

#include "DPTxConstDef.h"
#include "rtk_dptx.h"
#include "OneStepHelper.h"
#include "DPTxCallback.h"
#include "HDMILib.h"

using namespace android;
using namespace dptx_hidl;
using namespace realtek;

typedef struct _TV_SYSTEM_INFO {
    HDMI_VIC_ENUM   mVic;
    int32_t         mWidth;
    int32_t         mHeight;
    int32_t         mFps;
    bool            mProgressive;
} TV_SYSTEM_INFO;

typedef struct _hdmi_event {
    int32_t mEvent;
    int32_t mVic;
    int32_t mMode;
} hdmi_event_t;

class DPTxServiceCore : public hdmilib_module_callback_t {

    // hdmi event process thread
    class HDMIEventProcessThread : public Thread {
    public:
        HDMIEventProcessThread(DPTxServiceCore *parent) {
            mParent = parent;
            mRunning = true;
        }

        ~HDMIEventProcessThread(){}

        void                    signal();
        void                    stop();
        void                    queueEvent(hdmi_event_t event);
    private:
        virtual bool            threadLoop();

        bool                    mRunning;
        Mutex                   mLk;
        Condition               mSignal;
        DPTxServiceCore *       mParent;
        Vector<hdmi_event_t>    mEventQueue;
    };

    // dptx core event deliver thread
    class EventThread : public Thread {
    public:
        EventThread(DPTxServiceCore *parent);
        ~EventThread();
        void                    signal();
        void                    stop();
        void                    queueEvent(int32_t event);
    private:
        virtual bool            threadLoop();
        Mutex                   mLk;
        Condition               mSignal;
        DPTxServiceCore *       mParent;
        bool                    mRunning;
        Vector<int32_t>         mEventQueue;
    };

    // hdmi interface polling thread
    class HDMIPollingThread : public Thread {
    public:
        HDMIPollingThread(DPTxServiceCore *parent){ mParent = parent; }
        ~HDMIPollingThread(){}
    private:
        virtual bool            threadLoop();
        DPTxServiceCore *       mParent;
    };

public:
    DPTxServiceCore(dptx_core_module_callback_t * callback);
    ~DPTxServiceCore();

    bool                        mDPTxPlugged;
    void                        handleEvent(int32_t event);

    // service API
    void                        saveEdidAutoMode(int32_t value);
    int32_t                     readEdidAutoMode();

    status_t                    readOutputFormat(DPTX_OUTPUT_FORMAT *fmt);
    status_t                    readOutputFormat(
                                    DPTX_OUTPUT_FORMAT *fmt,
                                    bool dp,
                                    bool hdmi);
    int32_t                     saveOutputFormat(DPTX_OUTPUT_FORMAT fmt);

    void                        setOutputFormat(DPTX_OUTPUT_FORMAT fmt, int32_t flags);
    void                        getEDIDSupportList(struct dptx_support_list *pList);
    void                        getCurrentOutputFormat(DPTX_OUTPUT_FORMAT *pRst);

    int32_t                     hasDPTxBackend();

private:
    struct dptx_device_t *          mDPTXDevice;
    struct dptx_support_list        mEDIDSupportList;
    dptx_core_module_callback_t *   mCallback;

    Mutex                           mHDMILibLock;
    HDMILib *                       mHDMILib;
    int32_t                         mHDCPVersion;

    Mutex                           mLock;
    OneStepHelper *                 mOneStepHelper;
    sp<EventThread>                 mCoreEventThread;
    sp<HDMIPollingThread>           mHDMIPollingThread;
    sp<HDMIEventProcessThread>      mHDMIEventProcessThread;

    int32_t                         mHDMISession;

    status_t                    initDPTXDevice(void);
    status_t                    deInitDPTXDevice(void);
    int32_t                     getIntProperty(
                                    const char *property,
                                    int32_t _dft);

    void                        handlePluginEvent();
    void                        handlePlugoutEvent();

    void                        turnOffDP();
    void                        turnOffDPIgnoreHDMI(hdmi_event_t e);
    void                        turnOnDP();
    void                        turnOnDPIgnoreHDMI(hdmi_event_t e);
    bool                        _hdmiIsOn(hdmi_event_t e);
    bool                        hdmiIsOn();
    void                        halSetOutputFormat(
                                    struct dptx_format_setting fmt,
                                    bool lockHDMI);

    void                        dumpEDIDSupportList(struct dptx_support_list *pList);
    void                        resolveAutoOutputFormat(DPTX_OUTPUT_FORMAT *pRst);
    TV_SYSTEM_INFO *            findTvSystemInfoViaVIC(HDMI_VIC_ENUM vic);
    bool                        isOutputFormatSupported(DPTX_OUTPUT_FORMAT fmt);
    bool                        compareEDIDChecksum();
    INTERFACE_TYPE              resolveDisplayMode(bool dpOn);

    bool                        isDiffSourceOn();
    HDMILib *                   getHDMILib();
    static void                 hdmiEventHandler(
                                    const struct hdmilib_module_callback * callback,
                                    int32_t event,
                                    int32_t vic,
                                    int32_t mode);

    void                        onHDMIEvent(hdmi_event_t e);
    void                        waitHDMIComplete(bool on);
    void                        notifyHDMI(int32_t event);
    INTERFACE_TYPE              getCurrentInterfaceType();
    void                        acquireLock(int32_t type);
    void                        releaseLock(int32_t type);
};


#endif
