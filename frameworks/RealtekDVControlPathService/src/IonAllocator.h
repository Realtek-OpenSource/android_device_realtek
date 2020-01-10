#ifndef DV_ION_H
#define DV_ION_H

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>

#include <ion/ion.h>

namespace android
{
    class IonAllocator
    {
    public:
        IonAllocator();
        ~IonAllocator();

        bool Allocate(int size, unsigned int mask, unsigned int flag);
        bool Release();

        void Print(const char *p_tag = NULL);

        unsigned long *mp_virtual;
        unsigned long *mp_physical;
        int m_size;

    private:
        void Reset();

        int m_ion_fd;
        int m_mmap_fd;
        ion_user_handle_t m_ion_handle;
    };
}

#endif
