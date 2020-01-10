//#define LOG_NDEBUG 0
#define LOG_TAG "DPTX-HIDL-DPTxLib"

#include <utils/KeyedVector.h>
#include <utils/Log.h>
#include "Debug.h"
#include "DPTxLib.h"

#include <vendor/realtek/dptxutil/common/1.0/types.h>
#include <vendor/realtek/dptxutil/provider/1.0/IDPTxUtil.h>
#include <vendor/realtek/dptxutil/provider/1.0/IDPTxUtilCallback.h>

#define DEBUG_DPTX_LIB (1)

using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::hardware::hidl_death_recipient;
using ::android::sp;
using ::android::Mutex;

using ::vendor::realtek::dptxutil::common::V1_0::EDIDData;
using ::vendor::realtek::dptxutil::common::V1_0::DPTxFormatSupport;
using ::vendor::realtek::dptxutil::common::V1_0::EDIDSupportList;
using ::vendor::realtek::dptxutil::common::V1_0::OutputFormat;

using ::vendor::realtek::dptxutil::provider::V1_0::IDPTxUtilCallback;
using ::vendor::realtek::dptxutil::provider::V1_0::IDPTxUtil;

namespace realtek {

struct DPTxControl :
    virtual public IDPTxUtilCallback,
    virtual public hardware::hidl_death_recipient
{
    sp<IDPTxUtil>   mInterface = nullptr;
    DPTxLib *       mParent;
    int32_t         mKey;
    Mutex           mLock;
    Mutex           mInterfaceLock;

    DPTxControl(DPTxLib *parent);
    ~DPTxControl();

    virtual hardware::Return<void> handleEvent(
            int32_t event,
            int32_t vic,
            int32_t type) override;
    virtual void serviceDied(uint64_t cookie,
        const wp<hidl::base::V1_0::IBase>& who) override;

    IDPTxUtil * getService();
    IDPTxUtil * tryGetService();

    void setCallback();
    void removeCallback();
};

DPTxControl::DPTxControl(DPTxLib *parent)
{
    ALOGD("DPTxControl()");
    mParent = parent;
    mKey = (int32_t) getpid();
#if 0
    {
        Mutex::Autolock l(mParent->mLock);
        getService();
    }
#endif
}

DPTxControl::~DPTxControl()
{
    ALOGD("~DPTxControl()");
    Mutex::Autolock l(mLock);
    getService()->removeCallback(mKey);
}

void
DPTxControl::setCallback()
{
    ALOGD("[%s] mKey:%d",
        __FUNCTION__,
        mKey);

    Mutex::Autolock l(mLock);
    getService()->setCallback(mKey,this);
}

void
DPTxControl::removeCallback()
{
    Mutex::Autolock l(mLock);
    getService()->removeCallback(mKey);
}

IDPTxUtil *
DPTxControl::tryGetService()
{
    Mutex::Autolock l(mInterfaceLock);
    if(mInterface == nullptr) {
        mInterface = IDPTxUtil::tryGetService();
    }
    ALOGD("[%s] mInterface:%p",__FUNCTION__,mInterface.get());
    return mInterface.get();
}

IDPTxUtil *
DPTxControl::getService()
{
    ALOGD("[%s] : E",__FUNCTION__);
    while(mInterface == nullptr) {
        mInterface = tryGetService();
        usleep(100 * 1E3);
    }
    ALOGD("[%s] : X %p",__FUNCTION__,mInterface.get());
    return mInterface.get();
}

// HIDL function
hardware::Return<void>
DPTxControl::handleEvent(
        int32_t event,
        int32_t vic,
        int32_t type)
{
    ALOGD("%s:E callback %p",
        __FUNCTION__,
        mParent->mCallback);

    Mutex::Autolock l(mParent->mLock);
    // call registered callback from outside
    if(mParent->mCallback != NULL)
    {
        ALOGD("deliver event to outside");
        mParent->mCallback->handle_dptx_event(
                mParent->mCallback,
                event,
                vic,
                type);
    }

    return Void();
}

void
DPTxControl::serviceDied(
    uint64_t /*cookie*/,
    const wp<hidl::base::V1_0::IBase>& /*who*/)
{
    Mutex::Autolock l(mParent->mLock);
    ALOGW("%s:E",__FUNCTION__);
    mInterface = nullptr;
}

static KeyedVector<DPTxLib *, sp<DPTxControl>> sInternalMap;

static inline DPTxControl * cast(void *pt)
{
    return const_cast<DPTxControl*>(static_cast<const DPTxControl*>(pt));
}

DPTxLib::DPTxLib()
{
    ALOGD("DPTxLib()");
    mCallback = NULL;
    sp<DPTxControl> ctl = new DPTxControl(this);
    sInternalMap.add(this,ctl);
    ctl = NULL;
}

DPTxLib::~DPTxLib()
{
    Mutex::Autolock l(mLock);
    ALOGD("~DPTxLib()");
    sInternalMap.removeItem(this);
}

bool
DPTxLib::tryGetService()
{
    Mutex::Autolock l(mLock);
    if(cast(getDPTxControl())->tryGetService() != NULL) {
        return true;
    }else{
        return false;
    }
}

void *
DPTxLib::getDPTxControl()
{
    sp<DPTxControl> value = sInternalMap.valueFor(this);
    CHECK(value.get() != NULL);
    return (void *) value.get();
}

void
DPTxLib::setCallback()
{
    Mutex::Autolock l(mLock);
    cast(getDPTxControl())->setCallback();
}

void
DPTxLib::removeCallback()
{
    Mutex::Autolock l(mLock);
    cast(getDPTxControl())->removeCallback();
}

bool
DPTxLib::dpIsOn()
{
    // there is no dptx builtin
    if(hasDPTxBackend() < 0) {
        ALOGD("[%s] XXX no dptx builtin",__FUNCTION__);
        return false;
    }

#if 0
    // use dp plugged state instead.
    if(_readDPTxState() > 0) {
        return true;
    }else{
        return false;
    }
#endif

#if 1
    DPTX_OUTPUT_FORMAT fmt = {};
    getCurrentOutputFormat(&fmt);
    bool dpOn = false;
    INTERFACE_TYPE type = (INTERFACE_TYPE) fmt.display_mode;

    ALOGD("[DPTxCore] XXX [%s] dp display_mode: %s",
        __FUNCTION__,
        _getInterfaceTypeString(type));

    switch(type) {
    case DISPLAY_PORT_ONLY:
    case HDMI_AND_DISPLAY_PORT_SAME_SOURCE:
    case HDMI_AND_DISPLAY_PORT_DIFF_SOURCE:
    case DISPLAY_PORT_AND_CVBS_SAME_SOURCE:
    case HDMI_AND_DP_DIFF_SOURCE_WITH_CVBS:
        dpOn = true;
        break;
    default:
        dpOn = false;
        break;
    }

    return dpOn;
#endif
}

status_t
DPTxLib::readOutputFormat(DPTX_OUTPUT_FORMAT *pRst)
{
    Mutex::Autolock l(mLock);
    int32_t rst = 0;

    OutputFormat data;
    hardware::Return<void> ret;

    ret = cast(getDPTxControl())->getService()->readOutputFormat([&rst,&data](
                int32_t result,
                OutputFormat fmt){
                    rst = result;
                    data = fmt;
                });

    if(!ret.isOk()) {
        ALOGE("%s Error",__FUNCTION__);
        return DEAD_OBJECT;
    }

    if(rst) {
        DP_HIDL_OUTPUT_FORMAT_ASSIGN_PT(pRst,data);
        return OK;
    } else {
        return INVALID_OPERATION;
    }
}

status_t
DPTxLib::saveOutputFormat(const DPTX_OUTPUT_FORMAT &format)
{
    Mutex::Autolock l(mLock);

    OutputFormat hidl_format;

    DP_HIDL_OUTPUT_FORMAT_ASSIGN(hidl_format,format);

    cast(getDPTxControl())->getService()->saveOutputFormat(hidl_format);
    return OK;
}

int32_t
DPTxLib::readEdidAutoMode()
{
    Mutex::Autolock l(mLock);
    return cast(getDPTxControl())->getService()->readEdidAutoMode();
}

status_t
DPTxLib::saveEdidAutoMode(int32_t value)
{
    Mutex::Autolock l(mLock);
    cast(getDPTxControl())->getService()->saveEdidAutoMode(value);
    return OK;
}

bool
DPTxLib::getDPTxEDIDReady()
{
    Mutex::Autolock l(mLock);
    bool rst = cast(getDPTxControl())->getService()->getDPTxEDIDReady();
    return rst;
}

int32_t
DPTxLib::setOutputFormat(
    const DPTX_OUTPUT_FORMAT &fmt,
    int32_t flags)
{
    Mutex::Autolock l(mLock);

    OutputFormat format;
    DP_HIDL_OUTPUT_FORMAT_ASSIGN(format,fmt);

    int32_t rst = cast(getDPTxControl())->getService()->setOutputFormat(format,flags);
    return rst;
}

status_t
DPTxLib::getEDIDSupportList()
{
    Mutex::Autolock l(mLock);

    mEDIDSupportList.clear();

    int32_t rst = 0;
    EDIDSupportList lst;
    hardware::Return<void> ret;
    ret = cast(getDPTxControl())->getService()->getEDIDSupportList([&rst, &lst](
                int32_t result, EDIDSupportList list){
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
            DPTxFormatSupport item = lst.mList[i];
#if (DEBUG_DPTX_LIB)
            ALOGD("VIC:%2d[%20s]",
                item.vic,
                _getVICString((HDMI_VIC_ENUM) item.vic));
#endif

            mEDIDSupportList.add(
                DPTX_FORMAT_SUPPORT(item.vic)
            );

        }
        return OK;
    }else{
        return INVALID_OPERATION;
    }
}

int32_t
DPTxLib::hasDPTxBackend()
{
    Mutex::Autolock l(mLock);
    int32_t rst = cast(getDPTxControl())->getService()->hasDPTxBackend();
    return rst;
}

status_t
DPTxLib::getCurrentOutputFormat(DPTX_OUTPUT_FORMAT *pRst)
{
    Mutex::Autolock l(mLock);
    int32_t rst = 0;

    OutputFormat data;
    hardware::Return<void> ret;

    ret = cast(getDPTxControl())->getService()->getCurrentOutputFormat([&rst,&data](
            int32_t result, OutputFormat fmt){
                rst = result;
                data = fmt;
            });

    if(!ret.isOk()) {
        ALOGE("%s Error",__FUNCTION__);
        return DEAD_OBJECT;
    }

    if(rst) {
        DP_HIDL_OUTPUT_FORMAT_ASSIGN_PT(pRst,data);
        return OK;
    } else {
        return INVALID_OPERATION;
    }
}

}; // namespace realtek
