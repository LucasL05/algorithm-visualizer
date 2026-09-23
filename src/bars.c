#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>

#include "config.h"
#include "bars.h"
#include "sorting.h"

int find_margin(int screen_width, int count)
{
    int rest = screen_width % count;

    if (rest % 2 == 0) return rest;
    if (count % 2 == 1) return rest + count;
    else return 0;

    /* Maybe returninig 0 here isn't really the best option, but if rest isn't even
    and COUNT is, there's really no way to make all bar's width equal by changing just the margin.
    Maybe there's a way if I change the bar's width algorithm, but that may be complicated. */
}

void fisher_yates_shuffle(Bar *bars, int count)
{
    // Randomizes the values in the array.
    for (int i = count - 1; i >= 0; i--)
    {
        int r = rand() % (i + 1);
        Bar temp = bars[i];
        bars[i] = bars[r];
        bars[r] = temp;
    }
}

Bar *init_bars(int count)
{
    Bar *bars = (Bar*) malloc(count * sizeof(Bar));
    for (int i = 0; i < count; i++)
    {
        bars[i].value = i + 1;
        bars[i].state = IDLE;
    }
    fisher_yates_shuffle(bars, count);
    return bars;
}

void draw_bars(WindowDimensions w_dimensions, Bar *bars, int count, int usable_width, int margin)
{
    for (int i = 0; i < count; i++)
    {
        int value = bars[i].value; // there was a +1 here
        int bar_height = w_dimensions.height * 0.65 * value / count;

        // Calculate exact pixel boundaries for current and next bar
        int x_current = (i * usable_width / count) + margin/2;
        int x_next = ((i + 1) * usable_width / count) + margin/2;

        // Bar width fills the space between current and next boundary minus the gap
        int bar_width = (x_next - x_current) - GAP;

        // Prevent negative widths if COUNT is extremely large
        if (bar_width < 1) bar_width = 1;

        if (i == value - 1) bars[i].state = SETTLED;

        int available_height = w_dimensions.height * 0.75;
        switch(bars[i].state) {
            case IDLE:
            {
                DrawRectangle(
                    x_current,
                    available_height - bar_height,
                    bar_width,
                    bar_height,
                    WHITE
                );
            } break;

            case COMPARED:
            {
                DrawRectangle(
                    x_current,
                    available_height - bar_height,
                    bar_width,
                    bar_height,
                    YELLOW
                );
            } break;

            case MOVED:
            {
                DrawRectangle(
                    x_current,
                    available_height - bar_height,
                    bar_width,
                    bar_height,
                    RED
                );
            } break;

            case SETTLED:
            {
                DrawRectangle(
                    x_current,
                    available_height - bar_height,
                    bar_width,
                    bar_height,
                    GREEN
                );
            } break;
        }
        // reset bar to idle state
        bars[i].state = IDLE;

    }
}
