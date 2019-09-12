# c compiler flags
CC=gcc

# c compiler flags
CFLAGS=-Wall -Werror -I ./include
# CPPFLAGS ? CXXFLAGS?

all: compile

compile: bin main

main: bin/main.o bin/my_fav_func.o
	gcc -o main bin/main.o bin/my_fav_func.o

bin:
	mkdir bin

# = explicit + $@, $<
bin/main.o: src/main.c include/my_fav_func.h
	$(CC) $(CFLAGS) -c -o $@ $<

# = pattern-based
# NB: no include dependencies, but they can be generated.
bin/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# take header into account (workaround)
bin/my_fav_func.o: include/my_fav_func.h

clean:
	rm -fr bin main *~

# 'action' targets
.PHONY: all clean

#NB: useful make functions: patsubst, wildcard, addsuffix, notdir, etc.
