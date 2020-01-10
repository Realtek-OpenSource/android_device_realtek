/*
 * Copyright (c) 2016 Realtek Semiconductor Corp.
 */
 
#ifndef _VIDEO_DECODER_H_
#define _VIDEO_DECODER_H_

#include "BaseDecoder.h"

namespace android {
	
struct NuMediaExtractor;
struct MediaCodec;
class Surface;
class FileSource;

class VideoDecoder : public BaseDecoder
{
public:
    VideoDecoder();

    status_t setDataSource(const char *path);
    status_t setDataSource(int32_t fileId, int64_t offset, int64_t length);
    status_t setSurface(const sp<Surface> &surface);
    status_t prepare();
    status_t start();
    status_t stop();
    status_t reset();
    status_t setFreeRun(int32_t enable);
    status_t setCalculateFPS(double time);
    void setTunneledPlayback(int32_t audioSessionId) {mAudioSessionId = audioSessionId;}

    static const int64_t TIME_THRESHOLD = 30000; //us 
    int64_t mStartTimeUs;

protected:
    virtual void onMessageReceived(const sp<AMessage> &msg);

private:
    enum {
        kWhatSetDataSourceByPath,
        kWhatSetDataSourceByFileHandle,
        kWhatSetSurface,
        kWhatPrepare,
        kWhatStart,
        kWhatStop,
        kWhatReset,
        kWhatSetFreeRun,
        kWhatSetCalculateFPS
    };

    enum State {
        UNINITIALIZED,
        WAIT_SURFACE,
        UNPREPARED,
        PREPARED,
        STOPPED,
        STARTED
    };

    bool mCodecErr;
    bool mFreeRun;
    bool mReachToEos;
    double mCalculateFPS;
    int32_t mAudioSessionId;
    int64_t mEndTimeUs;
    int64_t mInstantStartDecodeUs;
    int64_t mInstantEndDecodeUs;
    int64_t mDecodeframeCount;
    int64_t mInstantDecodeframeCount;

    sp<NuMediaExtractor> mExtractor;
    sp<FileSource> mDataSource;
    sp<MediaCodec> mMediaCodec;
    sp<ALooper> mCodecLooper;
    sp<AMessage> mCallback;
    sp<Surface> mSurface;
    sp<ALooper> mDecodeCBLooper;
    sp<DecodeCBHandler> mDecodeCBHandler;

    AString mComponentName;
    State mState;
    Mutex mLock;
    Condition mDecodeWaitCondition;

    status_t onPrepare();
    status_t onStart();
    status_t onReset();
    status_t onStop();
    inline void calculateFps();
    void handleCodecEOS();
    virtual void handleDecoderInputBuffer(size_t index);
    virtual void handleDecoderOutputBuffer(size_t index, size_t offset, 
                                           size_t size, int64_t timeUs, int32_t flags);
    virtual void handleDecoderOutputFormatChange(const sp<AMessage> &format);
    virtual void handleDecoderError(status_t err, int32_t actionCode, const char *detail);

    DISALLOW_EVIL_CONSTRUCTORS(VideoDecoder);
	
}; //VideoDecoder end

} //namespace android

#endif // _VIDEO_DECODER_H_