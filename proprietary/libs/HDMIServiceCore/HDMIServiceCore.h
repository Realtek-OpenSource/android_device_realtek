#ifndef _REALTEK_HDMI_SERVICE_CORE_H_
#define _REALTEK_HDMI_SERVICE_CORE_H_

#include <pthread.h>
#include <rtk_ion.h>
#include <utils/threads.h>
#include <utils/Mutex.h>
#include <utils/Vector.h>
#include <utils/Errors.h>
#include <hardware/hardware.h>
#include "AudioRPCBaseDS_data.h"
#include "hdmitx/rtk_hdmi.h"
#include "osal_memory/osal_type.h"
#include "HdmiConstDef.h"
#include "HdmiCommon.h"
//#include "FactoryClient.h"
#include "HDCPCore.h"
#include "OneStepHelper.h"
#include "HDMICallback.h"
#include "ThreadWrapper.h"

#ifdef HAS_DPTX
#include "DPTxLib.h"
#endif

#define TV_VID_ARRAY_LENGTH     132
#define TV_3D_VIC_LENGTH        16
#define TV_SPEC_3D_LENGTH       18

#define  CTS_27M                0x01
#define  CTS_74M25              0x02
#define  CTS_148M5              0x03
#define  CTS_297M               0x04

#define HDMI_MODE_UNDEF	        0x00
#define HDMI_MODE_HDMI	        0x01
#define HDMI_MODE_DVI           0x02

#define  HDMI_SETAudioMute      0x01
#define  HDMI_CLRAudioMute      0x02

#define BOARD_NAME_BUF_LEN      128
//#define DOVI_V2_COLOR_MAP_LEN   8

using namespace android;

#ifdef HAS_DPTX
using namespace realtek;
#endif

