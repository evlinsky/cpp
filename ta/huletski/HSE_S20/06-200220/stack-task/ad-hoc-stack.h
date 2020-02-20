#ifndef AH_STACK_H_PRE_LAB_12
#define AH_STACK_H_PRE_LAB_12

#include <ostream>
#include <cstdint>
#include <cassert>

// Ad-hoc error prone implementation

template <typename T>
class Stack {
public:
  Stack();
  Stack/*<T>*/& operator=(const Stack&);
  ~Stack();

  std::size_t size() { return nm_; } // NB: consts
  bool empty() { return size() == 0; } // NB: size
  void reserve(std::size_t new_cap);
  void push(const T&);
  T pop();

  friend std::ostream& operator<<(std::ostream &os, const Stack &s) {
    for (std::size_t i = s.nm_; i != 0; i--) {
      os << s.data_[i - 1] << ";"[i == 1];
    }
    return os;
  }
private:
  static constexpr std::size_t Dflt_Cap = 2;
private:
  std::size_t nm_, cap_;
  T *data_;
};

template <typename T>
Stack<T>::Stack() : nm_(0), cap_(Dflt_Cap)
                  , data_(new T[cap_]) {} // on throw?

template <typename T>
Stack<T>::~Stack() {
  delete [] data_; // on throw?
}

template <typename T>
// NB: template arg in ret. type
Stack<T>& Stack<T>::operator=(const Stack& other) {
  delete [] data_; // drop junk ASAP

  cap_ = other.cap_;
  T* tmp_data = new T[other.cap_]; // on throw?
  nm_ = other.nm_;

  for (std::size_t i = 0; i < other.nm_; i++) {
    tmp_data[i] = other.data_[i]; // on throw?
  }
  /* Alternatives?
  a)
  for (auto &e : other.data_) {
    data_[i] = e; // op=
  }
  b) std::memcpy(data_, other.data_, sizeof(*data_) * other.nm_);
  */

  data_ = tmp_data;
  return *this;
}

template <typename T>
void Stack<T>::reserve(std::size_t new_cap) {
  if (new_cap <= cap_) { return; }
  cap_ = new_cap;
  T* expanded_storage = new T[cap_]; // on throw?
  for (std::size_t i = 0; i < nm_; i++) {
    expanded_storage[i] = data_[i];
  }
  delete [] data_;
  data_ = expanded_storage;
}

template <typename T>
void Stack<T>::push(const T& e) {
  if (nm_ == cap_) {
    reserve(cap_ * 2);
  }
  data_[nm_++] = e; // on throw?
}

template <typename T>
T Stack<T>::pop() {
  assert(!empty());
  return data_[--nm_]; // on throw?
}

#endif // AH_STACK_H_PRE_LAB_12
