.PHONY: all clean

CXX = g++
CXXFLAGS = -O2 -Wall -Wextra -Werror -std=c++17 -Iinclude
LDFLAGS = 

BINDIR = bin
SRCDIR = src
SOLUTION = include/format.hpp
TEST_NAME = smoke_test

all: test
	./test --reporters=verbose

test: src/$(TEST_NAME).cpp $(BINDIR)/doctest_main.o $(SOLUTION)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) src/$(TEST_NAME).cpp $(BINDIR)/doctest_main.o -o $@

$(BINDIR)/doctest_main.o: src/doctest_main.cpp | $(BINDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BINDIR):
	mkdir $@

clean:
	rm -rf test $(BINDIR)
