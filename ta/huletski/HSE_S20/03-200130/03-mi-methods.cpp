#include <iostream>

struct A {
  virtual ~A() {}
  void foo() {}
  void bar(int) {}
};

struct B {
  virtual ~B() {}
  void foo() {}
//private:
//  void bar(double) {}
};

struct C : A, B {
};

int main(int, char**) {
  C c;
  //c.foo(); // NB: simultaneous lookup among bases
  //c.A::foo();
  //c.bar(1);
}