namespace android_hdmi_hidl {

typedef struct _TV_SYSTEM_INFO {
    HDMI_VIC_ENUM   mVic;
    int32_t         mWidth;
    int32_t         mHeight;
    int32_t         mFps;
    bool            mProgressive;
} TV_SYSTEM_INFO;

typedef struct _VIC_VO_STANDARD_INFO {
    VO_STANDARD     mVoStandard;
    HDMI_VIC_ENUM   mVic;
    bool            m3D;
    bool            mFreqShift;
    int32_t         mColor;
} VIC_VO_STANDARD_INFO;

typedef struct _DV_BLOCK_INFO {
    int32_t mHasDV;
    int32_t mVersion;
    int32_t mSupport2160p60Hz;
    int32_t mSupportYUV422_12bit;
    // DOVI_V1_12:
    int32_t mLowLatency;
    // --

    // DOVI_V2:
    int32_t mInterfaceType;
    int32_t mSupports10b12b444;
} DV_BLOCK_INFO;

typedef struct dptx_event {
    int32_t mEvent;
    int32_t mVic;
    int32_t mType;
} dptx_event_t;

/**
 * Core class to provide HDMI service
 */
class HDMIServiceCore : public HDCPCallback 
#ifdef HAS_DPTX
                      , public dptxlib_module_callback_t
#endif
{

#ifdef HAS_DPTX

    class DPTxLibPollingThread : public ThreadWrapper {
    public:
        DPTxLibPollingThread(HDMIServiceCore *parent) { mParent = parent; }
        ~DPTxLibPollingThread(){}
    private:
        virtual bool            threadLoop();
        HDMIServiceCore *       mParent;
    };

    class DPTxEventProcessThread : public ThreadWrapper {
    public:
        DPTxEventProcessThread(HDMIServiceCore *parent) {
            mParent = parent;
            mRunning = true;
        }
        ~DPTxEventProcessThread() {}
        void                    signal();
        void                    stop();
        void                    queueEvent(dptx_event_t event);
    private:
        virtual bool            threadLoop();
        Mutex                   mLk;
        Condition               mSignal;
        HDMIServiceCore *       mParent;
        bool                    mRunning;
        Vector<dptx_event_t>    mEventQueue;
    };

#endif

    // Thread to process HDCP event.
    class HDCPEventThread : public ThreadWrapper {
    public:
        HDCPEventThread(HDMIServiceCore *parent);
        ~HDCPEventThread();
        void                    signal();
        void                    stop();
        void                    queueEvent(HDCP_EVENT event);
    private:
        virtual bool            threadLoop();
        Mutex                   mLk;
        Condition               mSignal;
        HDMIServiceCore*        mParent;
        bool                    mRunning;
        Vector<HDCP_EVENT>      mEventQueue;
    };

    // Thread to deliver HDMI Core event
    class EventThread : public ThreadWrapper {
    public:
        EventThread(HDMIServiceCore *parent);
        ~EventThread();
        void                    signal();
        void                    stop();
        void                    queueEvent(int32_t event);
    private:
        virtual bool            threadLoop();
        Mutex                   mLk;
        Condition               mSignal;
        HDMIServiceCore*        mParent;
        bool                    mRunning;
        Vector<int32_t>         mEventQueue;
    };

public:
    HDMIServiceCore(hdmi_core_module_callback_t *pCallback);
    ~HDMIServiceCore();

    HDCPCore *              mHDCPCore;
    OneStepHelper *         mOneStepHelper;

    Mutex                       mDPTxLibLock;
#ifdef HAS_DPTX
    DPTxLib *                   mDPTxLib;
    DPTxLibPollingThread *      mDPTxLibPollingThread;
    DPTxEventProcessThread *    mDPTxEventProcessThread;
#endif

    bool                    mDPTurnOffCompleted;

    HDCPEventThread *       mHDCPEventThread;
    EventThread *           mHDMICoreEventThread;

    // this lock might locked by outside
    Mutex                   mLock;

    void handleEvent(int32_t event);

    static void                 getVICInfoString(int32_t vic, char *pRst);
    static void                 dumpOutputFormat(HDMI_OUTPUT_FORMAT *fmt,
                                    const char *desc);

    // work-around for HDMI existing in system_server
    static HDMIServiceCore *    getInstance();

    status_t initHDMIDevice();
    status_t deinitHDMIDevice();

    // HDMI APIs (legacy APIs)
    status_t getSinkCapability();
    int32_t isSinkConnected();
    status_t getEDID(uint8_t *edidBuf);
    status_t sendAVMute(int32_t choice);
    //status_t configTVSystem(struct VIDEO_RPC_VOUT_CONFIG_TV_SYSTEM argp);
    //status_t configAVIInfoFrame(struct VIDEO_RPC_VOUT_CONFIG_HDMI_INFO_FRAME argp);
    //status_t setHDMIFrequency(int32_t videoCode, int32_t HDMIFrequency);
    //status_t sendAudioMute(int32_t select);
    //status_t sendAudioVSDBData(uint8_t latency[4], int32_t interlaced);
    //status_t sendAudioVSDBDataManual(int32_t delay);
    //int32_t checkLinkStatus();
    //int32_t checkRxSense();

    int32_t isEDIDReady();
    int32_t isHDMIDevice();
    int32_t getTVMaxLuminace();
    int32_t getTVSupportHDR();
    int32_t getTVSupportxvYCC();
    int32_t getTVSupportYCbCr();
    int32_t getTVSupportDeepColor();
    int32_t getTVSupportDeepColorYCbCr444();
    int32_t restartHDMI();
    int32_t getTVSupportHDCP();
	status_t HDCP_CkeckIfKeyExist();
	status_t SaveEDIDToTmp(uint8_t* edidBuf);

    status_t                    setOutputFormat(
                                    uint8_t vic,
                                    uint8_t freq_shift,
                                    COLOR_TYPE color,
                                    COLOR_TYPE color_depth,
                                    uint8_t _3d_format,
                                    uint8_t hdr,
                                    int32_t flags);

    status_t                    setOutputFormatViaHDR(
                                    HDMI_HDR_MODE hdr,
                                    int32_t flags);

    // check nothing, just call IOCTL directly
    status_t                    forceSetOutputFormat(HDMI_OUTPUT_FORMAT fmt,
                                    int32_t flags,
                                    bool fromDP);

    void                        saveEdidAutoMode(int32_t value);
    int32_t                     readEdidAutoMode();

    void                        saveColorModeEnum(int32_t value);
    int32_t                     readColorModeEnum();

    int32_t                     readHDRAutoProperty();

    void                        saveOutputFormat(const HDMI_OUTPUT_FORMAT &fmt,
                                    int32_t mode = SAVE_MODE_NAND);
    status_t                    readOutputFormat(HDMI_OUTPUT_FORMAT *pFmt);

    //status_t                  readOneStepInfo(ONE_STEP_INFO *pInfo);
    //status_t                  validateOneStepInfo(ONE_STEP_INFO *pInfo);

    status_t                    getCurrentOutputFormat(HDMI_OUTPUT_FORMAT *pFmt);
    void                        hdcpGetCurrentOutputFormat(HDMI_OUTPUT_FORMAT *pFmt);

    bool                        isOutputFormatSupported(HDMI_OUTPUT_FORMAT *pFmt);
    bool                        checkSupport(HDMI_OUTPUT_FORMAT *pFmt,
                                    struct hdmi_format_support *pSupport);

    //status_t                  setOutputFormat2(HDMI_OUTPUT_FORMAT *pFmt);
    status_t                    turnOffHDMI(bool fromDP=false);
    status_t                    turnOnHDMI(bool fromDP=false);
    //status_t                  findAutoOutputFormat(HDMI_OUTPUT_FORMAT *pRst);
    status_t                    findAutoOutputFormat(HDMI_OUTPUT_FORMAT *pRst,
                                    HDMI_HDR_MODE hdr);

    int32_t                     sourceVIC(HDMI_VIC_ENUM vic, HDMI_HDR_MODE hdr);
    TV_SYSTEM_INFO *            findTvSystemInfo(HDMI_VIC_ENUM vic);

    void                        dumpEDIDSupportList();
    struct hdmi_support_list *  getEDIDSupportList() { return &mEDIDSupportList; }
    int32_t                     readHDMIPlugged();
    void                        setHDREotfMode(int32_t mode);
    HDMI_HDR_MODE               getCurrentHDRMode();
    HDMI_HDR_MODE               getFactoryHDRMode();

    void                        resolveColorSet(
                                    COLOR_TYPE *pColor,
                                    COLOR_TYPE *pColorDepth,
                                    int32_t vic,
                                    HDMI_HDR_MODE hdr,
                                    int32_t policy);

    void                        findColorSet(
                                    COLOR_TYPE *pColor,
                                    COLOR_TYPE *pColorDepth,
                                    int32_t vic,
                                    HDMI_HDR_MODE hdr);

    status_t                    getAutoColorMode(
                                    COLOR_TYPE *pColor,
                                    COLOR_TYPE *pColorDepth,
                                    struct hdmi_format_support *pSupport);

    status_t                    getAutoDeepColorMode(
                                    COLOR_TYPE *pColor,
                                    COLOR_TYPE *pColorDepth,
                                    HDMI_HDR_MODE hdr,
                                    struct hdmi_format_support *pSupport);

    bool                        simpleColorSupportCheck(
                                    COLOR_TYPE color,
                                    COLOR_TYPE color_depth_mask,
                                    struct hdmi_format_support *pSupport);
    void                        getCurrentColorSet(
                                    COLOR_TYPE *pColor,
                                    COLOR_TYPE *pColorDepth);

    bool                        isUnderDoviMode(HDMI_HDR_MODE hdr);
    bool                        checkHDRModeSupported(HDMI_HDR_MODE hdr);

    void                        setHDMIEnable(int32_t enable);

    status_t                    setHDMIFormat3D(int32_t format3d, float targetFps);

    struct sink_capabilities_t *getTVCapInfo();

    void                        onHDCPEvent(int32_t version, int32_t event);
    void                        onHDCPEventLock(int32_t version, int32_t event);
    void                        queueHDCPEvent(HDCP_EVENT event);

    int32_t                     tryAcquireLock(int32_t type);
    void                        acquireLock(int32_t type);
    void                        releaseLock(int32_t type);

    status_t                    setHDCPVersion(int32_t version);
    status_t                    getHDCPVersion(int32_t *version);
    status_t                    getConfiguredHDCPVersion(int32_t *version);

    void                        waitHDCPAuthState();
    status_t                    getConfigTVSystem(struct VIDEO_RPC_VOUT_CONFIG_TV_SYSTEM *pConf);
private:

    char                        mBoardName[BOARD_NAME_BUF_LEN];
    int32_t                     mHDMIEnabled;

    pthread_mutex_t             mutex;
    pthread_mutex_t             hotplug_mutex;

    static HDMIServiceCore *    sInstance;
	struct hdmi_device_t *      mHDMIDevice;
    struct hdmi_support_list    mEDIDSupportList;
    DV_BLOCK_INFO               mDVBlockInfo;

    // event from HDMICore to HIDL interface
    hdmi_core_module_callback_t *mCallback;
    int32_t                     mDPTxSession;

    // HDMI capability info (legacy members)
    uint32_t                    SET_HDMI_Frequency_To_Audio;
    bool                        mEDIDReady;
    int32_t                     mHDMIStatus;
    int32_t                     mTVSupportDeepColor;
    int32_t                     mTVSupportYCbCr;
    int32_t                     mTVSupportxvYCC;
    int32_t                     mTVSupportDeepColorYCbCr444;
    int32_t                     mTVVidLength;
    int32_t                     mArrTVVid[TV_VID_ARRAY_LENGTH];
    int32_t                     m3DPresent;
    uint8_t                     mArr3DStructure[2];
    uint8_t                     mArr3DVic[TV_3D_VIC_LENGTH];
    uint8_t                     mArrSpec3D[TV_SPEC_3D_LENGTH][2];
    uint16_t                    mHdmiSourceAddress;
    int32_t                     mArrTVVid420[TV_VID_ARRAY_LENGTH];
    int32_t                     mTVVid420Length;
    int32_t                     mTVSupportHDR;
    int32_t                     mTVMaxLuminace;
    bool                        mSupportHDR;
    HDMI_HDR_MODE               mManualHDREotfMode;
    int32_t                     mDefaultColorMode;
    int32_t                     mDoviChipBonding;
    //struct AUDIO_HDMI_OUT_EDID_DATA2 mAudioHDMIEdidData2;

    dptx_event_t                mDPTxEvent;

    OSAL_S32                    ionfd;

    status_t                    extractVID(uint64_t value,
                                    uint64_t value2,
                                    uint64_t value2_420,
                                    uint8_t extended_value);

    status_t                    checkVID(uint64_t value,
                                    int32_t vid);

    status_t                    updateADBToAudio(int32_t enable);
	void *                      RTKIon_alloc(OSAL_U32 size,
                                    OSAL_U8 **noncacheable,
                                    OSAL_U32 *phys_addr,
                                    ion_user_handle_t *ionhdl);

	void                        RTKIon_free(void *addr,
                                    OSAL_U32 size,
                                    ion_user_handle_t *ionhdl);

    const char *                findVICName(HDMI_VIC_ENUM id);

    status_t                    readEDIDSupportList();
    status_t                    clearEDIDSupportList();

    VO_STANDARD                 getVOStandard(HDMI_OUTPUT_FORMAT format);
    void                        applyCurrentOutputFormat2Property();

    struct hdmi_format_support *getHDMIFormatSupport(int32_t vic);
    bool                        ignoreDolbyVision();
    bool                        deepColorFirst();
    int32_t                     getIntProperty(const char *property,int32_t _dft);
    void                        writeEDIDChecksum();
    bool                        halSetOutputFormat(
                                    struct hdmi_format_setting setting,
                                    bool ignoreCurrent,
                                    bool doCheckSupport,
                                    bool fromDP);

    void                        statusDump();
    bool                        parseDVBlock(
                                    uint8_t *edid,
                                    int32_t edid_size,
                                    DV_BLOCK_INFO *pInfo);

    // mode: DVI or HDMI
    int32_t                     resolveOutputMode();
    HDMI_HDR_MODE               resolveAutoHDRMode();

    const char *                getDoviVersionStr(DV_BLOCK_INFO *pInfo);
    //HDMI_HDR_MODE             convertAutoHDRMode(HDMI_HDR_MODE hdr);

    void                        resolveColorSetOfDovi(
                                    HDMI_HDR_MODE hdr,
                                    COLOR_TYPE *pColor,
                                    COLOR_TYPE *pColorDepth);

    int32_t                     sourceDoviTVSystemColorSet(
                                    HDMI_VIC_ENUM vic,
                                    HDMI_HDR_MODE hdr,
                                    COLOR_TYPE color,
                                    COLOR_TYPE depth);

    HDMI_HDR_MODE               readFactoryHDRMode();

    HDMI_HDR_MODE               resolveAutoDoviHDRMode();

    HDMI_3D_MODE                convert3DMode(int32_t format3d);
    bool                        support3DMode(HDMI_3D_MODE mode, int32_t bits);
    status_t                    getDisplayInfoViaVic(HDMI_VIC_ENUM vic,
                                    int32_t *pFps,
                                    int32_t *pWidth,
                                    int32_t *pHeigh,
                                    int32_t *pProgressive);

    status_t                    runtimeSet3DOutputFormat(
                                    HDMI_VIC_ENUM vic,
                                    int32_t format3d,
                                    int32_t freqShift3D);

    int32_t                     resolveHDCPDelay();
    int32_t                     compareEDIDChecksum();
    void                        switchToHDMIEDIDAutoMode();
    //void                      dumpOneStepInfo(ONE_STEP_INFO *pInfo);

    void                        resolveTurnOnHDMIPolicy(bool sameTv,
                                    bool savedFormatSupported,
                                    bool hasRuntimeFormat,
                                    int edidMode,
                                    bool * autoMode,
                                    int * newEdidMode);

    void                        getBoardName();
    INTERFACE_TYPE              resolveDisplayMode(bool hdmiOn);

    int32_t                     checkChipDoviBonding();
    bool                        isDiffSourceOn();
    void                        notifyDPTx(int32_t event);
    void                        waitDPTxComplete(bool on);
    void                        waitDPTxCompleteViaEvent(bool on);
    bool                        _dpIsOn(INTERFACE_TYPE type);
    bool                        isIgnoreEDID();

#ifdef HAS_DPTX
    DPTxLib *                   getDPTxLib();

public:
    static void                 dptxEventHandler(
                                    const struct dptxlib_module_callback * callback,
                                    int32_t event,
                                    int32_t vic,
                                    int32_t type);

    void                        onDPTxEvent(dptx_event_t e);
#endif

};

}; // namespace android_hdmi_hidl

#endif // _REALTEK_HDMI_SERVICE_CORE_H_
