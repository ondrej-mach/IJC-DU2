// htab_clear.c
// Řešení IJC-DU2, 28.3.2021
// Autor: Ondřej Mach, FIT
// Přeloženo: gcc 9.3.0

#include <stdlib.h>
#include "htab_private.h"

void htab_clear(htab_t *t) {
	for (size_t i=0; i < t->arr_size; i++) {
		htab_item_t *item = t->items[i];

		// free linked list of items - if there is any
		while (item != NULL) {
			htab_item_t *next = item->next;
			htab_item_free(item);
			item = next;
		}
		t->items[i] = NULL;
	}

	t->size = 0;
}
