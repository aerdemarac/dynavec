#include "vector.h"
#include <stdio.h>


int main(){
    IVec* vec = ivec_init();
    ivec_pop(vec);
    ivec_free(&vec);
    return 0;
}
