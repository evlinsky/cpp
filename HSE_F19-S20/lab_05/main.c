#include "point_list.h"

int main() {
    intrusive_list list;
    intrusive_list* l = &list;
    init_list(l);

    for (int i = 0; i < 20; ++i)
    {
        int first = 2 * i;
        int second = first + 1;
        add_point(l, first, second);
    }
    show_all_points(l);

    remove_point(l, 4, 5);
    remove_point(l, 0, 1);
    remove_point(l, 38, 39);
    show_all_points(l);
    
    remove_all_points(l);

    return 0;
}
