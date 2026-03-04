#include "vector_core.h"
#define maxSafeSize (size_t)(SIZE_MAX / 2) 

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
        //Object Allocation Failed
        return NULL;
    }
    vec->capacity = 32;
    vec->el_size = sizeof(int);
    if(!(vec->data = calloc(vec->capacity,vec->el_size))){
        //Container Allocation Failed
        free(vec);
        vec = NULL;
        return NULL;
    }
    return vec;
}
size_t ivec_size(const IVec* vec){
    if(!vec){
        return SIZE_MAX; // Sentinel Value 
    }
    return vec->size;
}
size_t ivec_capacity(const IVec* vec){
    if(!vec){
        return SIZE_MAX; // Sentinel Value 
    }
    return vec->capacity;
}
int ivec_get(const IVec* vec,size_t index){ // UNSAFE Version
        return *(vec->data + index);
}
int ivec_sget(const IVec* vec,size_t index,int* out){ // SAFE Version
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
    if(!vec || !list){
        return -1;
    }
    if(n == 0){
        return 1;
    }
    if(vec->size != 0){
        return -2;
    }
    for(size_t i = 0; i < n ; i++){
        ivec_push(vec,*(list + i));
    }
    return 0;
}

int ivec_push(IVec* vec,int num){
    if(!vec){
        return -1;
    }
    if(vec->size <= maxSafeSize){
        if(vec->size < vec->capacity){
            *(vec->data + vec->size) = num;
            vec->size++;
            return 0;
        }
        else{
            int* dummy = realloc(vec->data,vec->el_size * (vec->capacity * 2));
            if(!dummy){
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
    if(!vec){
        return -1;
    }
    if(vec->size == 0){
        return 1;

    }
    vec->size--;

    if(vec->size >= 32 && vec->size == vec->capacity / 4){ 
        int* dummy = realloc(vec->data, (vec->capacity / 2) * vec->el_size);
        if(!dummy){
            return -1;
        }
        vec->data = dummy;
        dummy = NULL;
        vec->capacity /= 2;
        return 0;
    }
    return 0;

}
int ivec_clear(IVec* vec){
    if(!vec){
        return -1;
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

//ADV
const int* ivec_cend(IVec* vec){
    return (vec->data + vec->size);
}

const int* ivec_cbegin(IVec* vec){
    return (vec->data);
}

int* ivec_end(IVec* vec){
    return (vec->data + vec->size);
}

int* ivec_begin(IVec* vec){
    return (vec->data);
}
