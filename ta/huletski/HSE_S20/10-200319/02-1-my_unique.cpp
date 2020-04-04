#include <algorithm>
#include <iterator>
#include <vector>
#include <cassert>
#include <iostream>

template <typename Itr>
Itr my_unique(Itr b, Itr e) {
  if (b == e) { return e; }
  // Goal:
  //   split into two parts: unque-ok elems (left),
  //                         whatever-value elems (right);
  // The right part holds to-be-removed, redundant 'storage cells'.
  //
  // [b ..................................................................... e)
  // [ <unique-ok elems> ][ <junk elems (any val)> ][    <unexamined elems>    )
  // = Init state
  // [     last_unique_ok]<       no junk so far   >[unique_ok_end/cursor ... e]
  // = Midle state
  // [ ... last_unique_ok][              ...       ][cursor             ...   e)
  // = Done state (no unexamined left)
  // [ ... last_unique_ok][ <to-be-removed storage cells               cursor/e)

  auto last_unique_ok = b;
  for (auto cursor = last_unique_ok; cursor != e; cursor++) {
    if (*cursor == *last_unique_ok) {
      continue; // extend 'junk elems'
    }
    *(++last_unique_ok) = *cursor; // extend 'unique-ok elems'
  }
  return ++last_unique_ok;
}

std::ostream& operator<<(std::ostream &os, const std::vector<int> &vi) {
  std::copy(vi.cbegin(), vi.cend(),
            std::ostream_iterator<int>(os, " "));
  return os;
}

void test_unique(const std::vector<int> &vi) {
  std::cout << "Test [" << vi << "] ... ";
  std::cout.flush();
  auto uni_vi = vi;
  uni_vi.erase(std::unique(uni_vi.begin(), uni_vi.end()), uni_vi.end());

  auto my_uni_vi = vi;
  my_uni_vi.erase(my_unique(my_uni_vi.begin(), my_uni_vi.end()),
                  my_uni_vi.end());

  assert(std::equal(uni_vi.begin(), uni_vi.end(),
                    my_uni_vi.begin(), my_uni_vi.end()));
  std::cout << "ok\n";
}

int main(int, char**) {
  test_unique({});
  test_unique({1});
  test_unique({1, 1, 1, 1});
  test_unique({1, 2, 3});
  test_unique({1, 1, 2, 3});
  test_unique({1, 2, 2, 2, 3});
  test_unique({1, 2, 3, 3, 3, 3});
  test_unique({1, 1, 1, 2, 2, 2, 3, 3, 3});
}
