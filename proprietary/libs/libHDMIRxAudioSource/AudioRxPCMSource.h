/*
 * Copyright (c) 2018 Realtek Semiconductor Corp.
 */

#ifndef _AUDIO_RX_PCM_SOURCE_H_
#define _AUDIO_RX_PCM_SOURCE_H_

#include <OSAL_RTK.h>
#include <utils/Vector.h>
#include <utils/Timers.h>
#include <AudioInbandAPI.h>
#include <AudioRxSource.h>

#ifdef ENABLE_HDMIRX_MULTICHN
#define AIN_CHANNEL_NUM     8
#else
#define AIN_CHANNEL_NUM     2
#endif

#define DEC_CHANNEL_NUM     8
#define RINGBUFFER_SIZE     (64 * 1024)
#define NON_PCM_BUF_SIZE    (36 * 1024)
#define DEC_INBAND_SIZE     (512)
#define MAX_AUDIO_SIZE      8192 //Audio encoder max buffer size is 8192
#define INSTANCE(inst, pin) (((inst) & 0xFFFFF000)|((pin) & 0xFFF))

#define PTS_CAPTURE_BUF     (16 * 1024)

typedef struct _PTS_RECORD {
    nsecs_t mRefPTS;
    uint32_t mWPStart;
    uint32_t mWPEnd;
    ssize_t mSize;
    uint64_t mIndex;
} PTS_RECORD;

// new added struct for batch mode capture
typedef struct pts_info_2 {
    nsecs_t mRefPTS;
    ssize_t mLen;
    uint8_t mData[PTS_CAPTURE_BUF];
} pts_info_2_t;

class AudioRxPCMSource : public AudioRxSource
{
public:
    AudioRxPCMSource();
    virtual ~AudioRxPCMSource();

    virtual int setAudioParams(int32_t sampleRate, int32_t channelCount);
    virtual int prepare();
    virtual int start();
    virtual int stop();
    virtual int setRenderAudio(bool renderAudio);
    virtual int setRecordAudio(bool recordAudio);
    virtual int captureAudio(RxAudioFrame &audioFrame);
    virtual long getAIInstanceId() { return mAudioInId; }
    virtual long getAOInstanceId() { return mAudioOutId; }
    virtual long getAOPinIdStatic() { return mAoutPinId; }
    virtual struct hdmirx_infoframe_packet *getAudioInfoFrameRecPtr()
    {
        return &mAudioInfoFrame;
    }

    virtual bool isRenderAudio() { return mRenderAudio; }
private:
    struct hdmirx_infoframe_packet mAudioInfoFrame;
    bool mRenderAudio;
    bool mRecordAudio;
    bool mStarted;

    long mAudioInId;
    long mAudioDecId;
    long mAudioPpId;
    long mAudioOutId;
    long mPpPinId;      //PP pin id
    long mAoutPinId;    //AO flash pin id

    int mIonFd;
    ion_user_handle_t mRefClkHdl;

    OSAL_RTKALLOCATOR *mCaptureAllocator;
    OSAL_RTKALLOCATOR *mAIInAllocator[AIN_CHANNEL_NUM];
    OSAL_RTKALLOCATOR *mDecInAllocator;
    OSAL_RTKALLOCATOR *mDecIcqAllocator;
    OSAL_RTKALLOCATOR *mDecOutAllocator[DEC_CHANNEL_NUM];

    // added for pts
    OSAL_RTKALLOCATOR *mPTSAllocator;
    uint32_t mLastWp;
    uint32_t mPCMCapturRingBufpAddr;
    uint32_t mPCMCaptureRingBufSize;
    // for accessing hw 90k
    int32_t rbus_fd;
    char*   rbus_mmap_base;
    HDMIRxAudioInfo mHDMIRxAudioInfo;
    int32_t mChannelCount;
    int32_t mSampleRate;
    int32_t mSampleSize;
    int32_t mPTSAvail;
    uint64_t mCapturePtsIdx;

    int64_t mCaptureStartTimeUs;
    char *mPrevBuf[4096];
    FILE *mFd;
    android::Vector<PTS_RECORD *> mPTSRecQueue;
    bool mPerformanceMode;
    nsecs_t mPrevTimeUs;
    nsecs_t mStartTimeUs;

    int getAOPinId();
    int releaseAOPinId(long instanceId, long pinId);
    int initPCMRingBuffer();
    int uninitPCMRingBuffer();
    int configMaxVolumeForTesting();
    int switchPpFocus(long instanceId, long pinId);
    int configAiCapture();
    int flushCaptureBuffer();

    int startCapturePCM();
    int stopCapturePCM();
    int enableAudioInput();
    int disableAudioInput();
    int setupAudioRedirect();
    int stopAudioRedirect();

    // new API -> get PTS info by myself
    int initPTSRingBuffer();
    int flushPTSBuffer();
    int uninitPTSRingBuffer();
    int capturePTS(AUDIO_DEC_PTS_INFO *pInfo);
    int captureAudioBase(uint32_t reqSize, uint8_t *dstBuf, uint32_t *readSize);
    // batch mode to capture pcm data. faster
    int captureAudioBatch(RxAudioFrame &audioFrame);

    nsecs_t convertPTS(AUDIO_DEC_PTS_INFO *pInfo);
    //int pli_init();
    //int pli_close();
    void clearPTSRecordQueue();
};

#endif // _AUDIO_RX_PCM_SOURCE_H_
