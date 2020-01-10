/*
 * Copyright (c) 2016 Realtek Semiconductor Corp.
 */

#ifndef _AUDIO_DECODER_H_
#define _AUDIO_DECODER_H_

#include "BaseDecoder.h"

namespace android {

struct NuMediaExtractor;
struct MediaCodec;
class AudioTrack;
class FileSource;

class AudioDecoder : public BaseDecoder
{
public:
    AudioDecoder();

    status_t setDataSource(const char *path);
    status_t setDataSource(int32_t fileId, int64_t offset, int64_t length);
    status_t prepare();
    status_t start(int64_t curTime);
    status_t stop();
    status_t reset();
    status_t setFreeRun(int32_t enable);
    void setTunneledPlayback(int32_t audioSessionId) {mAudioSessionId = audioSessionId;}

    static const int64_t TIME_THRESHOLD = 30000;//us
    static constexpr float HEADER_V2_SIZE_BYTES = 20.0f;

protected:
    virtual void onMessageReceived(const sp<AMessage> &msg);
    
private:
    enum {
        kWhatSetDataSourceByPath,
        kWhatSetDataSourceByFileHandle,
        kWhatSetFreeRun,
        kWhatPrepare,
        kWhatStart,
        kWhatStop,
        kWhatReset,
    };

    enum State {
        UNINITIALIZED,
        UNPREPARED,
        PREPARED,
        STARTED,
        STOPPED,
    };

    bool mFreeRun;
    bool mReachToEos;

    sp<NuMediaExtractor> mExtractor;
    sp<FileSource> mDataSource;
    sp<MediaCodec> mMediaCodec;
    sp<ALooper> mCodecLooper;
    sp<AudioTrack> mAudioTrack;
    sp<AMessage> mCallback;
    sp<ALooper> mDecodeCBLooper;
    sp<DecodeCBHandler> mDecodeCBHandler;

    AString mComponentName;
    int64_t mStartTimeUs;
    int32_t mAudioSessionId;
    State mState;
    Mutex mLock;
    Condition mDecodeWaitCondition;

    status_t onPrepare();
    status_t onStart();
    status_t onReset();
    status_t onStop();

    virtual void handleDecoderInputBuffer(size_t index);
    virtual void handleDecoderOutputBuffer(size_t index, size_t offset, 
                                           size_t size, int64_t timeUs, int32_t flags);
    virtual void handleDecoderOutputFormatChange(const sp<AMessage> &format);
	virtual void handleDecoderError(status_t err, int32_t actionCode, const char *detail);

    DISALLOW_EVIL_CONSTRUCTORS(AudioDecoder);

}; //AudioDecoder end

} //namespace android

#endif  // _AUDIO_DECODER_H_
