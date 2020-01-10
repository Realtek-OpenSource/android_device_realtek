/*
 * Copyright (c) 2016 Realtek Semiconductor Corp.
 */

#ifndef _HDMI_RX_INFO_H_
#define _HDMI_RX_INFO_H_

namespace android {
    
class HdmiRxInfo {
private:
	HdmiRxInfo();
    
	static HdmiRxInfo* instance;

public:
	static HdmiRxInfo* GetInstance();
    static void DelInstance();
    ~HdmiRxInfo();
    
    int getVideoHdmiRx() const { return mVideoHdmiRx; }
    int getVideoReady() const { return mVideoReady; }
    int getVideoProgressive() const { return mVideoProgressive; }
    int getVideoColor() const { return mVideoColor; }
    int getVideoWidth() const { return mVideoWidth; }
    int getVideoHeight() const { return mVideoHeight; }
    int getVideoFps() const { return mVideoFps; }
    
    int getAudioReady() const { return mAudioReady; }
    int getAudioSampleRate() const { return mAudioSampleRate; }
    int getAudioAudioLPCM() const { return mAudioLPCM; }
    
    enum {
        RGB,
        YUV422,
        YUV444
    };
    
private:
    
    int mVideoHdmiRx;
    int mVideoReady;
    int mVideoProgressive;
    int mVideoColor;
    int mVideoWidth;
    int mVideoHeight;
    int mVideoFps;
    
    int mAudioReady;
    int mAudioSampleRate;
    int mAudioLPCM;
    
    int retrieveHdmiRxVideoInfo();
    int retrieveHdmiRxAduioInfo();
    
};

} // end of namespace

#endif // _HDMI_RX_INFO_H_