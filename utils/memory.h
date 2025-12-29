#ifndef MEMORY_H
#define MEMORY_H
#include <stddef.h>

void *xmalloc(size_t size);
void *xrealloc(void *oldptr, size_t size);


#endif
