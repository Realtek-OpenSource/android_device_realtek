#ifndef RTK_STORAGE_H
#define RTK_STORAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

int storage_load(void);
int storage_save(void);
int storage_clean(void);
int storage_create_file(char* filename);
int storage_del_file(char* filename);

#ifdef __cplusplus
}
#endif

#endif
