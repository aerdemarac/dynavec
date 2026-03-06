#include <stdlib.h>
#include "vector_core.h"
#define maxSafeSize (size_t)(SIZE_MAX / 2) //Defines the possible maximum size for the vector
#define DEFAULT_CAPACITY 32 // Vector's default capacity

struct IVec {
    size_t size;
    size_t capacity;
    int* data;
};
 
struct CVec {
    size_t size;
    size_t capacity;
    char* data;
};

struct DVec {
    size_t size;
    size_t capacity;
    double* data;
};

struct UIVec {
    size_t size;
    size_t capacity;
    unsigned* data;
};

static void ivec_corrupt_check(IVec* vec); // Debug Only
static void cvec_corrupt_check(CVec* vec); // Debug Only
static void dvec_corrupt_check(DVec* vec); // Debug Only
static void uivec_corrupt_check(UIVec* vec); // Debug Only
                                           
//Integer Specific Methods
IVec* ivec_init(void){
    IVec* vec;
    if(!(vec = calloc(1,sizeof(IVec)))){
        //NULL is returned when object allocation fails
        return NULL;
    }
    vec->capacity = DEFAULT_CAPACITY;
    if(!(vec->data = calloc(vec->capacity,sizeof(int)))){
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
        return INVALID_PTR_PASSED;
    }
    if(index < vec->size){
        *out = *(vec->data + index);
        return SUCCESS;
    }
    else{
        return OOB_ACCESS;
    }
}

int ivec_set(IVec* vec,size_t index,int num){
    if(!vec){
        return INVALID_PTR_PASSED;
    }
    if(index < vec->size){
        *(vec->data + index) = num;
        return SUCCESS;
    }
    else{
        return OOB_ACCESS;
    }
}

int ivec_assign(IVec* vec,size_t n,int* list){
    ivec_corrupt_check(vec);
    if(!vec || !list) {
        return INVALID_PTR_PASSED;
    } // n == 0 case is not handled in order to keep sentinel values unique
    ivec_clear(vec);
    for(size_t i = 0; i < n ; i++){ // Since array is cleared the safest method is pushing whatever in the provided array
        if(ivec_push(vec,*(list + i))){
            ivec_clear(vec);
            return ASSIGN_FAILED;
        }
    }
    return SUCCESS;
}

int ivec_push(IVec* vec,int num){
    ivec_corrupt_check(vec);
    if(!vec){
        return INVALID_PTR_PASSED;
    }
    if(vec->size <= maxSafeSize / 2){ // Prevents over-growth of the vector
        if(vec->size < vec->capacity){//If vector has room set the one past element to the provided argument
            *(vec->data + vec->size) = num;
            vec->size++;
            return SUCCESS;
        }
        else{// If vector has no room to push double the capacity and push the element
            int* dummy = realloc(vec->data, sizeof(int) * (vec->capacity * 2));
            if(!dummy){ //In case realloc fails, dummy prevents the mem address loss
                return REALLOC_FAILED;
            }
            vec->data = dummy;
            dummy = NULL;
            vec->capacity *= 2;
            *(vec->data + vec->size) = num;
            vec->size++;
            return SUCCESS;
        }
    }
    else{
        return AT_MAX_CAPACITY;
    }
}

int ivec_pop(IVec* vec){
    ivec_corrupt_check(vec);
    if(!vec){
        return INVALID_PTR_PASSED;
    }
    if(vec->size == 0){
        return VEC_TOO_SMALL;

    }
    vec->size--;
    if(vec->size >= DEFAULT_CAPACITY && vec->size <= vec->capacity / 4){ //Prevents trashing by shrinking capacity the DEFAULT_CAPACITY most
        int* dummy = realloc(vec->data, (vec->capacity / 2) * sizeof(int));
        if(!dummy){ //In case realloc fails, dummy prevents the mem address loss
            return REALLOC_FAILED;
        }
        vec->data = dummy;
        dummy = NULL;
        vec->capacity /= 2;
        return SUCCESS;
    }
    return SUCCESS;
}

int ivec_clear(IVec* vec){ // Doesnt manipulate the vector capacity since user will be dealing with same amount numbers before the clear() call
    ivec_corrupt_check(vec);
    if(!vec){
        return INVALID_PTR_PASSED;
    }
    if(!vec->size){ 
        return VEC_TOO_SMALL;
    }
    vec->size = 0;
    return SUCCESS;
}

