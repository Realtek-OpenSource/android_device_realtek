#define LOG_NDEBUG 0
#define LOG_TAG "HDMI-HIDL-HDMILib"

#include <sys/types.h>
#include <unistd.h>

#include <utils/KeyedVector.h>
#include <utils/Log.h>
#include "HDMILib.h"
#include "Debug.h"
//#include "backtrace.h"

#include <vendor/realtek/hdmiutil/common/1.0/types.h>
#include <vendor/realtek/hdmiutil/provider/1.0/IHdmiUtil.h>
#include <vendor/realtek/hdmiutil/provider/1.0/IHdmiUtilCallback.h>

#define DEBUG_HDMI_LIB  (0)

#define PRINTF_BINARY_PATTERN_INT8 "%c%c%c%c"

#define PRINTF_BYTE_TO_BINARY_INT8(i)    \
    (((i) & 0x08ll) ? '1' : '0'), \
    (((i) & 0x04ll) ? '1' : '0'), \
    (((i) & 0x02ll) ? '1' : '0'), \
    (((i) & 0x01ll) ? '1' : '0')

using ::android::hardware::Return;
using ::android::hardware::Void;

//using ::vendor::realtek::hdmiutil::common::V1_0::VideoFormat;
using ::vendor::realtek::hdmiutil::common::V1_0::EDIDData;
using ::vendor::realtek::hdmiutil::common::V1_0::HDMIFormatSupport;
using ::vendor::realtek::hdmiutil::common::V1_0::EDIDSupportList;
using ::vendor::realtek::hdmiutil::common::V1_0::OutputFormat;
using ::vendor::realtek::hdmiutil::common::V1_0::ColorSet;
using ::vendor::realtek::hdmiutil::common::V1_0::TVCapInfo;

using ::vendor::realtek::hdmiutil::provider::V1_0::IHdmiUtil;
using ::vendor::realtek::hdmiutil::provider::V1_0::IHdmiUtilCallback;

