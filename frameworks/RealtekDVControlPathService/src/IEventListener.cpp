#define LOG_TAG "EventListener"

#include <utils/Log.h>
#include "IEventListener.h"

namespace android {

enum {
    ON_EVENT = IBinder::FIRST_CALL_TRANSACTION,
};

class BpEventListener : public BpInterface<IEventListener>
{
public:
    BpEventListener(const sp<IBinder>& impl)
        : BpInterface<IEventListener>(impl) {}

    ~BpEventListener()
    {
        ALOGD("~BpEventListener()");
    }

    virtual void onEvent(int event, int arg1)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IEventListener::getInterfaceDescriptor());
        data.writeInt32(event);
        data.writeInt32(arg1);
        remote()->transact(ON_EVENT, data, &reply, IBinder::FLAG_ONEWAY );
    }
};

IMPLEMENT_META_INTERFACE(EventListener, "realtek.EventListener")

status_t BnEventListener::onTransact(uint32_t code, const Parcel& data,
        Parcel* reply, uint32_t flags) {
    switch (code) {
        case ON_EVENT:
            CHECK_INTERFACE(IEventListener, data, reply);
            int event = data.readInt32();
            int arg1 = data.readInt32();
            onEvent(event,arg1);
            return NO_ERROR;
    }
    return BBinder::onTransact(code, data, reply, flags);
}

};  // namespace android
