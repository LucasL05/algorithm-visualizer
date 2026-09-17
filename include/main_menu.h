#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <raylib.h>
#include <stdlib.h>
#include "config.h"


Screen update_main_menu(Button **buttons, size_t b_length);
void draw_main_menu(int s_width, int s_height, Button **buttons, size_t b_length);

#endif // MAIN_MENU_H