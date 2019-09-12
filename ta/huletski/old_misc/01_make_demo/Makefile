# c compiler flags
CC=gcc

# c compiler flags
CFLAGS=-Wall -Werror -I ./includes
# CPPFLAGS ? CXXFLAGS?

all: hello

hello: hello.o my_prints.o
	$(CC) hello.o my_prints.o -o hello

hello.o: hello.c includes/my_prints.h
	$(CC) $(CFLAGS) -c hello.c

# NB: mimics implicit make rule
my_prints.o: my_prints.c
	$(CC) $(CFLAGS) -c my_prints.c

# NB: no include dependencies, but they can be generated.
#%.o: %.c
#	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o hello *~

.PHONY: all clean