int ivec_free(IVec** ptr_vec){
    if(!ptr_vec || !(*ptr_vec)){
        return INVALID_PTR_PASSED;
    }
    //Container Dealloc
    free((*ptr_vec)->data);
    (*ptr_vec)->data = NULL;
    //Struct Obj Dealloc
    free(*ptr_vec);
    *ptr_vec = NULL;
    return SUCCESS;
}
//Advance Integer Methods (Can be accessed by including vector_adv.h)
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

//Char Specific Methods 
CVec* cvec_init(void){
    CVec* vec;
    if(!(vec = calloc(1,sizeof(CVec)))){
        //NULL is returned when object allocation fails
        return NULL;
    }
    vec->capacity = DEFAULT_CAPACITY;
    if(!(vec->data = calloc(vec->capacity,sizeof(char)))){
        //NULL is returned when vector allocation fails
        free(vec);
        vec = NULL;
        return NULL;
    }
    return vec;
}

size_t cvec_size(const CVec* vec){
    if(!vec){
        return SIZE_MAX; // Sentinel value returned to clearly report the error
    }
    return vec->size;
}

size_t cvec_capacity(const CVec* vec){
    if(!vec){
        return SIZE_MAX; // Sentinel value returned to clearly report the error
    }
    return vec->capacity;
}

int cvec_sget(const CVec* vec,size_t index,char* out){ // This method has a faster but less safe variant below 
    if(!vec||!out){
        return INVALID_PTR_PASSED;
    }
    if(index < vec->size){
        *out = *(vec->data + index);
        return SUCCESS;
    }
    else{
        return OOB_ACCESS;
    }
}

int cvec_set(CVec* vec,size_t index,char ch){
    if(!vec){
        return INVALID_PTR_PASSED;
    }
    if(index < vec->size){
        *(vec->data + index) = ch;
        return SUCCESS;
    }
    else{
        return OOB_ACCESS;
    }
}


int cvec_assign(CVec* vec,size_t n,char* list){
    cvec_corrupt_check(vec);
    if(!vec || !list) {
        return INVALID_PTR_PASSED;
    } // n == 0 case is not handled in order to keep sentinel values unique
    cvec_clear(vec);
    for(size_t i = 0; i < n ; i++){ // Since array is cleared the safest method is pushing whatever in the provided array
        if(cvec_push(vec,*(list + i))){ // If pushing the next elemement ın the initializer list fails
            cvec_clear(vec);
            return ASSIGN_FAILED;
        }
    }
    return SUCCESS;
}

int cvec_push(CVec* vec,char ch){
    cvec_corrupt_check(vec);
    if(!vec){
        return INVALID_PTR_PASSED;
    }
    if(vec->size <= maxSafeSize / 2){ // Prevents over-growth of the vector
        if(vec->size < vec->capacity){//If vector has room set the one past element to the provided argument
            *(vec->data + vec->size) = ch;
            vec->size++;
            return SUCCESS;
        }
        else{// If vector has no room to push double the capacity and push the element
            char* dummy = realloc(vec->data, sizeof(char) * (vec->capacity * 2));
            if(!dummy){ //In case realloc fails, dummy prevents the mem address loss
                return REALLOC_FAILED;
            }
            vec->data = dummy;
            dummy = NULL;
            vec->capacity *= 2;
            *(vec->data + vec->size) = ch;
            vec->size++;
            return SUCCESS;
        }
    }
    else{
        return AT_MAX_CAPACITY;
    }
}

int cvec_pop(CVec* vec){
    cvec_corrupt_check(vec);
    if(!vec){
        return INVALID_PTR_PASSED;
    }
    if(vec->size == 0){
        return VEC_TOO_SMALL;

    }
    vec->size--;
    if(vec->size >= DEFAULT_CAPACITY && vec->size <= vec->capacity / 4){ //Prevents trashing by shrinking capacity the DEFAULT_CAPACITY most
        char* dummy = realloc(vec->data, (vec->capacity / 2) * sizeof(char));
        if(!dummy){ //In case realloc fails, dummy prevents the mem address loss
            return REALLOC_FAILED;
        }
        vec->data = dummy;
        dummy = NULL;
        vec->capacity /= 2;
        return SUCCESS;
    }
    return SUCCESS;
}

int cvec_clear(CVec* vec){ // Doesnt manipulate the vector capacity since user will be dealing with same amount numbers before the clear() call
    cvec_corrupt_check(vec);
    if(!vec){
        return INVALID_PTR_PASSED;
    }
    if(!vec->size){ 
        return VEC_TOO_SMALL;
    }
    vec->size = 0;
    return SUCCESS;
}

int cvec_free(CVec** ptr_vec){
    if(!ptr_vec || !(*ptr_vec)){
        return INVALID_PTR_PASSED;
    }
    //Container Dealloc
    free((*ptr_vec)->data);
    (*ptr_vec)->data = NULL;
    //Struct Obj Dealloc
    free(*ptr_vec);
    *ptr_vec = NULL;
    return SUCCESS;
}

