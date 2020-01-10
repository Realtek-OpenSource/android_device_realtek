#ifndef __RVSD_VDEC_ACODEC_H__
#define __RVSD_VDEC_ACODEC_H__

//#include <media/IMediaPlayerService.h>
#ifdef ANDROID
//#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
/*
#include <media/stagefright/foundation/hexdump.h>
#include <media/stagefright/foundation/ABuffer.h>
#include <media/stagefright/foundation/ADebug.h>
#include <media/stagefright/foundation/ALooper.h>
#include <media/stagefright/foundation/AMessage.h>

#ifndef ANDROID_6
#include <media/stagefright/NativeWindowWrapper.h>
#endif

#include <media/stagefright/MPEG2TSWriter.h>
#include <media/stagefright/MPEG4Writer.h>

#include <private/media/VideoFrame.h>

//#include <gui/SurfaceTextureClient.h>
#include <gui/Surface.h>
#include <gui/SurfaceComposerClient.h>
#include <gui/ISurfaceComposer.h>
#include <ui/DisplayInfo.h>
*/
#else
#include "foundation/include/hexdump.h"
#include "foundation/include/ABuffer.h"
#include "foundation/include/ADebug.h"
#include "foundation/include/ALooper.h"
#include "foundation/include/AMessage.h"
#endif
/*
#include <media/stagefright/ACodec.h>
#include <media/stagefright/AudioPlayer.h>
#include <media/stagefright/DataSource.h>
#include <media/stagefright/MediaDefs.h>
#include <media/stagefright/MediaErrors.h>
#include <media/stagefright/MediaExtractor.h>
#include <media/stagefright/MediaSource.h>
#include <media/stagefright/MetaData.h>
#include <media/stagefright/OMXClient.h>
#include <media/mediametadataretriever.h>

#include <media/stagefright/MediaBufferGroup.h>
*/
//#ifdef ENABLE_ENCODE
//#include "RtkTranscodeCommon.h"
//#endif

#include <utils/RefBase.h>
#include "rvsd_vdec.h"
#include "rvsd_InBandAPI.h"
#include "pthread-macro.h"
#include "rvsd_OSAL.h"
#include "rvsd_ringbuffer.h"
#include "rvsd_dbg.h"
#include "rpc_common.h"
//#include "rvsd_VDecVPU.h"

#ifdef RVSD_ENABLE_DOLBY_CONTROL_PATH
#include "RtkControlPath.h"
#endif




class RVSD_INFO;

namespace android {

void *VDec_ACodec_decode_pthread(void *data);
void *VDec_ACodec_vo_pthread(void *data);


//for HDR VP9.2
typedef struct RVSD_VP9_HDR_INFO
{
    uint32_t    is_vp92;
    uint32_t    matrix_coefficients;
    uint32_t    transferCharacteristics;
    //BT. 2020  (x 50000)
    uint32_t    display_primaries_x0;
    uint32_t    display_primaries_x1;
    uint32_t    display_primaries_x2;
    uint32_t    display_primaries_y0;
    uint32_t    display_primaries_y1;
    uint32_t    display_primaries_y2;
    uint32_t    white_point_x;
    uint32_t    white_point_y;
    uint32_t    min_display_mastering_luminance;
    uint32_t    max_display_mastering_luminance;
}RVSD_VP9_HDR_INFO;


class VDecACodec : public RefBase {
public:
    VDecACodec(RVSD_INFO* pRvsd_info, pthread_t *pThreadVideo);
    int VDecInit(void);
    void VDecUninit(void);
    void UnInit(void);
    void *VDec_decode_loop(void);
    void *VDec_showVO_loop(void);
    void GetVideoInfo(long *Data, int size);
    int GetVideoErrorRate();
     bool IsBehindMasterPts(long long pts, long long *pMasterPts);
    void *GetVpuDecHandle();
     virtual ~VDecACodec();

private:
    int VDecCreateVideoDecoder(void);
    void VDecDestroyVideoDecoder(void);
    int VDecHandleDecInitSequenceError(int apiErrorCode);
    void VDecSetDecConfig(void);
    int VDecSeqInit(unsigned int);
    int VDecWaitDecodeDone(unsigned int);
     int VDecStartDecode(void);
    int VDecGetInitialInfo(void);
    int VDecDisplayFrame(bool lock);
    void VDecCheckDecodeComplete(void);  
    void VDecProcessInBand_NewSeg(unsigned int pPrivInfoId, unsigned char *pPrivInfoData);
 

