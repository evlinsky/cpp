#include <stdexcept>
#include <iostream>

//NB: fix me

void foo() {
  try {
    throw std::logic_error("");
  } catch (const std::exception &e) {
    std::cout << "foo. exception\n";
    throw e;
  }
}

int main(int, char**) {
  try {
    foo();
  } catch (const std::logic_error &e) {
    std::cout << "main. logic_error\n";
  } catch (const std::exception &e) {
    std::cout << "main. exception\n";
  }
}
