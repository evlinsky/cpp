#include <exception>
#include <iostream>

int main(int, char**) {
  using MyException = std::exception;
  try {
    throw MyException();
  } catch (const MyException& e) {
    std::cout << "ME: " << typeid(e).name() << std::endl;
  } catch (const std::exception& e) {
    std::cout << "STD: " << typeid(e).name() << std::endl;
  }
}
