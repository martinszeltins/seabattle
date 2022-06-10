#include <SDL2/SDL.h>
#include <stdbool.h>
#include "include/game.h"
#include "include/input.h"

void input_handle(struct game * game)
{
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            game_quit(game);
            return;
        }

        // Enter
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
            if (!game->is_shooting) {
                gameplay_place_ship(game);
            }

            return;
        }

        // Spacebar
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
            if (!game->is_shooting) {
                gameplay_rotate_ship(game);
            }

            if (game->is_shooting) {
                gameplay_shoot_at_component(game);
            }

            return;
        }

        // Escape
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        {
            game_quit(game);
            return;
        }
    }
}