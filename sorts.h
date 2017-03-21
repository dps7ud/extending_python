#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

/* C Header file for sorts.c*/

void bubble(int array[], int size);
void print_array(int array[], int size);
void merge(int left[], int lmax, int right[], int rmax);
void sort(int array[], int size);
void* mt_sort(void* param);
int mt_wrapper(int* array, int len);
