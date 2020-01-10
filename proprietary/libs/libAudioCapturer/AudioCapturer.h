/*
 * Copyright (c) 2018 Realtek Semiconductor Corp.
 */

#ifndef _AUDIO_CAPTURER_H_
#define _AUDIO_CAPTURER_H_

#include <log/log.h>
#include <OSAL_RTK.h>

namespace android {

#define KARAOKE_CHANNELS    2
#define NUMBER_OF_CHANNELS  KARAOKE_CHANNELS

#define DEC_BYTE_SWAP(_dst, value) \
    _dst = (long)((value & 0x000000ff) << 24) | (long)(((value & 0x0000ff00) >> 8) << 16) | (long)(((value & 0x00ff0000) >> 16) << 8) | (long)((value & 0xff000000) >> 24);

struct FRAME
{
    unsigned char *bufferAddr;
    unsigned long bufferSize;
    unsigned long frameSize;
    long long timeStamp;
};

class AudioCapturer
{
public:
    AudioCapturer();
    ~AudioCapturer();

    int32_t prepare();
    int32_t flush();
    int32_t startCap(FRAME* frame);
    int32_t stopCap();
    int32_t setDelay(int32_t delay);

private:
    enum CAP_State
    {
        CAP_STATE_WAIT,
        CAP_STATE_GET_FRAME,
        CAP_STATE_EOS,
        CAP_STATE_ERROR = -1
    };

    int32_t mAOAgentId;
    int32_t mChannels;
    unsigned char *mAOcapLower[NUMBER_OF_CHANNELS];
    unsigned char *mAOcapUpper[NUMBER_OF_CHANNELS];
    OSAL_RTKALLOCATOR* mAOcapBuffer[NUMBER_OF_CHANNELS];

};

} // namespace android

#endif // _AUDIO_CAPTURER_H_
