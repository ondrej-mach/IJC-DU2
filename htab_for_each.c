// htab_for_each.c
// Řešení IJC-DU2, 28.3.2021
// Autor: Ondřej Mach, FIT
// Přeloženo: gcc 9.3.0

#include <stdlib.h>
#include "htab_private.h"

void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data)) {
	for (size_t i=0; i < t->arr_size; i++) {
		htab_item_t *item = t->items[i];

		while (item != NULL) {
			f(&item->pair);
			item = item->next;
		}
	}
}
