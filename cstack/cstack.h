#pragma once

#ifndef _CSTL_CSTACK_H_
#define _CSTL_CSTACK_H_

#include <stdlib.h>//malloc,free,realloc,NULL

#define CSIZE_T unsigned int//size_t

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct _cstack {
        CSIZE_T size;
        CSIZE_T capacity;
        CSIZE_T data_size;
        void *data;
    }cstack;


    /** init/free functions **/


    inline void cstack_init(cstack *stack, CSIZE_T data_size) {
        stack->size = 0;
        stack->capacity = 0;
        stack->data_size = data_size;
        stack->data = NULL;
    }

    inline void cstack_init_by_capacity(cstack *stack, CSIZE_T capacity, CSIZE_T data_size) {
        stack->size = 0;
        stack->capacity = capacity;
        stack->data_size = data_size;
        stack->data = malloc(data_size*capacity);
    }

    inline void cstack_free(cstack *stack) {
        if (stack->data)free(stack->data);
    }


    /** basic functions -1 **/

    inline void cstack_increase_capacity(cstack *stack) {
        if (stack->capacity == 0)stack->capacity = 1;
        else if (stack->capacity == 1)stack->capacity = 2;
        else stack->capacity = stack->capacity + stack->capacity / 2;

        stack->data = realloc(stack->data, stack->data_size*stack->capacity);
    }

    inline CSIZE_T cstack_size(cstack *stack) {
        return stack->size;
    }

    inline int cstack_empty(cstack *stack) {
        return stack->size == 0;
    }

    inline CSIZE_T cstack_capacity(cstack *stack) {
        return stack->capacity;
    }

    inline void cstack_clear(cstack *stack) {
        stack->size = 0;
    }

    /** basic functions -2 **/


    inline void *cstack_push(cstack *stack) {
        if (stack->size == stack->capacity)cstack_increase_capacity(stack);
        return (void *)((char *)stack->data + (stack->data_size*stack->size++));
    }

    inline void *cstack_pop(cstack *stack) {
        return (void *)((char *)stack->data + (stack->data_size*(--stack->size)));
    }

    inline void *cstack_top(cstack *stack) {
        return (void *)((char *)stack->data + (stack->data_size*(stack->size - 1)));
    }


    /** extension functions **/


    inline void cstack_swap(cstack *stack1, cstack *stack2) {
        cstack tmp = *stack1;
        *stack1 = *stack2;
        *stack2 = tmp;
    }

#ifdef __cplusplus
}
#endif

#endif//_CSTL_CSTACK_H_