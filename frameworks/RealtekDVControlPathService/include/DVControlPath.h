#ifndef REALTEK_HARDWARE_IDVCP_H
#define REALTEK_HARDWARE_IDVCP_H

#include <utils/RefBase.h>
#include "IEventListener.h"



namespace android {

typedef struct  {
	int rtk_dv_cp_param_fd;
	int rtk_dv_cp_param_fd_length;
	int rtk_dv_vo_register_fd;
	int rtk_dv_vo_register_fd_length;
	int rtk_hdr_10_infoframe_t_fd;
	int rtk_hdr_10_infoframe_t_fd_length;
} DV_CP_SERVICE_SFD;


class DVControlPath : public virtual RefBase
{
public:
    DVControlPath() {}
    virtual ~DVControlPath() {}
	virtual bool Rtk_DV_Metadata_to_reg_service(DV_CP_SERVICE_SFD dv_sfd) = 0;
	virtual bool SendShareMemoryToFW_service() = 0;

    // listener
    virtual void registerEventListener(const sp<IEventListener> &l) = 0;
    virtual void unregisterEventListener(const sp<IEventListener> &l) = 0;
};

}; // namespace android

#endif
