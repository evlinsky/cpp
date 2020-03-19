#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <iterator>
#include <algorithm>

template <typename Container>
void print_generic_container(const Container &c) {
  for (auto& e :  c) {
    std::cout << e << " ";
  }
  std::cout << std::endl;
}

template <typename T>
void print_fst_via_ptr(const T &c) {
  auto fst_ptr = &*c.begin(); // iterator -> pointer to element
  // auto fst_ptr = &c.front();
  // auto fst_ptr = &c[0];
  // ...
  std::cout << *fst_ptr << std::endl;
}

//------------------------------------------------------------------------------

template <typename Iter>
decltype(auto) to_vector(Iter b, Iter e) {
  // auto v = std::vector<typename Iter::value_type>();
  auto v = std::vector<typename std::iterator_traits<Iter>::value_type>();
  while (b != e) {
    v.push_back(*b++);
  }
  return v;
}

void test_to_vector() {
  // std::vector<int> vi = {1, 2, 3};
  // print_generic_container(to_vector(vi.cbegin(), vi.cend()));

  // int arr[] = {1, 2, 3};
  // print_generic_container(to_vector(arr, arr + sizeof(arr) / sizeof(*arr)));
}

//------------------------------------------------------------------------------

template <typename Container>
void print(const Container &c) {
  // for (auto it = c.cbegin(); it != c.cend(); it++) {          // 1. ?
  for (auto it = std::cbegin(c); it != std::cend(c); it++) {
    // std::cout << *it << " \n"[it + 1 == std::cend(c)];        // 2. ?
    std::cout << *it << " \n"[std::next(it) == std::cend(c)];
  }
}

void test_print() {
  // print(std::vector<int>{1, 2, 3});
  // int arr[] = {1, 2, 3, 4};
  // print(arr);
  // print(std::list<int>{1, 2, 3});
  // print(std::set<int>{1, 2, 3});
}

//--------------------------------------

template <typename Container>
// void distance_wo_first(Container &c) {
void distance_wo_first(Container c) {                             // ?
  std::cout
    << std::distance(++std::begin(c), std::end(c))                // ?
    // << std::distance(std::next(std::begin(c)), std::end(c))
    << std::endl;
}

void test_distance_wo_first() {
  // auto vi = std::vector<int>{1, 2, 3};
  // distance_wo_first(vi);
  // auto ai = std::array<int, 3>{1, 2, 3};
  // distance_wo_first(ai);

  // int(&)[N] vs int[N] -> int*
  // int arr[] = {1, 2, 3, 4};
  // distance_wo_first(arr);
}

int main(int, char**) {
  // === std::vector<bool> recap
  // = 0.
  // print_generic_container(std::vector<int>{1, 2, 3, 4});
  // print_generic_container(std::vector<bool>{true, false, true});
  // = 1.
  // print_fst_via_ptr(std::vector<int>{1, 2, 3, 4});
  // print_fst_via_ptr(std::vector<bool>{true, false, true});
  // === Generic 'algorithm' implementation
  // = a.
  // test_print();
  // = b.
  // test_to_vector();
  // = c.
  // test_distance_wo_first();
  // = d. =c by value
}