    int GetSkipFrmMode();
    VP_PICTURE_MODE_t GetOutputPicMode(void* pinfo);
    void FlushHandler();
    long long CalculatePTS();
    void DropDisplayFrame(int frmIdx);
    int  DropAndWaitDispIFrm(int frmIdx);
    void RemoveItemFromDispQueue(unsigned int dltIdx, unsigned int* wptr, unsigned char* queue, int qsize, int element_size);

#if _DBG_DUMP_FRAME_BUFFER_EN
    void _dbg_dump_frame_buffer(void *p_handle, void *p_dispFrame, void *p_rcDisplay, int mapType);
    void _dbg_dump_frame_buffer_ex(void *p_info, unsigned int dump_amount);
#endif
    
    void FillYUVData(YUV_STATE* yuv_win, void* pdisplayInfo, void* pdisplayInfoR, long long outTimestamp, long long RPTS, long long outTimestamp2, long long RPTS2, int mode, AspectRatioStruct *ar, char IsReSendFrm, const void *p_dolby_register);
    void SendOneFrameToVO(YUV_STATE* yuv_win, void* pdisplayInfo, void* pdisplayInfoR, long long outTimestamp, long long RPTS, char IsReSendFrm, const void *p_dolby_register);
    void UpdateFrameQueueInfo(int curIdx, DVD_VR_CCI cci, DVD_VR_DCI dci, long long derivedPts=-1);
    int SetAspectRatioInfo(AspectRatioStruct *ar, int pic_width, int pic_height);  
    void VDecSetErrConcealment(); 
    void SendEOSToVO();
    void VDecSetPropagationLevel();
    int CalculateFrameQualityLevel(int curIdx, int curPicType);
    void CalculateErrorRate(int curIdx); 
    int CheckToFreeSequenceChangeBuffer(int checkPLock);
    int GetErrorCntDown();
    unsigned int GetHeaderFrameRate();
     int VDecScanPLockBufferClearRtkFlag(int *pNumLock=NULL, int *pNumQpend=NULL, int *pNumClrDispFlag=NULL, int *pNumSeqChangeVoLock=NULL);
    int VDecGetDispQNum(int *pNumHoldByfq, int *pNumHoldByVo, int *pNumVoLock=NULL, int *pNumVoQpend=NULL, int *pNumClrDispFlag=NULL);
    bool VDecPrepareChangingSequence(void);
    bool VDecVP9InterResChange(void);
    int VDecIonAllocateFb(int ionfd, ion_user_handle_t *ionHandle, unsigned int *phyAddr, unsigned char *virtAddress, unsigned int *size, bool bScpuAcc); 

#ifdef RVSD_NEW_VIDEO_FLOW_EN
     int VDecScanInBandCmd();
    int VDecUpdateBSWritePtr(void *pStreamBuf);
    int VDecScanICQAndUpdateBS();
    void FlushShareICQ();
    int readdata();
    int FillStreamInputBuf(unsigned int nStreamLen, int64_t curTimestamp);
#endif

