/*
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 */
#ifndef _AUDIO_WRITEBACK_ENCODER_H_
#define _AUDIO_WRITEBACK_ENCODER_H_

#include "RtkMediaCodecPlayerCommon.h"
#include "AudioRPCBaseDS.h"
#include "RPCBaseDS.h"
#include "AudioRPC_Agent.h"
#include "AudioRPC_System.h"
#include "SVCFunc.h"
#include "RPCProxy.h"
#include "hresult.h"
#include "AudioInbandAPI.h"
#include "audio_common.h"
#include "BaseEncoder.h"
#include <OSAL_RTK.h>

typedef enum
{
    ENUM_AUDIO_PCM_FORMAT,                              //0
    ENUM_AUDIO_FRAME_SIZE,
    ENUM_AUDIO_FRAME_BOUNDARY,
    ENUM_AUDIO_DEC_EXT_BS,
    ENUM_AUDIO_DEC_CFG,
    ENUM_AUDIO_CS_DATA,
    ENUM_AUDIO_AI_STATE,
    ENUM_AUDIO_SPDIF_BS_INFO,
    ENUM_AUDIO_DEMUX_BUFFER_INIT,
    ENUM_AUDIO_CHANNEL_INDEX,                           //9
    ENUM_AUDIO_ECHO_INFO,
// add by ny /////////////////////////////////
    ENUM_AUDIO_ENC_CFG,
// add end ///////////////////////////////////
    ENUM_AUDIO_REFRESH_RBUFPTR,
    ENUM_AUDIO_SWITCH_FOCUS,                            //d
    ENUM_AIN_SWITCH_FOCUS,
    ENUM_AUDIO_CHANNEL_SOURCE,      //obsolete
    ENUM_AUDIO_SPDIF_NONPCM_CFG,
    ENUM_AOUT_MUTE_INFO,
    ENUM_AOUT_VOLUME_LEVEL,
    ENUM_AOUT_SPDIF_SOURCE_SELECT,
    ENUM_AOUT_KARAOKE_CONTROL,
    ENUM_AOUT_SPDIF_DIFF,
    ENUM_AUDIO_CHANGE_PP_OUT_SAMPLERATE,
    ENUM_APP_NIGHT_MODE_CFG,  // old version
    ENUM_APP_REINIT_PIN,
    ENUM_AUDIO_BS_ERR,
    ENUM_AUDIO_PTS_TEST,
    ENUM_AOUT_DROP_PTS,
    ENUM_APP_NIGHT_MODE_INFO, // for night mode global var
    ENUM_AUDIO_MPEG_TYPE,
    ENUM_AUDIO_NOISE_INFO,
    ENUM_AUDIO_SOUND_EVENT,
    ENUM_AUDIO_PRIVATE_CGMS_INFO,                       //21
// add by taro for inband /////////////////////////////////
    ENUM_AUDIO_INBAND_EOS_INFO,
    ENUM_AUDIO_INBAND_PTS_INFO,
//    ENUM_AUDIO_INBAND_PRIVATE_INFO,
    ENUM_AUDIO_INBAND_NEWFORMAT_INFO,
// end add by taro for inband /////////////////////////////////
    ENUM_AUDIO_DEC_GET_FORMAT,
// for trans-encoder, add by isometry
    ENUM_AUDIO_TRANSENC_BS_INFO,
    ENUM_AUDIO_TRANSENC_BUFFER_INIT,
    ENUM_AUDIO_TRANSENC_NONPCM_CFG,
    ENUM_AUDIO_SRC_CHANGE,
// end for trans-encoder
// send aac raw out info
    ENUM_AUDIO_AAC_RAW_OUT_INFO,
    ENUM_AUDIO_FLASH_AO,
    ENUM_AUDIO_IN_DATA_MEASURE,
    ENUM_AUDIO_DECODER_NEWFORMAT,
    ENUM_AUDIO_PASSTHROUGH_MODE,
    ENUM_AUDIO_DTS_DOWNMIX,
    ENUM_AUDIO_AAC_DOWNMIX,
    ENUM_AUDIO_KARAOKE_INFO, // for Karaoke mixer, add by Chris
#ifdef AUDIO_RAW_OUT_MORE_BYTES
    ENUM_AUDIO_DECODER_EOS,      // for raw out, decoder inform AO to raw out more 64 bytes.
#endif
    ENUM_AUDIO_GET_FLASH_PINID,
    ENUM_AUDIO_RELEASE_FLASH_PINID,
    ENUM_AUDIO_CONTROL_FLASH_VOLUME,
    ENUM_AUDIO_DEC_SUPPORT_RATE,
#ifdef AUDIO_TV_PLATFORM
    ENUM_AUDIO_SPDIF_OUT_CS_INFO,
    ENUM_AUDIO_DEC_DELAY_RP,
    ENUM_AUDIO_ANALOG_INPUT_CLOCK_INFO,
    ENUM_AIN_ATV_SET_CLOCK,
    ENUM_AIN_INOUT_CH_SELECT,
    ENUM_AIN_SET_FS_CLOCKSRC,
    ENUM_AIN_SET_PATH_DATA_OUT,
    ENUM_AIN_SET_INTERLEAVE_OUT,
#ifdef SUPPORT_GLOBAL_AI
    ENUM_AIN_SET_OUT_FMT,
#endif // SUPPORT_GLOBAL_AI
#endif // AUDIO_TV_PLATFORM
    ENUM_APP_AGC_MODE_CONFIG,
    ENUM_AO_LOW_DELAY_PARAMETERS,
    ENUM_AIN_CONNECT_ALSA
} ENUM_AUDIO_INFO_TYPE;

