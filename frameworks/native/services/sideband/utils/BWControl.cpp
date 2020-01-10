#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cutils/properties.h>
#include "BWControl.h"
#include <utils/Log.h>

#define PROPERTY_BW_CONTROL_DISABLE "rtk.sb.gpu.ctrl.disable"

#if defined(__LINARO_SDK__)
class BWControl_GPU : public BWControl {
public:
    BWControl_GPU()
    {
        mDisable = getDisableByProperty();
        mLowPower = false;
    };
    virtual ~BWControl_GPU() {
        if (mLowPower)
            HighPriority();
    };

    virtual bool getDisableByProperty(void) {
        bool ret = true;
        char value[PROPERTY_VALUE_MAX];
        char *p;
        p = getenv("rtk_omx_gpu_ctrl_enable");
        if(p != NULL) {
            strcpy(value, p);
            if ((!strcmp("1", (char *)value)) || !strcmp("true", (char *)value))
                ret = false;
        }
        return ret;
    };

    virtual void LowPriority(void)   {
        if (mDisable)
            return;
        if (mLowPower)
            return;
        system("echo 1 > /sys/kernel/debug/mali/pp/num_cores_enabled");
        system("echo 500000000 > /sys/class/devfreq/981d0000.gpu/min_freq");
        system("echo 500000000 > /sys/class/devfreq/981d0000.gpu/max_freq");

        printf("[BWControl] Enable LowPower\n");
        mLowPower = true;
    };
    virtual void HighPriority(void)  {
        if (mDisable)
            return;
        if (!mLowPower)
            return;

        system("echo 4 > /sys/kernel/debug/mali/pp/num_cores_enabled");
        system("echo 500000000 > /sys/class/devfreq/981d0000.gpu/min_freq");
        system("echo 750000000 > /sys/class/devfreq/981d0000.gpu/max_freq");

        printf("[BWControl] Disable LowPower\n");

        mLowPower = false;
    };
private:
    bool                mDisable;
    bool                mLowPower;
};

#elif defined(ANDROID)
#include <rtk_power/power.h>
#ifdef RTK_POWER_SERVICE_VERSION
#include <android/hardware/power/1.0/IPower.h>
using ::android::hardware::power::V1_0::IPower;
using ::android::hardware::power::V1_0::Feature;
using ::android::hardware::power::V1_0::PowerHint;
using ::android::hardware::power::V1_0::PowerStatePlatformSleepState;
using ::android::hardware::power::V1_0::Status;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::sp;

class BWControl_GPU : public BWControl {
public:
    BWControl_GPU()
    {
        mDisable = getDisableByProperty();
        mLowPower = false;
        if (!mDisable) {
            mPower = android::hardware::power::V1_0::IPower::getService();
        }
    };
    virtual ~BWControl_GPU()
    {
        if (mPower.get())
            mPower.clear();
    };
    virtual bool getDisableByProperty(void) {
        unsigned char value[PROPERTY_VALUE_MAX];
        if (property_get(PROPERTY_BW_CONTROL_DISABLE, (char *)value, "0")
                && (!strcmp("1", (char *)value) || !strcmp("true", (char *)value)))
            return true;
        return false;
    };
    virtual void LowPriority(void)   {
        if (mDisable)
            return;
        if (mLowPower)
            return;
        POWER_DEVICE_OPERATE operate;

        power_device_operate_prepare_data(operate, DEVICE_GPU, SET_CORES_ENABLE, 1);
        mPower->powerHint((PowerHint) RTK_POWER_HINT_DEVICE_OPERATE, operate.data);
        power_device_operate_prepare_data(operate, DEVICE_GPU, SET_MAX_FREQ, 500);
        mPower->powerHint((PowerHint) RTK_POWER_HINT_DEVICE_OPERATE, operate.data);
        power_device_operate_prepare_data(operate, DEVICE_GPU, SET_MIN_FREQ, 500);
        mPower->powerHint((PowerHint) RTK_POWER_HINT_DEVICE_OPERATE, operate.data);
        power_device_operate_prepare_data(operate, DEVICE_GPU, SPECIAL_CASE_0, NULL);
        mPower->powerHint((PowerHint) RTK_POWER_HINT_DEVICE_OPERATE, operate.data);
        mLowPower = true;
    };
    virtual void HighPriority(void)  {
        if (mDisable)
            return;
        if (!mLowPower)
            return;
        POWER_DEVICE_OPERATE operate;
        power_device_operate_prepare_data(operate, DEVICE_GPU, SET_FULL_CORES_ENABLE, NULL);
        mPower->powerHint((PowerHint) RTK_POWER_HINT_DEVICE_OPERATE, operate.data);
        power_device_operate_prepare_data(operate, DEVICE_GPU, SET_MAX_FREQ, 0);
        mPower->powerHint((PowerHint) RTK_POWER_HINT_DEVICE_OPERATE, operate.data);
        power_device_operate_prepare_data(operate, DEVICE_GPU, SET_MIN_FREQ, 0);
        mPower->powerHint((PowerHint) RTK_POWER_HINT_DEVICE_OPERATE, operate.data);
        power_device_operate_prepare_data(operate, DEVICE_GPU, SPECIAL_CASE_1, NULL);
        mPower->powerHint((PowerHint) RTK_POWER_HINT_DEVICE_OPERATE, operate.data);
        mLowPower = false;
    };

