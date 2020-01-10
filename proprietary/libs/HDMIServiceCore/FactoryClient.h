#ifndef _FACTORY_CLIENT_H_
#define _FACTORY_CLIENT_H_

#include <utils/Mutex.h>
#include <vendor/realtek/factoryutil/1.0/IFactoryUtil.h>

using ::android::hardware::Return;
using ::android::hardware::Void;
using ::vendor::realtek::factoryutil::V1_0::IFactoryUtil;

using namespace android;

namespace realtek {

struct FactoryClient :
    virtual public hardware::hidl_death_recipient
{
    FactoryClient();
    ~FactoryClient();

    sp<IFactoryUtil>    mInterface = nullptr;
    Mutex               mLock;

    virtual void serviceDied(uint64_t cookie,
                        const wp<hidl::base::V1_0::IBase>& who) override;

    IFactoryUtil *  getService();

    int32_t         factory_load();
    int32_t         factory_save();
};

};

#endif
