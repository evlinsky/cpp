#include <iostream>

class Foo {
public:
  void foo() & { std::cout << "foo &" << std::endl; }
  void foo() && { std::cout << "foo &&" << std::endl; }
};

int main(int, char**) {
  Foo{}.foo();
  Foo f;
  f.foo();
  // [usage example] Int{1} + Int{2} = Int{8};
  // void operator+(...) _&_
}
