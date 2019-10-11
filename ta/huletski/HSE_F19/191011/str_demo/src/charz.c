#include "charz.h"

#include <stdlib.h>
#include <assert.h>

struct cz_node {
  char c;
  struct cz_node *next;
};

struct charz {
  struct cz_node *head;
};

static int charz_is_empty(const charz_t *cz);
static void charz_push_back(charz_t *cz, const char c);

// Public functions

charz_t *charz_create() {
  charz_t *charz = calloc(1, sizeof(*charz));
  assert(charz);
  return charz;
}

void charz_destroy(charz_t **cz) {
  charz_remove_all(*cz);
  free(*cz);
  *cz = NULL;
}

void charz_append_cstr(charz_t *cz, const char *str) {
  while (*str) {
    charz_push_back(cz, *str++);
  }
}

void charz_remove_all(charz_t *cz) {
  while (cz->head) {
    struct cz_node *waste = cz->head;
    cz->head = cz->head->next;
    free(waste);
  }
  assert(cz->head == NULL);
}

// Internal functions

// NB: static, "private" function
static int charz_is_empty(const charz_t *cz) {
  return cz->head == NULL;
}

static void charz_push_back(charz_t *cz, const char c) {
  struct cz_node *new_node = calloc(1, sizeof(*new_node));
  assert(new_node && "Malloc failed");
  new_node->c = c;

  if (charz_is_empty(cz)) { // corner case
    cz->head = new_node;
    return;
  }

  struct cz_node *last = cz->head;          // guess
  while (last->next) { last = last->next; } // refine guess
  last->next = new_node;
}
