#include <raylib.h>
#include "config.h"
#include "main_menu.h"

// updates *b*'s state
// according to current user input
void update_button_state(Button *b) 
{
    Vector2 mouse_point = GetMousePosition();

    // Checks if the mouse is on the button
    if (CheckCollisionPointRec(mouse_point, b->bounds)) 
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) 
        {
            b->state = BTN_PRESSED;
        } else
        {
            b->state = BTN_HOVER;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            b->state = BTN_ACTION;
        }

    } else 
    {
        b->state = BTN_IDLE;
    }
}

// updates the main menu
// according to current user input
Screen update_main_menu(Button **buttons, size_t b_length) {
    for (int i = 0; i < b_length; i++)
    {
        update_button_state(buttons[i]);
        if (buttons[i]->state == BTN_ACTION)
        {
            return buttons[i]->target_screen;
        }
    }

    return MAIN_MENU;
}

void draw_button(Button *b) {
    if (b->state == BTN_HOVER) 
    {
        DrawRectangleRec(b->bounds, b->colors.hovered);
    }

    else {
        if (b->state == BTN_PRESSED) 
        {
            DrawRectangleRec(b->bounds, b->colors.pressed);
        }
        else 
        {
            DrawRectangleRec(b->bounds, b->colors.idle);
        }
    }

    DrawRectangleLinesEx(b->bounds, 2, BLACK);

    int font_size = 20;
    int text_width = MeasureText(b->text, font_size);
    DrawText(b->text, 
            b->bounds.x + (b->bounds.width - text_width) / 2, 
            b->bounds.y + (b->bounds.height - font_size) / 2, 
            font_size, BLACK);

}

// s_width -> screen width;
// s_height -> screen height
void draw_main_menu(int s_width, int s_height, Button **buttons, size_t b_length) {
    // Draw main menu texts
    DrawText("Main Menu", s_width/3.5, s_height/7, 80, RAYWHITE);

    // Draw main menu buttons
    for (int i = 0; i < b_length; i++)
    {
        draw_button(buttons[i]);
    }
}



