/*
 * Copyright (c) 2016 Realtek Semiconductor Corp.
 */

#ifndef _RTK_BASE_H_
#define _RTK_BASE_H_

#include <media/stagefright/foundation/AHandler.h>
#include <media/stagefright/foundation/AMessage.h>

namespace android {

struct RtkBase : public AHandler
{
public:
    RtkBase();
    void registerStatusHandler(sp<AHandler> handler) { mStatusId = handler; };
    void registerManagerHandler(sp<AHandler> handler) { mManagerId = handler; };
    void registerSinkHandler(sp<AHandler> handler) { mSinkId = handler; };
    void cleanup();
    void handleError(int32_t err, int32_t what);

    enum {
        kWhatCodecNotify = 0x1612,
        kWhatError,
    };

protected:
    sp<AHandler> mManagerId;
    sp<AHandler> mStatusId;
    sp<AHandler> mSinkId;

private:
    DISALLOW_EVIL_CONSTRUCTORS(RtkBase); 
};

} // namespace android

#endif // _RTK_BASE_H_
