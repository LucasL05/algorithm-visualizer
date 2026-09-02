#include <raylib.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <pthread.h>

#include "config.h"
#include "main_menu.h"
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

    // Initialize main menu's buttons

    ButtonColors colors = {
        .normal = LIGHTGRAY,
        .hovered = GRAY,
        .pressed = DARKGRAY
    };

    Rectangle btn1_bounds = {screen_width / 2.9, screen_height / 2.5, 300, 80};
    Button btn1 = {
        .bounds = btn1_bounds,
        .state = BTN_NORMAL,
        .text = "Merge Sort",
        .colors = colors
    };

    Rectangle btn2_bounds = {screen_width / 2.9, screen_height / 1.5, 300, 80};
    Button btn2 = {
        .bounds = btn2_bounds,
        .state = BTN_NORMAL,
        .text = "Quick sort",
        .colors = colors
    };

    InitWindow(screen_width, screen_height, "Sorting Visualizer");

    Screen current_screen = START;

    // TODO: Initialize all required variables and load all required data here!
    // int frames_counter = 0;

    SetTargetFPS(60);

    // Main loop
    bool sorting = false;
    while (!WindowShouldClose()) // Detect Window close button or esc key
    {
        if (!sorting) {
            switch (current_screen)
            {
                case START:
                {
                    //frames_counter++; -> not really necessary to count frames, I guess.

                    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                    {
                        current_screen = MAIN_MENU;
                    }
                } break;

                case MAIN_MENU:
                {
                    current_screen = update_main_menu(&btn1, &btn2);
                } break;

                case MERGE_SORT:
                {
                    pthread_create(&r_sort, NULL, merge_sort, &num_data);
                    sorting = true;
                } break;

                case QUICK_SORT:
                {

                } break;
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(BLACK);

        switch(current_screen)
        {
            case START:
            {
                // TODO: Draw a better menu screen here
                DrawText("Welcome!", screen_width/3, 20, 80, RAYWHITE);
                DrawText("Press ENTER or TAP to enter the main menu", screen_width/4, 220, 20, RAYWHITE);
            } break;

            case MAIN_MENU:
            {
                draw_main_menu(screen_width, screen_height, btn1, btn2);
            } break;
            
            case MERGE_SORT:
            {
                draw_bars(screen_width, screen_height, numbers, count, usable_width, margin);
            } break;

            case QUICK_SORT:
            {

            } break;
        }

        EndDrawing();
    }

    pthread_mutex_destroy(&lock); // Should I be doing this before?
    CloseWindow();
    free(numbers);
}
