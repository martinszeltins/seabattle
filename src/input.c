#include <SDL.h>
#include <stdbool.h>
#include "include/game.h"
#include "include/input.h"

void input_handle(struct game * game)
{
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            game_quit(game);
        }
    }
}