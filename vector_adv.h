#include "vector_core.h"

#ifndef VECTOR_ADV_H
#define VECTOR_ADV_H

//Integer Specific Methods
int ivec_get(const IVec* vec,size_t index);

const int* ivec_cend(const IVec* vec);

const int* ivec_cbegin(const IVec* vec);

int* ivec_end(IVec* vec);

int* ivec_begin(IVec* vec);

//Char Specific Methods
char cvec_get(const CVec* vec,size_t index);

const char* cvec_cend(const CVec* vec);

const char* cvec_cbegin(const CVec* vec);

char* cvec_end(CVec* vec);

char* cvec_begin(CVec* vec);

//Double Specific Methods
double dvec_get(const DVec* vec,size_t index);

const double* dvec_cbegin(const DVec* vec);

const double* dvec_cend(const DVec* vec);

double* dvec_begin(DVec* vec);

double* dvec_end(DVec* vec);

//Unsigned Integer Specific Methods
double dvec_get(const DVec* vec,size_t index);

const double* dvec_cbegin(const DVec* vec);

const double* dvec_cend(const DVec* vec);

double* dvec_begin(DVec* vec);

double* dvec_end(DVec* vec);

#endif


