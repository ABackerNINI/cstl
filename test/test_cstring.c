#include <stdio.h>
#include "../cstl/cstring.h"

void test_1() {
    cstring s;
    cstring_init_by_cstr(&s, "123");
    printf("%s\n", cstring_c_str(&s));

    cstring_push_back_char(&s, '4');
    printf("%s\n", cstring_c_str(&s));

    cstring_push_back_cstr(&s, "567");
    printf("%s\n", cstring_c_str(&s));

    cstring_insert_cstr(&s, 2, "000");
    printf("%s\n", cstring_c_str(&s));

    cstring_insert_cstr(&s, 0, "111");
    printf("%s\n", cstring_c_str(&s));

    cstring_replace_by_substr(&s, 1, 1, "222", 0, 3);
    printf("%s\n", cstring_c_str(&s));

    cstring_replace_by_substr(&s, 0, 4, "333", 0, 3);
    printf("%s\n", cstring_c_str(&s));

    printf("%d\n", cstring_find_cstr(&s, "3456"));

    cstring_shrink_to_fit(&s);

    cstring_free(&s);
}

int main() {
    test_1();

    return 0;
}