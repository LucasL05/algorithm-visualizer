#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#include "sorting.h"
#include "bars.h"

// 1000 mseconds = 1 second
void delay_ms(int milisseconds) {
    struct timespec ts;
    // ts = timespec and tv = timevalue
    ts.tv_sec = milisseconds / 1000;
    ts.tv_nsec = (milisseconds % 1000) * 1000000L;
    nanosleep(&ts, NULL);
}


// Notes: This merge sort could become even better by implementing the ping pong optimization.

void merge(int *numbers, int *temp, int l, int r, int middle, pthread_mutex_t lock) {

    int i = l;
    int j = middle + 1; // this is where the second array starts
    int t_index = 0;  // temporary array's index.

    while (i <= middle && j <= r) { 
        if (numbers[i] < numbers[j]) {
            temp[t_index] = numbers[i];
            i ++;
        }

        else {
            temp[t_index] = numbers[j];
            j ++;
        }

        t_index ++;
    }

    //  Appends to *temp* what was left behind in *numbers*[l, r] 
    if (i <= middle) {
        for (; i <= middle; i++, t_index++) {
            temp[t_index] = numbers[i];
        }
    }

    else {
        for (; j <= r; j++, t_index++) {
            temp[t_index] = numbers[j];
        }
    }

    // r - l +1 is the temp array's size that currently being used.
    for (int i = 0; i < (r - l + 1); i ++) {
        pthread_mutex_lock(&lock);
        numbers[l + i] = temp[i];
        pthread_mutex_unlock(&lock);
        delay_ms(5);
    }
}

// *l* is the left index and *r* is the right index
// that contains the sub array to be sorted.
// -  the interval [l, r] is inclusive at both sides;
// - *l* and *r* must be non-negative integers.
void merge_sort_recursive(int *numbers, int *temp, int l, int r, pthread_mutex_t lock)
// check if *r* and *l* are positive. 

{
    if (l < r) {
        int middle = l + (r - l) / 2; // It seems that the simpler (l + r) / 2 would cause an overflow with very large integers, so we use that other formula to avoid having to add two big numbers. 
        merge_sort_recursive(numbers, temp, l, middle, lock);
        merge_sort_recursive(numbers, temp, middle + 1, r, lock);
        merge(numbers, temp, l, r, middle, lock); 
    } 
} 

// call merge_sort_recursive if you only want to sort part of the array;
// - returns a void* in order to conform to pthread's requirements
void *merge_sort(void *num_data) {
    // 
    NumData *data = (NumData *) num_data;
    int *numbers = data->numbers;
    int num_length = data->length;
    pthread_mutex_t lock = data->lock;
    pthread_mutex_init(&lock, NULL);


    int *temp = (int *) malloc(sizeof(int) * num_length);
    merge_sort_recursive(numbers, temp, 0, num_length - 1, lock);
    free(temp);

    return NULL;
}

void quick_sort(void)
{
}
