#ifndef SP_INFO_H
#define SP_INFO_H

#if 1
//#if defined(__LINARO_SDK__)
#include "RPCBaseDS_data.h"
#include "VideoRPC_System_data.h"
#include "AudioRPCBaseDS_data.h"
#endif

#ifdef LOCAL_BUILD_SP   // RPC
//#include "RPCProxy.h"
#include "VideoRPCBaseDS.h"
#include "VideoRPC_System_data.h"
#include "AudioRPCBaseDS_data.h"
#include "hresult.h"
#include "AudioRPC_System.h"
#include "AudioInbandAPI.h"
#include "InbandAPI.h"
#endif
#include "sp_const_def.h"
#include "rtk_ion.h"

////////////
// define //
////////////
#define SP_EnqueueRPCRing(a, b) (a)->SP_EnqueueRPCRing_func(b)
#define VP_memcpy memcpy
#define SPU_RPC_PREPARE_CLNT(A, B, C)	prepareCLNT(A, B, C)

#if SP_TRACE_ENABLE
//#define SP_TRACE(fmt, args...) \ALOGD("[SP]%s:", fmt, __FUNCTION__, ##args);

#define SP_TRACE(fmt, args...) \
{\
    char buf[256], temp[256];\
    sprintf(temp, fmt, ##args); \
    sprintf(buf, "[SP]%s:", __FUNCTION__); \
    strcat(buf, temp); \
    ALOGD("%s", buf); \
}

#define SP_TRACE_RPC(rpc_type, func, line) { \
        char rpc_name[10][20]  = {"Create", "InitRingBuf", "Destroy", "Stop", "Run", "Enable", "Show", "Hide", "Flush", "Config"}; \
        ALOGD("[SP] %s @ %s %d\n", rpc_name[rpc_type], func, line); }
#define SP_PRINT_RING_PTR_NOW(p) (p)->SP_PrintRingPtrNow()
#else
#define SP_TRACE(format, ...)
#define SP_TRACE_RPC(rpc_type, func, line)
#define SP_PRINT_RING_PTR_NOW(p)
#endif

#define SP_WARNING(fmt, args...)   ALOGD("[SP WARN]%s:" fmt, __FUNCTION__, ##args);

//////////
// enum //
//////////
enum {
    ENUM_ABNORMAL_0_PACKET = 0,
};

typedef enum
{
    SP_RPC_CREATE = 0,
    SP_RPC_INIT_RING_BUF,
    SP_RPC_DESTROY,
    SP_RPC_STOP,
    SP_RPC_RUN,
    SP_RPC_ENABLE,
    SP_RPC_SHOW,
    SP_RPC_HIDE,
    SP_RPC_FLUSH,
    SP_RPC_CONFIG_RESOLUTION,
} SP_RPC_TYPE ;

typedef enum
{
    ENUM_SP_NONE = 0,
    ENUM_SP_DVD_TYPE,
    ENUM_SP_DVB_TYPE,
    ENUM_SP_BD_TYPE,
    ENUM_SP_DUMMY_TYPE
} SP_DECODE_TYPE;

