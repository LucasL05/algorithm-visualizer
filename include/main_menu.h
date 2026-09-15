#include <raylib.h>
#include <stdlib.h>
#include "config.h"

#ifndef MAIN_MENU_H
#define MAIN_MENU_H

typedef enum {
    BTN_IDLE,
    BTN_HOVER,
    BTN_PRESSED,
    BTN_ACTION
} ButtonState;

typedef struct {
    Color idle;
    Color hovered;
    Color pressed;
} ButtonColors;

typedef struct {
    Rectangle bounds;
    ButtonState state;
    ButtonColors colors;
    const char *text;
    Screen target_screen;
} Button;

Screen update_main_menu(Button **buttons, size_t b_length);
void draw_main_menu(int s_width, int s_height, Button **buttons, size_t b_length);

#endif // MAIN_MENU_H