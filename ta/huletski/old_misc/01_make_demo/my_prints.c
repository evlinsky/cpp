#include <stdio.h>

void print(const char* msg) {
  printf("%s\n", msg);
}

void pretty_print(const char* msg) {
  printf("= %s =\n", msg);
}
