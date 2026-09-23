#include <raylib.h>
#include "config.h"
#include "menus.h"
#include "screen.h"

// s_width -> screen width;
// s_height -> screen height
void draw_menu(int s_width, int s_height, Button **buttons, size_t b_length, char text[]) 
{
    // Draw main menu texts
    DrawText(text, s_width/3.5, s_height/20, 80, RAYWHITE);

    // Draw main menu buttons
    for (int i = 0; i < b_length; i++)
    {
        draw_button(buttons[i]);
    }
}



