#include <gtest/gtest.h>
#include <vector>
#include <cassert>
#include <sstream>

void always_die() {
  assert(0);
}

// checks if process dies
TEST(MyDeathTest, TestAlwaysDie) {
  std::vector<int> vi;
  ASSERT_DEATH(always_die(), ".*? Assertion .*? failed");
}

TEST(MyDeathTest, ExceptionThrow) {
  std::vector<int> vi;
  ASSERT_DEATH(vi.at(0), "");
}

TEST(StringStreamTest, ExceptionOnFailThrow) {
  std::stringstream ss("");
  ss.exceptions(ss.exceptions() | ss.failbit);
  char c;
  ASSERT_THROW(ss >> c, std::iostream::failure);
  ss.exceptions(ss.exceptions() & ~ss.failbit);
  ASSERT_NO_THROW(ss >> c);
}

// g++ 03-gtest-extra.cpp -Wall -lgtest -lgtest_main -lpthread && ./a.out --gtest_death_test_style=threadsafe
