#include <stdio.h>
#include "vector_adv.h"

void size_capacity_t(void){
    printf("Null ptr Passed, Size: %zu Capacity: %zu",ivec_size(NULL),ivec_capacity(NULL));
    return;
}
void size_capacity_t2(IVec* vec){
    ivec_clear(vec);
    printf("Vec cleared, Size: %zu Capacity: %zu",ivec_size(vec),ivec_capacity(vec));
    return;
}
int sget_t(void){
    int num;
    return ivec_sget(NULL, 10,&num );
}
int sget_t2(IVec* vec){
    return ivec_sget(vec, 10,NULL );
}
int sget_t3(IVec* vec){
    int num;
    return ivec_sget(vec, SIZE_MAX,&num);
}
int sget_t4(IVec* vec){
    int num;
    return ivec_sget(vec, ivec_size(vec),&num);
}
int sget_t5(IVec* vec){
    int num;
    return ivec_sget(vec, ivec_size(vec) - 1,&num);
}
int set_t(void){
    return ivec_set(NULL,0,31);
}
int set_t2(IVec* vec){
    return ivec_set(vec,31,31);
}
int set_t3(IVec* vec){
    ivec_clear(vec);
    return ivec_set(vec,0,31);
}
int set_t4(IVec* vec){
    ivec_push(vec,69);
    ivec_assign(vec, 1,(int[]){31});
    return ivec_set(vec,0,69);
}
int push_t(IVec* vec){
    for(int i = 0 ; i < 100000000; i++){
        ivec_push(vec,i);
    }
    int num;
    printf("Size: %zu, Back: %d",ivec_size(vec),ivec_get(vec,ivec_size(vec)-1));
    return ivec_sget(vec, ivec_size(vec) - 1, &num);
}
void push_t2(IVec* vec){
    for(int i = 0; i < 69 ; i++){
        for(size_t u = 0 ,max= (128 - ivec_size(vec)); u < max; u++){
            ivec_push(vec,8);
        }
        for(size_t d = 0,size=ivec_size(vec); d < size; d++){
            ivec_pop(vec);
        }
    }
    printf("Size: %zu , Capacity= %zu ",ivec_size(vec),ivec_capacity(vec));
    ivec_assign(vec, 20,(int[]){1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20});
    printf("Size: %zu , Capacity= %zu ....",ivec_size(vec),ivec_capacity(vec));
    return;
}
int pop_t(IVec* vec){
    return ivec_pop(vec);
}
int pop_t2(IVec* vec){
    ivec_clear(vec);
    return ivec_pop(vec);
}
int main(){
    IVec* vec = ivec_init();
    printf("Ret_code: %d\n",pop_t2(vec));
    ivec_free(&vec);
    return 0;
}
