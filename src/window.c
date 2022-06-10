#include <SDL.h>
#include "include/game.h"
#include "include/window.h"

SDL_Window * window_create()
{
    return SDL_CreateWindow("Seabattle",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_FULLSCREEN
    );
}