#ifndef VIDEO_COMMON_H
#define VIDEO_COMMON_H

#include "sp_info.h"
//#include "rvsd_def.h"
#include <string.h>
//#include "../rvsd_InBandCMD.h"
#if 0   // RPC
//#include "RPCProxy.h"
#include "VideoRPCBaseDS.h"
#include "VideoRPC_System_data.h"
#include "AudioRPCBaseDS_data.h"
#include "hresult.h"
#include "AudioRPC_System.h"
#include "AudioInbandAPI.h"
#include "InbandAPI.h"
#endif
//#include "rpc_common.h"
//#include "rvsd_VORPC.h"
#include <assert.h>
#include <pthread.h>
#include <utils/Log.h>  // for ALOGD
//#include "rvsd_CommonFunc.h"
#include "../bdsp_decoder/BDSP_Decode_def.h"

#ifdef ANDROID7_HACK_AVOID_SPU
#undef SP_DISABLE_SPU
#define SP_DISABLE_SPU 1
#endif

/*-----------------------------
DEFINE
------------------------------*/
#define SP_WAIT_VO_USEC 30
#define VP_DBGMASK_BDSP_DEC 0x08000000
#define VP_DBGMASK_DVBSP_DEC 0x00800000
#define VP_DBGMASK_SP_DEC 0x10000000
#define VP_DBGMASK_RPC            0x00000100      // 8
#define SP_BUSY_PRINT_SEC 3

