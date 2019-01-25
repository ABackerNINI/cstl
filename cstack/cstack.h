#pragma once

#ifndef _CSTL_CSTACK_H_
#define _CSTL_CSTACK_H_

#include <stdlib.h>//malloc,free,realloc,NULL

#define CSIZE_T unsigned int//size_t

#ifdef __cplusplus
extern "C" {
#endif

    //cstack
    typedef struct _cstack {
        //number of datas
        CSIZE_T size;
        //capacity of data holder
        CSIZE_T capacity;
        //size of each data
        CSIZE_T data_size;
        //data holder,its real size equ capacity * data_size
        void *data;
    }cstack;


    /** init/free functions **/


    //cstack_init
    inline void cstack_init(cstack *stack, CSIZE_T data_size) {
        stack->size = 0;
        stack->capacity = 0;
        stack->data_size = data_size;
        stack->data = NULL;
    }

    //cstack_init_by_capacity
    inline void cstack_init_by_capacity(cstack *stack, CSIZE_T capacity, CSIZE_T data_size) {
        stack->size = 0;
        stack->capacity = capacity;
        stack->data_size = data_size;
        stack->data = malloc(data_size*capacity);
    }

    //cstack_free
    inline void cstack_free(cstack *stack) {
        if (stack->data)free(stack->data);
    }


    /** basic functions -1 **/


    inline void cstack_reserve(cstack *stack, CSIZE_T n) {
        if (stack->capacity < n) {
            stack->capacity = n;
            stack->data = realloc(stack->data, stack->data_size*stack->capacity);
        }
    }

    //cstack_increase_capacity
    inline void cstack_increase_capacity(cstack *stack) {
        if (stack->capacity == 0)stack->capacity = 1;
        else if (stack->capacity == 1)stack->capacity = 2;
        else stack->capacity = stack->capacity + stack->capacity / 2;

        stack->data = realloc(stack->data, stack->data_size*stack->capacity);
    }

    //cstack_size
    inline CSIZE_T cstack_size(cstack *stack) {
        return stack->size;
    }

    //cstack_empty
    inline int cstack_empty(cstack *stack) {
        return stack->size == 0;
    }

    //cstack_capacity
    inline CSIZE_T cstack_capacity(cstack *stack) {
        return stack->capacity;
    }

    //cstack_clear
    inline void cstack_clear(cstack *stack) {
        stack->size = 0;
    }


    /** basic functions -2 **/


    //cstack_push
    inline void *cstack_push(cstack *stack) {
        if (stack->size == stack->capacity)cstack_increase_capacity(stack);
        return (void *)((char *)stack->data + (stack->data_size*stack->size++));
    }

    //cstack_pop
    inline void *cstack_pop(cstack *stack) {
        return (void *)((char *)stack->data + (stack->data_size*(--stack->size)));
    }

    //cstack_top
    inline void *cstack_top(cstack *stack) {
        return (void *)((char *)stack->data + (stack->data_size*(stack->size - 1)));
    }


    /** extension functions **/


    //cstack_swap
    inline void cstack_swap(cstack *stack1, cstack *stack2) {
        cstack tmp = *stack1;
        *stack1 = *stack2;
        *stack2 = tmp;
    }

#ifdef __cplusplus
    }
#endif

#endif//_CSTL_CSTACK_H_