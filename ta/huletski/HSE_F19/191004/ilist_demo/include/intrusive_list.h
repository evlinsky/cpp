#ifndef INTRUSIVE_LIST_H_INCLUDED
#define INTRUSIVE_LIST_H_INCLUDED

#include <stddef.h>

struct intrusive_node {
  struct intrusive_node *next;
  struct intrusive_node *prev;
};

struct intrusive_list {
  struct intrusive_node *head;
};

typedef struct intrusive_list intrusive_list_t;
typedef struct intrusive_node intrusive_node_t;

#define container_of(ptr, type, mem) \
  ((type*)((char*)(ptr) - offsetof(type, mem)))

void init_list(intrusive_list_t *il);
void push_back(intrusive_list_t *il, intrusive_node_t *in);

#endif
