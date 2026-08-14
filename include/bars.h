#ifndef BARS_H
#define BARS_H

int find_margin(int screen_width);
void fisher_yates_shuffle(int *numbers, int count);
int *init_numbers(int count);
void draw_bars(int screen_width, int screen_height, int *numbers, int count);

#endif // BARS_H
