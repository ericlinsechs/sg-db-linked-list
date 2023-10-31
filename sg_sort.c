#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "sort.h"
#include "list.h"

static LIST_HEAD(list_start);
static list *init()
{
	INIT_SG_LIST_HEAD(&list_start);
	return &list_start;
}

static list *sort(list *start)
{ 
    if (!start || start->next == start)
        return start;
    list *left = start;
    list *right = left->next;

    list *last = NULL;
    list_singular_find_last(&last, left);
    left->next = left;
    last->next = right;

    left = sort(left);
    right = sort(right);

    for (list *merge = NULL; left || right != start; ) {
        if (right == start || (left && left->data < right->data)) {
            if (!merge) {
                start = merge = left;
            } else {
		left->next = merge->next;
                merge->next = left;
                merge = merge->next;
            }
            left = NULL;
        } else {
            if (!merge) {
                start = merge = right;
            } else {
		if (merge == merge->next) {
			list *last = NULL;
			list_singular_find_last(&last, right);
			merge->next = right;
			last->next = merge; 
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
	// Only `next` would be used in singly linked list
	(*head_ref)->prev = NULL;
        return;
    }
    
    list *last = NULL;
    list_singular_find_last(&last, *head_ref);
    new_head->next = *head_ref;
    last->next = new_head;
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
	list *pos = head;
	list *n = NULL;
	list_for_each_safe(pos, n, head)
		free(pos);
	free(pos);
}

Sort sg_sort = {
    .initialize = init,
    .push = push,
    .print = print,
    .sort = sort,
    .test = test,
    .list_free = list_free,
};
