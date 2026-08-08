#include <raylib.h>
#include <stdio.h>


#define WIDTH 900
#define HEIGHT 600
#define GAP 2
// #define MARGIN 16

#define COUNT 99
// #if (COUNT * (1 + GAP)) > USABLE_WIDTH
//    #error "FATAL ERROR: Too many bars for this window width."
// #endif

int find_margin()
{
    for (int divisor = COUNT; divisor >= 1; divisor --)
    {
        if (WIDTH % divisor == 0 && (COUNT - divisor) % 2 == 0)
        {
            return COUNT - divisor;
        }
    }
}

int numbers[COUNT];
void draw_bars() 
{   
/* margin fixed! Now the only thing left to get even rectangles is probably related to the gap. Maybe I should incorporate
it in the usable_width calculation, but I'm not sure. */
    for (int i = 0; i < COUNT; i++) 
    {
        int value = numbers[i] + 1;
        int bar_height = HEIGHT * 0.75 * value / (COUNT +1); // + 1 cause the value of numbers[i] = i + 1, since otherwise the first bar whould have height zero.

        // Calculate margin and usable width
        int margin = find_margin();
        int usable_width = WIDTH - margin;
        // *****put usable_width test here****

        // Calculate exact pixel boundaries for current and next bar
        int x_current = ((i * usable_width) / COUNT) + margin/2;
        int x_next    = (((i + 1) * usable_width) / COUNT) + margin/2;

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