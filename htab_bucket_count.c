// htab_bucket_count.c
// Řešení IJC-DU2, 28.3.2021
// Autor: Ondřej Mach, FIT
// Přeloženo: gcc 9.3.0

#include "htab_private.h"

size_t htab_bucket_count(const htab_t *t) {
	return t->arr_size;
}
