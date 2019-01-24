#include <stdio.h>
#include "../cforward_list/cforward_list.h"

void print_list(cforward_list *list) {
    cforward_list_node *node = list->head;
    while (node) {
        printf("%lf ", *(double *)&node->data);
        node = node->next;
    }
    printf("\n");
}

void test_1() {
    typedef double type;

    cforward_list list;
    cforward_list_init(&list, sizeof(type));

    type *p;

    p = cforward_list_push_back(&list);
    *p = 1;
    print_list(&list);
    p = cforward_list_push_back(&list);
    *p = 2;
    print_list(&list);
    p = cforward_list_push_back(&list);
    *p = 3;
    print_list(&list);
    p = cforward_list_push_back(&list);
    *p = 4;
    print_list(&list);

    cforward_list_pop_front(&list);
    print_list(&list);
    cforward_list_pop_front(&list);
    print_list(&list);
    cforward_list_pop_front(&list);
    print_list(&list);
    cforward_list_pop_front(&list);
    print_list(&list);

    p = cforward_list_push_back(&list);
    *p = 1;
    print_list(&list);
    p = cforward_list_push_back(&list);
    *p = 2;
    print_list(&list);
    p = cforward_list_push_back(&list);
    *p = 3;
    print_list(&list);
    p = cforward_list_push_back(&list);
    *p = 4;
    print_list(&list);

    cforward_list_pop_front(&list);
    print_list(&list);
    cforward_list_pop_front(&list);
    print_list(&list);
    cforward_list_pop_front(&list);
    print_list(&list);
    cforward_list_pop_front(&list);
    print_list(&list);
}


int main() {
    test_1();

    return 0;
}