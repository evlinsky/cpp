#include <iostream>

struct Foo {
  // noexcept by default since C++11
  ~Foo() noexcept(false) {
    throw 1;//*this;
  }
};

void test_foo() {
  try {
    Foo f;
    throw "error";
  } catch (...) {
    std::cout << "Error" << std::endl;
  }
}

int main(int, char**) {
  test_foo();
}
