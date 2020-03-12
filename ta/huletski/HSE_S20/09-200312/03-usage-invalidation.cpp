#include <iostream>
#include <vector>

template <typename Container>
void print(const Container &c) {
  for (auto& e :  c) {
    std::cout << e << " ";
  }
  std::cout << std::endl;
}

void on_container_change() {
  std::vector<int> vi{1, 2, 3, 4, 5};
  auto it = vi.begin() + 3;
  std::cout << *it << std::endl;
  vi.resize(32); // insert, erase -> resize
  std::cout << *it << std::endl;
}

//---------------------------------------------------------------

void end_caching() {
  std::vector<int> vi{1, 2, 3, 4, 5};
  auto end = vi.end();
  vi.reserve(32);
  for (auto it = vi.begin(); it != end; it++) {
    std::cout << *it << std::endl;
  }
}

//---------------------------------------------------------------

int vi_push_back(std::vector<int> &vi, int value) {
  vi.push_back(value);
  return value + 1;
}

void return_n_assign() {
  std::vector<int> vi{1};
  vi[0] = vi_push_back(vi, 2);
  std::cout << vi[0] << std::endl;
}

//----------------------------------------------------------------

void drop_even() {
  std::vector<int> vi{1, 2, 3, 6, 5, 8, 13, 4};
  for (auto it = vi.begin(); it != vi.end(); it++) {
    if (*it % 2 != 0) {
      continue;
    }
    vi.erase(it);
  }
  print(vi);
}

void drop_even_() {
  std::vector<int> vi{1, 2, 3, 6, 5, 8, 13, 4};
  for (auto it = vi.begin(); it != vi.end();) {
    if (*it % 2 != 0) {
      it++;
      continue;
    }
    it = vi.erase(it);
  }
  print(vi);
}

//---------------------------------------------------------------

int main(int, char**) {
  // = a.
  // on_container_change();

  // = b. std::end(...) caching
  // end_caching();

  // = c. -std=c++11, -std=c++17
  // return_n_assign();

  // = d. container-changing loop
  // drop_even();
  // drop_even_();

  // = e.
  // stack::push_back(const T &e) {
  //   reserve(n+1);
  //   data[n] = e; // throws -> invalidation on reserve -> -strong exc.guar.
  //   n++;
  // }
}
