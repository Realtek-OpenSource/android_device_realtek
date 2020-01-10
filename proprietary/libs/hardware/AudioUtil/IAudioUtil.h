/*
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 */
#ifndef __IAUDIOUTIL_H__
#define __IAUDIOUTIL_H__

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>

namespace android {

int SetAudioSpdifOutputMode(int mode);
int SetAudioSpdifOutputOffMode();
int SetAudioHdmiOutputMode(int mode);
int SetAudioAGC(int mode);
int SetAudioForceChannelCtrl(int mode);
int SetAudioSurroundSoundMode(int mode);
int SetAudioHdmiFreqMode(void);
int SetAudioDecVolume(int volume);
int SetAudioMute(bool bMute);
int SetAudioHdmiMute(bool bMute);
int SetAudioHdmiRxVolume(int volume, int aoId, int aiId, int pinId);
int SetHDMIRXtoBTUsb(int flag, int aiId);

class IAudioUtil: public IInterface
{
    public:
        DECLARE_META_INTERFACE(AudioUtil);
        virtual int setAudioSpdifOutputMode(int mode) = 0;
        virtual int setAudioSpdifOutputOffMode() = 0;
        virtual int setAudioHdmiOutputMode(int mode) = 0;
        virtual int setAudioAGC(int mode) = 0;
        virtual int setAudioForceChannelCtrl(int mode) = 0;
        virtual int setAudioSurroundSoundMode(int mode) = 0;
        virtual int setAudioHdmiFreqMode(void) = 0;
        virtual int setAudioDecVolume(int volume) = 0;
        virtual int setAudioMute(bool bMute) = 0;
        virtual int setAudioHdmiMute(bool bMute) = 0;
        virtual int setAudioHdmiRxVolume(int volume, int aoId, int aiId, int pinId) = 0;
        virtual int setHDMIRXtoBTUsb(int flag, int aiId) = 0;
};

/* --- Server side --- */

class BnAudioUtil: public BnInterface<IAudioUtil>
{
    public:
        virtual status_t    onTransact( uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags = 0);
};

}; // namespace android

#endif //__IAUDIOUTIL_H__
