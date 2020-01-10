#ifndef REALTEK_HARDWARE_REALTEKDVCPSERVICE_H
#define REALTEK_HARDWARE_REALTEKDVCPSERVICE_H


#include <vector>
#include <utils/Mutex.h>
#include <pthread.h>
#include <IDVControlPathService.h>
#include "RtkControlPath.h"


using namespace std;

namespace android {

class RealtekDVControlPathService : public BnDVControlPathService,
                            private IBinder::DeathRecipient
{
public:
    RealtekDVControlPathService();
    ~RealtekDVControlPathService();

    
	bool SendShareMemoryToFW_service();
	bool Rtk_DV_Metadata_to_reg_service(DV_CP_SERVICE_SFD dv_sfd);


    void registerEventListener(const sp<IEventListener> &l);
    void unregisterEventListener(const sp<IEventListener> &l);

    // binder died handling
    virtual void binderDied(const wp<IBinder>& who);

private:
    // hdmi tx uevent monitor thread
    pthread_t mUeventThread;
    Vector<sp<IEventListener>> mListeners;

    Mutex mRegistrationLock;
    Mutex mTurnOffHdmiLock;

    bool mThreadAlive;
    int mediaLinkMode;
  
    int getPropertyInt(const char *key, int dft);
    void setPropertyInt(const char *key, int value);

    // internal thread related
    static void *pthread_entry(void *ptr);
    static void *pthread_entry_hdmi(void *ptr);
};

}; // namespace android

#endif
