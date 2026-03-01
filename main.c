#include "vector.h"
#include <stdio.h>


int main(){
    IVec* vec = ivec_init();
    for(int i = 0; i < 1000000; i++){
        ivec_push(vec, i);
    }
    ivec_set(vec,ivec_size(vec) - 2, 69);
    ivec_pop(vec);
    printf("%d",ivec_get(vec, ivec_size(vec) - 1));
    ivec_pop(vec);
    ivec_push(vec, 2);
    size_t vec_size = ivec_size(vec);
    for(size_t i = 0 ; i < vec_size ; i++){
        ivec_pop(vec);
    }
    ivec_free(&vec);
    printf("%zu",ivec_size(vec));
    return 0;
}
