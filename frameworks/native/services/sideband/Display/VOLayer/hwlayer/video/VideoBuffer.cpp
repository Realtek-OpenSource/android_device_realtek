#include "VideoBuffer.h"
#define ATRACE_TAG (ATRACE_TAG_VIDEO)
#include <utils/Trace.h>
#define BSWAP_32(x) (__builtin_bswap32((int32_t)x))
#define BSWAP_64(x) (__builtin_bswap64((int64_t)x))

struct debug_info {
    unsigned int context;
    unsigned int receive_time_H; // 90K
    unsigned int receive_time_L; // 90K
    unsigned int display_time_H; // 90K
    unsigned int display_time_L; // 90K
    unsigned int release_time_H; // 90K
    unsigned int release_time_L; // 90K
    unsigned int drop_cnt;
    unsigned int display_cnt;
    unsigned int reserve[64 - 9];
};

VideoBuffer::VideoBuffer()
    :mFlags(0),
     dm_reg1(NULL),
     dm_reg2(NULL),
     dm_reg3(NULL),
     dv_lut1(NULL),
     dv_lut2(NULL)
{
    mDebugInfo = new IonBuffer(IonBuffer::AllocBuffer, sizeof(struct debug_info));
    resetWin();
}

VideoBuffer::~VideoBuffer()
{
    ALOGI("[%s] %p : (mFlags:0x%x)", __FUNCTION__, this, mFlags);
    if (dm_reg1 != NULL)
	    delete dm_reg1;
    if (dm_reg2 != NULL)
	    delete dm_reg2;
    if (dm_reg3 != NULL)
	    delete dm_reg3;
    if (dv_lut1 != NULL)
        delete dv_lut1;
    if (dv_lut2 != NULL)
        delete dv_lut2;

    dm_reg1 = NULL;
    dm_reg2 = NULL;
    dm_reg3 = NULL;
    dv_lut1 = NULL;
    dv_lut2 = NULL;

    delete mDebugInfo;
#if 0
    if (mFlags & FILLYUV)
        resetWin();

    if (mFlags & QUEUE_BUFFER) {
        int wait = 3;
        while (!releaseBufferCheck() && wait-- && (mFlags & QUEUE_BUFFER))
            usleep(16000);

        if (wait == 0) {
            ALOGE("[%s] releaseBufferCheck wait too long!", __FUNCTION__);
            releaseBuffer_();
        }
    }
#endif
}

void VideoBuffer::removeBuffer() {
    if (mFlags & FILLYUV)
        resetWin();

    if (mFlags & QUEUE_BUFFER) {
        int wait = 3;
        while (BufferBase::releaseBuffer() != 0 && wait-- && (mFlags & QUEUE_BUFFER))
            usleep(16000);

        if (wait == 0) {
            ALOGE("[%s] releaseBufferCheck wait too long!", __FUNCTION__);
            mFlags &= ~QUEUE_BUFFER;
        }
    }

    BufferBase::removeBuffer();
}

void VideoBuffer::initYuvState(struct YUV_STATE * picObj)
{
    memset(picObj, 0, sizeof(*picObj));
    picObj->lumaOffTblAddr          = 0xffffffff;
    picObj->chromaOffTblAddr        = 0xffffffff;
    picObj->lumaOffTblAddrR         = 0xffffffff;
    picObj->chromaOffTblAddrR       = 0xffffffff;
    picObj->bufBitDepth             = 8;
    picObj->bufFormat               = 0;
    picObj->transferCharacteristics = 0;
    picObj->display_primaries_x0    = 0;
    picObj->display_primaries_y0    = 0;
    picObj->display_primaries_x1    = 0;
    picObj->display_primaries_y1    = 0;
    picObj->display_primaries_x2    = 0;
    picObj->display_primaries_y2    = 0;
    picObj->white_point_x           = 0;
    picObj->white_point_y           = 0;
    picObj->min_display_mastering_luminance = 0;
    picObj->max_display_mastering_luminance = 0;
    picObj->pReceived_prev          = 0;
    picObj->Y_addr_next             = 0;
    picObj->U_addr_next             = 0;
    picObj->pLock_prev              = 0;
    picObj->pReceived_prev          = 0;
    picObj->pLock_next              = 0;
    picObj->pReceived_next          = 0;
    picObj->video_full_range_flag   = 0; //default limit
    picObj->matrix_coefficients     = 1;//default bt709
    picObj->tch_hdr_metadata.specVersion = -1; //default not tch video.
    picObj->pFrameBufferDbg         = 0;
    picObj->pFrameBufferDbg_Right   = 0;
    picObj->dv_lut1_addr            = 0;
    picObj->dv_lut1_size            = 0;
    picObj->dv_lut2_addr            = 0;
    picObj->dv_lut2_size            = 0;
    picObj->slice_height            = 0;
    picObj->hdr_metadata_addr = 0;
    picObj->hdr_metadata_size = 0;
    picObj->tch_metadata_addr = 0;
    picObj->tch_metadata_size = 0;
    picObj->is_dolby_video = 0;

    picObj->lumaOffTblSize = 0;
    picObj->chromaOffTblSize = 0;
    picObj->Combine_Y_Addr = 0;
    picObj->Combine_U_Addr = 0;
    picObj->Combine_Width = 0;
    picObj->Combine_Height = 0;
    picObj->Combine_Y_Pitch = 0;
    picObj->secure_flag = 0;
}

