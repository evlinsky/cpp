#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <vector>

std::istream& skip_asterisks(std::istream &is) {
  while (is) {
    int next_char = is.peek();
    if (next_char == EOF || next_char != '*') { break; }
    is.get();
  }
  return is;
}

void run_custom_function_manip() {
  std::istringstream iss("***42 22");
  int i, j;
  iss >> skip_asterisks >> i >> j;
  std::cout << i << " " << j << std::endl;
}

//------------------------------------------------------------------------------
struct as_int_vector {
public:
  as_int_vector(std::vector<int> &dst, std::size_t cnt)
    : _dst(dst), _cnt(cnt) {
    dst.clear();
    dst.reserve(_cnt);
  }

  std::istream& operator()(std::istream &is) const {
    while (_cnt) {
      int i;
      if (!(is >> i)) { break; }
      _dst.push_back(i);
      --_cnt;
    }

    return is;
  }
private:
  std::vector<int> &_dst;
  mutable std::size_t _cnt;
};

// NB: 'const' for temp values handling. Fwd fix: use rvalue refs
std::istream& operator>>(std::istream &is, const as_int_vector &aiv) {
  return aiv(is);
}

void run_custor_functor_manip() {
  std::istringstream iss("1 2 3 4 5 6 7 8");
  std::vector<int> vi;
  iss >> as_int_vector(vi, 4);
  for (const int &i : vi) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}

int main(int, char **) {
  run_custom_function_manip();
  run_custor_functor_manip();
}
