#ifndef RVSD_VDECMPEG2_H
#define RVSD_VDECMPEG2_H

#include "rvsd_ringbuffer.h"
#include "rpc_common.h"
#include "rtk_ion.h"
#if defined(RVSD_USE_TEE) && defined(RVSD_PARSE_USER_DATA_SECURE)
#include "tee_client_api.h"
#include "tee_api.h"
#endif

///////////////////
// Debug Contorl //
///////////////////
#define MPEG2_TRACE_ENABLE 0
#define MPEG2_PRINT_CC_RINGBUF_EN 0
#define MPEG2_CC_DUMP_DATA_EN 0

//#define MPEG2_CC_TEE_SELFTEST
//#define H264_CC_TEE_SELFTEST

//#define IGNORE_IPC_SECURITY_BUF
//#define DBG_MPEG2_DUMP_ORIGINAL_USER_DATA // dump user data information from VPU
//#define DBG_MPEG2_DUMP_COPY_USER_DATA // dump CC which copy to local ring
//#define DBG_MPEG2_DUMP_SEND_USER_DATA // dump CC which copy to AP ring

////////////
// Define //
////////////
#define MPEG2_USER_DATA_START_CODE 0x000001B2
#define MPEG2_USER_IDENTIFIER 0x47413934 // GA94
#define MPEG2_USER_DATA_START_CODE_LE 0xB2010000
#define MPEG2_USER_IDENTIFIER_LE 0x34394147 // GA94
#define USER_DATA_MIN 10
#define RTK_CC_SYNC_A53_PART4 0x52744B63  // RtKc
#define RTK_CC_SYNC_SCTE_20 0x52744B64
#define RTK_CC_SYNC_DVD 0x52744B65
#define RTK_CC_HEADER_SIZE 16
#define MPEG2_CC_REG_FRAME_MAX  20 // the maximum of VPU register frames
#define MPEG2_CC_RINGBUF_SIZE 2048
#define MPEG2_CC_FRAME_DISPLAY_ORDER 1  // transfer CC bitstream by display-order
#define VPU_CC_BUF_SIZE 512
#define USER_DATA_NUM_MAX 8

///////////
// Macro //
///////////
#if MPEG2_TRACE_ENABLE
#define MPEG2_TRACE(fmt, args...)   ALOGD("[MPEG2]%s:" fmt, __FUNCTION__, ##args);
#else
#define MPEG2_TRACE(format, ...)
#endif
#define MPEG2_WARNING(fmt, args...)   ALOGD("[MPEG2 WARN]%s:" fmt, __FUNCTION__, ##args);
#define MPEG2_LOG(fmt, args...)   ALOGD("[MPEG2]%s:" fmt, __FUNCTION__, ##args);
#if MPEG2_CC_DUMP_DATA_EN
#define MPEG2_CC_DUMP_DATA(a, b) MPEG2_CC_DumpRingBuf(a, b)
#else
#define MPEG2_CC_DUMP_DATA(a, b) 
#endif

//////////
// enum //
//////////
enum
{
    ENUM_CC_VIDEO_NONE=0,
    ENUM_CC_VIDEO_MPGE2,
    ENUM_CC_VIDEO_H264,
    ENUM_CC_VIDEO_H265
};

enum
{
    ENUM_CC_A53_PART4=0,
    ENUM_CC_SCTE_20,
    ENUM_CC_DVD,



    ENUM_CC_TOTAL_NUM
};

////////////////////
// Data Structure //
////////////////////

typedef struct
{
    int nUserDataNum;
    int nTotalUserDataSize;
    int nUserDataType[USER_DATA_NUM_MAX];
    int nUserDataOffset[USER_DATA_NUM_MAX];
    int nUserDataSize[USER_DATA_NUM_MAX];
}USER_DATA_INFO;

typedef struct
{
#if defined(MPEG2_CC_TEE_SELFTEST) || defined(H264_CC_TEE_SELFTEST)
    char pOutBuf[MPEG2_CC_RINGBUF_SIZE];
#endif
    char pBuf[MPEG2_CC_RINGBUF_SIZE];
    int m_CCDecodeOrderWp[MPEG2_CC_REG_FRAME_MAX];
    RVSD_RINGBUF nInRing;
    RVSD_RINGBUF nOutRing;
    unsigned int cc_frame_cnt;
    USER_DATA_INFO nUserDataInfo;
    int cc_outring_size;
    int userData_buf_size;

    int reservd[8];
}RVSD_CC_TEE_INFO;

