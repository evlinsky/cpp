#include <iostream>
#include <utility>

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

Foo bar1() {
  Foo foo;
  return std::move(foo);
}

Foo bar2() {
  Foo foo;
  return foo;
}

Foo bar3(Foo &&foo) {
  // modify foo
  return foo;
}

Foo bar4(Foo &&foo) {
  // modify foo
  return std::move(foo);
}

Foo make_foo() { return Foo{}; }

int main(int, char**) {
  // a.
  // Foo foo;
  // foo = bar1();
  // std::cout << "------" << std::endl;
  // Foo foo2 = bar2();
  // std::cout << "------" << std::endl;
  // foo = bar3(Foo{});
  // std::cout << "------" << std::endl;
  // foo = bar4(Foo{});

  // b.
  // Foo foo1 = bar1();
  // std::cout << "- RVO (opt) -" << std::endl;
  // Foo foo2 = bar2();
  // std::cout << "- Copy Elision (mandatory) -" << std::endl;
  // Foo foo3 = make_foo();
};
