#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "sort.h"
#include "list.h"

static LIST_HEAD(list_start);
static list *init()
{
	return &list_start;
}

static list *sort(list *start)
{ 
    // check if input contains only 0/1 node
    if (!start || start->next == start)
        return start;
    list *left = start;
    list *right = left->next;
    
    left->next = left;
    left->prev->next = right;
    right->prev = left->prev;
    left->prev = left;

    left = sort(left);
    right = sort(right);

    for (list *merge = NULL; left || right != start; ) {
        if (right == start || (left && left->data < right->data)) {
            if (!merge) {
                start = merge = left;
            } else {
		left->prev = merge; 		// merge == right->prev
		left->next = merge->next; 	// merge->next == right
                merge->next = left; 		// merge -> left
		left->next->prev = left; 	// right->prev = left

                merge = merge->next; 		// merge == left
            }
            left = NULL;
        } else {
            if (!merge) {
                start = merge = right; 
            } else { 
		if (merge == merge->next) {
			merge->next = right;
			merge->prev = right->prev; // right->prev == start
			right->prev = merge;
			merge->prev->next = merge;
		}
		merge = merge->next;
            }
            right = right->next;
        }
    }
    return start;
}

/* push a new node to the head of the list */
static void push(list **head_ref, int data)
{
    list *new_head = (list *)malloc(sizeof(list));
    new_head->data = data;

    if (!*head_ref) {
	*head_ref = new_head;
	INIT_LIST_HEAD(*head_ref);
        return;
    }

    list *last = (*head_ref)->prev;
    new_head->next = *head_ref;
    new_head->prev = last;
    last->next = (*head_ref)->prev = new_head;
    *head_ref = new_head;
    return;
}
static void print(list *head, bool newline)
{
    list *curr = head;
    if (!curr)
        printf("The linked list is empty!\n");

    while (curr->next != head) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("%d ", curr->data);
    if (newline)
      printf("\n");
}

static int cmp (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

static bool test(list *head, int* ans, int len)
{
    list *curr = head;
    if (!curr) {
        printf("The linked list is empty!\n");
        return false;
    }
    
    qsort(ans, len, sizeof(int), cmp);
    curr = sort(head);

    int i = 0;
    while (i < len) {
        if (curr->data != ans[i]) {
            return false;
        }
        curr = curr->next;
        i++;
    }
    print(curr, false);
    return true;
}
static void list_free(list **head_ref)
{
	list *head = *head_ref; 
	list *pos = NULL;
	list *n = NULL;
	list_for_each_safe(pos, n, head)
		free(pos);
	free(pos);
}

Sort dbly_sort = {
    .initialize = init,
    .push = push,
    .print = print,
    .sort = sort,
    .test = test,
    .list_free = list_free,
};
