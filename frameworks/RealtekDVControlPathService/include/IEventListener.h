#ifndef REALTEK_HARDWARE_IEVENT_LISTENER_H
#define REALTEK_HARDWARE_IEVENT_LISTENER_H

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>

namespace android {

class EventListener : public virtual RefBase
{
public:
    EventListener() {}
    virtual ~EventListener() {}

    virtual void onEvent(int event, int arg1) = 0;

};

class IEventListener : public EventListener, public IInterface
{
public:
    DECLARE_META_INTERFACE(EventListener)
};

class BnEventListener : public BnInterface<IEventListener>
{
public:
    virtual status_t onTransact(uint32_t code, const Parcel& data,
            Parcel* reply, uint32_t flags = 0);
};

}; // namespace android

#endif // REALTEK_HARDWARE_IEVENT_LISTENER_H
