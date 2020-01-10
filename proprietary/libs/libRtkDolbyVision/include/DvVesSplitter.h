#ifndef RVSD_VDECBITSTREAMFEED_H
#define RVSD_VDECBITSTREAMFEED_H

#include "rpc_common.h"
//#include "vdi_osal.h"
#include "rvsd_ringbuffer.h"

#ifndef ANDROID
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#endif

#include <ion/ion.h>
#include "rvsd_dbg.h"


#define SPLITTER_BS_FILE_READER 0
#define SPLITTER_VES_FEED_SIZE_FIXED_EN 0
#define SPLITTER_VES_FEED_SIZE_FIXED (2*1024*1024)
#define MAX_SPLITTER_VES_TMP_BUF_SIZE (16*1024*1024)
#define SPLITTER_MAX_FILE_PATH (256)

typedef void * osal_file_t;

enum BufferItemIndex
{
    BlBufferItem,
    ElBufferItem,
    BufferItemAmount
};

enum SplitterCodecType
{
    SplitterHEVC,
    SplitterAVC,
    SplitterUnknown
};

enum RtkVesDmxType
{
    RTK_VES_DMX_START_CODE = 0,
    RTK_VES_DMX_START_CODE_AT_EOB,
    RTK_VES_DMX_NAL_PAYLOAD
};

enum RtkDvEsCodec
{
    RTK_ES_AVC_CODEC = 0,
    RTK_ES_HEVC_CODEC,
    RTK_ES_METADATA_CODEC,
    RTK_MAX_CODEC
};

enum RtkDvEsType
{
    RTK_ES_BASE_LAYER,
    RTK_ES_ENHANCEMENT_LAYER,
    RTK_ES_METADATA,
    RTK_MAX_ES
};

enum RtkVesImpType
{
    RTK_SINGLE_VES,
    RTK_DUAL_VES,
    RTK_MAX_VES
};

#define MAX_ES_RP_ACCUOFFSET_NUM 4096

typedef enum
{
  HEVC_NALU_TYPE_TRAIL_N        = 0,
  HEVC_NALU_TYPE_TRAIL_R        = 1,
  HEVC_NALU_TYPE_TSA_N          = 2,
  HEVC_NALU_TYPE_TSA_R          = 3,
  HEVC_NALU_TYPE_STSA_N         = 4,
  HEVC_NALU_TYPE_STSA_R         = 5,
  HEVC_NALU_TYPE_RADL_N         = 6,
  HEVC_NALU_TYPE_RADL_R         = 7,
  HEVC_NALU_TYPE_RASL_N         = 8,
  HEVC_NALU_TYPE_RASL_R         = 9,
  HEVC_NALU_TYPE_BLA_W_LP       = 16,
  HEVC_NALU_TYPE_BLA_W_RADL     = 17,
  HEVC_NALU_TYPE_BLA_N_LP       = 18,
  HEVC_NALU_TYPE_IDR_W_RADL     = 19,
  HEVC_NALU_TYPE_IDR_N_LP       = 20,
  HEVC_NALU_TYPE_CRA_NUT        = 21,
  HEVC_NALU_TYPE_RSV_IRAP_VCL23 = 23,
  HEVC_NALU_TYPE_VPS_NUT        = 32,
  HEVC_NALU_TYPE_SPS_NUT        = 33,
  HEVC_NALU_TYPE_PPS_NUT        = 34,
  HEVC_NALU_TYPE_AUD_NUT        = 35,
  HEVC_NALU_TYPE_EOS_NUT        = 36,
  HEVC_NALU_TYPE_EOB_NUT        = 37,
  HEVC_NALU_TYPE_FD_NUT         = 38,
  HEVC_NALU_TYPE_PREFIX_SEI_NUT = 39,
  HEVC_NALU_TYPE_SUFFIX_SEI_NUT = 40,
  HEVC_NALU_TYPE_UNDEFINED      = -1
}HEVC_NaluType;

