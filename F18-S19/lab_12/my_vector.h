#include <cstddef>

template <class T>
class my_vector{
public:
    my_vector();
    my_vector(size_t n);
    my_vector(my_vector& other);
    my_vector& operator=(my_vector& other);
    ~my_vector();

    size_t size();
    size_t capacity();
    bool empty();

    void resize(size_t n);
    void reserve(size_t n);

    ?? operator[](size_t index);

    void push_back(T& t);
    void pop_back();
    void clear();

private:
    size_t capacity_;
    size_t size_;
    T* array_;
};
