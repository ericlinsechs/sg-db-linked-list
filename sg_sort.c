#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "sort.h"
#include "list.h"

static LIST_HEAD(list_start);
static list *init() {
	INIT_SG_LIST_HEAD(&list_start);
	return &list_start;
}

static list *sort(list *start) { 
    if (!start || !start->next)
        return start;
    list *left = start;
    list *right = left->next;
    left->next = NULL;

    left = sort(left);
    right = sort(right);

    for (list *merge = NULL; left || right; ) {
        if (!right || (left && left->data < right->data)) {
            if (!merge) {
                start = merge = left;
            } else {
                merge->next = left;
                merge = merge->next;
            }
            left = left->next;
        } else {
            if (!merge) {
                start = merge = right;
            } else {
                merge->next = right;
                merge = merge->next;
            }
            right = right->next;
        }
    }
    return start;
}
/* append a new node to the head of the list */
static void append(list **head_ref, int data) {
    list *new = malloc(sizeof(list));
    new->data= data, new->next = NULL;

    if (!*head_ref) {
        // the list is empty, create a single node
	*head_ref = new;
	INIT_SG_LIST_HEAD(*head_ref);
        return;
    }

    list **indirect = head_ref;

    while (*indirect)
        indirect = &((*indirect)->next);

    *indirect = new;
    return;
}
static void print(list *head, bool newline) {
    list *curr = head;
    if (!curr)
        printf("The linked list is empty!\n");

    while (curr->next != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("%d ", curr->data);
    if (newline)
      printf("\n");
}

static int cmp (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

static bool test(list *head, int* ans, int len) {
    list *curr = head;
    if (!curr) {
        printf("The linked list is empty!\n");
        return false;
    }
    
    qsort(ans, len, sizeof(int), cmp);
    curr = sort(head);

    list *curr_head = curr;

    int i = 0;
    while (i < len) {
        if (curr->data != ans[i]) {
            return false;
        }
        curr = curr->next;
        i++;
    }
    print(curr_head, false);
    return true;
}

static void list_free(list **head_ref)
{
	list *head = *head_ref; 
	list *pos = head;
	list *n = NULL;
	while (pos->next != NULL) {
		n = pos->next;
		free(pos);
		pos = n;
	}
	free(pos);
}

Sort sg_sort = {
    .initialize = init,
    .push = append,
    .print = print,
    .sort = sort,
    .test = test,
    .list_free = list_free,
};
