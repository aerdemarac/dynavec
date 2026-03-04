#include "vector_adv.h"
#include <stdio.h>


int main(){
    IVec* vec = ivec_init();
    for(int i = 0; i < 12; i++){
        ivec_push(vec, i);
    }
    printf("%d",ivec_get(vec, 5));
    ivec_free(&vec);
    return 0;
}
