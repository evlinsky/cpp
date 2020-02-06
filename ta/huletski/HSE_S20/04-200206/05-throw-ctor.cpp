#include <iostream>

struct Foo {
  Foo(int id) : id_(id) {
    if (id == 42) { throw id; }
    std::cout << "Foo(" << id_ << ");\n";
  }
  ~Foo() { std::cout << "~Foo(" << id_ << ");\n"; }
private:
  int id_;
};

struct Bar {
  Bar()
    : f1(1), f42(42), f3(3) {
    std::cout << "Bar()\n";
  }
  ~Bar() { std::cout << "~Bar()\n"; }
  Foo f1, f42, f3;
};

struct Baz {
  Baz()
    : f1(1), f3(3) {
    throw 1;
  }
  ~Baz() { std::cout << "~Bar()\n"; }
  Foo f1, f3;
};


int main(int, char**) {
  std::cout << "== Init list exception\n";
  try {
    Bar b;
  } catch (...) {
    std::cout << "Error\n";
  }
  std::cout << "== Ctor body exception\n";
  try {
    Baz b;
  } catch (...) {
    std::cout << "Error\n";
  }

}
