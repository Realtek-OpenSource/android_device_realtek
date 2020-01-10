#ifndef _HDCP_CALLBACK_H_
#define _HDCP_CALLBACK_H_

#include <utils/Errors.h>
#include "HdmiConstDef.h"

namespace hdmi_hidl {

typedef struct _HDCP_EVENT {
    int32_t mVersion;
    int32_t mEvent;
} HDCP_EVENT;

class HDCPCallback {

public:
    virtual ~HDCPCallback();
    virtual void queueHDCPEvent(HDCP_EVENT event) = 0;
    //virtual void onHDCPEvent(int32_t version, int32_t event)=0;
    //virtual void onHDCPEventLock(int32_t version, int32_t event)=0;
    virtual void hdcpGetCurrentOutputFormat(HDMI_OUTPUT_FORMAT *pFmt)=0;
};

};

#endif // _HDCP_CALLBACK_H_
