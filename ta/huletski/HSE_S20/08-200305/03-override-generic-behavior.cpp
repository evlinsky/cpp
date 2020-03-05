#include <iostream>
#include <functional> // std::hash
#include <unordered_set>

struct Foo {
  std::string s;
  int i;
};

bool operator==(const Foo &lhs, const Foo &rhs) {
  return lhs.s == rhs.s && lhs.i == rhs.i;
}

namespace std {
  template <>
  struct hash<Foo> {
    std::size_t operator()(const Foo &f) const noexcept {
      //std::cout << "Hash!\n";
      return std::hash<std::string>{}(f.s) ^ std::hash<int>{}(f.i);
    }
  };
}

int main(int, char**) {
  std::unordered_set<Foo> set = {{"blah", 1}, {"blah", 2}};
}

