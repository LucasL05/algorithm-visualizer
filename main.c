#include <raylib.h>
#include <stdio.h>

#define WIDTH 900
#define HEIGHT 600

#define COUNT 100
int numbers[COUNT];

void draw_bars() 
{
    int gap = 2; // Fixed gap in pixels

    for (int i = 0; i < COUNT; i++) 
    {
        // STUDY THIS CODE! Using AI is olay sometimes
        int value = numbers[i];
        int bar_height = HEIGHT * 0.75 * value / COUNT;

        // Calculate exact pixel boundaries for current and next bar
        int x_current = (i * WIDTH) / COUNT;
        int x_next    = ((i + 1) * WIDTH) / COUNT;

        // Bar width fills the space between current and next boundary minus the gap
        int bar_width = (x_next - x_current) - gap;

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