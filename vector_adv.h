#include "vector_core.h"

#ifndef VECTOR_ADV_H
#define VECTOR_ADV_H




//UNSAFE Methods
int ivec_get(const IVec* vec,size_t index);

const int* ivec_cend(IVec* vec);

const int* ivec_cbegin(IVec* vec);

int* ivec_end(IVec* vec);

int* ivec_begin(IVec* vec);
#endif


