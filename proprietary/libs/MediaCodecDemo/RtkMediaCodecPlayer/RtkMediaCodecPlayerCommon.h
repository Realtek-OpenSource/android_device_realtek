/*
 * Copyright (c) 2016 Realtek Semiconductor Corp.
 */

#ifndef _RTK_MEDIACODEC_PLAYER_COMMON_H_

#define _RTK_MEDIACODEC_PLAYER_COMMON_H_

#include <binder/IMemory.h>
#include <utils/Log.h>
#include <utils/RefBase.h>
#include <media/stagefright/foundation/AHandler.h>
#include <media/stagefright/foundation/ALooper.h>
#include <media/stagefright/foundation/AMessage.h>
#include <media/stagefright/foundation/ADebug.h>
#include <media/stagefright/foundation/ABuffer.h>

namespace android {
	
typedef struct _VIDEO_FORMAT {
    int32_t width;              // resolution-width
    int32_t height;             // resolution-height
    int32_t fps;                // frame-rate
    int32_t bitrate;            // bit/s
    int32_t iframeInterval;     // the frequency of key frames
    int32_t deinterlace;        // [0]AUTO_DEINT [1]FORCE_DEINT [2]FORCE_PROCESSIVE
    int32_t bitrateMode;        // [0]Disable [1]Variable [2]Constant [3] VariableSkipFrames [4]ConstantSkipFrames
    int32_t level;
    int32_t profile;            // [0]AVCProfileHigh [1]AVCProfileBaseline [2]AVCProfileMain
} VIDEO_FORMAT;

typedef struct _AUDIO_FORMAT {
    int32_t channelCount;		// the number of channels
    int32_t channelMode;        // not used
    int32_t sampleRate;         // sample rate		
    int32_t bitrate;            // bit/s
} AUDIO_FORMAT;

typedef struct _AV_FORMAT_FORMAT {
    VIDEO_FORMAT videoFmt;
    AUDIO_FORMAT audioFmt;
} AV_FORMAT;

typedef struct _RtkTranscodeConfig {
    int outputType;
    int outputFormat;
    int fileDesc;
    const char *fileName;
    sp<IMemory> ashmemData;
    sp<IMemory> ashmemInfo;
    const char *udpIp;
    int udpPort;
    bool rtpHeader;
} RtkTranscodeConfig;

enum {
    SourceTypeFile = 0,
    SourceTypeUsbCamera,
    SourceTypeHdmiRx,
    SourceTypeMixer1,
    SourceTypeV1,
    SourceTypeMax,
};

enum {
    CODEC_AUDIO_ONLY = 1 << 0,
    CODEC_VIDEO_ONLY = 1 << 1,
};

enum {
    FILE_PATH,
    FILE_HANDLE,
};

enum {
    OUT_FORMAT_TS,
    OUT_FORMAT_MP4,
    OUT_FORMAT_MAX
};

typedef struct _CAMERA_SNAPSHOT_PARA {
    int format;             //input, PIXEL_FORMAT_NV21, PIXEL_FORMAT_ARGB, PIXEL_FORMAT_JPEG
    int x;                  //input
    int y;                  //input
    int width;              //input
    int height;             //input
    int outWidth;           //input
    int outHeight;          //input
    int size;               //output
    unsigned char *data;    //output
} CAMERA_SNAPSHOT_PARA;

enum {
    PIXEL_FORMAT_NV21,
    PIXEL_FORMAT_ARGB,
    PIXEL_FORMAT_JPEG,
    PIXEL_FORMAT_YV12,
};

enum {
    CHANNEL_MODE_NONE,
    CHANNEL_MODE_LEFT,
    CHANNEL_MODE_RIGHT,
};

/* For Status reference */
enum {
    /* For common */
    kWhatEOS = 0x20170330,
    kWhatVideoInstantFPS,
    kWhatVideoAverageFPS,
    kWhatVideoPTS,
    /* Camera status failed */
    kWhatCameraErr,
};

#define KWHAT_STOP                      0x20161201
#define KWHAT_SET_SURFACE               0x20161202
#define ITEM_VIDEO                      0x20161203
#define ITEM_AUDIO                      0x20161204
#define NO_AUDIO_TRACK                  0x20161205
#define NO_VIDEO_TRACK                  0x20161206

#define AMSG_CODEC_ERR_STATUS           "err"

/* For Setup decoder / encoder */
#define AMSG_MIME                        "mime"
#define ABUFFER_MEDIACODE_BUFFER         "buffer"
#define AMSG_BITRATE                     "bitrate"
#define AMSG_DATA_SOURCE                 "data-source"
#define AMSG_PATH                        "path"
#define AMSG_FILE_ID                     "FileId"
#define AMSG_FILE_OFFSET                 "FileOffset"
#define AMSG_FILE_LENGTH                 "FileLen"
#define AMSG_ENCODE_TYPE                 "type"
#define AMSG_TARTGET_FORMAT   	         "target-format"
#define AMSG_CALCULATE_FPS               "calculate-fps"
#define AMSG_FREE_RUN                    "free-run"
#define AMSG_SET_RENDER_VIDEO            "video"
#define AMSG_SET_RENDER_AUDIO            "audio"
#define AMSG_SET_TRANSCODE               "transcode"
#define AMSG_SET_TUNNELED_PLAYBACK       "tunneled-playback"
#define AMSG_SET_PLAYBACK                "playback"
#define AMSG_STOP_ITEM                   "stop-item"
#define AMSG_TRACK_ITEM                  "track-item"
#define AMSG_OUTPUT_FORMAT               "output-format"
#define AMSG_MUXER                       "muxer"
/* Video Parameter */
#define AMSG_VIDEO_WIDTH                 "width"
#define AMSG_VIDEO_HEIGHT                "height"
#define AMSG_VIDEO_FRAMERATE             "frame-rate"
#define AMSG_VIDEO_INTERLACED            "video-de-interlace"
#define AMSG_VIDEO_COLOR_FORMAT          "color-format"
#define AMSG_VIDEO_PROFILE               "profile"
#define AMSG_VIDEO_LEVEL                 "level"
#define AMSG_VIDEO_BITE_RATE_MODE        "bitrate-mode"
#define AMSG_VIDEO_IFRAME_INTERVAL       "i-frame-interval"
#define AMSG_VIDEO_SURFACE               "surface"
#define AMSG_VIDEO_INSTANT_FPS           "instant-fps"
#define AMSG_VIDEO_AVERAGE_FPS           "average-fps"
#define AMSG_VIDEO_DEC_INSTANT_FPS       "dec-instant-fps"
#define AMSG_VIDEO_ENC_INSTANT_FPS       "enc-instant-fps"
#define AMSG_VIDEO_DEC_AVERAGE_FPS       "dec-average-fps"
#define AMSG_VIDEO_ENC_AVERAGE_FPS       "enc-average-fps"
#define AMSG_VIDEO_CODEC_TYPE            "codec-type"
#define AMSG_VIDEO_PTS                   "video-pts"
/* Audio Parameter */
#define AMSG_AUDIO_CHANNELCOUNT          "channel-count"
#define AMSG_AUDIO_SAMPLERATE            "sample-rate"
#define AMSG_AUDIO_AAC_PROFILE           "aac-profile"
#define AMSG_AUDIO_MAX_INPUT             "max-input-size"
#define AMSG_AUDIO_SOURCE                "audio-source"
#define AMSG_AUDIO_CHANNELMODE           "channel-mode"
/* Camera Parameter */      
#define AMSG_CAMERA_TYPE                 "camera-type"
#define AMSG_CAMERA_ID                   "camera-id"
#define AMSG_CLIENT_NAME                 "client-name"
#define AMSG_CAMERA_SP                   "camera-sp"
#define AMSG_PIXELFORMAT                 "pixfmt"
#define AMSG_CAMERA_PARAM                "camera-param"
#define AMSG_COORDINATE_X                "x"
#define AMSG_COORDINATE_Y                "y"
#define AMSG_OUTPUT_WIDTH                "outw"
#define AMSG_OUTPUT_HEIGHT               "outh"
#define AMSG_CAM_PREVIEW_WIDTH           "campw"
#define AMSG_CAM_PREVIEW_HEIGHT          "camph"
#define AMSG_SURFACE                     "surface"
#define AMSG_VIRT_ADDR                   "virt"
#define AMSG_SIZE                        "size"
#define AMSG_IMEMORY_PTR                 "imemptr"   // added for binder interface
#define AMSG_CODE_ERR_STATUS             "err"
/* Writeback Parameter*/
#define AMSG_VIDEO_WRITE_BACK_TYPE       "WB-type"
#define ABUFFER_META_TIMESTAMP          "timeUs"
#define ABUFFER_META_FLAGS              "flags"
#define AMSG_VIDEO_VOWRITE_BACK          "YUV422"
#define AMSG_AGENT                       "agent"

/* misc */
#define AMSG_HDMIRX_VIDEO_STATE         "rx-video"

static inline void replyResponse(const sp<AMessage> &msg, const sp<AMessage> &response)
{
    sp<AReplyToken> replyID;
    CHECK(msg->senderAwaitsResponse(&replyID));
    response->postReply(replyID);
}

static inline void replyErrorStatus(const sp<AMessage> &msg, int32_t err)
{
    sp<AMessage> response = new AMessage;
    response->setInt32(AMSG_CODEC_ERR_STATUS, err);
    replyResponse(msg, response);
}

static inline status_t postAndAwaitResponse(const sp<AMessage> &msg, sp<AMessage> *response)
{
    status_t err = msg->postAndAwaitResponse(response);

    if (err != OK)
        return err;
    if (!(*response)->findInt32(AMSG_CODEC_ERR_STATUS, &err))
        err = OK;
    return err;
}

} // namespace android

#endif //_RTK_MEDIACODEC_PLAYER_COMMON_H_
