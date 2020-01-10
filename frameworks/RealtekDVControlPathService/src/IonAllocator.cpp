#include "IonAllocator.h"
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include "Common.h"

#undef LOG_TAG
#define LOG_TAG "IonAllocator"
#include <rtk_ion.h>

namespace android
{
    IonAllocator::IonAllocator()
    {
        Reset();
    }

    IonAllocator::~IonAllocator()
    {
        Release();
    }

    void IonAllocator::Reset()
    {
        mp_physical = NULL;
        mp_virtual = NULL;

        m_ion_handle = -1;
        m_ion_fd = -1;
        m_mmap_fd = -1;

        m_size = 0;
    }

    bool IonAllocator::Allocate(int size, unsigned int mask, unsigned int flag)
   {
 	
        unsigned int i;
        
        Release();

        m_ion_fd = ion_open();

        if (m_ion_fd < 0)
        {
            Reset();
            return false;
        }

        int ret = ion_alloc(m_ion_fd, size, getpagesize(), mask, flag, &m_ion_handle);


        if (ret < 0)
        {
            ion_close(m_ion_fd);
            Reset();
            return false;
        }

        ret = ion_phys(m_ion_fd, m_ion_handle,
                       (unsigned long *)&mp_physical,
                       (unsigned int *)&m_size);

        if (ret < 0)
        {
            ion_free(m_ion_fd, m_ion_handle);
            ion_close(m_ion_fd);
            Reset();
            return false;
        }

        ret = ion_map(m_ion_fd, m_ion_handle, m_size,
                      PROT_READ | PROT_WRITE, MAP_SHARED, 0,
                      (unsigned char **)&mp_virtual, &m_mmap_fd);


        if (ret < 0)
        {
            ion_free(m_ion_fd, m_ion_handle);
            ion_close(m_ion_fd);
            Reset();
            return false;
        }



       for(i = 0; i < (size >> sizeof(unsigned int)) ; i++ )
       {

         *(mp_virtual + i) = 0;
       }
       //We can't use memset in 64bit environment
       //  memset(mp_virtual, 0, size);


        return true;
    }

    bool IonAllocator::Release()
    {
        if (m_ion_fd >= 0)
        {
            munmap(mp_virtual, m_size);
            ion_free(m_ion_fd, m_ion_handle);
            close(m_mmap_fd);
            ion_close(m_ion_fd);
        }

        Reset();

        return true;
    }

    void IonAllocator::Print(const char *p_tag/*= NULL*/)
    {
        RTKDVLOG("[%s] handle: %x, fd: %x, physical: %p, virtual: %p, size: %d",
                 p_tag == NULL ? LOG_TAG : p_tag,
                 (unsigned int)m_ion_handle, m_ion_fd, mp_physical, mp_virtual, m_size);
    }
}
