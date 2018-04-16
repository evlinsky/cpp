#include <vector>
#include <iostream>
#include <cassert>

class Foo {
public:
  Foo() {}
  Foo(const Foo &) { std::cout << "Foo &" << std::endl; }
  Foo(Foo &&) { std::cout << "Foo &&" << std::endl; }
  Foo& operator=(Foo &&) {
    std::cout << "op= &&" << std::endl;
    return *this;
  }
  Foo& operator=(const Foo &) {
    std::cout << "op= &" << std::endl;
    return *this;
  }
};

int main(int, char**) {
  // a.
  // auto vfoo = std::vector<Foo>{};
  // vfoo.reserve(2);
  // Foo foo;
  // vfoo.push_back(foo);
  // vfoo.push_back(Foo{});

  // b.
  // auto vfoo = std::vector<Foo>{};
  // vfoo.shrink_to_fit();
  // assert(vfoo.capacity() == 0);
  
  // Foo foo;
  // vfoo.push_back(foo);
  // assert(vfoo.capacity() == 1);

  // vfoo.push_back(Foo{});
  // assert(vfoo.capacity() == 2);
  return 0;
}
