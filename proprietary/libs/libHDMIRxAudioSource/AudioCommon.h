#ifndef _AUDIO_COMMOM_H_
#define _AUDIO_COMMOM_H_

//#define HDMIRX_EVENT_AUDIO_STATE_OFF        (0)
//#define HDMIRX_EVENT_AUDIO_STATE_ON         (1)


#define HDMIRX_AUDIO_INFO_SYSFS             \
    "/sys/devices/virtual/video4linux/video250/hdmirx_audio_info"
#define HDMIRX_AUDIO_STATE_SYSFS            \
    "/sys/devices/virtual/switch/rx_audio/state"
#define HDMIRX_VIDEO_STATE_SYSFS            \
    "/sys/devices/virtual/switch/rx_video/state"
#define HDMIRX_AUDIO_STATE_MSG              \
    "devices/virtual/switch/rx_audio"
#define HDMIRX_VIDEO_STATE_MSG              \
    "devices/virtual/switch/rx_video"

// event type management

#define EVENT_NONE          (-1)
#define EVENT_RX_VIDEO      ( 0)
#define EVENT_RX_AUDIO      ( 1)

// audio info struct
typedef struct hdmirx_audio_info {
    int32_t mReady;
    int32_t mFreq;
    //int32_t mSPDIFType;
    //int32_t mCodingType;
    int32_t mChannelCount;
    //int32_t mSamplingFreq;
    //int32_t mSamplingSize;
} hdmirx_audio_info_t;

// common helper functions.
static inline void dumpHDMIRxAudioInfo(hdmirx_audio_info_t *pInfo)
{
    ALOGD("Ready:%d",pInfo->mReady);
    ALOGD("Freq :%d",pInfo->mFreq);
    ALOGD("Chn  :%d",pInfo->mChannelCount);
}

static inline int32_t getHDMIRxVideoState()
{
    char buf[32];
    memset(buf,0x0,32);

    FILE *fd = fopen(HDMIRX_VIDEO_STATE_SYSFS,"r");
    if(fd != NULL) {
        fread(buf,1,32,fd);
        int val = atoi(buf);
        fclose(fd);
        return val;
    }else{
        return 0;
    }
}

static inline int32_t getHDMIRxAudioState()
{
    char buf[32];
    memset(buf,0x0,32);

    FILE *fd = fopen(HDMIRX_AUDIO_STATE_SYSFS,"r");
    if(fd != NULL) {
        fread(buf,1,32,fd);
        int val = atoi(buf);
        fclose(fd);
        return val;
    }else{
        return 0;
    }
}

static inline void parseLineInfo(
        char *key,
        char *value,
        hdmirx_audio_info_t *pInfo)
{
    if(strcmp(key,"Ready")==0)
    {
        pInfo->mReady = atoi(value);
    }
    else if(strcmp(key,"Freq")==0)
    {
        pInfo->mFreq = atoi(value);
    }
    else if(strcmp(key,"Channel Count") == 0)
    {
        char *val = strchr(value, ' ');
        *val = '\0';
        pInfo->mChannelCount = atoi(value);
    }
    else
    {
        // skip
    }
}

static inline void getHDMIRxAudioInfo(hdmirx_audio_info_t *pInfo)
{
    FILE *fd = fopen(HDMIRX_AUDIO_INFO_SYSFS,"r");
    if(fd != NULL) {
        size_t len = 0;
        char *line = NULL;
        while(1){
            ssize_t size = getline(&line, &len, fd);
            if(size == -1)
                break;

            // has ":" or not
            char *val = strchr(line, ':');
            if(val == NULL){
                continue;
            }

            *val = '\0';
            char *value_pt = val+1;
            parseLineInfo(line,value_pt,pInfo);
        }

        if(line != NULL) {
            free(line);
        }

        fclose(fd);
    }
}

static inline const char * event2Str(int32_t event)
{
    switch(event)
    {
        case EVENT_NONE:
            return "EVENT_NONE";
        case EVENT_RX_VIDEO:
            return "EVENT_RX_VIDEO";
        case EVENT_RX_AUDIO:
            return "EVENT_RX_AUDIO";
        default:
            return "EVENT_ERROR";
    }
}
#endif
