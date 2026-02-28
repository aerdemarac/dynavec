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
void ivec_set(IVec* vec,size_t index,int num){
    // SET Implementation if index is valid according to size set it to value 
    if(!vec){
        puts("Null ptr passed to the set()");
        return;
    }
    if(index < vec->size){
        *(vec->data + index) = num;
    }
    else{
        puts("Invalid Index Passed to the set()");
        return;       
    }


}

void ivec_assign(IVec* vec,size_t n,int* list){
    if(!vec || !list || n == 0){
        puts("Null ptr passed to the assing() or invalid init-list size");
        return;
    }
    if(vec->size > 0){
        puts("This array is not assignable by a list. Used _force");
        return;
    }
    for(size_t i = 0; i < n ; i++){
        ivec_push(vec,*(list + i));
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
            fprintf(stderr,"Container Re-Allocation Failed push");
            return;
        }
        else{
            vec->data = dummy;
            dummy = NULL;
            vec->capacity *= 2;
            *(vec->data + vec->size) = num;
            vec->size++;
        }
    }
}

void ivec_pop(IVec* vec){
    if(!vec){
        puts("Null ptr passed to the pop()");
        return;
    }
    if(vec->size <= 0){
        puts("This vector cannot popable...");
        return;

    }

    *(vec->data + vec->size - 1) = 0;
    vec->size--;

    if(vec->size >= 20 && vec->size == vec->capacity / 4){ 
        int* dummy = realloc(vec->data, (vec->capacity / 2) * vec->el_size);
        if(!dummy){
            fprintf(stderr,"Container Re-Allocation Failed pop");
            return;
        }
        vec->data = dummy;
        dummy = NULL;
        vec->capacity /= 2;
    }

}

void ivec_clear(IVec* vec){
    if(!vec){
        puts("Null ptr passed to the clear()");
        return;
    }
    vec->size = 0;
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

