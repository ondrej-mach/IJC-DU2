// htab_lookup_add.c
// Řešení IJC-DU2, 28.3.2021
// Autor: Ondřej Mach, FIT
// Přeloženo: gcc 9.3.0

#include <stdlib.h>
#include <string.h>
#include "htab_private.h"

htab_item_t *htab_item_init(htab_key_t key) {
	htab_item_t *item = malloc(sizeof(htab_item_t));
	// allocate its key and set it
	item->pair.key = malloc(strlen(key) + 1);
	strcpy((char *)item->pair.key, key);
	// set the value to 0 by default
	item->pair.value = 0;
	// pointer to the next item is initialized to NULL,
	// since this is the last item in the list
	item->next = NULL;

	return item;
}
