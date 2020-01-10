#ifndef RTK_ION_API_H
#define RTK_ION_API_H

#include <linux/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <ion/ion.h>

#define ION_FLAG_NONCACHED              (1 << 31)
#define ION_FLAG_SCPUACC                (1 << 30)
#define ION_FLAG_ACPUACC                (1 << 29)
#define ION_FLAG_HWIPACC                (1 << 28)
#define ION_FLAG_VE_SPEC                (1 << 27)
#define ION_FLAG_SECURE_AUDIO           (1 << 26)
#define RTK_ION_FLAG_MASK               (ION_FLAG_NONCACHED | ION_FLAG_ACPUACC | ION_FLAG_SCPUACC | ION_FLAG_HWIPACC)

#define ION_USAGE_PROTECTED             (1 << 23)
#define ION_USAGE_MASK                  (ION_USAGE_PROTECTED)

#define ION_IOC_PHYS _IOWR(ION_IOC_MAGIC, 8, struct ion_phys_data)

struct ion_phys_data {
    ion_user_handle_t handle;
    unsigned long addr;
    unsigned int len;
};

/**
 * struct rtk_phoenix_ion_tiler_alloc_data - metadata passed from userspace for allocations
 * @w:		width of the allocation
 * @h:		height of the allocation
 * @fmt:	format of the data (8, 16, 32bit or page)
 * @flags:	flags passed to heap
 * @stride:	stride of the allocation, returned to caller from kernel
 * @handle:	pointer that will be populated with a cookie to use to refer
 *		to this allocation
 *
 * Provided by userspace as an argument to the ioctl
 */
struct rtk_phoenix_ion_tiler_alloc_data {
	size_t w;
	size_t h;
	int fmt;
	unsigned int flags;
	ion_user_handle_t handle;
	size_t stride;
	size_t offset;
	unsigned int size;
};

#ifdef __KERNEL__
int rtk_phoenix_ion_tiler_alloc(struct ion_client *client,
			 struct rtk_phoenix_ion_tiler_alloc_data *data);
int rtk_phoenix_ion_nonsecure_tiler_alloc(struct ion_client *client,
			 struct rtk_phoenix_ion_tiler_alloc_data *data);
/* given a handle in the tiler, return a list of tiler pages that back it */
int rtk_phoenix_tiler_pages(struct ion_client *client, ion_user_handle_t handle,
		     int *n, u32 ** tiler_pages);
#endif /* __KERNEL__ */

/* additional heaps used only on rtk_phoenix */
enum {
	RTK_PHOENIX_ION_HEAP_TYPE_TILER = ION_HEAP_TYPE_CUSTOM + 1,
	RTK_PHOENIX_ION_HEAP_TYPE_MEDIA,
	RTK_PHOENIX_ION_HEAP_TYPE_AUDIO,
	RTK_PHOENIX_ION_HEAP_TYPE_SECURE,
};

#define RTK_PHOENIX_ION_HEAP_TILER_MASK (1 << RTK_PHOENIX_ION_HEAP_TYPE_TILER)
#define RTK_PHOENIX_ION_HEAP_MEDIA_MASK (1 << RTK_PHOENIX_ION_HEAP_TYPE_MEDIA)
#define RTK_PHOENIX_ION_HEAP_AUDIO_MASK (1 << RTK_PHOENIX_ION_HEAP_TYPE_AUDIO)
#define RTK_PHOENIX_ION_HEAP_SECURE_MASK (1 << RTK_PHOENIX_ION_HEAP_TYPE_SECURE)

struct RTK_ION_IOC_SYNC_RANE {
    ion_user_handle_t   handle;
    unsigned long long  phyAddr;
    unsigned int        len;
};

struct RTK_ION_IOC_PHY_INFO {
    ion_user_handle_t handle;
    unsigned long long addr;
    unsigned long long len;
};

enum {
	RTK_PHOENIX_ION_TILER_ALLOC,
	RTK_PHOENIX_ION_GET_LAST_ALLOC_ADDR,
	RTK_ION_IOC_INVALIDATE  = 0x10,
	RTK_ION_IOC_FLUSH,
    RTK_ION_IOC_INVALIDATE_RANGE = 0x13,
    RTK_ION_IOC_FLUSH_RANGE,
    RTK_ION_IOC_GET_PHYINFO,
};

