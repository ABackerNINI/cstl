#pragma once

#ifndef _CSTL_CFORWARD_LIST_H_
#define _CSTL_CFORWARD_LIST_H_

#include <stdlib.h>//malloc,free,NULL

#define CSIZE_T unsigned int//size_t

#ifdef __cplusplus
extern "C" {
#endif

    //cforward_list_node
    typedef struct _cforward_list_node {
        struct _cforward_list_node *next;//next.
        char data;//data holder,but it's not really char type,but depending on the data_size,cast to the real type you need like '*(foo *)&data'.
    }cforward_list_node;

    //cforward_list
    typedef struct _cforward_list {
        cforward_list_node *head;//the first node,keep NULL while size is zero.
        cforward_list_node *tail;//the last node,indeterminate while size is zero.
        CSIZE_T size;//number of nodes.
        CSIZE_T data_size;//real size of the data holder.
    }cforward_list;


    /** init/free functions **/


    //cforward_list_init
    inline void cforward_list_init(cforward_list *list, CSIZE_T data_size) {
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
        list->data_size = data_size;
    }

    //cforward_list_free
    //free all nodes,[head] will be set to NULL,[tail] and [size] are indeterminate.
    inline void cforward_list_free(cforward_list *list) {
        cforward_list_node *tmp;

        while (list->head) {
            tmp = list->head;

            list->head = list->head->next;

            free(tmp);
        }
        //list->size = 0;
    }


    /** functions **/


    //cforward_list_swap
    inline void cforward_list_swap(cforward_list_node *node1, cforward_list_node *node2) {
        if (node1 != node2) {
            cforward_list_node tmp = *node1;
            *node1 = *node2;
            *node2 = tmp;
        }
    }

    //cforward_list_clear
    //free all nodes
    inline void cforward_list_clear(cforward_list *list) {
        cforward_list_free(list);
        list->size = 0;
    }

    //cforward_list_size
    inline CSIZE_T cforward_list_size(cforward_list *list) {
        return list->size;
    }

    //cforward_list_empty
    inline int cforward_list_empty(cforward_list *list) {
        return list->size == 0;
    }


    /** push_back/push_front/pop_front/insert_after/erase_after functions **/


    //cforward_list_push_back
    inline void *cforward_list_push_back(cforward_list *list) {
        cforward_list_node *new_node = malloc(sizeof(struct _cforward_list_node *) + list->data_size);
        new_node->next = NULL;
        if (list->head == NULL) {
            list->head = list->tail = new_node;
        } else {
            list->tail->next = new_node;
            list->tail = new_node;
        }
        ++list->size;

        return &(new_node->data);
    }

    //cforward_list_push_front
    inline void *cforward_list_push_front(cforward_list *list) {
        cforward_list_node *new_node = malloc(sizeof(struct _cforward_list_node *) + list->data_size);
        new_node->next = list->head;
        if (list->head == NULL) {
            list->tail = new_node;
        }
        list->head = new_node;

        ++list->size;

        return &(new_node->data);
    }

    //cforward_list_pop_front
    inline void cforward_list_pop_front(cforward_list *list) {
        cforward_list_node *tmp = list->head;
        list->head = list->head->next;

        free(tmp);

        --list->size;
    }

    //cforward_list_insert_after
    inline void *cforward_list_insert_after(cforward_list *list, cforward_list_node *node) {
        cforward_list_node *new_node = malloc(sizeof(struct _cforward_list_node *) + list->data_size);

        //if node is the tail
        if (node == list->tail) {
            list->tail = new_node;
        }

        new_node->next = node->next;
        node->next = new_node;

        ++list->size;

        return &(new_node->data);
    }

    //cforward_list_erase_after
    inline void cforward_list_erase_after(cforward_list *list, cforward_list_node *node) {
        cforward_list_node *tmp = node->next;

        //if node->next is the tail
        if (node->next == list->tail) {
            list->tail = node;
        }

        node->next = node->next->next;
        free(tmp);

        --list->size;
    }


    /** extension functions **/


    void cforward_list_remove();
    void cforward_list_remove_if();
    void cforward_list_unique();
    void cforward_list_merge();
    void cforward_list_sort();
    void cforward_list_reverse();
    void cforward_list_copy();
    void cforward_list_resize();

    //not recommended
    //void clist_pop_back(cforward_list *list);
    //not recommended
    //void clist_erase(cforward_list *list);

#ifdef __cplusplus
}
#endif

#endif//_CSTL_CFORWARD_LIST_H_
