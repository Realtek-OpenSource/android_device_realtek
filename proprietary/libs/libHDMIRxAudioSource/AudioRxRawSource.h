/*
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 */

#ifndef _AUDIO_RX_RAW_SOURCE_H_
#define _AUDIO_RX_RAW_SOURCE_H_

#include <utils/Log.h>
#include <utils/Timers.h>
#include <OSAL_RTK.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <AudioRxSource.h>
#include "AudioRPCBaseDS.h"
#include "RPCBaseDS.h"
#include "AudioRPC_Agent.h"
#include "AudioRPC_System.h"
#include "SVCFunc.h"
#include "RPCProxy.h"
#include "hresult.h"
#include "AudioInbandAPI.h"
#include "audio_common.h"

#ifdef ENABLE_HDMIRX_MULTICHN
#define AIN_CHANNEL_NUM     8
#else
#define AIN_CHANNEL_NUM     2
#endif

#define DEC_CHANNEL_NUM     8
#define DEC_INBAND_SIZE     (512)
#define RINGBUFFER_SIZE     (64 * 1024)
#define NON_PCM_BUF_SIZE    (64 * 1024)
#define RING_SAMPLE_SIZE    (64 * 1024)
#define RING_BYTE_SIZE      (RING_SAMPLE_SIZE << 2)
#define AUDIO_OUTPUT_PIN     2

typedef enum {
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

typedef struct {
    ENUM_AUDIO_INFO_TYPE    infoType;
    AUDIO_PCM_FORMAT        pcmFormat;
    long                    start_addr;
    int                     max_bit_rate;
} AUDIO_INFO_PCM_FORMAT;

typedef struct {
    ENUM_AUDIO_INFO_TYPE    infoType;
    char channel_index[8];
    long start_addr;
    char dual_mono_flag;
} AUDIO_INFO_CHANNEL_INDEX;

typedef enum {
    BS,
    COMMAND
} DELIVER_WHAT;

class AudioRxRawSource : public AudioRxSource
{
public:
    AudioRxRawSource();
    virtual ~AudioRxRawSource();

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
    enum ReaderState {
        READER_STATE_WAIT,
        READER_STATE_GET_FRAME,
        READER_STATE_EOS,
        READER_STATE_ERROR = -1
    };
    bool mRenderAudio;
    bool mRecordAudio;

    long mAudioInId;
    long mAudioDecId;
    long mAudioPpId;
    long mAudioOutId;
    long mPpPinId;      //PP pin id
    long mAoutPinId;    //AO flash pin id

    struct hdmirx_infoframe_packet mAudioInfoFrame;

    int mIonFd;
    ion_user_handle_t mRefClkHdl;

    HDMIRxAudioInfo mHDMIRxAudioInfo;

    OSAL_RTKALLOCATOR *mCaptureAllocator;
    OSAL_RTKALLOCATOR *mAIInAllocator[AIN_CHANNEL_NUM];
    OSAL_RTKALLOCATOR *mDecInAllocator;
    OSAL_RTKALLOCATOR *mDecIcqAllocator;
    OSAL_RTKALLOCATOR *mDecOutAllocator[DEC_CHANNEL_NUM];

    AudioFormat mAudioConfig;
    AUDIO_INFO_PCM_FORMAT mPCM_Format;

    OSAL_RTKALLOCATOR* mReaderDataBuffer[AUDIO_OUTPUT_PIN];
    unsigned char *mDataLower[AUDIO_OUTPUT_PIN];
    unsigned char *mDataUpper[AUDIO_OUTPUT_PIN];

    OSAL_RTKALLOCATOR* mReaderPtsBuffer;
    unsigned char *mPtsLower;
    unsigned char *mPtsUpper;

    // for accessing hw 90k
    int32_t rbus_fd;
    char*   rbus_mmap_base;

    void initPtsAndReaderBuffer();
    void stopRead();
    int32_t getFrame(RxAudioFrame &frame);

    nsecs_t convertPTS(uint64_t pcmPTS);

    int getPPPinId(long *pppPinId);
    int initRAWRingBuffer();
    int uninitRAWRingBuffer();
    int configRAWInput(long audioInId);
    int initRefClock();
    int switchPpFocus(long instanceId, long pinId);
    int enableAudioInput();
    int disableAudioInput();
    int releasePPPinId(long instanceId, long pinId);
    int uninitRefClock();
};

#endif // _AUDIO_RX_RAW_SOURCE_H_
