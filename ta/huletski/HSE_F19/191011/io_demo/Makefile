.PHONY: all clean

#DBG_FLAGS=-fsanitize=address
EXEC=demo

all: $(EXEC)

$(EXEC): obj/main.o
	gcc $(DBG_FLAGS) $^ -o $@

obj/%.o: src/%.c | obj
	gcc -c -Wall -Werror -g3 $(DBF_FLAGS) -Iinclude $< -o $@

obj:
	mkdir -p obj

clean:
	rm -rf obj $(EXEC)
