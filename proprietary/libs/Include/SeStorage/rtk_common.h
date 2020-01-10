#ifndef RTK_COMMON_H
#define RTK_COMMON_H
#include <sys/types.h>

#define uint8_t u8
#define u8 u_int8_t
#define U8 u_int8_t
#define UINT8 u_int8_t

#define uint16_t u16
#define u16 u_int16_t
#define U16 u_int16_t

#define uint32_t u32
#define u32 u_int32_t
#define UINT32 u_int32_t

#define uint64_t u64
#define u64 u_int64_t
#define UINT64 u_int64_t

typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned long long u64;

#include <stdio.h>

#define VT100_NONE          "\033[m"
#define VT100_LIGHT_RED     "\033[1;31m"

//#define RTK_GUI
#define MAC_TEST
#define MAC_INSTALL_A
#define FROM_MTD_BLOCK


//#define INSTALL_DEBUG
#define INSTALL_INFO
//#define INSTALL_LOG
#define INSTALL_FAIL

#ifdef INSTALL_DEBUG
#define install_debug(f, a...) \
do { \
    printf("[FACTORY DEBUG][%s][%d]\r\n", \
        __FILE__, __LINE__); \
    printf(f, ##a); \
} while (0)
#else
#define install_debug(f, a...) /**/
#endif


#ifdef INSTALL_INFO
#define install_info(f, a...) \
do { \
    printf("[SE_STORAGE INFO][%s][%d] ", \
        __FILE__, __LINE__); \
    printf(f, ##a); \
} while (0)
#else
#define install_info(f, a...) /**/
#endif
	

#ifdef INSTALL_LOG
#define install_log(f, a...) \
do { \
    printf("[SE_STORAGE LOG][%s][%d]\r\n", \
        __FILE__, __LINE__); \
    printf(f, ##a); \
} while (0)
#else
#define install_log(f, a...) /**/
#endif

#ifdef INSTALL_FAIL
#define install_fail(f, a...) \
do { \
    printf("[SE_STORAGE FAIL][%s][%d]\r\n", \
        __FILE__, __LINE__); \
    printf(VT100_LIGHT_RED f VT100_NONE, ##a); \
} while (0)
#else
#define install_fail(f, a...) /**/
#endif

typedef enum _BOOTTYPE
{
     BOOT_NAND=0,
     BOOT_SPI,
     BOOT_EMMC,
     BOOT_UNKNOWN,
} BOOTTYPE;

/* from mtd/mtd_abi.h */
struct mtd_info_user {
	uint8_t type;
	uint32_t flags;
	uint64_t size;   // Total size of the MTD
	uint32_t erasesize;
	uint32_t oobblock;  // Size of OOB blocks (e.g. 512)
	uint32_t oobsize;   // Amount of OOB data per block (e.g. 16)
	uint32_t ecctype;
	uint32_t eccsize;
};
struct erase_info_user {
	uint32_t start;
	uint32_t length;
};
#define ARRAY_COUNT(x)  (sizeof(x) / sizeof((x)[0]))
int fd_to_fd(int sfd, int dfd, unsigned int length, unsigned int* pchecksum=NULL, FILE* ffd=NULL);
int rtk_extract_file(struct t_rtkimgdesc* prtkimgdesc, struct t_imgdesc* pimgdesc, const char* file_path);
#define FILESIZELEN 11
unsigned int octalStringToInt(const char* str, unsigned int lenstr);
int rtk_get_size_of_file(const char* file_path);
u32 get_checksum(u8 *p, u32 len);
int rtk_command(const char* command, int line, const char* file);
int rtk_file_to_string(const char* path, char* str);
int rtk_file_to_flash(const char* filepath, unsigned int soffset, const char* devpath, unsigned int doffset, unsigned int len, unsigned int* checksum);
int rtk_ptr_to_flash(void* ptr, unsigned int len, const char* devpath, unsigned int doffset);
int rtk_file_to_ptr(const char* filepath, unsigned int soffset, void* ptr, unsigned int len);
int rtk_ptr_to_file(const char* filepath, unsigned int soffset, void* ptr, unsigned int len);
int rtk_flash_to_ptr(const char* devpath, unsigned int soffset, void* ptr, unsigned int len);
int rtk_file_lock(void);
int rtk_file_unlock(void);
int rtk_file_compare(const char *file1, const char *file2);
u32 crc32(UINT8  *p, int len, u32 *crc );
#endif
