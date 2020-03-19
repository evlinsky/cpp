#include <unordered_map>
#include <string>
#include <iostream>
#include <utility>
#include <vector>
#include <cassert>

void range_based_for() {
  auto stored_items = std::unordered_map<std::string, unsigned>{
    {"milk", 42}, {"pork", 64},
    {"juice", 135}, {"coconut", 65}
  };
  for (auto &[sku, nm] : stored_items) {
    std::cout << "We have " << nm << " " << sku << " units\n";
  }
}

//------------------------------------------------------------------------------

class StoredItem {
public:
  StoredItem(std::string sku, unsigned nm) : sku_(std::move(sku)), nm_(nm) {}

  std::string sku() const { return sku_; }
  unsigned nm() const { return nm_; }

// public:
private:
  std::string sku_;
  unsigned nm_;
};

template <std::size_t Index> auto get(const StoredItem &);
template <> auto get<0>(const StoredItem &si) { return si.sku(); }
template <> auto get<1>(const StoredItem &si) { return si.nm(); }

namespace std {
  template<> struct tuple_size<::StoredItem> {
    static constexpr std::size_t value = 2;
  };
  template<> struct tuple_element<0, ::StoredItem> {
    using type = std::string;
  };
  template<> struct tuple_element<1, ::StoredItem> {
    using type = unsigned;
  };
  // template<std::size_t Index>
  // struct tuple_element<Index, ::StoredItem> {
  //   //using type = decltype(get<Index>(::StoredItem()));
  //   using type = decltype(get<Index>(declval<::StoredItem>()));
  // };
};

void custom_binding() {
  std::cout << "= Custom Binding\n";
  auto stored_items = std::vector<StoredItem>{
    {"milk", 42}, {"pork", 64},
    {"juice", 135}, {"coconut", 65}
  };
  for (auto &[sku, nm] : stored_items) {
    std::cout << "We have " << nm << " " << sku << " units\n";
  }
}

//------------------------------------------------------------------------------

struct Foo {};

template <std::size_t Index> void get(const Foo &si) {}

namespace std {
  template<> struct tuple_size<::Foo> {
    static constexpr std::size_t value = 1;
  };
  template<>
  struct tuple_element<0, ::Foo> {
    using type = void;
  };
};

void gxx_9_2_1() {
  // auto [foo] = Foo{};
}

int main(int, char**) {
  // a. structured bind + range-based for
  // range_based_for();
  // b. custom binding
  // - 1. fields public
  // - 2. fields private
  // custom_binding();
  // c. (aside) the importance of being earnest
  // gxx_9_2_1();
}
