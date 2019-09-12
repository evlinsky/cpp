#include <iostream>

class Foo {
public:
  Foo() {}
  Foo(const Foo &) { std::cout << "Foo &" << std::endl; }
  Foo(Foo &&) { std::cout << "Foo &&" << std::endl; }
  Foo& operator=(Foo &&) {
    std::cout << "op= &&" << std::endl;
    return *this;
  }
  Foo& operator=(const Foo &) = delete;
};

void bar(Foo &&foo) {
  Foo foo_extra(foo);
}

int main(int, char**) {
  // NB: no auto&&, T&& ("universal" references)
  
  // a.
  //int &lvr_i = 5;
  //int &&rvr_i = 5;

  // b.
  // Foo foo;
  // Foo &&rv_foo = foo;
  // Foo &&rv_foo_extra = rv_foo;

  // c.
  //bar(Foo{});
  
  return 0;
}
