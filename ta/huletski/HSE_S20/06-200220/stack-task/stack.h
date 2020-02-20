#ifndef STACK_H_PRE_LAB_12
#define STACK_H_PRE_LAB_12

#include <cstdint>
#include <utility>
#include <iostream>
#include <cassert>

// Responsibility: FILO policy implementation
template <typename T>
class Stack {
public:
  Stack();
  Stack(const Stack&);
  Stack& operator=(Stack);
  ~Stack();

  std::size_t size() const { return elems_.nm(); }
  bool empty() const { return size() == 0; }
  void reserve(std::size_t new_cap);
  void push(const T&);
  void pop();
  T top() const;
  
  friend std::ostream& operator<<(std::ostream &os, const Stack &s) {
    for (std::size_t i = 0; i < s.elems_.nm(); i++) {
      os << s.elems_.data()[i] << ";"[i == 1];
    }
    return os;
  }
private:
  static constexpr std::size_t Dflt_Cap = 2;
private:
  // Resposibility: RAII-wrapper for a dynamic array
  class ElemsStorage {
  public:
    ElemsStorage(std::size_t cap);
    ~ElemsStorage();
    
    ElemsStorage(const ElemsStorage &) = delete;
    ElemsStorage& operator=(const ElemsStorage &) = delete;

    T* data() const { return data_; }
    std::size_t nm() const { return nm_; }
    std::size_t capacity() const { return cap_; }
    T* last() const {
      assert(nm());
      return data() + nm() - 1;
    };
    
    void swap(ElemsStorage &other);
    void destroy(T* beg, std::size_t nm);
    void copy(T* out_beg, const T* in_beg, std::size_t in_nm);
    void append(const T* in_beg, std::size_t in_nm) {
      return copy(data() + nm(), in_beg, in_nm);
    }
    bool is_full() const { return cap_ == nm_; }
  private:
    std::size_t cap_, nm_;
    T *data_;
  };
private:
  ElemsStorage elems_;
};

//------------------------------------------------------------------------------
// ElemsStorage implementation

template<typename T>
Stack<T>::ElemsStorage::ElemsStorage(std::size_t cap) {
  // TODO:
}

template<typename T>
void Stack<T>::ElemsStorage::destroy(T* beg, std::size_t nm) {
  // TODO:
}

template<typename T>
void Stack<T>::ElemsStorage::copy(T* out_beg,
                                  const T* in_beg, std::size_t in_nm) {
  // TODO:
}

template<typename T>
void Stack<T>::ElemsStorage::swap(ElemsStorage &other) {
  // TODO:
}

template<typename T>
Stack<T>::ElemsStorage::~ElemsStorage() {
  // TODO:
}

//------------------------------------------------------------------------------
// Stack implementation

template<typename T>
Stack<T>::Stack() {
  // TODO:
}

template<typename T>
Stack<T>::~Stack() {
  // TODO:
}

template<typename T>
Stack<T>::Stack(const Stack &s) {
  // TODO:
}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack s) {
  // TODO:
}

template<typename T>
void Stack<T>::reserve(std::size_t new_cap) {
  // TODO:
}

template<typename T>
void Stack<T>::push(const T &e) {
  // TODO:
}

template<typename T>
void Stack<T>::pop() {
  // TODO:
}

template<typename T>
T Stack<T>::top() const {
  // TODO:
}

#endif // STACK_H_PRE_LAB_12 
