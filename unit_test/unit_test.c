#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#define DYNAVEC_ON
#define DYNAVEC_ENABLE_ADVANCED
#include "../DynaVec.h"

#define RUN_TEST(test_func) \
    do { \
        printf("Running " #test_func "...\n"); \
        test_func(); \
        printf("[PASSED] " #test_func "\n\n"); \
    } while(0)


void test_ivec_basic_operations(void) {
    IVec* vec = ivec_init();
    assert(vec != NULL);
    assert(ivec_size(vec) == 0);
    assert(ivec_capacity(vec) == DEFAULT_CAPACITY);
    assert(ivec_corrupt_check(vec) == 0);

    assert(ivec_push(vec, 10) == SUCCESS);
    assert(ivec_push(vec, 20) == SUCCESS);
    assert(ivec_size(vec) == 2);

    int val = 0;
    assert(ivec_sget(vec, 0, &val) == SUCCESS);
    assert(val == 10);
    assert(ivec_sget(vec, 1, &val) == SUCCESS);
    assert(val == 20);

    assert(ivec_set(vec, 0, 99) == SUCCESS);
    assert(ivec_sget(vec, 0, &val) == SUCCESS);
    assert(val == 99);

    assert(ivec_pop(vec) == SUCCESS);
    assert(ivec_size(vec) == 1);

    assert(ivec_clear(vec) == SUCCESS);
    assert(ivec_size(vec) == 0);

    assert(ivec_free(&vec) == SUCCESS);
    assert(vec == NULL);
}

void test_error_handling(void) {
    IVec* vec = ivec_init();
    int val;

    assert(ivec_sget(vec, 0, &val) == OOB_ACCESS);
    assert(ivec_set(vec, 0, 50) == OOB_ACCESS);

    assert(ivec_pop(vec) == VEC_TOO_SMALL);

    assert(ivec_sget(NULL, 0, &val) == INVALID_PTR_PASSED);
    assert(ivec_size(NULL) == SIZE_MAX);
    assert(ivec_capacity(NULL) == SIZE_MAX);

    ivec_free(&vec);
}

void test_assignment_and_advanced(void) {
    IVec* vec = ivec_init();
    int initial_data[] = {1, 2, 3, 4, 5};
    
    assert(ivec_assign(vec, 5, initial_data) == SUCCESS);
    assert(ivec_size(vec) == 5);
    
    assert(ivec_get(vec, 2) == 3);

    int* begin = ivec_begin(vec);
    const int* cend = ivec_cend(vec);
    
    assert(*begin == 1);
    assert(*(cend - 1) == 5);

    ivec_free(&vec);
}

void test_other_datatypes(void) {
    
    CVec* cvec = cvec_init();
    assert(cvec_push(cvec, 'A') == SUCCESS);
    assert(cvec_get(cvec, 0) == 'A');
    cvec_free(&cvec);

    DVec* dvec = dvec_init();
    assert(dvec_push(dvec, 3.14159) == SUCCESS);
    assert(dvec_get(dvec, 0) == 3.14159);
    dvec_free(&dvec);

    UIVec* uivec = uivec_init();
    assert(uivec_push(uivec, 4294967295U) == SUCCESS);
    assert(uivec_get(uivec, 0) == 4294967295U);
    uivec_free(&uivec);
}



void test_stress_reallocation(void) {
    IVec* vec = ivec_init();
    const size_t STRESS_AMOUNT = 1000000; 
    for (size_t i = 0; i < STRESS_AMOUNT; i++) {
        assert(ivec_push(vec, (int)i) == SUCCESS);
    }

    assert(ivec_size(vec) == STRESS_AMOUNT);
    assert(ivec_capacity(vec) >= STRESS_AMOUNT);
    assert(ivec_corrupt_check(vec) == 0);     
    int val;
    assert(ivec_sget(vec, 500000, &val) == SUCCESS);
    assert(val == 500000);

    for (size_t i = 0; i < STRESS_AMOUNT; i++) {
        assert(ivec_pop(vec) == SUCCESS);
    }

    assert(ivec_size(vec) == 0);
    assert(ivec_capacity(vec) == DEFAULT_CAPACITY || ivec_capacity(vec) <= 64);

    ivec_free(&vec);
}


int main(void) {
    printf("==========================================\n");
    printf("   Launching Dynavec Test Unit\n");
    printf("==========================================\n\n");

    RUN_TEST(test_ivec_basic_operations);
    RUN_TEST(test_error_handling);
    RUN_TEST(test_assignment_and_advanced);
    RUN_TEST(test_other_datatypes);

    clock_t start = clock();
    RUN_TEST(test_stress_reallocation);
    clock_t end = clock();
    
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("==========================================\n");
    printf("ALL TESTS PASSED SUCCESSFULLY!\n");
    printf("Stress test completed in %f seconds.\n", time_spent);
    printf("==========================================\n");

    return 0;
}
