#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *gen_random_string(size_t len) {
  char *rstr = malloc((len + 1)* sizeof(*rstr));
  bzero(rstr, (len + 1) * sizeof(*rstr));

  const char * const Abc = "ABCDEF";
  const size_t Abc_Len = strlen(Abc);
  for (size_t i = 0; i < len; i++) {
    rstr[i] = Abc[rand() % Abc_Len];
  }
  return rstr;
}

unsigned count(const char *s, char c) {
  unsigned cnt = 0;
  while (*s) {
    cnt += *s == c;
    s++;
  }
  return cnt;
}

int main(int argc, char **argv) {
  if (argc == 2) {
    srand(atoi(argv[1]));
  }
  
  char *str = gen_random_string(30);
  printf("%s - %u\n", str, count(str, 'A'));
  free(str);
}
