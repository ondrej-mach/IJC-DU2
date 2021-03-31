// htab_hash_function.c
// Řešení IJC-DU2, 28.3.2021
// Autor: Ondřej Mach, FIT
// Přeloženo: gcc 9.3.0

#include <stdint.h>
#include "htab_private.h"

size_t htab_hash_function(htab_key_t str) {
	uint32_t h=0;
	const unsigned char *p;
	for(p=(const unsigned char*)str; *p != '\0'; p++) {
		h = 65599*h + *p;
	}
	return h;
}
