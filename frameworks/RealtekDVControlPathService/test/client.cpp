#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>

#include <DVControlPathClient.h>

#include <ion/ion.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
using namespace android;

void test()
{

    
    sp<DVControlPathClient> client = new DVControlPathClient();

    DV_CP_SERVICE_SFD sfd;
    
    int m_ion_fd_1,m_ion_fd_2,m_ion_fd_3;
    int m_mmap_fd_1,m_mmap_fd_2,m_mmap_fd_3;
    unsigned long *mp_virtual_1,*mp_virtual_2,*mp_virtual_3;
    unsigned long *mp_physical_1,*mp_physical_2,*mp_physical_3;
    ion_user_handle_t m_ion_handle_1,m_ion_handle_2,m_ion_handle_3;
    int ret = 0;
    int m_size_1,m_size_2,m_size_3; 


 
    m_ion_fd_1 = ion_open();
    ret = ion_alloc(m_ion_fd_1, 0x2000, getpagesize(), RTK_PHOENIX_ION_HEAP_MEDIA_MASK,
                      ION_FLAG_NONCACHED | ION_FLAG_SCPUACC | ION_FLAG_ACPUACC, &m_ion_handle_1);


    

    ret = ion_phys(m_ion_fd_1, m_ion_handle_1,
                       (unsigned long *)&mp_physical_1,
                       (unsigned int *)&m_size_1);

    
    ret = ion_map(m_ion_fd_1, m_ion_handle_1, m_size_1,
                      PROT_READ | PROT_WRITE, MAP_SHARED, 0,
                      (unsigned char **)&mp_virtual_1, &m_mmap_fd_1);

    memset(mp_virtual_1, 0, 0x2000);


    *mp_virtual_1 = 0;
   
    
    ALOGD("[1]ret:%d ,sfd:%d mp_virtual_1:%x m_size_1:%d\n",ret,m_mmap_fd_1,mp_virtual_1,m_size_1);

   
    



    m_ion_fd_2 = ion_open();
    ret = ion_alloc(m_ion_fd_2, 0x3000, getpagesize(), RTK_PHOENIX_ION_HEAP_MEDIA_MASK,
                      ION_FLAG_NONCACHED | ION_FLAG_SCPUACC | ION_FLAG_ACPUACC, &m_ion_handle_2);



    
    ret = ion_phys(m_ion_fd_2, m_ion_handle_2,
                       (unsigned long *)&mp_physical_2,
                       (unsigned int *)&m_size_2);


    ret = ion_map(m_ion_fd_2, m_ion_handle_2, m_size_2,
                      PROT_READ | PROT_WRITE, MAP_SHARED, 0,
                      (unsigned char **)&mp_virtual_2, &m_mmap_fd_2);

    memset(mp_virtual_2, 0, 0x3000);
      



    
    m_ion_fd_3 = ion_open();
    ion_alloc(m_ion_fd_3, 0x1000, getpagesize(), RTK_PHOENIX_ION_HEAP_MEDIA_MASK,
                      ION_FLAG_NONCACHED | ION_FLAG_SCPUACC | ION_FLAG_ACPUACC, &m_ion_handle_3);


    ret = ion_phys(m_ion_fd_3, m_ion_handle_3,
                       (unsigned long *)&mp_physical_3,
                       (unsigned int *)&m_size_3);
    
    ion_map(m_ion_fd_3, m_ion_handle_3, m_size_3,
                      PROT_READ | PROT_WRITE, MAP_SHARED, 0,
                      (unsigned char **)&mp_virtual_3, &m_mmap_fd_3);

    memset(mp_virtual_3, 0, 0x1000);


    ALOGD("[3]ret:%d ,sfd:%d mp_virtual_3:%x m_size_3:%d\n",ret,m_mmap_fd_3,mp_virtual_3,m_size_3);




    sfd.rtk_dv_cp_param_fd = m_mmap_fd_1;
	sfd.rtk_dv_cp_param_fd_length = 0x2000;
	sfd.rtk_dv_vo_register_fd = m_mmap_fd_2;
	sfd.rtk_dv_vo_register_fd_length = 0x3000;
    sfd.rtk_hdr_10_infoframe_t_fd = m_mmap_fd_3;
	sfd.rtk_hdr_10_infoframe_t_fd_length = 0x1000;


    
    client->Rtk_DV_Metadata_to_reg_service(sfd);



    ALOGD("[CP]@rtk_dv_cp_param::c2[0]:%x \n",*mp_virtual_2  );


    usleep(30000000);
}

int main()
{
    ProcessState::self()->startThreadPool();
    test();
    return 0;
}
