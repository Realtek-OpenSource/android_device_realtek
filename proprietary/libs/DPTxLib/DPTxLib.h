#ifndef _DPTX_LIB_
#define _DPTX_LIB_

#include <utils/Mutex.h>
#include <utils/Errors.h>
#include <utils/Vector.h>
#include <utils/RefBase.h>

#include "DPTxConstDef.h"

using namespace android;

//typedef void (*handle_dptx_event)(int32_t event);

typedef struct dptxlib_module_callback {
    void (*handle_dptx_event)(
            const struct dptxlib_module_callback *callback,
            int32_t event,
            int32_t vic,
            int32_t type);

} dptxlib_module_callback_t;

namespace realtek {

class DPTxLib : public RefBase {

public:
    DPTxLib();
    ~DPTxLib();

    //handle_dptx_event         mEventHandler;
    dptxlib_module_callback_t * mCallback;
    Mutex                       mLock;
    Vector<DPTX_FORMAT_SUPPORT> mEDIDSupportList;

    bool                        tryGetService();

    void                        setCallback();
    void                        removeCallback();

    status_t                    readOutputFormat(DPTX_OUTPUT_FORMAT *pRst);
    status_t                    saveOutputFormat(const DPTX_OUTPUT_FORMAT &format);

    int32_t                     readEdidAutoMode();
    status_t                    saveEdidAutoMode(int32_t value);
    bool                        getDPTxEDIDReady();
    int32_t                     setOutputFormat(const DPTX_OUTPUT_FORMAT &format,
                                    int32_t flags);
    status_t                    getEDIDSupportList();
    status_t                    getCurrentOutputFormat(DPTX_OUTPUT_FORMAT *pRst);
    int32_t                     hasDPTxBackend();
    bool                        dpIsOn(); // pure client side implementation

private:
    void *                      getDPTxControl();

};

}; // namespace realtek

#endif