//Advance Char Methods (Can be accessed by including vector_adv.h)
char cvec_get(const CVec* vec,size_t index){ //Considered Advance since this method is pre-conditional and does not report the failure
    return *(vec->data + index);
}

const char* cvec_cend(const CVec* vec){
    return (vec->data + vec->size);
}

const char* cvec_cbegin(const CVec* vec){
    return vec->data;
}

char* cvec_end(CVec* vec){
    return (vec->data + vec->size);
}

char* cvec_begin(CVec* vec){
    return vec->data;
}


//Double Specific Methods
DVec* dvec_init(void){
    DVec* vec;
    if(!(vec = calloc(1,sizeof(DVec)))){
        //NULL is returned when object allocation fails
        return NULL;
    }
    vec->capacity = DEFAULT_CAPACITY;
    if(!(vec->data = calloc(vec->capacity,sizeof(double)))){
        //NULL is returned when vector allocation fails
        free(vec);
        vec = NULL;
        return NULL;
    }
    return vec;
}

size_t dvec_size(const DVec* vec){
    if(!vec){
        return SIZE_MAX; // Sentinel value returned to clearly report the error
    }
    return vec->size;
}

size_t dvec_capacity(const DVec* vec){
    if(!vec){
        return SIZE_MAX; // Sentinel value returned to clearly report the error 
    }
    return vec->capacity;
}

int dvec_sget(const DVec* vec,size_t index,double* out){ // This method has a faster but less safe variant below 
    if(!vec||!out){
        return INVALID_PTR_PASSED;
    }
    if(index < vec->size){
        *out = *(vec->data + index);
        return SUCCESS;
    }
    else{
        return OOB_ACCESS;
    }
}

int dvec_set(DVec* vec,size_t index,double num){
    if(!vec){
        return INVALID_PTR_PASSED;
    }
    if(index < vec->size){
        *(vec->data + index) = num;
        return SUCCESS;
    }
    else{
        return OOB_ACCESS;
    }
}

int dvec_assign(DVec* vec,size_t n,double* list){
    dvec_corrupt_check(vec);
    if(!vec || !list) {
        return INVALID_PTR_PASSED;
    } // n == 0 case is not handled in order to keep sentinel values unique
    dvec_clear(vec);
    for(size_t i = 0; i < n ; i++){ // Since array is cleared the safest method is pushing whatever in the provided array
        if(dvec_push(vec,*(list + i))){
            dvec_clear(vec);
            return ASSIGN_FAILED;
        }
    }
    return SUCCESS;
}

int dvec_push(DVec* vec,double num){
    dvec_corrupt_check(vec);
    if(!vec){
        return INVALID_PTR_PASSED;
    }
    if(vec->size <= maxSafeSize / 2){ // Prevents over-growth of the vector
        if(vec->size < vec->capacity){//If vector has room set the one past element to the provided argument
            *(vec->data + vec->size) = num;
            vec->size++;
            return SUCCESS;
        }
        else{// If vector has no room to push double the capacity and push the element
            double* dummy = realloc(vec->data, sizeof(double) * (vec->capacity * 2));
            if(!dummy){ //In case realloc fails, dummy prevents the mem address loss
                return REALLOC_FAILED;
            }
            vec->data = dummy;
            dummy = NULL;
            vec->capacity *= 2;
            *(vec->data + vec->size) = num;
            vec->size++;
            return SUCCESS;
        }
    }
    else{
        return AT_MAX_CAPACITY;
    }
}

int dvec_pop(DVec* vec){
    dvec_corrupt_check(vec);
    if(!vec){
        return INVALID_PTR_PASSED;
    }
    if(vec->size == 0){
        return VEC_TOO_SMALL;

    }
    vec->size--;
    if(vec->size >= DEFAULT_CAPACITY && vec->size <= vec->capacity / 4){ //Prevents trashing by shrinking capacity the DEFAULT_CAPACITY most
        double* dummy = realloc(vec->data, (vec->capacity / 2) * sizeof(double));
        if(!dummy){ //In case realloc fails, dummy prevents the mem address loss
            return REALLOC_FAILED;
        }
        vec->data = dummy;
        dummy = NULL;
        vec->capacity /= 2;
        return SUCCESS;
    }
    return SUCCESS;
}

