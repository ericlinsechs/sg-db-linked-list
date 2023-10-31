#ifndef _LIST_H
#define _LIST_H

#include "sort.h"

/*
 * Circular doubly linked list implementation.
 *
 * Some of the internal functions ("__xxx") are useful when
 * manipulating whole lists rather than single entries, as
 * sometimes we already know the next/prev entries and we can
 * generate better code by using them directly rather than
 * using the generic single-entry routines.
 */
#define LIST_HEAD_INIT(name) 		\
    {                        		\
        (int)0, &(name), &(name)	\
    }

#define LIST_HEAD(name) \
    list name = LIST_HEAD_INIT(name)
/**
 * INIT_LIST_HEAD - Initialize a list_head structure
 * @list: list_head structure to be initialized.
 *
 * Initializes the list_head to point to itself.  If it is a list header,
 * the result is an empty list.
 */
static inline void INIT_LIST_HEAD(list *list)
{
    list->next = list;
    list->prev = list;
}

static inline void INIT_SG_LIST_HEAD(list *list)
{
    list->next = NULL;
    list->prev = NULL;
}

/**
 * list_empty - tests whether a list is empty
 * @head: the list to test.
 */
static inline int list_empty(const list *head)
{
	return head->next == head;
}

static inline void list_singular_find_last(list **last, list *head)
{
	if (list_empty(head)) {
		*last = head; 
		return;
	}

	list *pos = NULL;
	for (pos = head->next; !(pos->next == head); pos = pos->next)
		;
	*last = pos;
	return;
}

/**
 * list_for_each_safe - iterate over a list safe against removal of list entry
 * @pos:	the &struct list_head to use as a loop cursor.
 * @n:		another &struct list_head to use as temporary storage
 * @head:	the head for your list.
 */
#define list_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; \
	     !(pos == (head)); \
	     pos = n, n = pos->next)
#endif
