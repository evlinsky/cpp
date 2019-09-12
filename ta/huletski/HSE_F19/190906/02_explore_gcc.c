/*
  > gcc 02_explore_gcc.c -o explore_gcc # -o sets executalbe name
  > gcc 02_explore_gcc.c -E             # -E - stop after the proproc phase
                                        # result: output
  > gcc 02_explore_gcc.c -S             # -S - stop after the compilation phase
                                        # result: 02_explore_gcc.s
  > gcc 02_explore_gcc.c -c             # -c - stop after the assembling phase
                                        # result: 02_explore_gcc.o
  > objdump -d 02_explore_gcc.o         # view translated code
 */

/*
  > gcc 02_explore_gcc.c -nodefaultlibs # error (libc is linked implicitly)
 */

#define MY_FAVORITE_NUMBER 740

int main(int arc, char** argv) {
  // NB: still a bad practice (MY_FAV_NUM % 256 actually in linux)
  return MY_FAVORITE_NUMBER;
}
