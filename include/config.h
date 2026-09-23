#ifndef CONFIG_H
#define CONFIG_H

#include <raylib.h>
#include <stddef.h>

#define GAP 2

// **Warning** 
// This enum is sometimes compared by value.
// Ensure any modifications preserve this ordering pattern.
//
// Screens should be defined in the order that they are accessed. 
// e.g. main_menu -> sorting_menu -> merge_sort
//
// If a menu provides access to multiple screens, their relative
// order doesn't matter as long as they appear after that menu.
// For example, both of the following are valid
// (unless a specific screen must be accessed first):
//
// - sorting_menu -> quick_sort -> merge_sort
// - sorting_menu -> merge_sort -> quick_sort
// 
// If a screen provides access to multiple others,
// which in turn provide access to multiple others,
// all screens referenced by that first screen must come before
// any screen referenced by the ones that follow it.

// For example:
// main_menu -> sorting_menu and settings_menu,
// sorting_menu -> merge_sort, settings_menu -> language.
//
// Incorrect orders:
// main_menu -> sorting_menu -> merge_sort -> settings_menu -> language
// main_menu -> settings_menu -> language -> sorting_menu -> merge_sort,
//
// Correct order:
// main_menu -> sorting_menu -> settings_menu -> merge_sort -> language
// (sorting_menu and settings_menu's relative order doesn't matter,
// just like merge_sort and language)
//
// This is actually called Breadth-First Search (BFS), appearently.
typedef enum { 
    START, 
    MAIN_MENU,
    SORTING_MENU, 
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
        Screen target_screen; // Valid only if ActionType == CHANGE_SCREEN
        bool *exitRequested;  // Valid only if ActionType == EXIT
    } data;
} Action;

// this struct is used to generate buttons
typedef struct {
    Action btn_action;
    char *btn_text;
} ButtonSpec;

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
    const char text[];
    Action action;
} Button;

typedef struct {
    size_t height;
    size_t width;
} WindowDimensions;

#endif // CONFIG_H
