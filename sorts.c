#include "sorts.h"

#include <time.h>

/* This file defines a series of sorting functions to be
    made available in our python module via the CPython C-API.
*/

void bubble(int array[], int size){
    int unsorted = 1;
    int ii;
    while (unsorted){
        for(ii = 0; ii < size - 1; ii++){
            if(array[ii] > array[ii+1]){
                int tmp = array[ii+1];
                array[ii+1] = array[ii];
                array[ii] = tmp;
            }
        }
        unsorted = 0;
        for(ii = 0; ii < size - 1; ii++)
            unsorted = unsorted || (array[ii] > array[ii+1]);
    }
}

void print_array(int array[], int size){
    int ii;
    for(ii = 0; ii < size - 1; ii++){
        printf("%d, ", array[ii]);
    }
    printf("%d\n", array[ii]);
}

void merge(int left[], int lmax, int right[], int rmax){
    int loc = 0, ii = 0, jj = 0;
    int local[rmax + lmax];
    while(ii < lmax && jj < rmax){
        if(left[ii] > right[jj]){
            local[loc++] = right[jj++];
        } else {
            local[loc++] = left[ii++];
        }
    }
    while(ii < lmax)
        local[loc++] = left[ii++];
    while(jj < rmax){
        local[loc++] = right[jj++];
    }
    for(ii = 0; ii < loc; ii++)
        left[ii] = local[ii];
}

void sort(int array[], int size){
    if (size < 2)
        return;
    int mid = (int)(size / 2);
    sort(array + mid, size - mid);
    sort(array, mid);
    merge(array, mid, array + mid, size - mid);
}

typedef struct {
    int *base;
    int length;
} Param;

int mt_wrapper(int* array, int len){
    Param* param = malloc(sizeof(Param));
    if (param == NULL) return -1;
    param->base = array;
    param->length = len;
    mt_sort( (void*) param);
    free(param);
    return 0;
}

void* mt_sort(void* input){
    Param* param = (Param*)input;
    int size = param->length;
    if (size < 2)
        return (void*) 0;
    int *array = param->base;
    int l_resp, r_resp;
    int mid = (int)(size / 2);
    pthread_t left, right;
    Param* l_param;
    Param* r_param;

    l_param = (Param*)malloc(sizeof(Param));
    if (l_param == NULL) return (void*)-1;
    l_param->base = array;
    l_param->length = mid;

    r_param = (Param*)malloc(sizeof(Param));
    if (r_param == NULL) return (void*)-1;
    r_param->base = array + mid;
    r_param->length = size - mid;

    l_resp = pthread_create(&left, NULL, mt_sort, (void *) l_param);
    r_resp = pthread_create(&right, NULL, mt_sort, (void *) r_param);
    if(r_resp)
        printf("ERROR: pthread_create(right) returned code %d\n", r_resp);
    if(l_resp)
        printf("ERROR: pthread_create(left) returned code %d\n", l_resp);
    pthread_join(right, NULL);
    pthread_join(left, NULL);
    free(l_param);
    free(r_param);

    merge(array, mid, array + mid, size - mid);
}
