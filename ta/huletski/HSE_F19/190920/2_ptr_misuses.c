#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void null_dereference();
void stack_smashing();
void ptr_print();

int main(int argc, char **argv) {
  //null_dereference();
  //stack_smashing();
  ptr_print();
}

void null_dereference() {
  char *p = NULL;
  *p = 42;
}

void stack_smashing() {
  char a[1];
  a[2] = 0;
}

void inner() {
  char a;
  printf("inner &a = %p\n", &a);
}

void ptr_print() {
  // Show
  // - stack/heap growth
  // - bad access
  // - memory leak + fix
  // - double free error
  // - non-allocated ptr free
  char a, b, c;
  char *d = malloc(sizeof(*d)), *e = malloc(sizeof(*e));

  printf("&a = %p\n&b = %p\n&c = %p\n&d = %p\n", &a, &b, &c, &d);
  inner();
  printf("d = %p\ne = %p\ne - d = %ld\n", d, e, e - d);

  //d[100] = 'a';
  //free(d);
  //d = NULL;
  //free(e);
  //free(d);
  //free(NULL);

  //int *p1 = (int *)&c, *p2 = (int *)(uint64_t)c;
  //free(p1);
  //free(p2);
  //free(c);
}
