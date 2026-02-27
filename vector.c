#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "vector.h"


struct IVec {
    size_t size;
    size_t capacity;
    size_t el_size;
    int* data;
};
 
struct CVec {
    size_t size;
    size_t capacity;
    size_t el_size;
    char* data;
};

struct DVec {
    size_t size;
    size_t capacity;
    size_t el_size;
    double* data;
};

struct UIVec {
    size_t size;
    size_t capacity;
    size_t el_size;
    unsigned* data;
};


IVec* ivec_init(){
    IVec* vec;
    if(!(vec = calloc(1,sizeof(IVec)))){
        fprintf(stderr,"Object Allocation Failed");
        return NULL;
    }
    //size =  auto 0 init by calloc
    vec->capacity = 20;
    vec->el_size = sizeof(int);
    if(!(vec->data = calloc(vec->capacity,sizeof(vec->el_size)))){
        fprintf(stderr,"Container Allocation Failed");
        return NULL;
    }
    return vec;
}

void ivec_push(IVec* vec,int num){
    if(!vec){
        puts("Null ptr passed to the push()");
        return;
    }
    if(vec->size < vec->capacity){
        *(vec->data + vec->size) = num;
        vec->size++;
    }
    else{
        //realloc will expand the container
    }
}

void ivec_free(IVec** ptr_vec){
    if(!ptr_vec){
        puts("Null ptr passed to the free()");
        return;
    }
    //Container Dealloc
    free((*ptr_vec)->data);
    (*ptr_vec)->data = NULL;
    //Struct Obj Dealloc
    free(*ptr_vec);
    *ptr_vec = NULL;
}
