#include <iostream>
#include <vector>

class Foo {
public:
  Foo() {}
  Foo(const Foo &) { std::cout << "  Foo &" << std::endl; }
  Foo(Foo &&) { std::cout << "  Foo &&" << std::endl; }
  Foo& operator=(Foo &&) {
    std::cout << "  Foo::op= &&" << std::endl;
    return *this;
  }
  Foo& operator=(const Foo &) {
    std::cout << "  Foo::op= &" << std::endl;
    return *this;
  }
};

class FooNE {
public:
  FooNE() {}
  FooNE(const FooNE &) { std::cout << "  FooNE &" << std::endl; }
  FooNE(FooNE &&) noexcept { std::cout << "  FooNE &&" << std::endl; }
  FooNE& operator=(FooNE &&) noexcept {
    std::cout << "  FooNE::op= &&" << std::endl;
    return *this;
  }
  FooNE& operator=(const FooNE &) {
    std::cout << "  FooNE::op= &" << std::endl;
    return *this;
  }
};

template <typename T>
void test_vector_of() {
  std::cout << "= " << typeid(T).name() << "\n";
  std::cout << "- Init\n";
  std::vector<T> vf/*(1, Foo{})*/;
  vf.reserve(2);
  vf.push_back(T{});
  vf.push_back(T{});
  std::cout << "- Reserve\n";
  vf.reserve(10);
}

int main(int, char**) {
  test_vector_of<Foo>();
  test_vector_of<FooNE>();
};
