#ifndef _HDMI_LIB_
#define _HDMI_LIB_

#include <utils/Mutex.h>
#include <utils/Errors.h>
#include <utils/Vector.h>
#include <utils/RefBase.h>

#include "HdmiConstDef.h"

using namespace android;

//typedef void (*handle_hdmi_event)(int32_t event);

typedef struct hdmilib_module_callback {

    void (*handle_hdmi_event)(
            const struct hdmilib_module_callback *callback,
            int32_t event,
            int32_t vic,
            int32_t mode);

} hdmilib_module_callback_t;

typedef struct hdmilib_module_callback_2 {

    void (*handle_hdmi_event)(
            const struct hdmilib_module_callback_2 *callback,
            int32_t event,
            int32_t vic,
            int32_t mode,
            int32_t interfaceType);

} hdmilib_module_callback_2_t;

namespace realtek {

class HDMILib : public RefBase {

public:
    HDMILib();
    ~HDMILib();

    bool        tryGetService();

    bool        checkIfHDMIPlugged();
    bool        getHDMIEDIDReady();

    status_t    getEDIDRawData(uint8_t *out, int32_t length);
    bool        isTVSupport3D();
    int32_t     setHDMIFormat3D(int32_t format3d,
                    float fps);

    status_t    readOutputFormat(HDMI_OUTPUT_FORMAT *pRst);
    status_t    saveOutputFormat(const HDMI_OUTPUT_FORMAT &format);
    status_t    getCurrentOutputFormat(HDMI_OUTPUT_FORMAT *pRst);

    int32_t     readEdidAutoMode();
    status_t    saveEdidAutoMode(int32_t value);

    int32_t     readColorModeEnum();
    status_t    saveColorModeEnum(int32_t value);

    int32_t     readHDRAutoProperty();

    int32_t     isUnderDoviMode(int32_t mode);
    int32_t     checkHDRModeSupported(int32_t mode);

    status_t    getColorSet(int32_t *pColor,
                    int32_t *pColorDepth,
                    int32_t vic,
                    int32_t hdr,
                    int32_t policy);

    void        setCallback();
    void        removeCallback();

#if 0
    int32_t     setHDMIVideoColorMode(int32_t mode);
    int32_t     setTVSystem(int32_t value);
    int32_t     getTVSystemForRestored();
    int32_t     getTVSystem();
    status_t    getVideoFormat();
#endif

    // following is the new API designed for ner HDMI driver
    int32_t     setOutputFormat(const HDMI_OUTPUT_FORMAT &format,
                    int32_t flags);

    status_t    getEDIDSupportList();

    void        setHDREotfMode(int32_t mode);

    void        setHDMIEnable(int32_t enable);

    status_t    getTVCapInfo(HDMITVCapInfo *pInfo);

    void        getSinkCapability();
    int32_t     acquireLock(int32_t type);
    void        releaseLock(int32_t type);

    void        setHDCPVersion(int32_t version);
    int32_t     getHDCPVersion();
    int32_t     getConfiguredHDCPVersion();

    bool        hdmiIsOn();

    Mutex                           mLock;
    //void *                        mControl;
    Vector<HDMI_FORMAT_SUPPORT>     mEDIDSupportList;
    hdmilib_module_callback_t *     mCallback;
    hdmilib_module_callback_2_t*    mCallback2;
    //handle_hdmi_event             mEventHandler;

private:
    const char *    findVICName(HDMI_VIC_ENUM id);
    void *          getHdmiControl();
};

};

#endif
