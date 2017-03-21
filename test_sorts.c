#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorts.h"

/* Checks if *len* elements of *array* are in ascending order*/
int verify(int* array, int len){
    int ii;
    if (len < 2)
        return 1;
    for (ii = 0; ii < len - 1; ii++)
        if (array[ii] > array[ii + 1]){
            printf("%d > %d\tfor indicies %d, %d\n", array[ii], array[ii + 1], ii, ii+1);
            return 0;
        }
    return 1;
}

/* Constructs testcases of length *len* in *array**/
void build_case(int* array, int len, int reverse){
    int ii;
    /* If reverse, build the array [len, ..., 1]*/
    if (reverse)
        for (ii = 0; ii < len; ii++)
            array[ii] = len - ii;
    else
        for (ii = 0; ii < len; ii++)
            array[ii] = rand() % 100;
}

#define NUM_CASES 11
#define MAX_CASE 2048
int main(){
    int cases[NUM_CASES] = {0, 1, 2, 3, 4, 8,  10, 100, 1025, 2047, MAX_CASE};
    int to_sort[MAX_CASE];
    int ii;
    srand(1);
    for (ii = 0; ii < NUM_CASES; ii++){
        int case_length = cases[ii];
        int passed;
        build_case(to_sort, case_length, 1);
//        mt_wrapper(to_sort, case_length);
        sort(to_sort, case_length);
        passed = verify(to_sort, case_length);
        if (!passed)
            print_array(to_sort, case_length);
        printf("Case: %d %s\n", case_length, passed ? "PASS" : "FAIL");
    }
    return 0;
}
