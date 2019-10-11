#ifndef UTILS_H
#define UTILS_H

#include "charz.h"

// c-string utils
void print_upper_cstr(const char *);
unsigned long extract_number_cstr(const char *);
void collect_stat_cstr(const char *,
                       unsigned *alpha_nm, unsigned *digit_nm);

// charz utils
void print_upper_charz(const charz_t *);
unsigned long extract_number_charz(const charz_t *);
void collect_stat_charz(const charz_t *,
                         unsigned *alpha_nm, unsigned *digit_nm);

#endif
