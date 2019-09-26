#include "linked_list.h"

#include <stdlib.h>
#include <assert.h>

void create(list_t *l) {
  l->head.next = NULL;
  l->nm = 0;
}

void destroy(list_t *l) {
  // TODO: implement me
}

void push_back(list_t *l, int x) {
  // TODO: implement me
}

node_t* find(list_t *l, int x) {
  node_t *e = l->head.next;
  while (e && e->x != x) {
    e = e->next;
  }
  return e;
}

int get(list_t *l, size_t index) {
  // TODO: implemenet me
  return -1;
}

void insert(list_t *l, node_t *previous, int x) {
  // TODO: implement me
}

void erase(list_t *l, node_t *previous) {
  assert(previous);
  node_t *waste = previous->next;
  if (waste) {
    previous->next = waste->next;
    l->nm--;
  }
  free(waste);
}
