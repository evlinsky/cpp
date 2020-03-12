#include <iostream>
#include <vector>
#include <cstdint>
#include <iterator>
#include <utility>

void print_reversed() {
  auto v = std::vector<int>{1, 2, 3, 4, 5};
  // std::copy(v.rbegin(), v.rend(),
  std::copy(std::rbegin(v), std::rend(v),
            std::ostream_iterator<int>(std::cout, "<-"));
  std::cout << std::endl;
}

//------------------------------------------------------------------------------

void print_ptrs() {
  std::vector<int16_t> vi{1, 2, 3};
  std::cout << "= Elems:\n";
  std::cout << "[" << &*vi.begin() << ", " << &*vi.end() << ")\n";
  std::cout << "= Reversed elems:\n";
  std::cout << "(" << &*vi.rend() << ", " << &*vi.rbegin() << "]\n";

  std::cout << "= Reversed Base elems:\n"; // stores an iterator to the next e
  std::cout << "(" << &*vi.rend().base() << ", "
            << &*vi.rbegin().base() << "]\n";
}

void reverse_onion() {
  auto vi = std::vector<int>{1, 2, 3, 4, 5};
  auto it = vi.begin() + 2;
  auto r_it = std::make_reverse_iterator(it);
  auto rr_it = std::make_reverse_iterator(r_it);
  std::cout << "it: " << *it << "; rev(it): " << *r_it
            << "; rev(rev(it)): " << *rr_it << std::endl;
}

void show_internals() {
  std::cout << "=== Print Pointers\n";
  print_ptrs();
  std::cout << "=== Reverse Onion\n";
  reverse_onion();
}

//------------------------------------------------------------------------------

template <typename C>
struct Reversed {
  explicit Reversed(C c) : c_(std::move(c)) {}

  using iterator = typename C::reverse_iterator;
  iterator begin() { return std::rbegin(c_); }
  iterator end() { return std::rend(c_); }
private:
  C c_;
};

// template deduction guide example
template <typename C>
explicit Reversed(C c) -> Reversed<C>;

//------------------------------------------------------------------------------

int main(int, char**) {
  // = a. usage example
  // print_reversed();
  // = b. internals
  // show_internals();
  // = c.
  // for (auto &e : Reversed(std::vector<int>{1, 2, 3, 4})) {
  //   std::cout << e << " ";
  // }
  // std::cout << std::endl;
}
