.PHONY: all clean

#DBG_FLAGS=-fsanitize=address

all: il_demo

il_demo: obj/intrusive_list.o obj/il_demo.o
	gcc $(DBG_FLAGS) $^ -o $@

obj/%.o: src/%.c | obj
	gcc -c -Wall -Werror -g3 $(DBG_FLAGS) -Iinclude $< -o $@

obj/intrusive_list.o: include/intrusive_list.h
obj/il_demo.o: include/intrusive_list.h

obj:
	mkdir -p obj

clean:
	rm -rf obj il_demo
