#include <raylib.h>
#include <stdlib.h>

#include "config.h"
Rectangle generate_btn_bounds(size_t btn_index, size_t screen_btn_count, size_t screen, WindowDimensions w_dms)
{
    if (screen_btn_count <= 3)
    {
        Rectangle b = {
            w_dms.width / 2.9,
            w_dms.height / 3,
            300,
            80
        }; // Adapt this to btn_index and screen_btn_count
    }
}
    Rectangle btn_sm_bounds = {screen_width / 2.9, screen_height / 3, 300, 80};
// generates a standard button with the given specs
Button generate_btn(Rectangle bounds, ButtonSpec specs, Screen current_screen, ButtonColors colors)
{
    Button b = {
        .bounds = bounds,
        .state = BTN_IDLE,
        .colors = colors,
        .text = specs->text,
        .action = specs->action
    };
    return b;
}

// Reads 'count' specs and writes 'count' buttons into out_buttons.
// out_buttons must be pre-allocated with space for at least 'count' buttons.
//
// - 'count' must be <= 12;
// - If you'd like more buttons, creating a second screen is recommended.
// 
// NOTE: All buttons belonging to the same screen must be generated together.
// NOTE: buttons with text "<--" will be generated in the screen's left upper corner
void generate_btns(Button *out_buttons, ButtonSpec *specs, size_t count, Screen current_screen, WindowDimensions w_dms)
{
    // Colors for return buttons * <-- *
    ButtonColors colors_rtrn = {
        .idle = WHITE,
        .hovered = LIGHTGRAY,
        .pressed = GRAY
    };

    // main menu is the only screen that doesn't have a return button,
    // so it needs a different approach.
    if (current_screen == MAIN_MENU)
    {

    }
    for (int i = 0; i < count; i++) 
    {
        Rectangle bounds = generate
    }
}

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

void draw_button(Button *b) 
{
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

// updates the screen
// according to user input.
Screen update_screen(Button **buttons, size_t b_length, Screen current_screen) {
    for (int i = 0; i < b_length; i++)
    {
        update_button_state(buttons[i]);
        if (buttons[i]->state == BTN_ACTION)
        {
            if (buttons[i]->action.type == EXIT) 
            {
                *buttons[i]->action.data.exitRequested = true;
            }

            else 
            {
                return buttons[i]->action.data.target_screen;
            }
        }
    }

    return current_screen;
}