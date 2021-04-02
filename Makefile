CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Wextra -fPIC -g #-DHASHTEST -DMOVETEST
CXXFLAGS=-std=c++17 -pedantic -Wall
LIBHTAB_OBJECTS=htab_clear.o  htab_find.o  htab_free.o  htab_hash_function.o  htab_init.o  htab_size.o htab_lookup_add.o htab_for_each.o htab_item_free.o htab_item_init.o htab_move.o htab_erase.o
EXECUTABLES=tail wordcount wordcount-dynamic
XLOGIN=xmacho12
TEST_FILES=reference_out.txt dynamic_out.txt static_out.txt

all: $(EXECUTABLES) libhtab.so

wordcount: wordcount.o io.o libhtab.a
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -static -L. -lhtab -o $@

wordcount-dynamic: wordcount.o io.o
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -L. -lhtab -o $@

libhtab.a: $(LIBHTAB_OBJECTS)
	ar rcs $@ $^
	ranlib $@

libhtab.so: $(LIBHTAB_OBJECTS)
	$(CC) $(CPPFLAGS) $(CFLAGS) -shared $^ -o $@

test: wordcount- wordcount wordcount-dynamic libhtab.so
	rm $(TEST_FILES)
	./wordcount- < plain_text.txt | sort > reference_out.txt
	./wordcount < plain_text.txt | sort > static_out.txt
	./wordcount-dynamic < plain_text.txt | sort > dynamic_out.txt
	diff static_out.txt reference_out.txt > /dev/null && echo static passed || echo static failed
	diff dynamic_out.txt reference_out.txt > /dev/null && echo dynamic passed || echo dynamic failed

zip:
	zip $(XLOGIN).zip *.c *.h Makefile

clean:
	rm -f *.o *.so *.a $(XLOGIN).zip $(EXECUTABLES) $(TEST_FILES)
