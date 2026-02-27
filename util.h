#include <stdlib.h>
#pragma once

size_t next_powerof_two(size_t num){
    if(num <= 1){
        return 1;
    }
    size_t pow = 1;
    while(pow < num){ // Haven't handled the case where num is exaclty power of to since 20 * capacity multipler / 2 cannot be power of two
        pow *= 2;
    }
    return pow;
}
