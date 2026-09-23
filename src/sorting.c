#include <stdlib.h>
#include <pthread.h>
#include <time.h> //bars --> bars
#include <stdio.h>


// Definetly should add a specs tab for every algorithm
#include "sorting.h"
#include "bars.h"
#include "menus.h"
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

void merge(Bar *bars, Bar *temp, int l, int r, int middle, pthread_mutex_t *lock, int delay, atomic_bool *stop_requested) {

    if (atomic_load(stop_requested)) return;

    int i = l;
    int j = middle + 1; // this is where the second array starts
    int t_index = 0;  // temporary array's index.

    while (i <= middle && j <= r) { 
        pthread_mutex_lock(lock);
        bars[i].state = COMPARED;
        bars[j].state = COMPARED;
        pthread_mutex_unlock(lock);

        if (!atomic_load(stop_requested)) delay_ms(delay * 2);

        if (bars[i].value < bars[j].value) {
            temp[t_index] = bars[i];
            i ++;
        }
        else {
            temp[t_index] = bars[j];
            j ++;
        }

        t_index ++;
    }

    //  Appends to *temp* what was left behind in *bars*[l, r] 
    if (i <= middle) {
        for (; i <= middle; i++, t_index++) {
            temp[t_index] = bars[i];
        }
    }

    else {
        for (; j <= r; j++, t_index++) {
            temp[t_index] = bars[j];
        }
    }

    // r - l +1 is the temp array's size that's currently being used.
    for (int i = 0; i < (r - l + 1); i ++) {
        pthread_mutex_lock(lock);
        bars[l + i] = temp[i];
        bars[l + i].state = MOVED;
        pthread_mutex_unlock(lock);
        if (!atomic_load(stop_requested)) delay_ms(delay);
    }
}

// *l* is the left index and *r* is the right index
// that contains the sub array to be sorted.
// -  the interval [l, r] is inclusive at both sides;
// - *l* and *r* must be non-negative integers.
// - Cleanly stops if *stop_requested* == true.
void merge_sort_recursive(Bar *bars, Bar *temp, int l, int r, pthread_mutex_t *lock, int delay, atomic_bool *stop_requested)
// check if *r* and *l* are positive. Maybe ******** 
{
    if (atomic_load(stop_requested)) return;

    if (l < r) {
        int middle = l + (r - l) / 2; // It seems that the simpler (l + r) / 2 would cause an overflow with very large integers, so we use that other formula to avoid having to add two large indexes. 
        merge_sort_recursive(bars, temp, l, middle, lock, delay, stop_requested);
        merge_sort_recursive(bars, temp, middle + 1, r, lock, delay, stop_requested);
        merge(bars, temp, l, r, middle, lock, delay, stop_requested); 
    } 
} 

// call merge_sort_recursive if you only want to sort part of the array;
// - returns a void* in order to conform to pthread's requirements
void *merge_sort(void *sorter_data) {
    // 
    SorterData *data = (SorterData *) sorter_data;
    Bar *bars = data->bars;
    int bars_length = data->length;
    pthread_mutex_t *lock = data->lock;
    int delay = 2000 / bars_length;
    atomic_bool *stop_requested = data->stop_requested;

    Bar *temp = (Bar *) malloc(sizeof(Bar) * bars_length);
    merge_sort_recursive(bars, temp, 0, bars_length - 1, lock, delay, stop_requested);
    free(temp);

    return NULL;
}

// ** Hoare's Partition from CLRS*
// returns an index of *bars* so that all values
// on its left are smaller than *p* 
// and all values on its right are greater than it
int partition(Bar *bars, int p, int r, pthread_mutex_t *lock, int delay, atomic_bool *stop_requested)
{
    Bar pivot = bars[p];
    int i = p - 1;
    int j = r + 1;

    while (true) 
    {

        do {
            j--;
            pthread_mutex_lock(lock);
            bars[j].state = COMPARED;
            pthread_mutex_unlock(lock);
            if (!atomic_load(stop_requested)) delay_ms(delay);
        } while(bars[j].value > pivot.value);

        do {
            i++;
            pthread_mutex_lock(lock);
            bars[i].state = COMPARED;
            pthread_mutex_unlock(lock);
            if (!atomic_load(stop_requested)) delay_ms(delay);
        } while(bars[i].value < pivot.value);

        pthread_mutex_lock(lock);
        pivot.state = COMPARED;
        pthread_mutex_unlock(lock);
        if (!atomic_load(stop_requested)) delay_ms(delay);

        if (i < j) 
        {
            //Exchanges bars[i] with bars[j]
            Bar temp = bars[i];
            pthread_mutex_lock(lock);
            bars[i] = bars[j];
            bars[j] = temp;

            bars[i].state = MOVED;
            bars[j].state = MOVED;
            pthread_mutex_unlock(lock);
            if (!atomic_load(stop_requested)) delay_ms(delay);
        }
        else 
        {
            return j;
        }
    }

}

// Partiton with random pivot
int partition_r(Bar *bars, int p, int r, pthread_mutex_t *lock, int delay, atomic_bool *stop_requested)
    // srand is the same in main and it's the same for the whole program.
    // I hope that won't cause any problems. 
{
    // generate random pivot index within the sub-array's bounds
    int i = p + rand() % (r - p + 1);

    // exchange the current pivot with the random one
    pthread_mutex_lock(lock);
    Bar temp = bars[p];
    bars[p] = bars[i]; // Should I change their states to compared here? It'd be effective for such a brief moment
    bars[i] = temp;

    bars[p].state = MOVED;
    bars[i].state = MOVED;
    pthread_mutex_unlock(lock);
    if (!atomic_load(stop_requested)) delay_ms(delay);
    return partition(bars, p, r, lock, delay, stop_requested);
}

// *bars* is the array to be sorted;
// *p* -> pivot (that's also the leftmost index);
// *r* -> rightmost index.
void quick_sort_r_recursive(Bar *bars, int p, int r, pthread_mutex_t *lock, int delay, atomic_bool *stop_requested) 
{
    if (atomic_load(stop_requested)) return;

    if (p < r) {
        int q = partition_r(bars, p, r, lock, delay, stop_requested);
        quick_sort_r_recursive(bars, p, q, lock, delay, stop_requested);
        quick_sort_r_recursive(bars, q + 1, r, lock, delay, stop_requested);
    }
}

// Quick sort with random pivot
void *quick_sort_r(void *sorter_data)
{
    SorterData *data = (SorterData *) sorter_data;
    Bar *bars = data->bars;
    int bars_length = data->length;
    pthread_mutex_t *lock = data->lock;
    int delay = 1500 / bars_length; // In milisseconds
    atomic_bool *stop_requested = data->stop_requested;

    quick_sort_r_recursive(bars, 0, bars_length - 1, lock, delay, stop_requested);
    return NULL;

}

// sc = sorting screen
void draw_sc(int screen_width, int screen_height, Bar *bars, int count, int usable_width, int margin, Button **buttons, size_t b_length) 
{
    draw_bars(screen_width, screen_height, bars, count, usable_width, margin);

    for (int i = 0; i < b_length; i++)
    {
        draw_button(buttons[i]);
    }

}

void stop_sorting(pthread_t r_sort, atomic_bool *stop_requested, Bar *bars, int count)
{
    atomic_store(stop_requested, true);
    pthread_join(r_sort, NULL);
    fisher_yates_shuffle(bars, count);
    atomic_store(stop_requested, false);
}