namespace realtek {

//static Mutex sGlobalLock;

struct HdmiControl :
    virtual public IHdmiUtilCallback,
    virtual public hardware::hidl_death_recipient
{
    sp<IHdmiUtil>       mInterface = nullptr;
    HDMILib *           mParent;
    int32_t             mKey;
    // callback lock
    Mutex               mLock;
    Mutex               mInterfaceLock;
    // constructor, destructor
    HdmiControl(HDMILib *parent);

    ~HdmiControl();

    virtual hardware::Return<void> handleEvent(
            int32_t event,
            int32_t vic,
            int32_t mode,
            int32_t interfaceType) override;

    virtual void serviceDied(
            uint64_t cookie,
            const wp<hidl::base::V1_0::IBase>& who) override;

    IHdmiUtil * getService();
    IHdmiUtil * tryGetService();

    void setCallback();
    void removeCallback();

};

static KeyedVector<HDMILib *, sp<HdmiControl>> sInternalMap;

static inline HdmiControl * cast(void *pt)
{
    return const_cast<HdmiControl*>(static_cast<const HdmiControl*>(pt));
}

HDMILib::HDMILib()
: mCallback(NULL),
  mCallback2(NULL)
{
    //Mutex::Autolock gl(sGlobalLock);
    ALOGD("HDMILib()");
    sp<HdmiControl> ctl = new HdmiControl(this);
    sInternalMap.add(this,ctl);
    ctl = NULL;
}

HDMILib::~HDMILib()
{
    //Mutex::Autolock gl(sGlobalLock);
    Mutex::Autolock l(mLock);
    ALOGD("~HDMILib()");
    sInternalMap.removeItem(this);
}

bool
HDMILib::tryGetService()
{
    Mutex::Autolock l(mLock);
    if(cast(getHdmiControl())->tryGetService() != NULL) {
        return true;
    }else{
        return false;
    }
}

void *
HDMILib::getHdmiControl() {
    sp<HdmiControl> value = sInternalMap.valueFor(this);
    CHECK(value.get() != NULL);
    return (void *) value.get();
}

int32_t
HDMILib::acquireLock(int32_t type)
{
    Mutex::Autolock l(mLock);
    return cast(getHdmiControl())->getService()->acquireLock(type);
}

void
HDMILib::releaseLock(int32_t type)
{
    Mutex::Autolock l(mLock);
    cast(getHdmiControl())->getService()->releaseLock(type);
}

void
HDMILib::getSinkCapability()
{
    Mutex::Autolock l(mLock);
    cast(getHdmiControl())->getService()->getSinkCapability();
}

bool
HDMILib::checkIfHDMIPlugged()
{
    Mutex::Autolock l(mLock);
    bool rst = cast(getHdmiControl())->getService()->checkIfHDMIPlugged();
    return rst;
}

bool
HDMILib::getHDMIEDIDReady()
{
    Mutex::Autolock l(mLock);
    bool rst = cast(getHdmiControl())->getService()->getHDMIEDIDReady();
    return rst;
}

const char *
HDMILib::findVICName(HDMI_VIC_ENUM id)
{
    size_t length = sizeof(sVICInfo)/sizeof(VIC_INFO);
    for(size_t i=0;i<length;i++) {
        if(sVICInfo[i].id == id) {
            return sVICInfo[i].name;
        }
    }
    CHECK(NULL);
    return NULL;
}

status_t
HDMILib::getColorSet(
    int32_t *pColor,
    int32_t *pColorDepth,
    int32_t vic,
    int32_t hdr,
    int32_t policy)
{
    Mutex::Autolock l(mLock);

#if 0
    int32_t color_rst = cast(getHdmiControl())->getService()->getColorSet2(
                            vic,
                            hdr,
                            policy);

    if(color_rst == -1) {
        *pColor = -1;
        *pColorDepth = -1;
        return INVALID_OPERATION;
    }else{
        *pColor = GET_COLOR(color_rst);
        *pColorDepth = GET_COLOR_DEPTH(color_rst);
        return OK;
    }
#endif

#if 1
    *pColor = -1;
    *pColorDepth = -1;

    int32_t rst = 0;
    hardware::Return<void> ret;
    ColorSet cSet = {-1,-1};

    ret = cast(getHdmiControl())->getService()->getColorSet(
                            vic,
                            hdr,
                            policy,
                            [&rst, &cSet](int32_t result, ColorSet colorSet){
                                rst = result;
                                cSet = colorSet;
                            });

    if(!ret.isOk()) {
        ALOGE("%s Error %s",
            __FUNCTION__,
            ret.description().c_str() );
        return DEAD_OBJECT;
    }

    if(rst) {
        ALOGD("%s OK color:%d color_depth:%d",
            __FUNCTION__,
            cSet.color,
            cSet.color_depth);

        *pColor = cSet.color;
        *pColorDepth = cSet.color_depth;
        return OK;
    } else {
        ALOGE("%s NG",__FUNCTION__);
        return INVALID_OPERATION;
    }
#endif
}

status_t
HDMILib::getTVCapInfo(HDMITVCapInfo *pInfo)
{
    Mutex::Autolock l(mLock);

    CHECK(pInfo != NULL);
    memset(pInfo,0x0,sizeof(HDMITVCapInfo));

    int32_t rst = 0;
    TVCapInfo hInfo;
    hardware::Return<void> ret;
    ret = cast(getHdmiControl())->getService()->getTVCapInfo([&rst,&hInfo](int32_t result, TVCapInfo hidlInfo){
            rst = result;
            hInfo = hidlInfo;
        });

    if(!ret.isOk()) {
        ALOGE("%s Error",__FUNCTION__);
        return DEAD_OBJECT;
    }

    if(rst) {
        ALOGD("%s OK",__FUNCTION__);
        pInfo->mConnected       = hInfo.mConnected;
        pInfo->mEotf            = hInfo.mEotf;
        pInfo->mDV              = hInfo.mDV;
        pInfo->mMetaDataLen     = hInfo.mMetaDataLen;
        pInfo->mMaxLuminance    = hInfo.mMaxLuminance;
        pInfo->mAvgLuminance    = hInfo.mAvgLuminance;
        pInfo->mMinLuminance    = hInfo.mMinLuminance;
        return OK;
    } else {
        return INVALID_OPERATION;
    }
}

status_t
HDMILib::getEDIDSupportList()
{
    Mutex::Autolock l(mLock);

    mEDIDSupportList.clear();

    int32_t rst = 0;
    EDIDSupportList lst;
    hardware::Return<void> ret;
    ret = cast(getHdmiControl())->getService()->getEDIDSupportList([&rst, &lst](int32_t result, EDIDSupportList list){
            rst = result;
            lst = list;
        });

    if(!ret.isOk()) {
        ALOGE("%s Error",__FUNCTION__);
        return DEAD_OBJECT;
    }

    if(rst) {
        ALOGD("%s OK",__FUNCTION__);
        int32_t size = lst.mList.size();

        for(int i=0;i<size;i++) {
            HDMIFormatSupport item = lst.mList[i];
#if (DEBUG_HDMI_LIB)
            ALOGD("VIC:%2d[%20s]"
                " rgb:" PRINTF_BINARY_PATTERN_INT8
                " 422:" PRINTF_BINARY_PATTERN_INT8
                " 444:" PRINTF_BINARY_PATTERN_INT8
                " 420:" PRINTF_BINARY_PATTERN_INT8 ,
                item.vic,
                findVICName((HDMI_VIC_ENUM) item.vic),
                PRINTF_BYTE_TO_BINARY_INT8(item.rgb444),
                PRINTF_BYTE_TO_BINARY_INT8(item.yuv422),
                PRINTF_BYTE_TO_BINARY_INT8(item.yuv444),
                PRINTF_BYTE_TO_BINARY_INT8(item.yuv420));
#endif

            mEDIDSupportList.add(
                HDMI_FORMAT_SUPPORT(
                    item.vic,
                    item.rgb444,
                    item.yuv422,
                    item.yuv444,
                    item.yuv420,
                    item.support_3d,
                    item.support_fs,
                    item.reserved));

        }
        return OK;
    }else{
        return INVALID_OPERATION;
    }
}

#if 0
int32_t
HDMILib::setHDMIVideoColorMode(int32_t mode)
{
    Mutex::Autolock l(mLock);
    int32_t rst = cast(getHdmiControl())->getService()->setHDMIVideoColorMode(
        mode);

    return rst;
}
#endif

status_t
HDMILib::getEDIDRawData(uint8_t *out, int32_t length)
{
    Mutex::Autolock l(mLock);

    //ALOGD("%s : E",__FUNCTION__);

    int32_t rst = 0;
    EDIDData data;
    hardware::Return<void> ret;
    ret = cast(getHdmiControl())->getService()->getEDIDRawData([&rst,&data](int32_t result, EDIDData edid){
            rst = result;
            data = edid;
        });

    if(!ret.isOk()) {
        ALOGE("%s Error",__FUNCTION__);
        return DEAD_OBJECT;
    }

    if(rst) {

        int32_t size = (int32_t) data.mData.size();
        CHECK(size == length);

        for(int i=0;i<length;i++) {
            out[i] = data.mData[i];
        }

        return OK;
    }else{
        return INVALID_OPERATION;
    }
}

bool
HDMILib::isTVSupport3D()
{
    Mutex::Autolock l(mLock);
    bool rst = cast(getHdmiControl())->getService()->isTVSupport3D();
    return rst;
}

int32_t
HDMILib::setHDMIFormat3D(
    int32_t format3d,
    float fps)
{
    Mutex::Autolock l(mLock);
    int32_t rst = cast(getHdmiControl())->getService()->setHDMIFormat3D(
        format3d,
        fps);

    return rst;
}

void
HDMILib::setHDMIEnable(int32_t enable)
{
    Mutex::Autolock l(mLock);
    cast(getHdmiControl())->getService()->setHDMIEnable(enable);
}

int32_t
HDMILib::setOutputFormat(const HDMI_OUTPUT_FORMAT &fmt,
    int32_t flags)
{
    Mutex::Autolock l(mLock);

    OutputFormat format;

    HIDL_OUTPUT_FORMAT_ASSIGN(format,fmt);

#if 0
    format.vic          = fmt.vic;
    format.freq_shift   = fmt.freq_shift;
    format.color        = fmt.color;
    format.color_depth  = fmt.color_depth;
    format._3d_format   = fmt._3d_format;
    format.hdr          = fmt.hdr;
#endif

    int32_t rst = cast(getHdmiControl())->getService()->setOutputFormat(format,flags);

    return rst;
}

status_t
HDMILib::getCurrentOutputFormat(HDMI_OUTPUT_FORMAT *pRst)
{
    Mutex::Autolock l(mLock);
    int32_t rst = 0;

    OutputFormat data;
    hardware::Return<void> ret;

    ret = cast(getHdmiControl())->getService()->getCurrentOutputFormat([&rst,&data](int32_t result, OutputFormat fmt){
            rst = result;
            data = fmt;
        });

    if(!ret.isOk()) {
        ALOGE("%s Error",__FUNCTION__);
        return DEAD_OBJECT;
    }

    if(rst) {
        HIDL_OUTPUT_FORMAT_ASSIGN_PT(pRst,data);
        return OK;
    } else {
        return INVALID_OPERATION;
    }
}

status_t
HDMILib::readOutputFormat(HDMI_OUTPUT_FORMAT *pRst)
{
    Mutex::Autolock l(mLock);
    int32_t rst = 0;

    OutputFormat data;
    hardware::Return<void> ret;

    ret = cast(getHdmiControl())->getService()->readOutputFormat([&rst,&data](int32_t result, OutputFormat fmt){
            rst = result;
            data = fmt;
        });

    if(!ret.isOk()) {
        ALOGE("%s Error",__FUNCTION__);
        return DEAD_OBJECT;
    }

    if(rst) {
        HIDL_OUTPUT_FORMAT_ASSIGN_PT(pRst,data);
        return OK;
    } else {
        return INVALID_OPERATION;
    }
}

status_t
HDMILib::saveOutputFormat(const HDMI_OUTPUT_FORMAT &format)
{
    Mutex::Autolock l(mLock);

    OutputFormat hidl_format;

    HIDL_OUTPUT_FORMAT_ASSIGN(hidl_format,format);

    cast(getHdmiControl())->getService()->saveOutputFormat(hidl_format);
    return OK;
}

int32_t
HDMILib::readColorModeEnum()
{
    Mutex::Autolock l(mLock);
    return cast(getHdmiControl())->getService()->readColorModeEnum();
}

int32_t
HDMILib::readHDRAutoProperty()
{
    Mutex::Autolock l(mLock);
    return cast(getHdmiControl())->getService()->readHDRAutoProperty();
}

int32_t
HDMILib::isUnderDoviMode(int32_t mode)
{
    Mutex::Autolock l(mLock);
    return cast(getHdmiControl())->getService()->isUnderDoviMode(mode);
}

int32_t
HDMILib::checkHDRModeSupported(int32_t mode)
{
    Mutex::Autolock l(mLock);
    return cast(getHdmiControl())->getService()->checkHDRModeSupported(mode);
}

int32_t
HDMILib::readEdidAutoMode()
{
    Mutex::Autolock l(mLock);
    return cast(getHdmiControl())->getService()->readEdidAutoMode();
}

status_t
HDMILib::saveColorModeEnum(int32_t value)
{
    Mutex::Autolock l(mLock);
    cast(getHdmiControl())->getService()->saveColorModeEnum(value);
    return OK;
}

status_t
HDMILib::saveEdidAutoMode(int32_t value)
{
    Mutex::Autolock l(mLock);
    cast(getHdmiControl())->getService()->saveEdidAutoMode(value);
    return OK;
}

void
HDMILib::setHDREotfMode(int32_t mode)
{
    Mutex::Autolock l(mLock);
    cast(getHdmiControl())->getService()->setHDREotfMode(mode);
}

void
HDMILib::setHDCPVersion(int32_t version)
{
    Mutex::Autolock l(mLock);
    cast(getHdmiControl())->getService()->setHDCPVersion(version);
}

int32_t
HDMILib::getHDCPVersion()
{
    Mutex::Autolock l(mLock);
    int32_t hdcp = cast(getHdmiControl())->getService()->getHDCPVersion();
    return hdcp;
}

int32_t
HDMILib::getConfiguredHDCPVersion()
{
    Mutex::Autolock l(mLock);
    int32_t hdcp = cast(getHdmiControl())->getService()->getConfiguredHDCPVersion();
    return hdcp;
}

bool
HDMILib::hdmiIsOn()
{
    HDMI_OUTPUT_FORMAT fmt = {};
    getCurrentOutputFormat(&fmt);
    if(fmt.mode != NO_OUTPUT_MODE) {
        return true;
    } else {
        return false;
    }
}

void
HDMILib::setCallback()
{
    Mutex::Autolock l(mLock);
    cast(getHdmiControl())->setCallback();
}

void
HDMILib::removeCallback()
{
    Mutex::Autolock l(mLock);
    cast(getHdmiControl())->removeCallback();
}

// ------ HdmiControl ------ //
HdmiControl::HdmiControl(HDMILib *parent)
{
    ALOGD("HdmiControl()");
    mParent = parent;
    mKey = (int32_t) getpid();

#if 0
    {
        Mutex::Autolock l(mParent->mLock);
        getService();
    }
#endif
}

HdmiControl::~HdmiControl()
{
    {
        Mutex::Autolock l(mLock);
        //backtrace(LOG_TAG);
        ALOGD("~HdmiControl() %p",this);
        getService()->removeCallback(mKey);
    }
}

void
HdmiControl::setCallback()
{
    Mutex::Autolock l(mLock);
    getService()->setCallback(mKey,this);
}

void
HdmiControl::removeCallback()
{
    Mutex::Autolock l(mLock);
    getService()->removeCallback(mKey);
}

IHdmiUtil *
HdmiControl::tryGetService() {
    Mutex::Autolock l(mInterfaceLock);
    if(mInterface == nullptr) {
        mInterface = IHdmiUtil::tryGetService();
    }
    //ALOGD("[%s] mInterface:%p",__FUNCTION__,mInterface.get());
    return mInterface.get();
}

IHdmiUtil *
HdmiControl::getService()
{
    //ALOGD("[%s] : E",__FUNCTION__);
    while(mInterface == nullptr) {
        tryGetService();
        usleep(100 * 1E3);
    }
    //ALOGD("[%s] : X %p",__FUNCTION__,mInterface.get());
    return mInterface.get();
}

// HIDL function
hardware::Return<void>
HdmiControl::handleEvent(
        int32_t event,
        int32_t vic,
        int32_t mode,
        int32_t interfaceType)
{
    ALOGD("%s:E callback %p callback2 %p event %d",
        __FUNCTION__,
        mParent->mCallback,
        mParent->mCallback2,
        event);

    Mutex::Autolock l(mParent->mLock);
    // call registered callback from outside
    if(mParent->mCallback != NULL)
    {
        ALOGD("deliver event to outside");
        mParent->mCallback->handle_hdmi_event(
                mParent->mCallback,
                event,
                vic,
                mode);
    }

    if(mParent->mCallback2 != NULL)
    {
        ALOGD("deliver event to outside");
        mParent->mCallback2->handle_hdmi_event(
                mParent->mCallback2,
                event,
                vic,
                mode,
                interfaceType);
    }

    return Void();
}

void
HdmiControl::serviceDied(
    uint64_t /*cookie */,
    const wp<hidl::base::V1_0::IBase>& /*who*/)
{
    Mutex::Autolock l(mParent->mLock);
    ALOGW("%s:E",__FUNCTION__);
    mInterface = nullptr;
}

}; // namespace realtek

