#pragma once

#include <cstddef>

char *alloc_chars(std::size_t nm);

class my_string {
public:
  my_string(const char *);
  my_string(const my_string &);
  my_string& operator=(my_string);
  ~my_string();

  const char& operator[](std::size_t) const;
  char& operator[](std::size_t);
  friend bool operator==(const my_string &lhs, const my_string &rhs);
private:
  void swap(my_string &that);
private:
  char *_data;
};

bool operator==(const my_string &lhs, const my_string &rhs);
