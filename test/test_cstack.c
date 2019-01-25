#include <stdio.h>
#include "../cstl/cstack.h"

void test_1() {
    cstack stack;
    double *p;
    cstack_init_by_capacity(&stack, 10, sizeof(double));
    p = cstack_push(&stack);
    *p = 1;
    printf("%lf\n", *(double *)cstack_top(&stack));

    p = cstack_push(&stack);
    *p = 2;
    printf("%lf\n", *(double *)cstack_top(&stack));

    p = cstack_push(&stack);
    *p = 3;
    printf("%lf\n", *(double *)cstack_top(&stack));

    printf("%lf\n", *(double *)cstack_pop(&stack));
    printf("%lf\n", *(double *)cstack_pop(&stack));
    printf("%lf\n", *(double *)cstack_pop(&stack));

    cstack_free(&stack);
}

void test_2() {
    cstack stack;
    char *p;
    cstack_init_by_capacity(&stack, 10, sizeof(char));
    p = cstack_push(&stack);
    *p = 'a';
    printf("%c\n", *(char *)cstack_top(&stack));

    p = cstack_push(&stack);
    *p = 'b';
    printf("%c\n", *(char *)cstack_top(&stack));

    p = cstack_push(&stack);
    *p = 'c';
    printf("%c\n", *(char *)cstack_top(&stack));

    printf("%c\n", *(char *)cstack_pop(&stack));
    printf("%c\n", *(char *)cstack_pop(&stack));
    printf("%c\n", *(char *)cstack_pop(&stack));

    cstack_free(&stack);
}

struct foo {
    int a;
    double b;
};

void test_3() {
    cstack stack;
    struct foo *p;
    cstack_init(&stack, sizeof(struct foo));

    p = cstack_push(&stack);
    p->a = 1; p->b = 1;
    p = cstack_top(&stack);
    printf("%d %lf\n", p->a, p->b);

    p = cstack_push(&stack);
    p->a = 2; p->b = 2;
    p = cstack_top(&stack);
    printf("%d %lf\n", p->a, p->b);

    p = cstack_push(&stack);
    p->a = 3; p->b = 3;
    p = cstack_top(&stack);
    printf("%d %lf\n", p->a, p->b);

    p = cstack_push(&stack);
    p->a = 4; p->b = 4;
    p = cstack_top(&stack);
    printf("%d %lf\n", p->a, p->b);

    p = cstack_push(&stack);
    p->a = 5; p->b = 5;
    p = cstack_top(&stack);
    printf("%d %lf\n", p->a, p->b);

    p = cstack_pop(&stack);
    printf("%d %lf\n", p->a, p->b);
    p = cstack_pop(&stack);
    printf("%d %lf\n", p->a, p->b);
    p = cstack_pop(&stack);
    printf("%d %lf\n", p->a, p->b);
    p = cstack_pop(&stack);
    printf("%d %lf\n", p->a, p->b);
    p = cstack_pop(&stack);
    printf("%d %lf\n", p->a, p->b);

    cstack_free(&stack);
}

int main() {
    printf("test_1\n");
    test_1();

    printf("test_2\n");
    test_2();

    printf("test_3\n");
    test_3();

    return 0;
}