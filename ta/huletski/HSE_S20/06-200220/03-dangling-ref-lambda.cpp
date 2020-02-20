#include <iostream>

auto foo() {
  int i = 0;
  return [&i]{ return i + 1; };
}

int main(int, char**) {
  std::cout << foo()() << std::endl;
}
