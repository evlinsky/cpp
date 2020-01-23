all: 01-sstream-tests 02-sstream-gtest 03-gtest-extra 04-game-of-life

01-sstream-tests: 01-sstream-tests.cpp
	g++ -Wall -o $@ $<

02-sstream-gtest: 02-sstream-gtest.cpp
	g++ -Wall -o $@ $< -lgtest -lgtest_main -lpthread

03-gtest-extra: 03-gtest-extra.cpp
	g++ -Wall -o $@ $< -lgtest -lgtest_main -lpthread

04-game-of-life: 04-game-of-life.cpp
	g++ -Wall -o $@ $< -lncurses

clean:
	rm 01-sstream-tests 02-sstream-gtest 03-gtest-extra 04-game-of-life
