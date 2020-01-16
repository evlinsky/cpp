#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
#include <iomanip>

void print_flags(const std::ifstream &ifs) {
  std::cout << std::boolalpha
            << "eof: " << std::setw(5) << ifs.eof()
            << ", fail: " << std::setw(5) << ifs.fail()
            << ", bad: " << std::setw(5) << ifs.bad() << ";"
            << " an error - " << !ifs
            << std::noboolalpha << std::endl;
}

void test(const std::string &fname) {
  std::ifstream ifs(fname);
  assert(ifs);

  print_flags(ifs);
  int i;
  ifs >> i;
  print_flags(ifs);
  ifs >> i;
  print_flags(ifs);
  ifs.close();
}

// run: "./error_flags . 123.txt 123space.txt 123a.txt"
int main(int argc, char **argv) {
  for (int i = 1; i < argc; i++) {
    std::cout << "== " << argv[i] << " ==\n";
    test(argv[i]);
  }
}
