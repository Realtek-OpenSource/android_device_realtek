/**
 * copyright 2016 Realtek Semiconductor
 *
 * Description:
 * A pure C/C++ binder service to control Realtek Dolby Vision Control Path
 *
 * Aurthor:
 * chenwei_yu@realtek.com
 *
 *
 */

#define LOG_TAG "RealtekDVControlPathService"



#include <string.h>
#include <utils/Log.h>
#include <cutils/properties.h>
//#include <hardware_legacy/uevent.h>

#include "hresult.h"
#include "RPCBaseDS_data.h"
#include "AudioRPC_System.h"
#include "AudioRPC_Agent.h"
#include "SVCFunc.h"
#include "RPCProxy.h"

#include "RealtekDVControlPathService.h"
#include "RealtekDVControlPathService_rpc.h"


#if 0
#include "control_path_api.h"
#include "KdmTypeFxp.h"
#include "rpu_api_common.h"
#include "rpu_ext_config.h"
#include "VdrDmUtil.h"
#endif
#include "IonAllocator.h"
#include <rtk_ion.h>

/*
#if defined (__cplusplus)
extern "C" {
#endif

#include "rvsd_dbg_md5.h"

#if defined (__cplusplus)
}
#endif
*/


namespace android {


IonAllocator *mp_dolby_vo_register_allocator= NULL;
rtk_dv_vo_register *mp_dolby_vo_register;




RealtekDVControlPathService::RealtekDVControlPathService()
{


    ALOGD("[CP][+]RealtekDVControlPathService init!\n");

    if (mp_dolby_vo_register_allocator == NULL)
    {
   

      mp_dolby_vo_register_allocator = new IonAllocator();

      mp_dolby_vo_register_allocator->Allocate(sizeof(rtk_dv_vo_register), RTK_PHOENIX_ION_HEAP_MEDIA_MASK,
                      ION_FLAG_NONCACHED | ION_FLAG_SCPUACC | ION_FLAG_ACPUACC);

      mp_dolby_vo_register = (rtk_dv_vo_register *)mp_dolby_vo_register_allocator->mp_virtual;
    }
    

    Rtk_DV_Control_Path_Init(1);
    ALOGD("[CP][-]RealtekDVControlPathService init!\n");
}


RealtekDVControlPathService::~RealtekDVControlPathService()
{

   Rtk_DV_Control_Path_Delete();
}






//==============================================================
// endian swap table(4 bytes units)
//==============================================================
static void CP_buffer_endian_swap_4bytes(void *addr, unsigned int byte_size)
{
    unsigned int i, data;
    unsigned int *p = (unsigned int*)addr;

    if(byte_size%4 != 0)
        printf("[buffer_endian_swap size warnning]\n");

    for(i=0; i<(byte_size>>2); i++)
    {
        unsigned long b0 = *p & 0x000000ff;
        unsigned long b1 = (*p & 0x0000ff00) >> 8;
        unsigned long b2 = (*p & 0x00ff0000) >> 16;
        unsigned long b3 = (*p & 0xff000000) >> 24;
        *p = (b0 << 24) | (b1 << 16) | (b2 << 8) | b3;
        p++;
    }
}

unsigned long long ConvertVirtualToPhysical(unsigned long long address,
                                            unsigned long long physical_base,
                                            unsigned long long virtual_base)
{
    if (address == 0 || physical_base == 0 || virtual_base == 0 || address < virtual_base)
        return 0;

    unsigned long long offset = address - virtual_base;
    return physical_base + offset;
}


bool
RealtekDVControlPathService::SendShareMemoryToFW_service()
{
  //do in control path
#if 0
  ALOGD("[CP]CW!!! %s",__FUNCTION__);
   
  ALOGD("[+][CP]Rtk_DV_Control_Path_RPC_to_VO_Sink_Cap_Share_Mem:test\n");

  if (gp_ion == NULL)
  {
      ALOGD("Error, share mem is NULL,  %s:%d", __FUNCTION__, __LINE__);
      return false;
  }

  ALOGD("[+][CP]Rtk_DV_Control_Path_RPC_to_VO_Sink_Cap_Share_Mem: %p\n", gp_ion->mp_physical);
  
  CLNT_STRUCT rpc;
  VIDEO_RPC_VOUT_DV_CP_INFO cp_info;
  HRESULT *res;
  memset( &cp_info, 0, sizeof(VIDEO_RPC_VOUT_DV_CP_INFO ));


  rpc =  prepareCLNT(BLOCK_MODE | USE_INTR_BUF | SEND_AUDIO_CPU, AUDIO_SYSTEM, VERSION);

  
  cp_info.is_destroy = 0;
  cp_info.ControlPathMemAddr = (unsigned long long)gp_ion->mp_physical;

  res = VIDEO_RPC_VOUT_ToAgent_DV_ControlPath_Info_0( &cp_info, &rpc);

  ALOGD("[-][CP]Rtk_DV_Control_Path_RPC_to_VO_Sink_Cap_Share_Mem\n");

#endif
  
  return true;
}


bool RealtekDVControlPathService::Rtk_DV_Metadata_to_reg_service(DV_CP_SERVICE_SFD dv_sfd)
{
  //do in control path
#if 0

#ifdef TEST_COMMIT_REG
    ALOGD("[CP]@sfd[0]:%d [1]:%d [2]:%d\n",dv_sfd.rtk_dv_cp_param_fd, dv_sfd.rtk_dv_vo_register_fd,dv_sfd.rtk_hdr_10_infoframe_t_fd );
    ALOGD("[CP]@L[0]:%d L[1]:%d L[2]:%d\n",dv_sfd.rtk_dv_cp_param_fd_length, dv_sfd.rtk_dv_vo_register_fd_length,dv_sfd.rtk_hdr_10_infoframe_t_fd_length );

#endif

   int err = 0;


   rtk_dv_control_path_param *rtk_dv_cp_param  = (rtk_dv_control_path_param *)mmap(NULL, dv_sfd.rtk_dv_cp_param_fd_length, PROT_READ | PROT_WRITE, MAP_SHARED, dv_sfd.rtk_dv_cp_param_fd, 0);



   rtk_dv_vo_register *rtk_dv_vo_register_p  = (rtk_dv_vo_register *)mmap(NULL, dv_sfd.rtk_dv_vo_register_fd_length, PROT_READ | PROT_WRITE, MAP_SHARED, dv_sfd.rtk_dv_vo_register_fd, 0);


   rtk_hdr_10_infoframe_t *rtk_out_info_frame  = (rtk_hdr_10_infoframe_t *)mmap(NULL, dv_sfd.rtk_hdr_10_infoframe_t_fd_length, PROT_READ | PROT_WRITE, MAP_SHARED, dv_sfd.rtk_hdr_10_infoframe_t_fd, 0);

#ifdef TEST_COMMIT_REG
   ALOGD("[CP]@rtk_dv_cp_param::%x [1]:%x [2]:%x\n",rtk_dv_cp_param, rtk_dv_vo_register_p,rtk_out_info_frame );
   ALOGD("[CP]@size:[0]%x [1]:%x [2]:%x\n",sizeof(rtk_dv_control_path_param),sizeof(rtk_dv_vo_register),sizeof(rtk_hdr_10_infoframe_t));


#endif




    dv_control_path_param_t dv_cp_param;
    dv_vo_register dv_vo_register;
    hdr_10_infoframe_t out_info_frame;

    memset(&dv_cp_param, 0, sizeof(dv_cp_param));
    memset(&dv_vo_register, 0, sizeof(dv_vo_register));

    ConvertRtkToDolby(&dv_cp_param, rtk_dv_cp_param, &dv_vo_register, rtk_dv_vo_register_p, &out_info_frame, rtk_out_info_frame);

    get_Sink_and_Graphic_info_from_fw();


    //target w/h should be the same as src w/h.
    dv_cp_param.src_param.width =  cp_sink_param.target_param.width ;
    dv_cp_param.src_param.height =  cp_sink_param.target_param.height ;

    

    dv_cp_param.src_param.src_chroma_format = CF_UYVY;
    dv_cp_param.src_param.src_yuv_range = SIG_RANGE_FULL;
    dv_cp_param.src_param.src_bit_depth = 10;

    populate_graphics_param( &(cp_sink_param.graphics_param), cp_sink_param.g_format);


    /* Create the hdr10 info frame from dolby vision metadata, hdr10 sei message or statically (SDR)
       This step has to be performed before commit_reg because in DoVi in, HDR10 out use case all dynamic
       metadata including L6 is removed.
    */

    if ((cp_sink_param.output_format == FORMAT_HDR10) /*|| unrec_vsvdb*/) {
       get_info_frame(h_ctx, &(cp_sink_param.target_param), dv_cp_param.input_format, &(dv_cp_param.src_param.hdr10_param), &(dv_cp_param.dm_metadata), &out_info_frame);
     //dump_struct(&info_frame, sizeof(info_frame), hdr10_info_frame_file, frame_cnt);
    }

 
#ifdef TEST_COMMIT_REG

    ALOGD("[CP]@1 %d %d %d %d %d\n",cp_sink_param.priority_mode, cp_sink_param.output_format,cp_sink_param.graphics_param.on, cp_sink_param.g_format, cp_sink_param.target_param.width);
    ALOGD("[CP]@2 %d %d %d %d %d  \n",cp_sink_param.target_param.height, cp_sink_param.target_param.use_ll_flag, cp_sink_param.target_param.vsvdb_length, cp_sink_param.target_param.vsvdb_version,  cp_sink_param.target_param.v1_low_latency );


    ALOGD("[CP]@3 %d %d %d %d %d \n",dv_cp_param.input_format, cp_sink_param.output_format, dv_cp_param.src_param.src_bit_depth, dv_cp_param.src_param.src_chroma_format, dv_cp_param.src_param.src_yuv_range );
    ALOGD("[CP]@4 %d %d %d %d %d\n", dv_cp_param.src_param.width, dv_cp_param.src_param.height,  dv_cp_param.src_param.hdr10_param.max_display_mastering_luminance, dv_cp_param.src_param.hdr10_param.min_display_mastering_luminance,dv_cp_param.src_param.hdr10_param.max_content_light_level);
#endif


    commit_reg(h_ctx, (signal_format_t)dv_cp_param.input_format, (signal_format_t)cp_sink_param.output_format,
                 &(dv_cp_param.dm_metadata), &(dv_cp_param.src_comp_metadata),
                &(cp_sink_param.target_param), &(cp_sink_param.graphics_param),
                &(dv_cp_param.src_param), cp_sink_param.priority_mode,
            #if IPCORE
                &(dv_vo_register.dst_dm_reg1),  &(dv_vo_register.dst_dm_reg2), &(dv_vo_register.dst_dm_reg3),
            #else
                &dst_comp_reg,
                &dst_dm_reg,
            #endif
                &(dv_vo_register.dv_lut1),&(dv_vo_register.dv_lut2));


        /* Generate or update Dolby Vision metadata for hdmi transmission */
        if (cp_sink_param.output_format == FORMAT_DOVI) {
            if (dv_cp_param.input_format == FORMAT_DOVI) {
                update_md_for_hdmi(h_ctx, &(dv_cp_param.dm_metadata));
            } else {
                get_fixed_metadata(h_ctx, &(dv_cp_param.dm_metadata));
            }
          //  write_md(p_md_current, fp_md_hdmi);
        }

    ConvertDolbyToRtk(rtk_dv_cp_param, &dv_cp_param, rtk_dv_vo_register_p, &dv_vo_register, rtk_out_info_frame, &out_info_frame);



    munmap(rtk_dv_cp_param, dv_sfd.rtk_dv_cp_param_fd_length);
    close(dv_sfd.rtk_dv_cp_param_fd);
    munmap(rtk_dv_vo_register_p, dv_sfd.rtk_dv_vo_register_fd_length);
    close(dv_sfd.rtk_dv_vo_register_fd);
    munmap(rtk_out_info_frame, dv_sfd.rtk_hdr_10_infoframe_t_fd_length);
    close(dv_sfd.rtk_hdr_10_infoframe_t_fd);



#endif

    return 0;
}


#if defined (__cplusplus)
extern "C" {
#endif

VIDEO_RPC_VOUT_GET_DV_REGISTER SendControlPathOutToFW(int argp)
{



    // return core1/2/3
    ALOGD("[CP]CW!!! %s  input:%d\n",__FUNCTION__, argp);
    VIDEO_RPC_VOUT_GET_DV_REGISTER cp_out;
    rtk_dv_control_path_param no_used1;
    rtk_hdr_10_infoframe_t  no_used2;


    memset(&no_used1, 0, sizeof(rtk_dv_control_path_param));
    memset(&no_used2, 0, sizeof(rtk_hdr_10_infoframe_t));

     no_used1.input_format = RTK_FORMAT_INVALID; //if only osd, we have to set input format to invalid.
     Rtk_DV_Metadata_to_reg(&no_used1, mp_dolby_vo_register, &no_used2);
     CP_buffer_endian_swap_4bytes(&mp_dolby_vo_register->dst_dm_reg1, sizeof(mp_dolby_vo_register->dst_dm_reg1));
     CP_buffer_endian_swap_4bytes(&mp_dolby_vo_register->dst_dm_reg2, sizeof(mp_dolby_vo_register->dst_dm_reg2));
     CP_buffer_endian_swap_4bytes(&mp_dolby_vo_register->dst_dm_reg3, sizeof(mp_dolby_vo_register->dst_dm_reg3));



     memset( &cp_out,0,sizeof(cp_out));

     cp_out.dm_reg1_addr = ConvertVirtualToPhysical((unsigned long long)&mp_dolby_vo_register->dst_dm_reg1,
                                                         (unsigned long long)mp_dolby_vo_register_allocator->mp_physical,
                                                         (unsigned long long)mp_dolby_vo_register_allocator->mp_virtual);
     cp_out.dm_reg1_size = sizeof(mp_dolby_vo_register->dst_dm_reg1);
     cp_out.dm_reg2_addr = ConvertVirtualToPhysical((unsigned long long)&mp_dolby_vo_register->dst_dm_reg2,
                                                         (unsigned long long)mp_dolby_vo_register_allocator->mp_physical,
                                                         (unsigned long long)mp_dolby_vo_register_allocator->mp_virtual);
     cp_out.dm_reg2_size = sizeof(mp_dolby_vo_register->dst_dm_reg2);
     cp_out.dm_reg3_addr = ConvertVirtualToPhysical((unsigned long long)&mp_dolby_vo_register->dst_dm_reg3,
                                                         (unsigned long long)mp_dolby_vo_register_allocator->mp_physical,
                                                         (unsigned long long)mp_dolby_vo_register_allocator->mp_virtual);
     cp_out.dm_reg3_size = sizeof(mp_dolby_vo_register->dst_dm_reg3);

     cp_out.dv_lut1_addr = ConvertVirtualToPhysical((unsigned long long)&mp_dolby_vo_register->dv_lut1,
                                                         (unsigned long long)mp_dolby_vo_register_allocator->mp_physical,
                                                         (unsigned long long)mp_dolby_vo_register_allocator->mp_virtual);
     cp_out.dv_lut1_size = sizeof(mp_dolby_vo_register->dv_lut1);

     cp_out.dv_lut2_addr = ConvertVirtualToPhysical((unsigned long long)&mp_dolby_vo_register->dv_lut2,
                                                         (unsigned long long)mp_dolby_vo_register_allocator->mp_physical,
                                                         (unsigned long long)mp_dolby_vo_register_allocator->mp_virtual);

     cp_out.dv_lut2_size = sizeof(mp_dolby_vo_register->dv_lut2);


     ALOGD("[CP]1addr:%x 1size:%x 2addr:%x 2size:%x 3addr:%x 3size:%x \n",   cp_out.dm_reg1_addr, cp_out.dm_reg1_size,cp_out.dm_reg2_addr, cp_out.dm_reg2_size,  cp_out.dm_reg3_addr,cp_out.dm_reg3_size );
  

    return cp_out;

}


#if defined (__cplusplus)
}
#endif

void
RealtekDVControlPathService::registerEventListener(const sp<IEventListener> &l)
{
    Mutex::Autolock lock(mRegistrationLock);
    ALOGD("registerEventListener l: %p", l.get());
    // linkToDeath
    if(l != NULL && IInterface::asBinder(l)->remoteBinder() != NULL)
    {
        int status = IInterface::asBinder(l)->linkToDeath(
            static_cast<IBinder::DeathRecipient*>(this));
        if (status != NO_ERROR) {
            ALOGE("set DeathRecipient failed.");
        }else{
            ALOGD("set DeathRecipient success");
        }
    }

    mListeners.add(l);

#if DUMP_LISTENERS
    {
        ALOGD("registerEventListener");
        for(size_t i = 0; i < mListeners.size(); i++){
            ALOGD("[REG] hooked listener %p",mListeners[i].get());
        }
    }
#endif
}

void
RealtekDVControlPathService::unregisterEventListener(const sp<IEventListener> &l)
{
    Mutex::Autolock lock(mRegistrationLock);
    ALOGD("unregisterEventListener l: %p",l.get());
    for(size_t i = 0; i < mListeners.size(); i++){
        if (IInterface::asBinder(mListeners[i]) == IInterface::asBinder(l)) {
            // unlinkToDeath
            IInterface::asBinder(mListeners[i])->unlinkToDeath(
                static_cast<IBinder::DeathRecipient*>(this));
            mListeners.removeAt(i);
            ALOGD("[UNREG] find registered listener, remove it done");
            break;
        }
    }
}

void
RealtekDVControlPathService::setPropertyInt(const char *key, int value)
{
    char val[PROPERTY_VALUE_MAX];
    memset(val,0x0,PROPERTY_VALUE_MAX);
    snprintf(val,PROPERTY_VALUE_MAX,"%d",value);
    ALOGI("set property %s : %s",key, val);
    property_set(key,val);
}

int
RealtekDVControlPathService::getPropertyInt(const char *key, int dft)
{
    char value[PROPERTY_VALUE_MAX];
    char dftStr[PROPERTY_VALUE_MAX];

    memset(value, 0x0 ,PROPERTY_VALUE_MAX);
    memset(dftStr, 0x0, PROPERTY_VALUE_MAX);

    snprintf(dftStr,PROPERTY_VALUE_MAX,"%d",dft);

    property_get(key,value,dftStr);

    int rst = atoi(value);
    ALOGI("get property %s : %d",key,rst);
    return rst;
}



void
RealtekDVControlPathService::binderDied(const wp<android::IBinder>& who)
{
    Mutex::Autolock lock(mRegistrationLock);
    ALOGD("BinderDied");
    for (size_t i = 0; i < mListeners.size(); i++) {
        if (IInterface::asBinder(mListeners[i]) == who) {
            mListeners.removeAt(i);
            ALOGD("[UNREG] binderDied, remove register list done");
            break;
        }
    }


}

#if 0
void set_hdr10_param_default()
{
  hdr10_param.min_display_mastering_luminance = 50; 
  hdr10_param.max_display_mastering_luminance = 10000000; 
  hdr10_param.Rx = 0;                              
  hdr10_param.Ry = 0;                              
  hdr10_param.Gx = 0;                              
  hdr10_param.Gy = 0;                              
  hdr10_param.Bx = 0;                              
  hdr10_param.By = 0;                              
  hdr10_param.Wx = 0;                              
  hdr10_param.Wy = 0;                              
  hdr10_param.max_content_light_level = 0;         
  hdr10_param.max_pic_average_light_level = 0;     

}

void set_cp_sink_param_default()
{
  cp_sink_param.priority_mode = VIDEO_PRIORITY;
  cp_sink_param.output_format = FORMAT_HDR10;

  cp_sink_param.target_param.tmax = 650;  //100+50*CV, CV=11
  cp_sink_param.target_param.tmin = 0;   //(CV/127)^2 CV=41
  cp_sink_param.target_param.width = 3840; // equal as source, should be refill in control path lib.
  cp_sink_param.target_param.height = 2160;
  cp_sink_param.target_param.use_ll_flag = 0;
  cp_sink_param.target_param.ll_rgb_desired = 0;
  cp_sink_param.target_param.use_ll_flag = 0;    /**< @brief Use DoVi low latency if Sink supports */
  cp_sink_param.target_param.ll_rgb_desired = 0;  /**< @brief Use RGB in low latency if Sink supports */
  cp_sink_param.target_param.vsvdb_length = 15;   /**< @brief Sink VSVDB size in byte */
  cp_sink_param.target_param.vsvdb_version = 0;  /**< @brief Sink VSVDB version number */
  cp_sink_param.target_param.v1_low_latency = 0;  /**< @brief Low latency indicator in v1 VSVDB */
  cp_sink_param.target_param.v2_interface = 0;    /**< @brief Interface indicator in v2 VSVDB */
  cp_sink_param.target_param.v2_supports_10b_12b_444 = 0;    /**< @brief 444 indicator in v2 VSVDB */
  cp_sink_param.target_param.Rx = 0xab;
  cp_sink_param.target_param.Ry = 0x55;
  cp_sink_param.target_param.Gx = 0x44;
  cp_sink_param.target_param.Gy = 0xac;
  cp_sink_param.target_param.Bx = 0x24;
  cp_sink_param.target_param.By = 0x0d;
}
#endif


}; // namespace android


