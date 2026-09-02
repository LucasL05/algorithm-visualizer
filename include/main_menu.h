#include <raylib.h>
#include "config.h"
#ifndef MAIN_MENU_H
#define MAIN_MENU_H

typedef enum {
    BTN_NORMAL,
    BTN_PRESSED,
    BTN_HOVER
} ButtonState;

typedef struct {
    Color normal;
    Color hovered;
    Color pressed;
} ButtonColors;

typedef struct {
    Rectangle bounds;
    ButtonState state;
    const char *text;
    ButtonColors colors;
} Button;

Screen update_main_menu(Button *btn1, Button *btn2);
void draw_main_menu(int screen_width, int screen_height, Button btn1, Button btn2);
#endif // MAIN_MENU_H