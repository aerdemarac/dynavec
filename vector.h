#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef struct IVec IVec;
 
typedef struct CVec CVec;

typedef struct DVec DVec;

typedef struct UIVec UIVec;


IVec* ivec_init();

size_t ivec_size(const IVec* vec);

size_t ivec_capacity(const IVec* vec);

int ivec_get(const IVec* vec,size_t index);

void ivec_set(IVec* vec,size_t index,int num);

void ivec_assign(IVec* vec,size_t n,int* list); 

void ivec_push(IVec* vec,int num);

void ivec_pop(IVec* vec);

void ivec_clear(IVec* vec);

void ivec_free(IVec** vec);

