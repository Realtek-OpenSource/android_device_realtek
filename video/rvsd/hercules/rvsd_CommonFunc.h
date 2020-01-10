#ifndef RVSD_COMMON_FUNC_H
#define RVSD_COMMON_FUNC_H

#define RVSD_MAX_FILE_PATH (256)

typedef struct
{
    volatile unsigned int   base   ;
    volatile unsigned int   limit  ;
    volatile unsigned int *pWrPtr ;
    volatile unsigned int *pRdPtr ;
    volatile unsigned int   write ;
    volatile unsigned int   phyBase;

} VP_INBAND_RING_BUF ;

#if defined(RVSD_USE_1295_VE) || defined(RVSD_VP9_NEW_FLOW)

/************************************************************************/
/* DataQueue                                                                                                                */
/************************************************************************/
typedef struct {
    uint8_t*    buffer;
    uint32_t    size;
    uint32_t    itemSize;
    uint32_t    count;
    uint32_t    front;
    uint32_t    rear;
} DataQueue;

DataQueue* DataQueue_Create(
    uint32_t    itemCount,
    uint32_t    itemSize
);

void DataQueue_Destroy(
    DataQueue*  queue
);

/**
 * \brief       Enqueue with deep copy
 */
int DataQueue_Enqueue(
    DataQueue*  queue,
    void*       data
);

/**
 * \brief       Caller has responsibility for releasing the returned data
 */
void* DataQueue_Dequeue(
    DataQueue*  queue
);

void DataQueue_Flush(
    DataQueue*  queue
);

void* DataQueue_Peek(
    DataQueue*  queue
);

/**
 * \brief       @dstQ is NULL, it allocates Queue structure and then copy from @srcQ.
 */
DataQueue* DataQueue_Copy(
    DataQueue*  dstQ,
    DataQueue*  srcQ
);

int DataQueue_Count(
    DataQueue*  queue
);
#endif

int RVSD_GetExitLoopThread(void *p);
void ICQ_UpdateReadPtr_LE (VP_INBAND_RING_BUF *pVIRB, int size);
void *ICQ_GetCmd_LE (void *p, int p_size, VP_INBAND_RING_BUF *pVIRB, int bUpdateReadPtr);
int ICQ_PeekCmd_LE (VP_INBAND_RING_BUF *pVIRB, int numPeeks, INBAND_CMD_TYPE *pCmd);
int ICQ_SeekCmd_LE (void *p, VP_INBAND_RING_BUF *pVIRB, int cmdType);
void *ICQ_WriteCmd_LE(void *p, int p_size, VP_INBAND_RING_BUF *pVIRB);
unsigned int endian_swap(unsigned char *in);
void rvsd_adjust_DecOpenParam(void* p, int mapType);
bool IsFloatEqual(float a, float b);
void* my_memcpy(void *des, const void *src, size_t num);
void* my_memset(void *p, int value, int byte_size);
void StartElapseTime(struct timespec &start);
float EndElapseTime(struct timespec &start);

void GetDirectoryPath(char directory[RVSD_MAX_FILE_PATH],
                      char file_name[RVSD_MAX_FILE_PATH],
                      const char *p_path);
void EndianChange4Bytes(void *p_addr, unsigned int byte_size);
unsigned long long ConvertVirtualToPhysical(unsigned long long address,
                                            unsigned long long physical_base,
                                            unsigned long long virtual_base);

int IPC_GetRingBufFd(
    int client_sockfd,          // (I)
    unsigned char *pData,       // (I)
    unsigned int *pRingSize,    // (O)
    int *pHdrFd,                // (O)
    int *pRingBaseFd);           // (O)
int IPC_GetRingBufAddrByFd(
    int nRingHdrFd,
    int nRingBaseFd,
    int nBufSize,
    RINGBUFFER_HEADER **pHdr,
    unsigned char **pBase);

#define SAFE_DELETE_PTR(ptr) {if ((ptr) != NULL) {delete (ptr); (ptr) = NULL;}}
#define SAFE_DELETE_ARRAT(ptr) {if ((ptr) != NULL) {delete[] (ptr); (ptr) = NULL;}

#endif // #ifdef RVSD_COMMON_FUNC_H

