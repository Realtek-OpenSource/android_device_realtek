/*
 * Copyright (c) 2016 Realtek Semiconductor Corp.
 */

#ifndef _CAMERA_RECODER_H_
#define _CAMERA_RECODER_H_

#include <MetadataBufferType.h>
#include <media/stagefright/foundation/Mutexed.h>
#include <camera/CameraParameters.h>
#include "RtkMediaCodecPlayerCommon.h"
#include "BaseEncoder.h"

namespace android {

namespace hardware {
    class ICamera;
}
class Camera;
class CameraSource;
struct MediaCodec;
struct RtkMediaMuxer;

class CameraRecorder : public BaseEncoder
{
public:
    CameraRecorder();

    status_t setDataSource(int32_t cameraType, int32_t cameraId, String16 &clientName);
    status_t setDataSource(int32_t cameraType, const sp<::android::hardware::ICamera> &camera, String16 &clientName);
    status_t setSurface(sp<Surface> &surface);
    status_t setMuxer(const sp<RtkMediaMuxer> &);
    status_t configure(AV_FORMAT &config);
    status_t prepare();
    status_t setPlayback(int32_t flag);
    status_t setRecord(int32_t flag);
    status_t start();
    status_t stop();
    status_t reset();

    enum {
        kWhatGetSnapshot = 0x1000,
        kWhatGetCameraParam
    };
    int64_t mStartTimeUs;

protected:
    virtual void onMessageReceived(const sp<AMessage> &msg);

private:
    struct Puller;

    enum {
        kWhatPullerNotify,
        kWhatSetCameraSource,
        kWhatSetCameraSource2,
        kWhatSetSurface,
        kWhatSetMuxer,
        kWhatConfigure,
        kWhatConfigurePreview,
        kWhatPrepare,
        kWhatSetPlayback,
        kWhatSetRecord,
        kWhatStart,
        kWhatStop,
        kWhatReset,
    };

    enum State {
        UNINITIALIZED,
        WAIT_SURFACE,
        WAIT_MUXER,
        WAIT_PREVIEW_PARAMS,
        INITIALIZED,
        CONFIGURED,
        PREPARED,
        STARTED,
        STOPPED,
    };
    struct StopProcess {
        StopProcess();
        bool mEncoderReachedEOS;
        bool mStopping;
        Condition mCond;
    };
    Mutexed<StopProcess> mStopProcess;
    Mutex mLock;
    Condition mTranscodeWaitCondition;
    int mCameraId;
    int mSrcHdmiRx;
    int mSrcReady;
    int mSrcProgressive;
    int mSrcColor;
    int mSrcWidth;
    int mSrcHeight;
    int mSrcFps;
    int mPreviewWidth;
    int mPreviewHeight;
    int mPreviewFps;

    bool mHdmiRx;	        // source is HDMI-Rx
    bool mPreviewCamera;	// camera preview
    bool mRecordCamera;	    // camera record
    bool mSetEncoderFormat;
    int32_t mEncoderFormat;
    int32_t mEncoderDataSpace;
    String16 mClientName;
    uid_t mClientUid;
    pid_t mClientPid;
    CameraParameters mParameters;

    sp<Camera> mCamera;
    sp<CameraSource> mCameraSource;
    sp<Surface> mSurface;
    sp<Puller> mPuller;
    sp<MediaCodec> mEncoder;
    sp<RtkMediaMuxer> mMuxer;
    sp<ALooper> mEncoderLooper;
    sp<ALooper> mEncodeCBLooper;
    sp<EncodeCBHandler> mEncodeCBHandler;

    ssize_t mVideoTrackIndex;
    AV_FORMAT *mTargetFormat;
    MetadataBufferType mMetaDataStoredInVideoBuffers;
    State mState;

    status_t configureCamera();
    status_t onStart();
    status_t onStop();
    status_t onReset();
    status_t onSetPlayback(int previewCamera);
    status_t setupVideoEncoder();
    status_t setupCameraSource();
    void releaseEncoder();
    void releaseCameraSource();
    void signalEOS();
    status_t onSetRecord(int encodeCamera);
    status_t retrieveHdmiRxVideoInfo();

    virtual void handleEncoderInputBuffer(size_t index);
    virtual void handleEncoderOutputBuffer(size_t index, size_t offset,
                                           size_t size, int64_t timeUs, int32_t flags);
    virtual void handleEncoderOutputFormatChange(const sp<AMessage> &format);
    virtual void handleEncoderError(status_t err, int32_t actionCode, const char *detail);

    DISALLOW_EVIL_CONSTRUCTORS(CameraRecorder);
};

} // namespace android

#endif // _CAMERA_RECODER_H_
