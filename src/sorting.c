#include "sorting.h"
#include "bars.h"


// I mean, this is weird, since I'm not actually mergin anything... should probably check this out later.

/* Sorts *numbers[*l*:*j*].
    l < j and j = l + 1 
*/
void merge(int *numbers, int l, int r, int middle) {
    for (int i = l; i <= middle; i ++) {
        int j = middle + i;
        if (numbers[i] > numbers[j]) {
            int temp = numbers[j];
            numbers[j] = numbers[l];
            numbers[l] = temp;
            printf("ola");
        }
    }
}
// *l* is the left index adn *r* is the right index
// that contains the sub array to be sorted.
// - If you'd like to sort the whole array, 
// insert l = 0 and r = the array's rightmost index.
// - *l* and *r* must be non-negative integers.
void merge_sort(int *numbers, int l, int r)
// check if *r* and *l* are positive. 
{
    if (l < r) {
        int middle = (l + r) / 2;
        merge_sort(numbers, l, middle);
        merge_sort(numbers, middle + 1, r);
        merge(numbers, l, r, middle); 
    } 
} 
void quick_sort(void)
{
}
