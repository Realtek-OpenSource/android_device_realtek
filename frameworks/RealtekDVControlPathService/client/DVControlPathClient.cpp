#define LOG_TAG "DVControlPathClient"

#include <utils/Log.h>
#include <binder/IServiceManager.h>
#include <DVControlPathClient.h>

using namespace android;

namespace android {

/**
 * A simple EventListener
 */
class MyListener : public BnEventListener
{
public:
    ~MyListener()
    {
        ALOGD("~MyListener");
    }

    void onEvent(int event, int arg1)
    {
        ALOGD("onEvent event %d arg1 %d",event,arg1);
    }

};

DVControlPathClient::DVControlPathClient()
{
    ALOGD("DVControlPathClient()");
    sp<IServiceManager> sm = defaultServiceManager();
    sp<IBinder> binder = sm->getService(String16("realtek.DVCP"));
    mService = interface_cast<IDVControlPathService>(binder);
    mListener = new MyListener();
    mService->registerEventListener(mListener);
}

DVControlPathClient::~DVControlPathClient()
{
    ALOGD("~DVControlPathClient()");
    mService->unregisterEventListener(mListener);
    mService = NULL;
}

bool
DVControlPathClient::Rtk_DV_Metadata_to_reg_service(DV_CP_SERVICE_SFD dv_sfd)
{
    return mService->Rtk_DV_Metadata_to_reg_service(dv_sfd);
}

bool
DVControlPathClient::SendShareMemoryToFW_service()
{
    return mService->SendShareMemoryToFW_service();
}


void
DVControlPathClient::registerEventListener(const sp<IEventListener> &l)
{
    mService->registerEventListener(l);
}

void
DVControlPathClient::unregisterEventListener(const sp<IEventListener> &l)
{
    mService->unregisterEventListener(l);
}

};  // namespace android
