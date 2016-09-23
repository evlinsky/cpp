struct intrusive_node {
  struct intrusive_node* next;
  struct intrusive_node* prev;
};

struct intrusive_list {
  struct intrusive_node* head;
};

/* ? */ init_list(intrusive_list /* ? */, intrusive_node /* ? */);
/* ? */ add_node(intrusive_list /* ? */, intrusive_node /* ? */);
/* ? */ remove_node(intrusive_list /* ? */, intrusive_node /* ? */);

int get_length(intrusive_list /* ? */ );
