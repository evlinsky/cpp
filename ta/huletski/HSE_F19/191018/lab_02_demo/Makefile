.PHONY: all clean

DBG_FLAGS=-fsanitize=address
EXEC=demo

all: $(EXEC)

$(EXEC): obj/main.o obj/str.o
	gcc $(DBG_FLAGS) $^ -o $@

obj/%.o: src/%.c | obj
	gcc -c -Wall -Werror -g3 $(DBG_FLAGS) -Iinclude $< -o $@

obj:
	mkdir -p obj

obj/main.o: include/str.h
obj/str.o: include/str.h

clean:
	rm -rf obj $(EXEC)
