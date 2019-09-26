.PHONY: all clean

all: ll_demo

ll_demo: obj/linked_list.o obj/ll_demo.o
	gcc $^ -o $@

obj/%.o: src/%.c | obj
	gcc -c -Wall -Werror -g3 -Iinclude $< -o $@

obj/linked_list.o: include/linked_list.h
obj/ll_demo.o: include/linked_list.h

obj:
	mkdir -p obj

clean:
	rm -rf obj ll_demo
