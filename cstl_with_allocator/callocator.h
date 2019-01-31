#pragma once

#ifndef _CSTL_CALLOCATOR_H_
#define _CSTL_CALLOCATOR_H_

#define CSIZE_T unsigned int//size_t

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct _callocator {
        void *(*allocate)(CSIZE_T n);
        void(*deallocate)(void *p, CSIZE_T n);
        void(*construct)(void *p);
        void(*destroy)(void *p);
    }callocator;

#ifdef __cplusplus
}
#endif

#endif//_CSTL_CALLOCATOR_H_