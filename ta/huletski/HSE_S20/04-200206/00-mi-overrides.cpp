#include <iostream>

struct A {
  virtual void foo() { std::cout << "A::foo\n"; }
};

struct B : /*virtual*/ A {
  void foo() override { std::cout << "B::foo\n"; };
};

struct C : B, /*virtual*/ A {
  //using A::foo;
  //using B::foo;
};

int main(int, char**) {
  C c;
  c.foo();
  c.C::foo();
}

