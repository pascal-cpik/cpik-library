#ifndef __SORT_H
#define __SORT_H

#include <sys/types.h>

typedef char (*sort_cmpfun)(void *e1, void *e2);
void bsort(void *data, size_t length, unsigned char size, sort_cmpfun );
void csort(void *data, size_t length, size_t size, sort_cmpfun);
void ssort(void *data, size_t length, size_t size, sort_cmpfun);

#endif // #ifndef __SORT_H


