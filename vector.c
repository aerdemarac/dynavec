#include "vector.h"
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


static void fatal_terminate(const char* err);

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
        return SIZE_MAX; // Error Handling by returning an impossible value 
    }
    return vec->size;
}
size_t ivec_capacity(const IVec* vec){
    if(!vec){
        return SIZE_MAX; // Error Handling by returning an impossible value 
    }
    return vec->capacity;
}
int ivec_get(const IVec* vec,size_t index){
    if(!vec){
        fatal_terminate("Null Pointer Passed to the ivec_get()");
    }
    if(index < vec->size){
        return *(vec->data + index);
    }
    else{
        fatal_terminate("Out of bound access to the IVec by ivec_get()");
        return 404; // Allready unreachable, just added to suppress compiler warnings 
    }
}
void ivec_set(IVec* vec,size_t index,int num){
    // SET Implementation if index is valid according to size set it to value 
    if(!vec){
        fatal_terminate("Null Pointer Passed to the ivec_set()");
        return;
    }
    if(index < vec->size){
        *(vec->data + index) = num;
    }
    else{
        fatal_terminate("Out of bound access to the IVec by ivec_set()");
        return;       
    }

}

void ivec_assign(IVec* vec,size_t n,int* list){
    if(!vec || !list){
        fatal_terminate("Null Pointer Passed to the ivec_assing()");
    }
    if(n == 0){
        fatal_terminate("Invalid initializer list size passed to the ivec_assign()");
    }
    if(vec->size != 0){
        fatal_terminate("This array is not assignable by a list");
        return;
    }
    for(size_t i = 0; i < n ; i++){
        ivec_push(vec,*(list + i));
    }
}

void ivec_push(IVec* vec,int num){
    if(!vec){
        fatal_terminate("Null Ptr Passed to the ivec_push()");
        return;
    }
    if(vec->size <= maxSafeSize){
        if(vec->size < vec->capacity){
            *(vec->data + vec->size) = num;
            vec->size++;
        }
        else{
            int* dummy = realloc(vec->data,vec->el_size * (vec->capacity * 2));
            if(!dummy){
                fatal_terminate("Container Re-Allocation Failed");
                return;
            }
            vec->data = dummy;
            dummy = NULL;
            vec->capacity *= 2;
            *(vec->data + vec->size) = num;
            vec->size++;
        }
    }
    else{
        fatal_terminate("This vector reached max possible size");
        return;
    }
}

void ivec_pop(IVec* vec){
    if(!vec){
        fatal_terminate("Null ptr passed to the pop()");
        return;
    }
    if(vec->size == 0){
        fatal_terminate("This vector is not popable...");
        return;

    }

    vec->size--;

    if(vec->size >= 32 && vec->size == vec->capacity / 4){ 
        int* dummy = realloc(vec->data, (vec->capacity / 2) * vec->el_size);
        if(!dummy){
            fatal_terminate("Container Re-Allocation Failed pop");
            return;
        }
        vec->data = dummy;
        dummy = NULL;
        vec->capacity /= 2;
    }

}

void ivec_clear(IVec* vec){
    if(!vec){
        fatal_terminate("Null ptr passed to the clear()");
        return;
    }
    vec->size = 0;
}

void ivec_free(IVec** ptr_vec){
    if(!ptr_vec || !(*ptr_vec)){
        fatal_terminate("Null ptr passed to the free()");
        return;
    }
    //Container Dealloc
    free((*ptr_vec)->data);
    (*ptr_vec)->data = NULL;
    //Struct Obj Dealloc
    free(*ptr_vec);
    *ptr_vec = NULL;
}
static void fatal_terminate(const char* err){
    fprintf(stderr,"VECTOR_ERR_MSG: %s" ,err);
    exit(EXIT_FAILURE);
}
