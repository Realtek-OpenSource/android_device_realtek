#ifndef _HDCP_COMMON_H_
#define _HDCP_COMMON_H_

#include <cutils/properties.h>

#define HDCP_STORAGE_PATH_PROP      "ro.vendor.rtk.hdcp.storage"
#define DFT_HDCP_STORAGE_PATH       "/data"
#define DFT_HDCP_KEY_PATH           "/tmp"

#define HDCP22_KEY_NAME             "_custom_param_tx"
#define HDCP14_KEY_NAME             "_custom_param_h13"

static inline void resolveRxInfoPath(char *out)
{
    char value[PROPERTY_VALUE_MAX] = {'\0'};
    property_get(HDCP_STORAGE_PATH_PROP,value,DFT_HDCP_STORAGE_PATH);
    sprintf(out,"%s",value);
}

static inline void resolveHDCPKeyPath(char *out)
{
    char value[PROPERTY_VALUE_MAX] = {'\0'};
    property_get(HDCP_STORAGE_PATH_PROP,value,DFT_HDCP_KEY_PATH);
    sprintf(out,"%s",value);
}

static inline void resolveHDCP14Key(char *out)
{
    char hdcp_key_dir[128];
    memset(hdcp_key_dir,0x0,128);
    resolveHDCPKeyPath(hdcp_key_dir);

    sprintf(out,"%s/%s",hdcp_key_dir,HDCP14_KEY_NAME);
}

static inline void resolveHDCP22Key(char *out)
{
    char hdcp_key_dir[128];
    memset(hdcp_key_dir,0x0,128);
    resolveHDCPKeyPath(hdcp_key_dir);

    sprintf(out,"%s/%s",hdcp_key_dir,HDCP22_KEY_NAME);
}


#endif
