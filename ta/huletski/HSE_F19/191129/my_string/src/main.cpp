#include <cstdio>
#include <cassert>

#include "my_string.h"

int main(int, char **) {
  const char * const Test_CStr = "abc";
  my_string a(Test_CStr), b(a), c(b);
  printf("= a,b,c created\n");
  assert(a == b);
  a[1] = 'e';
  printf("= a modified\n");
  my_string d = a;
  printf("= d created\n");
  b = c;
  printf("= b assigned\n");
  assert(b == Test_CStr);
  assert(c == Test_CStr);
  assert("aec" == a);
  assert(d == "aec");
}
