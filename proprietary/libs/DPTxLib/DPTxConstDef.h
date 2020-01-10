#ifndef _DPTX_CONST_DEF_H_
#define _DPTX_CONST_DEF_H_

#include <stdlib.h>
#include <unistd.h>

#include "HdmiConstDef.h"
#include "Debug.h"

//#define ID_NAME_PARE(x) {x,#x}

//#define EVENT_PLUG_IN                   (1)
//#define EVENT_PLUG_OUT                  (0)

// sync to RtkTVSystem.java
//#define TV_SYSTEM_AUTO_MODE_OFF         (0)
//#define TV_SYSTEM_AUTO_MODE_HDMI_EDID   (2)

#define DPTX_MODE_OFF                   (0)
#define DPTX_MODE_ON                    (1)

#define DPTX_STATE_SYSFS                "/sys/devices/virtual/switch/dptx/state"

#define PROPERTY_DPTX_START             "vendor.rtk.dptx.service.start"

#define DP_HIDL_OUTPUT_FORMAT_ASSIGN(x,y)      \
    {                                       \
        x.mode          = y.mode;           \
        x.vic           = y.vic;            \
        x.display_mode  = y.display_mode;   \
        x.reserved1     = y.reserved1;      \
    }

#define DP_HIDL_OUTPUT_FORMAT_ASSIGN_PT(px,y)  \
    {                                       \
        px->mode          = y.mode;         \
        px->vic           = y.vic;          \
        px->display_mode  = y.display_mode; \
        px->reserved1     = y.reserved1;    \
    }

typedef struct _DPTX_FORMAT_SUPPORT {
    uint8_t mVic;
    uint8_t mReserved1;
    uint8_t mReserved2;
    uint8_t mReserved3;

    _DPTX_FORMAT_SUPPORT()
    {
        mVic = 0;
        mReserved1 = 0;
        mReserved2 = 0;
        mReserved3 = 0;
    }

    _DPTX_FORMAT_SUPPORT(uint8_t vic)
    {
        mVic = vic;
        mReserved1 = 0;
        mReserved2 = 0;
        mReserved3 = 0;
    }

} DPTX_FORMAT_SUPPORT;

typedef struct _DPTX_OUTPUT_FORMAT {
    uint8_t mode; // don't care
    uint8_t vic;
    uint8_t display_mode;
    uint8_t reserved1;
} DPTX_OUTPUT_FORMAT;

// --------- following structs is copied from hal header
/*
struct dptx_format_support {
	unsigned char vic;
	unsigned char reserved1;
	unsigned char reserved2;
	unsigned char reserved3;
};

struct dptx_support_list {
	struct dptx_format_support tx_support[25];
	unsigned int tx_support_size;
};

struct dptx_format_setting {
    unsigned char mode;
	unsigned char vic;
    unsigned char display_mode; // same source, different source..
	unsigned char reserved1;
};
*/

// --------------------------------------------------------

static inline int32_t _readDPTxState()
{
    FILE *fd = fopen(DPTX_STATE_SYSFS, "r");
    int32_t plugged = 0;

    if(fd != NULL) {
        char buf[32]={'\0'};
        fread(buf,1,32,fd);
        plugged = atoi(buf);
        fclose(fd);
    }

    return plugged;
}

static const char * _getVICString(HDMI_VIC_ENUM vic)
{
    size_t len = sizeof(sVICInfo)/sizeof(VIC_INFO);
    for(size_t i=0;i<len;i++) {
        if(vic == sVICInfo[i].id) {
            return sVICInfo[i].name;
        }
    }

    ALOGE("[%s] vic:%d not found",__FUNCTION__,vic);

    CHECK(false);

    return "ERROR";
}

#endif
