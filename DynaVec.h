/**
 /$$$$$$$  /$$     /$$ /$$   /$$  /$$$$$$  /$$    /$$ /$$$$$$$$  /$$$$$$ 
| $$__  $$|  $$   /$$/| $$$ | $$ /$$__  $$| $$   | $$| $$_____/ /$$__  $$
| $$  \ $$ \  $$ /$$/ | $$$$| $$| $$  \ $$| $$   | $$| $$      | $$  \__/
| $$  | $$  \  $$$$/  | $$ $$ $$| $$$$$$$$|  $$ / $$/| $$$$$   | $$      
| $$  | $$   \  $$/   | $$  $$$$| $$__  $$ \  $$ $$/ | $$__/   | $$      
| $$  | $$    | $$    | $$\  $$$| $$  | $$  \  $$$/  | $$      | $$    $$
| $$$$$$$/    | $$    | $$ \  $$| $$  | $$   \  $/   | $$$$$$$$|  $$$$$$/
|_______/     |__/    |__/  \__/|__/  |__/    \_/    |________/ \______/ 

  Dynavec - Header-Only, Zero-Dependency Dynamic Vector Library
 Strict ISO C99 compliant

 Author  : Erdem Araç
 License : MIT
 Year    : 2026

 */ 

#include <stdint.h>
#include <stdlib.h>

#ifndef DYNAVEC_H
#define DYNAVEC_H

#define maxSafeSize (size_t)(SIZE_MAX / 2) //Defines the possible maximum size for the vector
#define DEFAULT_CAPACITY 32 // Vector's default capacity

typedef struct IVec IVec; //Partially opaque structs, internals can be accessed with implementation macro (Deprecated)
 
typedef struct CVec CVec;

typedef struct DVec DVec;

typedef struct UIVec UIVec;

enum RETCODES{
    OOB_ACCESS = -1,
    SUCCESS = 0,
    INVALID_PTR_PASSED = 1,
    VEC_TOO_SMALL = 2,
    AT_MAX_CAPACITY = 3,
    REALLOC_FAILED = 4,
    ASSIGN_FAILED = 5,
    INTERNAL_CORRUPTION = 6

}; //Check README.md for comperhensive explanation on return values.

//Integer Specific Methods
IVec* ivec_init(void);

size_t ivec_size(const IVec* vec);

size_t ivec_capacity(const IVec* vec);

int ivec_sget(const IVec* vec,size_t index,int* out); 

int ivec_set(IVec* vec,size_t index,int num);

int ivec_assign(IVec* vec,size_t n,const int* list); 

int ivec_push(IVec* vec,int num);

int ivec_pop(IVec* vec);

int ivec_clear(IVec* vec);

int ivec_free(IVec** vec);

//Char Specific Methods
CVec* cvec_init(void);

size_t cvec_size(const CVec* vec);

size_t cvec_capacity(const CVec* vec);

int cvec_sget(const CVec* vec,size_t index,char* out); 

int cvec_set(CVec* vec,size_t index,char ch);

int cvec_assign(CVec* vec,size_t n,const char* list); 

int cvec_push(CVec* vec,char ch);

int cvec_pop(CVec* vec);

int cvec_clear(CVec* vec);

int cvec_free(CVec** vec);

//Double Specific Methods
DVec* dvec_init(void);

size_t dvec_size(const DVec* vec);

size_t dvec_capacity(const DVec* vec);

int dvec_sget(const DVec* vec,size_t index,double* out); 

int dvec_set(DVec* vec,size_t index,double num);

int dvec_assign(DVec* vec,size_t n,const double* list); 

int dvec_push(DVec* vec,double num);

int dvec_pop(DVec* vec);

int dvec_clear(DVec* vec);

int dvec_free(DVec** vec);

//Unsigned Integer Specific Methods
UIVec* uivec_init(void);

size_t uivec_size(const UIVec* vec);

size_t uivec_capacity(const UIVec* vec);

int uivec_sget(const UIVec* vec,size_t index,unsigned* out); 

int uivec_set(UIVec* vec,size_t index,unsigned num);

int uivec_assign(UIVec* vec,size_t n,const unsigned* list); 

int uivec_push(UIVec* vec,unsigned num);

