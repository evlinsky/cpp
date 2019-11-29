.PHONY: all clean

DBG_FLAGS=-fsanitize=address
EXEC=my_string

all: $(EXEC)

$(EXEC): obj/main.o obj/my_string.o
	g++ $(DBG_FLAGS) $^ -o $@

obj/%.o: src/%.cpp | obj
	g++ -c -Wall -std=c++03 -Werror -g3 $(DBG_FLAGS) -Iinclude $< -o $@

obj:
	mkdir -p obj

obj/main.o: include/my_string.h
obj/my_string.o: include/my_string.h

clean:
	rm -rf obj $(EXEC)