    virtual void setLowPowerMode(void) {
        mLowPower = true;
    }
private:
    bool                mDisable;
    bool                mLowPower;
    sp<IPower> mPower;
};
#else /* else of RTK_POWER_SERVICE_VERSION */
class BWControl_GPU : public BWControl {
public:
    BWControl_GPU()
    {
        mDisable = getDisableByProperty();
        mLowPower = false;
        if (!mDisable) {
            hw_get_module(POWER_HARDWARE_MODULE_ID, (const hw_module_t **)&mPowerModule);
            mPowerModule->init(mPowerModule);
        }
    };
    virtual ~BWControl_GPU() {
        if (mLowPower)
            HighPriority();
    };

    virtual bool getDisableByProperty(void) {
        unsigned char value[PROPERTY_VALUE_MAX];
        if (property_get(PROPERTY_BW_CONTROL_DISABLE, (char *)value, "0")
                && (!strcmp("1", (char *)value) || !strcmp("true", (char *)value)))
            return true;
        return false;
    };

    virtual void LowPriority(void)   {
        if (mDisable)
            return;
        if (mLowPower)
            return;
        POWER_DEVICE_OPERATE operate;
        power_device_operate_prepare_data(&operate, DEVICE_GPU, SET_CORES_ENABLE, 1);
        mPowerModule->powerHint(mPowerModule, (power_hint_t) RTK_POWER_HINT_DEVICE_OPERATE, &operate);
        power_device_operate_prepare_data(&operate, DEVICE_GPU, SET_MAX_FREQ, 500000000);
        mPowerModule->powerHint(mPowerModule, (power_hint_t) RTK_POWER_HINT_DEVICE_OPERATE, &operate);
        power_device_operate_prepare_data(&operate, DEVICE_GPU, SET_MIN_FREQ, 500000000);
        mPowerModule->powerHint(mPowerModule, (power_hint_t) RTK_POWER_HINT_DEVICE_OPERATE, &operate);
        power_device_operate_prepare_data(&operate, DEVICE_GPU, SPECIAL_CASE_0, NULL);
        mPowerModule->powerHint(mPowerModule, (power_hint_t) RTK_POWER_HINT_DEVICE_OPERATE, &operate);
        mLowPower = true;
    };
    virtual void HighPriority(void)  {
        if (mDisable)
            return;
        if (!mLowPower)
            return;
        POWER_DEVICE_OPERATE operate;
        power_device_operate_prepare_data(&operate, DEVICE_GPU, GET_CORES_TOTAL, NULL);
        mPowerModule->powerHint(mPowerModule, (power_hint_t) RTK_POWER_HINT_DEVICE_OPERATE, &operate);
        power_device_operate_prepare_data(&operate, DEVICE_GPU, SET_CORES_ENABLE, operate.data);
        mPowerModule->powerHint(mPowerModule, (power_hint_t) RTK_POWER_HINT_DEVICE_OPERATE, &operate);
        power_device_operate_prepare_data(&operate, DEVICE_GPU, SET_MAX_FREQ, 0);
        mPowerModule->powerHint(mPowerModule, (power_hint_t) RTK_POWER_HINT_DEVICE_OPERATE, &operate);
        power_device_operate_prepare_data(&operate, DEVICE_GPU, SET_MIN_FREQ, 0);
        mPowerModule->powerHint(mPowerModule, (power_hint_t) RTK_POWER_HINT_DEVICE_OPERATE, &operate);
        power_device_operate_prepare_data(&operate, DEVICE_GPU, SPECIAL_CASE_1, NULL);
        mPowerModule->powerHint(mPowerModule, (power_hint_t) RTK_POWER_HINT_DEVICE_OPERATE, &operate);
        mLowPower = false;
    };
private:
    bool                mDisable;
    bool                mLowPower;
    power_module_t     *mPowerModule;
};
#endif /* end of RTK_POWER_SERVICE_VERSION */

#else /* !ANDROID && !__LINARO_SDK__ */
class BWControl_GPU : public BWControl {};
#endif /* end of ANDROID/__LINARO_SDK__ */

BWControl * BWControl_create        (BW_DEVICE device) {
    BWControl * ret = NULL;
    switch (device) {
        case BW_GPU:
            ret = new BWControl_GPU();
            break;
        default:
            ret = new BWControl();
            break;
    }
    return ret;
}

void        BWControl_destroy       (BWControl * instance) {
    delete instance;
}

void        BWControl_LowPriority   (BWControl * instance) {

    return instance->LowPriority();
}

void        BWControl_HighPriority  (BWControl * instance) {
    return instance->HighPriority();
}
