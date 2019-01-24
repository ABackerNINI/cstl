#pragma once

#ifndef _CSTL_CSTRING_H_
#define _CSTL_CSTRING_H_


#include <stdlib.h>//malloc,realloc
#include <string.h>//memcpy,strcmp,strncmp

#define CSIZE_T unsigned int//size_t

#ifdef __cplusplus
extern "C" {
#endif

    //struct cstring
    typedef struct _cstring {
        CSIZE_T size;//length of the string
        CSIZE_T capacity;//capacity of data,usually equ to size + 1(reserve for '\0')
        char *data;//it is not always '\0' at the end of the string,call cstring_c_str() to append '\0'
    }cstring;


    /** init/free functions **/


    //cstring_init
    inline void cstring_init(cstring *s) {
        s->size = 0;
        s->capacity = 0;
        s->data = NULL;
    }

    //cstring_init_by_capacity
    inline void cstring_init_by_capacity(cstring *s, CSIZE_T capacity) {
        s->size = 0;
        s->capacity = capacity + 1;
        s->data = (char *)malloc(sizeof(char)*s->capacity);
    }

    //cstring_init_by_substr
    inline void cstring_init_by_substr(cstring *s, const char *str, CSIZE_T begin, CSIZE_T n) {
        s->size = n;
        s->capacity = n + 1;
        s->data = (char *)malloc(sizeof(char)*s->capacity);
        memcpy(s->data, str + begin, sizeof(char)*n);
    }

    //cstring_init_by_cstr_n
    inline void cstring_init_by_cstr_n(cstring *s, const char *str, CSIZE_T n) {
        cstring_init_by_substr(s, str, 0, n);
    }

    //cstring_init_by_cstr
    inline void cstring_init_by_cstr(cstring *s, const char *str) {
        cstring_init_by_cstr_n(s, str, (CSIZE_T)strlen(str));
    }

    //cstring_free
    inline void cstring_free(cstring *s) {
        if (s->data)free(s->data);
    }


    /** functions **/


    //cstring_reserve
    inline void cstring_reserve(cstring *s, CSIZE_T n) {
        if (s->capacity < n + 1) {
            s->capacity = n + 1;
            s->data = (char *)realloc(s->data, sizeof(char)*s->capacity);
        }
    }

    //cstring_shrink_to_fit
    inline void cstring_shrink_to_fit(cstring *s) {
        if (s->size < s->capacity) {
            char *tmp = (char *)malloc(sizeof(char)*(s->size + 1));
            memcpy(tmp, s->data, sizeof(char)*s->size);
            s->data = tmp;
        }
    }

    //cstring_c_str
    inline char *cstring_c_str(cstring *s) {
        s->data[s->size] = '\0';
        return s->data;
    }

    //cstring_copy
    inline cstring cstring_copy(cstring *s) {
        cstring tmp;
        //cstring_init_by_cstr(&tmp, cstring_c_str(s), s->size);
        cstring_init_by_substr(&tmp, s->data, 0, s->size);
        return tmp;
    }

    //cstring_substr
    //remember to call cstring_free,do NOT use as an intermediate variable
    inline cstring cstring_substr(cstring *s, CSIZE_T begin, CSIZE_T n) {
        cstring tmp;
        cstring_init_by_substr(&tmp, s->data, begin, n);
        return tmp;
    }

    //cstring_swap
    inline void cstring_swap(cstring *s, CSIZE_T n1, CSIZE_T n2) {
        char c = s->data[n1];
        s->data[n1] = s->data[n2];
        s->data[n2] = c;
    }

    //cstring_at
    inline char cstring_at(cstring *s, CSIZE_T n) {
        return s->data[n];
    }

    //cstring_size
    inline CSIZE_T cstring_size(cstring *s) {
        return s->size;
    }

    //cstring_empty
    inline int cstring_empty(cstring *s) {
        return s->size == 0;
    }

    //cstring_capacity
    inline CSIZE_T cstring_capacity(cstring *s) {
        return s->capacity;
    }

    //cstring_clear
    inline void cstring_clear(cstring *s) {
        s->size = 0;
    }


    /** push_back/pop_back/insert/erase/replace/find/compare functions **/


    //cstring_push_back_char
    inline void cstring_push_back_char(cstring *s, char c) {
        cstring_reserve(s, s->size + 1);
        s->data[s->size++] = c;
        //s->data[s->size] = '\0';
    }

    //cstring_push_back_substr
    inline void cstring_push_back_substr(cstring *s, const char *str, CSIZE_T begin, CSIZE_T n) {
        cstring_reserve(s, s->size + n);
        memcpy(s->data + s->size, str + begin, sizeof(char)*n);
        s->size += n;
    }

    //cstring_pop_back_n
    inline void cstring_pop_back_n(cstring *s, CSIZE_T n) {
        s->size -= n;
    }

    //cstring_insert_char
    inline void cstring_insert_char(cstring *s, CSIZE_T pos, char c) {
        cstring_reserve(s, s->size + 1);
        //memcpy(s->data + pos + 1, s->data + pos, sizeof(char)*(s->size - pos));
        CSIZE_T i, l = pos + 1;
        for (i = s->size + 1; i >= l; --i) {
            s->data[i] = s->data[i - 1];
        }
        s->data[pos] = c;
        ++s->size;
    }

    //cstring_insert_substr
    inline void cstring_insert_substr(cstring *s, CSIZE_T pos, const char *str, CSIZE_T begin, CSIZE_T n) {
        cstring_reserve(s, s->size + n);
        //memcpy(s->data + pos + n, s->data + pos, sizeof(char)*(s->size - pos));
        CSIZE_T i, l = pos + n;
        for (i = s->size + n; i >= l; --i) {
            s->data[i] = s->data[i - n];
        }
        memcpy(s->data + pos, str + begin, sizeof(char)*n);
        s->size += n;
    }

    //cstring_erase
    inline void cstring_erase(cstring *s, CSIZE_T begin, CSIZE_T n) {
        memcpy(s->data + begin, s->data + begin + n, sizeof(char)*(s->size - begin - n));
        s->size -= n;
    }

    //cstring_replace_by_char
    inline void cstring_replace_by_char(cstring *s, CSIZE_T begin, CSIZE_T n, char c) {
        CSIZE_T i, r = begin + n;
        for (i = begin; i < r; ++i) {
            s->data[i] = c;
        }
    }

    //cstring_replace_by_substr
    inline void cstring_replace_by_substr(cstring *s, CSIZE_T begin1, CSIZE_T n1, const char *str, CSIZE_T begin2, CSIZE_T n2) {
        cstring_reserve(s, s->size - n1 + n2);
        //memcpy(s->data + begin1 + n1, s->data + begin1 + n2, sizeof(char)*(s->size - begin1 - n2));
        if (n1 < n2) {
            CSIZE_T k = n2 - n1;
            CSIZE_T i, l = begin1 + k;
            for (i = s->size + k; i >= l; --i) {
                s->data[i] = s->data[i - k];
            }
        } else if (n1 > n2) {
            memcpy(s->data + begin1 + n2, s->data + begin1 + n1, sizeof(char)*(s->size - begin1 - n1));
        }

        memcpy(s->data + begin1, str + begin2, sizeof(char)*n2);
        s->size = s->size - n1 + n2;
    }

    inline int cstring_rfind();

    //cstring_find_char
    inline int cstring_find_char(cstring *s, char c) {
        CSIZE_T i;
        for (i = 0; i < s->size; ++i) {
            if (s->data[i] == c) {
                return i;
            }
        }
        return -1;
    }

    //cstring_substr_find_substr
    inline int cstring_substr_find_substr(cstring *s, CSIZE_T begin1, CSIZE_T n1, const char *str, CSIZE_T begin2, CSIZE_T n2) {
        CSIZE_T i, j, f, r = begin1 + n1 - n2;
        for (i = begin1; i < r; ++i) {
            f = 1;
            for (j = 0; j < n2; ++j) {
                if (s->data[i + j] != str[begin2 + j]) {
                    f = 0;
                    break;
                }
            }
            if (f)return i;
        }
        return -1;
    }

    //cstring_compare_substr_with_substr
    inline int cstring_compare_substr_with_substr(cstring *s, CSIZE_T begin1, CSIZE_T n1, const char *str, CSIZE_T begin2, CSIZE_T n2) {
        const char *str1 = cstring_c_str(s);
        return strncmp(str1 + begin1, str + begin2, n1 < n2 ? n1 : n2);
    }


    /** extension functions **/


    //cstring_push_back_cstr_n
    inline void cstring_push_back_cstr_n(cstring *s, const char *str, CSIZE_T n) {
        cstring_push_back_substr(s, str, 0, n);
    }

    //cstring_push_back_cstr
    inline void cstring_push_back_cstr(cstring *s, const char *str) {
        cstring_push_back_cstr_n(s, str, (CSIZE_T)strlen(str));
    }

    //cstring_insert_cstr_n
    inline void cstring_insert_cstr_n(cstring *s, CSIZE_T pos, const char *str, CSIZE_T n) {
        cstring_insert_substr(s, pos, str, 0, n);
    }

    //cstring_insert_cstr
    inline void cstring_insert_cstr(cstring *s, CSIZE_T pos, const char *str) {
        cstring_insert_cstr_n(s, pos, str, (CSIZE_T)strlen(str));
    }

    //cstring_replace_by_cstr_n
    inline void cstring_replace_by_cstr_n(cstring *s, CSIZE_T begin1, CSIZE_T n1, const char *str, CSIZE_T n2) {
        cstring_replace_by_substr(s, begin1, n1, str, 0, n2);
    }

    //cstring_replace_by_cstr
    inline void cstring_replace_by_cstr(cstring *s, CSIZE_T begin1, CSIZE_T n1, const char *str) {
        cstring_replace_by_cstr_n(s, begin1, n1, str, (CSIZE_T)strlen(str));
    }

    //cstring_find_substr
    inline int cstring_find_substr(cstring *s, const char *str, CSIZE_T begin2, CSIZE_T n2) {
        return cstring_substr_find_substr(s, 0, s->size, str, begin2, n2);
    }

    //cstring_find_cstr_n
    inline int cstring_find_cstr_n(cstring *s, const char *str, CSIZE_T n2) {
        return cstring_find_substr(s, str, 0, n2);
    }

    //cstring_find_cstr
    inline int cstring_find_cstr(cstring *s, const char *str) {
        return cstring_find_cstr_n(s, str, (CSIZE_T)strlen(str));
    }

    //cstring_find
    inline int cstring_find(cstring *s1, cstring *s2) {
        return cstring_substr_find_substr(s1, 0, s1->size, cstring_c_str(s2), 0, s2->size);
    }

    //cstring_compare_substr_with_cstr_n
    inline int cstring_compare_substr_with_cstr_n(cstring *s, CSIZE_T begin1, CSIZE_T n1, const char *str, CSIZE_T n2) {
        return cstring_compare_substr_with_substr(s, begin1, n1, str, 0, n2);
    }

    //cstring_compare_substr_with_cstr
    inline int cstring_compare_substr_with_cstr(cstring *s, CSIZE_T begin1, CSIZE_T n1, const char *str) {
        return cstring_compare_substr_with_cstr_n(s, begin1, n1, str, (CSIZE_T)strlen(str));
    }

    //cstring_compare_with_substr
    inline int cstring_compare_with_substr(cstring *s, const char *str, CSIZE_T begin2, CSIZE_T n2) {
        return cstring_compare_substr_with_substr(s, 0, s->size, str, begin2, n2);
    }

    //cstring_compare_with_cstr_n
    inline int cstring_compare_with_cstr_n(cstring *s, const char *str, CSIZE_T n2) {
        return cstring_compare_with_substr(s, str, 0, n2);
    }

    //cstring_compare_with_cstr
    inline int cstring_compare_with_cstr(cstring *s, const char *str) {
        return cstring_compare_with_cstr_n(s, str, (CSIZE_T)strlen(str));
    }

    //cstring_compare
    inline int cstring_compare(cstring *s1, cstring *s2) {
        const char *str1 = cstring_c_str(s1);
        const char *str2 = cstring_c_str(s2);
        return strcmp(str1, str2);
    }

#ifdef __cplusplus
}
#endif

#endif//_CSTL_CSTRING_H_