#include <raylib.h>
#include "config.h"
#include "main_menu.h"

Screen update_main_menu(Button *btn1, Button *btn2) {
    // bool btn_action = false; // is this really necessary
    
    // ---- division ----- 
    Vector2 mouse_point = GetMousePosition();
    // btn_action = false; // again?

    // Check if mouse is hovering over the button
    // **** There's surely a better way to do this
    if (CheckCollisionPointRec(mouse_point, btn1->bounds)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) 
        {
            btn1->state = BTN_PRESSED;
        } 
        else 
        {
            btn1->state = BTN_HOVER;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            // btn_action = true;
            return MERGE_SORT;
        }
    }
    else 
    {
        btn1->state = BTN_NORMAL;


        if (CheckCollisionPointRec(mouse_point, btn2->bounds)) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) 
            {
                btn2->state = BTN_PRESSED;
            } 
            else 
            {
                btn2->state = BTN_HOVER;
            }

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                // btn_action = true;
                return QUICK_SORT;
            }
        }

        else{
            btn2->state = BTN_NORMAL;
        }
    }

    return MAIN_MENU;
}

void draw_button(Button b) {
    if (b.state == BTN_HOVER) 
    {
        DrawRectangleRec(b.bounds, b.colors.hovered);
    }

    else {
        if (b.state == BTN_PRESSED) 
        {
            DrawRectangleRec(b.bounds, b.colors.pressed);
        }
        else 
        {
            DrawRectangleRec(b.bounds, b.colors.normal);
        }
    }

    DrawRectangleLinesEx(b.bounds, 2, BLACK);

    int font_size = 20;
    int text_width = MeasureText(b.text, font_size);
    DrawText(b.text, 
            b.bounds.x + (b.bounds.width - text_width) / 2, 
            b.bounds.y + (b.bounds.height - font_size) / 2, 
            font_size, BLACK);

}

void draw_main_menu(int screen_width, int screen_height, Button btn1, Button btn2) {
    DrawText("Main Menu", screen_width/3.5, screen_height/7, 80, RAYWHITE);
    draw_button(btn1);
    draw_button(btn2);

//    if (btnAction) {
//                DrawText("Action Triggered!", 10, 10, 20, MAROON);
//            } 
}



