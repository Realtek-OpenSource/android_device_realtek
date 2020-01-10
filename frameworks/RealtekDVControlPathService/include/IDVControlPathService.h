#ifndef REALTEK_HARDWARE_IDVControlPathSERVICE_H
#define REALTEK_HARDWARE_IDVControlPathSERVICE_H

#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <DVControlPath.h>

namespace android {

class IDVControlPathService : public DVControlPath, public IInterface
{
public:
    enum {
		DV_METADATA_TO_REG = IBinder::FIRST_CALL_TRANSACTION,
        SEND_SHARE_MEMORY_TO_FW,
			
        REGISTER_EVENT_LISTENER,
        UNREGISTER_EVENT_LISTENER,
    };

    DECLARE_META_INTERFACE(DVControlPathService)

};

// --------------------------------------------------------------------------

// BnInterface
class BnDVControlPathService: public BnInterface<IDVControlPathService>
{
public:
    virtual status_t    onTransact( uint32_t code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    uint32_t flags = 0);

};

}; // namespace android

#endif // REALTEK_HARDWARE_IDVControlPathSERVICE_H
