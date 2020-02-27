#include <iostream>

struct Foo {
  Foo() { std::cout << "Foo()\n"; }
  Foo(const Foo &that) { std::cout << "Foo&\n"; }
  Foo(Foo &&) noexcept { std::cout << "Foo&&\n"; }
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

struct Bar {
  // a. define dtor only
  // ~Bar() = default;

  // b. define cp only
  // Bar() {}
  // Bar(const Bar&) = default;
  // Bar& operator=(const Bar &) = default;

  // c. define mv only
  // Bar() {}
  // Bar(Bar&&) = default;
  // Bar& operator=(Bar &&) = default;
private:
  Foo f;
};

int main(int, char**) {
  Bar b1, b2(b1);
  Bar b3(std::move(b1));
  b1 = b2;
  b1 = std::move(b2);
}
