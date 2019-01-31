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
        //next
        struct _cforward_list_node *next;
        //data holder,it's not really char type,but depending on the data_size
        //cast to the real type you need like '*(foo *)&data'
        char data;
    }cforward_list_node;

    //cforward_list
    typedef struct _cforward_list {
        //the first node,keep NULL while size is zero
        cforward_list_node *head;
        //the last node,indeterminate while size is zero
        cforward_list_node *tail;
        //number of nodes
        CSIZE_T size;
        //real size of the data holder
        CSIZE_T data_size;
    }cforward_list;


    /** Init/free functions **/


    //cforward_list_init
    inline void cforward_list_init(cforward_list *list, CSIZE_T data_size) {
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
        list->data_size = data_size;
    }

    //cforward_list_free
    //free all nodes,[head] will be set to NULL,[tail] and [size] are indeterminate
    inline void cforward_list_free(cforward_list *list) {
        cforward_list_node *tmp;

        while (list->head) {
            tmp = list->head;

            list->head = list->head->next;

            free(tmp);
        }
        //list->size = 0;
    }


    /** Capacity functions **/


    //cforward_list_size
    inline CSIZE_T cforward_list_size(cforward_list *list) {
        return list->size;
    }

    //cforward_list_empty
    inline int cforward_list_empty(cforward_list *list) {
        return list->size == 0;
    }


    /** Element access functions **/


    inline void *cforward_list_front();
    inline void *cforward_list_back();


    /** Modifier functions **/


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

    //cforward_list_swap_node
    inline void cforward_list_swap_node(cforward_list_node *node1, cforward_list_node *node2) {
        if (node1 != node2) {
            cforward_list_node tmp = *node1;
            *node1 = *node2;
            *node2 = tmp;
        }
    }

    inline void cforward_list_remove();
    inline void cforward_list_remove_if();
    inline void cforward_list_unique();
    inline void cforward_list_sort();
    inline void cforward_list_reverse();
    inline void cforward_list_resize();

    //cforward_list_clear
    //free all nodes
    inline void cforward_list_clear(cforward_list *list) {
        cforward_list_free(list);
        list->size = 0;
    }

    inline void cforward_list_copy();
    inline void cforward_list_merge();


    /** extension functions **/

    inline void cforward_list_swap(cforward_list *list1, cforward_list *list2) {
        if (list1 != list2) {
            cforward_list tmp;
            tmp = *list1;
            *list1 = *list2;
            *list2 = tmp;
        }
    }


    //not recommended
    //void clist_pop_back(cforward_list *list);
    //not recommended
    //void clist_erase(cforward_list *list);

#ifdef __cplusplus
}
#endif

#endif//_CSTL_CFORWARD_LIST_H_
