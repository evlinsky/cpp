#ifndef LAB_08_MATRIX_H
#define LAB_08_MATRIX_H

#include <cstdio>
#include <cstddef>

class Matrix {
public:
  Matrix(std::size_t r, std::size_t c);

  std::size_t get_rows();
  std::size_t get_cols();
  void set(std::size_t i, std::size_t j, int val);
  int get(std::size_t i, std::size_t j);
  void print(FILE *f);

  Matrix operator+(Matrix& m);
  Matrix operator-(Matrix& m);
  Matrix operator*(Matrix& m);

  Matrix& operator+=(Matrix& m);
  Matrix& operator-=(Matrix& m);
  Matrix& operator*=(Matrix& m);

  bool operator==(Matrix& m);
  bool operator!=(Matrix& m);
private:
  std::size_t _rows;
  std::size_t _cols;
  int **_data;
};

#endif
