#ifndef _SORT_H
#define _SORT_H

#include <stdbool.h>

typedef struct __list {
    int data;
    struct __list *next;
    struct __list *prev;
} list;

typedef struct __Sort {
    list *(*initialize)();
    void (*push)(list **head_ref, int data);
    void (*print)(list *head, bool new_line);
    list *(*sort)(list *start);
    bool (*test)(list *head, int *ans, int len);
    void (*list_free)(list **head_ref);
} Sort;

extern Sort dbly_sort;
extern Sort sg_sort;

#endif
