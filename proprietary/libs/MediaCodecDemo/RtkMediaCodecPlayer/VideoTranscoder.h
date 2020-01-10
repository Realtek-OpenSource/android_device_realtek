/*
 * Copyright (c) 2016 Realtek Semiconductor Corp.
 */

#ifndef _VIDEO_TRANSCODER_H_
#define _VIDEO_TRANSCODER_H_

#include "BaseDecoder.h"
#include "BaseEncoder.h"

namespace android {

struct NuMediaExtractor;
struct MediaCodec;
struct RtkMediaMuxer;
class FileSource;
class DecodeCBHandler;
class EncodeCBHandler;

class VideoTranscoder : public BaseDecoder, public BaseEncoder
{
public:
    VideoTranscoder();

    status_t setDataSource(const char *path);
    status_t setDataSource(int32_t fileId, int64_t offset, int64_t length);
    status_t setMuxer(const sp<RtkMediaMuxer> &muxer);
    status_t setTargetFormat(const AV_FORMAT &config);
    status_t setStreamOutput(bool enable);
    status_t prepare();
    status_t setCalculateFPS(double val);
    status_t start();
    status_t stop();
    status_t reset();
    int64_t getVideoTimeUs() { return curVideoTimeUs; }

protected:
    virtual void onMessageReceived(const sp<AMessage> &msg);

private:
    enum {
        kWhatSetDataSourceByPath,
        kWhatSetDataSourceByFileHandle,
        kWhatPrepare,
        kWhatStart,
        kWhatStop,
        kWhatReset,
        kWhatSetMuxer,
        kWhatSetTargetFormat,
        kWhatSetCalculateFPS,
    };

    enum State {
        UNINITIALIZED,
        WAIT_MUXER,
        WAIT_TARGET_FORMAT,
        UNPREPARED,
        PREPARED,
        STOPPED,
        STARTED
    };

    sp<NuMediaExtractor> mExtractor;
    sp<MediaCodec> decoder;
    sp<MediaCodec> encoder;
    sp<RtkMediaMuxer> mMuxer;
    sp<FileSource> mDataSource;
    sp<ALooper> mDecoderLooper;
    sp<ALooper> mEncoderLooper;
    sp<ALooper> mDecodeCBLooper;
    sp<ALooper> mEncodeCBLooper;
    sp<DecodeCBHandler> mDecodeCBHandler;
    sp<EncodeCBHandler> mEncodeCBHandler;
    sp<IGraphicBufferProducer> mBufferProducer;
    AString mDComponentName;
    AString mEComponentName;
    sp<Surface> mSurface;

    AV_FORMAT* mTargetFormat;
    int64_t mStartTimeUs;
    int64_t mEndTimeUs;
    int64_t mInstantStartDecodeUs;
    int64_t mInstantEndDecodeUs;
    int64_t mInstantStartEncodeUs;
    int64_t mInstantEndEncodeUs;
    int64_t mDecodeframeCount;
    int64_t mEncodeframeCount;
    int64_t mInstantDecodeframeCount;
    int64_t mInstantEncodeframeCount;
    double mCalculateFPS;
    int64_t curVideoTimeUs;
    ssize_t mVideoTrackIndex;   
    bool mFirstFrame;
    bool mStreamOutput;
    bool mStopping;
    int64_t mFirstFrameTime;
    State mState;
    Mutex mLock;
    Condition mTranscodeWaitCondition;

    status_t onPrepare();
    status_t onStart();
    status_t onStartDecoder();
    status_t onStartEncoder();
    status_t onReset();
    status_t onStop();
    void signalEOS();
    virtual void handleDecoderInputBuffer(size_t index);
    virtual void handleDecoderOutputBuffer(size_t index, size_t offset, 
                                           size_t size, int64_t timeUs, int32_t flags);
    virtual void handleDecoderOutputFormatChange(const sp<AMessage> &format);
    virtual void handleDecoderError(status_t err, int32_t actionCode, const char *detail);

    virtual void handleEncoderInputBuffer(size_t index);
    virtual void handleEncoderOutputBuffer(size_t index, size_t offset, 
                                           size_t size, int64_t timeUs, int32_t flags);
    virtual void handleEncoderOutputFormatChange(const sp<AMessage> &format); 
    virtual void handleEncoderError(status_t err, int32_t actionCode, const char *detail);

    DISALLOW_EVIL_CONSTRUCTORS(VideoTranscoder);	

}; //VideoTranscoder end

} //namespace android

#endif //_VIDEO_TRANSCODER_H_
