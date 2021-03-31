// htab_erase.c
// Řešení IJC-DU2, 28.3.2021
// Autor: Ondřej Mach, FIT
// Přeloženo: gcc 9.3.0

#include <stdlib.h>
#include "htab_private.h"

bool htab_erase(htab_t *t, htab_key_t key) {
	size_t index = htab_hash_function(key) % t->arr_size;

	htab_item_t **item = &t->items[index];

	while (*item != NULL) {
		// if you find it, delete it and return true
		if (strcmp((*item)->pair.key, key) == 0) {
			htab_item_t *erasedItem = *item;
			(*item) = (*item)->next;
			htab_item_free(erasedItem);
			// one item less in table
			t->size--;
			return true;
		}
		item = &(*item)->next;
	}
	// if item is not there, return false
	return false;
}