int VideoBuffer::prepareBuffer_() {
    int ret = -1;
    struct debug_info * info;
    GraphicBufferInfo::private_yuv_data * pYUVData = getYUVData();
    GraphicBufferInfo::private_rtk_data * pPrivData = getPrivData();
    unsigned int phyBase = -1U;
    rtk_dv_vo_register *p_register;
    GetMetadataInfo_t *metaInfo = NULL;

    initYuvState(&mYUVWin);

    if (pYUVData == NULL) {
        ALOGE("[%s] pYUVData:%p", __FUNCTION__, pYUVData);
        goto err;
    }

    if (getPLockVersion() != PLOCK_VERSION) {
        ALOGE("[%s] getPLockVersion return 0x%x", __FUNCTION__, getPLockVersion());
        goto err;
    }

    if (isExtraBuffer()) {
        ALOGE("[%s] not support the extra buffer!", __FUNCTION__);
        goto err;
    }

    if (isReplicaBuffer()) {
        //pYUVData->pts[0] = pYUVData->pts[1] = 0;
        pYUVData->delay_mode = RingBufferBase::LowDelayDisplay;
        pPrivData->lumaOffTblAddr       = -1U;
        pPrivData->chromaOffTblAddr     = -1U;
        pPrivData->lumaOffTblAddrR      = -1U;
        pPrivData->chromaOffTblAddrR    = -1U;
    }
/*
    if (    pPrivData->display_width  != 0 &&
            pPrivData->display_height != 0 &&
            pPrivData->display_stride != 0) {
        pYUVData->width             = pPrivData->display_width;
        pYUVData->height            = pPrivData->display_height;
        pYUVData->stride            = pPrivData->display_stride;
    }
*/
    mYUVWin.version         = 0x72746B3C;//'rtk10'
    mYUVWin.IsForceDIBobMode = pYUVData->IsForceDIBobMode;

    if ((pYUVData->format & HAL_PIXEL_FORMAT_RTK_P10_MAGIC_MASK) == HAL_PIXEL_FORMAT_RTK_P10_MAGIC) {
        mYUVWin.Y_addr          = (unsigned int) ((long) getPhyAddr(0) & -1U);
        mYUVWin.Y_addr          += pYUVData->p10_compressed_offset[0];
        mYUVWin.U_addr          = (unsigned int) ((long) getPhyAddr(1) & -1U);
        mYUVWin.U_addr          += pYUVData->p10_compressed_offset[0];
    } else {
        mYUVWin.Y_addr          = (unsigned int) ((long) getPhyAddr(0) & -1U);
        mYUVWin.U_addr          = (unsigned int) ((long) getPhyAddr(1) & -1U);
    }

    mYUVWin.width           = pYUVData->width;
    mYUVWin.height          = pYUVData->height;
    if(pYUVData->ch_stride != 0)
        mYUVWin.Y_pitch         = pYUVData->ch_stride;
    else
        mYUVWin.Y_pitch         = pYUVData->stride;
    mYUVWin.C_pitch         = 0;
    mYUVWin.slice_height  = pYUVData->sliceheight;

    mYUVWin.Combine_Y_Addr = 0;
    mYUVWin.Combine_U_Addr = 0;
    mYUVWin.Combine_Width = 0;
    mYUVWin.Combine_Height = 0;
    mYUVWin.Combine_Y_Pitch = 0;

    if ((pYUVData->format & HAL_PIXEL_FORMAT_RTK_P10_MAGIC_MASK) == HAL_PIXEL_FORMAT_RTK_P10_MAGIC) {
        if (mYUVWin.height >= pYUVData->origin_height) {
            mYUVWin.Combine_Y_Addr = (unsigned int) ((long) getPhyAddr(0) & -1U);
            mYUVWin.Combine_U_Addr = mYUVWin.Combine_Y_Addr + GRALLOC_ALIGN(pYUVData->origin_width, 32) * GRALLOC_ALIGN(pYUVData->origin_height, 32);
            mYUVWin.Combine_Width =  pYUVData->origin_width;
            mYUVWin.Combine_Height =  pYUVData->origin_height;
            mYUVWin.Combine_Y_Pitch = GRALLOC_ALIGN(pYUVData->origin_width, 32);
        }
    }

    mYUVWin.pLock           = (unsigned int) ((long) getPLockPhyAddr() & -1U);
    mYUVWin.context         = (unsigned int)this & -1U;//mContext;
    mYUVWin.mode            = pYUVData->yuv_mode;// CONSECUTIVE_FRAME;
    switch (pYUVData->format) {
        case HAL_PIXEL_FORMAT_RTK_W16_H16_YCrCb_420_SP:
        case HAL_PIXEL_FORMAT_RTK_W32_H16_YCrCb_420_SP :
        case HAL_PIXEL_FORMAT_RTK_W16_H32_YCrCb_420_SP :
        case HAL_PIXEL_FORMAT_RTK_W32_H32_YCrCb_420_SP :
        case HAL_PIXEL_FORMAT_RTK_W16_H8_YCrCb_420_SP :
        case HAL_PIXEL_FORMAT_RTK_W64_H64_YCrCb_420_SP :
            mYUVWin.mode |= VO_NV21_MASK;
            break;
    }
    mYUVWin.pixelAR_hor     = 0;
    mYUVWin.pixelAR_ver     = 0;
    mYUVWin.Y_addr_Right    = 0xffffffff;
    mYUVWin.U_addr_Right    = 0xffffffff;
    mYUVWin.pLock_Right     = 0xffffffff;
    mYUVWin.mvc             = 0;
    mYUVWin.subPicOffset    = 0;

    mYUVWin.PTSH2           = (unsigned int) (pYUVData->pts[1] >> 32);
    mYUVWin.RPTSH2          = (unsigned int) (pYUVData->pts[1] >> 32);
    mYUVWin.PTSL2           = (unsigned int) (pYUVData->pts[1] & 0xffffffffLL);
    mYUVWin.RPTSL2          = (unsigned int) (pYUVData->pts[1] & 0xffffffffLL);
    mYUVWin.PTSH            = (unsigned int) (pYUVData->pts[0] >> 32);
    mYUVWin.PTSL            = (unsigned int) (pYUVData->pts[0] & 0xffffffffLL);
    mYUVWin.RPTSH           = (unsigned int) (pYUVData->pts[0] >> 32);
    mYUVWin.RPTSL           = (unsigned int) (pYUVData->pts[0] & 0xffffffffLL);

    mYUVWin.pFrameBufferDbg                    = (unsigned int) ((unsigned long)mDebugInfo->getPhyAddr() & -1U);
    info = (struct debug_info *) mDebugInfo->getVirAddr();
    memset(info, 0, sizeof(struct debug_info));
    info->context = (unsigned int)this & -1U;

    for(int i = 0; i < 2; i++)
        mPTS[i] = pYUVData->pts[i];

    /* For HEVC 10bit HDR */
    phyBase = ((unsigned int) ((long) getPhyAddr(0) & -1U)) + pYUVData->p10_compressed_offset[0];

    mYUVWin.lumaOffTblAddr =
        (pYUVData->lumaTableOffset      != -1U) ? (phyBase + pYUVData->lumaTableOffset ):(pPrivData->lumaOffTblAddr != -1U) ? pPrivData->lumaOffTblAddr: -1U;

    mYUVWin.chromaOffTblAddr =
        (pYUVData->chromaTableOffset    != -1U) ? (phyBase + pYUVData->chromaTableOffset ):(pPrivData->chromaOffTblAddr != -1U) ? pPrivData->chromaOffTblAddr : -1U;

    mYUVWin.lumaOffTblAddrR =
        (pYUVData->lumaTableOffsetR     != -1U) ? (phyBase + pYUVData->lumaTableOffsetR ):(pPrivData->lumaOffTblAddrR     != -1U) ? pPrivData->lumaOffTblAddrR : -1U;

    mYUVWin.chromaOffTblAddrR =
        (pYUVData->chromaTableOffsetR   != -1U) ? (phyBase + pYUVData->chromaTableOffsetR ):(pPrivData->chromaOffTblAddrR   != -1U) ? pPrivData->chromaOffTblAddrR : -1U;

#if 0
    mYUVWin.lumaOffTblAddr                     = pPrivData->lumaOffTblAddr;
    mYUVWin.chromaOffTblAddr                   = pPrivData->chromaOffTblAddr;
    mYUVWin.lumaOffTblAddrR                    = 0xffffffff;
    mYUVWin.chromaOffTblAddrR                  = 0xffffffff;
#endif
    mYUVWin.bufBitDepth                        = pPrivData->bufBitDepth;
    mYUVWin.bufFormat                          = pPrivData->bufFormat;
    mYUVWin.transferCharacteristics            = pPrivData->transferCharacteristics;
    mYUVWin.display_primaries_x0               = (unsigned short)pPrivData->display_primaries_x0;
    mYUVWin.display_primaries_y0               = (unsigned short)pPrivData->display_primaries_y0;
    mYUVWin.display_primaries_x1               = (unsigned short)pPrivData->display_primaries_x1;
    mYUVWin.display_primaries_y1               = (unsigned short)pPrivData->display_primaries_y1;
    mYUVWin.display_primaries_x2               = (unsigned short)pPrivData->display_primaries_x2;
    mYUVWin.display_primaries_y2               = (unsigned short)pPrivData->display_primaries_y2;
    mYUVWin.white_point_x                      = (unsigned short)pPrivData->white_point_x;
    mYUVWin.white_point_y                      = (unsigned short)pPrivData->white_point_y;
    mYUVWin.max_display_mastering_luminance    = pPrivData->max_display_mastering_luminance;
    mYUVWin.min_display_mastering_luminance    = pPrivData->min_display_mastering_luminance;
    mYUVWin.video_full_range_flag = pPrivData->video_full_range_flag;
    mYUVWin.matrix_coefficients = pPrivData->matrix_coefficients;

    mYUVWin.is_tch_video = pPrivData->is_tch_video;
    memcpy(&mYUVWin.tch_hdr_metadata, pPrivData->technicolor_data, sizeof(tch_metadata));

    if (getGrallocVersion() == 5) {
        metaInfo = getMetadataInfo();
        if(metaInfo->size) {
            if (!(pYUVData->usage & GRALLOC_USAGE_PROTECTED) && !(pYUVData->usage & GRALLOC_USAGE_SECURE)) {
                if (!isReplicaBuffer())
                    endianSwap(metaInfo->vir_addr, pPrivData->hdr_metadata_size);

                flushMetaBuffer();
                mYUVWin.hdr_metadata_addr = metaInfo->phy_addr;
                mYUVWin.hdr_metadata_size = pPrivData->hdr_metadata_size;
            }
#ifdef ENABLE_TEE_DRM_FLOW
            else {
                if (!isReplicaBuffer())
                    Tee_4ByteSwap(metaInfo->phy_addr, pPrivData->hdr_metadata_size);

                mYUVWin.hdr_metadata_addr = metaInfo->phy_addr;
                mYUVWin.hdr_metadata_size = pPrivData->hdr_metadata_size;
            }
#endif
            rtk_dv_vo_register dolby_register;
            mYUVWin.dm_reg1_addr = metaInfo->phy_addr + GRALLOC_ALIGN(mYUVWin.hdr_metadata_size, 16);
            mYUVWin.dm_reg1_size = sizeof(dolby_register.dst_dm_reg1);
            mYUVWin.dm_reg2_addr = mYUVWin.dm_reg1_addr + offsetof(rtk_dv_vo_register, dst_dm_reg2);
            mYUVWin.dm_reg2_size = sizeof(dolby_register.dst_dm_reg2);
            mYUVWin.dm_reg3_addr = mYUVWin.dm_reg1_addr + offsetof(rtk_dv_vo_register, dst_dm_reg3);
            mYUVWin.dm_reg3_size = sizeof(dolby_register.dst_dm_reg3);
            mYUVWin.dv_lut1_addr = mYUVWin.dm_reg1_addr + offsetof(rtk_dv_vo_register, dv_lut1);
            mYUVWin.dv_lut1_size = sizeof(dolby_register.dv_lut1);
            mYUVWin.dv_lut2_addr = mYUVWin.dm_reg1_addr + offsetof(rtk_dv_vo_register, dv_lut2);
            mYUVWin.dv_lut2_size = sizeof(dolby_register.dv_lut2);
        }
    } else
    {
        p_register = (rtk_dv_vo_register *)pPrivData->dolby_register;
        if (dm_reg1 == NULL)
            dm_reg1 = new IonBuffer(IonBuffer::AllocBuffer, sizeof(p_register->dst_dm_reg1), IonBuffer::AudioHeapMask);
        if (dm_reg2 == NULL)
            dm_reg2 = new IonBuffer(IonBuffer::AllocBuffer, sizeof(p_register->dst_dm_reg2), IonBuffer::AudioHeapMask);
        if (dm_reg3 == NULL)
            dm_reg3 = new IonBuffer(IonBuffer::AllocBuffer, sizeof(p_register->dst_dm_reg3), IonBuffer::AudioHeapMask);
        if (dv_lut1 == NULL)
            dv_lut1 = new IonBuffer(IonBuffer::AllocBuffer, sizeof(p_register->dv_lut1), IonBuffer::AudioHeapMask);
        if (dv_lut2 == NULL)
            dv_lut2 = new IonBuffer(IonBuffer::AllocBuffer, sizeof(p_register->dv_lut2), IonBuffer::AudioHeapMask);

        memcpy(dm_reg1->getVirAddr(), &p_register->dst_dm_reg1, sizeof(p_register->dst_dm_reg1));
        memcpy(dm_reg2->getVirAddr(), &p_register->dst_dm_reg2, sizeof(p_register->dst_dm_reg2));
        memcpy(dm_reg3->getVirAddr(), &p_register->dst_dm_reg3, sizeof(p_register->dst_dm_reg3));
        memcpy(dv_lut1->getVirAddr(), &p_register->dv_lut1, sizeof(p_register->dv_lut1));
        memcpy(dv_lut2->getVirAddr(), &p_register->dv_lut2, sizeof(p_register->dv_lut2));

        mYUVWin.dm_reg1_addr = (unsigned int) ((unsigned long)dm_reg1->getPhyAddr() & -1U);
        mYUVWin.dm_reg1_size = sizeof(p_register->dst_dm_reg1);
        mYUVWin.dm_reg2_addr = (unsigned int) ((unsigned long)dm_reg2->getPhyAddr() & -1U);
        mYUVWin.dm_reg2_size = sizeof(p_register->dst_dm_reg2);
        mYUVWin.dm_reg3_addr = (unsigned int) ((unsigned long)dm_reg3->getPhyAddr() & -1U);
        mYUVWin.dm_reg3_size = sizeof(p_register->dst_dm_reg3);
        mYUVWin.dv_lut1_addr = (unsigned int) ((unsigned long)dv_lut1->getPhyAddr() & -1U);
        mYUVWin.dv_lut1_size = sizeof(p_register->dv_lut1);
        mYUVWin.dv_lut2_addr = (unsigned int) ((unsigned long)dv_lut2->getPhyAddr() & -1U);
        mYUVWin.dv_lut2_size = sizeof(p_register->dv_lut2);
    }

    mYUVWin.is_dolby_video = pPrivData->is_dolby_video;
    mFlags |= FILLYUV;

    if ((pYUVData->usage & GRALLOC_USAGE_PROTECTED) || (pYUVData->usage & GRALLOC_USAGE_SECURE))
    {
        mYUVWin.secure_flag |= SECURE_BUFFER;
    }

    if (    mYUVWin.Y_addr  == 0    ||
            mYUVWin.width   == 0    ||
            mYUVWin.height  == 0    ||
            mYUVWin.Y_pitch == 0) {
        ALOGE("[%s] w:%d h:%d Yaddr:0x%08x Ypitch:%d", __FUNCTION__, mYUVWin.width, mYUVWin.height,
                mYUVWin.Y_addr, mYUVWin.Y_pitch);
        goto err;
    }

    ret = 0;
err:
    return ret;
}

