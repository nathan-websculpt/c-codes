//https://github.com/mkirchner/linked-list-good-taste/blob/main/src/list.c

#include <stdio.h>
#include "list.h"

/**
 * Find an item in the list.
 *
 * Finds the item identified by `target` in the list `l` and returns a
 * the address of the `next` pointer of the item before `target`.
 * This is a linear O(n) search.
 *
 * @param l A list of integers
 * @param target The list item to find
 * @return Pointer to the `next` pointer of the item that precedes
 *         `target`, or `head`. Pointer to the last `next` field in the list
 *         if `target` is not in `l`.
 */
static inline list_item **find_indirect(list *l, list_item *target)
{
	list_item **p = &l->head;
	while (*p != target)
		p = &(*p)->next;
	return p;
}

void remove_elegant(list *l, list_item *target)
{
	// undef results if target is not in l
	list_item **p = find_indirect(l, target);
	*p = target->next;
}

/**
 * Insert an item into the list.
 *
 * Inserts an item `item` into the list `l`, before the item identified
 * by `before`. Runtime is O(n) where n refers to the distance of before from
 * the list head.
 *
 * @param l A list of integers
 * @param before Pointer to item before which the new item should be inserted.
 *               If `before` points to the list head, the new item will be
 *               inserted at the beginning; if `before` is NULL or invalid,
 *               the item will be appended at the the end of the list
 * @param item The item to insert
 */
void insert_before(list *l, list_item *before, list_item *item)
{
	/* Using indirect pointers really allows us to write
	 * tight code here */
	list_item **p = find_indirect(l, before);
	*p = item;
	item->next = before;
}

size_t size(list *l)
{
	size_t k = 0;
	list_item *cur = l->head;
	while (cur) {
		cur = cur->next;
		k++;
	}
	return k;
}

int main(void)
{


}