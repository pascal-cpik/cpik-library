#ifndef __MEMCPY_H
#define __MEMCPY_H

#include <sys/types.h>

void *memcpy(void *dest, void *src, size_t num);
void *memmove(void *dest, void *src, size_t num);
void xmemshift(void *vec, uint8_t offset, int8_t shift, uint8_t blklen, uint8_t size);

#endif
