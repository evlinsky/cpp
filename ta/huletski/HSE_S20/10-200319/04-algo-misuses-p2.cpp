#include <numeric>
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <list>
#include <iterator>
#include <cassert>
#include <chrono>
#include <random>

void test_accum() {
  auto vi = std::vector{1, 2, 3, 4};
  std::cout << std::accumulate(vi.begin(), vi.end(), 0) << std::endl;

  auto vs = std::vector<std::string>{"a", "b", "c"};
  // std::cout << std::accumulate(vs.begin(), vs.end(), "my_") << std::endl;
  // std::cout << std::accumulate(vs.begin(), vs.end(), std::string("my_"))
  //           << std::endl;
}

//------------------------------------------------------------------------------

void test_unique() {
  auto li = std::list<int>{};

  std::mt19937 gen{std::random_device{}()};
  std::uniform_int_distribution<> elem_source{0, 100};
  for (int i = 0; i < 3000000; i++) {
    li.push_front(elem_source(gen));
  }

  auto gen_li = li;
  auto gen_start = std::chrono::high_resolution_clock::now();
  gen_li.erase(std::unique(gen_li.begin(), gen_li.end()), gen_li.end());
  auto gen_end = std::chrono::high_resolution_clock::now();

  auto spc_li = li;
  auto spc_start = std::chrono::high_resolution_clock::now();
  spc_li.unique();
  auto spc_end = std::chrono::high_resolution_clock::now();

  assert(std::equal(gen_li.begin(), gen_li.end(),
                    spc_li.begin(), spc_li.end()));

  using std::chrono::duration_cast;
  using std::chrono::milliseconds;
  std::cout << "std::unique       - "
            << duration_cast<milliseconds>(gen_end - gen_start).count()
            << " ms\n";
  std::cout << "std::list::unique - "
            << duration_cast<milliseconds>(spc_end - spc_start).count()
            << " ms\n";
}

int main(int, char**) {
  // a. implicit conversions
  // test_accum();
  // b. generic vs container-specific
  // test_unique();
}
