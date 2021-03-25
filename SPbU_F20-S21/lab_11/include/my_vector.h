#ifndef MY_VECTOR_H_
#define MY_VECTOR_H_

#include <cstddef>

namespace containers {

template<typename T>
class my_vector {
public:
    my_vector();
    my_vector(std::size_t n);
    my_vector(my_vector other);
    my_vector operator=(my_vector other);
    ~my_vector();

    std::size_t size();
    std::size_t capacity();
    bool empty();

    void resize(std::size_t n);
    void reserve(std::size_t n);

    ?? operator[](std::size_t index);

    void push_back(T t);
    void pop_back();
    void clear();

private:
    size_t capacity_;
    size_t size_;
    T* array_;
};

}

#include "my_vector_impl.h"

#endif  // MY_VECTOR_H_
