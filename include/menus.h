#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <raylib.h>
#include <stdlib.h>
#include "config.h"

void draw_menu(WindowDimensions w_dimensions, Button *buttons, size_t b_length, char *text);

#endif // MAIN_MENU_H