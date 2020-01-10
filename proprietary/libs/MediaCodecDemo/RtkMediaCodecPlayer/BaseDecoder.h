/*
 * Copyright (c) 2016 Realtek Semiconductor Corp.
 */
 
#ifndef _BASE_DECODER_H_
#define _BASE_DECODER_H_

#include "RtkBase.h"

namespace android {

struct BaseDecoder : virtual public RtkBase
{
public:
    BaseDecoder();
    ~BaseDecoder();

    class DecodeCBHandler : public AHandler
    {
    public:
        DecodeCBHandler(sp<BaseDecoder> decoder);
    protected:
        ~DecodeCBHandler();
        virtual void onMessageReceived(const sp<AMessage> &msg);
    private:
        wp<BaseDecoder> mDecoder;
    };

private:
    friend class DecodeCBHandler;

    virtual void handleDecoderInputBuffer(size_t index) = 0;
    virtual void handleDecoderOutputBuffer(size_t index, size_t offset,
                                           size_t size, int64_t timeUs, int32_t flags) = 0;
    virtual void handleDecoderOutputFormatChange(const sp<AMessage> &format) = 0;
    virtual void handleDecoderError(status_t err, int32_t actionCode, const char *detail) = 0;

    DISALLOW_EVIL_CONSTRUCTORS(BaseDecoder);
};

} // namespace android

#endif // _BASE_DECODER_H_
