#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef VECTOR_CORE_H
#define VECTOR_CORE_H

typedef struct IVec IVec;
 
typedef struct CVec CVec;

typedef struct DVec DVec;

typedef struct UIVec UIVec;

enum RETCODES{
    OOB_ACCESS = -1,
    SUCCESS = 0,
    INVALID_PTR_PASSED = 1,
    VEC_TOO_SMALL = 2,
    AT_MAX_CAPACITY = 3,
    REALLOC_FAILED = 4,
    ASSIGN_FAILED = 5

};

IVec* ivec_init();

size_t ivec_size(const IVec* vec);

size_t ivec_capacity(const IVec* vec);

int ivec_sget(const IVec* vec,size_t index,int* out); 

int ivec_set(IVec* vec,size_t index,int num);

int ivec_assign(IVec* vec,size_t n,int* list); 

int ivec_push(IVec* vec,int num);

int ivec_pop(IVec* vec);

int ivec_clear(IVec* vec);

int ivec_free(IVec** vec);

#endif
