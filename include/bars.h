#ifndef BARS_H
#define BARS_H

#include <raylib.h>

typedef enum {
    IDLE,
    COMPARED,
    MOVED, // Only valid when moved within the main bars array e.g. invalid when a bar is copied into a subarray
    SETTLED
} BarState;


typedef struct {
    int value;
    BarState state;
} Bar;

int find_margin(int screen_width, int count);
void fisher_yates_shuffle(Bar *bars, int count);
Bar *init_bars(int count);
void draw_bars(int screen_width, int screen_height, Bar *bars, int count, int usable_width, int margin);

#endif // BARS_H
