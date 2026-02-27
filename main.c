#include <math.h>
#include "vector.h"


int main(){
    IVec* vec = ivec_init();
    for(size_t i = 0 ; i < ivec_capacity(vec); i++){
        ivec_push(vec,pow(2,i));
    }
    size_t index = 5;
    printf("pow(2,%zu) = %d",index,ivec_get(vec,index));
    ivec_free(&vec);
    return 0;
}
