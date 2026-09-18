#ifndef SORTING_H
#define SORTING_H

#include <pthread.h>
#include "config.h"
#include "bars.h"

typedef struct {
    Bar *bars;
    int length;
    pthread_mutex_t *lock;
} BarsData;

void *merge_sort(void *bars_data);
void *quick_sort_r(void *bars_data);
void draw_sc(int screen_width, int screen_height, Bar *bars, int count, int usable_width, int margin, Button **buttons, size_t b_length);
void delay_ms(int milisseconds);

#endif // SORTING_H
