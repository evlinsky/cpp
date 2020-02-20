#include <iostream>

struct Foo {
  ~Foo() { std::cout << "~Foo" << std::endl; }
};

void foo() {
  Foo f1;
  throw 1;
  Foo f2;
}

void bar() {
  Foo b1;
  foo();
  Foo b2;
}

int main(int, char**) {
  bar();
  // try {
  //   bar();
  // } catch (...) {}
}
