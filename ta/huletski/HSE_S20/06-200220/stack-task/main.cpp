//#include "stack.h"
#include "ad-hoc-stack.h"
#include <cassert>
#include <sstream>
#include <utility>
#include <new>
#include <exception>
#include <iostream>

struct AssignException : std::exception {};
struct CopyException : std::exception {};

struct IntWrapper {
  static std::size_t copy_ticks;
  static std::size_t assign_ticks;
  static int ctor_ticks;
  static bool throw_on_alloc;

  static void reset(std::size_t copy = 100,
                    std::size_t assign = 100,
                    int ctor = 0) {
    copy_ticks = copy;
    assign_ticks = assign;
    ctor_ticks = ctor;
    throw_on_alloc = false;
  }

  IntWrapper() : IntWrapper(ctor_ticks++) {}
  IntWrapper(int v)
    : managed_resource_(new int(v)) {}
  IntWrapper(const IntWrapper &iw)
    : managed_resource_(nullptr) {
    if (copy_ticks == 0) { throw CopyException(); }
    copy_ticks--;
    managed_resource_ = new int(*iw.managed_resource_);
  }
  IntWrapper& operator=(IntWrapper iw) {
    copy_ticks++;
    if (assign_ticks == 0) { throw AssignException(); }
    assign_ticks--;
    std::swap(iw.managed_resource_, managed_resource_);
    return *this;
  }
  ~IntWrapper() { delete managed_resource_; }

  void *operator new[] (std::size_t count) {
    if (throw_on_alloc) { throw std::bad_alloc(); }
    return ::operator new[](count);
  }

  operator int() {
    assert(managed_resource_);
    return *managed_resource_;
  }

  friend std::ostream& operator<<(std::ostream &os, const IntWrapper& iw) {
    return os << *iw.managed_resource_;
  }
private:
  int *managed_resource_;
};

std::size_t IntWrapper::copy_ticks = 1000;
std::size_t IntWrapper::assign_ticks = 1000;
int IntWrapper::ctor_ticks = 0;
bool IntWrapper::throw_on_alloc = false;

//--------

template<typename T>
bool operator==(const Stack<T> &lhs, const Stack<T> &rhs) {
  std::ostringstream lss, rss;
  lss << lhs;
  rss << rhs;
  return lss.str() == rss.str();
}

//--------

void test_push_pop() {
  IntWrapper::reset();
  Stack<IntWrapper> s;
  for (int i = 1; i <= 20; i++) { s.push(i); }
  for (int i = 20; 0 < i; i--) {
#ifdef AH_STACK_H_PRE_LAB_12
    assert(i == s.pop());
#else
    assert(i == s.top());
    s.pop();
#endif
  }
  assert(s.empty());
}

void test_copy_ctor() {
  IntWrapper::reset();
  Stack<IntWrapper> s;
  s.push(0);
  Stack<IntWrapper> s_copy(s);
  assert(s == s_copy);
}

void test_assign_noexcept() noexcept {
  IntWrapper::reset();
  Stack<IntWrapper> s, s_copy;
  s.push(0);
  s_copy = s;
  assert(s == s_copy);
}

void test_reserve() {
  IntWrapper::reset();
  Stack<IntWrapper> s;
  s.reserve(100);
  IntWrapper::throw_on_alloc = true;
  try {
    for (int i = 1; i <= 20; i++) {
      s.push(i);
    }
  } catch (const std::bad_alloc &e) {
    assert(0 && "Unexpected alloc after reserve");
  }
}

void test_assign_bad_alloc() {
  IntWrapper::reset();
  Stack<IntWrapper> s, s_copy;
  s.push(0);
  IntWrapper::throw_on_alloc = true;
  try {
    s_copy = s;
    assert(s == s_copy);
  } catch (const std::bad_alloc &e) {}
}

void test_assign_throw_on_assign() {
  IntWrapper::reset();
  Stack<IntWrapper> s, s_copy;
  s.push(0);
#ifdef AH_STACK_H_PRE_LAB_12
  IntWrapper::reset(100/*copy*/, 0/*assign*/);
#else
  IntWrapper::reset(0/*copy*/, 100/*assign*/);
#endif
  bool exception_thrown = false;
  try {
    s_copy = s;
    assert(s == s_copy);
  } catch (const AssignException &ae) {
    exception_thrown = true;
  } catch (const CopyException &ce) {
    exception_thrown = true;
  }
  assert(exception_thrown);
}

void test_copy_except_on_elem_copy() {
  IntWrapper::reset();
  Stack<IntWrapper> s;
  s.push(0);
  IntWrapper::reset(0/*copy*/, 100/*assign*/);
  bool elem_copy_thrown = false;
  try {
    Stack<IntWrapper> s_copy(s);
    assert(s == s_copy);
  } catch (const CopyException &ce) {
    elem_copy_thrown = true;
  }
  assert(elem_copy_thrown);
}

void test_reserve_bad_alloc() {
  IntWrapper::reset(100, 100);
  Stack<IntWrapper> s;
  s.push(1);
  s.push(2);
  IntWrapper::throw_on_alloc = true;
  try {
    s.reserve(100);
  } catch (const std::bad_alloc &e) {}
  s.push(3);
}

void test_push_throw_on_assign() {
#ifdef AH_STACK_H_PRE_LAB_12
  IntWrapper::reset(100, 0 /*assign*/);
#else
  IntWrapper::reset(0 /*copy*/);
#endif
  Stack<IntWrapper> s;
  bool exception_thrown = false;
  try {
    s.push(1);
  } catch (const AssignException &ae) {
    exception_thrown = true;
  } catch (const CopyException &ce) {
    exception_thrown = true;
  }
  assert(exception_thrown);

  IntWrapper::reset();
#ifdef AH_STACK_H_PRE_LAB_12
  assert(s.empty() || s.pop() == 1);
#else
  assert(s.empty() || s.top() == 1);
#endif
}

void test_pop_copy_exception() {
  IntWrapper::reset();
  Stack<IntWrapper> s;
  s.push(1);
  IntWrapper::reset(0/*no copy*/);
  try {
    s.pop();
  } catch (const CopyException &ce) {
    assert(!s.empty());
  }
}

int main(int, char**) {
  test_push_pop();
  test_assign_noexcept();
  test_reserve();

  //test_assign_bad_alloc();
  //test_assign_throw_on_assign();
  //test_reserve_bad_alloc();
  //test_push_throw_on_assign();
  //test_pop_copy_exception();
#ifndef AH_STACK_H_PRE_LAB_12
  test_copy_except_on_elem_copy();
  test_copy_ctor();
#endif
  return 0;
}
