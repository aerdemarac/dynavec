#include <stdio.h>
#include "vector.h"


int main(){
    IVec* vec = ivec_init();
    ivec_push(vec, 5);
    ivec_push(vec, 8);
    ivec_push(vec, 1);
    ivec_push(vec, 9);
    ivec_free(&vec);
    return 0;
}
