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
            } else if (game->is_shooting) {
                gameplay_shoot_at_component(game);
            }

            return;
        }

        // Escape
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
            game_quit(game);
            return;
        }

        // W and UP
        if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP)) {
            if (!game->is_shooting) {
                gameplay_player_move_ship_up(game);
            } else if (game->is_shooting) {
                gameplay_player_move_aim_up(game);
            }

            return;
        }

        // S and DOWN
        if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN)) {
            if (!game->is_shooting) {
                gameplay_player_move_ship_down(game);
            } else if (game->is_shooting) {
                gameplay_player_move_aim_down(game);
            }

            return;
        }

        // A and LEFT
        if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT)) {
            if (!game->is_shooting) {
                gameplay_player_move_ship_left(game);
            } else if (game->is_shooting) {
                gameplay_player_move_aim_left(game);
            }

            return;
        }

        // D and RIGHT
        if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)) {
            if (!game->is_shooting) {
                gameplay_player_move_ship_right(game);
            } else if (game->is_shooting) {
                gameplay_player_move_aim_right(game);
            }

            return;
        }
    }
}