class RVSD_MPEG2_INFO
{
public:
    RVSD_MPEG2_INFO();
    ~RVSD_MPEG2_INFO();

    /////////////////////
    // member variable //
    /////////////////////
    RVSD_RINGBUF cc_ring_buf;   // share memory with AP
    RVSD_RINGBUF m_RingBuf[ENUM_CC_TOTAL_NUM]; // local ring buffer
    ION_DATA m_ion; // for parsing CC in TEE
    USER_DATA_INFO nUserDataInfo;
    int CC_fd;
    int CC_base_fd;
    RINGBUFFER_HEADER* CC_HDR;  // cc ring buffer
    unsigned char* CC_ring_base;    // cc ring buffer virtual
    unsigned int CC_ring_size;  // cc ring buffer
    unsigned int CC_ring_base_phy; // cc ring buffer physical
    unsigned char *pBuf[ENUM_CC_TOTAL_NUM];
    unsigned long m_CCDecodeOrderWp[ENUM_CC_TOTAL_NUM][MPEG2_CC_REG_FRAME_MAX];
    unsigned int cc_frame_cnt[ENUM_CC_TOTAL_NUM];
    unsigned char *pVPU_cc_buf;
    char bTTAK_KO_CC;
    char bSecurity;
    void *pRvsd;
    int cc_type;
    int nUserDataSize;
    
    /////////////////////
    // member function //
    /////////////////////
    RVSD_MPEG2_INFO(void *pRVSD);
    unsigned int MPEG2_FindSyncCC(unsigned long BSbase, unsigned long BSlimit, unsigned long frameStart,unsigned long frameEnd);
#ifdef VPU_GET_CC
    unsigned int MPEG2_ProcessCC(unsigned char*, long long PTS, int decode_index, int display_index, int);
#else
    unsigned int MPEG2_ProcessCC(unsigned long BSbase, unsigned long BSlimit, unsigned long frameStart,unsigned long frameEnd, long long, int, int);
#endif
    inline long MPEG2_FindSyncCC_SubFunc1(RVSD_RINGBUF *pRing, unsigned long pStart, unsigned long data_size, long *search_bytelen);
    inline unsigned int MPEG2_FindSyncCC_SubFunc0(unsigned char *p, unsigned long loop_count, long *search_bytelen);
    int MPEG2_GetCCRingBuf(int client_sockfd, unsigned char *);
    void MPEG2_UpdateCCWp();
    void MPEG2_UpdateCCRp();
    int ProcessCC_TTAK_KO(unsigned char *pUserData, int);
/*    int H264_ProcessCC_TTAK_KO(unsigned char *pUserData, // point to itu_t_t35_country_code
        int nUserDataSize);*/
#if defined(RVSD_USE_TEE) && defined(RVSD_PARSE_USER_DATA_SECURE)
    unsigned int MPEG2_InitCC_tee(TEEC_Session *pSess);
    unsigned int MPEG2_ProcessCC_tee(TEEC_Session *pSess
        , unsigned long VPU_userdata_buf_phy, long long PTS, int decode_index
        , int display_index, int codec_type, int nUserDataSize);
    int MPEG2_GetCCRingBuf_security(
        TEEC_Session *pSess, int client_sockfd, unsigned char *pData);
    int malloc_buffer_security();
#endif
    int FindMpeg2CCInUserData(USER_DATA_INFO *pUserDataInfo
        , char *pUserDataBuf, long long PTS, int decode_index, int display_index);
    int MPEG2_CC_copy_2_local_ring(int idx, unsigned char *pUserData, unsigned int nUserDataSize
        , long long *pRTKHeader, int decode_index, int display_index);
    int MPEG2_send_CC(int idx, int display_index);
    int malloc_local_ring_buf(int idx, int size);
    int FindH264CCInUserData(USER_DATA_INFO *pUserDataInfo
        , char *pUserDataBuf, long long PTS, int decode_index, int display_index);
    int ProcessCC(unsigned long pUserDataPhy, long long PTS
        , int decode_index, int display_index, int codec_type);


};

ION_HDL *rvsd_get_ion_hdl(void *pRvsd);
int ParseUserDataInfo(USER_DATA_INFO *pUserDataInfo, char *pUserDataBuf);

#endif  // #ifndef RVSD_VDECMPEG2_H


