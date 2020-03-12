#include <iostream>
#include <iterator>
#include <utility> // for potential std::exchange
#include <algorithm>

class Range {
public:
  Range(unsigned limit) : limit_(limit) {}

  class RangeIterator { // : std::iterator<category, value_t, ...>
                        // Depricated since C++17.
  public: // types
    using iterator_category = std::input_iterator_tag; // forward?
    using value_type = int;
    using pointer = value_type*;
    using reference = value_type&;
    using difference_type = void; // std::ptrdiff_t
  public: // methods
    RangeIterator(unsigned init) : curr_(init) {}
    RangeIterator& operator++() {
      curr_++;
      return *this;
    }
    RangeIterator operator++(int) {
      //return std::exchange(*this, (*this)++);
      RangeIterator prev = *this;
      ++(*this);
      return prev;
    }
    friend bool operator==(const RangeIterator &lhs, const RangeIterator &rhs) {
      return lhs.curr_ == rhs.curr_;
    }
    friend bool operator!=(const RangeIterator &lhs, const RangeIterator &rhs) {
      return !(lhs == rhs);
    }
    value_type operator*() const { return curr_; }
    // operator-> has no meaning
  private:
    unsigned curr_;
  };

  RangeIterator begin() { return RangeIterator(0); }
  RangeIterator end() { return RangeIterator(limit_ + 1); }
private:
  unsigned limit_;
};

int main(int, char**) {
  // auto range = Range(3);
  // for (auto it = range.begin(); it != range.end(); it++) {
  //  auto e = *it;
  for (auto e : Range(3)) {
    std::cout << e;
  }
  std::cout << std::endl;
}
