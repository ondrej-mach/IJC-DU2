// tail.c
// Řešení IJC-DU2, 24.3.2021
// Autor: Ondřej Mach, FIT
// Přeloženo: gcc 9.3.0

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// line length with terminating \0
#define MAX_LINE_LENGTH 512
// default number of allocated lines ideally power of 2
#define MALLOC_LINES 16

static FILE *inFile = NULL;
// After the first long line wrning is sent, this will be set to true
static bool longLineWarned = false;

void closeInFile() {
	fclose(inFile);
}

// increments the pointer, until the first character is not whitespace
// modifies the argument, so be careful
void removeWhitespace(char **pStr) {
	while (isspace(**pStr)) {
		(*pStr)++;
	}
}

// read and discard all the characters from file until there is /n
void readUntilLN(FILE *f) {
	int c;
	while ((c=fgetc(f)) != EOF) {
		if (c == '\n') {
			return;
		}
	}
}

// counts to end, then prints n last lines
void printLinesFromEnd(FILE *f, unsigned long n) {
	bool success = false;

	size_t allocatedLines = MALLOC_LINES;
	size_t lineIndex = 0;
	size_t charIndex = 0;

	char **lines = malloc(sizeof(char *) * allocatedLines);
	if (lines == NULL) {
		goto DEALLOCATE;
	}

	lines[lineIndex] = malloc(MAX_LINE_LENGTH);
	if (lines[lineIndex] == NULL) {
		goto DEALLOCATE;
	}

	int c;
	while ((c=fgetc(f)) != EOF) {
		if ((c == '\n') || (charIndex == MAX_LINE_LENGTH - 1)) {
			// if line is too long
			if (c != '\n') {
				// if this is the first warning
				if (!longLineWarned) {
					fprintf(stderr, "Line %zu is too long, it was truncated to %d characters\n", lineIndex+1, MAX_LINE_LENGTH-1);
					longLineWarned = true;
				}
				readUntilLN(f);
			}
			// Add termination zero to the end of the string
			// note that \n is not stored in the string
			// because it'll always be there
			lines[lineIndex][charIndex++] = '\0';

			lineIndex++;
			charIndex = 0;

			if (lineIndex >= allocatedLines) {
				allocatedLines <<= 1;
				char **tmp = realloc(lines, sizeof(char *) * allocatedLines);
				if (tmp == NULL) {
					goto DEALLOCATE;
				}
				lines = tmp;
			}

			lines[lineIndex] = malloc(MAX_LINE_LENGTH);

			// if there is any unused line, free it
			// this is optional, program uses less memory when running
			// everything will be deallocated again at the end of the function
			if (lineIndex >= n+1) {
				free(lines[lineIndex-1-n]);
				lines[lineIndex-1-n] = NULL;
			}
			continue;
		}
		lines[lineIndex][charIndex++] = c;
	}

	// if number of lines to print is greater than the file itself
	// then start at 0
	size_t start = (lineIndex > n) ? lineIndex-n : 0;
	for (size_t i=start; i<lineIndex; i++) {
		printf("%s\n", lines[i]);
	}
	// everything is done, so success variable is set
	// if program jumped to DEALLOCATE before this point, it is considered an error
	success = true;

	DEALLOCATE:
	if (lines != NULL) {
		for (size_t i=0; i<=lineIndex; i++) {
			free(lines[i]);
		}
	}
	free(lines);

	if (!success) {
		fprintf(stderr, "Unable to allocate more memory\n");
		exit(1);
	}
}

// prints n lines counting from start
void printLinesFromStart(FILE *f, unsigned long n) {
	unsigned long currentLine = 1;
	int c;
	while ((c=fgetc(f)) != EOF) {
		if (currentLine >= n) {
			fputc(c, stdout);
		} else if (c == '\n') {
			currentLine++;
		}
	}
}

typedef struct {
	bool countFromEnd;
    unsigned long numLines;
} Options;

// returns options, but also sets inFile, which is global
Options parseArgs(int argc, char **argv) {
	// defaults
	Options opts = {
		.countFromEnd = true,
		.numLines = 10
	};

	int optIndex = 1;
	while (optIndex < argc) {
		if (strcmp(argv[optIndex], "-n") == 0) {
			optIndex++;

			char *numberStr = argv[optIndex];
			removeWhitespace(&numberStr);
			if (numberStr[0] == '+') {
				opts.countFromEnd = false;
			}

			char *numberEnd;
			opts.numLines = strtoul(numberStr, &numberEnd, 10);

			if (numberEnd[0] != '\0') {
				fprintf(stderr, "Invalid number of lines '%s'\n", argv[optIndex]);
				exit(1);
			}

			optIndex++;
			continue;
		}

		if (inFile == NULL) {
			inFile = fopen(argv[optIndex], "r");
			atexit(closeInFile);
			optIndex++;
			continue;
		}

		// if none of conditions passes, there is nothing to do twith the argument
		fprintf(stderr, "Bad argument \"%s\"\n", argv[optIndex]);
		exit(1);
	}
	return opts;
}

int main(int argc, char **argv) {
	// lines are counted from the beginning or from the end

	Options opts = parseArgs(argc, argv);

	if (inFile == NULL) {
		inFile = stdin;
	}

	if (opts.countFromEnd) {
		printLinesFromEnd(inFile, opts.numLines);
	} else {
		printLinesFromStart(inFile, opts.numLines);
	}
}
