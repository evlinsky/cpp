#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "intrusive_list.h"

typedef struct {
  char c;
  intrusive_node_t node;
} character_t;

void print_ilstring(const intrusive_list_t *l) {
  intrusive_node_t *icursor = l->head;
  while (icursor) {
    char c = container_of(icursor, character_t, node)->c;
    printf("%c", c);
    icursor = icursor->next;
  }
  printf("\n");
}

void push_back_character(intrusive_list_t *il, char c) {
  character_t *ch = malloc(sizeof(*ch));
  assert(ch);
  ch->c = c;
  //NB: performance hit
  push_back(il, &ch->node);
}

void push_back_string(intrusive_list_t *il, const char *str) {
  while (*str) {
    push_back_character(il, *str++);
  }
}

void clean_list(intrusive_list_t *il) {
  /* TODO: implement me */
}

int main(int argc, char **argv) {
  intrusive_list_t il;
  init_list(&il);

  if (1 < argc) {
    for (size_t i = 1; i < argc - 1; i++) {
      push_back_string(&il, argv[i]);
      push_back_character(&il, ' ');
    }
    push_back_string(&il, argv[argc - 1]);
  } else {
    push_back_string(&il, "John 2-64-4 Doe");
  }

  print_ilstring(&il);
  /* TODO: add 'ilstring' pretty printing
      - upper case (man toupper)
      - digit -> '*' (man isdigit)
     Hint: (*)()
  */
  clean_list(&il);
}
