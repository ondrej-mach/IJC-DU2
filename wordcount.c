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
	const char *memErrMsg = "Memory could not be allocated, exiting\n";
	htab_t *table = htab_init(HASTABLE_SIZE);
	// if new table cannot be allocated
	if (table == NULL) {
		fprintf(stderr, "%s", memErrMsg);
		exit(1);
	}
	// only one warning is issued, next are ignored
	bool longWarned = false;
	// buffer for words
	char word[WORD_LENGTH];
	// length of the read word to detect words that are too long
	int len;
	// read words from stdin, while you can
	while ((len = read_word(word, WORD_LENGTH, stdin)) != EOF) {
		if ((len >= WORD_LENGTH - 1) && !longWarned) {
			fprintf(stderr, "Word is too long, it has been truncated to %d characters.\n", WORD_LENGTH-1);
			longWarned = true;
		}
		// get the pointer to the pair
		// this function will find existing or create a new one
		// if new one is created, the value is initialized to zero
		htab_pair_t *pair = htab_lookup_add(table, word);
		// pair did not exist and could not be allocated
		if (pair == NULL) {
			fprintf(stderr, "%s", memErrMsg);
			htab_free(table);
			exit(1);
		}
		// value is incremented for each occurence of the word
		pair->value++;
	}

	// copy the pointer to original table
	htab_t *tableToPrint = table;

	#ifdef MOVETEST
		// test the move function
		tableToPrint = htab_move(NEW_HASTABLE_SIZE, table);
		htab_free(table);
		// if new table cannot be allocated
		if (tableToPrint == NULL) {
			fprintf(stderr, "%s", memErrMsg);
			exit(1);
		}
	#endif

	// print every stored with the number of its occurences
	htab_for_each(tableToPrint, &printPair);
	// if MOVETEST is not defined, original table points to the same location
	// and thus is freed at the same time
	// in case the MOVETEST is defined, the original table has been freed already
	htab_free(tableToPrint);
}
