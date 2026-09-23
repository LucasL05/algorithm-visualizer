#include <raylib.h>
#include <string.h>
#include "config.h"
#include "menus.h"
#include "screen.h"

// s_width -> screen width;
// s_height -> screen height
void draw_menu(WindowDimensions w_dimensions, Button *buttons, size_t b_length, char *text) 
{
    // Draw menu title
    int font_size = 80;
    int text_width = MeasureText(text, font_size);
    int width = (w_dimensions.width - text_width) / 2;
    int height = w_dimensions.height / 20;
    DrawText(text, width, height, font_size, RAYWHITE);

    // Draw main menu buttons
    for (int i = 0; i < b_length; i++)
    {
        draw_button(&buttons[i]);
    }
}



