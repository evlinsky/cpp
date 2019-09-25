#include <stdlib.h>

void null_dereference();
void memory_leak();
void non_allocated_free();

void out_of_bounds_heap_access();
void out_of_bounds_stack_access();

void double_free();
void dangling_ptr_access();

int main(int argc, char **argv) {
  //null_dereference();
  //memory_leak();
  //non_allocated_free();

  /* overflows */
  //out_of_bounds_heap_access();
  //out_of_bounds_stack_access();

  /* 1+ owners */
  //double_free();
  //dangling_ptr_access();
}

void null_dereference() {
  char *p = NULL;
  *p = 42;
}

void memory_leak() {
  char *p = malloc(sizeof(*p));
  *p = 'a';
}

void non_allocated_free() {
  char p;
  free(&p);
}

void out_of_bounds_heap_access() {
  char *p = malloc(sizeof(*p) * 256);
  char c = p[2048];
  p[256] = '1'; // buffer overflow
  free(p);
}

void out_of_bounds_stack_access() {
  // NB: -fno-stack-protector
  char a[1];
  a[2] = 0;
}

void double_free() {
  // 1+ 'owner'
  char *p = malloc(sizeof(*p));
  char *d = p;

  free(p);
  //free(p);
  free(d);
  /*
    free(p);
    p = NULL;
    free(p);
   */
}

void dangling_ptr_access() {
  char *p = malloc(sizeof(*p));
  char *d = p;

  free(p);
  *d = 'a';
}
