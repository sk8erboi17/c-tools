#include<stdio.h>
#include<stdlib.h>
#include "../utils/memory.h"
#include "linkedlist.h"

/*Search, the void *x is a generic item, so we need to use the callback help cmp*/
list *ll_search(list *l, void *x, int (*cmp)(void *, void *)) {
    //Base case: END OF LIST
    if (l == NULL) {
        return NULL;
    }

    if(cmp(l->item, x) == 0) {
        return l;
    } else {
        return ll_search(l->next, x, cmp);
    }
} 

/*Insert an item*/
list *ll_push(list *head, void *new_item) {
    list *new_node = xmalloc(sizeof(list));
    new_node->item = new_item; // new_item must to be a pointer to a date that remain in memory, not local var.
    new_node->next = head;
    return new_node;
}

/*Return null if a item is not found*/
list *ll_del(list *head, void *target, int(*cmp)(void *, void *)) {
  list *curr = head;
  list *prev = NULL;
  while(curr != NULL) {
    if(cmp(curr->item, target) == 0) {
        if(prev == NULL) {
            head = curr->next;
        } else {
            prev->next = curr->next;
        }
        free(curr->item);
        free(curr);

        return head;
    }
    // Go to next node
    prev = curr; 
    curr = curr->next;
  }   
    //Nothing found
    return head;
}