    void CheckDropFrmBeforeStartPTS();   // PHOENIX-18
    unsigned int GetUnavailableFbCount(int *pNumHoldByDec, int *pNumHoldByfq, int *pNumHoldByVo, int *pNumVoLock=NULL, int *pNumVoQpend=NULL, int *pNumClrDispFlag=NULL);
    bool IsNoAvailableDPB(int *pNumHoldByDec, int *pNumHoldByfq, int *pNumHoldByVo, int *pNumVoLock=NULL, int *pNumVoQpend=NULL, int *pNumClrDispFlag=NULL);
    void GetLumaChromaOffsetTableAddr(int myIndex, int width, int height, unsigned int *pLumaOffTblAddr, unsigned int *pChromeOffTblAddr);
    int AllocateRegisterDecFrameBufferForHEVC();

    int SetScaleMode(unsigned int origin_width, unsigned int origin_height);
    unsigned int CalculateScaleSize(unsigned int origin_size, unsigned int scale_size) const;

 
    bool IsActualDecodedFrame(bool bUpdateStats=false);

    long ComputeFrameRateTick() const;
    void GetBuffer(RINGBUFFER_HEADER **pp_header, unsigned char **pp_base, int *p_size);
 
 
    int GetPpuIndex();
    void ReleasePpu(int vpu_index);
    void HoldPpu(int ppu_index);
    void CheckContinuousFrmNotification(int dispIdx);
    void seqChangeFreeMostIon();
 
    bool IsHasFrame() const;
 
    void PopDispQueue();
    void PeekDispQueue(void *info);    // DecOutputInfo *info 

    void* GenerateDolbyRegisters(const void *p_bl_display_info, const void *p_el_display_info);
    void GetHdrFromInfoframe(YUV_STATE *p_yuv);     
    void GetHdrFromInfoframe_DV(YUV_STATE *p_yuv); 

    int LoadVDecFw(int core_index);
    void ReduceFractionTerms (int *s1, int *s2);
    int64_t GetLocalPTS(REFCLOCK_t* m_pRefClock);
    void GetMastership(REFCLOCK_t* m_pRefClock, MASTERSHIP *mastership);
    int IsMaster(int mode, int masterState);
    unsigned int vdi_get_realchip_memory_size(unsigned long coreIdx);
    void rvsd_close(RVSD_INFO* pRvsdInfo);
    void ParseSuperframeIndex(const unsigned char* data, unsigned int data_sz,
                          const unsigned char* buf, unsigned int buf_sz,
                          unsigned int sizes[8], int* count);
    unsigned char PrivateAreaReadByte(const unsigned char *p);
#if _DBG_DUMP_BS_EN
    void _dbg_dump_bs_new(void *Ptr1, int nStreamLen);
#endif
    void ShowIonMediaHeap();
    enum {
        kWhatVideoNotify                = 'vidr',
    };

    enum {
        AVCFORMAT_AVC,
        AVCFORMAT_MVC
    };

    enum {
        MPEG4FORMAT_MPEG4 = 0,
        MPEG4FORMAT_DIVX5,
        MPEG4FORMAT_XVID,
        MPEG4FORMAT_DIVX4 = 5,
        MPEG4FORMAT_SORENSON = 256
    };

    enum {
        VDEC_OK = 0,
        VDEC_NEED_MORE,
        VDEC_HAS_FRAME,
        VDEC_HAS_INFO,
        VDEC_EOS,
        VDEC_DECODE,
        VDEC_BUFFER_EMPTY,
        VDEC_NOT_HAS_RESOURCE,
        VDEC_FAIL = -1,
        VDEC_NOT_SUPPORT = -2
    };

    enum
    {
        I_FRAME_SEARCH_OFF = 0,
        IDR_FRM_SEARCH_MODE = 1,
        I_FRM_SEARCH_MODE = 2
    };

    enum
    {
        SKIP_FRM_OFF = 0,
        SKIP_EXCEPT_IDR_FRM = 1,
        SKIP_NON_REF_FRM = 2
    };

