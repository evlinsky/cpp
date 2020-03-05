#include <vector>
#include <cassert>
#include <iostream>

template <typename T>
void examine_first(/*const*/ std::vector<T> &v) {
  assert(!v.empty());
  std::cout << "v[0] = " << v[0] << std::endl;;
  auto value = v[0];
  //typename std::vector<T>::value_type value = v[0];
  value = T{};
}

template <typename T>
void print_all(const std::vector<T> &v) {
  //for (auto&& e : v) {
  for (auto& e : v) {
    std::cout << e << " ";
  }
  std::cout << std::endl;
}

int main(int, char**) {
  // a. Assign to return value
  // std::cout << "== int ==\n";
  // auto vi = std::vector<int>{1, 2, 3};
  // examine_first(vi);
  // examine_first(vi);
  // std::cout << "== bool ==\n";
  // auto vb = std::vector<bool>{true, true, false};
  // examine_first(vb);
  // examine_first(vb);

  // b. Print all
  // std::cout << "== int ==\n";
  // print_all(std::vector<int>{1, 2, 3});
  // std::cout << "== bool ==\n";
  // print_all(std::vector<bool>{true, true, false});
}
