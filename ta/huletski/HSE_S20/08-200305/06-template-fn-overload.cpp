#include <iostream>

void foo(int) { std::cout << "int\n"; }

template <typename T>
void foo(T a) { std::cout << "T\n"; }

template <typename T>
void foo(T* a) { std::cout << "T*\n"; }

int main(int, char**) {
  foo(1);
  foo(1.0);
  foo(nullptr);
  foo(static_cast<int*>(nullptr));
}
