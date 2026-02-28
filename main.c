#include <math.h>
#include "vector.h"


int main(){
    IVec* vec = ivec_init();
    size_t size = 1;
    int arr[size];
    for(size_t i = 0; i<size;i++){
        arr[i] = i;
    }
    ivec_assign(vec, size,arr);
    ivec_set(vec,0,69);
    ivec_push(vec,31);
    ivec_clear(vec);
    ivec_free(&vec);
    return 0;
}
