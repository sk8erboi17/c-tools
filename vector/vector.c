#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../utils/memory.h"
#include "vector.h"

Vector *vector_create() {
    Vector *v = xmalloc(sizeof(Vector));
    v->size = 0;
    v->max_size = 4;
    v->items = xmalloc(v->max_size * sizeof(void *));
    return v;
}
/* ==================== OPERATIONS  ==================== */

void vector_push(Vector *v, void *item) {
    if(v->size == v->max_size) {
        v->max_size = v->max_size*2;
        v->items = xrealloc(v->items,v->max_size * sizeof(void *));
    }
    v->items[v->size] = item;
    v->size++;
}

/*This is not O(n^2) because we return after delete because we return after delete */
Vector *vector_del(Vector *v, void *target, int(*cmp)(void*, void*), void(*destroy_elem)(void *)) {
   for(size_t i = 0; i < v->size; i++) {
        if(cmp(v->items[i], target) == 0) {
            if(destroy_elem) {
                destroy_elem(v->items[i]);
            }
            /*The v->items[i](== v->items[j]) must be overwrite by the next item*/
            for(size_t j = i; j < v->size-1; j++) {
                v->items[j] = v->items[j+1];
            } 
            v->size--;
            v->items[v->size] = NULL;
            return v;
        }
    }   
    //Nothing found
    return v;
}

void *vector_get(Vector *v, size_t i) {
    if(i >= v->size) {
        fprintf(stderr, "Index out of bound: %zu position\n", i);
        exit(1);
    }
    return v->items[i];
}

void v_destroy(Vector *v, void(*destroy_elem)(void *)){

    if(destroy_elem) {
        for(size_t i = 0; i<v->size;i++){
            if(v->items[i]) destroy_elem(v->items[i]);
        }
    }
    free(v->items);
    free(v);
}

void *vector_search(Vector *v, void *target, int(*cmp)(void *, void*)) {
   for(size_t i = 0; i < v->size; i++) {
        if(cmp(v->items[i], target) == 0) {
            return v->items[i];
        }
   }
    return NULL;
}
/* ==================== ADD Primitives ==================== */

/* OPTIMIZATION: "Value Embedding" (Zero-Allocation)
 * * On 64-bit systems, a pointer (void*) is 8 bytes. An int is usually 4 bytes.
 * Instead of asking the OS for memory (malloc) to store a tiny integer,
 * we store the value DIRECTLY inside the pointer variable itself.
 *
 * WHY WE DO THIS:
 * 1. Zero Overhead: No malloc/free syscalls. It's instant.
 * 2. Cache Locality: The data sits inside the vector's contiguous array.
 * The CPU reads it sequentially. If we used malloc, the CPU would have 
 * to "chase pointers" to random heap locations, causing expensive 
 * Cache Misses.
 */
void vector_new_int(Vector *v, int i) {
    vector_push(v, (void*)(intptr_t)i);
}

void vector_new_char(Vector *v, char c) {
    vector_push(v, (void*)(intptr_t)c);
}

/* STANDARD ALLOCATION (Heap Strategy)
 *
 * Floats and Doubles have complex bit representations or sizes that don't
 * always safely fit into a void* pointer across all architectures.
 * Here we must fall back to the slow approach: allocating heap memory.
 *
 * THE TRADE-OFF:
 * This introduces "Indirection". The vector holds an address, not the data.
 * To read the value, the CPU must jump to a different memory location,
 * which is significantly slower than the embedding technique above.
 */
void vector_new_float(Vector *v, float f) {
    float *ptr = xmalloc(sizeof(float));
    *ptr = f;
    vector_push(v, ptr);
}

void vector_new_double(Vector *v, double d) {
    double *ptr = xmalloc(sizeof(double));
    *ptr = d;
    vector_push(v, ptr);
}
