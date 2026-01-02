#include <stdio.h>
#include <assert.h>
#include <stdint.h> /* Required for intptr_t */
#include "../vector/vector.h"


 /* This function handles the "Impedance Mismatch" between storage and search.
 *
 * PARAM 'a' (From Vector): IMMEDIATE VALUE.
 * The vector was optimized to store integers directly inside the pointer bits.
 * 'a' is NOT a valid memory address. It is the number itself (e.g. 0x...32).
 * -> We must CAST it (Unpack).
 *
 * PARAM 'b' (From Caller): MEMORY REFERENCE.
 * The search function requires a generic pointer to the target.
 * 'b' points to a variable living on the stack (e.g. &target).
 * -> We must DEREFERENCE it (Read Memory).
 */
int cmp_int(void *a, void *b) {
    int val_a = (int)(intptr_t)a; /* Unpack: Treat pointer address as data */
    int val_b = *(int*)b;         /* Deref:  Follow pointer to read data */
    return val_a - val_b;
}

void test_initialization() {
    printf("Test 1: Initialization... ");

    Vector *v = vector_create();

    /* Sanity check: Ensure struct is allocated and defaults are set. */
    assert(v != NULL);
    assert(v->size == 0);
    assert(v->max_size == 4);

    v_destroy(v, NULL); /* Clean up vector struct (no items to free) */
    printf("PASSED\n");
}

void test_push_and_resize() {
    printf("Test 2: Push and Automatic Resize... ");

    Vector *v = vector_create();

    /* FILL VECTOR
     * We are pushing integers cast to void*.
     * Memory layout: [ITEMS ARRAY] -> [10][20][30][40] (contiguous)
     */
    vector_new_int(v, 10);
    vector_new_int(v, 20);
    vector_new_int(v, 30);
    vector_new_int(v, 40);

    /* Boundary check before resize */
    assert(v->size == 4);
    assert(v->max_size == 4);

    /* FORCE RESIZE
     * Pushing the 5th element triggers realloc() inside vector_push.
     * Capacity should double to 8.
     */
    vector_new_int(v, 50);

    assert(v->size == 5);
    assert(v->max_size == 8);

    /* DATA VERIFICATION
     * vector_get(v, 4) returns a void* containing 0x32 (50).
     *
     * WRONG WAY:  *(int*)ptr
     * This tries to read memory at address 50 and will launch a SEGFAULT (Core Dump).
     *
     * RIGHT WAY:  (int)ptr
     * Because the address IS the value.
     */
    int val = (int)(intptr_t)vector_get(v, 4); 
    assert(val == 50);

    v_destroy(v, NULL);
    printf("PASSED\n");
}

void test_delete_and_shift() {
    printf("Test 3: Deletion and Shift... ");

    Vector *v = vector_create();

    /* Setup: [10, 20, 30] */
    vector_new_int(v, 10);
    vector_new_int(v, 20);
    vector_new_int(v, 30);

    /* DELETE OPERATIONS
     * We pass '&target'  because the API expects a void*.
     * The cmp_int function will handle the comparison logic.
     * We pass NULL as destructor because '20' is not malloc'd (it's embedded).
     */
    int target = 20;
    vector_del(v, &target, cmp_int, NULL);

    /* Verify Size */
    assert(v->size == 2);

    /* VERIFY SHIFT
     * Memory was: [10][20][30]
     * Memory is:  [10][30]
     * Index 1 must now contain 30.
     */
    int val = (int)(intptr_t)vector_get(v, 1);
    assert(val == 30);

    /* Verify Search logic confirms deletion */
    assert(vector_search(v, &target, cmp_int) == NULL);

    v_destroy(v, NULL);
    printf("PASSED\n");
}

int main() {
    test_initialization();
    test_push_and_resize();
    test_delete_and_shift();
    return 0;
}
