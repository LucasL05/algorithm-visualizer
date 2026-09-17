#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdio.h>

// Definetly should add a specs tab for every algorithm
#include "sorting.h"
#include "bars.h"
#include "main_menu.h"
#include "config.h"
#include "screen.h"

// 1000 mseconds = 1 second
void delay_ms(int milisseconds) {
    struct timespec ts;
    // ts = timespec and tv = timevalue
    ts.tv_sec = milisseconds / 1000;
    ts.tv_nsec = (milisseconds % 1000) * 1000000L;
    nanosleep(&ts, NULL);
}


// Notes: This merge sort could become even better by implementing the ping pong optimization.

void merge(int *numbers, int *temp, int l, int r, int middle, pthread_mutex_t *lock) {

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
        pthread_mutex_lock(lock);
        numbers[l + i] = temp[i];
        pthread_mutex_unlock(lock);
        delay_ms(12);
    }
}

// *l* is the left index and *r* is the right index
// that contains the sub array to be sorted.
// -  the interval [l, r] is inclusive at both sides;
// - *l* and *r* must be non-negative integers.
void merge_sort_recursive(int *numbers, int *temp, int l, int r, pthread_mutex_t *lock)
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
    pthread_mutex_t *lock = data->lock;

    int *temp = (int *) malloc(sizeof(int) * num_length);
    merge_sort_recursive(numbers, temp, 0, num_length - 1, lock);
    free(temp);

    return NULL;
}

// ** Hoare's Partition from CLRS*
// returns an index of *numbers* so that all values
// on its left are smaller than *p* 
// and all values on its right are greater than it
int partition(int *numbers, int p, int r, pthread_mutex_t *lock)
{
    int pivot = numbers[p];
    int i = p - 1;
    int j = r + 1;

    while (true) 
    {

        do {
            j--;
        } while(numbers[j] > pivot);

        do {
            i++;
        } while(numbers[i] < pivot);

        if (i < j) 
        {
            int temp = numbers[i];
            pthread_mutex_lock(lock);
            numbers[i] = numbers[j];
            numbers[j] = temp;
            pthread_mutex_unlock(lock);

            delay_ms(50);
        }
        else 
        {
            return j;
        }
    }

}

// returns an index of *numbers* so that all values 
// on its left are smaller than a random pivot
// and all values on its right are greater than 
// that same pivot
int partition_r(int *numbers, int p, int r, pthread_mutex_t *lock)
    // srand is the same in main and it's the same for the whole program.
    // I hope that won't cause any problems. 
{
    // generate random pivot index within the sub-array's bounds
    int i = p + rand() % (r - p + 1);

    // exchange the current pivot with the random one
    int temp = numbers[p];
    numbers[p] = numbers[i];
    numbers[i] = temp;
    return partition(numbers, p, r, lock);
}

// *numbers* is the array to be sorted;
// *p* -> pivot (that's also the leftmost index);
// *r* -> rightmost index.
void quick_sort_r_recursive(int *numbers, int p, int r, pthread_mutex_t *lock) 
{
    if (p < r) {
        int q = partition_r(numbers, p, r, lock);
        quick_sort_r_recursive(numbers, p, q, lock);
        quick_sort_r_recursive(numbers, q + 1, r, lock);
    }
}

// Quick sort with random pivot
void *quick_sort_r(void *num_data)
{
    NumData *data = (NumData *) num_data;
    int *numbers = data->numbers;
    int num_length = data->length;
    pthread_mutex_t *lock = data->lock;

    quick_sort_r_recursive(numbers, 0, num_length - 1, lock);
    return NULL;

}

// sc = sorting screen
void draw_sc(int screen_width, int screen_height, int *numbers, int count, int usable_width, int margin, Button **buttons, size_t b_length) 
{
    draw_bars(screen_width, screen_height, numbers, count, usable_width, margin);

    for (int i = 0; i < b_length; i++)
    {
        draw_button(buttons[i]);
    }

}