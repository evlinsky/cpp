#ifndef MY_ARRAY_H_
#define MY_ARRAY_H_

#include <cstddef>

namespace lab_13 {

template<typename T, std::size_t N>
class my_array {
public:
    at(std::size_t index);
    operator[](std::size_t index);

    bool empty();
    size();

    fill(T val);
};

}  // namespace lab_13

#endif  // MY_ARRAY_H_
