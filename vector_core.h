#include <stdio.h>
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

//Integer Specific Methods
IVec* ivec_init(void);

size_t ivec_size(const IVec* vec);

size_t ivec_capacity(const IVec* vec);

int ivec_sget(const IVec* vec,size_t index,int* out); 

int ivec_set(IVec* vec,size_t index,int num);

int ivec_assign(IVec* vec,size_t n,int* list); 

int ivec_push(IVec* vec,int num);

int ivec_pop(IVec* vec);

int ivec_clear(IVec* vec);

int ivec_free(IVec** vec);

//Char Specific Methods
CVec* cvec_init(void);

size_t cvec_size(const CVec* vec);

size_t cvec_capacity(const CVec* vec);

int cvec_sget(const CVec* vec,size_t index,char* out); 

int cvec_set(CVec* vec,size_t index,char ch);

int cvec_assign(CVec* vec,size_t n,char* list); 

int cvec_push(CVec* vec,char ch);

int cvec_pop(CVec* vec);

int cvec_clear(CVec* vec);

int cvec_free(CVec** vec);

//Double Specific Methods
DVec* dvec_init(void);

size_t dvec_size(const DVec* vec);

size_t dvec_capacity(const DVec* vec);

int dvec_sget(const DVec* vec,size_t index,double* out); 

int dvec_set(DVec* vec,size_t index,double num);

int dvec_assign(DVec* vec,size_t n,double* list); 

int dvec_push(DVec* vec,double num);

int dvec_pop(DVec* vec);

int dvec_clear(DVec* vec);

int dvec_free(DVec** vec);

//Unsigned Integer Specific Methods
UIVec* uivec_init(void);

size_t uivec_size(const UIVec* vec);

size_t uivec_capacity(const UIVec* vec);

int uivec_sget(const UIVec* vec,size_t index,unsigned* out); 

int uivec_set(UIVec* vec,size_t index,unsigned num);

int uivec_assign(UIVec* vec,size_t n,unsigned* list); 

int uivec_push(UIVec* vec,unsigned num);

int uivec_pop(UIVec* vec);

int uivec_clear(UIVec* vec);

int uivec_free(UIVec** vec);


#endif
