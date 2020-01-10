#ifndef _VODEINTERLACE_HELPER_H_
#define _VODEINTERLACE_HELPER_H_

#include <utils/Mutex.h>
#include <utils/threads.h>
//#include <utils/Vector.h>
#include <utils/KeyedVector.h>
//#include <hardware/gralloc.h>

#include "hresult.h"
#include "VideoRPCBaseDS.h"
#include "VideoRPC_System.h"

//#include "RPCBaseDS_data.h"
//#include "AudioRPC_System.h"
//#include "AudioRPC_Agent.h"

#include "VideoRPC_Agent.h"
#include "RPCProxy.h"
#include "InbandAPI.h"

#include "allocator/Allocator.h"
#include "allocator/IonAllocator.h"
#include "allocator/MallocAllocator.h"
#include "hardware/GrallocWrapper.h"

#include "system/RingBuffer.h"
#include "system/RingBufferBody.h"
#include "system/RingBufferHeader.h"

#include "Debug.h"
#include "DeInterlaceCallback.h"

#define USE_V1_BIT      1
#define USE_V2_Bit      0

using namespace android;

/**
 * A basic class to wrapp some vo deinterlace RPC flow.
 * Author: bruce_huang@realtek.com
 * Date: 2019.02.12
 *
 * Standard code flow
 * - init()
 * - start()
 * - stop()
 */
class VoDeInterlaceHelper {

    /**
     * A simple wrapper class to fill up some routine stuff.
     */
    class WorkerCore : public Thread {

    public:
        WorkerCore(VoDeInterlaceHelper *parent, const char *name)
        {
            mRunning = true;
            mParent = parent;
            mName = name;
        }

        virtual ~WorkerCore();

        // implemented by child class.
        virtual bool            loopFunc() = 0;

        const char *            mName;
        bool                    mRunning;
        VoDeInterlaceHelper *   mParent;
        Mutex                   mWorkerLock;
        Condition               mWorkerSignal;

        bool threadLoop() {
            return loopFunc();
        }

        void start() {
            run(mName);
        }

        void stop() {
            mRunning = false;
            signal();
            requestExitAndWait();
        }

        void signal() {
            Mutex::Autolock l(mWorkerLock);
            mWorkerSignal.signal();
        }
    };

    class BufferQueue {
    public:
        BufferQueue() {}
        ~BufferQueue() {}

        KeyedVector<uint64_t,buffer_handle_t>   mBuffers;

        Mutex                                   mLock;
        Condition                               mSignal;

        status_t        queueBuffer(uint64_t idx, buffer_handle_t buffer);
        status_t        removeBuffer(uint64_t key);
        buffer_handle_t valueFor(uint64_t key);

        int32_t         size() { return (int32_t) (mBuffers.size()) ; }
    };

    class TranscodeWorker : public WorkerCore {
    public:
        TranscodeWorker(VoDeInterlaceHelper *parent, const char *name)
        : WorkerCore(parent,name) {

            mInputIdx = 0;
            mOutputIdx = 0;

            mActFrameIdx = 1;   // start from 1
            mActOutputIdx = 0;

            mInputFrames = new BufferQueue();
            mOutputFrames = new BufferQueue();

        }

        ~TranscodeWorker();

        BufferQueue *   mInputFrames;
        BufferQueue *   mOutputFrames;

        // simple counter to tracking input / output buffers
        uint64_t        mInputIdx;
        uint64_t        mOutputIdx;

        uint64_t        mActFrameIdx;
        uint64_t        mActOutputIdx;

        bool            loopFunc();
        bool            hasBuffers();
    };

    class WritebackWorker : public WorkerCore {
    public:
        WritebackWorker(VoDeInterlaceHelper *parent, const char *name)
        : WorkerCore(parent,name) {}

        ~WritebackWorker();

        bool loopFunc();
    };

public:
    VoDeInterlaceHelper(
            DeInterlaceCallback *callback,
            int32_t width,
            int32_t height,
            int32_t planBit);

    ~VoDeInterlaceHelper();

    status_t                init();
    status_t                start();
    status_t                stop();

    status_t                queueInputFrame(const buffer_handle_t &input);
    status_t                queueOutputBuffer(const buffer_handle_t &output);

private:
    CLNT_STRUCT                 clnt;
    uint32_t                    mVOId;

    int32_t                     mWidth;
    int32_t                     mHeight;
    int32_t                     mPlanBit;

    bool                        mStarted;

    DeInterlaceCallback *       mCallback;

    GrallocWrapper *            mGrallocWrapper;

    RingBuffer *                mTranscodeInbandRing;
    RingBuffer *                mWritebackInbandRing;

    sp<TranscodeWorker>         mTranscode;
    sp<WritebackWorker>         mWriteback;

    status_t                create();
    status_t                destroy();
    status_t                stopVo();
    status_t                release();
    status_t                run();
    status_t                startWorkers();

    RingBuffer *            allocRingBuffer(
                                int32_t size,
                                int32_t flag);

    status_t                allocInbandCmdRings();

    status_t                initInbandCmdRing(
                                RingBuffer *pRingBuffer,
                                int32_t pinID);

    // called by mTranscode worker
    status_t                deliverBuffers(
                                uint64_t idx,
                                uint64_t outIdx,
                                buffer_handle_t prev,
                                buffer_handle_t curr,
                                buffer_handle_t next,
                                buffer_handle_t out);

    status_t                convertBufferToTranscodeObject(
                                uint64_t idx,
                                uint64_t outIdx,
                                buffer_handle_t prev,
                                buffer_handle_t curr,
                                buffer_handle_t next,
                                buffer_handle_t out,
                                VIDEO_TRANSCODE_PICTURE_OBJECT *pObj);

    status_t                resolveAddrInfo(
                                buffer_handle_t buf,
                                uint32_t *pPhyAddr,
                                android_ycbcr *pYCbCr);

    uint32_t                sendInbandCmd(
                                RingBuffer *pRing,
                                void *cmd_endian_swapped,
                                uint32_t cmd_size);

    status_t                processWritebackObj(
                                VIDEO_WRITEBACK_PICTURE_OBJECT *pObj);
};

#endif
