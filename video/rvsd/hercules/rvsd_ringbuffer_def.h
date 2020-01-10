#ifndef __RVSD_RINGBUFFER_DEF__
#define __RVSD_RINGBUFFER_DEF__

typedef struct
{
    unsigned long base;
    unsigned long limit;
    unsigned long wp;
    unsigned long rp;
} RVSD_RINGBUF;

typedef struct
{
    unsigned long base;
    unsigned long limit;
    unsigned long wp;
    unsigned long rp;
    unsigned long bit_offset;   // the bit offset of the first 4 bytes which ReadPtr points to. Smaller than 32.
} RVSD_EXTRACT_RINGBUF;

#endif
