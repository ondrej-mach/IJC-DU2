// htab_move.c
// Řešení IJC-DU2, 28.3.2021
// Autor: Ondřej Mach, FIT
// Přeloženo: gcc 9.3.0

#include <stdlib.h>
//#include <stddef.h>
#include "htab_private.h"

htab_t *htab_move(size_t n, htab_t *oldTab) {
	htab_t *newTab = htab_init(n);
	if (newTab == NULL) {
		return NULL;
	}

	for (size_t i=0; i < oldTab->arr_size; i++) {
		htab_item_t *item = oldTab->items[i];

		// move all items from the linked list
		while (item != NULL) {
			htab_pair_t *movedPair = htab_lookup_add(newTab, item->pair.key);
			if (movedPair == NULL) {
				htab_free(newTab);
				return NULL;
			}
			movedPair->value = item->pair.value;

			item = item->next;
		}
	}
	htab_clear(oldTab);
	return newTab;
}
