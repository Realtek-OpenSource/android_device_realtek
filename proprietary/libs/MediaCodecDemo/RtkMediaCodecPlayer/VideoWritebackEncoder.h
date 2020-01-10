/*
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 */

#ifndef _VIDEO_WRITEBACK_ENCODER_H_
#define _VIDEO_WRITEBACK_ENCODER_H_

#include <vendor/realtek/screenrecord/1.0/IScreenRecordService.h>
#include "BaseEncoder.h"

#define WB_BUF_NUM 12
//#define DUMP_WB_FRAME

namespace android {

struct MediaCodec;
struct RtkMediaMuxer;

class VideoWritebackEncoder : public BaseEncoder
{
public:
    VideoWritebackEncoder();

    status_t setDataSource(int wbType);
    status_t configure(AV_FORMAT &config);
    status_t setMuxer(const sp<RtkMediaMuxer> &muxer);
    status_t prepare();
    status_t start();
    status_t stop();
    status_t reset();

    int64_t mStartTimeUs;

protected:
    virtual ~VideoWritebackEncoder();
    virtual void onMessageReceived(const sp<AMessage> &msg);

private:
    class CaptureThread : public Thread
    {
    public:
        CaptureThread(const sp<VideoWritebackEncoder> &wb)
                : Thread(false), mVideoWritebackEncoder(wb) {}
            virtual void onFirstRef() {
                run("TranscodeWritebackCaptureThread", PRIORITY_DISPLAY);
            }
            virtual bool threadLoop() {
                sp<VideoWritebackEncoder> encoder = mVideoWritebackEncoder.promote();
                if (encoder.get() != NULL) {
                    encoder->captureThread();
                }
                return true; // loop until we need to quit
            }
    private:
        wp<VideoWritebackEncoder> mVideoWritebackEncoder;
    };

    enum {
        kWhatSetWritebackType = 0x700,
        kWhatConfigure,
        kWhatSetMuxer,
        kWhatPrepare,
        kWhatStart,
        kWhatStop,
        kWhatReset,
    };

    enum State {
        UNINITIALIZED,
        INITIALIZED,
        CONFIGURED,
        PREPARED,
        STARTED,
        STOPPED,
    };

    State mState;
    int mTargetWidth;
    int mTargetHeight;
    int mTargetFps;
    int mSrcFps;
    int mDivide;
    int mWritebackType;
    unsigned int mFrameReceived;
    bool mCaptureStopped;

    sp<::vendor::realtek::screenrecord::V1_0::IScreenRecordService> mRecordService;
    sp<CaptureThread> mCaptureThread;
    sp<MediaCodec> mEncoder;
    sp<RtkMediaMuxer> mMuxer;
    sp<ALooper> mEncoderLooper;
    sp<ALooper> mEncodeCBLooper;
    sp<EncodeCBHandler> mEncodeCBHandler;

    List<int32_t> mBufferList;
    List<int64_t> mTimeUsList;

    ssize_t mVideoTrackIndex;
    AV_FORMAT *mTargetFormat;
    Mutex mLock, mCaptureLock;
    Condition mTranscodeWaitCondition, mCaptureWaitCondition;

    status_t onPrepare();
    status_t onStart();
    status_t onStop();
    status_t setupVideoEncoder();
    status_t releaseEncoder();
    status_t captureThread();
#ifdef DUMP_WB_FRAME
    void dumpWbFrame(void *buf, int cnt);
#endif
    virtual void handleEncoderInputBuffer(size_t index);
    virtual void handleEncoderOutputBuffer(size_t index, size_t offset,
                                           size_t size, int64_t timeUs, int32_t flags);
    virtual void handleEncoderOutputFormatChange(const sp<AMessage> &format);
    virtual void handleEncoderError(status_t err, int32_t actionCode, const char *detail);
    
    DISALLOW_EVIL_CONSTRUCTORS(VideoWritebackEncoder);
};

} // namespace android

#endif // _VIDEO_WRITEBACK_ENCODER_H_
