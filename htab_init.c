// htab_init.c
// Řešení IJC-DU2, 28.3.2021
// Autor: Ondřej Mach, FIT
// Přeloženo: gcc 9.3.0

#include <stdlib.h>
#include <stddef.h>
#include "htab_private.h"

htab_t *htab_init(size_t n) {
	htab_t *t = malloc(offsetof(htab_t, items) + n * sizeof(htab_item_t *));
	t->size = 0;
	t->arr_size = n;

	for(size_t i=0; i<n; i++) {
		t->items[i] = NULL;
	}
	return t;
}
