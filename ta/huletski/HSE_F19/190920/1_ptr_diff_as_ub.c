#include <stdint.h>
#include <stdio.h>

void case1() {
  char a[4], b[4],
       *a_ptr = a, *b_ptr = b;
  printf("= Case1\n");
  printf("a = %p\nb = %p\ndiff = %ld\n", a_ptr, b_ptr, b_ptr - a_ptr);
}

void case2() {
  char a[4], b[3],
       *a_ptr = a, *b_ptr = b;
  printf("= Case1\n");
  printf("a = %p\nb = %p\ndiff = %ld\n", a_ptr, b_ptr, b_ptr - a_ptr);
}

int main(int argc, char **argv) {
  case1();
  case2();
}
