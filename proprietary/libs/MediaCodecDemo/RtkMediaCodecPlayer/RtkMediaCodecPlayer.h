/*
 * Copyright (c) 2016 Realtek Semiconductor Corp.
 */

#ifndef _RTK_MEDIACODEC_PLAYER_H_
#define _RTK_MEDIACODEC_PLAYER_H_

#define BUFFER_LEN  4096

namespace android {

class AudioDecoder;
class VideoDecoder;
class AudioTranscoder;
class VideoTranscoder;
class CameraRecorder;
class AudioInputSource;
class AudioRxEncoder;
class AudioRecordEncoder;
class FileSource;
class Surface;
namespace hardware {
    class ICamera;
}
class IGraphicBufferProducer;
#if 0 // disable screen record
class VideoWritebackEncoder;
class AudioWritebackEncoder;
#endif
struct RtkBase;
struct RtkMediaMuxer;

typedef void(*STATUS_CALLBACK)(sp<AMessage> &msg);

// workround for android 9.0
enum {
    OUTPUT_FILE = 0,
    OUTPUT_STDOUT = 1,
    OUTPUT_ASHMEM = 2,
    OUTPUT_ASHMEM_RTP = 3,
    OUTPUT_UDP = 4,
    OUTPUT_UDP_RTP = 5,
    OUTPUT_UDP_ASHMEM = 6,  //OUTPUT_RTP_BOTH
    OUTPUT_FD = 7,
    OUTPUT_MAX
};

class RtkMediaCodecPlayer : public AHandler
{
public:
    RtkMediaCodecPlayer(bool createLooper = false, int32_t onlyTrack = 0);

    status_t initiate(int transcodeType = SourceTypeFile, bool playback = false, bool transcode = false);
    status_t setDataSource(const char *path);
    status_t setDataSource(int32_t fileId, int64_t offset, int64_t length);
    status_t setCameraSource(int cameraId, String16 &clientName);
    status_t setCameraSource(const sp<::android::hardware::ICamera> &camera);
    status_t setWritebackSource(int wbType);
    status_t setAudioSource(int audioSource);
    status_t setSurface(const sp<IGraphicBufferProducer> &bufferProducer);
    status_t setMuxer(RtkTranscodeConfig &conf);    
    status_t setTargetFormat(const AV_FORMAT &config); //Transcode or Preview parameters
    status_t setOutputFormat(RtkTranscodeConfig &conf); //Output Format/Type
    status_t setPlayback(bool video, bool audio);
    status_t setTranscode(bool transcode);
    /* This function must be called before calling prepare,otherwise, it can't take effect. */
    status_t setTunneledPlayback(bool tunnel);
    status_t setFreeRun(bool enable);
    status_t setCalculateFPS(double time);
    status_t prepare();
    status_t start();
    status_t stop();
    void cleanup();
    bool EOSReached();
    bool getTranscodeEnabled() { return mTranscode; };
    status_t getCameraSnapshot(CAMERA_SNAPSHOT_PARA *snapshot);
    String8 getCameraParameters();

    void registerStatusHandler(sp<AHandler> id) { mStatusId = id; };
    void registerStatusCallback(STATUS_CALLBACK callback) { mStatusCb = callback; };

    // TODO: review me later, not sure if it cause memory leak.
    sp<IMemory> mBuffer;

    enum {
        /* Decoder or Encoder --> Player */
        kWhatDecodeGotEOS = 0x130,
        kWhatStopTranscode,
        kWhatTrackReady,
        kWhatHDMIRxVideoHotplug,
    };

protected:
    virtual ~RtkMediaCodecPlayer();
    virtual void onMessageReceived(const sp<AMessage> &msg);

private:
    enum {
        kWhatInitiate,
        kWhatSetDataSourceByPath,
        kWhatSetDataSourceByFileHandle,
        kWhatSetCameraSource,
        kWhatSetCameraSource2,
        kWhatSetAudioSource,
        kWhatSetPlayback,
        kWhatSetTranscode,
        kWhatSetTunneledPlayback,
        kWhatSetFreeRun,
        kWhatSetCalculateFPS,
        kWhatPrepare,
        kWhatStart,
        kWhatSetMuxer,
        kWhatSetTargetFormat,
        kWhatSetSurface,
        kWhatStop,
    };

