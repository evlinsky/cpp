.PHONY: all clean

#DBG_FLAGS=-fsanitize=address
EXEC=demo

all: $(EXEC)

$(EXEC): obj/main.o obj/charz.o obj/utils.o
	gcc $(DBG_FLAGS) $^ -o $@

obj/%.o: src/%.c | obj
	gcc -c -Wall -Werror -g3 $(DBF_FLAGS) -Iinclude $< -o $@

obj/main.o: include/charz.h include/utils.h
obj/charz.o: include/charz.h
obj/utils.o: include/charz.h

obj:
	mkdir -p obj

clean:
	rm -rf obj $(EXEC)
