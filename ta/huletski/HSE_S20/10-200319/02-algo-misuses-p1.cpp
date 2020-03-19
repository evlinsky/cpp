#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>
#include <cassert>

void print_vector(const std::vector<int> &vi) {
  std::copy(std::begin(vi), std::end(vi),
            std::ostream_iterator<int>(std::cout, ", "));
  std::cout << std::endl;
}

void erase_remove() {
  auto vi = std::vector{2, 1, 2, 2, 31, 2, 4, 7, 5, 2, 6};
  // a.
  std::cout << "Pre remove:\n";
  print_vector(vi);
  auto new_end = std::remove(std::begin(vi), std::end(vi), 2);
  std::cout << "After remove:\n";
  print_vector(vi);
  vi.erase(new_end, std::end(vi));
  std::cout << "After erase:\n";
  print_vector(vi);

  // b.
  // print_vector(vi);
  // vi.erase(std::remove_if(vi.begin(), vi.end(), [](int i) { return i % 2; }),
  //          vi.end());
  // std::cout << "Drop odd:\n";
  // print_vector(vi);
}

void erase_unique() {
  auto vi = std::vector{2, 1, 1, 2, 2, 31, 2, 4, 4, 4, 5, 6};
  print_vector(vi);
  std::cout << "Unique:\n";
  vi.erase(std::unique(vi.begin(), vi.end()), vi.end());
  print_vector(vi);
}

//------------------------------------------------------------------------------

void init_vector() {
  auto vi = std::vector<int>(5, 2);
  print_vector(vi);
  // *it = e -> vi.push_bakc(e);
  std::fill_n(vi.end(),
              //std::back_inserter(vi),
              //vi.begin(),
              5 /* cnt */, 42 /* value */);
  print_vector(vi);
}

//------------------------------------------------------------------------------

void compare() {
  auto vi1237 = std::vector<int>{1, 2, 3, 7},
       vi1242 = std::vector<int>{1, 2, 4, 2},
         vi12 = std::vector<int>{1, 2};
  assert( std::equal(vi1237.begin(), vi1237.end(), vi1237.begin()));
  assert(!std::equal(vi1237.begin(), vi1237.end(), vi1242.begin()));
  // assert( std::equal(vi12.begin()  ,   vi12.end(), vi1237.begin()));
  // assert(!std::equal(vi1237.begin(), vi1237.end(), vi12.begin()));

  // assert(!std::equal(vi12.begin()  ,   vi12.end(),
  //                    vi1237.begin(), vi1237.end()));
  // assert(!std::equal(vi1237.begin(), vi1237.end(),
  //                    vi12.begin()  ,   vi12.end()));
}

int main(int, char**) {
  // a. drop elements
  // erase_remove();
  // erase_unique();
  // b. add elements
  // init_vector();
  // c. compare
  // compare();
}
