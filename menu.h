#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

typedef enum {
    MENU_NONE,
    MENU_START,
    MENU_HELP,
    MENU_QUIT
} MenuChoice;

bool showMenu(SDL_Renderer *renderer, MenuChoice *choice);

#endif

