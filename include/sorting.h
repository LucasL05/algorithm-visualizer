#ifndef SORTING_H
#define SORTING_H

#include <pthread.h>
#include "config.h"

typedef struct {
    int *numbers;
    int length;
    pthread_mutex_t *lock;
} NumData;

void *merge_sort(void *num_data);
void *quick_sort_r(void *num_data);
void draw_sc(int screen_width, int screen_height, int *numbers, int count, int usable_width, int margin, Button **buttons, size_t b_length);

#endif // SORTING_H
