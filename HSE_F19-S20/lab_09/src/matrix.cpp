#include "matrix.hpp"

#include <cassert>
#include <algorithm>

Matrix::Matrix(std::size_t r, std::size_t c) :
        _rows(r), _cols(c), _data(new int*[_rows]()) {
    for (std::size_t row_i = 0; row_i != _rows; ++row_i) {
        _data[row_i] = new int[_cols]();
    }
}

Matrix::~Matrix() {
    for (std::size_t row_i = 0; row_i != _rows; ++row_i) {
        delete[] _data[row_i];
    }
    delete[] _data;
}

std::size_t Matrix::get_rows() const { return _rows; }
std::size_t Matrix::get_cols() const { return _cols; }

void Matrix::set(std::size_t i, std::size_t j, int val) {
    assert(i < _rows && j < _cols);
    _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
    assert(i < _rows && j < _cols);
    return _data[i][j];
}

bool Matrix::operator==(const Matrix& that) const {
    for (std::size_t i = 0; i != get_rows(); ++i) {
        for (std::size_t j = 0; j != get_cols(); ++j) {
            if (get(i, j) != that.get(i, j)) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& that) const {
    return !(*this == that);
}
