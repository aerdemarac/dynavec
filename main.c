#include <math.h>
#include "vector.h"


int main(){
    IVec* vec = ivec_init();
    size_t lim = pow(10,6);
    for(size_t i = 0; i < lim ; i++ ){
        ivec_push(vec, i);
    }
    for(size_t i = 0; i < lim ; i++ ){
        ivec_pop(vec);
    }
    ivec_free(&vec);
    return 0;
}
