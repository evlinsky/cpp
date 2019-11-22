#pragma once

#include <cstddef>

class Range {
public:
  Range(int from, int to);
  Range& operator++();
  Range operator++(int);
  // get element
  int operator*() const;
  bool done() const;
  // NB: operator bool/int() implementation
  //   C++11 -> use "explicit" keyword
  // --C++11 -> Safe Bool idiom
private:
  int _from, _curr, _to;
};

class IntSet {
public:
  IntSet(std::size_t max_nm);
  bool operator[](int e) const;
  // is a superset
  bool operator<=(const IntSet &) const;
  bool operator==(const IntSet &) const;
  void print();
//--------------------------------------
  IntSet& operator&=(const IntSet &);
  // NB: not const IntSet &
  IntSet operator&(const IntSet &) const;
  IntSet& operator|=(const IntSet &);
  IntSet operator|(const IntSet &) const;
//---------------------------------------
  IntSet operator()(bool (*)(int e)) const;
  IntSet& operator<<(void (*)(IntSet&));
//---------------------------------------
  // is a proper superset
  bool operator<(const IntSet &) const;
  bool operator>(const IntSet &) const;
  bool operator>=(const IntSet &) const;
  bool operator!=(const IntSet &) const;
//--------------------------------------
  // Range methods
  IntSet& operator<<(Range);
//--------------------------------------
private:
  std::size_t _nm, _cp;
  int *_data;
};
