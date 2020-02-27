#include <cstdint>
#include <utility>
#include <cstring>
#include <iostream>
#include <cassert>

//#define USE_COMMON_ASSIGN_IMPL
#define USE_BUF_OPTIMIZATION

#ifdef USE_COMMON_ASSIGN_IMPL
  #undef USE_BUF_OPTIMIZATION
#endif

class CharBuff {
public:
  inline static bool print_debug = false; // C++17
public:
  CharBuff() : data_sz_(0), data_(nullptr) {}
  CharBuff(const char *s)
    : data_sz_(std::strlen(s) + 1)
    , data_(new char[data_sz_]) {
    std::strncpy(data_, s, data_sz_);
  }

  CharBuff(const CharBuff &that) : CharBuff(that.data_) {
    if (print_debug) {
      std::cout << "[CB &]\n";
    }
  }

  CharBuff(CharBuff &&that) noexcept/*(noexcept(swap(that)))*/
    : CharBuff() {
    if (print_debug) {
      std::cout << "[CB &&]\n";
    }
    swap(that);
  }

  ~CharBuff() {
    if (print_debug) {
      std::cout << "~CB: delete [] " << static_cast<void*>(data_) << "\n";
    }
    delete [] data_;
  }

#ifdef USE_COMMON_ASSIGN_IMPL
  CharBuff& operator=(CharBuff that) {
    if (print_debug) { std::cout << "[op=]\n"; }
    that.swap(*this);
    return *this;
  }
#else
  CharBuff& operator=(const CharBuff &that) {
    if (print_debug) { std::cout << "[op= const &]\n"; }
    if (this == &that) { return *this; }
  #ifdef USE_BUF_OPTIMIZATION
    if (that.data_sz_ <= data_sz_) {
      std::strncpy(data_, that.data_, std::strlen(that.data_) + 1);
      return *this;
    }
  #endif
    CharBuff(that).swap(*this);
    return *this;
  }

  CharBuff& operator=(CharBuff &&that) noexcept {
    if (print_debug) { std::cout << "[op= &&]\n"; }
    if (print_debug) {
      std::cout << "op=(&&): delete [] " << (void*)data_ << "\n";
    }
    // clean up & reset state(opt)
    delete [] data_;
    data_ = nullptr;   //std::exchange(that.data_, nullptr);
    data_sz_ = 0;      //std::exchange(that.data_sz_, 0);
    // steal resources
    swap(that);
    return *this;
  }
#endif  // USE_COMMON_ASSIGN_IMPL

  const char *data() const { return data_; }
private:
  void swap(CharBuff &that) {
    using std::swap;
    swap(data_, that.data_);
    swap(data_sz_, that.data_sz_);
  }
private:
  std::size_t data_sz_;
  char *data_;
};

void smoke_test_cb();

void cb_assign() {
  CharBuff::print_debug = true;
  CharBuff cb1("foo"), cb2("baz");
  std::cout << "== COPY Assign\n";
  cb1 = cb2;
  std::cout << "== Move Assign\n";
  cb1 = std::move(cb2);
  std::cout << "== Done\n";
}

void print_run_mode() {
  std::cout << "<MODE: ";
#ifdef USE_COMMON_ASSIGN_IMPL
  std::cout << "common op= >\n";
#ifdef USE_BUF_OPTIMIZATION
  static_assert(false);
#endif // USE_BUF_OPTIMIZATION
#else
  std::cout << "op=&& + op=& (buf_opt:";
  bool opt_enabled = false;
#ifdef USE_BUF_OPTIMIZATION
  opt_enabled = true;
#endif // USE_BUF_OPTIMIZATION
  std::cout << (opt_enabled ? "+" : "-") << ")>\n";
#endif // USE_COMMON_ASSIGN_IMPL
}

int main(int, char**) {
  print_run_mode();
  //smoke_test_cb();
  cb_assign();
}

void smoke_test_cb() {
  // ctor
  { // const char*
    CharBuff cb1("foo");
    assert(strcmp(cb1.data(), "foo") == 0);
  }
  std::cout << "smoke ctor: PASSED\n";
  // cp ctor
  {
    CharBuff cb1("foo"), cb2 = cb1;
    assert(strcmp(cb1.data(), "foo") == 0);
    assert(strcmp(cb2.data(), "foo") == 0);
  }
  std::cout << "smoke cp ctor: PASSED\n";
  // mv ctor
  {
    CharBuff cb1("foo"), cb2 = std::move(cb1);
    assert(cb1.data() == nullptr);
    assert(strcmp(cb2.data(), "foo") == 0);
  }
  std::cout << "smoke mv ctor: PASSED\n";
  // cp op=
  { // same sz
    CharBuff cb1("foo"), cb2("bar");
#ifdef USE_BUF_OPTIMIZATION
    const char *cb1_buf = cb1.data();
#endif
    cb1 = cb2;
    assert(strcmp(cb1.data(), "bar") == 0);
    assert(strcmp(cb2.data(), "bar") == 0);
#ifdef USE_BUF_OPTIMIZATION
    assert(cb1.data() == cb1_buf);
#endif
  }
  { // greater sz
    CharBuff cb1("foo"), cb2("foobar");
#ifdef USE_BUF_OPTIMIZATION
    const char *cb1_buf = cb1.data();
#endif
    cb1 = cb2;
    // NB: cb1_buf can't be dereferenced
    assert(strcmp(cb1.data(), "foobar") == 0);
    assert(strcmp(cb2.data(), "foobar") == 0);
#ifdef USE_BUF_OPTIMIZATION
    assert(cb1.data() != cb1_buf);
#endif
    assert(cb1.data() != cb2.data());
  }
  { // default
    CharBuff cb1, cb2("foo");
    cb1 = cb2;
    assert(strcmp(cb2.data(), "foo") == 0);
  }
  std::cout << "smoke cp op=: PASSED\n";
  // mv op=
  {
    CharBuff cb1("foo"), cb2("bar"), cb3("baz");
    cb1 = std::move(cb2); // mv
    assert(strcmp(cb1.data(), "bar") == 0);
    cb2 = cb3;
    assert(strcmp(cb2.data(), "baz") == 0);
  }
  std::cout << "smoke mv op=: PASSED\n";
  std::cout << "= all tests: PASSED\n";
}
