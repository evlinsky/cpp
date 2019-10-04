#include <stdio.h>

void modify(const char *prefix, const char *data) {
  printf("%s: %p\n", prefix, data);
  ((char *)data)[0] = 'a';
  printf("%s: %s\n", prefix, data);
}

void modify_carr() {
  const char c[] = "ABC";
  modify("carr", c);
}

void modify_cptr() {
  const char *c = "ABC";
  modify("cptr", c);
}

int main(int argc, char **argv) {
  modify_carr();
  modify_cptr();
}
