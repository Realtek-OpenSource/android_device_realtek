#ifndef __DOLBYPARSERWRAPPER_H__
#define __DOLBYPARSERWRAPPER_H__

#include "rtk_common.h"
#include "rtk_metadata.h"
#include "rvsd_ringbuffer_def.h"

class DolbyParserWrapper
{
public:
    DolbyParserWrapper(RVSD_RINGBUF *p_ring);
    ~DolbyParserWrapper();

    void* DoTask();
    void StopTask();

    const DolbyMetadataItem* GetMetadata();
    void UpdateOutputRp();

    int GetMetadataAmount() const;
    void SetEos();
    void Flush();

private:
    void *p_parser;
};

#endif
