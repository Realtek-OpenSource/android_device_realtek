/*
 * Copyright (c) 2016 Realtek Semiconductor Corp.
 */

#ifndef _AUDIO_RX_ENCODER_H_
#define _AUDIO_RX_ENCODER_H_

#include "BaseEncoder.h"
#include "RtkMediaCodecPlayerCommon.h"

#include <hidlmemory/mapping.h>
#include <android/hidl/memory/1.0/IMemory.h>
#include <android/hidl/allocator/1.0/IAllocator.h>
#include <audio_utils/resampler.h>
#include <vendor/realtek/audioutil/1.0/IAudioUtil.h>
#include <vendor/realtek/audioutil/1.0/IAudioUtilCallback.h>

using ::android::hardware::Void;
using ::vendor::realtek::audioutil::V1_0::IAudioUtilCallback;
using ::android::hidl::allocator::V1_0::IAllocator;

namespace android {

struct MediaCodec;
struct RtkMediaMuxer;

typedef struct _RxAudioFrame
{
    uint8_t *bufferAddr;
    int32_t bufferSize;
    int32_t frameSize;
    int64_t timeStamp;
    int32_t channelCount;
    int32_t sampleRate;
} RxAudioFrame;

class AudioRxEncoder : public BaseEncoder
{

    class AudioCallback : virtual public IAudioUtilCallback
    // TODO: better to add hidl_death_recipient
    {
    public:
        AudioCallback(AudioRxEncoder *parent) { mParent = parent; }
        ~AudioCallback(){}
        virtual hardware::Return<void> handleEvent(
                int32_t event) override;

        AudioRxEncoder *mParent;
    };

public:
    AudioRxEncoder();

    enum {
        kWhatDrainAudioBuffer,
        kWhatCaptureAudio,
    };
    
    status_t setAudioSource(int audioSource);
    status_t setMuxer(const sp<RtkMediaMuxer> &muxer);
    status_t configure(const AV_FORMAT *config);
    status_t prepare();
    status_t start(int64_t startTime);
    status_t stop();
    status_t setPlayback(int renderAudio);
    status_t setRecord(int encodeAudio, int64_t startTime);
    status_t reset();    


protected:
    virtual ~AudioRxEncoder();
    virtual void onMessageReceived(const sp<AMessage> &msg);
    
private:
    enum State {
        UNINITIALIZED,
        INITIALIZED,
        CONFIGURED,
        PREPARED,
        STARTED,
        STOPPED,
    };

    State mState;
    sp<::vendor::realtek::audioutil::V1_0::IAudioUtil> mAudioUtil;
    sp<ALooper> mAudioInputReaderLooper;
    Mutex mLock;
    Condition mTranscodeWaitCondition;
    /*----Variables are used to record----*/
    sp<MediaCodec> mEncoder;
    sp<RtkMediaMuxer> mMuxer;
    sp<ALooper> mEncoderLooper;
    sp<ALooper> mEncodeCBLooper;
    sp<EncodeCBHandler> mEncodeCBHandler;
    List<RxAudioFrame> mBufferList;
    int64_t mPrevPTS;

    struct resampler_itfe *mResampler;
    ssize_t mAudioTrackIndex;
    int32_t mChannelCount;
    int32_t mSampleRate;    
    int64_t mStartTimeUs;
    bool mEncodeAudio;

    int32_t mKey;
    sp<AudioCallback> mAudioCallback;

    // global hidl buffer
    hardware::hidl_memory mHidlBuffer;
    uint8_t *             mHidlBufPtr;
    sp<android::hidl::memory::V1_0::IMemory> mHidlMemory;
    /*------------------------------------*/

    status_t configureEncoder();
    status_t releaseEncoder();
    status_t notifyHotplug(int32_t state);
    void resampleAudio(RxAudioFrame &srcAudioFrame, RxAudioFrame &outAudioFrame);
    virtual void handleEncoderInputBuffer(size_t index);
    virtual void handleEncoderOutputBuffer(size_t index, size_t offset, 
                                           size_t size, int64_t timeUs, int32_t flags);
    virtual void handleEncoderOutputFormatChange(const sp<AMessage> &format);    
    virtual void handleEncoderError(status_t err, int32_t actionCode, const char *detail);
    DISALLOW_EVIL_CONSTRUCTORS(AudioRxEncoder);
};

} // namespace android

#endif // _AUDIO_RX_ENCODER_H_
