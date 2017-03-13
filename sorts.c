#include "sorts.h"

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

void mt_sort(int array[], int size){
    if (size < 2)
        return;
    int mid = (int)(size / 2);
    sort(array + mid, size - mid);
    sort(array, mid);
    merge(array, mid, array + mid, size - mid);
}
