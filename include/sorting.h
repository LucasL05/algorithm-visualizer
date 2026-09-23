#ifndef SORTING_H
#define SORTING_H

#include <pthread.h>
#include <stdatomic.h>

#include "config.h"
#include "bars.h"

typedef struct {
    Bar *bars;
    int length;
    pthread_mutex_t *lock;
    atomic_bool *stop_requested;
} SorterData;

void *merge_sort(void *bars_data);
void *quick_sort_r(void *bars_data);
void draw_sc(WindowDimensions w_dimensions, Bar *bars, int count, int usable_width, int margin, Button *buttons, size_t b_length);
void delay_ms(int milisseconds);
void stop_sorting(pthread_t r_sort, atomic_bool *stop_requested, Bar *bars, int count);

#endif // SORTING_H
