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
  try
    : v(new int), f1(1), f42(42), f3(3) {
    std::cout << "Bar()\n";
  } catch (int &i) {
    std::cout << "Exception " << i << std::endl;
    // delete v; // NB: Undefined Behavior (@see cppref)
                 // Use RAII to prevent leak
    // return; // compiler error
    // Opt: throw another, terminate
  } // implicit throw; 
  ~Bar() { std::cout << "~Bar()\n"; }
  int *v;
  Foo f1, f42, f3;
};

int main(int, char**) {
  try {
    Bar b;
  } catch (...) {
    std::cout << "Error\n";
  }
}
