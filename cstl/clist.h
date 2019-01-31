#pragma once

#ifndef _CSTL_CLIST_H_
#define _CSTL_CLIST_H_

#ifndef _C_STL_TYPE_
#define _C_STL_TYPE_ void *
#endif

#ifndef _C_STL_MALLOC_
#define _C_STL_MALLOC_ _c_stl_malloc
#endif

#ifndef _C_STL_FREE_
#define _C_STL_FREE_ _c_stl_free
#endif

#ifndef NULL
#define NULL 0
#endif

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct _clist_node {
        _C_STL_TYPE_ data;
        struct _clist_node *next;
    }clist_node;

    typedef struct _clist {
        clist_node *head;
        clist_node *tail;
        unsigned int size;
    }clist;

    inline clist_node *_c_stl_malloc() {
        return (clist_node *)malloc(sizeof(clist_node));
    }

    inline void _c_stl_free(clist_node *node) {
        free(node);
    }

    void clist_init(clist *list);

    _C_STL_TYPE_ *clist_push_back(clist *list);

    _C_STL_TYPE_ *clist_push_front(clist *list);

    void clist_pop_front(clist *list);

    //not recommended
    void clist_pop_back(clist *list);

    //not recommended
    _C_STL_TYPE_ *clist_insert(clist *list);

    _C_STL_TYPE_ *clist_insert_after(clist_node *node);

    //not recommended,consider 
    void clist_erase(clist *list);

    void clist_swap(clist_node *node1, clist_node *node2);

    void clist_merge();
    void clist_unique();
    void clist_sort();
    void clist_clear();
    void clist_remove();

    unsigned int clist_size(clist *list);

    int clist_empty(clist *list);

#ifdef __cplusplus
}
#endif

#endif//_CSTL_CLIST_H_