struct FRAME
{
    unsigned char *bufferAddr;
    unsigned long bufferSize;
    unsigned long frameSize;
    long long timeStamp;
};

typedef struct
{
    ENUM_AUDIO_INFO_TYPE    infoType;
    AUDIO_PCM_FORMAT        pcmFormat;
    long                    start_addr;
    int                     max_bit_rate;
} AUDIO_INFO_PCM_FORMAT;

typedef enum
{
    BS,
    COMMAND
} DELIVER_WHAT;

namespace android {

#define AUDIO_OUTPUT_PIN 2
#define NUMBER_OF_CHANNELS  2
#define MAX_AUDIO_SIZE      8192 //Audio encoder max buffer size is 8192

struct MediaCodec;
struct RtkMediaMuxer;

class AudioWritebackEncoder : public BaseEncoder
{
public:
    AudioWritebackEncoder();

    status_t setAudioSource(int audioSource = 0);
    status_t setMuxer(const sp<RtkMediaMuxer> &muxer);
    status_t configure(const AV_FORMAT *config);
    status_t prepare();
    status_t start(int64_t startTime);
    status_t stop();
    status_t reset();

protected:
    virtual ~AudioWritebackEncoder();
    virtual void onMessageReceived(const sp<AMessage> &msg);

private:
    enum {
        kWhatSetAudioSource = 0x500,
        kWhatSetMuxer,
        kWhatConfigure,
        kWhatPrepare,
        kWhatStart,
        kWhatAudioRead,
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

    enum ReaderState {
        READER_STATE_WAIT,
        READER_STATE_GET_FRAME,
        READER_STATE_EOS,
        READER_STATE_ERROR = -1
    };

    State mState;

    uint32_t mAOAgentId;
    AUDIO_FORMAT mAudioConfig;
    FRAME mAudioFrame;
    AUDIO_INFO_PCM_FORMAT mPCM_Format;

    OSAL_RTKALLOCATOR* mReaderDataBuffer[AUDIO_OUTPUT_PIN];
    OSAL_RTKALLOCATOR* mReaderPtsBuffer;
    unsigned char *mDataLower[AUDIO_OUTPUT_PIN];
    unsigned char *mDataUpper[AUDIO_OUTPUT_PIN];
    unsigned char *mPtsLower;
    unsigned char *mPtsUpper;
    
    /*----Variables are used to record----*/
    sp<MediaCodec> mEncoder;
    sp<RtkMediaMuxer> mMuxer;
    sp<ALooper> mEncoderLooper;
    sp<ALooper> mEncodeCBLooper;
    sp<EncodeCBHandler> mEncodeCBHandler;
	List<sp<ABuffer> > mBufferList;
    ssize_t mAudioTrackIndex;
    int64_t mStartTimeUs;
    Mutex mLock, mALisLock;
    Condition mTranscodeWaitCondition;

    status_t setupAudioEncoder();
    status_t releaseEncoder();
    status_t onStart();
    status_t read();
    void onPrepare();
    void stopRead();
    int32_t getFrame(FRAME *frame);

    virtual void handleEncoderInputBuffer(size_t index);
    virtual void handleEncoderOutputBuffer(size_t index, size_t offset, 
                                           size_t size, int64_t timeUs, int32_t flags);
    virtual void handleEncoderOutputFormatChange(const sp<AMessage> &format); 
    virtual void handleEncoderError(status_t err, int32_t actionCode, const char *detail);

    DISALLOW_EVIL_CONSTRUCTORS(AudioWritebackEncoder);
};

} // namespace android

#endif // _AUDIO_WRITEBACK_ENCODER_H_
