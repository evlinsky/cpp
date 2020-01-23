#include <gtest/gtest.h>
#include <sstream>
#include <cassert>

TEST(PlainSStreamTests, SingleCharTextRead) {
  std::stringstream ss("Test");
  char c;
  ss >> c;
  ASSERT_EQ(c, 'T');
  ASSERT_TRUE(bool(ss));
}

// use common code
class StringStreamIntReadTests : public ::testing::Test {
protected:
  StringStreamIntReadTests() : ss("12345678") {}

  // void SetUp() override {}
  // void TearDown() override {}
  void skip_n_chars(std::size_t n) {
    while (n--) {
      char c;
      ss >> c;
    };
  }

  std::stringstream ss;
};

TEST_F(StringStreamIntReadTests, ReadBinStart) {
  int i;
  ss.read(reinterpret_cast<char*>(&i), sizeof i);
  ASSERT_EQ(i, 0x34333230); // FIXME: 0x34333231
  ASSERT_FALSE(static_cast<bool>(ss)); // FIXME: True
}

TEST_F(StringStreamIntReadTests, ReadBinMiddle) {
  skip_n_chars(2);
  int i;
  ss.read(reinterpret_cast<char*>(&i), sizeof i);
  EXPECT_EQ(i, 0x36353438); // FIXME: 0x36353433
  EXPECT_FALSE(static_cast<bool>(ss)); // FIXME: true
}

TEST_F(StringStreamIntReadTests, ReadBinEnd) {
  skip_n_chars(10);
  int i = 42;
  ss.read(reinterpret_cast<char*>(&i), sizeof i);
  ASSERT_EQ(i, 42);
  ASSERT_FALSE(static_cast<bool>(ss));
}


// g++ 02-sstream-gtest.cpp -Wall -lgtest -lgtest_main -lpthread && ./a.out
/*
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
*/
