#include <stdio.h>
#include <memory.h>
#include "../cstl/cvector.h"

void test_1() {

}

struct A {
    int *a;
};

struct B {
    struct A base;
    int b;
};

void print_a(struct A *a) {
    printf("%d\n", a->a);
}

int main() {
    struct B b;
    b.base.a = 1;
    print_a(&b.base);


    printf("test_1\n");
    test_1();

    //printf("test_2\n");
    //test_2();

    //printf("test_3\n");
    //test_3();

    return 0;
}