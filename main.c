#include <raylib.h>
#include <stdio.h>

#define WIDTH 900
#define HIGHT 600

#define COUNT 10
int numbers[COUNT];

void draw_bars() {

}



int main() 
{
    for (int i = 0; i < COUNT; i++) 
    {
        numbers[i] = i;
        printf("number[%d] = %d\n", numbers[i]);
    }

    InitWindow(WIDTH, HIGHT, "Sorting Visualizer");

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        DrawRectangle(50, 50, 30, 100, WHITE);
        EndDrawing();
    }

    CloseWindow();
}