int uivec_pop(UIVec* vec);

int uivec_clear(UIVec* vec);

int uivec_free(UIVec** vec);

// !!Warning!!: Pointers returned by *_cbegin(),*_cend(),*_begin(),*_end() is invalidated if vector grows or shrinks.

//Integer Specific Advanced Methods
int ivec_get(const IVec* vec,size_t index);

const int* ivec_cend(const IVec* vec);

const int* ivec_cbegin(const IVec* vec);

int* ivec_end(IVec* vec);

int* ivec_begin(IVec* vec);

//Char Specific Advanced Methods
char cvec_get(const CVec* vec,size_t index);

const char* cvec_cend(const CVec* vec);

const char* cvec_cbegin(const CVec* vec);

char* cvec_end(CVec* vec);

char* cvec_begin(CVec* vec);

//Double Specific Advanced Methods
double dvec_get(const DVec* vec,size_t index);

const double* dvec_cbegin(const DVec* vec);

const double* dvec_cend(const DVec* vec);

double* dvec_begin(DVec* vec);

double* dvec_end(DVec* vec);

//Unsigned Integer Specific Advanced Methods
unsigned uivec_get(const UIVec* vec,size_t index);

const unsigned* uivec_cbegin(const UIVec* vec);

const unsigned* uivec_cend(const UIVec* vec);

unsigned* uivec_begin(UIVec* vec);

unsigned* uivec_end(UIVec* vec);


//Internal Integrity Checker Methods
static inline int ivec_corrupt_check(const IVec* vec); 
static inline int cvec_corrupt_check(const CVec* vec); 
static inline int dvec_corrupt_check(const DVec* vec); 
static inline int uivec_corrupt_check(const UIVec* vec); 

#ifdef DYNAVEC_ON
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

