#include <cstdint>
#include <utility>
#include <cstring>
#include <iostream>
#include <cassert>

class CharBuff {
public:
  CharBuff() : data_sz_(0), data_(nullptr) {}
  CharBuff(const char *s)
    : data_sz_(std::strlen(s) + 1)
    , data_(new char[data_sz_]) {
    std::strncpy(data_, s, data_sz_);
  }

  CharBuff(const CharBuff &that) : CharBuff(that.data_) {}

  CharBuff(CharBuff &&that) noexcept/*(noexcept(swap(that)))*/
    : CharBuff() {
    swap(that);
  }

  ~CharBuff() {
    delete [] data_;
  }

  CharBuff& operator=(const CharBuff &that) {
    CharBuff(that).swap(*this);
    return *this;
  }

  CharBuff& operator=(CharBuff &&that) noexcept {
    // clean up & reset state(opt)
    delete [] data_;
    data_ = nullptr;   //std::exchange(that.data_, nullptr);
    data_sz_ = 0;      //std::exchange(that.data_sz_, 0);
    // steal resources
    swap(that);
    return *this;
  }

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

int main(int, char**) {
  smoke_test_cb();
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
    cb1 = cb2;
    assert(strcmp(cb1.data(), "bar") == 0);
    assert(strcmp(cb2.data(), "bar") == 0);
  }
  { // greater sz
    CharBuff cb1("foo"), cb2("foobar");
    cb1 = cb2;
    // NB: cb1_buf can't be dereferenced
    assert(strcmp(cb1.data(), "foobar") == 0);
    assert(strcmp(cb2.data(), "foobar") == 0);
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
