#include <stdlib.h>
#include "vector_core.h"
#define maxSafeSize (size_t)(SIZE_MAX / 2) //Defines the possible maximum size for the vector
#define DEFAULT_CAPACITY 32 // Vector's default capacity

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
static void ivec_corrupt_check(IVec* vec); // Debug Only
IVec* ivec_init(){
    IVec* vec;
    if(!(vec = calloc(1,sizeof(IVec)))){
        //NULL is returned when object allocation fails
        return NULL;
    }
    vec->capacity = DEFAULT_CAPACITY;
    vec->el_size = sizeof(int);
    if(!(vec->data = calloc(vec->capacity,vec->el_size))){
        //NULL is returned when vector allocation fails
        free(vec);
        vec = NULL;
        return NULL;
    }
    return vec;
}

size_t ivec_size(const IVec* vec){
    if(!vec){
        return SIZE_MAX; // Sentinel value returned to clearly report the error
    }
    return vec->size;
}

size_t ivec_capacity(const IVec* vec){
    if(!vec){
        return SIZE_MAX; // Sentinel value returned to clearly report the error 
    }
    return vec->capacity;
}

int ivec_sget(const IVec* vec,size_t index,int* out){ // This method has a faster but less safe variant below 
    if(!vec||!out){
        return -1;
    }
    if(index < vec->size){
        *out = *(vec->data + index);
        return 0;
    }
    else{
        return 1;
    }
}

int ivec_set(IVec* vec,size_t index,int num){
    if(!vec){
        return -1;
    }
    if(index < vec->size){
        *(vec->data + index) = num;
        return 0;
    }
    else{
        return 1;
    }
}

int ivec_assign(IVec* vec,size_t n,int* list){
    ivec_corrupt_check(vec);
    if(!vec || !list) {
        return -1;
    }
    if(n == 0){
        return 1;
    }
    ivec_clear(vec);
    for(size_t i = 0; i < n ; i++){ // Since array is cleared the safest method is pushing whatever in the provided array
        if(ivec_push(vec,*(list + i))){
            ivec_clear(vec);
            return -1;
        }
    }
    return 0;
}

int ivec_push(IVec* vec,int num){
    ivec_corrupt_check(vec);
    if(!vec){
        return -1;
    }
    if(vec->size <= maxSafeSize / 2){ // Prevents over-growth of the vector
        if(vec->size < vec->capacity){//If vector has room set the one past element to the provided argument
            *(vec->data + vec->size) = num;
            vec->size++;
            return 0;
        }
        else{// If vector has no room to push double the capacity and push the element
            int* dummy = realloc(vec->data,vec->el_size * (vec->capacity * 2));
            if(!dummy){ //In case realloc fails, dummy prevents the mem address loss
                return -1;
            }
            vec->data = dummy;
            dummy = NULL;
            vec->capacity *= 2;
            *(vec->data + vec->size) = num;
            vec->size++;
            return 0;
        }
    }
    else{
        return -2;
    }
}

int ivec_pop(IVec* vec){
    ivec_corrupt_check(vec);
    if(!vec){
        return -1;
    }
    if(vec->size == 0){
        return 1;

    }
    vec->size--;
    if(vec->size >= DEFAULT_CAPACITY && vec->size <= vec->capacity / 4){ //Prevents trashing by shrinking capacity the DEFAULT_CAPACITY most
        int* dummy = realloc(vec->data, (vec->capacity / 2) * vec->el_size);
        if(!dummy){ //In case realloc fails, dummy prevents the mem address loss
            return -1;
        }
        vec->data = dummy;
        dummy = NULL;
        vec->capacity /= 2;
        return 0;
    }
    return 0;
}

int ivec_clear(IVec* vec){ // Doesnt manipulate the vector capacity since user will be dealing with same amount numbers before the clear() call
    ivec_corrupt_check(vec);
    if(!vec){
        return -1;
    }
    if(!vec->size){ 
        return 0;
    }
    vec->size = 0;
    return 0;
}

int ivec_free(IVec** ptr_vec){
    if(!ptr_vec || !(*ptr_vec)){
        return -1;
    }
    //Container Dealloc
    free((*ptr_vec)->data);
    (*ptr_vec)->data = NULL;
    //Struct Obj Dealloc
    free(*ptr_vec);
    *ptr_vec = NULL;
    return 0;
}

//Advance Methods (Can be accessed by including vector_adv.h)
int ivec_get(const IVec* vec,size_t index){ //Considered Advance since this method is pre-conditional and does not report the failure
    return *(vec->data + index);
}
const int* ivec_cend(const IVec* vec){
    return (vec->data + vec->size);
}

const int* ivec_cbegin(const IVec* vec){
    return (vec->data);
}

int* ivec_end(IVec* vec){
    return (vec->data + vec->size);
}

int* ivec_begin(IVec* vec){
    return (vec->data);
}
//Debug Only
static void ivec_corrupt_check(IVec* vec){ 
    int willExit = 0;
    if(vec->size > vec->capacity){
        fprintf(stderr,"Vector's size exceeded its capacity");
        willExit++;
    }
    if(vec->capacity < DEFAULT_CAPACITY){
        fprintf(stderr,"Vector's size has gone below the DEFAULT_CAPACITY");
        willExit++;
        
    }
    if(vec->capacity && !vec->data){
        fprintf(stderr,"Vector's data section has corrupted");
    }
    if(willExit){
        exit(EXIT_FAILURE);
    }
}
