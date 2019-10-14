#ifndef CLIST_H_
#define CLIST_H_

typedef struct intrusive_node {
    struct intrusive_node *next;
    struct intrusive_node *prev;
} intrusive_node;

typedef struct intrusive_list {
    intrusive_node head;
} intrusive_list;

void init_list(intrusive_list *);

void add_node(intrusive_list *, intrusive_node *);

// contract: node != &list->head
void remove_node(intrusive_list *, intrusive_node *);

int get_length(intrusive_list *);

#endif
