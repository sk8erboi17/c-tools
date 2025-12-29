#include <stdio.h>
#include <stdlib.h>
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
Vector *vector_del(Vector *v, void *target, int(*cmp)(void*, void*)) {
   for(size_t i = 0; i < v->size; i++) {
        if(cmp(v->items[i], target) == 0) {
            free(v->items[i]);
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

/*Get an item by index*/
void *vector_get(Vector *v, size_t i) {
    if(i >= v->size) {
        fprintf(stderr, "Index out of bound: %zu position\n", i);
        exit(1);
    }
    return v->items[i];
}

void *vector_search(Vector *v, void *target, int(*cmp)(void *, void*)) {
   for(size_t i = 0; i < v->size; i++) {
        if(cmp(v->items[i], target) == 0) {
            return v->items[i];
        }
   }
    return NULL;
}

/* ==================== ADD Primitives  ==================== */
void vector_new_int(Vector *v, int i) {
    int *ptr = xmalloc(sizeof(int));
    *ptr = i;
    vector_push(v, ptr);
}

void vector_new_float(Vector *v, float f) {
    float *ptr = xmalloc(sizeof(float));
    *ptr = f;
    vector_push(v, ptr);
}

void vector_new_char(Vector *v, char c) {
    char *ptr = xmalloc(sizeof(char));
    *ptr = c;
    vector_push(v, ptr);
}

void vector_new_double(Vector *v, double d) {
    double *ptr = xmalloc(sizeof(double));
    *ptr = d;
    vector_push(v, ptr);
}
