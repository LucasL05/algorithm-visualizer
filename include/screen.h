#ifndef SCREEN_H
#define SCREEN_H

#include <raylib.h>
#include <stdlib.h>
#include "config.h"

Screen update_screen(Button **buttons, size_t b_length, Screen current_screen);
void draw_button(Button *b);
void update_button_state(Button *b);

#endif // SCREEN_H