int dvec_clear(DVec* vec){ // Doesnt manipulate the vector capacity since user will be dealing with same amount numbers before the clear() call
    dvec_corrupt_check(vec);
    if(!vec){
        return INVALID_PTR_PASSED;
    }
    if(!vec->size){ 
        return VEC_TOO_SMALL;
    }
    vec->size = 0;
    return SUCCESS;
}

int dvec_free(DVec** ptr_vec){
    if(!ptr_vec || !(*ptr_vec)){
        return INVALID_PTR_PASSED;
    }
    //Container Dealloc
    free((*ptr_vec)->data);
    (*ptr_vec)->data = NULL;
    //Struct Obj Dealloc
    free(*ptr_vec);
    *ptr_vec = NULL;
    return SUCCESS;
}
//Advance Integer Methods (Can be accessed by including vector_adv.h)
double dvec_get(const DVec* vec,size_t index){ //Considered Advance since this method is pre-conditional and does not report the failure
    return *(vec->data + index);
}

const double* dvec_cend(const DVec* vec){
    return (vec->data + vec->size);
}

const double* dvec_cbegin(const DVec* vec){
    return vec->data;
}

double* dvec_end(DVec* vec){
    return (vec->data + vec->size);
}

double* dvec_begin(DVec* vec){
    return vec->data;
}


//Unsigned Integer Specific Methods
UIVec* uivec_init(void){
    UIVec* vec;
    if(!(vec = calloc(1,sizeof(UIVec)))){
        //NULL is returned when object allocation fails
        return NULL;
    }
    vec->capacity = DEFAULT_CAPACITY;
    if(!(vec->data = calloc(vec->capacity,sizeof(unsigned)))){
        //NULL is returned when vector allocation fails
        free(vec);
        vec = NULL;
        return NULL;
    }
    return vec;
}

size_t uivec_size(const UIVec* vec){
    if(!vec){
        return SIZE_MAX; // Sentinel value returned to clearly report the error
    }
    return vec->size;
}

size_t uivec_capacity(const UIVec* vec){
    if(!vec){
        return SIZE_MAX; // Sentinel value returned to clearly report the error 
    }
    return vec->capacity;
}

int uivec_sget(const UIVec* vec,size_t index,unsigned* out){ // This method has a faster but less safe variant below 
    if(!vec||!out){
        return INVALID_PTR_PASSED;
    }
    if(index < vec->size){
        *out = *(vec->data + index);
        return SUCCESS;
    }
    else{
        return OOB_ACCESS;
    }
}

int uivec_set(UIVec* vec,size_t index,unsigned num){
    if(!vec){
        return INVALID_PTR_PASSED;
    }
    if(index < vec->size){
        *(vec->data + index) = num;
        return SUCCESS;
    }
    else{
        return OOB_ACCESS;
    }
}

int uivec_assign(UIVec* vec,size_t n,unsigned* list){
    uivec_corrupt_check(vec);
    if(!vec || !list) {
        return INVALID_PTR_PASSED;
    } // n == 0 case is not handled in order to keep sentinel values unique
    uivec_clear(vec);
    for(size_t i = 0; i < n ; i++){ // Since array is cleared the safest method is pushing whatever in the provided array
        if(uivec_push(vec,*(list + i))){
            uivec_clear(vec);
            return ASSIGN_FAILED;
        }
    }
    return SUCCESS;
}

int uivec_push(UIVec* vec,unsigned num){
    uivec_corrupt_check(vec);
    if(!vec){
        return INVALID_PTR_PASSED;
    }
    if(vec->size <= maxSafeSize / 2){ // Prevents over-growth of the vector
        if(vec->size < vec->capacity){//If vector has room set the one past element to the provided argument
            *(vec->data + vec->size) = num;
            vec->size++;
            return SUCCESS;
        }
        else{// If vector has no room to push double the capacity and push the element
            unsigned* dummy = realloc(vec->data, sizeof(unsigned) * (vec->capacity * 2));
            if(!dummy){ //In case realloc fails, dummy prevents the mem address loss
                return REALLOC_FAILED;
            }
            vec->data = dummy;
            dummy = NULL;
            vec->capacity *= 2;
            *(vec->data + vec->size) = num;
            vec->size++;
            return SUCCESS;
        }
    }
    else{
        return AT_MAX_CAPACITY;
    }
}

int uivec_pop(UIVec* vec){
    uivec_corrupt_check(vec);
    if(!vec){
        return INVALID_PTR_PASSED;
    }
    if(vec->size == 0){
        return VEC_TOO_SMALL;

    }
    vec->size--;
    if(vec->size >= DEFAULT_CAPACITY && vec->size <= vec->capacity / 4){ //Prevents trashing by shrinking capacity the DEFAULT_CAPACITY most
        unsigned* dummy = realloc(vec->data, (vec->capacity / 2) * sizeof(unsigned));
        if(!dummy){ //In case realloc fails, dummy prevents the mem address loss
            return REALLOC_FAILED;
        }
        vec->data = dummy;
        dummy = NULL;
        vec->capacity /= 2;
        return SUCCESS;
    }
    return SUCCESS;
}

