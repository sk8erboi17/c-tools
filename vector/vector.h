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

/*O(1) | Get element by index*/
void *vector_get(Vector *v, size_t i);


/*O(n) | Search, return NULL if item is not found*/
void *vector_search(Vector *v, void *target, int(*cmp)(void *, void*));

/* This function destroys the vector and its elements.
 * It's up to the caller to pass:
 * - 'free': if the elements are allocated using malloc, strdup, etc.
 * - NULL: if the elements don't require deallocation (int, stack variables, etc).
 *
 * O(n) | Delete */
Vector *vector_del(Vector *v, void *target, int(*cmp)(void *, void*), void(*destroy_elem)(void *));

/* This function destroys the vector and its elements.
 * It's up to the caller to pass:
 * - 'free': if the elements are allocated using malloc, strdup, etc.
 * - NULL: if the elements don't require deallocation (int, stack variables, etc).
 */
void v_destroy(Vector *v, void (*destroy_elem)(void *));

void vector_new_int(Vector *v, int i);
void vector_new_float(Vector *v, float f);
void vector_new_char(Vector *v, char c);
void vector_new_double(Vector *v, double d);
#endif