typedef enum
{
NALU_TYPE_SLICE    = 1,
NALU_TYPE_DPA      =2,
NALU_TYPE_DPB      =3,
NALU_TYPE_DPC      =4,
NALU_TYPE_IDR      =5,
NALU_TYPE_SEI      =6,
NALU_TYPE_SPS      =7,
NALU_TYPE_PPS      =8,
NALU_TYPE_AUD      =9,
NALU_TYPE_EOSEQ    =10,
NALU_TYPE_EOSTREAM =11,
NALU_TYPE_FILL     =12,
NALU_TYPE_SPS_EXT  =13,
NALU_TYPE_PREFIX   =14,
NALU_TYPE_SUB_SPS  =15,
NALU_TYPE_AUX      =19,
NALU_TYPE_SLC_EXT  =20
}H264_NaluType;

typedef struct
{
    unsigned long long pts; // derived pts
    unsigned long wp;
    unsigned int accuOffset;
    // this vesAccuOffset is not the same as the vesAccuOffset of frame start,
    // because this value is the first VCL NAL UNIT address which has derived pts, but frame start maybe started from AUD NAL UNIT
    unsigned int vesAccuOffset;
} ES_PTS_WP_ACCUOFFSET;

class FeedBufferItem
{
public:
    FeedBufferItem();
    ~FeedBufferItem();

    bool Initialize(void **pp_vpu_handle, RINGBUFFER_HEADER **pp_header,
                    unsigned char **pp_virtual, int *p_size, BufferItemIndex index);
    bool Uninitialize();

    bool IsInitialized() const;

    unsigned long VirtualToPhysical(unsigned long address) const;
    unsigned long PhysicalToVirtual(unsigned long address) const;

    void PrintRingHeader() const;
    void FlushCache();

#if defined(RVSD_ENABLE_VES_SPLITTER)
    void Flush();
    void UpdateAccuOffset(int newCopiedBytes);
    unsigned int GetAccuOffset();
    int InsertDerivedPts(RtkVesDmxType evt, unsigned long wp, unsigned int esAccuOffset, unsigned int vesAccuOffset, uint8_t nal_unit_type_byte, uint64_t derivedPts);
    bool FindDerivedPts(unsigned long frameStart, unsigned long frameEnd, long long *pts);
    BufferItemIndex GetItemIndex();
    void SetCodecType(RtkDvEsCodec codecType);
#endif // #if defined(RVSD_ENABLE_VES_SPLITTER)

    void **mpp_vpu_handle;
    RINGBUFFER_HEADER **mpp_header;
    unsigned char **mpp_virtual;
    int *mp_size;

private:
    bool Allocate();
    bool Release();

    void Reset();

    BufferItemIndex mBufItemIdx;
    RINGBUFFER_HEADER *mp_internal_header;
    unsigned long *mp_internal_virtual;
    int m_internal_size;
    unsigned long *mp_ion_physical;
    int m_ion_fd;
    int m_mmap_fd;
    ion_user_handle_t m_ion_handle;

    int m_is_initialized;

    unsigned int m_ringAccuOffset;
    pthread_mutex_t m_esPtsWpAccuOffsetMtx;
    ES_PTS_WP_ACCUOFFSET m_esPtsWpAccuOffset[MAX_ES_RP_ACCUOFFSET_NUM];
    unsigned int m_esPtsWpAccuOffsetWptr;
    unsigned int m_esPtsWpAccuOffsetRptr;

    bool m_is_cached;
#if defined(RVSD_ENABLE_VES_SPLITTER)
    RtkDvEsCodec m_codecType;
#endif // #if defined(RVSD_ENABLE_VES_SPLITTER)
};

class BitstreamFileReader
{
public:
    BitstreamFileReader(FeedBufferItem *p_buffer);
    ~BitstreamFileReader();

#if defined(RVSD_ENABLE_VES_SPLITTER)
    void SetVesDmx(void* h_dmx);
#endif
    void SetSplitter(void *pSp);
    void *ReadBsTask();

