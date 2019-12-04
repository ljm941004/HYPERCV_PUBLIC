/*************************************************************************
	> File Name: core/include/core/hypercvvector.h
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/

#ifndef __HYPERCV_VECTOR_H__
#define __HYPERCV_VECTOR_H__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <assert.h>

#ifndef MALLOC
    #define MALLOC malloc
#endif /* MALLOC */

#ifndef REALLOC
    #define REALLOC realloc
#endif /* REALLOC */

#ifndef MEMCPY
    #define MEMCPY memcpy
#endif /* MEMCPY */

#ifndef ASSERT
    #define ASSERT assert
#endif /* ASSERT */

#ifndef MFREE
    #define MFREE free
#endif /* MFREE */


#ifndef __HYPERCV_VECTOR_MALLOC_CHECK
#define __HYPERCV_VECTOR_MALLOC_CHECK(__ptr_in)                                 \
do {                                                                           \
    if(!(__ptr_in))                                                            \
    {                                                                          \
        fprintf(stderr, "fatal: memory allocation faild in function %s(), "    \
                        "file: %s, line: %d. exit.\n",                         \
                __FUNCTION__, __FILE__, __LINE__);                             \
        exit(1);                                                               \
    }                                                                          \
} while(0)
#endif


#define HYPERCV_VECTOR_DECLARE(__vector_type, type)                             \
struct __vector_type                                                           \
{                                                                              \
    type *data;                                                                \
    size_t size;                                                               \
                                                                               \
    size_t __allocatedLength;                                                  \
} typedef __vector_type                                                        \


#define HYPERCV_VECTOR_ALLOC(__vector_type, __vector_in,                        \
                            __init_size, __type_name)                          \
do {                                                                           \
    if((__init_size) == 0)                                                     \
        ASSERT(!"fatal: HYPERCV_VECTOR: initial size of a vector cannot be 0.");\
                                                                               \
    __vector_type *__vector_ =                                                 \
        ( __vector_type *)MALLOC(sizeof(__vector_type));                       \
    __HYPERCV_VECTOR_MALLOC_CHECK(__vector_);                                   \
                                                                               \
    __vector_->data =                                                          \
        (__type_name *)MALLOC(sizeof(__type_name) * (__init_size));            \
    __HYPERCV_VECTOR_MALLOC_CHECK(__vector_->data);                             \
                                                                               \
    __vector_->__allocatedLength = (__init_size);                              \
    __vector_->size = 0;                                                       \
                                                                               \
    (__vector_in) = __vector_;                                                 \
} while(0)


#define HYPERCV_VECTOR_PUSH_BACK(__vector_in, __data_in, __type_name)           \
do {                                                                           \
    if((__vector_in)->__allocatedLength - 1 < (__vector_in)->size)             \
    {                                                                          \
        (__vector_in)->__allocatedLength *= 2;                                 \
                                                                               \
        __type_name *__realloced_address_ =                                    \
            (__type_name *)REALLOC((__vector_in)->data,                        \
            sizeof(__type_name) * (__vector_in)->__allocatedLength);           \
                                                                               \
            __HYPERCV_VECTOR_MALLOC_CHECK(__realloced_address_);                \
                                                                               \
        (__vector_in)->data = __realloced_address_;                            \
    }                                                                          \
                                                                               \
    (__vector_in)->data[(__vector_in)->size] = (__data_in);                    \
    (__vector_in)->size++;                                                     \
                                                                               \
} while(0)


#define HYPERCV_VECTOR_ERASE_AT(__vector, __element_index, __type_name)         \
do {                                                                           \
    if((__element_index > (__vector)->size - 1) || (__element_index) < 0)      \
        ASSERT(!"fatal: HYPERCV_VECTOR: out of range.");                        \
                                                                               \
    MEMCPY((__vector)->data + (__element_index),                               \
           (__vector)->data + (__element_index) + 1,                           \
           sizeof(__type_name) * ((__vector)->size - (__element_index) - 1));  \
    (__vector)->size--;                                                        \
} while(0)


#define HYPERCV_VECTOR_RELEASE(__vector_in)                                     \
do {                                                                           \
    MFREE((__vector_in)->data);                                                \
    (__vector_in)->data = NULL;                                                \
    MFREE((__vector_in));                                                      \
    (__vector_in) = NULL;                                                      \
} while(0)


#define HYPERCV_VECTOR_AT(__vertor_in, __element_index)                         \
    ((__vertor_in)->data[__element_index])


#define HYPERCV_VECTOR_SIZE(__vector_in)                                        \
    ((__vector_in)->size)

#endif /* __HYPERCV_VECTOR_H__ */