/**
 * These should match the defines in the tiler driver
 */
enum {
	TILER_PIXEL_FMT_MIN   = 0,
	TILER_PIXEL_FMT_8BIT  = 0,
	TILER_PIXEL_FMT_16BIT = 1,
	TILER_PIXEL_FMT_32BIT = 2,
	TILER_PIXEL_FMT_PAGE  = 3,
	TILER_PIXEL_FMT_MAX   = 3
};

/**
 * List of heaps in the system
 */
enum {
	RTK_PHOENIX_ION_HEAP_LARGE_SURFACES,
	RTK_PHOENIX_ION_HEAP_TILER,
	RTK_PHOENIX_ION_HEAP_SECURE_INPUT,
	RTK_PHOENIX_ION_HEAP_NONSECURE_TILER,
};

typedef struct  {
    int mmap_fd;
    /* usually size >= want_size, ex: if want_size == 32B, size = 4KB */
    unsigned int size;  // memroy size got from ION
    unsigned char* ion_virt;
    unsigned char* ion_phy;
    int flag;
    ion_user_handle_t ion_handle;
    unsigned int want_size; // memory size which want to get
} ION_DATA;

typedef struct
{
    int ion_fd;
}ION_HDL;

#ifdef __cplusplus
extern "C" {
#endif

int ion_alloc_tiler(int fd, size_t w, size_t h, int fmt, unsigned int size, unsigned int flags,
                    ion_user_handle_t *handle, size_t *stride);
int ion_phys(int fd, ion_user_handle_t handle, unsigned long *addr, unsigned int *size);
int ion_last_alloc_addr(int fd, unsigned long *addr, unsigned int *size);
int ion_get_phys_from_shared_fd(int share_fd, unsigned long *addr, unsigned int *size);
int ion_flush_fd(int fd, int handle_fd);
int ion_invalidate_fd(int fd, int handle_fd);
int ion_flush_range(int fd, int handle_fd, unsigned long addr, unsigned int size);
int ion_invalidate_range(int fd, int handle_fd, unsigned long addr, unsigned int size);

int ion_send_share_fd(int socket, int sharefd);
int ion_receive_share_fd(int socketfd);
int ion_creat_client_socket(int *socketfd);
int ion_close_client_soket(int socket);

void *IonAllocMemoryFromShareFd(int *IonFd, int *sharefd, int socket , int *size ,int *IonMapFd,void **noncacheable, unsigned long *PhyAddr,ion_user_handle_t *IonHandle);
void *IonGetShareMemory(int *IonFd, int sharefd, int *size ,int *IonMapFd,void **noncacheable, unsigned long *PhyAddr,ion_user_handle_t *IonHandle);
int IonFreeShareMemory(void *VirAddr,int sharefd,int size,int IonFd, int IonMapFd,ion_user_handle_t IonHandle);
int IonPutShareMemory(void *VirAddr,int size,int IonFd, int IonMapFd,ion_user_handle_t IonHandle);

int rtk_ion_malloc(ION_DATA *p, size_t size, size_t align, unsigned int heap, unsigned int flag);
int rtk_ion_free(ION_DATA *p);
void rtk_ion_close();
int rtk_ion_flush_handle_fd(int handle_fd);
int rtk_ion_invalidate_fd(int handle_fd);

ION_HDL* ION_hdl_init();
void ION_hdl_uninit(ION_HDL *pInfo);
int ION_hdl_malloc(ION_HDL *hdl, ION_DATA *p, size_t size, size_t align, unsigned int heap, unsigned int flag);
int ION_hdl_free(ION_HDL *hdl, ION_DATA *p);
int ION_hdl_flush_handle_fd(ION_HDL *hdl, int handle_fd);
int ION_hdl_invalidate_fd(ION_HDL *hdl, int handle_fd);
unsigned char *ION_GetPhyFromVirt(ION_DATA *pIon, unsigned char *pVirt);

#ifdef __cplusplus
}
#endif

#endif
