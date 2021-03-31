// htab_move.c
// Řešení IJC-DU2, 28.3.2021
// Autor: Ondřej Mach, FIT
// Přeloženo: gcc 9.3.0

#include <stdlib.h>
//#include <stddef.h>
#include "htab_private.h"

htab_t *htab_move(size_t n, htab_t *oldTab) {
	htab_t *newTab = htab_init(n);

	for (size_t i=0; i < oldTab->arr_size; i++) {
		htab_item_t *item = oldTab->items[i];

		// move all items form linked list
		while (item != NULL) {
			htab_item_t *next = item->next;

			htab_pair_t *movedPair = htab_lookup_add(newTab, item->pair.key);
			movedPair->value = item->pair.value;

			item = next;
		}
		oldTab->items[i] = NULL;
	}

	return newTab;
}
