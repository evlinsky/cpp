#include <stdlib.h>
#include <stdio.h>

char *create_default_str() {
  return "pefault str";

  //char buffer[] = "pefault str";
  //return buffer;
  //char *bfr_ptr = buffer;
  //return bfr_ptr;
}

int main(int argc, char **argv) {
  char *str = create_default_str();
  //*str = 'd';
  printf("%s\n", str);
}
