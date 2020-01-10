#ifndef GRALLOC_CMD_H
#define GRALLOC_CMD_H

#ifdef __cplusplus
extern "C" {
#endif
typedef enum {
    GRALLOC_CMD_GET_METADATA_INFO = 0,
    GRALLOC_CMD_NONE
} GRALLOC_CMD_TYPE;

typedef struct {
    void *vir_addr;
    unsigned int phy_addr;
    unsigned int size;
    int share_metadata_fd;
} GetMetadataInfo_t;

#ifdef __cplusplus
}
#endif

#endif // GRALLOC_CMD_H
