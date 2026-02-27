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
    if(!(vec->data = calloc(vec->capacity,vec->el_size))){
        fprintf(stderr,"Container Allocation Failed");
        return NULL;
    }
    return vec;
}
size_t ivec_size(IVec* vec){
    if(!vec){
        puts("Null ptr passed to the size()");
        return 0;
    }
    return vec->size;
}
size_t ivec_capacity(IVec* vec){
    if(!vec){
        puts("Null ptr passed to the capacity()");
        return 0;
    }
    return vec->capacity;
}
int ivec_get(IVec* vec,size_t index){
    if(!vec){
        puts("Null ptr passed to the get()");
        return 0; // WILL RETURN A DISTINGUİSBLE ERROR VALUE LATER
    }
    if(index < vec->size){
        return *(vec->data + index);
    }
    else{
        puts("Invalid Index Passed to the get()");
        return 0; // WILL RETURN A DISTINGUİSBLE ERROR VALUE LATER
        
    }
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
        int* dummy = realloc(vec->data,vec->el_size * (vec->capacity * 2));
        if(!dummy){
            fprintf(stderr,"Container Re-Allocation Failed");
            return;
        }
        else{
            vec->data = dummy;
            dummy = NULL;
            vec->capacity *= 2;
            *(vec->data + vec->size) = num;
            vec->size++;
            size_t i; // Will be used to imitate zero initialize of the new allocated memory after the pushed number
            for(i = vec->capacity / 2 + 1 ; i < vec->capacity ; i++){
                *(vec->data + i) = 0;
            }
        }
    }
}

void ivec_pop(IVec* vec){
    //POP MECHANICS
    if(!vec){
        puts("Null ptr passed to the pop()");
        return;

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
