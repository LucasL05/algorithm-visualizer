#include <raylib.h>
#include <stdio.h>
#include <math.h>

#define WIDTH 900
#define HEIGHT 600
#define GAP 2
// #define MARGIN 16

#define COUNT 200
// #if (COUNT * (1 + GAP)) > USABLE_WIDTH
//    #error "FATAL ERROR: Too many bars for this window width."
// #endif

int numbers[COUNT];

void draw_bars() 
{   
    /* To get a beautiful, flawless grid, every single slot must be exactly the same width (e.g., exactly 4 pixels), 
    which means we have to reverse our architecture.
    Instead of hardcoding a MARGIN of 16 and forcing the bars to stretch into the messy leftover space, 
    what if we calculate the perfect bar size first (WIDTH / COUNT), 
    and let the margin absorb the leftover pixels? 
    How would you write the math to automatically calculate a dynamic margin that centers the perfect grid on the screen?*/

    /* def margin as width % (count - margin) = 0
    maybe it'd also be nice to make margin always be even, but probably not.*/
    for (int i = 0; i < COUNT; i++) 
    {
        int value = numbers[i] + 1;
        int bar_height = HEIGHT * 0.75 * value / (COUNT +1); // + 1 cause the value of numbers[i] = i + 1, since otherwise the first bar whould have height zero.

        // Calculate exact pixel boundaries for current and next bar
        int x_current = ((i * USABLE_WIDTH) / COUNT) + MARGIN;
        int x_next    = (((i + 1) * USABLE_WIDTH) / COUNT) + MARGIN;

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
    for (int i = 0; i < COUNT; i++) {
        numbers[i] = i;
    }

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