    enum State {
        UNINITIALIZED,
        INITIALIZED,
        WAIT_AUDIO_SOURCE,
        WAIT_SURFACE,
        WAIT_MUXER,
        WAIT_TARGET_FORMAT,
        WAIT_PREVIEW_PARAMS,
        UNPREPARED,
        PREPARED,
        STARTED,
        STOPPING,
        STOPPED,
    };

    State mState;
    bool mHasPlayerLooper;
    sp<ALooper> mPlayerLooper;
    sp<AHandler> mStatusId;
    STATUS_CALLBACK mStatusCb;
    Mutex mLock;
    Condition mWaitCondition;

    int32_t mTranscodeType;
    int32_t mOutFormat;
    int32_t mTranscode;
    int32_t mPlayback;
    int32_t mOnlyTrack;
    int32_t mAudioSessionId;

    bool mRenderVideo;
    bool mRenderAudio;
    bool mEOSReached;
    bool mEOSVideoReached;
    bool mEOSAudioReached;
    bool mNoVideoTrack;
    bool mNoAudioTrack;
    bool mVideoTranscodeDone;
    bool mAudioTranscodeDone;
    bool mMuxerDone;
    bool mVideoTrackReady;
    bool mAudioTrackReady;

    sp<AudioDecoder> mAudioDecoder;
    sp<ALooper> mAudioDecoderLooper;

    sp<VideoDecoder> mVideoDecoder;
    sp<ALooper> mVideoDecoderLooper;

    sp<VideoTranscoder> mVideoTranscoder;
    sp<ALooper> mVideoTranscoderLooper;

    sp<AudioTranscoder> mAudioTranscoder;
    sp<ALooper> mAudioTranscoderLooper;

    sp<CameraRecorder> mCameraRecorder;
    sp<ALooper> mCameraRecorderLooper;

    sp<AudioRxEncoder> mAudioRxEncoder;
    sp<ALooper> mAudioRxEncoderLooper;

    sp<AudioRecordEncoder> mAudioRecordEncoder;
    sp<ALooper> mAudioRecordEncoderLooper;
#if 0 // disable screen record
    sp<VideoWritebackEncoder> mVideoWritebackEncoder;
    sp<AudioWritebackEncoder> mAudioWritebackEncoder;
    sp<ALooper> mVideoWritebackEncoderLooper;
    sp<ALooper> mAudioWritebackEncoderLooper;
#endif
    sp<RtkMediaMuxer> mMediaMuxer;

    AString mInputFile;
    AString mOutputFile;

    sp<FileSource> mDataSource;
    sp<Surface> mSurface;

    sp<::android::hardware::ICamera> mICamera;

    AV_FORMAT mTargetFormat;
    RtkTranscodeConfig mOutputFormat;
    String16 mClientName;
    int32_t mCameraType;
    int32_t mCameraId;
    int32_t mAudioSource;
    int32_t mFileId;
    int64_t mFileOffset;
    int64_t mFileLength;
    int32_t mFileSourceType;

    char mFileName[BUFFER_LEN];
    char mUdpIp[BUFFER_LEN];

    void resetVariables();
    void closeFd();
    void waitTime(int64_t usec);
    status_t onInitiate();
    status_t onSetDataSource();
    status_t onSetCameraSource();
    status_t onSetCameraSource2();
    status_t onSetAudioSource();
    status_t onSetSurface();
    status_t onSetMuxer();
    status_t onSetTargetFormat();
    status_t onSetPlayback(bool video, bool audio);
    status_t onSetTranscode(bool transcode);
    status_t onSetFreeRun(bool enable);
    status_t onSetCalculateFPS(double time);
    status_t onPrepare();
    status_t onStart();
    status_t onStop();
    status_t onReset();
    status_t onStopMuxer();
    
    DISALLOW_EVIL_CONSTRUCTORS(RtkMediaCodecPlayer);
};

} // namespace android

#endif // _RTK_MEDIACODEC_PLAYER_H_
