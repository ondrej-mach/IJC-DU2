// htab_free.c
// Řešení IJC-DU2, 28.3.2021
// Autor: Ondřej Mach, FIT
// Přeloženo: gcc 9.3.0

#include <stdlib.h>
#include "htab_private.h"

void htab_free(htab_t *t) {
	htab_clear(t);
	free(t);
}
