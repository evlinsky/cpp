#include <iostream>

class Foo {
public:
  Foo() { }
  Foo(const Foo &) = default;
  Foo(Foo &&) noexcept = default;
  Foo& operator=(Foo &&) noexcept = default;

  Foo& operator=(const Foo &) & = default;
  static Foo make_foo() { return Foo(); }

  void bar() const &  { std::cout << "const &\n"; }
  void bar() &  { std::cout << "&\n"; }
  void bar() && { std::cout << "&&\n"; }
};

void baz_lv(const Foo &f)  { f.bar(); }
void baz_lv(Foo &f)  { f.bar(); }
//void baz_rv(const Foo &&f) { f.bar(); }
void baz_rv(Foo &&f) { f.bar(); }

int main(int, char**) {
  // a. Assign to rvalue
  // Foo f = Foo();
  // Foo::make_foo() = f;

  // b. Call bars
  // * 1
  // Foo::make_foo().bar();
  // Foo().bar();
  // * 2
  // Foo f;
  // Foo &lv_ref = f;
  // Foo &&rv_ref = std::move(lv_ref);
  // f.bar();
  // lv_ref.bar();
  // rv_ref.bar();
  // * 3
  // Foo f;
  // baz_lv(f);
  // baz_lv(Foo());
  // * 4
  // Foo f;
  // baz_rv(f);
  // baz_rv(Foo());
}
