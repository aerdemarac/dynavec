#include <stdio.h>
#include <stdlib.h>


typedef struct IVec IVec;
 
typedef struct CVec CVec;

typedef struct DVec DVec;

typedef struct UIVec UIVec;


IVec* ivec_init();

size_t ivec_size(IVec* vec);

size_t ivec_capacity(IVec* vec);

int ivec_get(IVec* vec,size_t index);

void ivec_push(IVec* vec,int num);

void ivec_pop(IVec* vec);

void ivec_free(IVec** vec);
