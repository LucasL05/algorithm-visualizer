#include "sorting.h"
#include "bars.h"


// I mean, this is weird, since I'm not actually mergin anything... should probably check this out later. 
//                                          !!! Well, well, well lol

/* Sorts *numbers[*l*:*j*].
    l < j and j = l + 1 
*/
void merge(int *numbers, int l, int r, int middle) {
    int temp[r - l + 1]; // this 1 would be necessary if the input was *the array's length**. Then it would be like Python.

    int i = l;
    int j = middle + 1; // this is where the second array starts
    int t_index = 0;  // temporary array's index.
    while (i <= middle && j <= r) { // This while loop definetly should be a subfunction. I wouldn't even neeed to define j and so on here. I'd be just passing them as parameters and changing their names on the subfuction's header.
        if (numbers[i] < numbers[j]) {
            temp[t_index] = numbers[i];
            i += 1;
        }

        else {
            temp[t_index] = numbers[j];
            j += 1;
        }

        t_index ++;
    }

    //verifies if some items in some list wasn't seen and inserts them in temp;
    if (i <= middle) { // this one should also be a subfunction.
        for (int x = i; i <= middle; x++ ) { // ****Does it make sense to define x as i?
            temp[t_index] = numbers[x];
            t_index++;
        } 
    }

        if (j <= r) { // this one should also be a subfunction.
        for (int x = i; i <= r; x++ ) { // ****Does it make sense to define x as i?
            temp[t_index] = numbers[x];
            t_index++;
        } 
    }


    // r - l +1 is the temp array's size.
    for (int i = 0; i < (r - l + 1); i ++) {
        numbers[l + i] = temp[i];
    }
}

// *l* is the left index adn *r* is the right index
// that contains the sub array to be sorted.
// - If you'd like to sort the whole array, 
// insert l = 0 and r = the array's rightmost index.
// - *l* and *r* must be non-negative integers.
void merge_sort(int *numbers, int l, int r)
// check if *r* and *l* are positive. 
// doesn't really work, but it's getting better
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
