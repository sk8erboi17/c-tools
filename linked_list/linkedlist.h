#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/*The LinkedList is structured by pointers which are connected each-other*/
/*node of a linkedlist*/
typedef struct node {
    void* item;
    struct node *next;

} list;

/*search a node, this is an O(N) operation*/
list *ll_search(list *l, void *x, int(*cmp)(void *, void *));

/*insert a node, this is an O(1) operation*/
list *ll_push(list *head, void *new_item);

/*delete a node, this is an O(n) operation*/
list *ll_del(list *head, void *target, int(*cmp)(void *, void*));

#endif
