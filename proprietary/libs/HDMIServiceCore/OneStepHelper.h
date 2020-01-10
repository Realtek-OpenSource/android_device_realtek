#ifndef _ONE_STEP_HELPER_
#define _ONE_STEP_HELPER_

#include <utils/Errors.h>
#include "hdmitx/rtk_hdmi.h"
#include "HdmiCommon.h"

#define ONE_STEP_INFO_HDR_LEN   16

#define SAVE_MODE_RAM           (1)
#define SAVE_MODE_NAND          (2)

using namespace android;

typedef struct _ONE_STEP_INFO {
    uint8_t                     mHeaderFormat[ONE_STEP_INFO_HDR_LEN]; // FMT
    struct hdmi_format_setting  mSetting;
    uint8_t                     mHeaderEDIDCheckSum[ONE_STEP_INFO_HDR_LEN]; // EDID
    uint8_t                     mChecksum[2];
} ONE_STEP_INFO;

class OneStepHelper {

public:
    OneStepHelper();
    ~OneStepHelper();

    status_t        saveOutputFormat(const HDMI_OUTPUT_FORMAT &fmt, int32_t mode);
    status_t        readOutputFormat(HDMI_OUTPUT_FORMAT *pFmt);
    status_t        writeEDIDChecksum(uint8_t d1, uint8_t d2);
    status_t        validateOneStepInfo(ONE_STEP_INFO *pInfo);
    status_t        readEDIDChecksum(uint8_t *d1, uint8_t *d2);

    void            dumpInfo();
    bool            hasRuntimeFormat() { return mHasRuntimeFormat; }
    void            setRuntimeFormat(bool enable) { mHasRuntimeFormat = enable; }

private:
    bool                mHasGPT;
    long                mHeaderFmtOffset;
    long                mFmtOffset;
    long                mHeaderChecksumOffset;
    long                mChecksumOffset;

    bool                mHasRuntimeFormat;
    HDMI_OUTPUT_FORMAT  mRuntimeFormat;

    status_t        readOneStepInfo(ONE_STEP_INFO *pInfo);
    void            dumpOneStepInfo(ONE_STEP_INFO *pInfo);

    // legacy mode
    void            saveOutputFormatLegacy(const HDMI_OUTPUT_FORMAT &fmt);
    status_t        readOutputFormatLegacy(HDMI_OUTPUT_FORMAT *pFmt);
    status_t        writeEDIDChecksumLegacy(uint8_t d1, uint8_t d2);
    status_t        readEDIDChecksumLegacy(uint8_t *d1, uint8_t *d2);

};

#endif
