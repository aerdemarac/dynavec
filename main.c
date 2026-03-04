#include "vector_adv.h"
#include <stdio.h>


int main(){
    IVec* vec = ivec_init();
    for(int i = 0; i < 1000000 ; i++){
        ivec_push(vec, i);
    }
    ivec_set(vec,ivec_size(vec) - 2, 69);
    ivec_pop(vec);
    ivec_set(vec,ivec_size(vec) - 2,99);
    ivec_push(vec, 19);
    ivec_assign(vec,10,(int[]){1,2,3,4,5,6,7,8,9,0});
    for(int i = 0; i < 2000000; i++){
        ivec_push(vec, 31);
    }
    for(size_t i = 0; i < 1000000; i++){
        ivec_pop(vec);
    }
    ivec_set(vec,500000,69);
    for(size_t i = ivec_size(vec); i >= 500000; i--){
        ivec_pop(vec);
    }
    ivec_clear(vec);
    ivec_push(vec,29);
    ivec_clear(vec);
    ivec_free(&vec);
    return 0;
}
