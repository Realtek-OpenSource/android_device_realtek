/*
 * Copyright (c) 2018 Realtek Semiconductor Corp.
 */

#ifndef _AUDIO_RX_SOURCE_H_
#define _AUDIO_RX_SOURCE_H_

#include <log/log.h>
#include <utils/RefBase.h>

#define HDMIRX_AUDIO_INFO   "/sys/devices/virtual/video4linux/video250/hdmirx_audio_info"
#define DATA_BUFFER_SIZE    (16 * 1024)
#define DATA_BUFFER_NUM     16

#define RX_VOLUME_MUTE      (31)
#define RX_VOLUME_UNMUTE    ( 0)

using namespace android;

typedef struct _HDMIRxAudioInfo {
    bool ready;
    int32_t freq;
    int32_t type;
    int32_t channelCount;
} HDMIRxAudioInfo;

typedef struct _RxAudioFrame
{
    uint8_t* bufferAddr;
    int32_t bufferSize;
    int32_t frameSize;
    int64_t timeStamp;
    int32_t channelCount;
    int32_t sampleRate;
} RxAudioFrame;

typedef struct _AudioFormat {
    int32_t channelCount;		// the number of channels
    int32_t channelMode;        // not used
    int32_t sampleRate;         // sample rate
    int32_t bitrate;            // bit/s
} AudioFormat;

enum {
    CHANNEL_MODE_NONE,
    CHANNEL_MODE_LEFT,
    CHANNEL_MODE_RIGHT,
};

// only for multi-channel support device
typedef struct hdmirx_infoframe_packet {
    unsigned char type;
    unsigned char version;
    unsigned char length;
    unsigned char data_byte[29];
} hdmirx_infoframe_packet_t;

class AudioRxSource : public RefBase
{
public:
    AudioRxSource();
    virtual ~AudioRxSource();

    virtual int setAudioParams(int32_t sampleRate, int32_t channelCount) = 0;
    virtual int prepare() = 0;
    virtual int start() = 0;
    virtual int stop() = 0;
    virtual int setRenderAudio(bool renderAudio) = 0;
    virtual int setRecordAudio(bool recordAudio) = 0;
    virtual int captureAudio(RxAudioFrame &audioFrame) = 0;
    virtual long getAIInstanceId() = 0;
    virtual long getAOInstanceId() = 0;
    virtual long getAOPinIdStatic() = 0;
    virtual struct hdmirx_infoframe_packet *getAudioInfoFrameRecPtr() = 0;
    virtual bool isRenderAudio() = 0;

    virtual int handleRxAudioChanged(int state);
    virtual int setAOVolume(int32_t volume);
protected:
    virtual int createAudioInstance(uint32_t instanceType, long *instanceId);
    virtual int getAOInstance(long *audioOutId);
    virtual int configADC(long audioInId, long sampleRate);
    virtual int runAudioInstance(long instanceId);
    virtual int pauseAudioInstance(long instanceId);
    virtual int startAudioRender(long instanceId);
    virtual int stopAudioInstance(long instanceId);
    virtual int stopAudioRender(long instanceId);
    virtual int destroyAudioInstance(long instanceId);
    virtual int setAIRxSource(long instanceId);
    virtual bool getHDMIRxAudioInfoFrame(struct hdmirx_infoframe_packet *pInfoFrame);
    virtual bool deliverHDMIRxAudioInfoFrame(long instanceId, struct hdmirx_infoframe_packet *pInfoFrame);
    virtual void setAudioInfoFrame(long instanceId);


    virtual int64_t getHW90k(int32_t *pFd, char **pBase);
    virtual int pli_init(int32_t *pFd, char **pBase);
    virtual int pli_close(int32_t *pFd, char **pBase);
    virtual int* getIOAddress(unsigned int addr, int32_t *pFd, char **pBase);

    static void firmware_init();
    static void firmware_uninit();
    static int retrieveHdmiRxAduioInfo(HDMIRxAudioInfo &info);
};

#endif // _AUDIO_RX_SOURCE_H_
