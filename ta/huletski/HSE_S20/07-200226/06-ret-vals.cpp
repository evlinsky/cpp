#include <iostream>
#include <utility>

class Foo {
public:
  Foo() { std::cout << "Foo\n"; }
  Foo(const Foo &) { std::cout << "Foo &\n"; }
  Foo(Foo &&) noexcept { std::cout << "Foo &&\n"; }
  Foo& operator=(Foo &&) noexcept {
    std::cout << "op= &&\n";
    return *this;
  }
  Foo& operator=(const Foo &) {
    std::cout << "op= &\n";
    return *this;
  }
};

//------------------------

Foo make_foo() { return Foo{}; }
Foo make_n_move_foo() { return std::move(Foo{}); }

//------------------------

Foo move_local() {
  Foo foo;
  return std::move(foo);
}

Foo return_local() {
  Foo foo;
  return foo;
}

int main(int, char**) {
  // a. copy elision
  // std::cout << "= Make" << std::endl;
  // Foo foo1 = make_foo();
  // std::cout << "= Make and Move" << std::endl;
  // Foo foo2 = make_n_move_foo();

  // b. NRVO (named RVO)
  // std::cout << "= 1. Move local" << std::endl;
  // Foo foo1 = move_local();
  // std::cout << "= 2. Return local" << std::endl;
  // Foo foo2 = return_local();
};
