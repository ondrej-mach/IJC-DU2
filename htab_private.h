// htab-private.h
// Řešení IJC-DU2, 28.3.2021
// Autor: Ondřej Mach, FIT
// Přeloženo: gcc 9.3.0

#ifndef __HTAB_PRIVATE_H__
#define __HTAB_PRIVATE_H__

#include "htab.h"

struct htab_item {
    htab_pair_t pair;
    struct htab_item *next;
};

typedef struct htab_item htab_item_t;

// The full definition of htab
struct htab {
    size_t size;
    size_t arr_size;
    htab_item_t *items[];
};

htab_item_t *htab_item_init();
void htab_item_free(htab_item_t *item);

#endif // __HTAB_PRIVATE_H__
