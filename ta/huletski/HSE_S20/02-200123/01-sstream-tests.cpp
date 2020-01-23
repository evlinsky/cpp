#include <sstream>
#include <cstdio>

#define DO_CHECK(expr)                                          \
  test_utils::check(expr, __func__, __FILE__, __LINE__);

namespace test_utils {
  void check(bool status, const char *fn_name,
             const char *file_name, std::size_t line_i) {
    if (!status) {
      fprintf(stderr, "FAILED: %s at %s:%ld\n", fn_name, file_name, line_i);
    }
    // update suit's state
  }
}

void test_single_char_read() {
  std::stringstream ss("Test");
  char c;
  ss >> c;
  DO_CHECK(c == 'T');
  DO_CHECK(static_cast<bool>(ss)); // NB: operator bool is explicit
                                   // NB: if (ss) doesn't require cast
  DO_CHECK(bool(ss));
  DO_CHECK(!!ss);
}

void test_text_int_read() {
  std::stringstream ss("123");
  int i;
  ss >> i;
  DO_CHECK(i == 123);
  DO_CHECK(static_cast<bool>(ss));
  DO_CHECK(ss.eof());
}

void test_binary_int_read() {
  std::stringstream ss("12345");
  int i;
  ss.read(reinterpret_cast<char*>(&i), sizeof i);
  DO_CHECK(i == 0x34333230); // FIXME: 0x34333231
  DO_CHECK(static_cast<bool>(ss));
}

int main(int, char**) {
  test_single_char_read();
  test_text_int_read();
  test_binary_int_read();
}

