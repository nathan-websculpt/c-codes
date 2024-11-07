//https://github.com/mkirchner/linked-list-good-taste/blob/main/src/list.h

#ifndef LIST_H
#define LIST_H

#include <stddef.h>

struct list_item {
	int value;
	struct list_item *next;
};
typedef struct list_item list_item;

struct list {
	struct list_item *head;
};
typedef struct list list;

size_t size(list *l);
void insert_before(list *l, list_item *before, list_item *item);

void remove_elegant(list *l, list_item *target);

#endif 