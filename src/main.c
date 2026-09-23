#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <pthread.h>
#include <stdatomic.h>
// I can definetly keep *numbers* for now, but I think arr would be a much better name
#include "config.h"
#include "menus.h"
#include "bars.h"
#include "sorting.h"
#include "screen.h"


int main()
{
    //initialization
    // Initialize all required variables and load all required data here!
    const int screen_width = 900;
    const int screen_height = 600;
    WindowDimensions w_dimensions = {screen_height, screen_width};
    const int count = 100;
    bool exitWindowRequested = false;
    bool exitWindow = false;


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
    pthread_mutex_init(&lock, NULL);
    atomic_bool stop_requested;
    atomic_init(&stop_requested, false);

    // Organize data to be sent to sorters.
    SorterData sorter_data = {
        .bars = bars, 
        .length = count,
        .lock = &lock,
        .stop_requested = &stop_requested
    };

    // Initialize buttons
    Button btns_main_menu[2];
    ButtonSpec specs_main_menu[2];
    specs_main_menu[0] = (ButtonSpec) 
    {
        .btn_action = 
        {
            .type = CHANGE_SCREEN,
            .data.target_screen = SORTING_MENU
        }, 
        .btn_text = "Sorting Menu"
    };
    specs_main_menu[1] = (ButtonSpec) 
    {
        .btn_action =
        {
            .type = EXIT,
            .data.exitRequested = &exitWindowRequested
        },
        .btn_text = "Leave Program"
    };
    generate_btns(btns_main_menu, specs_main_menu, 2, true, w_dimensions);

    Button btns_sorting_menu[3];
    ButtonSpec specs_sorting_menu[3];
    specs_sorting_menu[0] = (ButtonSpec)
    {
        .btn_action =
        {
            .type = CHANGE_SCREEN,
            .data.target_screen = MAIN_MENU
        },
        .btn_text = "<--"
    };
    specs_sorting_menu[1] = (ButtonSpec)
    {
        .btn_action =
        {
            .type = CHANGE_SCREEN,
            .data.target_screen = MERGE_SORT
        },
        .btn_text = "Merge Sort"
    };
    specs_sorting_menu[2] = (ButtonSpec)
    {
        .btn_action =
        {
            .type = CHANGE_SCREEN,
            .data.target_screen = QUICK_SORT
        },
        .btn_text = "Quick Sort"
    };
    generate_btns(btns_sorting_menu, specs_sorting_menu, 3, false, w_dimensions);

    Button btns_sorting_screens[1];
    ButtonSpec specs_sorting_screens[1];
    specs_sorting_screens[0] = (ButtonSpec) 
    {
        .btn_action =
        {
            .type = CHANGE_SCREEN,
            .data.target_screen = SORTING_MENU
        },
        .btn_text = "<--"
    };
    generate_btns(btns_sorting_screens, specs_sorting_screens, 1, false, w_dimensions);

    
    

    InitWindow(screen_width, screen_height, "Alogrithm Visualizer");
    Screen current_screen = START;

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
                current_screen = update_screen(btns_main_menu, 2, MAIN_MENU);
            } break;

            case SORTING_MENU:
            {
                current_screen = update_screen(btns_sorting_menu, 3, SORTING_MENU);
            } break;

            case MERGE_SORT:
            {
                if (!sorting)
                {
                    pthread_create(&r_sort, NULL, merge_sort, &sorter_data);
                    sorting = true;
                } 

                current_screen = update_screen(btns_sorting_screens, 1, MERGE_SORT);

                if (current_screen != MERGE_SORT) 
                { 
                    stop_sorting(r_sort, &stop_requested, bars, count);
                    sorting = false;
                }
                
            } break;

            case QUICK_SORT:
            {
                if (!sorting) 
                {
                    pthread_create(&r_sort, NULL, quick_sort_r, &sorter_data);
                    sorting = true;
                }
                
                current_screen = update_screen(btns_sorting_screens, 1, QUICK_SORT);

                if (current_screen != QUICK_SORT) 
                {
                    stop_sorting(r_sort, &stop_requested, bars, count);
                    sorting = false;
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
                draw_menu(w_dimensions, btns_main_menu, 2, "Main Menu");
            } break;

            case SORTING_MENU:
            {
                draw_menu(w_dimensions, btns_sorting_menu, 3, "SORTING MENU");
            } break;
            
            case MERGE_SORT:
            {   // Merge sort == quick sort. Maybe I should merge both in the future? Like draw_sorting.
                draw_sc(w_dimensions, bars, count, usable_width, margin, btns_sorting_screens, 1);
            } break;

            case QUICK_SORT:
            {
                draw_sc(w_dimensions, bars, count, usable_width, margin, btns_sorting_screens, 1);
            } break;
        }

        EndDrawing();
        if (WindowShouldClose() || exitWindowRequested) exitWindow = true;
    }

    pthread_mutex_destroy(&lock); // Should I be doing this before?
    free(bars);
    CloseWindow();
}
