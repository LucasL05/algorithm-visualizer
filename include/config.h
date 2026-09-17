#ifndef CONFIG_H
#define CONFIG_H

#include <raylib.h>

#define GAP 2


typedef enum { 
    START, 
    MAIN_MENU, 
    MERGE_SORT, 
    QUICK_SORT
} Screen;

typedef enum {
    CHANGE_SCREEN,
    EXIT
} ActionType;

typedef struct {
    ActionType type;
    union {
        // Screen can be generalized as "data" if necessary
        Screen target_screen; // Valid only when ActionType == CHANGE_SCREEN
        bool *exitRequested;
    } data;
} Action;

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
    Action action;
} Button;

#endif // CONFIG_H
