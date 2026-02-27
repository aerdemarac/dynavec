#include <malloc.h>


typedef struct IVec IVec;
 
typedef struct CVec CVec;

typedef struct DVec DVec;

typedef struct UIVec UIVec;


IVec* ivec_init();

void ivec_push(IVec* vec,int num);

void ivec_free(IVec** vec);
