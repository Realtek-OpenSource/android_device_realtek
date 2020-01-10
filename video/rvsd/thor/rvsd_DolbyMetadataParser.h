#include "rvsd_maincore.h"
#include "rvsd_VDecVPU.h"
#include "rvsd_dbg.h"

#if defined (ENABLE_DOLBY_METADATA_PARSER)
#include "rpu_ext_config.h"
#include "rpu_api_common.h"
#include "rpu_api_decoder.h"
#include "dv_md_parser.h"
#endif

#undef LOG_TAG
#define LOG_TAG "DolbyMetadataParser"

#if defined (ENABLE_DOLBY_METADATA_PARSER)

#define CONTROL_PATH_FORMAT

typedef struct DolbyMetadataItem
{
    rpu_ext_config_fixpt_main_t composer;
    dm_metadata_t dm;
    timestamp_t pts;
} DolbyMetadataItem;

typedef struct ParserOutputContext
{
    ParserOutputContext()
    {
        comp_out = NULL;
        dm_out = NULL;
        memset(&rpu_data_out_buffer, 0, sizeof(rpu_data_t));
        memset(&main_cfg, 0, sizeof(rpu_ext_config_fixpt_main_t));
        memset(&out_ring, 0, sizeof(RVSD_RINGBUF));
        p_dm_byte_sequence = NULL;
        p_parser_handle = NULL;
        p_out_buffer = NULL;

        m_reorder_counter = 0;
        memset(m_reorder_buffer, 0, sizeof(DolbyMetadataItem) * m_reorder_amount);

        for (int i = 0; i < m_reorder_amount; i++)
        {
            m_reorder_buffer[i].pts.time_val = m_initial_pts;
        }
    }

    ~ParserOutputContext()
    {
    }

    osal_file_t comp_out;
    osal_file_t dm_out;
    rpu_data_t rpu_data_out_buffer;
    rpu_ext_config_fixpt_main_t main_cfg;
    char *p_dm_byte_sequence;
    dv_md_parser_handle_t *p_parser_handle;

    RVSD_RINGBUF out_ring;
    char *p_out_buffer;

    static const uint64_t m_initial_pts = UINT64_MAX;
    static const int m_reorder_amount = 6;
    DolbyMetadataItem m_reorder_buffer[m_reorder_amount];
    int m_reorder_counter;
} ParserOutputContext;

class DolbyMetadataParser
{
public:
    DolbyMetadataParser(RVSD_RINGBUF *p_ring);
    ~DolbyMetadataParser();

    void* DoTask();

    const DolbyMetadataItem* GetMetadata();
    void UpdateOutputRp();

    int GetMetadataAmount() const;
    void SetEos();
    void Flush();

private:
    void Allocate();
    void Release();

    bool AllocateParserEngine();
    bool ReleaseParserEngine();

    void InitOutputContext();
    void UninitOutputContext();

    static void OutputCallback(void *ctx_arg,
                                    dv_md_parser_evt_t md_parser_evt,
                                    timestamp_t *p_pts,
                                    rpu_data_header_t *hdr,
                                    vdr_rpu_data_payload_t *rpu_payload,
                                    int rpu_payload_sz,
                                    vdr_dm_data_payload_t *dm_payload,
                                    int dm_payload_sz,
                                    int len);
    static void ConvertRpuToConfig(rpu_data_header_t *rh,
                                           vdr_rpu_data_payload_t *rpu_payload,
                                           rpu_ext_config_fixpt_main_t *comp_cfg);
    static int ConvertDmToConfig(vdr_dm_data_payload_t *dm_rpu,
                                          char* dm_byte_sequence,
                                          int *length);
    bool IsWriteRpuBufferSucceed(dv_md_parser_rc_t process_ret) const;

    void FlushReorderBuffer();
    void DoFlush();

    RVSD_RINGBUF *mp_in_ring;

    dv_md_parser_handle_t m_parser_handle;
    dv_md_parser_conf_t m_parser_config;

    ParserOutputContext m_output_context;

    pthread_mutex_t m_mutex;

    bool m_is_eos;
    bool m_is_last_rpu_parsed;
    bool m_is_flush;
};
#else

typedef struct DolbyMetadataItem
{
} DolbyMetadataItem;

class DolbyMetadataParser
{
public:
    DolbyMetadataParser(RVSD_RINGBUF *p_ring __unused)
    {
    };

    ~DolbyMetadataParser()
    {
    };

    void* DoTask()
    {
        return 0;
    };

    const DolbyMetadataItem* GetMetadata()
    {
        return NULL;
    };

    void UpdateOutputRp()
    {
    };

    int GetMetadataAmount() const
    {
        return 0;
    };

    void SetEos()
    {
    };

    void Flush()
    {
    };
};


#endif