int uivec_clear(UIVec* vec){ // Doesnt manipulate the vector capacity since user will be dealing with same amount numbers before the clear() call
    uivec_corrupt_check(vec);
    if(!vec){
        return INVALID_PTR_PASSED;
    }
    if(!vec->size){ 
        return VEC_TOO_SMALL;
    }
    vec->size = 0;
    return SUCCESS;
}

int uivec_free(UIVec** ptr_vec){
    if(!ptr_vec || !(*ptr_vec)){
        return INVALID_PTR_PASSED;
    }
    //Container Dealloc
    free((*ptr_vec)->data);
    (*ptr_vec)->data = NULL;
    //Struct Obj Dealloc
    free(*ptr_vec);
    *ptr_vec = NULL;
    return SUCCESS;
}
//Advance Integer Methods (Can be accessed by including vector_adv.h)
unsigned uivec_get(const UIVec* vec,size_t index){ //Considered Advance since this method is pre-conditional and does not report the failure
    return *(vec->data + index);
}

const unsigned* uivec_cend(const UIVec* vec){
    return (vec->data + vec->size);
}

const unsigned* uivec_cbegin(const UIVec* vec){
    return vec->data ;
}

unsigned* uivec_end(UIVec* vec){
    return (vec->data + vec->size);
}

unsigned* uivec_begin(UIVec* vec){
    return vec->data;
}







































static void ivec_corrupt_check(IVec* vec){
    if(!vec->data){
        fprintf(stderr,"Data Section Corrupted");
        exit(EXIT_FAILURE);
    }
    if(vec->size > vec->capacity){
        fprintf(stderr,"Size Has Exceeded The capacity");
        exit(EXIT_FAILURE);
    }
    if(vec->capacity < DEFAULT_CAPACITY){
        fprintf(stderr,"Capacity Has shrank down below the default value");
        exit(EXIT_FAILURE);
    }
    if(vec->size > maxSafeSize || vec->capacity > maxSafeSize){
        fprintf(stderr,"Size or Capacity has exceeded the maximum safe value");
        exit(EXIT_FAILURE);
    }
}
static void cvec_corrupt_check(CVec* vec){
    if(!vec->data){
        fprintf(stderr,"Data Section Corrupted");
        exit(EXIT_FAILURE);
    }
    if(vec->size > vec->capacity){
        fprintf(stderr,"Size Has Exceeded The capacity");
        exit(EXIT_FAILURE);
    }
    if(vec->capacity < DEFAULT_CAPACITY){
        fprintf(stderr,"Capacity Has shrank down below the default value");
        exit(EXIT_FAILURE);
    }
    if(vec->size > maxSafeSize || vec->capacity > maxSafeSize){
        fprintf(stderr,"Size or Capacity has exceeded the maximum safe value");
        exit(EXIT_FAILURE);
    }
}
static void dvec_corrupt_check(DVec* vec){
    if(!vec->data){
        fprintf(stderr,"Data Section Corrupted");
        exit(EXIT_FAILURE);
    }
    if(vec->size > vec->capacity){
        fprintf(stderr,"Size Has Exceeded The capacity");
        exit(EXIT_FAILURE);
    }
    if(vec->capacity < DEFAULT_CAPACITY){
        fprintf(stderr,"Capacity Has shrank down below the default value");
        exit(EXIT_FAILURE);
    }
    if(vec->size > maxSafeSize || vec->capacity > maxSafeSize){
        fprintf(stderr,"Size or Capacity has exceeded the maximum safe value");
        exit(EXIT_FAILURE);
    }
}
static void uivec_corrupt_check(UIVec* vec){
    if(!vec->data){
        fprintf(stderr,"Data Section Corrupted");
        exit(EXIT_FAILURE);
    }
    if(vec->size > vec->capacity){
        fprintf(stderr,"Size Has Exceeded The capacity");
        exit(EXIT_FAILURE);
    }
    if(vec->capacity < DEFAULT_CAPACITY){
        fprintf(stderr,"Capacity Has shrank down below the default value");
        exit(EXIT_FAILURE);
    }
    if(vec->size > maxSafeSize || vec->capacity > maxSafeSize){
        fprintf(stderr,"Size or Capacity has exceeded the maximum safe value");
        exit(EXIT_FAILURE);
    }
}
