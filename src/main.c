#include <raylib.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <pthread.h>

#include "config.h"
#include "bars.h"
#include "sorting.h"

int main()
{
    //initialization
    const int screen_width = 900;
    const int screen_height = 600;
    const int count = 100;

        // Calculate margin and usable width
    int margin = find_margin(screen_width, count);
    int usable_width = screen_width - margin;
    assert(count * (1 + GAP) < usable_width && "ERROR: Too many bars for this window width.");
    //assert is no good here. The program should never crash

    srand(time(NULL));
    int *numbers = init_numbers(count);
    

    //initializing a thread for recursive sorters ***Maybe I could organize this better later on.
    //not all functions use recursiveness. Or maybe I could use threads for ewverything. Should 
    //probably test out their speed. Hmmm. ACtually, it may be better to load everything
    //before the program starts, just like this
    pthread_t r_sort;
    pthread_mutex_t lock;

    //organizing data to be sent to recursive sorters.
    NumData num_data = {
        .numbers = numbers, 
        .length = count,
        .lock = lock
    };


    InitWindow(screen_width, screen_height, "Sorting Visualizer");

    Screen current_screen = MAIN_MENU;

    // TODO: Initialize all required variables and load all required data here!
    // int frames_counter = 0;

    SetTargetFPS(240);

    // Main loop
    bool drawing = false;
    while (!WindowShouldClose()) // Detect Window close button or esc key
    {
        if (!drawing) {
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
                pthread_create(&r_sort, NULL, merge_sort, &num_data);
                drawing = true;
            } break;
            }
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
            
                draw_bars(screen_width, screen_height, numbers, count, usable_width, margin);
            } break;
        }

        EndDrawing();
    }

    pthread_mutex_destroy(&lock); // Should I be doing this before?
    CloseWindow();
    free(numbers);
}
