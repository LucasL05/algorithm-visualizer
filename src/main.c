#include <raylib.h>
#include <stdlib.h>
#include <time.h>

#include "config.h"
#include "bars.h"
#include "sorting.h"

int main()
{
    //initialization
    const int screen_width = 900;
    const int screen_height = 600;
    const int count = 99;

    srand(time(NULL));
    int *numbers = init_numbers(count);

    InitWindow(screen_width, screen_height, "Sorting Visualizer");

    Screen current_screen = MAIN_MENU;

    // TODO: Initialize all required variables and load all required data here!
    int frames_counter = 0;

    //SetTargetFPS(60);

    // Main loop
    while (!WindowShouldClose()) // Detect Window close button or esc key
    {
        switch (current_screen)
        {
            case MAIN_MENU:
            {
                // TODO: Update MAIN_MENU screen variables here!
                //frames_counter++; -> not really necessary to count frames, I guess.

                //press enter to change to MERGE_SORT screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    current_screen = MERGE_SORT;
                }
            } break;
            case MERGE_SORT:
            {
            } break;
        }

        // Draw
        BeginDrawing();
        ClearBackground(BLACK);

        switch(current_screen)
        {
            case MAIN_MENU:
            {
                // TODO: Draw a better menu screen here
                DrawRectangle(0, 0, screen_width, screen_height, BLACK);
                DrawText("Main Menu", screen_width/2.5, 20, 40, RAYWHITE);
                DrawText("Press ENTER or TAP to jump to simulation screen", screen_width/4, 220, 20, RAYWHITE);
            } break;
            case MERGE_SORT:
            {
                draw_bars(screen_width, screen_height, numbers);
            } break;
        }

        EndDrawing();
    }

    CloseWindow();
    free(numbers);
}
