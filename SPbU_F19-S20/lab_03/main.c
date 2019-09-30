struct point {
  int x, y;
  struct intrusive_node /* ? */ node;
};

/* ? */ add_point(intrusive_list /* ? */, int x, int y) {

}

/* ? */ remove_point(intrusive_list /* ? */, int x, int y) { // removes all (x, y) pairs

}

/* ? */ show_all_points(/* ? */) {

}

/* ? */ remove_all_points(/* ? */) {

}

int main() {
  /* usage

     intrusive_list_t l;
     init_list(&l);

     add_point(&l, 10, 10);
     add_point(&l, 20, 20);

     show_all_points(&l);

     return 0;
  */
}
