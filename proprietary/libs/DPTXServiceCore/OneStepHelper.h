#ifndef _ONE_STEP_HELPER_
#define _ONE_STEP_HELPER_

#include <utils/Errors.h>
#include "rtk_dptx.h"
#include "DPTxConstDef.h"

#define ONE_STEP_INFO_HDR_LEN   16

#define SAVE_MODE_RAM           (1)
#define SAVE_MODE_NAND          (2)

using namespace android;

typedef struct _ONE_STEP_INFO {
    uint8_t                     mHeaderFormat[ONE_STEP_INFO_HDR_LEN]; // FMT
    struct dptx_format_setting  mSetting;
    uint8_t                     mHeaderEDIDCheckSum[ONE_STEP_INFO_HDR_LEN]; // EDID
    uint8_t                     mChecksum[2];
} ONE_STEP_INFO;

class OneStepHelper {

public:
    OneStepHelper();
    ~OneStepHelper();

    status_t        saveOutputFormat(const DPTX_OUTPUT_FORMAT &fmt);
    status_t        readOutputFormat(DPTX_OUTPUT_FORMAT *pFmt);
    status_t        writeEDIDChecksum(uint8_t d1, uint8_t d2);
    status_t        validateOneStepInfo(ONE_STEP_INFO *pInfo);
    status_t        readEDIDChecksum(uint8_t *d1, uint8_t *d2);

    void            dumpInfo();

private:
    bool            mHasGPT;
    long            mHeaderFmtOffset;
    long            mFmtOffset;
    long            mHeaderChecksumOffset;
    long            mChecksumOffset;

    status_t        readOneStepInfo(ONE_STEP_INFO *pInfo);
    void            dumpOneStepInfo(ONE_STEP_INFO *pInfo);

    // legacy mode
    void            saveOutputFormatLegacy(const DPTX_OUTPUT_FORMAT &fmt);
    status_t        readOutputFormatLegacy(DPTX_OUTPUT_FORMAT *pFmt);
    status_t        writeEDIDChecksumLegacy(uint8_t d1, uint8_t d2);
    status_t        readEDIDChecksumLegacy(uint8_t *d1, uint8_t *d2);

};

#endif
