// wordcount.c
// Řešení IJC-DU2, 26.3.2021
// Autor: Ondřej Mach, FIT
// Přeloženo: gcc 9.3.0

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "htab.h"
#include "io.h"

// size of the word buffer. Actual word length is one less because of terminating \0
#define WORD_LENGTH 128
#define HASTABLE_SIZE 256
// only for test of htab_move()
#define NEW_HASTABLE_SIZE 30

// user-defined hash function
#ifdef HASHTEST
// hashing algorithm djb2 by Dan Bernstein
// http://www.cse.yorku.ca/~oz/hash.html
size_t htab_hash_function(htab_key_t str) {
	size_t hash = 5381;
    int c;
    while ((c = *str++) != '\0') {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
	}
    return hash;
}
#endif

// function to print (key, value) pair in the hash table
void printPair(htab_pair_t *pair) {
	printf("%s\t%d\n", pair->key, pair->value);
}

int main() {
	htab_t *table = htab_init(HASTABLE_SIZE);

	char word[WORD_LENGTH];
	// read words from stdin, while you can
	while (read_word(word, WORD_LENGTH, stdin) != EOF) {
		// get the pointer to the pair
		// this function will find existing or create a new one
		// if new one is created, the value is initialized to zero
		htab_pair_t *pair = htab_lookup_add(table, word);
		// value is incremented for each occurence of the word
		pair->value++;
	}

	// copy the pointer to original table
	htab_t *tableToPrint = table;

	#ifdef MOVETEST
		// test the move function
		tableToPrint = htab_move(NEW_HASTABLE_SIZE, table);
		htab_free(table);
	#endif

	// print every stored with the number of its occurences
	htab_for_each(tableToPrint, &printPair);
	// if MOVETEST is not defined, original table points to the same location
	// and thus is freed at the same time
	// in case the MOVETEST is defined, the original table has been freed already
	htab_free(tableToPrint);
}
