#ifndef __RVSD_BSVALIDATE_H__
#define __RVSD_BSVALIDATE_H__

void CheckBitstreamValidation(long bsBase, long bsSize, int* bitrate, int* type, RVSD_INFO *p_rvsd_info);
int PreParseVideoSequenceInfo(long bsBase, long bsSize, long* retInfo, int videoType, RVSD_INFO *p_rvsd_info);


#endif