#ifndef _CLIST_12112014_
#define _CLIST_12112014_

struct intrusive_node {
    intrusive_node *next;
    intrusive_node *prev;
};
struct intrusive_list {
    intrusive_node head;
};

void init_list(intrusive_list *);

void add_node(intrusive_list *, intrusive_node *);

// contract: node != &list->head
void remove_node(intrusive_list *, intrusive_node *);

int get_length(intrusive_list *);

#endif