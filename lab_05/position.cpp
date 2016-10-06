#include <iostream>
#include <cstddef>
#include "position.h"

using std::cout;
using std::endl;

#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

position_node *get_position(intrusive_node *node) {
    return container_of(node, position_node, node);
}

bool match_position(intrusive_node *node, int x, int y) {
    position_node *pnode = get_position(node);
    return pnode->x == x && pnode->y == y;
}

void delete_position(intrusive_list *list, intrusive_node *node) {
    remove_node(list, node);
    delete get_position(node);
}

void print_position(intrusive_node *node) {
    position_node *pnode = get_position(node);
    cout << '(' << pnode->x << ", " << pnode->y << ')';
}


void remove_position(intrusive_list *list, int x, int y) {
    intrusive_node *head = &list->head;
    intrusive_node *node = head->next;

    while (node != head) {
        intrusive_node *next = node->next;

        if (match_position(node, x, y))
            delete_position(list, node);

        node = next;
    }
}

void add_position(intrusive_list *list, int x, int y) {
    position_node *pnode = new position_node(x, y);
    add_node(list, &pnode->node);
}

void show_all_positions(intrusive_list *list) {
    intrusive_node *head = &list->head;
    intrusive_node *node = head->next;

    cout << get_length(list) << ": ";

    for (; node != head; node = node->next) {
        print_position(node);
        cout << " ";
    }

    cout << endl;
}

// should be called delete_all
void remove_all(intrusive_list *list) {
    while (list->head.next != &list->head)
        delete_position(list, list->head.next);
}
