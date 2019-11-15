#ifndef MY_VECTOR_H
#define MY_VECTOR_H

// Class name: MyVector
// Methods:
//   MyVector() - инициализирует вектор с capacity 2;
//   MyVector(size_t init_capacity)
//     - инициализирует вектор с capacity <init_capacity>;
//  ~MyVector() - уничтожает объект;
//
//  void set(size_t i, int value) -- i-ый эл-т становится равным value;
//  int get(size_t i) - возвращает i-ый элемент;
//  size_t size() - текущий количество элементов;
//  size_t capacity() - зарезервированный размер памяти в элементах;
//
//  void push_back(int value) - добавить элемент в конец вектора;
//  void insert(size_t index, int value) -
//    - вставить элемент со значением <value> в позицию
//      с индексом <index> ([0; size]);
//  void erase(size_t index) - удалить элемент по индексу <index>;
//  void resize(size_t new_size);
//    - изменить размер вектора, новыe значения должны инициализироваться 0-ем.
//      Eсли <new_size> больше capacity, новое значение capacity должо быть
//      максимумом из <new_size> и 2*capacity;
//
//  void reserve(size_t new_capacity)
//    - зарезервировать память достаточную для хранения <new_capacity>
//      элементов. Eсли аргумент больше capacity, capacity становится
//      равным аргументу, иначе ничего не происходит.
//
// Reference: https://en.cppreference.com/w/cpp/container/vector
//
// Extra:
//   a) operator+=(const MyVector &)
//   b) autotests for MyVector
//   c) vector of bools:
//        - 1 bit per element;
//        - operator[](size_t index) (s.t. vec_bools[i] = true; )

#endif
