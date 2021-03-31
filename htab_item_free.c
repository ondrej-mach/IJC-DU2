// htab_clear.c
// Řešení IJC-DU2, 28.3.2021
// Autor: Ondřej Mach, FIT
// Přeloženo: gcc 9.3.0

#include <stdlib.h>
#include "htab_private.h"

void htab_item_free(htab_item_t *item) {
	free((char *)item->pair.key);
	free(item);
}
