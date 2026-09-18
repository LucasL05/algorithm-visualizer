#include <raylib.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <pthread.h>
// I can definetly keep *numbers* for now, but I think arr would be a much better name
#include "config.h"
#include "main_menu.h"
#include "bars.h"
#include "sorting.h"
#include "screen.h"


int main()
{
    //initialization
    // Initialize all required variables and load all required data here!
    const int screen_width = 900;
    const int screen_height = 600;
    const int count = 100;

        // Calculate margin and usable width
    int margin = find_margin(screen_width, count);
    int usable_width = screen_width - margin;
    assert(count * (1 + GAP) < usable_width && "ERROR: Too many bars for this window width.");
    //assert is no good here. The program should never crash

    srand(time(NULL));
    Bar *bars = init_bars(count);
    

    //initializing a thread for recursive sorters ***Maybe I could organize this better later on.
    //not all functions use recursiveness. Or maybe I could use threads for everything. Should 
    //probably test out their speed. Hmmm. ACtually, it may be better to load everything
    //before the program starts, just like this
    pthread_t r_sort;
    pthread_mutex_t lock;

    //organizing data to be sent to recursive sorters.
    BarsData bars_data = {
        .bars = bars, 
        .length = count,
        .lock = &lock
    };

    ButtonColors colors = {
        .idle = LIGHTGRAY,
        .hovered = GRAY,
        .pressed = DARKGRAY
    };

    // Colors for the return buttons * <-- *
    ButtonColors ret_btn_colors = {
        .idle = WHITE,
        .hovered = LIGHTGRAY,
        .pressed = GRAY
    };

    // Use to return to main menu screen
    Rectangle btn_mm_bounds = {screen_width / 80, screen_height / 60, 50, 25};
    Button btn_mm = {
        .bounds = btn_mm_bounds,
        .state = BTN_IDLE,
        .colors = ret_btn_colors,
        .text = "<--",
        .action = {
            .type = CHANGE_SCREEN,
            .data.target_screen = MAIN_MENU
        }
    };

    // Initialize main menu's buttons
    // Having a "initialize_main_menu()" umbrella function
    // would make things much tidier, but then I'd need to
    // use more heap memory, I think
    bool exitWindowRequested = false;
    Rectangle btn_ext_bounds = {screen_width / 2.9, screen_height / 1.4, 300, 80};
    Button btn_ext= {
        .bounds = btn_ext_bounds,
        .state = BTN_IDLE,
        .colors = colors,
        .text = "Exit program",
        .action = {
            .type = EXIT,
            .data.exitRequested = &exitWindowRequested
        }
    };

    Rectangle btn_ms_bounds = {screen_width / 2.9, screen_height / 3, 300, 80};
    Button btn_ms = {
        .bounds = btn_ms_bounds,
        .state = BTN_IDLE,
        .colors = colors,
        .text = "Merge Sort",
        .action = {
            .type = CHANGE_SCREEN,
            .data.target_screen = MERGE_SORT
        }
    };
    // I should probably change these button's names later on 
    Rectangle btn_qs_bounds = {screen_width / 2.9, screen_height / 1.92, 300, 80};
    Button btn_qs = {
        .bounds = btn_qs_bounds,
        .state = BTN_IDLE,
        .colors = colors,
        .text = "Quick sort",
        .action = {
            .type = CHANGE_SCREEN,
            .data.target_screen = QUICK_SORT
        }
    };

    // Packing main menu buttons
    Button *buttons_mm[3]; 
    buttons_mm[0] = &btn_ext;
    buttons_mm[1] = &btn_ms;
    buttons_mm[2] = &btn_qs;
  
    // Packing sorting screen buttons
    Button *buttons_sc[1];
    buttons_sc[0] = &btn_mm;

    InitWindow(screen_width, screen_height, "Alogrithm Visualizer");
    Screen current_screen = START;
    bool exitWindow = false;

    // Main loop
    SetTargetFPS(60);
    bool sorting = false;
    while (!exitWindow) // WindowShouldClose(Detect Window close button or esc key)
    {
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
                current_screen = update_screen(buttons_mm, 3, MAIN_MENU);
            } break;

            case MERGE_SORT:
            {
                current_screen = update_screen(buttons_sc, 1, MERGE_SORT);

                if (!sorting)
                {
                    pthread_mutex_init(&lock, NULL);
                    pthread_create(&r_sort, NULL, merge_sort, &bars_data);
                    sorting = true;
                } // FIND A WAY TO STOP THE SORTING IF THE SCREEN CHANGES
                
            } break;

            case QUICK_SORT:
            {
                current_screen = update_screen(buttons_sc, 1, QUICK_SORT);

                if (!sorting) 
                {
                    pthread_mutex_init(&lock, NULL);
                    pthread_create(&r_sort, NULL, quick_sort_r, &bars_data);
                    sorting = true;
                }
                
            } break;
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
            {    // Maybe a union struct buttons and length would be better?
                draw_main_menu(screen_width, screen_height, buttons_mm, 3);
            } break;
            
            case MERGE_SORT:
            {   // Merge sort == quick sort. Maybe I should merge both in the future? Like draw_sorting.
                draw_sc(screen_width, screen_height, bars, count, usable_width, margin, buttons_sc, 1);
            } break;

            case QUICK_SORT:
            {
                draw_sc(screen_width, screen_height, bars, count, usable_width, margin, buttons_sc, 1);
            } break;
        }

        EndDrawing();
        if (WindowShouldClose() || exitWindowRequested) exitWindow = true;
    }

    pthread_mutex_destroy(&lock); // Should I be doing this before?
    free(bars);
    CloseWindow();
}
