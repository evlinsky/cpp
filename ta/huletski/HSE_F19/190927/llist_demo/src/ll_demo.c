#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "linked_list.h"

void run_ll_tests();

void print_ll(list_t *l) {
  node_t *e = l->head.next;
  while (e) {
    printf("%d%c", e->x, " \n"[e->next == NULL]);
    e = e->next;
  }
}

int main(int argc, char **argv) {
  if (1 < argc && strcmp(argv[1], "-t") == 0) {
    run_ll_tests();
    return 0;
  }
  /* list_t ll; */
  /* create(&ll); */
  /* push_back(&ll, 1); */
  /* push_back(&ll, 2); */
  /* push_back(&ll, 3); */
  /* push_back(&ll, 4); */
  /* print_ll(&ll); */

  /* insert(&ll, find(&ll, 2), 20); */
  /* print_ll(&ll); */
  /* destroy(&ll); */
}

void run_create_tests();
void run_insert_tests();
void run_erase_tests();
void run_push_back_tests();
void run_find_tests();
void run_get_tests();

void run_ll_tests() {
  run_create_tests();
  run_insert_tests();
  run_erase_tests();
  run_push_back_tests();
  run_find_tests();
  run_get_tests();
}

int is_eq(list_t *l, char *expected) {
  // NB: unsafe
  char buff[1 << 8], *buff_cursor = buff;
  *buff = '\0';
  node_t *e = l->head.next;
  while (e) {
    int res = sprintf(buff_cursor, "%d%c", e->x, " \0"[e->next == NULL]);
    assert(0 < res);
    buff_cursor += res;
    e = e->next;
  }
  return strcmp(buff, expected) == 0;
}

void run_create_tests() {
  {
    list_t ll;
    create(&ll);
    assert(ll.nm == 0);
    assert(is_eq(&ll, ""));
  }
  printf("Create ... OK\n");
}

void run_insert_tests() {
  { // plain insert
    list_t ll;
    create(&ll);
    insert(&ll, &ll.head, 1);
    assert(ll.nm == 1);
    assert(is_eq(&ll, "1"));
    destroy(&ll);
  }
  {
    list_t ll;
    create(&ll);
    insert(&ll, &ll.head, 1);
    insert(&ll, &ll.head, 2);
    insert(&ll, &ll.head, 3);
    assert(ll.nm == 3);
    assert(is_eq(&ll, "3 2 1"));
    destroy(&ll);
  }
  printf("Insert ... OK\n");
}

void run_push_back_tests() {
  {
    list_t ll;
    create(&ll);
    push_back(&ll, 1);
    push_back(&ll, 1);
    push_back(&ll, 1);
    push_back(&ll, 1);
    assert(ll.nm == 4);
    assert(is_eq(&ll, "1 1 1 1"));
    destroy(&ll);
  }
  printf("Push back ... OK\n");
}

void run_find_tests() {
  {
    list_t ll;
    create(&ll);
    assert(find(&ll, 42) == NULL);
    destroy(&ll);
  }
  {
    list_t ll;
    create(&ll);
    push_back(&ll, 1);
    assert(find(&ll, 42) == NULL);
    destroy(&ll);
  }
  {
    list_t ll;
    create(&ll);
    push_back(&ll, 1);
    push_back(&ll, 0);
    push_back(&ll, 42);
    push_back(&ll, 8);
    assert(find(&ll, 42)->x == 42);
    destroy(&ll);
  }
  {
    list_t ll;
    create(&ll);
    push_back(&ll, 42);
    push_back(&ll, 8);
    push_back(&ll, 42);
    assert(find(&ll, 42)->x == 42);
    destroy(&ll);
  }

  printf("Find ... OK\n");
}

void run_get_tests() {
  {
    list_t ll;
    create(&ll);
    push_back(&ll, 1);
    push_back(&ll, 8);
    push_back(&ll, 4);
    assert(get(&ll, 0) == 1);
    assert(get(&ll, 1) == 8);
    assert(get(&ll, 2) == 4);
    destroy(&ll);
  }

  printf("Get ... OK\n");
}

void run_erase_tests() {
  {
    list_t ll;
    create(&ll);
    push_back(&ll, 0);
    push_back(&ll, 8);
    push_back(&ll, 5);
    push_back(&ll, 17);

    erase(&ll, find(&ll, 8));
    assert(is_eq(&ll, "0 8 17"));
    assert(ll.nm == 3);
    destroy(&ll);
  }
  { // erase the first
    list_t ll;
    create(&ll);
    push_back(&ll, 0);
    push_back(&ll, 8);
    erase(&ll, &ll.head);
    assert(is_eq(&ll, "8"));
    assert(ll.nm == 1);
    destroy(&ll);
  }
  { // erase next to the last
    list_t ll;
    create(&ll);
    push_back(&ll, 0);
    push_back(&ll, 8);
    erase(&ll, find(&ll, 8));
    assert(is_eq(&ll, "0 8"));
    assert(ll.nm == 2);
    destroy(&ll);
  }

  printf("Erase ... OK\n");
}