    enum
    {
        VDEC_EOS_NONE,
        VDEC_EOS_END_OF_SEGMENT,    // inband EOS event ID = -1 , no need to notify system
        VDEC_EOS_END_OF_STREAM,     // inband EOS event ID != -1, need to notify system
        VDEC_SEQ_END,               // inband SEQ_END
        VDEC_EOV                    // VIDEO_DEC_INBAND_CMD_TYPE_VOBU
    };

    enum
    {
        PTS_UNINIT = 0, //initial state,
        PTS_DEC_SYNC = 1,//got pts info at dec stage.
        PTS_DISP_SYNC = 2//got pts info at display stage.
    };

    enum
    {
        PRESEND_I_FRM_OFF  = 0,//reset state,
        PRESEND_I_FRM_WAIT = 1,//wait to send first I frm to VO
        PRESEND_I_FRM_SENT = 2//first I frm has passed to VO, wait for disp idx = 1st I frm idx.
    };

    enum
    {
        MVC_VIEWIDX_NONE = -1,
        MVC_VIEWIDX_LEFT = 0,
        MVC_VIEWIDX_RIGHT = 1
    };

    enum
    {
        LAYOUT_1GB = 0,
        LAYOUT_512MB,
        LAYOUT_256MB
    };

    enum
    {
        SCAN_ICQ_STAT_NONE,
        SCAN_ICQ_STAT_PTSQ_FULL,
        SCAN_ICQ_STAT_CNTXTQ_FULL,
        SCAN_ICQ_STAT_VOBUQ_FULL,
        SCAN_ICQ_STAT_EOS,
        SCAN_ICQ_STAT_VOBU_END,
        SCAN_ICQ_STAT_MBIT
    };

#ifndef RVSD_NEW_VIDEO_FLOW_EN
    sp<MediaSource> mVideoSource;
#endif

    void *pVpuDec;//pointer to VPU info
    void *mp_splitter;
    void *mp_metadata_parser; // point to DolbyMetadataParser
    void *mp_hdr_parser; // point to HdrParameterParser

    RVSD_INFO *pRvsdInfo;
    bool mbFirstFrame;

    bool m_is_base_decoder;

    unsigned long mSeHandle;
    int mIonFd;

    //int mem_fd;
    unsigned char* disp_base_ptr;
    pthread_t pThreadVO;
    pthread_cond_t rvsd_vo_cond;
    pthread_mutex_t rvsd_vo_mtx;
    pthread_mutex_t rvsd_get_icq_mtx;  
    bool bVOUninit;

    int lastDispIndex;
    pthread_mutex_t rvsd_scan_plock_mtx;
    pthread_mutex_t rvsd_plock_mtx;
    pthread_mutex_t rvsd_dispQ_mtx;
    unsigned int nPLockBufferSet; // for sequence change

    pthread_mutex_t rvsd_reorderOutputPts_mtx;

    pthread_t m_dolby_parser_thread;
    bool m_is_stop_metadata_parser;

    unsigned int m_support_vtype;

    static const int m_bl_to_el_size = 62;
    int m_bl_to_el_display[m_bl_to_el_size];
#ifdef RVSD_ENABLE_DOLBY_CONTROL_PATH
    void *mp_dolby_vo_register_allocator;
    rtk_dv_vo_register *mp_dolby_vo_register;

    rtk_hdr_10_infoframe_t m_hdr_info_frame;
    bool m_is_hdr_infoframe;
#endif	 
 
    int superframe_nframes;
    int superframe_frame_cnt;
    unsigned int superframe_sizes[8];

#if _DBG_PRINT_VPU_STATUS_EN
    void PrintVpuStatus(uint32_t coreIdx, uint32_t productId);
#endif

 

    void VDecGetBitStreamBuffer(void* pVpuDec);

    bool bNotHasResource;
public: 
    void DVLOG(int lineNum, const char *format, ...);
    void DVLOG_SEC(int lineNum, int sec, long long *pPrePTS, const char *format, ...);
};

}  // namespace android


#endif
