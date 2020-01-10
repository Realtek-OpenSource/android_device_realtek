#ifndef REALTEK_DVCP_CLIENT
#define REALTEK_DVCP_CLIENT

#include <IDVControlPathService.h>

namespace android {

class DVControlPathClient : public DVControlPath
{
public:
    DVControlPathClient();
    ~DVControlPathClient();
	
	bool Rtk_DV_Metadata_to_reg_service(DV_CP_SERVICE_SFD dv_sfd);
    bool SendShareMemoryToFW_service();
    void registerEventListener(const sp<IEventListener> &l);
    void unregisterEventListener(const sp<IEventListener> &l);

private:
    sp<IDVControlPathService> mService;
    sp<IEventListener> mListener;
};

}; // namespace android

#endif // REALTEK_DVCP_CLIENT
