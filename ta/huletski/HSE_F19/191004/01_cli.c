#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void foo() {
  exit(EXIT_FAILURE); // general error
}

int main(int argc, char **argv) {
  // = Print program args
  for (int i = 0; i < argc; i++) {
    printf("%d - %s\n", i, argv[i]);
  }

  // = Exit status: echo $?
  //foo();
  //assert(0); // -> error 134 program abort
  //int a = 0, b = 1 / a; // -> error 136 arith error
  //char *p = NULL; *p = 'a'; // -> error 139 seg fault
}
