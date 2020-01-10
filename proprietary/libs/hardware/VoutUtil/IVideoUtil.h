/*
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 */
#ifndef __IVIDEOUTIL_H__
#define __IVIDEOUTIL_H__

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>

namespace android {

// wrapper to use VideoUtil binder interface
int SetRescaleMode(int videoPlane, int rescaleMode);
int SetFormat3d(int format3d, float fps);
int SetShiftOffset3d(bool exchange_eyeview, bool shift_direction, int delta_offset, int targetPlane);
int Set3Dto2D(int srcformat3d);
int Set3DSub(int sub);
int ApplyVoutDisplayWindowSetup(int r, int g, int b, bool isRGB);
int ConfigureDisplayWindow(int plane, int x, int y, int w, int h); 
int ConfigureDisplayWindowZoomWin(int plane, int x, int y, int w, int h, int zx, int zy, int zw, int zh); 
int ConfigureDisplayWindowDispZoomWin(int plane, int x, int y, int w, int h, int zx, int zy, int zw, int zh); 
int Zoom(int plane, int x, int y, int w, int h);
int SetDisplayRatio(int ratio);
int SetDisplayPosition(int x, int y, int w, int h);
int GetHWCV1Rect(int *x, int *y, int *w, int *h);
int SetEnhancedSDR(int flag);
bool IsHDRTv(void);
bool IsCVBSOn(void);
int SetCVBSOff(int off);
int SetPeakLuminance(int flag);
int SetHdrSaturation(int flag);
int QueryDisplayWin(int plane, unsigned char *out, int outSize);
int ShowVideoWindow(int instanceId, int plane);
int HideVideoWindow(int instanceId, int plane);
int SetTvResolution(int videoSystem, int videoStandard);
int ApplyVideoStandardSetup(unsigned char *config, int configSize, unsigned char *nandConfig, int nandSize, bool bUpdateVideo, int vSystem, bool bCheck);
int ConfigureZOrder(unsigned char *config, int configSize);


class IVideoUtil: public IInterface
{
    public:
        DECLARE_META_INTERFACE(VideoUtil);
        virtual int setRescaleMode(int videoPlane, int rescaleMode) = 0;
        virtual int setFormat3d(int format3d, float fps) = 0;
        virtual int setShiftOffset3d(bool exchange_eyeview, bool shift_direction, int delta_offset, int targetPlane) = 0;
        virtual int set3Dto2D(int srcformat3d) = 0;
        virtual int set3DSub(int sub) = 0;
        virtual int applyVoutDisplayWindowSetup(int r, int g, int b, bool isRGB) = 0;
        virtual int configureDisplayWindow(int plane, int x, int y, int w, int h) = 0; 
        virtual int configureDisplayWindowZoomWin(int plane, int x, int y, int w, int h, int zx, int zy, int zw, int zh) = 0; 
        virtual int configureDisplayWindowDispZoomWin(int plane, int x, int y, int w, int h, int zx, int zy, int zw, int zh) = 0; 
        virtual int zoom(int plane, int x, int y, int w, int h) = 0;
        virtual int setDisplayRatio(int ratio) = 0;
        virtual int setDisplayPosition(int x, int y, int w, int h) = 0;
        virtual int getHWCV1Rect(int *x, int *y, int *w, int *h) = 0;
        virtual int setEnhancedSDR(int flag) = 0;
        virtual bool isHDRTv(void) = 0;
        virtual bool isCVBSOn(void) = 0;
        virtual int setCVBSOff(int off) = 0;
        virtual int setPeakLuminance(int flag) = 0;
        virtual int setHdrSaturation(int flag) = 0;
        virtual int queryDisplayWin(int plane, unsigned char *out, int outSize) = 0;
        virtual int showVideoWindow(int instanceId, int plane) = 0;
        virtual int hideVideoWindow(int instanceId, int plane) = 0;
        virtual int setTvResolution(int videoSystem, int videoStandard) = 0;
        virtual int applyVideoStandardSetup(unsigned char *config, int configSize, unsigned char *nandConfig, int nandSize, bool bUpdateVideo, int vSystem, bool bCheck) = 0;
        virtual int configureZOrder(unsigned char *config, int configSize) = 0;
};

/* --- Server side --- */

class BnVideoUtil: public BnInterface<IVideoUtil>
{
    public:
        virtual status_t    onTransact( uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags = 0);
};

}; // namespace android

#endif //__IVIDEOUTIL_H__
