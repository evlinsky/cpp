#include <cstdio>
#include <cassert>

#include "intset.h"

void test_p1() {
  // { // []
  //   IntSet a(100);
  //   a << 6;
  //   assert(a[6]);
  //   assert(!a[2]);
  // }
  // { // <=
  //   IntSet a(100), b(100);
  //   a << 6;
  //   b << 2 << 6 << 5;
  //   assert(a <= b);
  //   assert(!(b <= a));
  // }
  // { // ==
  //   IntSet a(100), b(100), c(100);
  //   a << 6 << 5 << 7;
  //   b << 2 << 6 << 5;
  //   c << 6 << 5 << 2;
  //   assert(b == c);
  //   assert(!(b == a));
  // }

  // { // copy ctor
  //   IntSet a(100);
  //   a << 1 << 2 << 5 << 8;
  //   IntSet b = a;
  //   assert(a == b);
  //   assert(b == (IntSet(10) << 2 << 8 << 5 << 1));
  // }
  // { // op=
  //   IntSet a(100);
  //   a << 1 << 8 << 13;
  //   IntSet b(23);
  //   b = a;
  //   assert(a == b);
  //   assert(b == (IntSet(10) << 1 << 8 << 13));
  // }
  // std::puts("test_p1 ... OK");
}

void test_p2() {
  // { // &=
  //   IntSet a(10), b(10);
  //   a << 1 << 6 << 32;
  //   b << 6 << 7 << 42 << 1 << 0;
  //   a &= b;
  //   assert(a == (IntSet(10) << 1 << 6));
  // }
  // { // &
  //   IntSet a(10), b(10);
  //   a << 1 << 6 << 32 << 72 << 4;
  //   b << 7 << 42 << 10 << 0;
  //   assert((a & b) == IntSet(10));
  // }
  // { // |=
  //   IntSet a(10), b(10);
  //   a << 1 << 6 << 32;
  //   b << 6 << 7 << 42 << 1 << 0;
  //   a |= b;
  //   assert(a == (IntSet(10) << 1 << 6 << 32 << 7 << 1 << 42 << 0));
  // }
  // { // |
  //   IntSet a(10), b(10);
  //   a << 1 << 6 << 32;
  //   b << 6 << 1 << 0;
  //   assert((a | b) == (IntSet(10) << 1 << 6 << 32 << 1 << 0));
  // }

  // std::puts("test_p2 ... OK");
}

// bool is_even(int e) { return (e & 1) == 0; }
// void drop_odds(IntSet &is) {
//   is = is(is_even);
// }

void test_p3() {
  // { // op((*)) const
  //   IntSet a(10);
  //   a << 1 << 3 << 42 << 0 << 31;
  //   const IntSet &c_aref = a;
  //   assert(c_aref(is_even) == (IntSet(10) << 42 << 0));
  //   assert(a == (IntSet(10) << 42 << 0 << 1 << 3 << 31));
  // }
  // { // << (*)
  //   IntSet a(10);
  //   a << 1 << 3 << 42 << drop_odds << 0 << 31;
  //   assert(a == (IntSet(10) << 42 << 31 << 0));
  // }
  // std::puts("test_p3 ... OK");
}

void test_p4() {
  // { // <
  //   IntSet a(10), b(10);
  //   a << 1 << 3 << 5;
  //   b << 3 << 5;
  //   assert(b < a);
  //   assert(!((b << 1) < a));
  // }
  // { // >
  //   IntSet a(10), b(10);
  //   a << 1 << 3 << 5;
  //   b << 3 << 5;
  //   assert(a > b);
  //   assert(!(a > (b << 1)));
  // }
  // { // >=
  //   IntSet a(10), b(10);
  //   a << 1 << 3 << 5;
  //   b << 3 << 5;
  //   assert(a >= b);
  //   assert(a >= (b << 1));
  // }
  // { // !=
  //   IntSet a(10), b(10);
  //   a << 1 << 3 << 5;
  //   b << 3 << 5;
  //   assert(a != b);
  // }
  // std::puts("test_p4 ... OK");
}

void test_p5() {
  // { // << Range
  //   IntSet a(10);
  //   a << 236 << Range(-2, 1) << drop_odds;
  //   assert(a == (IntSet(10) << 236 << -2 << 0));
  // }
  // std::puts("test_p5 ... OK");
}

int main(int, char**) {
  test_p1();
  test_p2();
  test_p3();
  test_p4();
  test_p5();
}
