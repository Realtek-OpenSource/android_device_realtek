/*
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 */
#ifndef __VIDEOUTILSERVICE_H__
#define __VIDEOUTILSERVICE_H__

#include "IVideoUtil.h"

namespace android {

    class VideoUtilService : public BnVideoUtil {
        public:
            static void instantiate();

            VideoUtilService();
            virtual ~VideoUtilService();

            virtual int setRescaleMode(int videoPlane, int rescaleMode);
            virtual int setFormat3d(int format3d, float fps);
            virtual int setShiftOffset3d(bool exchange_eyeview, bool shift_direction, int delta_offset, int targetPlane);
            virtual int set3Dto2D(int srcformat3d);
            virtual int set3DSub(int sub);
            virtual int applyVoutDisplayWindowSetup(int r, int g, int b, bool isRGB);
            virtual int configureDisplayWindow(int plane, int x, int y, int w, int h); 
            virtual int configureDisplayWindowZoomWin(int plane, int x, int y, int w, int h, int zx, int zy, int zw, int zh); 
            virtual int configureDisplayWindowDispZoomWin(int plane, int x, int y, int w, int h, int zx, int zy, int zw, int zh); 
            virtual int zoom(int plane, int x, int y, int w, int h);
            virtual int setDisplayRatio(int ratio);
            virtual int setDisplayPosition(int x, int y, int w, int h);
            virtual int getHWCV1Rect(int *x, int *y, int *w, int *h);
            virtual int setEnhancedSDR(int flag);
            virtual bool isHDRTv(void);
            virtual bool isCVBSOn(void);
            virtual int setCVBSOff(int off);
            virtual int setPeakLuminance(int flag);
            virtual int setHdrSaturation(int flag);
            virtual int queryDisplayWin(int plane, unsigned char *out, int outSize);
            virtual int showVideoWindow(int instanceId, int plane);
            virtual int hideVideoWindow(int instanceId, int plane);
            virtual int setTvResolution(int videoSystem, int videoStandard);
            virtual int applyVideoStandardSetup(unsigned char *config, int configSize, unsigned char *nandConfig, int nandSize, bool bUpdateVideo, int vSystem, bool bCheck);
            virtual int configureZOrder(unsigned char *config, int configSize);
    };

} // namespace android

#endif //__VIDEOUTILSERVICE_H__

