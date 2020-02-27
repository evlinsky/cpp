#include "uni_ptr.h"
#include <memory>
#include <utility>
#include <iostream>
#include <cassert>
#include <type_traits>

class Int {
public:
  explicit Int(int i = 0) : i_{new int{i}} {}
  ~Int() { delete i_; }
  Int(const Int& i) : Int{*i_} {}
  Int(Int &&i) : i_{std::exchange(i.i_, nullptr)} {}
  Int& operator=(Int i) & { // common op
    std::swap(i_, i.i_);
    return *this;
  }
  operator int () const {
    assert(i_);
    return *i_;
  }
  void stub() const { };
private:
  int *i_;
};

// ---- Tests

template <template <typename> typename PtrT>
void test_dflt_ctor() {
  static_assert(std::is_nothrow_default_constructible_v<PtrT<Int>>);
  PtrT<Int> pi;
  assert(pi.get() == nullptr);
  static_assert(!std::is_convertible_v<Int*, PtrT<Int>>);
}

template <template <typename> typename PtrT>
void test_get_is_const() {
  Int *raw_pi = new Int(42);
  const PtrT<Int> pi(raw_pi);
  assert(pi.get() == raw_pi);
}

template <template <typename> typename PtrT>
void test_ctor_move() {
  Int *raw_pi = new Int(42);
  PtrT<Int> pi1(raw_pi), pi2(std::move(pi1));

  assert(pi1.get() != raw_pi && pi2.get() == raw_pi);
  static_assert(std::is_nothrow_move_constructible_v<PtrT<Int>>);
}

template <template <typename> typename PtrT>
void test_assign_move() {
  Int *raw_pi2 = new Int(42);
  PtrT<Int> pi1(new Int(42)), pi2(raw_pi2);
  pi1 = std::move(pi2);
  assert(pi1.get() == raw_pi2 && pi2.get() != raw_pi2);
  static_assert(std::is_nothrow_move_assignable_v<PtrT<Int>>);
}

template <template <typename> typename PtrT>
void test_unable_to_copy() {
  static_assert(!std::is_copy_constructible_v<PtrT<Int>>);
  static_assert(!std::is_copy_assignable_v<PtrT<Int>>); 
}

template <template <typename> typename PtrT>
void test_release() {
  Int *raw_pi = new Int(42);
  PtrT<Int> pi(raw_pi);
  Int *released_pi = pi.release();
  assert(raw_pi == released_pi);
  assert(pi.get() == nullptr);
  delete raw_pi;
  static_assert(noexcept(pi.release()));
}

template <template <typename> typename PtrT>
void test_reset() {
  Int *raw_pi = new Int(42), *raw_pi_new = new Int(42);
  PtrT<Int> pi(raw_pi);
  pi.reset(raw_pi_new);
  assert(pi.get() == raw_pi_new);
}

template <template <typename> typename PtrT>
void test_access() {
  Int *raw_pi = new Int(42);
  PtrT<Int> pi(raw_pi), pi_empty;
  // init value
  assert(pi.get() == raw_pi && pi_empty.get() == nullptr);
  assert(*pi.get() == 42);

  pi->stub();
  (*pi).stub();
}

template <typename T>
class is_bool_safe {
  struct AlwaysTrue{ operator bool() const { return true; }};

  template<typename U, typename = bool>
  struct check : std::true_type {};

  template<typename U>
  struct check<U, decltype(AlwaysTrue() == U())> : std::false_type {};
  
public:
  inline static constexpr bool value = check<T>::value;
};

template <template <typename> typename PtrT>
void test_to_bool() {
  PtrT<Int> dflt_pi, zero_pi(new Int(0)), pi(new Int(42));
  assert(!dflt_pi && zero_pi && pi);

  static_assert(is_bool_safe<PtrT<Int>>::value);
}

template <template <typename> typename PtrT>
void test_uni_ptr() {
  test_dflt_ctor<PtrT>();
  test_get_is_const<PtrT>();
  test_ctor_move<PtrT>();
  test_assign_move<PtrT>();
  test_unable_to_copy<PtrT>();
  test_release<PtrT>();
  test_reset<PtrT>();
  test_access<PtrT>();
  test_to_bool<PtrT>();
}

template <typename T>
using std_uni_ptr = std::unique_ptr<T, std::default_delete<T>>;

int main(int, char**) {
  //test_uni_ptr<std_uni_ptr>();
  test_uni_ptr<uni_ptr>();
}
