#include "my_string.h"

#include <cstring>
#include <cassert>
#include <cstdio>
#include <utility>

char *alloc_chars(std::size_t nm) {
  std::printf("new char[%lu]\n", nm);
  return new char[nm];
}

my_string::my_string(const char *c_str)
  : _data(alloc_chars(std::strlen(c_str) + 1)) {
  //assert(_data); // nb: plain new[] throws on fail
  std::strcpy(_data, c_str);
}

my_string::my_string(const my_string &that)
  : _data(alloc_chars(std::strlen(that._data) + 1)) {
  assert(_data);
  std::strcpy(_data, that._data);
}

my_string& my_string::operator=(my_string that) {
  my_string(that).swap(*this);
  return *this;
}

my_string::~my_string() {
  delete [] _data;
}

void my_string::swap(my_string &that) {
  using std::swap;
  swap(_data, that._data);
}

const char& my_string::operator[](std::size_t i) const {
  return _data[i];
}

char& my_string::operator[](std::size_t i) {
  //return const_cast<char &>(static_cast<const my_string &>(*this)[i]);
  return (char &)(((const my_string&)(*this))[i]);
}

bool operator==(const my_string &lhs, const my_string &rhs) {
  return std::strcmp(lhs._data, rhs._data) == 0;
}
