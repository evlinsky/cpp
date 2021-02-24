#include "matrix.h"

Matrix::Matrix(std::size_t r, std::size_t c) {
}

std::size_t Matrix::get_rows() { return 0; }
std::size_t Matrix::get_cols() { return 0; }

void Matrix::set(std::size_t i, std::size_t j, int val) {
}

int Matrix::get(std::size_t i, std::size_t j) {
  return 0;
}

void Matrix::print(FILE* f) {
}

bool Matrix::operator==(Matrix& m) {
  return true;
}

bool Matrix::operator!=(Matrix& m) {
  return false;
}

Matrix& Matrix::operator+=(Matrix& m) {
  return *this;
}

Matrix& Matrix::operator-=(Matrix& m) {
  return *this;
}

Matrix& Matrix::operator*=(Matrix& m) {
  return *this;
}

Matrix Matrix::operator+(Matrix& m) {
  return *this;
}

Matrix Matrix::operator-(Matrix& m) {
  return *this;

}

Matrix Matrix::operator*(Matrix& m) {
  return *this;
}
