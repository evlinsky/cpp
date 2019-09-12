// = Run =
/*
  > gcc 01_run_me.c # run gcc 'pipeline' -> a.out (by defaut)
  > ./a.out bla bla # run compiled program, './' prefix is mandatory
  > echo $?         # print exit code, $? - bash way to access it
  3
  > gcc 01_run_me.c -v # -v flag is for verbose output
  NOTICE:
    cc1      (preprocessing (cpp), compiling (cc)) -> asm file
    as       (assembling)                          -> object file
    collect2 (linking (ld))                        -> a.out
 */

int main(int argc, char** argv) {
  // NB: bad practice. Main ret value is supposed to indicate an error
  return argc;
}
