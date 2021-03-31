// io.c
// Řešení IJC-DU2, 28.3.2021
// Autor: Ondřej Mach, FIT
// Přeloženo: gcc 9.3.0

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

// ensures, that the long word warning is printed only once
static bool longWarned = false;

// true if whitespace, false if EOF
void readUntilSpace(FILE *f) {
	int c;
	while ((c=fgetc(f)) != EOF) {
		if (isspace(c)) {
			return;
		}
	}
}

int read_word(char *str, int maxLength, FILE *f) {
	int index = 0;
	int c;
	while ((c=fgetc(f)) != EOF) {
		if (isspace(c)) {
			// remove all heading spaces without increasing the index
			if (index == 0) {
				continue;
			}
			// if the space is after word, break the cycle
			break;
		}
		// stop reading, if the buffer is about to overflow
		if (index == maxLength-1) {
			break;
		}
		// normal case, character is just copied into the buffer
		str[index] = c;
		index++;
	}

	str[index] = '\0';

	// no valid characters were read and the file has ended
	if ((index==0) && (c == EOF)) {
		return EOF;
	}

	// normal ending, the word isn't too long
	if (isspace(c)) {
		return index;
	}
	// otherwise the word was longer
	if (!longWarned) {
		fprintf(stderr, "Word is too long, it has been truncated to %d characters.\n", maxLength-1);
		longWarned = true;
	}
	// discards the rest of the word
	readUntilSpace(f);
	// still returns maxLength - 1
	return index;
}
