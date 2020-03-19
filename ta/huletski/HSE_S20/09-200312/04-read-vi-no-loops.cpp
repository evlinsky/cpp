#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

int main(int, char**) {
  std::vector<int> vi;
  // cin -> vector
  std::copy(std::istream_iterator<int>(std::cin),
            std::istream_iterator<int>(),
            // vi.begin());
            std::back_inserter(vi));

  // vector -> cout
  std::copy(vi.begin(), vi.end(),
            std::ostream_iterator<int>(std::cout, "->"));
  std::cout << std::endl;
}