void VideoBuffer::queueBuffer_() {
    GraphicBufferInfo::private_yuv_data * pYUVData = getYUVData();
    if (pYUVData == NULL) {
        ALOGE("[%s] pYUVData:%p", __FUNCTION__, pYUVData);
        return;
    }

    if (!(mFlags & FILLYUV)) {
        ALOGE("[%s] mFlags:0x%x", __FUNCTION__, mFlags);
        return;
    }

    if (mFlags & QUEUE_BUFFER) {
        ALOGE("[%s] mFlags:0x%x", __FUNCTION__, mFlags);
        return;
    }

    ConfigLowDelay((enum RingBufferBase::LowDelayMode) pYUVData->delay_mode,
            pYUVData->delay_depth, pYUVData->init_frame);

    setPLockStatus(PLockBase::PLOCK_STATUS_Q_PEND);

    SetDeintFlag(pYUVData->deintflag);

    InbandCmd(VIDEO_VO_INBAND_CMD_TYPE_OBJ_PIC, &mYUVWin, sizeof(mYUVWin));

    mFlags &= ~FILLYUV;
    mFlags |= QUEUE_BUFFER;
}

void VideoBuffer::cancelBuffer_() {
    if (mFlags & QUEUE_BUFFER)
        ALOGE("[%s] mFlags:0x%x", __FUNCTION__, mFlags);
    else
        resetWin();
}

