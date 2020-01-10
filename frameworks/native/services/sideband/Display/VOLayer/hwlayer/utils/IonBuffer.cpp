#include "IonBuffer.h"

IonBuffer::IonBuffer(enum IonOper oper, long long oper_data, unsigned int heap_mask, unsigned int flag_mask)
    : mIonFd(-1),
    mIonMmapFd(-1),
    mViraddr(MAP_FAILED),
    mPhyaddr(NULL),
    mSize(0),
    mIonHandle(0),
    mHeapMask(heap_mask),
    mFlagMask(flag_mask)
{
    switch (oper) {
        case AllocBuffer:
            allocBuffer(oper_data);
            break;
        case ImportBuffer:
            importBuffer((int)oper_data, false);
            break;
        case ImportBuffer_lock:
            importBuffer((int)oper_data, true);
            break;

    };
}

IonBuffer::~IonBuffer()
{
    freeBuffer();
}

int IonBuffer::sync() {
    int ret = -1;
    if (mIonFd != -1 && mIonMmapFd != -1)
        ret = ion_sync_fd(mIonFd, mIonMmapFd);
    else
        ALOGE("[%s] mIonFd=%d mIonMmapFd=%d", __func__, mIonFd, mIonMmapFd);
    return ret;
}

void IonBuffer::allocBuffer(long long bufferSize) {
    int ret = -1;
    unsigned int ion_heap_mask = 0;
    unsigned int ion_heap_flag = 0;

    if (mSize > 0) {
        ALOGW("[%s] bufferSize=%lld mSize=%lld", __func__, bufferSize, mSize);
        freeBuffer();
    }

    ion_heap_mask |= (mHeapMask & MediaHeapMask )?  RTK_PHOENIX_ION_HEAP_MEDIA_MASK :0;
    ion_heap_mask |= (mHeapMask & AudioHeapMask )?  RTK_PHOENIX_ION_HEAP_AUDIO_MASK :0;
    ion_heap_mask |= (mHeapMask & SecureHeapMask)?  RTK_PHOENIX_ION_HEAP_SECURE_MASK:0;

    ion_heap_flag |= (mFlagMask & NONCACHED )?  ION_FLAG_NONCACHED  :0;
    ion_heap_flag |= (mFlagMask & SCPUACC   )?  ION_FLAG_SCPUACC    :0;
    ion_heap_flag |= (mFlagMask & ACPUACC   )?  ION_FLAG_ACPUACC    :0;
    ion_heap_flag |= (mFlagMask & HWIPACC   )?  ION_FLAG_HWIPACC    :0;
    ion_heap_flag |= (mFlagMask & PROTECTED )?  ION_USAGE_PROTECTED :0;
    ion_heap_flag |= (mFlagMask & SECURE_AUDIO  )?  ION_FLAG_SECURE_AUDIO :0;

    mIonFd = ion_open();

    if (mIonFd >= 0)
        ret = ion_alloc(mIonFd, bufferSize,
                0, /* align */
                ion_heap_mask,
                ion_heap_flag,
                &mIonHandle);

    if (ret == 0) {
        ion_share(mIonFd, mIonHandle, &mIonMmapFd);
        ion_phys(mIonFd, mIonHandle, (unsigned long *)&mPhyaddr, (unsigned int *)&mSize);
        mViraddr = mmap(NULL, mSize, PROT_READ | PROT_WRITE, MAP_SHARED, mIonMmapFd, 0);
    } else {
        ALOGE("[%s] ion alloc failed! heap=0x%x flag=0x%x size=%lld IonFd=%d (ret=%d)", __func__,
                ion_heap_mask, ion_heap_flag, bufferSize, mIonFd, ret);

        if (mIonFd != -1) {
            ion_close(mIonFd);
            mIonFd = -1;
        }
    }

}

void IonBuffer::importBuffer(int import_fd, bool lock) {
    int ret = -1;

    if (mSize > 0) {
        ALOGW("[%s] import_fd=%d mSize=%lld", __func__, import_fd, mSize);
        freeBuffer();
    }

    mIonFd = ion_open();

    if (mIonFd >= 0)
        ret = ion_import(mIonFd, import_fd, &mIonHandle);

    if (ret == 0) {
        ion_share(mIonFd, mIonHandle, &mIonMmapFd);
        if (!lock) {
            ion_phys(mIonFd, mIonHandle, (unsigned long *)&mPhyaddr, (unsigned int *)&mSize);
            mViraddr = mmap(NULL, mSize, PROT_READ | PROT_WRITE, MAP_SHARED, mIonMmapFd, 0);
        } else
            mSize = 1;
    } else {
        ALOGE("[%s] ion import failed! IonFd=%d import_fd=%d (ret=%d)", __func__,
                mIonFd, import_fd, ret);

        if (mIonFd != -1) {
            ion_close(mIonFd);
            mIonFd = -1;
        }
    }

}

void IonBuffer::freeBuffer() {
    if (mSize > 0) {
        if (mIonMmapFd != -1)
            close(mIonMmapFd);

        if (mViraddr != MAP_FAILED)
            munmap(mViraddr, mSize);

        if (mIonFd >= 0) {
            ion_free(mIonFd, mIonHandle);
            ion_close(mIonFd);
            mIonFd = -1;
        }
        mPhyaddr = NULL;
        mSize = 0;
    }
}

void IonBuffer::flushBuffer() {
    if (mIonMmapFd != -1 && mIonFd != -1)
        ion_flush_fd(mIonFd, mIonMmapFd);
}
