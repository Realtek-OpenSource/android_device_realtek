#define LOG_TAG "IDVControlPathService"

#include <utils/Log.h>
#include <IDVControlPathService.h>

namespace android {

// BpInterface
class BpDVControlPathService: public BpInterface<IDVControlPathService>
{
public:
    BpDVControlPathService(const sp<IBinder>& impl)
        : BpInterface<IDVControlPathService>(impl)
    {
    }

	virtual bool SendShareMemoryToFW_service()
    {
        ALOGD("%s",__FUNCTION__);
        Parcel data, reply;
        data.writeInterfaceToken(IDVControlPathService::getInterfaceDescriptor());
        remote()->transact(BnDVControlPathService::SEND_SHARE_MEMORY_TO_FW, data, &reply);
        return (bool) reply.readInt32();
    }
	virtual bool Rtk_DV_Metadata_to_reg_service(DV_CP_SERVICE_SFD dv_sfd)
    {
        ALOGD("%s",__FUNCTION__);
        Parcel data, reply;

        int sfd[6];//need to modify
        sfd[0]= dv_sfd.rtk_dv_cp_param_fd;
        sfd[1]= dv_sfd.rtk_dv_cp_param_fd_length;
        sfd[2]= dv_sfd.rtk_dv_vo_register_fd;
        sfd[3]= dv_sfd.rtk_dv_vo_register_fd_length;
        sfd[4]= dv_sfd.rtk_hdr_10_infoframe_t_fd;
        sfd[5]= dv_sfd.rtk_hdr_10_infoframe_t_fd_length;

        data.writeInterfaceToken(IDVControlPathService::getInterfaceDescriptor());
        //data.writeInt32Array(6, sfd);


     ALOGD("111%s",__FUNCTION__);

        data.writeFileDescriptor(sfd[0],false);


        data.writeInt32(sfd[1]);
  ALOGD("writeFD:%d length:%d\n",sfd[0],sfd[1]);


        data.writeFileDescriptor(sfd[2],false);
        data.writeInt32(sfd[3]);

        data.writeFileDescriptor(sfd[4],false);
        data.writeInt32(sfd[5]);
  

        remote()->transact(BnDVControlPathService::DV_METADATA_TO_REG, data, &reply);
        return (bool) reply.readInt32();
    }

    void registerEventListener(const sp<IEventListener> &l)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IDVControlPathService::getInterfaceDescriptor());
        sp<IBinder> b(l->asBinder(l));
        data.writeStrongBinder(b);
        remote()->transact(BnDVControlPathService::REGISTER_EVENT_LISTENER, data, &reply);
    }

    void unregisterEventListener(const sp<IEventListener> &l)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IDVControlPathService::getInterfaceDescriptor());
        sp<IBinder> b(l->asBinder(l));
        data.writeStrongBinder(b);
        remote()->transact(BnDVControlPathService::UNREGISTER_EVENT_LISTENER, data, &reply);
    }
};

IMPLEMENT_META_INTERFACE(DVControlPathService, "realtek.hardware.IDVControlPathService");

// ------------------------------------------------------------------

// BnInterface
status_t BnDVControlPathService::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    ALOGD("BnDVControlPathService onTransact");
    switch(code) {
    case SEND_SHARE_MEMORY_TO_FW: {
        
        ALOGD("[CP]SEND_SHARE_MEMORY_TO_FW!! onTransact");
        CHECK_INTERFACE(IDVControlPathService, data, reply);
        reply->writeInt32(SendShareMemoryToFW_service());
        return NO_ERROR;
    } break;
    case DV_METADATA_TO_REG: {

        ALOGD("[CP]DV_METADATA_TO_REG!! onTransact");
        CHECK_INTERFACE(IDVControlPathService, data, reply);

        DV_CP_SERVICE_SFD dv_sfd;
        
        dv_sfd.rtk_dv_cp_param_fd = data.readFileDescriptor();
        dv_sfd.rtk_dv_cp_param_fd_length = data.readInt32();
        dv_sfd.rtk_dv_vo_register_fd =  data.readFileDescriptor();
        dv_sfd.rtk_dv_vo_register_fd_length = data.readInt32();
        dv_sfd.rtk_hdr_10_infoframe_t_fd = data.readFileDescriptor();
        dv_sfd.rtk_hdr_10_infoframe_t_fd_length = data.readInt32();



  ALOGD("readFD:%d length:%d\n", dv_sfd.rtk_dv_cp_param_fd, dv_sfd.rtk_dv_cp_param_fd_length);

         
        reply->writeInt32(Rtk_DV_Metadata_to_reg_service(dv_sfd));
        return NO_ERROR;
    } break;
    case REGISTER_EVENT_LISTENER: {
        CHECK_INTERFACE(IHDMIService, data, reply);
        sp<IEventListener> l =
            interface_cast<IEventListener>(data.readStrongBinder());
        registerEventListener(l);
        return NO_ERROR;
    } break;
    case UNREGISTER_EVENT_LISTENER: {
        CHECK_INTERFACE(IHDMIService, data, reply);
        sp<IEventListener> l =
            interface_cast<IEventListener>(data.readStrongBinder());
        unregisterEventListener(l);
        return NO_ERROR;
    } break;
    default:
        return BBinder::onTransact(code, data, reply, flags);
    }
}

// ------------------------------------------------------------------

}; // namespace
