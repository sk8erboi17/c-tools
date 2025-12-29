#include <stdio.h>
#include <assert.h>
#include "../vector/vector.h"

/* Helper for comparisons */
int cmp_int(void *a, void *b) {
    return *(int*)a - *(int*)b;
}

void test_initialization() {
    printf("Test 1: Initialization... ");
    
    Vector *v = vector_create();
    
    // Check that it starts empty and with default capacity
    assert(v != NULL);
    assert(v->size == 0);
    assert(v->max_size == 4);
    
    printf("PASSED\n");
}

void test_push_and_resize() {
    printf("Test 2: Push and Automatic Resize... ");
    
    Vector *v = vector_create();

    //fill the vector (4 elements)
    vector_new_int(v, 10);
    vector_new_int(v, 20);
    vector_new_int(v, 30);
    vector_new_int(v, 40);

    // should be full but not resized yet
    assert(v->size == 4);
    assert(v->max_size == 4); 

    // add 5th element, realloc must trigger here
    vector_new_int(v, 50);

    // check if capacity doubled
    assert(v->size == 5);
    assert(v->max_size == 8); 
    
    //verify data integrity
    int *val = (int*) vector_get(v, 4); // Index 4 is the 5th element (50)
    assert(*val == 50);

    printf("PASSED\n");
}

void test_delete_and_shift() {
    printf("Test 3: Deletion and Shift... ");
    
    Vector *v = vector_create();

    // Create [10, 20, 30]
    vector_new_int(v, 10);
    vector_new_int(v, 20);
    vector_new_int(v, 30);

    // Delete 20 (the middle element)
    int target = 20;
    vector_del(v, &target, cmp_int);

    // Now we should have [10, 30]
    assert(v->size == 2);
    
    // Check if index 1 is now 30 (Shift occurred)
    int *val = (int*)vector_get(v, 1);
    assert(*val == 30);

    // Ensure 20 is really gone
    assert(vector_search(v, &target, cmp_int) == NULL);

    printf("PASSED\n");
}

int main() {
    test_initialization();
    test_push_and_resize();
    test_delete_and_shift();
    return 0;
}