/*-----------------------------
MACRO FUNCTION
------------------------------*/
#if SP_USE_ION_MEMORY
#define VP_malloc(a, b, c) (a)->VP_malloc_func(b)
#define VP_free(a, b)
#else
#define VP_malloc(a, b, c) malloc(b)
#define VP_free(a, b) free(a)
#endif
//#define VP_memblk_alloc(a, b) malloc(a)
//#define VP_memblk_request(a, b) malloc(a)
//#define VP_memblk_release(a) free(a)
//#define VP_memblk_free(a, b) free(a)
#define SP_WAIT_VO_UNLOCK(a, status) (a)->SP_WaitVOUnlock(SP_WAIT_VO_USEC, status)
#define VP_memset memset
//#define VP_malloc(a, b) malloc(a)
#define VBM_RemoveTask(a)   // NO usage
#define VTM_VALID_TASKID(a) // NO usage
#define VTM_RemoveTask(a)   // NO usage
#define VTM_ForceResume(a, b) (b)->SP_ForceResume()
#define VTM_ResumeTask(a, b, c) (c)->SP_ResumeTask(b)
#define VTM_SuspendTask(a, b, c) (c)->SP_SuspendTask(b)
#define SP_EnqueueRPCRing(a, b) (a)->SP_EnqueueRPCRing_func(b)
#if 0
#define VPMaskPrintf(level, format, ...) {\
    { ALOGD(format, ##__VA_ARGS__); }\
}
#else
#define VPMaskPrintf(...)
#endif
#define SP_CHECK(a, b) {(a) = (b);}
#define SP_ToMipsUncacheAddr(a, b) (a)->SP_ToMipsUncacheAddrFunc(b, __FUNCTION__, __LINE__)
//#define SP_CHECK(a, b) {int c, d; c=(a); d=(b); if(c != d) {ROSPrintf("[SP %d %s %x %x]\n", __LINE__ ,  __FUNCTION__, c, d);}}
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define GET_BIT(x, pos) (((x) >> (pos)) & 0x1)
#define RESET_BIT(x, pos) ((x) & ~(0x1 << (pos)))
#define SET_BIT(x, pos) ((x) | (0x1 << (pos)))
#define TO_MIPS_UNCACHE_ADDR(x) (((int)(x)) | 0xa0000000)
#define CHECK_MEMORY_FOR_MIPS(x) { if(((unsigned int)(x)) >= 0x20000000) SP_WARNING("[memory error %08x for MIPS]\n", (unsigned int)(x));}
#define SP_SLEEP() usleep(25000)   // estimate 25ms ... Need to tune...

#define ROUND16(a) (((a) + 15) & ~15)
#define ROUND8(a) (((a) + 7) & ~7)

#define RVSD_ENDIAN_CHANGE(x)    ((((x)&0xff000000)>>24)|(((x)&0x00ff0000)>>8)|(((x)&0x0000ff00)<<8)|(((x)&0x000000ff)<<24))
#define RVSD_ENDIAN_CHANGE_16(x) ((((x)&0xff00)>>8) | (((x)&0x00ff)<<8))

#if 1   // for android player
#define WarningPrint ALOGD
//#define Warning(fmt, args...) ALOGD("[SP Warn]%s:"fmt, __FUNCTION__, ##args);
#define Warning(format, ...) \
{\
  static long long prePTS = 0;\
  long long curPTS, diffPTS;\
  curPTS = getPTS();\
  diffPTS = curPTS - prePTS;\
  if(diffPTS > 90000)\
  {\
        ALOGD( format, ##__VA_ARGS__);\
        prePTS = curPTS;\
  }\
}
#define ROSPrintf ALOGD
#define RTK_CHECK() ALOGD("[SP CHECK @ %s %d]\n", __func__, __LINE__);   // code may have error...

#if 1
//#if SP_ENABLE_DBG
#define SP_DBG() ALOGD("[SP %s %d]\n", __FUNCTION__, __LINE__);
#define SP_DBG2 ALOGD
#else
#define SP_DBG()
#define SP_DBG2(format, ...)
#endif

#define SP_LOG ALOGD
//#define SP_WARNING(format, ...) { ALOGD("[SP WARN]"); ALOGD(format, ##__VA_ARGS__); }
#define SP_PRINT ALOGD

#else   // #if 1   // for android player

#define WarningPrint printf
#define Warning printf
#define ROSPrintf printf
#define RTK_CHECK() printf("[SP CHECK @ %s %d]\n", __func__, __LINE__);   // code may have error...
#define SP_TRACE(format, ...) {printf("[SP]"); printf(format, ##__VA_ARGS__); }
#define SP_DBG() printf("[SP %s %d]\n", __FUNCTION__, __LINE__);
#define SP_LOG printf
#define SP_DBG2 printf
#define SP_WARNING(format, ...) { printf("[SP WARN]"); printf(format, ##__VA_ARGS__); }
#define SP_PRINT printf
#endif

#if SP_DBG_VO
#define SP_PRINT_DVB(x, y, z) SP_Print_DVB(x, y, z)
#define SP_PRINT_DVD(x, y) SP_Print_DVD(x, y)
#define SP_PRINT_WORD(a, b, c) SP_PrintWord(a, b, c)
#else
#define SP_PRINT_DVB(x, y, z)
#define SP_PRINT_DVD(x, y)
#define SP_PRINT_WORD(a, b, c)
#endif

#if SP_DBG_BS_RING   // check BS ring
#define SP_PRINT_RING_PTR(a) (a)->SP_PrintRingPtr_func()
#else
#define SP_PRINT_RING_PTR(a)
#endif

#if SP_CHECK_VIRT_ADDR_RANGE
#define SP_CheckVirtAddrValid(a, b, c, d) (a)->SP_CheckVirtAddrValidFunc(b, c, d)
#else
#define SP_CheckVirtAddrValid(a, b, c, d)
#endif

#define SP_WARNNING_SEC(_sec, format, ...) \
{\
  static long long prePTS = 0;\
  long long curPTS, diffPTS;\
  curPTS = getPTS();\
  diffPTS = curPTS - prePTS;\
  if(diffPTS > 90000 * _sec)\
  {\
        SP_PRINT( format, ##__VA_ARGS__);\
        prePTS = curPTS;\
  }\
}

#define ASSERT(cond, msgID, format, ...)                                      \
{                                                                             \
  if (cond)                                                                   \
  {                                                                           \
    WarningPrint(format, ##__VA_ARGS__);                                      \
    assert(0);                                                                \
  }                                                                           \
}

#if SP_DVB_PRINT_DATA_EN
#define SP_DVB_PRINT_DATA(a, b, c, d) SP_DVB_PrintData(a, b, c, d)
#else
#define SP_DVB_PRINT_DATA(a, b, c, d)
#endif

#define SP_UNUSED(x) (void)(x)
#define UNUSED(x) (void)(x)


/*-----------------------------
DEFINE
------------------------------*/
#define DVBSP_ON_MIPS 0

//#define ION_MEMORY_SIZE (9 * 1024 * 1024)

#define ION_FILTER_SIZE (258 * 1024)
#define ION_DVD_SIZE (0)
#define ION_DVB_SIZE (6 * 1024 * 1024)

#define PALETTE_SIZE 16

#define SP_MAX_PACKET_4BYTES_UNIT 60

#define VMM_SIZE_DVB_SUBTITLE (0x0200000 * 3)

#define VMM_SIZE_SP_FILTER ( 256*1024)

#define TASK_STK_SIZE_DEC 64

#define SP_UNDERFLOW (0x80000000)
//#define TO_VIRTUAL_ADDR(x) (((x) & 0x1fffffff) | 0xa0000000)
#define TO_VIRTUAL_ADDR(x) (x)

#define VTM_INVALID_TASK           0xff

#define VTM_SEMAPHORE_REGISTRATION  0
#define VTM_SEMAPHORE_BUFFER        1
#define VTM_SEMAPHORE_INPUT         2
#define VTM_SEMAPHORE_OUTPUT        3
#define VTM_SEMAPHORE_ISR           4
#define VTM_SEMAPHORE_MEQ           5
#define VTM_SEMAPHORE_DINQ          6
#define VTM_SEMAPHORE_CMD           7
#define VTM_SEMAPHORE_POLL          8
#define VTM_SEMAPHORE_SMALLBUFFER   9

#define VP_SUCCESS                 0
#define VP_ERR_NO_MEMORY          -1
#define VP_ERR_INVALID_PIN        -2
#define VP_ERR_WRONG_ADDRESSEE    -3
#define VP_ERR_RECEIVER_OVERFLOW  -4
#define VP_ERR_VTM_OVERFLOW       -5
#define VP_ERR_WRONG_DATA         -6
#define VP_ERR_NO_SEMAPHORE       -7
#define VP_ERR_NOT_SUSPEND        -8

#define VMM_ID_BD_SUBTITLE_BUFFER   16

#define VP_STREAM_PACKET_HEAD_SIZE  (sizeof(VP_STREAM_PACKET) - (8 * (VP_PACKET_DWORD_SIZE  - 1)))
#define VP_STREAM_PACKET_SIZE(x) (sizeof(VP_STREAM_PACKET) - (8 * (VP_PACKET_DWORD_SIZE - 1) - sizeof(x)))

/* Decoder flow standardized pin ID */
#define VP_PIN_VIDEO_DECODER_COMMAND      0
#define VP_PIN_VIDEO_DECODER_INPUT        1
#define VP_PIN_VIDEO_DECODER_OUTPUT       2
#define VP_PIN_VIDEO_DECODER_TOSCALER     3

#define VMM_ID_DECODER_FILTER        1
#define VMM_ID_JPEGDEC_FILTER        2
#define VMM_ID_SP_FILTER             3
#define VMM_ID_VOUT_FILTER           4
#define VMM_ID_DVB_SP_DECODER        5
#define VMM_ID_DIVX_SP_DECODER       6
#define VMM_ID_COMEM_BUFFER          7
#define VMM_ID_VBM_CONTEXT           8
#define VMM_ID_VBM_BUFFER            9
#define VMM_ID_VOUT_STILL_FLAG      10
#define VMM_ID_VOUT_MIXER2          11
#define VMM_ID_PERF_ANALYZER        12
#define VMM_ID_DEBUG_LOG            13
#define VMM_ID_TRANSITION_FILTER    14
#define VMM_ID_THUMBNAIL_FILTER     15
#define VMM_ID_BD_SUBTITLE_BUFFER   16
#define VMM_ID_FLASH_FILTER         17
#define VMM_ID_VMIXER_FILTER        18
#define VMM_ID_COMEM_EXTRA          19
#define VMM_ID_VO_PLANE_MIXER_BUFFER 20
#define VMM_ID_DYNAMIC_STEAL_COMEM  21

#define H_FLAG_SUCCESS                  (0x10000000)
#define H_FLAG_ERROR                    (0x20000000)
#define H_FLAG_WARNNING                 (0x40000000)

#define H_TYPE_ERROR_GENERAL            ((H_FLAG_ERROR)   |     (0x00010000))
#define H_TYPE_ERROR_PIN                ((H_FLAG_ERROR)   |     (0x00020000))
#define H_TYPE_ERROR_ALLOC              ((H_FLAG_ERROR)   |     (0x00030000))
#define H_TYPE_ERROR_MEDIA_SAMPLE       ((H_FLAG_ERROR)   |     (0x00040000))
#define H_TYPE_ERROR_MEDIA_TYPE         ((H_FLAG_ERROR)   |     (0x00050000))
#define H_TYPE_ERROR_FILTER             ((H_FLAG_ERROR)   |     (0x00060000))
#define H_TYPE_ERROR_STATE              ((H_FLAG_ERROR)   |     (0x00070000))
#define H_TYPE_ERROR_ENUM_PINS          ((H_FLAG_ERROR)   |     (0x00080000))
#define H_TYPE_ERROR_ENUM_FILTERS       ((H_FLAG_ERROR)   |     (0x00090000))
#define H_TYPE_ERROR_EVENT              ((H_FLAG_ERROR)   |     (0x000a0000))

/*****************************************************************************/
/* Success codes                                                             */
/*****************************************************************************/
#define S_OK                            ((H_FLAG_SUCCESS) |     (0x00000000))
#define S_FALSE                         ((H_FLAG_SUCCESS) |     (0x00000001))

#define SW_TRAP_VBM_MEM_ERROR               0xFF01
#define SW_TRAP_MEM_HEADER_TRASH            0xFF02
#define SW_TRAP_MEM_INTRCHK_FAIL            0xFF03
#define SW_TRAP_VBM_MEM_OVERFLOW            0xFE04
#define SW_TRAP_VP_MEM_OVERFLOW             0xFE05
#define SW_TRAP_FLOW_ERROR                  0xFE06
#define SW_TRAP_INVALID_PTR                 0xFE07

/*****************************************************************************/
/* Error codes                                                               */
/*****************************************************************************/
// H_TYPE_ERROR_GENERAL
#define E_FAIL                          ((H_TYPE_ERROR_GENERAL) | (0x00000001))
#define E_GEN_POINTER_NULL              ((H_TYPE_ERROR_GENERAL) | (0x00000002))
#define E_GEN_UNEXPECTED                ((H_TYPE_ERROR_GENERAL) | (0x00000003))
#define E_GEN_MEM_ARRAY_BOUNDARY        ((H_TYPE_ERROR_GENERAL) | (0x00000004))
#define E_TIMEOUT                       ((H_TYPE_ERROR_GENERAL) | (0x00000005))
#define E_IO                            ((H_TYPE_ERROR_GENERAL) | (0x00000006))
#define E_IO_UNKNOWN_PROTOCOL           ((H_TYPE_ERROR_GENERAL) | (0x00000007))


/*-----------------------------
ENUM
------------------------------*/
enum {
    ENUM_SP_EXIT_0 = 0,
    ENUM_SP_EXIT_1,
    ENUM_SP_EXIT_2,
    ENUM_SP_EXIT_3,
    ENUM_SP_EXIT_4,
    ENUM_SP_EXIT_5,
    ENUM_SP_EXIT_6,
};

enum
{
    ENUM_WAIT_VO_READY_DONE = 0,
    ENUM_WAIT_VO_READY_EXIT,
    ENUM_WAIT_VO_READY_EXIT_ABNORMALLY,
};

enum SP_DVD_SEND_TO_VO_TYPE {
    SP_DVD_ICQ_TO_VO = 0,
    SP_DVD_DELIVER_TO_VO,
};

enum {
    ENUM_VO_RESET = 0,
    ENUM_VO_INIT,
    ENUM_VO_READY,
    ENUM_VO_UNINIT,
};

/*-----------------------------
DATA STRUCTURE
------------------------------*/

typedef unsigned char  BYTE;

typedef struct
{
    volatile unsigned int   base   ;
    volatile unsigned int   limit  ;
    volatile unsigned int *pWrPtr ;
    volatile unsigned int *pRdPtr ;
    volatile unsigned int   write ;
    volatile unsigned int   phyBase;

} VP_INBAND_RING_BUF ;


//class SP_INFO;
//typedef long HRESULT;
typedef unsigned int VP_TASK_STACK;
typedef unsigned char u_char;
typedef unsigned long u_long;
typedef unsigned int u_int;
typedef unsigned short u_short;

typedef struct
{
    short x ;        /* upper-left corner x coordinate */
    short y ;        /* upper-left corner y coordinate */
    short width ;    /* window width */
    short height ;   /* window height */

} VP_WINDOW ;

typedef struct
{
//  ROS_EVENT         *sem ;
    RINGBUFFER_HEADER *pRBH ;
} VP_CMD_COMMON_INIT_RING_BUF ;

typedef struct
{
    unsigned char  time_out ;     /* in seconds */
    unsigned char  pixel_depth ;  /* 1: 2-bit; 2: 4-bit; 3: 8-bit */
    unsigned char  st_mode ;      /* 0: block mode; 1: sequential mode */
    unsigned char  last_in_page ; /* 1 if the region is the last one in the region list of a display page */

    unsigned short start_x ;
    unsigned short start_y ;
    unsigned short width ;
    unsigned short height ;
    unsigned short pitch ;
    unsigned int   pixel_addr ;  /* absolute DRAM address of the first pixel */
    unsigned int  *CLUT ;        /* receiver must copy the CLUT contents upon receival of this object */
    VP_BUFFER     *buffer ;

    unsigned short video_width ; /* fullWidth and fullHeight for BD subtitle */
    unsigned short video_height ;
    long long      PTS ;

} VP_OBJ_DVB_SP_REGION ;

typedef struct
{
    SP_STREAM_TYPE streamType ;
}SP_DUMMY_DECODE;

// copy from android/hardware/realtek/StreamEngine2/SeLib.h
typedef struct _SE_PROCINFO                     		
{                                               		
    uint16_t    wDataX;                 				//Set Data Location X
    uint16_t    wDataY;                 				//Set Data Location Y
    uint16_t    wDataHeight;            				//Set Data Height
    uint16_t    wDataWidth;             				//Set Data Width

  	uint8_t		byCommandQueueSelect;   				//Select Corresponding Command Queue for Current Serivce
  	bool    	bInterruptService;      				//Select Which CPU to Service Interrupt Events

    uint8_t   	byBaseAddressIndex;     				//Set Index of Base Address 
                	                   	 				//- Sequential Mode: Select Corresponding SE_Baddr and SE_Pitch Registers
                    	               					//- Block Mode: Select DCU Address Index If Color Format is YUV                                                
    uint8_t 	byChronmaAddressIndex;  				//Set DCU Index of Chronma Address     
    bool    	bInterleavingModeEnable;				//Enable/Disable Interleaving Mode    
} SE_PROCINFO;

typedef struct
{
    int hdl;
    int cmdQ;
    int src_width;
    int src_height;
    int dst_width;
    int dst_height;
    ION_HDL *hdl_ion;
    ION_DATA argb_raw_ion;  // 3840 * 2160 * 4
    ION_DATA yuv420_4k_ion; // 3840 * 2160 * 1.5
    char clut_lock;
}SP_SE_INFO;

/*
typedef struct
{
  FILTER       filter ;
  VP_COMPONENT vout ;

} FILTER_VOUT ;*/

/*-----------------------------
FUNCTION PROTOTYPE
------------------------------*/
void ICQ_UpdateReadPtr (VP_INBAND_RING_BUF *pVIRB, int size);
void *ICQ_GetCmd (void *p, int p_size, VP_INBAND_RING_BUF *pVIRB, int bUpdateReadPtr);
void VP_InitPool(VP_BUFFER *pool, int pool_size, void *large_buffer, int small_buffer_size, unsigned char taskID);
VP_BUFFER*  VP_AllocateMem(VP_BUFFER *pool, int pool_size);
int SP_Decoder_Create (SP_INFO* pSpInfo, VP_COMPONENT *_this, int mtag);
int DVBSP_Decoder_Create (SP_INFO *, VP_COMPONENT *_this, int mtag);
int BDSP_Decoder_Create (SP_INFO *, VP_COMPONENT *_this, int mtag);
void VP_memblk_free (void* ptr, int tag_id);
FILTER *FILTER_SPDEC_Create(SP_INFO *pSpInfo);
int RVSD_SP_Create(SP_INFO *);
int RVSD_SP_GetRingBufFileHandler(SP_INFO *pSpInfo, int client_sockfd);
HRESULT FILTER_SPDEC_Run (FILTER *f);
HRESULT *VIDEO_RPC_SUBPIC_DEC_ToAgent_Configure_RVSD (SP_INFO *pSpInfo, VIDEO_RPC_SUBPIC_DEC_CONFIGURE *argp, RPC_STRUCT *rpc, HRESULT* retval);
HRESULT FILTER_SPDEC_Stop (FILTER *f);
HRESULT FILTER_SPDEC_Flush (SP_INFO*, FILTER *f);
HRESULT FILTER_SPDEC_Destroy (SP_INFO*, FILTER *f);
void* SP_Run_thread(void *data);
void SP_Swap4Bytes(char *p, int num);
long long SP_EndianChangeLL(long long *p);
void SP_Print_DVB(VIDEO_VO_OBJ_DVB_SP_REGION *p, int , int);
void SP_Print_DVD(VIDEO_VO_OBJ_DVD_SP *p, int);
unsigned int rvsd_vo_getVOFilterAddr(void);
unsigned int rvsd_vo_GetVOFilter(void*  p);
int rvsd_check_vo_state(void *p);
void SP_DVB_PrintData(unsigned char *pData, int pitch, int height, int);
int VIDEO_RPC_VOUT_QUERY_RVSD(SP_INFO *pSpInfo, int queryWhat, int arg0, int arg1);
void SP_PrintWord(char *name, unsigned int *p, int num);
int RVSD_SP_InitRingBuf_disable(int);
void rvsd_set_sp_null(void *p);
void VIDEO_RPC_SUBPIC_DEC_ToAgent_FlushSubPicture_RVSD(SP_INFO *pSpInfo);
void rvsd_set_sp_thread(void *p, pthread_t nThread);
void DBG_SP_DumpBS(SP_RINGBUF *pRing);
long long SP_get_master_pts(void *p);
ION_HDL *rvsd_get_ion_hdl(void *pRvsd);
SP_SE_INFO *SE_Index4k_2_rgb2k_init(int src_width, int src_height
    , int dst_width, int dst_height);
void SE_Index4k_2_rgb2k_uninit(SP_SE_INFO *se);
void SE_Index4k_2_rgb2k(SP_SE_INFO *se
    , int index_phy /* SIZE = MAX(I: 3940*2160, O:1920*1088*4) */
    , int *clut_virt, int clut_phy);
void SE_clut_yuv_2_rgb(int *clut_idx, int bARGB_BE);
void SP_scale_uninit(SP_SCALE_INFO *se);
SP_SCALE_INFO *SP_scale_init(int src_width, int src_height
    , int dst_width, int dst_height);
void SP_RPC_set_se_clock(int clk);
int SP_Dummy_Create (SP_INFO* pSpInfo, VP_COMPONENT *_this, int mtag);
void    pli_IPCWriteULONG(BYTE* des, unsigned long data);
void* my_memcpy(void *des, const void *src, size_t num);
void* my_memset(void *p, int value, int byte_size);
unsigned long ring_add(unsigned long ring_base, unsigned long ring_limit, unsigned long ptr, unsigned int bytes);
unsigned long ring_minus(unsigned long ring_base,unsigned long ring_limit,unsigned long ptr,unsigned long bytes);
void ring_read(unsigned long ring_base, unsigned long ring_limit, unsigned long ptr, unsigned int bytes, char* buf);
unsigned long ring_valid_data(unsigned long ring_base, unsigned long ring_limit, unsigned long ring_rp, unsigned long ring_wp);
unsigned long ring_memcpy2_buf(char* buf,unsigned long base, unsigned long limit, unsigned long ptr, unsigned long size);
unsigned long buf_memcpy2_ring(unsigned long base, unsigned long limit, unsigned long ptr, char* buf, unsigned long size);
unsigned long valid_free_size(unsigned long base, unsigned long limit, unsigned long rp, unsigned long wp);
int64_t getPTS();
int RVSD_GetExitLoopThread(void *p);
unsigned int rvsd_vo_sendInbandCmd(void* p, void *cmd_endian_swapped, unsigned int cmd_size);

#endif

