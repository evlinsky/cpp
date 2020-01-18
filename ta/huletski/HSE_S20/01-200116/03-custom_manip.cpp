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

std::istream& skip_asterisks_alt(std::istream &is) {
  // also skips ws, uses >>
  while (1) {
    char next_char;
    is >> next_char;
    if (!is || next_char != '*') {
      is.unget(); // implicit no-op if !is.good()
      break;
    }
  }
  return is;
}

void run_custom_function_manip() {
  std::cout << "== run_custom_function_manip ==" << std::endl;
  {
    std::istringstream iss("***42 22");
    int i, j;
    iss >> skip_asterisks >> i >> j;
    std::cout << i << " " << j << std::endl;
  }
  {
    std::istringstream iss(" ** 1 ****  4 ");
    int i, j;
    iss >> skip_asterisks_alt >> i >> skip_asterisks_alt >> j
        >> skip_asterisks_alt;
    std::cout << i << " " << j << std::endl;
  }
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
    std::size_t cnt = _cnt;
    while (cnt) {
      int i;
      if (!(is >> i)) { break; }
      _dst.push_back(i);
      --cnt;
    }
    return is;
  }
private:
  std::vector<int> &_dst;
  std::size_t _cnt;
};

// NB: 'const' for temp values handling. Fwd fix: use rvalue refs
std::istream& operator>>(std::istream &is, const as_int_vector &aiv) {
  return aiv(is);
}

void run_custor_functor_manip() {
  std::cout << "== run_custor_functor_manip ==" << std::endl;
  {
    std::istringstream iss("1 2 3 4 5 6 7 8");
    std::vector<int> vi;
    iss >> as_int_vector(vi, 4);
    for (const int &i : vi) {
      std::cout << i << " ";
    }
    std::cout << std::endl;
  }
  {
    std::istringstream iss("1 2 3 *** 4 5 6 7 8");
    std::vector<int> vi;
    as_int_vector read_3_ints(vi, 3);
    iss >> read_3_ints >> skip_asterisks_alt >> read_3_ints;
    for (const int &i : vi) {
      std::cout << i << " ";
    }
    std::cout << std::endl;
  }
}

int main(int, char **) {
  run_custom_function_manip();
  run_custor_functor_manip();
}
