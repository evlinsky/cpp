#include <stdexcept>
#include <iostream>

void foo() noexcept/*(true)*/ {}
void bar() { throw 1; }
void baz() noexcept(false) { throw 1; }

void violate() noexcept { throw 1; }

int main(int, char**) {
  std::cout << noexcept(foo()) << " "
            << noexcept(bar()) << " "
            << noexcept(baz()) << std::endl;
  violate();
}