bool VideoBuffer::releaseBufferCheck() {
    bool release = false;
    if (!(mFlags & QUEUE_BUFFER)) {
        ALOGE("[%s] mFlags:0x%x", __FUNCTION__, mFlags);
        release = true;
    }

    if (!release && getPLockStatus() == PLockBase::PLOCK_STATUS_VO_UNLOCK)
        release = true;
#if 0
    else
        ALOGI("[%s] getPLockStatus:%x", __FUNCTION__, getPLockStatus());
#endif

    if (release)
        releaseBuffer_();

    return release;
}

void VideoBuffer::releaseBuffer_() {
    struct debug_info * info = (struct debug_info *) mDebugInfo->getVirAddr();
    struct debug_message message;
    message.display_time = (BSWAP_32(info->display_time_L) - BSWAP_32(info->receive_time_L)) * 1000 / 90000;
    message.release_time = (BSWAP_32(info->release_time_L) - BSWAP_32(info->display_time_L)) * 1000 / 90000;
    message.display_cnt = BSWAP_32(info->display_cnt);
    message.drop_cnt = BSWAP_32(info->drop_cnt);
    message.context = BSWAP_32(info->context);
    message.timestamp = (float)mPTS[0] / 90.0;
    message.bufferId = getBufferId();

    if (!(mFlags & QUEUE_BUFFER)) {
        ALOGE("[%s] mFlags:0x%x", __FUNCTION__, mFlags);
        return;
    }

    updataATraceInfo(&message);
    setPLockStatus(PLockBase::PLOCK_STATUS_RESET);
    mFlags &= ~QUEUE_BUFFER;
}

void VideoBuffer::resetWin() {
    memset((void *) &mYUVWin, 0, sizeof(mYUVWin));
    mFlags &= ~FILLYUV;
}

void VideoBuffer::dump(android::String8& buf, const char* prefix) {
    android::String8 state;
    if (prefix != NULL)
        buf.appendFormat("%s", prefix);
    PLockBase::Client::dump(state);
    state.append(",");
    BufferBase::dump(state);
    buf.appendFormat("%s", state.string());
    if (prefix != NULL)
        buf.append("\n");
}

void VideoBuffer::endianSwap(void *addr, unsigned int byte_size) {
    unsigned int i;
    unsigned int *p = (unsigned int*)addr;

    if(byte_size%4 != 0)
        printf("[buffer_endian_swap size warnning]\n");

    for(i=0; i<(byte_size>>2); i++)
    {
        unsigned int b0 = *p & 0x000000ff;
        unsigned int b1 = (*p & 0x0000ff00) >> 8;
        unsigned int b2 = (*p & 0x00ff0000) >> 16;
        unsigned int b3 = (*p & 0xff000000) >> 24;
        *p = (b0 << 24) | (b1 << 16) | (b2 << 8) | b3;
        p++;
    }
}
