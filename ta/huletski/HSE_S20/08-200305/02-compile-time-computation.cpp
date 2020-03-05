#include <iostream>
#include <utility>
#include <tuple>

//-----------------------------------------------------------------------------
// pre C++11 (no constexpr)

// recursive step, primary template
template <unsigned N>
struct Fibo {
  static const unsigned value = Fibo<N - 1>::value + Fibo<N - 2>::value;
};

// recursion bases, full specialization
template <>
struct Fibo<0> {
  static const unsigned value = 0;
};

template <>
struct Fibo<1> {
  static const unsigned value = 1;
};

// well, C++17
template <int N>
constexpr unsigned fibo_v = Fibo<N>::value;

//-----------------------------------------------------------------------------
// post C++11

constexpr unsigned fibo(unsigned n) {
  if (n == 0) { return 0; }
  unsigned prev = 0, curr = 1;
  while (--n) {
    // * std::exchange is not constexpr till C++20
    //curr = std::exchange(prev, curr) + curr;
    // * C++20, tuple::op= constexpr
    //std::tie(prev, curr) = std::make_tuple(curr, prev + curr);
    unsigned new_prev = curr;
    curr += prev;
    prev = new_prev;
  }
  return curr;
}

int main() {
  static_assert(Fibo<10>::value == 55);
  static_assert(fibo_v<10> == 55);
  static_assert(fibo(10) == 55);

  std::cout << Fibo<10>::value << std::endl;
  std::cout << fibo_v<10> << std::endl;
  std::cout << fibo(10) << std::endl;
}
