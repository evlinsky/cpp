#include <iostream>
#include <sstream>

void print_stream(std::istream &is) {
  // TODO: implement me
}

void test_print_stream(const std::string &str) {
  std::istringstream iss(str);
  print_stream(iss);
  std::cout << std::endl;
}

int main(int argc, char **argv) {
  test_print_stream("abc");
  test_print_stream("a   b c");
}
