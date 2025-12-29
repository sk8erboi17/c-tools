#ifndef VECTOR_H
#define VECTOR_H
#include <stddef.h>

typedef struct Vector {
    void **items;
    size_t size; // actual items
    size_t max_size;
} Vector;

Vector *vector_create();

/*O(1) | PUSH*/
void vector_push(Vector *v, void *items);
/*O(n) |  Delete*/
Vector *vector_del(Vector *v, void *target, int(*cmp)(void *, void*));

/*O(1) | Get element by index*/
void *vector_get(Vector *v, size_t i);
/*O(n) | Search, return NULL if item is not found*/
void *vector_search(Vector *v, void *target, int(*cmp)(void *, void*));

void vector_new_int(Vector *v, int i);
void vector_new_float(Vector *v, float f);
void vector_new_char(Vector *v, char c);
void vector_new_double(Vector *v, double d);
#endif