    void Start();
    void Stop();


public:
    // test
    int readBSTotalBytes;

private:
    bool ReadBs(BufferItemIndex index);
#if defined(RVSD_ENABLE_VES_SPLITTER)
    bool ReadVES();
#endif

    void OpenFile();
    void CloseFile();

    const static int m_read_unit = 1024 * 1024;
    const static int m_ves_read_unit = 1024 * 1024;

    osal_file_t m_file[BufferItemAmount];
    pthread_t m_read_thread;
    bool m_is_stop_read_thread;

    FeedBufferItem *mp_buffer[BufferItemAmount];

    char *mp_working_buffer;

#if defined(RVSD_ENABLE_VES_SPLITTER)
    void* m_hdmx;
#endif
    void *mp_sp;
    osal_file_t m_ves_file;
    char *mp_ves_buffer;
};

#define MAX_VES_RP_ACCUOFFSET_NUM       4096
#define MAX_VES_PTS_WP_ACCUOFFSET_NUM   4096
#define MAX_VES_NAL_ACCUOFFSET_NUM      4096
#define MAX_VES_DMX_DATA_RANGE_NUM      32

typedef struct
{
    unsigned long addr;             // physical address in BL ring buffer
    unsigned int ves_accuOffset;    // accumulated byte offset
} VES_NAL_ACCUOFFSET;

typedef struct
{
    unsigned long       ves_rp;
    unsigned int        ves_accuOffset;
    unsigned long       bl_wp;
    unsigned long       curr_bl_wp;
    VES_NAL_ACCUOFFSET  nalAccuOffset[MAX_VES_NAL_ACCUOFFSET_NUM];
    unsigned int        nalAccuOffsetWptr;
    unsigned int        nalAccuOffsetRptr;
} VES_RP_ACCUOFFSET;

typedef struct
{
    unsigned long       ves_rp;
    unsigned long       ves_wp;
    unsigned int        ves_accuOffset;
} VES_DMX_DATA_RANGE;

typedef struct
{
    unsigned long long  pts;
    unsigned long       ves_wp;
    unsigned int        ves_accuOffset;
} VES_PTS_WP_ACCUOFFSET;

typedef struct
{
    uint64_t time_val;
    uint32_t time_scale;
} RVSD_TIMESTAMP;

class Splitter
{
public:
    Splitter();
    ~Splitter();

    bool SetVpuHandle(void **pp_vpu_handle,
                      bool is_base,
                      RINGBUFFER_HEADER **pp_header = NULL,
                      unsigned char **pp_virtual = NULL,
                      int *p_size = NULL);
    bool Run(void *pBSHDRBase, unsigned char *pBSringBase, unsigned long BSringPhyaddr, int BSringSize, int blVideoType, int elVideoType);
    void Stop();
    bool IsStoping();
    bool GetBuffer(void *p_vpu_handle, RINGBUFFER_HEADER **pp_header,
                   unsigned char **pp_base, int *p_size) const;
    bool GetBuffer(BufferItemIndex index, RINGBUFFER_HEADER **pp_header,
                    unsigned char **pp_base, int *p_size) const;
    FeedBufferItem* GetFeedBufferItem(BufferItemIndex index);
    bool SetEos(unsigned int last_position);
    void SetDecMode(unsigned char decMode);

    RVSD_RINGBUF* GetMetadataRing();

    bool GetCodecType(SplitterCodecType &bl, SplitterCodecType &el) const;

    bool IsGetFirstBL();
    void SetGetFirstBL();
    void SetBlFound();
    void SetElFound();
    void SetMdFound();
    void SetOneAuParsed();
    void SetAlwaysDolbyFlow();
    bool IsVesHasEl() const;
    bool IsVesHasMd() const;
    bool IsOneAuParsed() const;
    bool IsAlwaysDolbyFlow() const;

#if defined(RVSD_ENABLE_VES_SPLITTER)
    void* VesDmx();
    bool IsDmxEos(unsigned long eosWptr);

#if _DBG_DUMP_SPLITTER_BL_EL_MD
    void Dump2LayerData(BufferItemIndex index, unsigned char *pPtr, unsigned int wSize, bool fromIONRing);
#endif // #if _DBG_DUMP_SPLITTER_BL_EL_MD
#if _DBG_DUMP_SPLITTER_VES
    void DumpVesBitstream(unsigned char *pPtr, unsigned int wSize);
#endif // #if _DBG_DUMP_SPLITTER_VES