typedef enum
{
    VP_OBJ_STREAM_TYPE,
    VP_OBJ_PICTURE_TYPE,
    VP_OBJ_PICTURE_422_TYPE,
    VP_OBJ_SMBUFFER_PICTURE_TYPE,
    VP_OBJ_JPEG_PICTURE_TYPE,

    VP_MSG_EOS_TYPE,

    /* common commands */
    VP_CMD_COMMON_RUN_TYPE,
    VP_CMD_COMMON_PAUSE_TYPE,
    VP_CMD_COMMON_STOP_TYPE,
    VP_CMD_COMMON_INIT_RING_BUF_TYPE,
    VP_CMD_COMMON_CREATE_TYPE,
    VP_CMD_COMMON_DESTROY_TYPE,
    VP_CMD_COMMON_FLUSH_TYPE,

    /* decoder commands */
    VP_CMD_DEC_SET_CCBYPASS_MODE_TYPE,
    VP_CMD_DEC_SET_DNR_MODE_TYPE,

    /* VscaleToRGB commands */
    VP_CMD_VSCALE_TORGB_SETUP_TYPE,

    /* JpegDecInband commands */
    VP_CMD_JPEGDEC_INBAND_INIT_TYPE,
    VP_CMD_JPEGDEC_INBAND_INIT_ICQ_TYPE,
    VP_CMD_JPEGDEC_INBAND_SEM_TYPE,

    /* transition commands */
    VP_CMD_TRANSITION_SETUP_TYPE,

    VP_OBJ_DVD_SP_TYPE,
    VP_OBJ_DVB_SP_REGION_TYPE,
    VP_OBJ_DIVX_SP_TYPE,
    VP_OBJ_BD_SP_PAGE_TYPE,

    /* scaler commands */
    VP_CMD_SCALER_SETUP_TYPE,

    /* for switch DivX3 and MJPEG in DIVX3 component */
    VP_CMD_DIVX3_SWITCH_TO_DIVX3,
    VP_CMD_DIVX3_SWITCH_TO_MJPEG,

    /* for Scaler component in small buffer mode */
    VP_CMD_SCALER_HOR_SCALING_TYPE,

    /* smooth level for scaling */
    VP_CMD_SMOOTH_LEVEL_TYPE,

    /* thumbnail commands */
    VP_CMD_THUMBNAIL_SET_THRESHOLD_TYPE,
    VP_CMD_THUMBNAIL_SET_STARTPIC_TYPE,

    /*  image command */
    VP_CMD_IMG_DECODE_TYPE,

    /* send buffer to scaler */
    VP_OBJ_PICTURE_SCALER_START_TYPE,
    VP_OBJ_PICTURE_SCALER_BUFFER_TYPE,
    VP_OBJ_PICTURE_SCALER_END_TYPE,           /* decode success */
    VP_OBJ_PICTURE_SCALER_FAIL_TYPE,          /* Maybe decoder detects something wrong in the middle, we won't show picture */
    VP_OBJ_PICTURE_SCALER_REALPIC_TYPE,
    VP_OBJ_PICTURE_SCALER_UNSUPPORT_SIZE_TYPE,  /* memory isn't enough to decode this picture, e.g.: big progressive jpeg */

    /*flash decoder command*/
    VP_CMD_FLASH_SETOUTPUT,

    /* add all your definitions above this line */
    VP_PACKET_NUM_MAX
} VP_PACKET_TYPE ;

typedef enum
{
    VIDEO_COMPONENT_STOP = 0,
    VIDEO_COMPONENT_RUN,
    VIDEO_COMPONENT_PAUSE,
    VIDEO_COMPONENT_CREATED
} VP_COMPONENT_STATE;

typedef enum
{
    VF_STATUS_STOP = 0,
    VF_STATUS_RUN,
    VF_STATUS_PAUSE
} VF_STATUS ;

enum
{
    SP_ION_FILTER_IDX = 0,
    SP_ION_DECODER_IDX,

    SP_ION_SEG_NUM
};

////////////
// struct //
////////////
class SP_INFO;
typedef struct tagVP_COMPONENT VP_COMPONENT ;
typedef struct tagFILTER FILTER ;

typedef struct  {
    long base;
    long limit;
    long wp;
    long rp;
} SP_RINGBUF;

typedef struct
{
    unsigned int memblk_start_addr ;
    unsigned int freeblk_start_addr ;
    unsigned int size ;
    int owner_id ;

} MEM_BLK_INFORMATION ;

typedef struct
{
    VP_PACKET_TYPE type ;
    unsigned char  sender ;    /* ID of the task from which the packet is sent */
    unsigned char  receiver ;  /* ID of the task to which the packet is addressed */
    unsigned short len ;       /* The total length of the header plus the struct in payLoad[] */

    unsigned long long payLoad[VP_PACKET_DWORD_SIZE - 1] ;    // 120 Bytes
} VP_STREAM_PACKET ;

typedef struct
{

    unsigned int  Qread ;
    unsigned int  Qwrite ;
    unsigned int  Qsize ;

    VP_STREAM_PACKET *Q ;

    int  boundPin ;
    VP_COMPONENT *boundFilter ;
} VP_IO_PIN ;

struct tagVP_COMPONENT
{
    // do not reorder the part. this part should be the same as the beginning of the filter.
    unsigned char numPins ;
    char taskID ;

    int (*Receive)     (VP_COMPONENT *, VP_STREAM_PACKET *recvPkt, int pin, int bSuspend) ;
    int (*Bind)        (VP_COMPONENT *, VP_COMPONENT *boundComp,   int thisPin, int boundPin) ;
    // end of non-reorder part

