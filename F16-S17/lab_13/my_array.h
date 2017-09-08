template<typename T, std::size_t N>
class my_array {
 public:
  at(std::size_t index);
  operator[](std::size_t index);

  bool empty();
  size();

  fill(T val);
};
