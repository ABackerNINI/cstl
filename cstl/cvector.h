#pragma once

#ifndef _CSTL_CVECTOR_H_
#define _CSTL_CVECTOR_H_

#include <stdlib.h>//malloc,free,realloc,NULL

#define CSIZE_T unsigned int//size_t

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct _cvector {
        //number of datas
        CSIZE_T size;
        //capacity of data holder
        CSIZE_T capacity;
        //size of each data
        CSIZE_T data_size;
        //data holder,its real size equ capacity * data_size
        void *data;
    }cvector;

    typedef struct _cvector_ {
        //number of datas
        CSIZE_T size;
        //capacity of data holder
        CSIZE_T capacity;
        //size of each data
        CSIZE_T data_size;
        //data holder,its real size equ capacity * data_size
        void *data;
    };


    /** Init/free functions **/


    inline void cvector_init(cvector *vec, CSIZE_T data_size) {
        vec->size = 0;
        vec->capacity = 0;
        vec->data_size = data_size;
        vec->data = NULL;
    }

    inline void cvector_init_by_capacity(cvector *vec, CSIZE_T capacity, CSIZE_T data_size) {
        vec->size = 0;
        vec->capacity = capacity;
        vec->data_size = data_size;
        vec->data = malloc(data_size*capacity);
    }

    inline void cvector_free(cvector *vec) {
        if (vec->data)free(vec->data);
    }


    /** Capacity functions **/


    inline void _cvector_increase_capacity(cvector *vec) {
        if (vec->capacity == 0)vec->capacity = 1;
        else if (vec->capacity == 1)vec->capacity = 2;
        else vec->capacity = vec->capacity + vec->capacity / 2;

        vec->data = realloc(vec->data, vec->data_size*vec->capacity);
    }

    inline void cvector_reserve(cvector *vec, CSIZE_T n) {
        if (vec->capacity < n) {
            vec->capacity = n;
            vec->data = realloc(vec->data, vec->data_size*vec->capacity);
        }
    }

    inline void cvector_shrink_to_fit(cvector *vec);

    inline CSIZE_T cvector_size(cvector *vec) {
        return vec->size;
    }

    inline CSIZE_T cvector_capacity(cvector *vec) {
        return vec->capacity;
    }

    inline int cvector_empty(cvector *vec) {
        return vec->size == 0;
    }


    /** Element access functions **/


    inline void cvector_at(cvector *vec);
    inline void cvector_front(cvector *vec);
    inline void cvector_back(cvector *vec);


    /** Modifier functions **/

    inline void cvector_data(cvector *vec);
    inline void cvector_push_back(cvector *vec);
    inline void cvector_pop_back(cvector *vec);
    inline void cvector_insert(cvector *vec);
    inline void cvector_erase(cvector *vec);
    inline void cvector_swap_element(cvector *vec);
    inline void cvector_clear(cvector *vec) {
        vec->size = 0;
    }

    /** Extension functions **/


    inline void cvector_swap(cvector *vec1, cvector *vec2) {
        //if (vec1 != vec2) {
        cvector tmp = *vec1;
        *vec1 = *vec2;
        *vec2 = tmp;
        //}
    }

#ifdef __cplusplus
}
#endif

#endif//_CSTL_CVECTOR_H_