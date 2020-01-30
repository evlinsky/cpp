#include <iostream>

struct X {
  int i;
  virtual ~X() {}
};
struct Y : X { int j; };
struct Z : Y { int k; };

struct A {
  int i;
  virtual ~A() {}
};
struct B {
  int j;
  virtual ~B() {}
};
struct C : A, B { int k; };

void address_change_on_upcast() {
  std::cout << "== Address Change on Upcast\n";
  std::cout << "= Single Inheritance\n";
  Z z;
  std::cout << "Object: " << &z << "\n"
            << "Base: " << static_cast<Y*>(&z) << "\n"
            << "Super base: " << static_cast<Z*>(&z) << std::endl;
  std::cout << &z.i << " " << &z.j << " " << &z.k << std::endl;

  std::cout << "\n";
  std::cout << "= Multiple Inheritance\n";
  C c;
  std::cout << "Object: " << &c << "\n"
            << "Base 1: " << static_cast<A*>(&c) << "\n"
            << "Base 2: " << static_cast<B*>(&c) << std::endl;
  std::cout << &c.i << " " << &c.j << " " << &c.k << std::endl;
}

//--------------------

void foo(B *b) {
  std::cout << "foo :&c " << b << std::endl;
}

void run_implicit_cast_demo() {
  std::cout << "== Implicit cast demo\n";
  C c;
  std::cout << "demo:&c " << &c << std::endl;
  foo(&c);
}

int main(int, char**) {
  address_change_on_upcast();
  std::cout << "\n";
  run_implicit_cast_demo();
}
