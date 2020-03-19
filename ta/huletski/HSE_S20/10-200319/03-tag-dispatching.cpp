#include <iterator>
#include <iostream>
#include <vector>
#include <list>
#include <forward_list>

template <typename Itr>
auto my_prev_tagged(Itr it, int n, std::random_access_iterator_tag) {
  return it - n;
}

template <typename Itr>
auto my_prev_tagged(Itr it, int n, std::bidirectional_iterator_tag) {
  while (n--) {
    it--;
  }
  return it;
}

template <typename Itr>
auto my_prev(Itr it, int n) {
  // return it - n;                   // ?
  // while (n--) { it--; } return it; // ?
  using category_t = typename std::iterator_traits<Itr>::iterator_category;
  // using category_t = Itr::iterator_category;
  return my_prev_tagged(it, n, category_t());
}

void tag_dispatching_test() {
  auto vi = std::vector{1, 2, 3, 4};
  std::cout << *my_prev(vi.end(), 2) << std::endl;

  auto li = std::list{1, 2, 3, 4};
  std::cout << *my_prev(li.end(), 2) << std::endl;

  // a.
  // b. comment RA category
  // c. try fwd category
  // auto fli = std::forward_list{1, 2, 3, 4};
  // std::cout << *my_prev(fli.end(), 2) << std::endl;
}

//------------------------------------------------------------------------------

// since C++17

template <typename Itr>
auto my_prev_cei(Itr it, int n) {
  using ra_tag = std::random_access_iterator_tag;
  using bd_tag = std::bidirectional_iterator_tag;

  using category_t = typename std::iterator_traits<Itr>::iterator_category;
  if constexpr (std::is_base_of_v<ra_tag, category_t>) {
    return it - n;
  } else if constexpr (std::is_base_of_v<bd_tag, category_t>) {
    while (n--) { it--; }
    return it;
  } else {
    static_assert(std::is_base_of_v<bd_tag, category_t>,
                  "Category must be at least BI");
  }
}

void constexpr_if_test() {
  auto vi = std::vector{1, 2, 3, 4};
  std::cout << *my_prev_cei(vi.end(), 2) << std::endl;

  auto li = std::list{1, 2, 3, 4};
  std::cout << *my_prev_cei(li.end(), 2) << std::endl;

  // a. try fwd category
  // auto fli = std::forward_list{1, 2, 3, 4};
  // std::cout << *my_prev_cei(fli.end(), 2) << std::endl;
}


int main(int, char**) {
  // = a.
  // tag_dispatching_test();
  // = b.
  // constexpr_if_test();
}
