#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <raylib.h>
#include <stdlib.h>
#include "config.h"


Screen update_main_menu(Button **buttons, size_t b_length);
void draw_menu(int s_width, int s_height, Button **buttons, size_t b_length, char text[]);

#endif // MAIN_MENU_H