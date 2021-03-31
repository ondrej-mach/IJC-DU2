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

	// allocate new item
	*item = malloc(sizeof(htab_item_t));
	// allocate its key and set it
	htab_key_t *newKeyPtr = &(*item)->pair.key;
	*newKeyPtr = malloc(strlen(key) + 1);
	strcpy((char *)*newKeyPtr, key);
	// set the value to 0 by default
	(*item)->pair.value = 0;
	// pointer to the next item is initialiyed to 0,
	// since this is the last item in the list
	(*item)->next = NULL;

	return &(*item)->pair;
}
