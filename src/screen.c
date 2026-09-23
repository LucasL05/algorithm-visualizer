#include <raylib.h>
#include <stdlib.h>

#include "config.h"

Rectangle generate_return_button_bounds(WindowDimensions w_dimensions)
{
    Rectangle b = {w_dimensions.width / 80, w_dimensions.height / 60, 50, 25};
    return b;
}

// generates a return button with the given specs
Button generate_ret_button(ButtonSpec specs, WindowDimensions w_dimensions)
{

    ButtonColors colors_ret = {
        .idle = WHITE,
        .hovered = LIGHTGRAY,
        .pressed = GRAY
    };

    Rectangle bounds_ret = generate_return_button_bounds(w_dimensions);
    Button ret = {
        .bounds = bounds_ret,
        .state = BTN_IDLE,
        .colors = colors_ret,
        .text = specs.btn_text,
        .action = specs.btn_action
    };
    return ret;
}

Rectangle generate_std_btn_bounds(size_t btn_index, size_t screen_btn_count, WindowDimensions w_dimensions)
{
    Rectangle bounds;
    // The other 5% are occupied by the title. 
    // The only button there will be "<--", that is defined at generate_return_button()
    double usable_height = w_dimensions.height * 0.95;
    double btn_height = btn_index * (usable_height / 3);

    // Position buttons in a single, centralized column.
    if (screen_btn_count <= 3)
    {
        double btn_width = w_dimensions.width / 2.9;

        bounds = (Rectangle) {
            btn_width,
            btn_height,
            300,
            80
        };
    } 

    // Position buttons in a 3x4 grid

    //            Title
    // btn1    btn2    btn3    btn4
    // btn5    btn6    btn7    btn8
    // btn9    btn10   btn11   btrn12
    //
    else {
        double gap_width = w_dimensions.width/15;
        double btn_width = btn_index * w_dimensions.width / 6 + gap_width; 

        bounds = (Rectangle) {
            btn_width,
            btn_height,
            200,
            80
        };
    }
    return bounds;
}
    
// generates a standard button with the given specs.
// - max 'screen_btn_count' == 12.
Button generate_std_btn(ButtonSpec specs, size_t btn_index, size_t screen_btn_count, WindowDimensions w_dimensions)
{
    Rectangle bounds = generate_std_btn_bounds(btn_index, screen_btn_count, w_dimensions);
    ButtonColors colors_std = {
        .idle = LIGHTGRAY,
        .hovered = GRAY,
        .pressed = DARKGRAY
    };

    Button b = {
        .bounds = bounds,
        .state = BTN_IDLE,
        .colors = colors_std,
        .text = specs.btn_text,
        .action = specs.btn_action
    };
    return b;
}

// Reads 'count' specs and writes 'count' buttons into out_buttons.
// out_buttons must be pre-allocated with space for at least 'count' buttons.
//
// - 'count' must be <= 13 if there is a return button;
// - 'count' must be <= 12 if there is no return button;
// - If you'd like more buttons, creating a second screen is recommended;
// - No screen can have more than one return button;
//
// - Buttons will be inserted in 'out_buttons' in the same order of
// their provided specs in 'specs'.
//
// NOTE: All buttons belonging to the same screen must be generated together.
// NOTE: Return buttons "<--" will be generated in the screen's left upper corner.
// NOTE: If there is a return button "<--", its specs must be at specs[0],
// if there is not, a standard button must occupy that index.
// NOTE: All Screens except MAIN_MENU need to have a return button.
void generate_btns(Button *out_buttons, ButtonSpec *specs, size_t count, bool is_main_menu, WindowDimensions w_dimensions)
{
    // MAIN_MENU is the only screen that doesn't have a return button
    // so it gets a different approach.
    if (is_main_menu)
    {
        for (int i = 0; i < count; i++)
        {
            out_buttons[i] = generate_std_btn(specs[i], i, count, w_dimensions);
        }
    } 
    else {
        out_buttons[0] = generate_ret_button(specs[0], w_dimensions);
        // i = 1 because index 0 is already defined as the return button
        for (int i = 1; i < count; i++) 
        {
            out_buttons[i] = generate_std_btn(specs[i], i, count, w_dimensions);
        }
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