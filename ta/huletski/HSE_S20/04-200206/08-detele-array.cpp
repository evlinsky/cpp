#include <stdexcept>
#include <iostream>
#include <memory>

struct Baz {
  static int i;
  Baz() : c(std::make_unique<char>('a')) {
    std::cout << __func__ << std::endl;
  }
  ~Baz() noexcept(false) {
    if (i == 2) { throw i; }
    i++;
    std::cout << "~Baz - " << i << std::endl;
  }
  std::unique_ptr<char> c;
};

int Baz::i = 0;

void test_baz() {
  Baz* baz = new Baz[5];
  try {
    // generic type clean up
    delete [] baz; // -> leak if dtor throws
  } catch (const int &i) {
    std::cout << "Error:"<< i << std::endl;
  }
}

int main(int, char**) {
  test_baz();
}
