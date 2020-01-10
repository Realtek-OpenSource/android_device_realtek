/*
 * Copyright (c) 2016 Realtek Semiconductor Corp.
 */
 
#ifndef _BASE_ENCODER_H_
#define _BASE_ENCODER_H_

#include "RtkBase.h"

namespace android {

struct BaseEncoder : virtual public RtkBase
{
public:
    BaseEncoder();
    ~BaseEncoder();

    class EncodeCBHandler : public AHandler
    {
    public:
        EncodeCBHandler(sp<BaseEncoder> encoder);
    protected:
        ~EncodeCBHandler();
        virtual void onMessageReceived(const sp<AMessage> &msg);
    private:
        wp<BaseEncoder> mEncoder;
    };

private:
    friend class EncodeCBHandler;

    virtual void handleEncoderInputBuffer(size_t index) = 0;
    virtual void handleEncoderOutputBuffer(size_t index, size_t offset,
                                           size_t size, int64_t timeUs, int32_t flags) = 0;
    virtual void handleEncoderOutputFormatChange(const sp<AMessage> &format) = 0;
    virtual void handleEncoderError(status_t err, int32_t actionCode, const char *detail) = 0;

    DISALLOW_EVIL_CONSTRUCTORS(BaseEncoder);
};

} // namespace android

#endif // _BASE_ENCODER_H_
