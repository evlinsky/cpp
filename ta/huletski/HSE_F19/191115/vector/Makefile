.PHONY: all clean

DBG_FLAGS=-fsanitize=address
EXEC=demo

all: $(EXEC)

$(EXEC): obj/main.o obj/my_vector.o
	g++ $(DBG_FLAGS) $^ -o $@

obj/%.o: src/%.cpp | obj
	g++ -c -Wall -Werror -g3 $(DBG_FLAGS) -Iinclude $< -o $@

obj:
	mkdir -p obj

obj/main.o: include/my_vector.h
obj/vector.o: include/my_vector.h

clean:
	rm -rf obj $(EXEC)
