#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "charz.h"
#include "utils.h"

char *combine_cstrings(int str_nm, char **strs, char *sep) {
  assert(sep);
  if (str_nm == 0) {
    char *combined_strs = malloc(sizeof(char));
    assert(combined_strs);
    *combined_strs = '\0';
    return combined_strs;
  }

  size_t combined_strs_sz = 0;
  { // estimate combined size
    size_t sep_sz = strlen(sep);
    int str_i = 0;
    do {
      combined_strs_sz += strlen(strs[str_i++]);
      if (str_nm <= str_i) { break; }
      combined_strs_sz += sep_sz;
    } while (1);
  }

  char *combined_strs = calloc(1, combined_strs_sz + 1);
  { // combine strings
    int str_i = 0;
    do {
      strcat(combined_strs, strs[str_i++]);
      if (str_nm <= str_i) { break; }
      strcat(combined_strs, sep);
    } while (1);
  }
  return combined_strs;
}

void print_cstr_info(const char *cstr) {
  printf("== Cstr\n");
  printf("UPPER: ");
  print_upper_cstr(cstr);
  printf("\n");
  printf("NUMBER: ");
  printf("%lu\n", extract_number_cstr(cstr));
  unsigned d = 0, a = 0;
  collect_stat_cstr(cstr, &a, &d);
  printf("STAT: %u digits, %u alphas\n", d, a);
}

void print_charz_info(const charz_t *charz) {
  printf("== Charz\n");
  printf("UPPER: ");
  print_upper_charz(charz);
  printf("\n");
  printf("NUMBER: ");
  printf("%lu\n", extract_number_charz(charz));
  unsigned d = 0, a = 0;
  collect_stat_charz(charz, &a, &d);
  printf("STAT: %u digits, %u alphas\n", d, a);
}

int main(int argc, char** argv) {
  char *combined = combine_cstrings(argc - 1, argv + 1, "+");
  print_cstr_info(combined);

  //charz_t *charz = malloc(sizeof(*charz)); // ?
  charz_t *charz = charz_create();
  charz_append_cstr(charz, combined);
  print_charz_info(charz);
  charz_destroy(&charz);
  
  free(combined);
}
