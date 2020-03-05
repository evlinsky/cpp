#include <iostream>

struct Foo {
  Foo() = default;

  Foo(const Foo &) = delete;
  Foo(Foo&&) = delete;
  //Foo(Foo&&) { std::cout << "Foo&&\n"; };
  Foo &operator=(const Foo &) = delete;
  Foo &operator=(Foo &&) = delete;
};

Foo make_foo() { return Foo(); }

// compile with -std=c++17
// compile with -std=c++11
int main(int, char**) {
  [[maybe_unused]] Foo f = make_foo();
  std::cout << "Done" << std::endl;
}
