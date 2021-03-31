// htab_size.c
// Řešení IJC-DU2, 28.3.2021
// Autor: Ondřej Mach, FIT
// Přeloženo: gcc 9.3.0

#include "htab_private.h"

size_t htab_size(const htab_t *t) {
	return t->size;
}
