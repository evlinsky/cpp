#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

size_t count_odds(int *elems, int *elems_end) {
  assert(elems != NULL && "[Pre] Elems must provide data");
  size_t odds_cnt = 0;
  
  while (elems != elems_end) {
    odds_cnt += *elems++ % 2;
  }
  return odds_cnt;
}

int* get_odds(int *elems, size_t elems_nm, size_t *out_odds_nm) {
  assert(elems && "[Pre] Elems must be allacated");

  int *elems_end = elems + elems_nm;
  size_t odds_nm = count_odds(elems, elems_end);
  int *odds = malloc(odds_nm * sizeof (*odds));
  int *odds_end = odds + odds_nm;
  assert(odds && "FAIL: Malloc failed to allocate memory");
  int *next_odds = odds;
  for (;elems != elems_end; elems++) {
    if (*elems % 2 == 0) { continue; }
    assert((next_odds < odds_end) && "[Inv] Odd array has enough space");
    *next_odds++ = *elems;
  }
  assert(next_odds == odds_end && "[Post] Odd is full");

  assert(out_odds_nm && "[Pre] Bad out ptr");
  *out_odds_nm = odds_nm;
  return odds;
}

size_t get_odds_alt(int *elems, size_t elems_nm, int **out_odds) {
  size_t odds_nm = 0;
  
  assert(out_odds && "Bad out ptr");
  *out_odds = get_odds(elems, elems_nm, &odds_nm);
  return odds_nm;
}

void print_ints(int *ints, size_t ints_nm) {
  size_t i = 0;
  while (i != ints_nm) {
    printf("%d ", ints[i++]);
  }
  printf("\n");
}

int main(int argc, char **argv) {
  #define SIZEOF_ARRAY(arr) (sizeof(arr) / sizeof(*(arr)))
  #define GET_END(arr) ((arr) + SIZEOF_ARRAY(arr)) // FYI
  {
    int arr[] = {1, 2, 3, 4, 5, 7, 4};
    { // Extra scope to reuse var names
      size_t odds_nm = 0;
      int *odds = get_odds(arr, SIZEOF_ARRAY(arr), &odds_nm);
      print_ints(odds, odds_nm);
      free(odds);
    }
    {
      int *odds;
      size_t odds_nm = get_odds_alt(arr, SIZEOF_ARRAY(arr), &odds);
      print_ints(odds, odds_nm);
      free(odds);
    }
  }
  //assert(NULL && "Always fail"); // disable with -DNDEBUG gcc arg
  #undef GET_END
  #undef SIZEOF_ARRAY
}
