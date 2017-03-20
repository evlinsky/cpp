#include <iostream>
#include <string>
#include <iterator>

//-------

struct Day {
private:
  static constexpr std::size_t Unique_Day_Name_Nm = 7;
public:
  explicit Day(int id)
    : name{1 <= id && id <= Unique_Day_Name_Nm ?
        _Id2Name[id - 1] : "Unknown"} { }

  std::string name;
private:
  static const std::string _Id2Name[Unique_Day_Name_Nm];
};

const std::string Day::_Id2Name[] =
  { "Mod", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};

std::ostream& operator<<(std::ostream &os, const Day &d) {
  return os << d.name;
}

bool operator==(const Day &lhs, const Day &rhs) {
  return lhs.name == rhs.name;
}

//-------

struct Week {
public:
  class DayIterator /* NB: std::iterator is depricated in C++17; RIP. */
                    /*     define types aliases explicitly */
    : public std::iterator<std::input_iterator_tag, /* iterator_category */
                           Day                      /* value_type */
                       /*, std::ptrdiff_t,          // difference_type
                           Day*,                    // pointer
                           Day&                     // reference
                         */
                           > {
  public:
    DayIterator(int id) : _id{id} {}
    DayIterator& operator++() {
      _id++;
      return *this;
    }
    DayIterator operator++(int) {
      DayIterator prev = *this;
      ++(*this);
      return prev;
    }
    bool operator==(const DayIterator &that) const { return **this == *that; }
    bool operator!=(const DayIterator &that) const { return !(*this == that); }
    value_type operator*() const { return Day{_id}; }
  private:
    int _id;
  };

  DayIterator begin() { return DayIterator{1}; }
  DayIterator end() { return DayIterator{-1}; }
};



int main(int, char**) {
  for (const Day& d : Week()) {
    std::cout << d << std::endl;
  }
  return 0;
}
