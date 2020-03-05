#include <iostream>
#include <optional>

class Foo {
public:
  Foo() { std::cout << "Foo\n"; }
  Foo(const Foo &) { std::cout << "Foo &\n"; }
  Foo(Foo &&) noexcept { std::cout << "Foo &&\n"; }
  Foo& operator=(Foo &&) noexcept {
    std::cout << "op= &&\n";
    return *this;
  }
  Foo& operator=(const Foo &) {
    std::cout << "op= &\n";
    return *this;
  }
};

// b.

void func_b(Foo &&f) {
  Foo foo(f);
}

// c.

void func_c(Foo &&f) {
  std::cout << "func_c &&\n";
}

void func_c(const Foo &f) {
  std::cout << "func_c &\n";
}

// d.

Foo func_d_plain() {
  Foo foo;
  return foo;
}

Foo func_d_paren() {
  Foo foo;
  return (foo);
}

Foo func_d_multi_paren() {
  Foo foo;
  return ((foo));
}

Foo func_d_paren_move() {
  Foo foo;
  return (std::move(foo));
}

Foo func_d_braces() {
  Foo foo;
  return {foo};
}

Foo func_d_braces_move() {
  Foo foo;
  return {std::move(foo)};
}

int main(int, char**) {
  // a. rval ref to rval ref
  // Foo foo_a;
  // Foo&& rv_foo1 = Foo(foo_a);
  // Foo&& rv_foo2 = std::move(rv_foo1);

  // b. create from passed rval ref
  // func_b(Foo{});

  // c. rval ref overload
  // Foo&& foo_c = Foo{};
  // func_c(foo_c);
  // func_c(Foo{});

  // d. return
  // std::cout << "= return foo;\n";
  // func_d_plain();
  // std::cout << "= return (foo);\n";
  // func_d_paren();
  // std::cout << "= return ((foo));\n";
  // func_d_multi_paren();
  // std::cout << "= return (std::move(foo));\n";
  // func_d_paren_move();
  // std::cout << "= return {foo};\n";
  // func_d_braces();
  // std::cout << "= return {std::move(foo)};\n";
  // func_d_braces_move();

  // d. extra
  // try with -fno-elide-constructors
}
