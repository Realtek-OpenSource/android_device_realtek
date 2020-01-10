/*
 * Copyright (c) 2016 Realtek Semiconductor Corp.
 */

#ifndef _AUDIO_TRANSCODER_H_
#define _AUDIO_TRANSCODER_H_

#include "BaseDecoder.h"
#include "BaseEncoder.h"
#include "RtkMediaCodecPlayerCommon.h"

namespace android {

struct NuMediaExtractor;
struct MediaCodec;
struct RtkMediaMuxer;
class FileSource;
class DecodeCBHandler;
class EncodeCBHandler;

class AudioTranscoder : public BaseDecoder, public BaseEncoder
{
public:
    AudioTranscoder();

    status_t setDataSource(const char *path);
    status_t setDataSource(int32_t fileId, int64_t offset, int64_t length);
    status_t setMuxer(const sp<RtkMediaMuxer> &muxer);
    status_t setTargetFormat(const AV_FORMAT &config);
    status_t setStreamOutput(bool enable);
    status_t prepare();
    status_t start();
    status_t stop();
    status_t reset();
    void setVideoTimeUs(int64_t timeUs) { mCurVideoTimeUs = timeUs; }

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

    List<sp<ABuffer> > mBufferList;
    Mutex mBufferLock;
    Mutex mLock;
    Condition mTranscodeWaitCondition;

    AString mDComponentName;
    AString mEComponentName;
    AV_FORMAT* mTargetFormat;
    int64_t mCurVideoTimeUs;
    ssize_t mAudioTrackIndex;
    bool mFirstFrame;
    bool mStreamOutput;
    bool mStopping;
    int64_t mFirstFrameTime;
    State mState;

    status_t onPrepare();
    status_t onStart();
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

    DISALLOW_EVIL_CONSTRUCTORS(AudioTranscoder);

}; //AudioTranscoder end

} //namespace android

#endif //_AUDIO_TRANSCODER_H_
