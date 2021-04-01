// htab_lookup_add.c
// Řešení IJC-DU2, 28.3.2021
// Autor: Ondřej Mach, FIT
// Přeloženo: gcc 9.3.0

#include <stdlib.h>
#include <string.h>
#include "htab_private.h"

htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key) {
	size_t index = htab_hash_function(key) % t->arr_size;

	htab_item_t **item = &t->items[index];

	while (*item != NULL) {
		if (strcmp((*item)->pair.key, key) == 0) {
			return &(*item)->pair;
		}
		item = &(*item)->next;
	}

	// allocate new item at the end of the list with the given key
	*item = htab_item_init(key);
	// if item could not be added, return NULL
	if (*item == NULL) {
		return NULL;
	}
	// one more item in table
	t->size++;

	return &(*item)->pair;
}
