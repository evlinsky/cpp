#ifndef LINQ_H_
#define LINQ_H_

#include <utility>
#include <vector>

namespace linq {
namespace impl {

template<typename T, typename Iter>
class range_enumerator;
template<typename T>
class drop_enumerator;
template<typename T, typename U, typename F>
class select_enumerator;
template<typename T, typename F>
class until_enumerator;

template<typename T>
class enumerator {
public:
  T operator*(); // Получает текущий элемент.
  ??? operator++();  // Переход к следующему элементу
  operator bool();  // Возвращает true, если есть текущий элемент

  auto drop(int count) {
  }

  template<typename U = T, typename F>
  auto select(F func) {
  }

  template<typename F>
  auto until(F func) {
  }

  std::vector<T> to_vector() {
  }

  template<typename Iter>
  void copy_to(Iter it) {
  }
};

template<typename T, typename Iter>
class range_enumerator : public enumerator<T> {
public:
  range_enumerator(Iter begin, Iter end) : begin_(begin), end_(end) {
  }

private:
  Iter begin_, end_;
};

template<typename T>
class drop_enumerator : public enumerator<T> {
public:
  drop_enumerator(enumerator<T> &parent, int count) : parent_(parent) {
  }

private:
};

template<typename T, typename U, typename F>
class select_enumerator : public enumerator<T> {
public:
  select_enumerator(enumerator<U> &parent, F func) : parent_(parent) {
  }

private:
};

template<typename T, typename F>
class until_enumerator : public enumerator<T> {
public:
  until_enumerator(enumerator<T> &parent, F predicate) : parent_(parent) {
  }

private:
};

} // namespace impl

template<typename T>
auto from(T begin, T end) {
  return impl::range_enumerator<???, ???>(begin, end);
}

} // namespace linq

#endif
