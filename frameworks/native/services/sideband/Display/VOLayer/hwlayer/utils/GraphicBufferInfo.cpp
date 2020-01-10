#include "GraphicBufferInfo.h"

GraphicBufferInfo::Client::Client()
    : mLock((pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER),
    mReleaseLock((pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER),
    mService(NULL),
    mHandle(NULL),
    mState(BufferFree),
    mViraddr(MAP_FAILED),
    mViraddrSize(0),
    mIonBuffer(NULL),
    mExtBuffer(NULL),
    mShareBuffer(NULL),
    mGralloc_version(0),
    mReplicaMetadata(NULL),
    mMetadataBuffer(NULL)
{
    memset((void *) &mYUVData, 0, sizeof(mYUVData));
    memset((void *) &mPrivData, 0, sizeof(mPrivData));
    memset((void *) &metaInfo, 0, sizeof(metaInfo));
}

void GraphicBufferInfo::Client::setBufferHandle(buffer_handle_t handle) {
    pthread_mutex_lock(&mLock);
    if (mService)
        mService->setBufferHandle(this, handle);
    else
        mHandle = handle;

    if (mState == Client::BufferGralloc && mYUVData.share_fd > 0)
        mShareBuffer = new IonBuffer(IonBuffer::ImportBuffer_lock, (long long) mYUVData.share_fd);

    if (mState == Client::BufferGralloc && mGralloc_version == 5 && metaInfo.share_metadata_fd >= 0 && (mYUVData.usage & GRALLOC_USAGE_HW_ION)) {
        mMetadataBuffer = new IonBuffer(IonBuffer::ImportBuffer, (long long)metaInfo.share_metadata_fd);
        metaInfo.vir_addr = mMetadataBuffer->getVirAddr();
        metaInfo.phy_addr = (unsigned long)mMetadataBuffer->getPhyAddr();
    }

    pthread_mutex_unlock(&mLock);
}

void GraphicBufferInfo::Client::setExtBuffer(ExtBuffer * buffer) {
    pthread_mutex_lock(&mLock);
    if (mService)
        mService->setExtBuffer(this, buffer);
    else
        mExtBuffer = buffer;
    pthread_mutex_unlock(&mLock);
}

int GraphicBufferInfo::Client::validate(buffer_handle_t handle) {
    int ret = -1;
    pthread_mutex_lock(&mLock);
    if (mService)
        ret = mService->validate(this, handle);
    pthread_mutex_unlock(&mLock);
    return ret;
}

unsigned long GraphicBufferInfo::Client::getSliceHeight() {
    unsigned long offset = 0;
    offset = (mPrivData.display_height != 0) ? mPrivData.display_height : mYUVData.height;
    if (mState == BufferGralloc || mState == BufferReplica) {

        switch (mYUVData.format) {
            case HAL_PIXEL_FORMAT_RTK_W16_H8_YCbCr_420_SP:
            case HAL_PIXEL_FORMAT_RTK_W16_H8_YCrCb_420_SP:
                offset = GRALLOC_ALIGN(offset,  8);
                break;
            case HAL_PIXEL_FORMAT_RTK_W16_H32_YCbCr_420_SP:
            case HAL_PIXEL_FORMAT_RTK_W32_H32_YCbCr_420_SP:
            case HAL_PIXEL_FORMAT_RTK_W16_H32_YCrCb_420_SP:
            case HAL_PIXEL_FORMAT_RTK_W32_H32_YCrCb_420_SP:
                offset = GRALLOC_ALIGN(offset, 32);
                break;
            case HAL_PIXEL_FORMAT_RTK_W64_H64_YCbCr_420_SP:
            case HAL_PIXEL_FORMAT_RTK_W64_H64_YCrCb_420_SP:
                offset = GRALLOC_ALIGN(offset,  64);
                break;
            case HAL_PIXEL_FORMAT_RTK_P8_COMPRESSED:
            case HAL_PIXEL_FORMAT_RTK_P10_COMPRESSED:
                offset = offset;
                break;
            case HAL_PIXEL_FORMAT_RTK_P8_COMPRESSED_VP9:
            case HAL_PIXEL_FORMAT_RTK_P10_COMPRESSED_VP9:
                offset = GRALLOC_ALIGN(offset, 64);
                break;
            case HAL_PIXEL_FORMAT_RTK_W32_H32_P8_COMPRESSED:
            case HAL_PIXEL_FORMAT_RTK_W32_H32_P10_COMPRESSED:
                offset = GRALLOC_ALIGN(offset,32);
                break;
            default:
                offset = GRALLOC_ALIGN(offset, 16);
                break;
        }
    }
    return offset;
}

unsigned long GraphicBufferInfo::Client::getStride() {
    unsigned long offset = 0;
    if (mState == BufferGralloc || mState == BufferReplica) {

        switch (mYUVData.format) {
            case HAL_PIXEL_FORMAT_RTK_P8_COMPRESSED:
            case HAL_PIXEL_FORMAT_RTK_P10_COMPRESSED:
                offset = (mPrivData.display_width  != 0) ? mPrivData.display_width  : mYUVData.width;
                break;
            case HAL_PIXEL_FORMAT_RTK_P8_COMPRESSED_VP9:
            case HAL_PIXEL_FORMAT_RTK_P10_COMPRESSED_VP9:
                offset = (mPrivData.display_width  != 0) ? mPrivData.display_width  : mYUVData.width;
                offset = GRALLOC_ALIGN(offset, 64);
                break;
            case HAL_PIXEL_FORMAT_RTK_W16_H8_YCbCr_420_SP:
            case HAL_PIXEL_FORMAT_RTK_W16_H8_YCrCb_420_SP:
            case HAL_PIXEL_FORMAT_RTK_W16_H32_YCbCr_420_SP:
            case HAL_PIXEL_FORMAT_RTK_W32_H32_YCbCr_420_SP:
            case HAL_PIXEL_FORMAT_RTK_W16_H32_YCrCb_420_SP:
            case HAL_PIXEL_FORMAT_RTK_W32_H32_YCrCb_420_SP:
            case HAL_PIXEL_FORMAT_RTK_W64_H64_YCbCr_420_SP:
            case HAL_PIXEL_FORMAT_RTK_W64_H64_YCrCb_420_SP:
            case HAL_PIXEL_FORMAT_RTK_W32_H32_P8_COMPRESSED:
            case HAL_PIXEL_FORMAT_RTK_W32_H32_P10_COMPRESSED:
            default:
                offset = mYUVData.stride;
                break;
        }
    }
    return offset;
}

unsigned long GraphicBufferInfo::Client::getOffset(unsigned int slot) {
    unsigned long offset = 0;
    uint64_t format = mYUVData.format;
    if (mState == BufferGralloc || mState == BufferReplica) {

#if 0
        if ((mYUVData.format & HAL_PIXEL_FORMAT_RTK_P10_MAGIC_MASK) == HAL_PIXEL_FORMAT_RTK_P10_MAGIC) {
            if (slot < RTK_P10_MAX_COMPRESSED_PLANE)
                offset = mPrivData.p10_compressed_offset[slot];
        } else {
#endif
            if (slot == 0) {
                offset = 0;
            } else if (slot == 1) {
                if ((mYUVData.format & HAL_PIXEL_FORMAT_RTK_P10_MAGIC_MASK) == HAL_PIXEL_FORMAT_RTK_P10_MAGIC) {
                    int compressedModeBits = HAL_PIXEL_FORMAT_RTK_P10_CM_GET(mYUVData.format) ? 10 : 8;
                    int isVP9 = HAL_PIXEL_FORMAT_RTK_P10_LM_GET(mYUVData.format) ? 1 : 0; // NOT READY
                    if (!isVP9) {
                        if (compressedModeBits == 10)
                            format = HAL_PIXEL_FORMAT_RTK_P10_COMPRESSED;
                        else
                            format = HAL_PIXEL_FORMAT_RTK_P8_COMPRESSED;
                    } else {
                        if (compressedModeBits == 10)
                            format = HAL_PIXEL_FORMAT_RTK_P10_COMPRESSED_VP9;
                        else
                            format = HAL_PIXEL_FORMAT_RTK_P8_COMPRESSED_VP9;
                    }
                }

                switch (format) {
                    case HAL_PIXEL_FORMAT_RTK_W16_H8_YCbCr_420_SP:
                    case HAL_PIXEL_FORMAT_RTK_W16_H8_YCrCb_420_SP:
                        offset = (GRALLOC_ALIGN(mYUVData.height,  8) * mYUVData.stride);
                        break;
                    case HAL_PIXEL_FORMAT_RTK_W16_H32_YCbCr_420_SP:
                    case HAL_PIXEL_FORMAT_RTK_W32_H32_YCbCr_420_SP:
                    case HAL_PIXEL_FORMAT_RTK_W16_H32_YCrCb_420_SP:
                    case HAL_PIXEL_FORMAT_RTK_W32_H32_YCrCb_420_SP:
                        offset = (GRALLOC_ALIGN(mYUVData.height, 32) * mYUVData.stride);
                        break;
                    case HAL_PIXEL_FORMAT_RTK_W64_H64_YCbCr_420_SP:
                    case HAL_PIXEL_FORMAT_RTK_W64_H64_YCrCb_420_SP:
                        offset = (GRALLOC_ALIGN(mYUVData.height,  64) * mYUVData.stride);
                        break;
                    case HAL_PIXEL_FORMAT_RTK_P8_COMPRESSED:
                    case HAL_PIXEL_FORMAT_RTK_P10_COMPRESSED:
                        offset = (mYUVData.height * mYUVData.stride);
                        break;
                    case HAL_PIXEL_FORMAT_RTK_P8_COMPRESSED_VP9:
                    case HAL_PIXEL_FORMAT_RTK_P10_COMPRESSED_VP9:
                        offset = (GRALLOC_ALIGN(mYUVData.height, 64) * mYUVData.stride);
                        break;
                    case HAL_PIXEL_FORMAT_RTK_W32_H32_P8_COMPRESSED:
                    case HAL_PIXEL_FORMAT_RTK_W32_H32_P10_COMPRESSED:
                        offset = (GRALLOC_ALIGN(mYUVData.height,32) * mYUVData.stride);
                        break;
                    default:
                        offset = (GRALLOC_ALIGN(mYUVData.height, 16) * mYUVData.stride);
                        break;
                }
            }
#if 0
        }
#endif
    }
    return offset;
}

void * GraphicBufferInfo::Client::getPhyAddr(unsigned int slot, long long * pBufferSize) {
    pthread_mutex_lock(&mLock);
    long long retSize = 0;
    void * retAddr = NULL;

    if (mState == BufferGralloc) {
        retSize = (long long) mYUVData.size;
        retAddr = (void *) (mYUVData.phyAddr & -1UL);
    } else if (mState == BufferReplica) {
        if (mIonBuffer != NULL) {
            retSize = mIonBuffer->getSize();
            retAddr = mIonBuffer->getPhyAddr();
        }
    }

    if (retAddr) {
        retAddr = (void *) (((unsigned long) retAddr )+ getOffset(slot));
    }

    if (pBufferSize)
        *pBufferSize = retSize;
    pthread_mutex_unlock(&mLock);

    return retAddr;
}

void * GraphicBufferInfo::Client::getVirAddr(long long * pBufferSize) {
    pthread_mutex_lock(&mLock);
    long long retSize = 0;
    void * retAddr = NULL;

    if (mState == BufferGralloc) {
        if (mViraddr ==  MAP_FAILED && mShareBuffer != NULL) {
            mViraddr = mmap(NULL, mYUVData.size, PROT_READ | PROT_WRITE, MAP_SHARED, mShareBuffer->getShareFd(), 0);
            if (mViraddr != MAP_FAILED)
                mViraddrSize = mYUVData.size;
        }
        if (mViraddr != MAP_FAILED) {
            retSize = mViraddrSize;
            retAddr = mViraddr;
        } else
            ALOGE("[%s] MAP_FAILED! (ion:share_fd = %d , size = %d)",
                    __FUNCTION__, mYUVData.share_fd, mYUVData.size);
    } else if (mState == BufferReplica) {
        if (mIonBuffer != NULL) {
            retSize = mIonBuffer->getSize();
            retAddr = mIonBuffer->getVirAddr();
        }
    }

    if (pBufferSize)
        *pBufferSize = retSize;
    pthread_mutex_unlock(&mLock);

    if (retAddr == NULL || retSize == 0)
        ALOGW("[%s] return %p (size=%lld , mState = 0x%x)", __FUNCTION__, retAddr, retSize, mState);

    return retAddr;
}

int GraphicBufferInfo::Client::getFormat(unsigned int * pFormat) {
    if (pFormat == NULL)
        goto err;
    if (isExtraBuffer() || isFreedBuffer())
        goto err;

    *pFormat = mYUVData.format;

    return 0;
err:
    return -1;
}

void GraphicBufferInfo::Client::clearBufferHandle() {
    pthread_mutex_lock(&mReleaseLock);
    pthread_mutex_lock(&mLock);
    if (mService != NULL && mService->clearBufferHandle(this) != 0)
        ALOGE("[%s] service->clearBufferHandle return error! (mService:%p mClient:%p)",
                __FUNCTION__, mService, this);
    else
        mState = BufferFree;

    if (mState == BufferFree) {
        mHandle = NULL;
        if (mViraddr != MAP_FAILED) {
            munmap(mViraddr, mViraddrSize);
            mViraddr = MAP_FAILED;
            mViraddrSize = 0;
        }
        if (mIonBuffer) {
            delete mIonBuffer;
            mIonBuffer = NULL;
        }
        if (mExtBuffer) {
            delete mExtBuffer;
            mExtBuffer = NULL;
        }
        if (mShareBuffer) {
            delete mShareBuffer;
            mShareBuffer = NULL;
        }

        if (mReplicaMetadata) {
            delete mReplicaMetadata;
            mReplicaMetadata = NULL;
        }

        if (mMetadataBuffer) {
            delete mMetadataBuffer;
            mMetadataBuffer = NULL;
        }

        memset(&mYUVData, 0, sizeof(mYUVData));
        memset(&mPrivData, 0, sizeof(mPrivData));
        memset(&metaInfo, 0, sizeof(metaInfo));
        mGralloc_version = 0;
    }
    pthread_mutex_unlock(&mLock);
    pthread_mutex_unlock(&mReleaseLock);
}

void GraphicBufferInfo::Client::dump(android::String8& buf, const char* prefix) {
    if (prefix != NULL)
        buf.appendFormat("%s", prefix);
    buf.appendFormat("GBInfo[state=%x]", mState);
    if (prefix != NULL)
        buf.append("\n");
}


/****************************************************************************************************/
#ifdef ENABLE_TEE_DRM_FLOW
#include "tee_client_api.h"
#include "tee_api.h"
class ProtectedOps {
public:
    ProtectedOps() : mReady(false) {
        if (TEE_API_Initialize(&ctx, &sess, &rtk_sess) == TA_SUCCESS) {
            mReady = true;
        }
    };
    virtual  ~ProtectedOps() {
        if (mReady)
            TEE_API_Finalize(&ctx, &sess, &rtk_sess);
    };
    int memcpy (void * dstPhyAddr, void * srcPhyAddr, long size) {
        int ret = -1;
        do {
            unsigned int dstPhyAddr_tee = (unsigned int) ((long) dstPhyAddr) & -1U;
            unsigned int srcPhyAddr_tee = (unsigned int) ((long) srcPhyAddr) & -1U;
            int size_tee = (int) size & -1U;

            if (!mReady) {
                ALOGE("[%s] ProtectedOps not ready!", __func__);
                break;
            }

            if (TEE_API_memcpy(&sess, &rtk_sess, dstPhyAddr_tee, srcPhyAddr_tee, size_tee) != TA_SUCCESS) {
                ALOGE("[%s] TEE_API_memcpy return error!", __func__);
                break;
            }

            ret = 0;
            break;
        } while (0);
        return ret;
    };

    int Tee_4ByteSwap(unsigned int dstPhyAddr, int size) {
        int ret = -1;
        do {
            unsigned int dstPhyAddr_tee = dstPhyAddr & -1U;
            int size_tee = size & -1U;

            if (!mReady) {
                ALOGE("[%s] ProtectedOps not ready!", __func__);
                break;
            }

            if (TEE_API_4ByteSwap(&sess, dstPhyAddr_tee, size_tee) != TA_SUCCESS) {
                ALOGE("[%s] TEE_API_4ByteSwap return error!", __func__);
                break;
            }
            ret = 0;
            break;
        } while(0);
        return ret;
    };

private:
    bool                mReady;
    TEEC_Context        ctx;
    TEEC_Session        sess;
    RTK_TEEC_Session    rtk_sess;

};
#else
class ProtectedOps {
public:
    ProtectedOps() { };
    virtual  ~ProtectedOps() { };
    int memcpy (void * /*dstPhyAddr*/, void * /*srcPhyAddr*/, long /*size*/) {
        ALOGE("[%s] Should not happen!", __func__);
        return -1;
    };
};
#endif

GraphicBufferInfo::GraphicBufferInfo()
    : mLock((pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER),
    mClientLock((pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER),
    mProtectedOps(NULL)
{
    while (mClientList.size() > 0) {
        Client * client = mClientList.itemAt(0);
        removeClient(client);
#if 1 // debug
        if (client == mClientList.itemAt(0))
            ALOGE("[%s] ERROR! client=%p", __func__, client);
#endif
    }
    hw_get_module(GRALLOC_HARDWARE_MODULE_ID, &mGrallocModule);
    mProtectedOps = new ProtectedOps();
}

GraphicBufferInfo::~GraphicBufferInfo() {
    if (mProtectedOps) {
        delete mProtectedOps;
        mProtectedOps = NULL;
    }
}

void GraphicBufferInfo::registerClient(Client * client) {
    pthread_mutex_lock(&mClientLock);
    bool found = false;
    for (size_t i=0;i<mClientList.size();i++) {
        if (mClientList.itemAt(i) == client) {
            found = true;
            break;
        }
    }
    if (!found) {
        if (client != NULL) {
            mClientList.add(client);
            client->mService = this;
        }
    }
    pthread_mutex_unlock(&mClientLock);
}

void GraphicBufferInfo::removeClient(Client * client) {
    pthread_mutex_lock(&mClientLock);
    for (size_t i=0;i<mClientList.size();i++) {
        if (mClientList.itemAt(i) == client) {
            mClientList.removeAt(i);
            client->mService = NULL;
            break;
        }
    }
    pthread_mutex_unlock(&mClientLock);
}

void GraphicBufferInfo::setBufferHandle(Client * client, buffer_handle_t handle) {
    pthread_mutex_lock(&mClientLock);
    mali_gralloc_private_module_t * privateModule = (mali_gralloc_private_module_t *) mGrallocModule;
    bool found = false;
    for (size_t i=0;i<mClientList.size();i++) {
        if (mClientList.itemAt(i) == client) {
            found = true;
            break;
        }
    }
    if (found) {
        int ret = privateModule->GetYUVData(privateModule,
                handle,
                (void *) &client->mYUVData);

        if (ret == 0) {
            privateModule->GetPrivData(privateModule,
                    handle,
                    (void *) &client->mPrivData, sizeof(client->mPrivData));
            client->mHandle = handle;
            client->mState = Client::BufferGralloc;

            client->mGralloc_version = privateModule->base.common.version_minor;
            if(privateModule->base.common.version_minor == 5 && (client->mYUVData.usage & GRALLOC_USAGE_HW_ION))
               privateModule->GetBufferInfo(privateModule, handle, GRALLOC_CMD_GET_METADATA_INFO, &client->metaInfo, sizeof(client->metaInfo));
        } else
            ALOGE("[%s] GetYUVData return ERROR!!! (%d)", __FUNCTION__, ret);
        
    } else
        ALOGE("[%s] Client(%p) is not found!", __FUNCTION__, client);
    pthread_mutex_unlock(&mClientLock);
}

int GraphicBufferInfo::validate(Client * client, buffer_handle_t handle) {
    int ret = -1;
    pthread_mutex_lock(&mClientLock);
    mali_gralloc_private_module_t * privateModule = (mali_gralloc_private_module_t *) mGrallocModule;
    bool found = false;
    for (size_t i=0;i<mClientList.size();i++) {
        if (mClientList.itemAt(i) == client) {
            found = true;
            break;
        }
    }
    if (found) {
        ret = privateModule->Validate(privateModule, handle);
    } else
        ALOGE("[%s] Client(%p) is not found!", __FUNCTION__, client);
    pthread_mutex_unlock(&mClientLock);
    return ret;
}

void GraphicBufferInfo::setExtBuffer(Client * client, Client::ExtBuffer * buffer) {
    pthread_mutex_lock(&mClientLock);
    mali_gralloc_private_module_t * privateModule = (mali_gralloc_private_module_t *) mGrallocModule;
    bool found = false;
    for (size_t i=0;i<mClientList.size();i++) {
        if (mClientList.itemAt(i) == client) {
            found = true;
            break;
        }
    }
    if (found) {
        client->mExtBuffer = buffer;
        client->mState = Client::BufferExtra;
    } else
        ALOGE("[%s] Client(%p) is not found!", __FUNCTION__, client);
    pthread_mutex_unlock(&mClientLock);
}

int GraphicBufferInfo::clearBufferHandle(Client * client) {
    int ret = -1;
    pthread_mutex_lock(&mClientLock);
    bool found = false;
    for (size_t i=0;i<mClientList.size();i++) {
        if (mClientList.itemAt(i) == client) {
            found = true;
            break;
        }
    }
    if (found) {
        ret = 0;
        client->mState = Client::BufferFree;
    }
    pthread_mutex_unlock(&mClientLock);
    return ret;
}

#ifdef ENABLE_TEE_DRM_FLOW
int GraphicBufferInfo::Tee_4ByteSwap(unsigned int dstPhyAddr, int size) {
    return mProtectedOps->Tee_4ByteSwap(dstPhyAddr, size);
}
#endif

int GraphicBufferInfo::replicaCopy(Client * des, Client * src) {
    int ret = -1;
    pthread_mutex_lock(&mClientLock);
    bool found_des = false, found_src = false;
    for (size_t i=0;i<mClientList.size();i++) {
        if (mClientList.itemAt(i) == des)
            found_des = true;
        if (mClientList.itemAt(i) == src)
            found_src = true;
        if (found_des && found_src)
            break;
    }
    if (found_des && found_src) {
        src->lockBuffer();
        des->lockBuffer();
        if (    des->mState == Client::BufferFree   &&
                src->mState != Client::BufferFree   ) {
            if (src->mState & Client::BufferExtra) {
                if (des->mExtBuffer != NULL)
                    delete des->mExtBuffer;
                des->mExtBuffer = src->mExtBuffer->replica();
                des->mState = Client::BufferReplica | Client::BufferExtra;
                ret = 0;
            } else {
                {
                    memcpy((void *) &des->mYUVData, (void *) &src->mYUVData, sizeof(des->mYUVData));
                    memcpy((void *) &des->mPrivData, (void *) &src->mPrivData, sizeof(des->mPrivData));
                    ret = 0;
                }
                if (ret == 0) {
#ifdef ENABLE_TEE_DRM_FLOW
                    if ((des->mYUVData.usage & GRALLOC_USAGE_PROTECTED) || (des->mYUVData.usage & GRALLOC_USAGE_SECURE)) {
                        // TODO : need to use memcpy provided by TEE

                        do {
                            long long copySize;
                            void * srcPhyAddr = src->getPhyAddr(0/*slot*/, &copySize);
                            void * dstPhyAddr = NULL;

                            ret = -1;

                            if (!srcPhyAddr)
                                break;

                            if (des->mIonBuffer)
                                delete des->mIonBuffer;

                            des->mIonBuffer = new IonBuffer(IonBuffer::AllocBuffer, copySize,
                                    IonBuffer::SecureHeapMask, IonBuffer::HWIPACC/*flag_mask*/);

                            dstPhyAddr = des->mIonBuffer->getPhyAddr();

                            if (!dstPhyAddr) {
                                delete des->mIonBuffer;
                                des->mIonBuffer = NULL;
                                ALOGW("[%s] create IonBuffer failed! (copySize = %lld)", __FUNCTION__, copySize);
                                break;
                            }

                            if (mProtectedOps->memcpy(dstPhyAddr, srcPhyAddr, (long) copySize & -1L) != 0)
                                break;

                            des->mState = Client::BufferReplica;
                            ret = 0;
                        } while (0);

                        do {
                            memset((void *)&des->metaInfo, 0, sizeof(des->metaInfo));

                            if(src->mGralloc_version != 5 || !src->metaInfo.size)
                                break;

                            void *srcPhyAddr = (void *)src->metaInfo.phy_addr;
                            void *dstPhyAddr = NULL;

                            if(!srcPhyAddr)
                                break;

                            if(des->mReplicaMetadata)
                                delete des->mReplicaMetadata;

                            des->mReplicaMetadata = new IonBuffer(IonBuffer::AllocBuffer, src->metaInfo.size,
                                    IonBuffer::SecureHeapMask, IonBuffer::HWIPACC);

                            dstPhyAddr = des->mReplicaMetadata->getPhyAddr();

                            if (!dstPhyAddr) {
                                delete des->mReplicaMetadata;
                                des->mReplicaMetadata = NULL;
                                ALOGE("[%s] create MetadataBuffer Failed! (copySize = %u)", __FUNCTION__, src->metaInfo.size);
                                break;
                            }

                            if (mProtectedOps->memcpy(dstPhyAddr, srcPhyAddr, (long) src->metaInfo.size & -1L) != 0)
                                break;

                            des->metaInfo.size = src->metaInfo.size;
                            des->metaInfo.phy_addr = (unsigned int)dstPhyAddr;
                            des->metaInfo.vir_addr = NULL;
                            des->mGralloc_version = src->mGralloc_version;
                        } while(0);

                    } else
#endif
                    {
	                    long long copySize;
	                    void * srcAddr = src->getVirAddr(&copySize);
	                    if (srcAddr) {
	                        des->mIonBuffer = new IonBuffer(IonBuffer::AllocBuffer, copySize);
	                        if (des->mIonBuffer->getVirAddr()) {
	                            memcpy(des->mIonBuffer->getVirAddr(), srcAddr, copySize);
	                            des->mState = Client::BufferReplica;
	                            ret = 0;
	                        } else {
	                            delete des->mIonBuffer;
	                            des->mIonBuffer = NULL;
	                            ret = -1;
	                            ALOGW("[%s] create IonBuffer failed! (copySize = %lld)", __FUNCTION__, copySize);
	                        }
	                    } else
	                        ret = -1;

                       GetMetadataInfo_t *metaInfo = src->getMetadataInfo();
                       memset((void *)&des->metaInfo, 0, sizeof(des->metaInfo));
                       if (src->mGralloc_version == 5 && metaInfo->size != 0) {
                           des->mReplicaMetadata = new IonBuffer(IonBuffer::AllocBuffer, metaInfo->size);
                           if (des->mReplicaMetadata->getVirAddr()) {
                               memcpy(des->mReplicaMetadata->getVirAddr(), metaInfo->vir_addr, metaInfo->size);
                               des->metaInfo.vir_addr = des->mReplicaMetadata->getVirAddr();
                               des->metaInfo.phy_addr = (unsigned long)des->mReplicaMetadata->getPhyAddr();
                               des->metaInfo.size = metaInfo->size;
                               des->mGralloc_version = src->mGralloc_version;
                               ret = 0;
                           } else {
                               delete des->mReplicaMetadata;
                               des->mReplicaMetadata = NULL;
                               ALOGE("[%s] create mReplicaMetadata failed! (size = %d)", __FUNCTION__, metaInfo->size);
                           }
                       }
                    }
                }
            }
        }
        src->unlockBuffer();
        des->unlockBuffer();
    }
    pthread_mutex_unlock(&mClientLock);
    return ret;
}

