// htab_find.c
// Řešení IJC-DU2, 28.3.2021
// Autor: Ondřej Mach, FIT
// Přeloženo: gcc 9.3.0

#include <stdlib.h>
#include <string.h>
#include "htab_private.h"

htab_pair_t *htab_find(htab_t *t, htab_key_t key) {
	size_t index = htab_hash_function(key) % t->arr_size;

	htab_item_t *item = t->items[index];

	while (item != NULL) {
		if (strcmp(item->pair.key, key) == 0) {
			return &item->pair;
		}
		item = item->next;
	}
	return NULL;
}
