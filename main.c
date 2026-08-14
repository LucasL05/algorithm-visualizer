#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define GAP 2
#define COUNT 99


typedef enum Screen { MAIN_MENU = 0, MERGE_SORT} Screen;

int find_margin(int screen_width)
{
    int rest = screen_width % COUNT;
    if (rest % 2 == 0) return rest;
    if (COUNT % 2 == 1) return rest + COUNT;
    else return 0;
    /* Maybe returninig 0 here isn't really the best option, but if rest isn't even
    and COUNT is, there's really no way to make all bar's width equal by changing just the margin.
    Maybe there's a way if I change the bar's width algorithm, but that may be complicated. */
    
}

void fisher_yates_shuffle(int *numbers, int count)
{
    // Randomizes the values in the array.
    for (int i = count - 1; i >= 0; i--)
    {
        int r = rand() % (i + 1);
        int temp = numbers[i];
        numbers[i] = numbers[r];
        numbers[r] = temp;
    }
}

int *init_numbers(int count) 
{   
    int *numbers = (int*) malloc(count * sizeof(int));
    for (int i = 0; i < COUNT; i++) // "i" should probably be = 1, so that I won't need to add 1 to the height later on.
    {
        numbers[i] = i + 1;
    }

    fisher_yates_shuffle(numbers, count);

    return numbers;
}

void draw_bars(int screen_width, int screen_height, int *numbers) 
{   
/* margin fixed! Now the only thing left to get even rectangles is probably related to the gap. Maybe I should incorporate
it in the usable_width calculation, but I'm not sure. */
    // Calculate margin and usable width
    int margin = find_margin(screen_width);
    int usable_width = screen_width - margin;
    assert(COUNT * (1 + GAP) < usable_width && "ERROR: Too many bars for this window width."); // beware that assert is a no-op when NDEBUG is defined.
        

    for (int i = 0; i < COUNT; i++) 
    {
        int value = numbers[i]; // there was a +1 here
        int bar_height = screen_height * 0.65 * value / COUNT;

        // Calculate exact pixel boundaries for current and next bar
        int x_current = (i * usable_width / COUNT) + margin/2;
        int x_next    = ((i + 1) * usable_width / COUNT) + margin/2;

        // Bar width fills the space between current and next boundary minus the gap
        int bar_width = (x_next - x_current) - GAP;

        // Prevent negative widths if COUNT is extremely large
        if (bar_width < 1) bar_width = 1;

        DrawRectangle(
            x_current, 
            screen_height * 0.75 - bar_height, 
            bar_width, 
            bar_height, 
            WHITE
        );
    }
}

void merge_sort()
{
    
}

void quick_sort()
{

}


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
    while (!WindowShouldClose())  // Detect Window close button or esc key  
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
                
            }   break;
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