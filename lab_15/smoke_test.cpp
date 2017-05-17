#include "linq.h"
#include <math.h>
#include <assert.h>
#include <vector>
#include <sstream>
#include <iterator>

void example1() {
  int xs[] = { 1, 2, 3, 4, 5 };
  
  std::vector<int> res =
    from(xs, xs + 5)  // Взять элементы xs
    .select([](int x) { return x * x; })  // Возвести в квадрат
    .where_neq(25)    // Оставить только значения != 25
    .where([](int x) { return x > 3; })   // Оставить только значения > 3
    .drop(2)          // Убрать два элемента из начала
    .to_vector();     // Преобразовать результат в вектор

  std::vector<int> expected = { 16 };
  assert(res == expected);
}

void example2() {
  std::stringstream ss("1 2 3 -1 4");
  std::istream_iterator<int> in(ss), eof;
  
  std::vector<int> res =
    from(in, eof)  // Взять числа из входного потока
    .take(4)       // Не более четырёх чисел
    .until_eq(-1)  // Перестать читать после прочтения -1
    .to_vector();  // Получить список считанных чисел
  
  std::vector<int> expected = { 1, 2, 3 };
  assert(expected == res);

  int remaining;
  assert(ss >> remaining);
  assert(remaining == 4);
}

void example3() {
  int xs[] = { 1, 2, 3, 4, 5 };
  
  std::vector<double> res =
    from(xs, xs + 5)  // Взять элементы xs
    .select<double>([](int x) { return sqrt(x); })  // Извлечь корень
    .to_vector();     // Преобразовать результат в вектор
  
  assert(res.size() == 5);
  for (std::size_t i = 0; i < res.size(); i++) {
    assert(fabs(res[i] - sqrt(xs[i])) < 1e-9);
  }
}

void example4() {
  std::stringstream iss("4 16");
  std::stringstream oss;
  std::istream_iterator<int> in(iss), eof;
  std::ostream_iterator<double> out(oss, "\n");

  from(in, eof)    // Взять числа из входного потока
  .select([](int x) { return sqrt(x); })  // Извлечь из каждого корень
  .copy_to(out);  // Вывести на экран
  
  assert(oss.str() == "2\n4\n");
}

int main() {
  example1();
  example2();
  example3();
  example4();
  return 0;
}
