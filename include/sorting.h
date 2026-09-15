#include <pthread.h>


#ifndef SORTING_H
#define SORTING_H

typedef struct {
    int *numbers;
    int length;
    pthread_mutex_t *lock;
} NumData;

void *merge_sort(void *num_data);
void *quick_sort_r(void *num_data);

#endif // SORTING_H
