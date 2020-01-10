#ifndef _DEINTERLACE_CALLBACK_H_
#define _DEINTERLACE_CALLBACK_H_

#include <cutils/native_handle.h>

class DeInterlaceCallback {

public:
    virtual ~DeInterlaceCallback();
    virtual void onInputBufferReturned(const buffer_handle_t &buf) = 0;
    virtual void onOutputBufferAvailable(const buffer_handle_t &buf) = 0;
};


#endif
