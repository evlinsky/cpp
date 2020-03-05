#include <cstdint>
#include <utility>
#include <new>
#include <cassert>

class IntArray2D {
public:
  IntArray2D(std::size_t row_nm, std::size_t col_nm,
             std::size_t throw_on_col = 100500)
    : rows_(nullptr)
    , throw_on_col_(throw_on_col) {
    allocate(row_nm, col_nm);
  }
  ~IntArray2D() { deallocate(); }
  IntArray2D(const IntArray2D&) = delete;
  IntArray2D(IntArray2D&&) = delete;
  IntArray2D& operator=(const IntArray2D&) = delete;
  IntArray2D& operator=(IntArray2D&&) = delete;
private:
  void allocate(std::size_t row_nm, std::size_t col_nm) {
    try {
      if (throw_on_col_ == 0xDEAD) {
        throw std::bad_alloc();
      }
      // mandatory value-initialization -> all ptrs are 0
      rows_ = new int*[row_nm + 1](); // NB: extra sentinel/guard value
      for (std::size_t col_i = 0; col_i < col_nm; col_i++) {
        if (col_i == throw_on_col_) {
          throw std::bad_alloc();
        }
        rows_[col_i] = new int[col_nm]/*()*/;
      }
    } catch (const std::bad_alloc &ba) {
      deallocate();
      throw;
    }
  }

  void deallocate() noexcept {
    if (!rows_) { return; }
    int** row = rows_;
    while (*row) {
      //delete [] std::exchange(*row, nullptr);
      delete [] *row;
      row++;
    }
    delete [] rows_;
  }
private:
  int **rows_;
  std::size_t throw_on_col_;
};

int main(int, char**) {
  // {
  //   [[maybe_unused]] IntArray2D ia{1000, 10};
  // }
  {
    bool is_caught = false;
    try {
      [[maybe_unused]] IntArray2D ia{1000, 10, 0xDEAD};
    } catch (const std::bad_alloc &ba) {
      is_caught = true;
    }
    assert(is_caught);
  }
  {
    bool is_caught = false;
    try {
      [[maybe_unused]] IntArray2D ia{1000, 10, 0};
    } catch (const std::bad_alloc &ba) {
      is_caught = true;
    }
    assert(is_caught);
  }
  {
    bool is_caught = false;
    try {
      [[maybe_unused]] IntArray2D ia{1000, 10, 5};
    } catch (const std::bad_alloc &ba) {
      is_caught = true;
    }
    assert(is_caught);
  }
}
