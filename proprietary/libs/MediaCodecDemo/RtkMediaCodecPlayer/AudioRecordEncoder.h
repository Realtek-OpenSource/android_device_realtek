/*
 * Copyright (c) 2016 Realtek Semiconductor Corp.
 */

#ifndef _AUDIO_RECORD_ENCODER_H_
#define _AUDIO_RECORD_ENCODER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <media/AudioTrack.h>
#include <media/AudioRecord.h>
#include "RtkMediaCodecPlayerCommon.h"
#include "BaseEncoder.h"

namespace android {

struct MediaCodec;
struct RtkMediaMuxer;

class AudioRecordEncoder : public BaseEncoder
{
public:
    AudioRecordEncoder();

    status_t setAudioSource(int audioSource, String16 &clientName);
    status_t setMuxer(const sp<RtkMediaMuxer> &muxer);
    status_t configure(const AV_FORMAT *config);
    status_t prepare();
    status_t start();
    status_t stop();
    status_t setPlayback(int renderAudio);
    status_t setRecord(int encodeAudio);
    status_t reset();

protected:
    virtual ~AudioRecordEncoder();
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

    enum {
        kWhatSetAudioSource,
        kWhatConfigure,
        kWhatPrepare,
        kWhatSetMuxer,
        kWhatSetPlayback,
        kWhatSetEncode,
        kWhatStart,
        kWhatStop,
        kWhatReset,
    };

    enum {
        kMaxBufferSize = 2048,
    };

    State mState;

    bool mRenderAudio;
    bool mRecordAudio;

    sp<AudioTrack> mAudioTrack;
    sp<AudioRecord> mAudioRecord;
    List< sp<ABuffer> > mAudioQueue;
    List< sp<ABuffer> > mBufferList;
    Mutex mAQueLock, mALisLock;
    Mutex mLock;
    Condition mTranscodeWaitCondition;
    int32_t mChannelCount;
    int32_t mSampleRate;
    int32_t mAudioSource;
    String16 mClientName;

    sp<MediaCodec> encoder;
    sp<RtkMediaMuxer> mMuxer;
    sp<ALooper> mEncoderLooper;
    sp<ALooper> mEncodeCBLooper;
    sp<EncodeCBHandler> mEncodeCBHandler;
    ssize_t mAudioTrackIndex;
    int64_t mStartTimeUs;

    status_t startAudioRender();
    status_t stopAudioRender();
    status_t onSetPlayback(int renderAudio);
    status_t onSetRecord(int encodeAudio);
    status_t onStart();
    status_t onStop();
    status_t onPrepare();
    status_t setupAudioEncoder();
    status_t releaseEncoder();
    static void AudioRecordCallback(int event, void *user, void *info);
    void AudioRecordDataCb(AudioRecord::Buffer *info);

    static void AudioTrackCallback(int event, void *user, void *info);
    void AudioTrackDataCb(AudioTrack::Buffer *info);

    virtual void handleEncoderInputBuffer(size_t index);
    virtual void handleEncoderOutputBuffer(size_t index, size_t offset, 
                                           size_t size, int64_t timeUs, int32_t flags);
    virtual void handleEncoderOutputFormatChange(const sp<AMessage> &format);
    virtual void handleEncoderError(status_t err, int32_t actionCode, const char *detail);
    
    DISALLOW_EVIL_CONSTRUCTORS(AudioRecordEncoder);
};

} // namespace android

#endif // _AUDIO_RECORD_ENCODER_H_
