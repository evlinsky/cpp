#include <stdexcept>
#include <iostream>

int main(int, char**) {
  const long Too_Much_Ints = 1000000000;
  try {
    new int[Too_Much_Ints];
  } catch (const std::bad_alloc &e) {
    std::cout << "Bad alloc\n";
  }

  int *i = new (std::nothrow) int[Too_Much_Ints]; // use overloaded operator new
  std::cout << (i == nullptr ? "Unable to alloc" : "Ok") << std::endl;
  delete [] i;
}
