/*
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 */
#ifndef __AUDIOUTILSERVICE_H__
#define __AUDIOUTILSERVICE_H__

#include "IAudioUtil.h"

namespace android {

    class AudioUtilService : public BnAudioUtil {
        public:
            static void instantiate();

            AudioUtilService();
            virtual ~AudioUtilService();

            virtual int setAudioSpdifOutputMode(int mode);
            virtual int SetAudioSpdifOutputOffMode();
            virtual int setAudioHdmiOutputMode(int mode);
            virtual int setAudioAGC(int mode);
            virtual int setAudioForceChannelCtrl(int mode);
            virtual int setAudioSurroundSoundMode(int mode);
            virtual int setAudioHdmiFreqMode(void);
            virtual int setAudioDecVolume(int volume);
            virtual int setAudioMute(bool bMute);
            virtual int setAudioHdmiMute(bool bMute);
            virtual int setAudioHdmiRxVolume(int volume, int aoId, int aiId, int pinId);
            virtual int setHDMIRXtoBTUsb(int flag, int aiId);
    };


} // namespace android

#endif //__AUDIOUTILSERVICE_H__
