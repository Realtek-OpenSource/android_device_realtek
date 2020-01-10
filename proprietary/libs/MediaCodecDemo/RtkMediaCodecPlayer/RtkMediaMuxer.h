/*
 * Copyright (c) 2016 Realtek Semiconductor Corp.
 */

#ifndef _RTK_MEDIA_MUXER_H_
#define _RTK_MEDIA_MUXER_H_

#include <utils/Errors.h>
#include <utils/RefBase.h>
#include <utils/Vector.h>
#include <utils/threads.h>

#include <media/stagefright/foundation/ABase.h>
#include <media/stagefright/foundation/Mutexed.h>

namespace android {

struct ABuffer;
struct AMessage;
struct MediaAdapter;
class MediaBuffer;
struct MediaSource;
class MetaData;
struct MediaWriter;

struct RtkMediaMuxer : public RefBase {
public:
    enum OutputFormat {
        OUTPUT_FORMAT_MPEG_4 = 0,
        OUTPUT_FORMAT_WEBM   = 1,
#ifdef RTK_PLATFORM
        OUTPUT_FORMAT_MPEG2TS  = 2,
#endif
        OUTPUT_FORMAT_LIST_END // must be last - used to validate format type
    };

    RtkMediaMuxer(int fd, OutputFormat format);

    RtkMediaMuxer(int port, const char *ip, bool enableRtp, OutputFormat format); //add by self
    
    RtkMediaMuxer(FILE *f_fd, OutputFormat format); //add by self
    
    RtkMediaMuxer(sp<IMemory> data, sp<IMemory> info, bool enableRtp, OutputFormat format); //add by self
    
    RtkMediaMuxer(sp<IMemory> data, sp<IMemory> info, bool enableRtp, int port, const char *ip, OutputFormat format); //add by self
    
    virtual ~RtkMediaMuxer();

    /**
     * Add a track with its format information. This should be
     * called before start().
     * @param format the track's format.
     * @return the track's index or negative number if error.
     */
    ssize_t addTrack(const sp<AMessage> &format);

    /**
     * Start muxing. Make sure all the tracks have been added before
     * calling this.
     */
    status_t start();

    /**
     * Set the orientation hint.
     * @param degrees The rotation degrees. It has to be either 0,
     *                90, 180 or 270.
     * @return OK if no error.
     */
    status_t setOrientationHint(int degrees);

    /**
     * Set the location.
     * @param latitude The latitude in degree x 1000. Its value must be in the range
     * [-900000, 900000].
     * @param longitude The longitude in degree x 1000. Its value must be in the range
     * [-1800000, 1800000].
     * @return OK if no error.
     */
    status_t setLocation(int latitude, int longitude);

    /**
     * Stop muxing.
     * This method is a blocking call. Depending on how
     * much data is bufferred internally, the time needed for stopping
     * the muxer may be time consuming. UI thread is
     * not recommended for launching this call.
     * @return OK if no error.
     */
    status_t stop();

    /**
     * Send a sample buffer for muxing.
     * The buffer can be reused once this method returns. Typically,
     * this function won't be blocked for very long, and thus there
     * is no need to use a separate thread calling this method to
     * push a buffer.
     * @param buffer the incoming sample buffer.
     * @param trackIndex the buffer's track index number.
     * @param timeUs the buffer's time stamp.
     * @param flags the only supported flag for now is
     *              MediaCodec::BUFFER_FLAG_SYNCFRAME.
     * @return OK if no error.
     */
    status_t writeSampleData(const sp<ABuffer> &buffer, size_t trackIndex,
                             int64_t timeUs, uint32_t flags) ;

    struct MuxerState {
        MuxerState() : mMuxerStarted(false) {}
        bool mMuxerStarted;
        Condition mCond;
    };
    Mutexed<MuxerState> mMuxerState;

private:
    const OutputFormat mFormat;
    sp<MediaWriter> mWriter;
    Vector< sp<MediaAdapter> > mTrackList;  // Each track has its MediaAdapter.
    sp<MetaData> mFileMeta;  // Metadata for the whole file.

    Mutex mMuxerLock;

    enum State {
        UNINITIALIZED,
        INITIALIZED,
        STARTED,
        STOPPED
    };
    State mState;

    DISALLOW_EVIL_CONSTRUCTORS(RtkMediaMuxer);
};

}  // namespace android

#endif  // _RTK_MEDIA_MUXER_H_

