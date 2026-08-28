#include <pthread.h>


#ifndef SORTING_H
#define SORTING_H

typedef struct {
    int *numbers;
    int length;
    pthread_mutex_t lock;
} NumData;

void *merge_sort(void *num_data);
void quick_sort(void);

#endif // SORTING_H