    /* component functions */
    int (*Run)        (VP_COMPONENT *) ;
    int (*Reset)      (VP_COMPONENT *) ;
    int (*Query)      (VP_COMPONENT *, int queryWhat, int arg0, int arg1) ;
    int (*Init)       (VP_COMPONENT *, void *init) ;
    int (*Destroy)    (VP_COMPONENT *) ;
    int (*ReceiveCmd) (VP_COMPONENT *, VP_STREAM_PACKET *cmd) ;
    int (*Poll)       (VP_COMPONENT *) ;

#ifdef VP_MEMORY_CHECK
    unsigned  comp_context_start;
    unsigned  comp_context_end;
#endif
    /* ROS Semaphore used betwee ProcCmd() and ReceiveCmd() */
#if SP_DATA_STRUCTURE_SIZE_SYNC_WITH_VO
    void *padding0;
    void *padding1;
#else
//  ROS_EVENT  *sem ;
//  VP_TASK_STACK *task_stack ;
#endif

    /* component data */
    char name[32] ;


    unsigned char numInPins ;
    unsigned char numOutPins ;
    int           tag;
    VP_COMPONENT_STATE  state ;

    VP_IO_PIN  *pin ;
    void       *data ;
    SP_INFO *pSpInfo;
#if SP_DATA_STRUCTURE_SIZE_SYNC_WITH_VO
#ifdef RPC_SUPPORT_MULTI_CALLER
    unsigned long sysPID;
#endif
#endif
} ;

typedef struct
{
    long filter ;
    long filter_pinID ;
} Connectable_Param ;

typedef struct
{
    VP_COMPONENT *comp ;
    int comp_pinID ;
} Connectable ;

struct tagFILTER
{
    // do not reorder the part. this part should be the same as the beginning of the filter.
    unsigned char numPins ;
    char taskID ;

    int (*Receive)     (VP_COMPONENT *, VP_STREAM_PACKET *recvPkt, int pin,     int bSuspend) ;
    int (*Bind)        (VP_COMPONENT *, VP_COMPONENT *boundComp,   int thisPin, int boundPin) ;
    // end of non-reorder part

    HRESULT (*Run)		        (FILTER *) ;
    HRESULT (*Stop)		        (FILTER *) ;
    HRESULT (*Pause)          (FILTER *) ;
    HRESULT (*Destroy)        (SP_INFO*, FILTER *) ;
    HRESULT (*Flush)	        (SP_INFO*, FILTER *) ;
    HRESULT (*SetRefClock)    (FILTER *, long pRefClock) ;
    HRESULT (*InitRingBuffer) (SP_INFO *, FILTER *, RINGBUFFER_HEADER *ring) ;

    /* from system software's view, they command filters connect.
       However, the basic concept of connection is built between VP_COMPONENT
       We design a function to get the connectable VP_COMPONENT
       FILTER should return a connectable VP_COMPONENT according to asker filter's type.
       The selection is up to each filter's internal implementation. */
    HRESULT (*getConnectable) (Connectable_Param* self, Connectable_Param* asker, Connectable* con) ;
    HRESULT (*ProcCmd)        (FILTER *, VP_STREAM_PACKET *cmd) ;

    /* filter attribute */
    VF_STATUS      status ;
    VIDEO_VF_TYPE  type ;
    VP_COMPONENT   *des_comp; /*pointer where current filter connect to next component,
                             Note: only componet can connect each other */
    int            des_pinNum; /*pin number that connect to the destination*/
    int            tag;
    unsigned char  ringbuf_counter;
    RINGBUFFER_HEADER ringbuf[5];

#if SP_DATA_STRUCTURE_SIZE_SYNC_WITH_VO
    void *padding;
#else
//  ROS_EVENT*      rpc_sem;  /* Semaphore to prevent RPC re-entrance */
#endif
} ;

typedef struct
{
    FILTER  filter ;

    SP_STREAM_TYPE  streamType ;
    VP_COMPONENT    decComp ;
//  VO_CHANNEL     *voChannel ;

    int mtagDecoder ;

} FILTER_SPDEC ;

typedef struct
{
    ION_HDL *hdl_ion;
    ION_DATA argb_raw_ion;  // 3840 * 2160 * 4
    int src_width;
    int src_height;
    int dst_width;
    int dst_height;
}SP_SCALE_INFO;

typedef struct VP_BUFFER
{
    char      usage;
#ifdef VP_MEMORY_CHECK
    char      cs_status;
#endif
    void      *ptr;
#ifdef VP_MEMORY_CHECK
    int       size;
    unsigned  checksum;
    struct VP_BUFFER *next;
#endif
    unsigned char taskID ;
} VP_BUFFER;