//Integer Specific Methods
IVec* ivec_init(void){
    IVec* vec;
    if(!(vec = calloc(1,sizeof(IVec)))){
        //Returns NULL when object allocation fails
        return NULL;
    }
    vec->capacity = DEFAULT_CAPACITY;
    if(!(vec->data = calloc(vec->capacity,sizeof(int)))){
        //Returns NULL when vector allocation fails
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
    if(ivec_corrupt_check(vec)){
        return INTERNAL_CORRUPTION;
    }
    if(index < vec->size){
        *out = vec->data[index];
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
    if(ivec_corrupt_check(vec)){
        return INTERNAL_CORRUPTION;
    }
    if(index < vec->size){
        vec->data[index] = num;
        return SUCCESS;
    }
    else{
        return OOB_ACCESS;
    }
}

int ivec_assign(IVec* vec,size_t n,const int* list){
    if(!vec || !list) {
        return INVALID_PTR_PASSED;
    } // n == 0 case is not handled in order to keep sentinel values unique
    if(ivec_corrupt_check(vec)){
        return INTERNAL_CORRUPTION;
    }
    ivec_clear(vec);
    for(size_t i = 0; i < n ; i++){ // Since array is cleared the safest method is pushing whatever in the provided array
        if(ivec_push(vec,list[i])){
            ivec_clear(vec);
            return ASSIGN_FAILED;
        }
    }
    return SUCCESS;
}

int ivec_push(IVec* vec,int num){
    if(!vec){
        return INVALID_PTR_PASSED;
    }
    if(ivec_corrupt_check(vec)){
        return INTERNAL_CORRUPTION;
    }
    if(vec->size <= maxSafeSize / 2){ // Prevents over-growth of the vector
        if(vec->size < vec->capacity){//If vector has room for the upcoming push 
            vec->data[vec->size] = num;
            vec->size++;
            return SUCCESS;
        }
        else{// If vector has no room to push double the capacity and push the element
            int* dummy = realloc(vec->data, sizeof(int) * (vec->capacity * 2));
            if(!dummy){ //In case realloc fails, dummy prevents the memory address loss
                return REALLOC_FAILED;
            }
            vec->data = dummy;
            dummy = NULL;
            vec->capacity *= 2;
            vec->data[vec->size] = num;
            vec->size++;
            return SUCCESS;
        }
    }
    else{
        return AT_MAX_CAPACITY;
    }
}

int ivec_pop(IVec* vec){
    if(!vec){
        return INVALID_PTR_PASSED;
    }
    if(ivec_corrupt_check(vec)){
        return INTERNAL_CORRUPTION;
    }
    if(vec->size == 0){
        return VEC_TOO_SMALL;

    }
    vec->size--;
    if(vec->size >= DEFAULT_CAPACITY && vec->size <= vec->capacity / 4){ //Prevents trashing by shrinking capacity to the DEFAULT_CAPACITY at very least
        int* dummy = realloc(vec->data, (vec->capacity / 2) * sizeof(int));
        if(!dummy){ //In case realloc fails, dummy prevents the memory address loss
            return REALLOC_FAILED;
        }
        vec->data = dummy;
        dummy = NULL;
        vec->capacity /= 2;
        return SUCCESS;
    }
    return SUCCESS;
}

int ivec_clear(IVec* vec){ // Doesnt manipulate the vector capacity since user will be dealing with same amount elements as before the clear() call
    if(!vec){
        return INVALID_PTR_PASSED;
    }
    if(ivec_corrupt_check(vec)){
        return INTERNAL_CORRUPTION;
    }
    if(!vec->size){ 
        return SUCCESS;
    }
    vec->size = 0;
    return SUCCESS;
}

int ivec_free(IVec** ptr_vec){
    if(!ptr_vec || !(*ptr_vec)){
        return INVALID_PTR_PASSED;
    }
    //Container Deallocation
    free((*ptr_vec)->data);
    (*ptr_vec)->data = NULL;
    //Struct Object Deallocation
    free(*ptr_vec);
    *ptr_vec = NULL;
    return SUCCESS;
}

//Char Specific Methods 
CVec* cvec_init(void){
    CVec* vec;
    if(!(vec = calloc(1,sizeof(CVec)))){
        //Returns NULL when object allocation fails
        return NULL;
    }
    vec->capacity = DEFAULT_CAPACITY;
    if(!(vec->data = calloc(vec->capacity,sizeof(char)))){
        //Returns NULL when vector allocation fails
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
    if(cvec_corrupt_check(vec)){
        return INTERNAL_CORRUPTION;
    }
    if(index < vec->size){
        *out = vec->data[index];
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
    if(cvec_corrupt_check(vec)){
        return INTERNAL_CORRUPTION;
    }
    if(index < vec->size){
        vec->data[index] = ch;
        return SUCCESS;
    }
    else{
        return OOB_ACCESS;
    }
}


int cvec_assign(CVec* vec,size_t n,const char* list){
    if(!vec || !list) {
        return INVALID_PTR_PASSED;
    } // n == 0 case is not handled in order to keep sentinel values unique
    if(cvec_corrupt_check(vec)){
        return INTERNAL_CORRUPTION;
    }
    cvec_clear(vec);
    for(size_t i = 0; i < n ; i++){ // Since array is cleared the safest method is pushing whatever in the provided array
        if(cvec_push(vec,list[i])){ // If pushing the next element in the initializer list fails
            cvec_clear(vec);
            return ASSIGN_FAILED;
        }
    }
    return SUCCESS;
}

int cvec_push(CVec* vec,char ch){
    if(!vec){
        return INVALID_PTR_PASSED;
    }
    if(cvec_corrupt_check(vec)){
        return INTERNAL_CORRUPTION;
    }
    if(vec->size <= maxSafeSize / 2){ // Prevents over-growth of the vector
        if(vec->size < vec->capacity){//If vector has room for the upcoming push
            vec->data[vec->size] = ch;
            vec->size++;
            return SUCCESS;
        }
        else{// If vector has no room to push double the capacity and push the element
            char* dummy = realloc(vec->data, sizeof(char) * (vec->capacity * 2));
            if(!dummy){ //In case realloc fails, dummy prevents the memory address loss
                return REALLOC_FAILED;
            }
            vec->data = dummy;
            dummy = NULL;
            vec->capacity *= 2;
            vec->data[vec->size] = ch;
            vec->size++;
            return SUCCESS;
        }
    }
    else{
        return AT_MAX_CAPACITY;
    }
}

int cvec_pop(CVec* vec){
    if(!vec){
        return INVALID_PTR_PASSED;
    }
    if(cvec_corrupt_check(vec)){
        return INTERNAL_CORRUPTION;
    }
    if(vec->size == 0){
        return VEC_TOO_SMALL;

    }
    vec->size--;
    if(vec->size >= DEFAULT_CAPACITY && vec->size <= vec->capacity / 4){ //Prevents trashing by shrinking capacity to the DEFAULT_CAPACITY at very least
        char* dummy = realloc(vec->data, (vec->capacity / 2) * sizeof(char));
        if(!dummy){ //In case realloc fails, dummy prevents the memory address loss
            return REALLOC_FAILED;
        }
        vec->data = dummy;
        dummy = NULL;
        vec->capacity /= 2;
        return SUCCESS;
    }
    return SUCCESS;
}

int cvec_clear(CVec* vec){ // Doesnt manipulate the vector capacity since user will be dealing with same amount elements as before the clear() call
    if(!vec){
        return INVALID_PTR_PASSED;
    }
    if(cvec_corrupt_check(vec)){
        return INTERNAL_CORRUPTION;
    }
    if(!vec->size){ 
        return SUCCESS;
    }
    vec->size = 0;
    return SUCCESS;
}

int cvec_free(CVec** ptr_vec){
    if(!ptr_vec || !(*ptr_vec)){
        return INVALID_PTR_PASSED;
    }
    //Container Deallocation
    free((*ptr_vec)->data);
    (*ptr_vec)->data = NULL;
    //Struct Object Deallocation
    free(*ptr_vec);
    *ptr_vec = NULL;
    return SUCCESS;
}

//Double Specific Methods
DVec* dvec_init(void){
    DVec* vec;
    if(!(vec = calloc(1,sizeof(DVec)))){
        //Returns NULL when object allocation fails
        return NULL;
    }
    vec->capacity = DEFAULT_CAPACITY;
    if(!(vec->data = calloc(vec->capacity,sizeof(double)))){
        //Returns NULL when vector allocation fails
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
    if(dvec_corrupt_check(vec)){
        return INTERNAL_CORRUPTION;
    }
    if(index < vec->size){
        *out = vec->data[index];
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
    if(dvec_corrupt_check(vec)){
        return INTERNAL_CORRUPTION;
    }
    if(index < vec->size){
        vec->data[index] = num;
        return SUCCESS;
    }
    else{
        return OOB_ACCESS;
    }
}

int dvec_assign(DVec* vec,size_t n,const double* list){
    if(!vec || !list) {
        return INVALID_PTR_PASSED;
    } // n == 0 case is not handled in order to keep sentinel values unique
    if(dvec_corrupt_check(vec)){
        return INTERNAL_CORRUPTION;
    }
    dvec_clear(vec);
    for(size_t i = 0; i < n ; i++){ // Since array is cleared the safest method is pushing whatever in the provided array
        if(dvec_push(vec,list[i])){
            dvec_clear(vec);
            return ASSIGN_FAILED;
        }
    }
    return SUCCESS;
}

int dvec_push(DVec* vec,double num){
    if(!vec){
        return INVALID_PTR_PASSED;
    }
    if(dvec_corrupt_check(vec)){
        return INTERNAL_CORRUPTION; 
    }
    if(vec->size <= maxSafeSize / 2){ // Prevents over-growth of the vector
        if(vec->size < vec->capacity){//If vector has room for the upcoming push
            vec->data[vec->size] = num;
            vec->size++;
            return SUCCESS;
        }
        else{// If vector has no room to push double the capacity and push the element
            double* dummy = realloc(vec->data, sizeof(double) * (vec->capacity * 2));
            if(!dummy){ //In case realloc fails, dummy prevents the memory address loss
                return REALLOC_FAILED;
            }
            vec->data = dummy;
            dummy = NULL;
            vec->capacity *= 2;
            vec->data[vec->size] = num;
            vec->size++;
            return SUCCESS;
        }
    }
    else{
        return AT_MAX_CAPACITY;
    }
}

int dvec_pop(DVec* vec){
    if(!vec){
        return INVALID_PTR_PASSED;
    }
    if(dvec_corrupt_check(vec)){
        return INTERNAL_CORRUPTION; 
    }
    if(vec->size == 0){
        return VEC_TOO_SMALL;

    }
    vec->size--;
    if(vec->size >= DEFAULT_CAPACITY && vec->size <= vec->capacity / 4){ //Prevents trashing by shrinking capacity to the DEFAULT_CAPACITY at very least
        double* dummy = realloc(vec->data, (vec->capacity / 2) * sizeof(double));
        if(!dummy){ //In case realloc fails, dummy prevents the memory address loss
            return REALLOC_FAILED;
        }
        vec->data = dummy;
        dummy = NULL;
        vec->capacity /= 2;
        return SUCCESS;
    }
    return SUCCESS;
}

int dvec_clear(DVec* vec){ // Doesnt manipulate the vector capacity since user will be dealing with same amount elements as before the clear() call
    if(!vec){
        return INVALID_PTR_PASSED;
    }
    if(dvec_corrupt_check(vec)){
        return INTERNAL_CORRUPTION;
    }
    if(!vec->size){ 
        return SUCCESS;
    }
    vec->size = 0;
    return SUCCESS;
}

int dvec_free(DVec** ptr_vec){
    if(!ptr_vec || !(*ptr_vec)){
        return INVALID_PTR_PASSED;
    }
    //Container Deallocation
    free((*ptr_vec)->data);
    (*ptr_vec)->data = NULL;
    //Struct Object Deallocation
    free(*ptr_vec);
    *ptr_vec = NULL;
    return SUCCESS;
}

//Unsigned Integer Specific Methods
UIVec* uivec_init(void){
    UIVec* vec;
    if(!(vec = calloc(1,sizeof(UIVec)))){
        //Returns NULL when object allocation fails
        return NULL;
    }
    vec->capacity = DEFAULT_CAPACITY;
    if(!(vec->data = calloc(vec->capacity,sizeof(unsigned)))){
        //Returns NULL when vector allocation fails
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
    if(uivec_corrupt_check(vec)){
        return INTERNAL_CORRUPTION;
    }
    if(index < vec->size){
        *out = vec->data[index];
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
    if(uivec_corrupt_check(vec)){
        return INTERNAL_CORRUPTION;
    }
    if(index < vec->size){
        vec->data[index] = num;
        return SUCCESS;
    }
    else{
        return OOB_ACCESS;
    }
}

int uivec_assign(UIVec* vec,size_t n,const unsigned* list){
    if(!vec || !list) {
        return INVALID_PTR_PASSED;
    } // n == 0 case is not handled in order to keep sentinel values unique
    if(uivec_corrupt_check(vec)){
        return INTERNAL_CORRUPTION;
    }
    uivec_clear(vec);
    for(size_t i = 0; i < n ; i++){ // Since array is cleared, the safest method is pushing whatever in the provided array
        if(uivec_push(vec,list[i])){
            uivec_clear(vec);
            return ASSIGN_FAILED;
        }
    }
    return SUCCESS;
}

int uivec_push(UIVec* vec,unsigned num){
    if(!vec){
        return INVALID_PTR_PASSED;
    }
    if(uivec_corrupt_check(vec)){
        return INTERNAL_CORRUPTION;
    }
    if(vec->size <= maxSafeSize / 2){ // Prevents over-growth of the vector
        if(vec->size < vec->capacity){//If vector has room for the upcoming push
            vec->data[vec->size] = num;
            vec->size++;
            return SUCCESS;
        }
        else{// If vector has no room to push double the capacity and push the element
            unsigned* dummy = realloc(vec->data, sizeof(unsigned) * (vec->capacity * 2));
            if(!dummy){ //In case realloc fails, dummy prevents the memory address loss
                return REALLOC_FAILED;
            }
            vec->data = dummy;
            dummy = NULL;
            vec->capacity *= 2;
            vec->data[vec->size] = num;
            vec->size++;
            return SUCCESS;
        }
    }
    else{
        return AT_MAX_CAPACITY;
    }
}

int uivec_pop(UIVec* vec){
    if(!vec){
        return INVALID_PTR_PASSED;
    }
    if(uivec_corrupt_check(vec)){
        return INTERNAL_CORRUPTION;
    }
    if(vec->size == 0){
        return VEC_TOO_SMALL;

    }
    vec->size--;
    if(vec->size >= DEFAULT_CAPACITY && vec->size <= vec->capacity / 4){ //Prevents trashing by shrinking capacity to the DEFAULT_CAPACITY at very least
        unsigned* dummy = realloc(vec->data, (vec->capacity / 2) * sizeof(unsigned));
        if(!dummy){ //In case realloc fails, dummy prevents the memory address loss
            return REALLOC_FAILED;
        }
        vec->data = dummy;
        dummy = NULL;
        vec->capacity /= 2;
        return SUCCESS;
    }
    return SUCCESS;
}

int uivec_clear(UIVec* vec){ // Doesnt manipulate the vector capacity since user will be dealing with same amount elements as before the clear() call
    if(!vec){
        return INVALID_PTR_PASSED;
    }
    if(uivec_corrupt_check(vec)){
        return INTERNAL_CORRUPTION;
    }
    if(!vec->size){ 
        return SUCCESS;
    }
    vec->size = 0;
    return SUCCESS;
}

int uivec_free(UIVec** ptr_vec){
    if(!ptr_vec || !(*ptr_vec)){
        return INVALID_PTR_PASSED;
    }
    //Container Deallocation
    free((*ptr_vec)->data);
    (*ptr_vec)->data = NULL;
    //Struct Object Deallocation
    free(*ptr_vec);
    *ptr_vec = NULL;
    return SUCCESS;
}

static inline int ivec_corrupt_check(const IVec* vec){
    int hasCorrupt = 0;
    if(!vec->data){
        hasCorrupt++;
    }
    if(vec->size > vec->capacity){
        hasCorrupt++;
    }
    if(vec->capacity < DEFAULT_CAPACITY){
        hasCorrupt++;
    }
    if(vec->size > maxSafeSize || vec->capacity > maxSafeSize){
        hasCorrupt++;
    }
    return hasCorrupt;
}
static inline int cvec_corrupt_check(const CVec* vec){
    int hasCorrupt = 0;
    if(!vec->data){
        hasCorrupt++;
    }
    if(vec->size > vec->capacity){
        hasCorrupt++;
    }
    if(vec->capacity < DEFAULT_CAPACITY){
        hasCorrupt++;
    }
    if(vec->size > maxSafeSize || vec->capacity > maxSafeSize){
        hasCorrupt++;
    }
    return hasCorrupt;
}
static inline int dvec_corrupt_check(const DVec* vec){
    int hasCorrupt = 0;
    if(!vec->data){
        hasCorrupt++;
    }
    if(vec->size > vec->capacity){
        hasCorrupt++;
    }
    if(vec->capacity < DEFAULT_CAPACITY){
        hasCorrupt++;
    }
    if(vec->size > maxSafeSize || vec->capacity > maxSafeSize){
        hasCorrupt++;
    }
    return hasCorrupt;
}
static inline int uivec_corrupt_check(const UIVec* vec){
    int hasCorrupt = 0;
    if(!vec->data){
        hasCorrupt++;
    }
    if(vec->size > vec->capacity){
        hasCorrupt++;
    }
    if(vec->capacity < DEFAULT_CAPACITY){
        hasCorrupt++;
    }
    if(vec->size > maxSafeSize || vec->capacity > maxSafeSize){
        hasCorrupt++;
    }
    return hasCorrupt;
}
#endif

#ifdef DYNAVEC_ENABLE_ADVANCED
#ifdef DYNAVEC_ON
//define DYNAVEC_ENABLE_ADVANCED macro in order to access advanced methods
int ivec_get(const IVec* vec,size_t index){ //Considered Advance since this method is pre-conditional and does not report the failure
    return vec->data[index];
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

char cvec_get(const CVec* vec,size_t index){ //Considered Advance since this method is pre-conditional and does not report the failure
    return vec->data[index];
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

double dvec_get(const DVec* vec,size_t index){ //Considered Advance since this method is pre-conditional and does not report the failure
    return vec->data[index];
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

unsigned uivec_get(const UIVec* vec,size_t index){ //Considered Advance since this method is pre-conditional and does not report the failure
    return vec->data[index];
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
#endif
#endif
#endif
