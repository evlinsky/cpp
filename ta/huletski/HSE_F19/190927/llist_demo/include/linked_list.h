#ifndef LINKED_LIST_H_INCLUDED
#define LINKED_LIST_H_INCLUDED

#include <stddef.h>

typedef struct node {
  int x;
  struct node *next;
} node_t;

typedef struct {
  node_t head; //sentiel
  size_t nm;
} list_t;

void create(list_t *l);
void destroy(list_t *l);

void insert(list_t *l, node_t *previous, int x);
void push_back(list_t *l, int x);
node_t* find(list_t *l, int x);
int get(list_t *l, size_t index);
void erase(list_t *l, node_t *previous);

#endif
