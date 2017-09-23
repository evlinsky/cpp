struct position_node {
  int x, y;
  struct intrusive_node /* ? */ node;
};

/* ? */ remove_position(intrusive_list /* ? */, int x, int y) { // removes all (x, y) pairs

}

/* ? */ add_position(intrusive_list /* ? */, int x, int y) {

}

/* ? */ show_all_positions(/* ? */) {

}

/* ? */ remove_all_positions(/* ? */) {

}

int main() {
  /* usage

     intrusive_list_t l;
     init_list(&l);

     add_position(&l, 10, 10);
     add_position(&l, 20, 20);

     show_all_positions(&l);

     return 0;
  */
}
