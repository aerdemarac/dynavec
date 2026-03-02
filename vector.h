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

int* ivec_sget(const IVec* vec,size_t index); 

int ivec_set(IVec* vec,size_t index,int num);

int ivec_assign(IVec* vec,size_t n,int* list); 

int ivec_push(IVec* vec,int num);

int ivec_pop(IVec* vec);

int ivec_clear(IVec* vec);

int ivec_free(IVec** vec);


