#include <stdlib.h>
#include <stdio.h>
#include "memory.h"

void *xmalloc(size_t size) {
  void *ptr = malloc(size);
  if (ptr == NULL) {
    fprintf(stderr, "Out of memory allocation %zu bytes\n", size);
    exit(1);
  }
  return ptr;

}

void *xrealloc(void *oldptr, size_t size) {
     void *ptr = realloc(oldptr, size);
     if (ptr == NULL) {
        fprintf(stderr, "Out of memory allocation %zu bytes\n", size);
        exit(1);
    }
   return ptr;
}
