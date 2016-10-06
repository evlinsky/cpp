#include <iostream>
#include "position.h"

using std::cout;
using std::endl;

int main() {
    intrusive_list list;
    intrusive_list* l = &list;
    init_list(l);

    for (int i = 0; i < 20; ++i)
    {
        int first = 2 * i;
        int second = first + 1;
        add_position(l, first, second);
    }
    show_all_positions(l);

    remove_position(l, 4, 5);
    remove_position(l, 0, 1);
    remove_position(l, 38, 39);
    show_all_positions(l);
    
    remove_all(l);

    return 0;
}