class SP_INFO
{
public:
    SP_INFO(void *);
    ~SP_INFO();
    MEM_BLK_INFORMATION  memblk_info[MAX_TAG_NUM] ;
    SP_RINGBUF BS_ring;
    SP_RINGBUF ICQ_ring;
    SP_RINGBUF RPC_ring;
    FILTER_SPDEC *pFilter;
    pthread_t nThread;
    VIDEO_RPC_SUBPIC_DEC_CONFIGURE nConfig;
    RINGBUFFER_HEADER *BS_HDR;  // endian change
    RINGBUFFER_HEADER *ICQ_HDR; // endian change
    int nSem;
    int bGetDestoryCmd;
    int RPC_buf[RPC_BUF_SIZE];  // for RPC_ring

    /* ION */
    ION_DATA m_ion[SP_ION_SEG_NUM];
    unsigned int ion_cur_seg;
    unsigned int ion_used_size[SP_ION_SEG_NUM];
    /* ION */
    
    unsigned char *BS_ring_base;
    unsigned char *ICQ_ring_base;
    unsigned int alwaysOnTop;
    unsigned int spFullWidth;
    unsigned int spFullHeight;
    SP_DECODE_TYPE codec_type;
    void *pVO_Filter;   // this address is big-endian, it doesn't need to do endian_change when send to VO.
    void *pRVSD;
    int   *pWaitUnlockByVO;    /* for blocking, when subtitle-decoder send decoded-object to VO. */
    int BS_ring_size;
    int ICQ_ring_size;
    int BS_fd;
    int ICQ_fd;
    int BS_base_fd;
    int ICQ_base_fd;
    int nAbnormalExit;	// bitwise operations
    int bInitRingBuf;
    int used_tag_number;
    long FlushBSWp;
    long FlushICQWp;
//    SP_SE_INFO *se;
    SP_SCALE_INFO *se_scale;

    // Function
#if SP_USE_ION_MEMORY
    void *VP_malloc_func(unsigned int size);
#endif
    void VP_memblk_init(void);
    int VP_memblk_request (unsigned int size, int owner_id);
    void *VP_memblk_alloc (unsigned int size, int tag_id);
    void VP_memblk_release (int tag_id);
    void SP_IONUseDefaultDecoder();
    void SP_IONReuseDecoder();
    void SP_SuspendTask(int type);
    void SP_ForceResume();
    void SP_ResumeTask(int type);
    void VP_ReleaseMem (VP_BUFFER *buf);
    void SP_UpdateICQWp();
    void SP_UpdateBSWp();
    void SP_UpdateICQRp();
    void SP_UpdateBSRp();
    void VP_memblk_free (void* ptr, int tag_id);
    void VP_memblk_reset (int tag_id);
    long SP_ToMipsUncacheAddrFunc(unsigned char *pVirt, const char *func, int line);
    unsigned char * SP_Virt2Phy(unsigned char *pVirt);
    int SP_SetVOFilter(void *filter);
    void SP_WaitVOUnlock(int usec, char *);
    void SP_EnqueueRPCRing_func(SP_RPC_TYPE rpc_type);
    int SP_ExtractBits(
        int bs_base, // unit: byte << 3
        int bs_limit,// unit: byte << 3
        int *bs_rp,   // unit: byte << 3
        int bs_wp,    // unit: byte << 3
        const int nNumBits);
    unsigned int SP_PeekBits(
        int bs_base, // unit: byte << 3
        int bs_limit,// unit: byte << 3
        int *bs_rp,   // unit: byte << 3
        int bs_wp,    // unit: byte << 3
        const int nNumBits);
    void SP_flush_ion(int tag);
    void SP_invalidate_ion(int tag);
#if SP_TRACE_ENABLE
    void SP_PrintRingPtrNow();
#endif
#if SP_CHECK_VIRT_ADDR_RANGE
    void SP_CheckVirtAddrValidFunc(unsigned char *pVirt, const char *func, int line);
#endif
#if SP_DBG_BS_RING
    void SP_PrintRingPtr_func();
#endif
protected:
private:
//    pthread_mutex_t nMutex;
//    pthread_cond_t nCond;
};

////////////////////////
// function prototype //
////////////////////////

int RVSD_SP_GetRingBufFileHandler(SP_INFO *pSpInfo, int client_sockfd);
void SP_Swap4Bytes(char *p, int bytes);

#endif  // #ifndef SP_INFO_H


