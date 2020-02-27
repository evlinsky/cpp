#include <iostream>
#include <utility>

struct Foo {
  Foo() { std::cout << "Foo\n"; }
  Foo(const Foo &that) { std::cout << "Foo &\n"; }
  Foo(Foo &&) noexcept { std::cout << "Foo &&\n"; }
  Foo& operator=(const Foo &) /*&*/ {
    std::cout << "op= &\n";
    return *this;
  }
  Foo& operator=(Foo &&) noexcept /*&*/ {
    std::cout << "op= &&\n";
    return *this;
  }
  ~Foo() { std::cout << "~Foo\n"; }
};

int main(int, char**) {
  std::cout << "-0 Ctor-\n";
  Foo f_dflt;                        // ctor
  std::cout << "-1 Cp Ctor-\n";
  Foo f_cp(f_dflt);                  // copy ctor
  std::cout << "-2 Cp Assign-\n";
  f_dflt = f_cp;                     // copy assign
  std::cout << "-3 Mv Ctor-\n";
  Foo f_mv = std::move(f_dflt);      // mv ctor
  std::cout << "-4 Mv Assign-\n";
  f_dflt = Foo();                    // mv assign
  std::cout << "====\n";
}
