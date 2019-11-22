.PHONY: all clean

DBG_FLAGS=-fsanitize=address
EXEC=intset_tests

all: $(EXEC)

$(EXEC): obj/main.o obj/intset.o
	g++ $(DBG_FLAGS) $^ -o $@

obj/%.o: src/%.cpp | obj
	g++ -c -Wall -std=c++03 -Werror -g3 $(DBG_FLAGS) -Iinclude $< -o $@

obj:
	mkdir -p obj

obj/main.o: include/intset.h
obj/intset.o: include/intset.h

clean:
	rm -rf obj $(EXEC)
