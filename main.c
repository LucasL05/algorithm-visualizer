#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>


#define WIDTH 900
#define HEIGHT 600
#define GAP 2
// #define MARGIN 16

#define COUNT 99
int numbers[COUNT]; // *** This probably shouldn't stay as a global variable

int find_margin()
{
    int rest = WIDTH % COUNT;
    if (rest % 2 == 0) return rest;
    if (COUNT % 2 == 1) return rest + COUNT;
    else return 0;
    /* Maybe returninig 0 here isn't really the best option, but if rest isn't even
    and COUNT is, there's really no way to make all bar's width equal by changing just the margin.
    Maybe there's a way if I change the bar's width algorithm, but that may be complicated. */
    
}

void fisher_yates_shuffle()
{
    // Randomizes the values in the array.
    for (int i = COUNT - 1; i >= 0; i--)
    {
        int r = rand() % (i + 1);
        int temp = numbers[i];
        numbers[i] = numbers[r];
        numbers[r] = temp;
    }
}

void init_numbers() 
{
    for (int i = 0; i < COUNT; i++) // "i" should probably be = 1, so that I won't need to add 1 to the hight later on.
    {
        numbers[i] = i;
    }

    fisher_yates_shuffle();
}

void draw_bars() 
{   
/* margin fixed! Now the only thing left to get even rectangles is probably related to the gap. Maybe I should incorporate
it in the usable_width calculation, but I'm not sure. */
    // Calculate margin and usable width
    int margin = find_margin();
    int usable_width = WIDTH - margin;
    assert(COUNT * (1 + GAP) < usable_width && "ERROR: Too many bars for this window width."); // beware that assert is a no-op when NDEBUG is defined.
        

    for (int i = 0; i < COUNT; i++) 
    {
        int value = numbers[i] + 1;
        int bar_height = HEIGHT * 0.75 * value / (COUNT +1); // + 1 cause the value of numbers[i] = i + 1, since otherwise the first bar whould have height zero.

        // Calculate exact pixel boundaries for current and next bar
        int x_current = (i * usable_width / COUNT) + margin/2;
        int x_next    = ((i + 1) * usable_width / COUNT) + margin/2;

        // Bar width fills the space between current and next boundary minus the gap
        int bar_width = (x_next - x_current) - GAP;

        // Prevent negative widths if COUNT is extremely large
        if (bar_width < 1) bar_width = 1;

        DrawRectangle(
            x_current, 
            HEIGHT * 0.75 - bar_height, 
            bar_width, 
            bar_height, 
            WHITE
        );
    }
}
int main() 
{
    srand(time(NULL));
    init_numbers();

    InitWindow(WIDTH, HEIGHT, "Sorting Visualizer");
    SetTargetFPS(60);

    while (!WindowShouldClose())    
    {
        BeginDrawing();
            ClearBackground(BLACK);
            draw_bars();
        EndDrawing();
    }

    CloseWindow();
}