#include <stdio.h>
#include <stdlib.h>

void inner() {
  char a;
  printf("inner &a = %p\n", &a);
}

int main(int argc, char **argv) {
  char a, b, c;
  char *d = malloc(sizeof(*d)), *e = malloc(sizeof(*e));

  printf("&a = %p\n&b = %p\n&c = %p\n&d = %p\n", &a, &b, &c, &d);
  inner();
  printf("d = %p\ne = %p\ne - d = %ld\n", d, e, e - d);

  free(d);
  free(e);
}