    RtkDvEsCodec DetectCodecType(void *pBSHDRBase, unsigned char *pBSringBase, int BSringSize) const;
    void SetFilePath(const char *p_path);

#if _DBG_DUMP_SPLITTER_BL_EL_MD
    void DumpRemainRpu();
#endif // #if _DBG_DUMP_SPLITTER_BL_EL_MD
    int InsertPTS(long long pts, unsigned int wp);

    // in nal_dmx_cb_func(), when BL start code is copied to BL ring buffer, add (bl_wp, ves_accuOffset) to VES_RP_ACCUOFFSET.
    void AddBLNalAddr2RpAccuOffset(unsigned long addr, unsigned int vesAccuOffset);
    void AddRpAccuOffset(unsigned int nal_len);
    unsigned int GetVesAccuOffet();
    // in nal_dmx_cb_func(), when BL nal payload is copied to BL ring buffer, update bl_wp to curr_bl_wp in VES_RP_ACCUOFFSET.
    void UpdateBLWp2RpAccuOffset(unsigned long bl_wp);
    bool FindPTS(unsigned long frmStart, unsigned int *pVesAccuOffset);

    void FlushStart();
    void FlushEnd();
    bool IsFlushing();
    void UpdateEsAccuOffset(BufferItemIndex index, unsigned int newCopiedBytes);
    unsigned int GetEsAccuOffset(BufferItemIndex index);
    int InsertDerivedPts(BufferItemIndex index, RtkVesDmxType evt, unsigned long wp, unsigned int esAccuOffset, unsigned int vesAccuOffset, uint8_t nal_unit_type_byte, uint64_t derivedPts);
    bool FindDerivedPts(BufferItemIndex index, unsigned long frameStart, unsigned long frameEnd, long long *pts);
    void ShowNalDmxCb(RtkDvEsType esType, RtkVesDmxType valueType, uint32_t nal_len, uint8_t *p_nal_buf, RVSD_TIMESTAMP *p_pts, unsigned int esAccuOffset, unsigned int vesAccuOffset, unsigned long nalStartWp);
    void CheckSeparatedCases(RtkDvEsType esType, RtkVesDmxType valueType, uint32_t nal_len, unsigned int esAccuOffset, unsigned int vesAccuOffset);
    void CheckExist(RtkDvEsType esType, RtkVesDmxType valueType, uint8_t *p_nal_buf);
    int GetNaluType(RtkDvEsType esType, RtkVesDmxType valueType, uint8_t *p_nal_buf);
    unsigned long GetVesStartPhyRp();
#endif  // #if defined(RVSD_ENABLE_VES_SPLITTER)

public:
    int                 m_w2rBytes[BufferItemAmount];   // total BL/EL bytes written to ring buffer
    bool                m_newOpenDump[BufferItemAmount];// true means new open dump file to write
    unsigned int        m_dumpEsSerial[BufferItemAmount];
    char                m_dumpEsFileName[BufferItemAmount][256];
    bool                m_newOpenVesDump;
    unsigned int        m_dumpVesSerial;
    char                m_dumpVesFileName[256];
    unsigned char       *m_pTmpBuf;
    unsigned char       *m_pVesTmpBuf;  // for speed up splitter demux, copy data form video ion ring buffer and set m_pVesTmpBuf to ves splitter library.
    osal_file_t         m_fp_rpu;
    int                 m_w2fBytes[BufferItemAmount];   // total BL/EL bytes written to file
    int                 m_w2fBytesRPU;  // total RPU bytes written to file
    int                 m_dmxBytesRPU;  // total RPU bytes demux
    void*               h_md_info;

    char *mp_metadata_buffer;
    RVSD_RINGBUF m_metadata_ring;

#if defined(RVSD_ENABLE_VES_SPLITTER)
    RtkVesDmxType       m_prevDmxCbEvt;
#endif  // #if defined(RVSD_ENABLE_VES_SPLITTER)
    long long           m_esRingNoRoomCheckCtrlPTS;
    long long           m_dropNalDmxCtrlPTS;

    unsigned long m_previous_pts;
    bool m_is_md_within_pts;
    bool m_is_md_found_after_flush;

    int m_default_rpu_read;
    int m_is_dual_ves;

    unsigned char m_decMode;
    int m_previous_au;
    bool m_previous_startcode;
    
private:
    FeedBufferItem      m_buffer[BufferItemAmount];
#if defined(RVSD_ENABLE_VES_SPLITTER)
    void* m_hdmx;
#endif  // #if defined(RVSD_ENABLE_VES_SPLITTER)
    pthread_t           m_vesDmxThread;
    void                *m_pBSHDRBase;
    unsigned char       *m_pBSringBase;
    unsigned long       m_BSringPhyaddr;
    int                 m_BSringSize;
    bool                m_isStopVesDmxThread;
    bool                m_isFlush;
    bool                m_isFlushDone;
    long long           m_vesBSEmptyLogCtrlPTS;
    long long           m_waitVDecNotifyFlushEndCtrlPTS;
    long long           m_waitSplitterFlushDoneCtrlPTS;
    pthread_mutex_t         m_vesRpAccuMtx;
    unsigned int            m_vesBSringAccuOffset;
    unsigned long           m_vesStartPhyRp;
    VES_RP_ACCUOFFSET       m_vesRpAccuOffset[MAX_VES_RP_ACCUOFFSET_NUM];
    unsigned int            m_vesRpAccuOffsetWptr;
    unsigned int            m_vesRpAccuOffsetRptr;
    pthread_mutex_t         m_ptsInsertMtx;
    VES_DMX_DATA_RANGE      m_vesDmxDataRange[MAX_VES_DMX_DATA_RANGE_NUM];
    unsigned int            m_vesDmxDataRangeWptr;
    unsigned int            m_vesDmxDataRangeRptr;
    VES_PTS_WP_ACCUOFFSET   m_vesPtsWpAccuOffset[MAX_VES_PTS_WP_ACCUOFFSET_NUM];
    unsigned int            m_vesPtsWpAccuOffsetWptr;
    unsigned int            m_vesPtsWpAccuOffsetRptr;
    pthread_mutex_t         m_flushMtx;
#if defined(RVSD_ENABLE_VES_SPLITTER)
    RtkDvEsCodec            m_blCodecType;
    RtkDvEsCodec            m_elCodecType;
#endif  // #if defined(RVSD_ENABLE_VES_SPLITTER)

    bool m_isGetFirstBL;
    bool m_is_bl_found;
    bool m_is_el_found;
    bool m_is_md_found;
    bool m_is_one_au_parsed;
    bool m_always_dolby_flow;

    char m_file_path[SPLITTER_MAX_FILE_PATH];

    void Allocate();
    void Release();

#if defined(RVSD_ENABLE_VES_SPLITTER)
    bool InitVesDmx(RtkDvEsCodec bl_codec, RtkDvEsCodec el_codec);
    bool StartVesDmx(void *pBSHDRBase, unsigned char *pBSringBase, unsigned long BSringPhyaddr, int BSringSize);
    void UninitVesDmx();
#endif  // #if defined(RVSD_ENABLE_VES_SPLITTER)

    int GetFreeBufferIndex() const;
    bool IsBufferIndexValid(int index) const;

    void ionRing2File(unsigned char *pPtr, unsigned char *pBase, unsigned char *plimit, unsigned int wSize, osal_file_t fp);
    void Flush();

#if SPLITTER_BS_FILE_READER
    BitstreamFileReader m_bs_reader;
#endif
};

#endif
