#include <stdbool.h>
#include <SDL2/SDL.h>
#include "include/util.h"
#include "include/game.h"
#include "include/renderer.h"

void renderer_draw(struct game * game)
{
    renderer_clear_screen(game->renderer);
    renderer_draw_title(game);
    renderer_draw_placed_ships(game);
    renderer_draw_placing_ship(game);
    renderer_draw_player_aim(game);
    renderer_draw_player_shots(game);
    renderer_draw_opponent_shots(game);
    renderer_draw_grid_lines(game);

    SDL_RenderPresent(game->renderer);
    SDL_Delay(1000 / 25);
}

void renderer_clear_screen(SDL_Renderer * renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
}

void renderer_draw_title(struct game * game)
{
    SDL_RenderCopy(game->renderer, game->title.texture, NULL, &game->title.rect);
}

void renderer_draw_grid_lines(struct game * game)
{
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);

    // Horizontal
    for (int y = game->grid_offset_y; y < 1 + game->grid_height * game->cell_size + game->grid_offset_y; y += game->cell_size) {
        SDL_RenderDrawLine(game->renderer, game->player_grid_offset_x, y, game->player_grid_offset_x + (10 * game->cell_size), y);
    }

    // Vertical
    for (int x = game->player_grid_offset_x; x < 1 + game->grid_width * game->cell_size + game->player_grid_offset_x; x += game->cell_size) {
        SDL_RenderDrawLine(game->renderer, x, game->grid_offset_y, x, game->grid_offset_y + (10 * game->cell_size));
    }

    // Draw the opponent grid lines
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);

    // Horizontal
    for (int y = game->grid_offset_y; y < 1 + game->grid_height * game->cell_size + game->grid_offset_y; y += game->cell_size) {
        SDL_RenderDrawLine(game->renderer, game->opponent_grid_offset_x, y, game->opponent_grid_offset_x + (10 * game->cell_size), y);
    }

    // Vertical
    for (int x = game->opponent_grid_offset_x; x < 1 + game->grid_width * game->cell_size + game->opponent_grid_offset_x; x += game->cell_size) {
        SDL_RenderDrawLine(game->renderer, x, game->grid_offset_y, x, game->grid_offset_y + (10 * game->cell_size));
    }
}

void renderer_draw_placed_ships(struct game * game)
{
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 0);

    for (int i = 0; i < 10; i++) {
        if (game->player_ships[i].is_placed) {
            SDL_RenderFillRect(game->renderer, &game->player_ships[i].rect);
        }
    }
}

void renderer_draw_placing_ship(struct game *game)
{
    if (game->is_shooting == true) return;

    bool ships_overlap = false;

    SDL_SetRenderDrawColor(game->renderer, 75, 75, 75, 0);

    for (int i = 0; i < 10; i++) {
        if (game->player_ships[i].is_placed) {
            int placing_ship_x     = game->player_ships[game->placing_ship_index].rect.x;
            int placing_ship_y     = game->player_ships[game->placing_ship_index].rect.y;
            int placing_ship_x_end = placing_ship_x + game->player_ships[game->placing_ship_index].rect.w;
            int placing_ship_y_end = placing_ship_y + game->player_ships[game->placing_ship_index].rect.h;

            int outer_boundary_x_start = game->player_ships[i].rect.x - game->cell_size;
            int outer_boundary_x_end   = game->player_ships[i].rect.x + game->player_ships[i].rect.w + game->cell_size;
            int outer_boundary_y_start = game->player_ships[i].rect.y - game->cell_size;
            int outer_boundary_y_end   = game->player_ships[i].rect.y + game->player_ships[i].rect.h + game->cell_size;

            ships_overlap = util_rectangles_overlap(
                placing_ship_x, placing_ship_x_end, placing_ship_y, placing_ship_y_end,
                outer_boundary_x_start, outer_boundary_x_end, outer_boundary_y_start, outer_boundary_y_end
            );

            if (ships_overlap) {
                SDL_SetRenderDrawColor(game->renderer, 75, 0, 0, 0);
                break;
            }
        }
    }

    SDL_RenderFillRect(game->renderer, &game->player_ships[game->placing_ship_index].rect);
}

void renderer_draw_player_aim(struct game *game)
{
    if (game->is_shooting == false) return;

    SDL_SetRenderDrawColor(game->renderer, 187, 74, 0, 0);
    SDL_RenderFillRect(game->renderer, &game->player_aim);
}

void renderer_draw_player_shots(struct game *game)
{
    for (int i = 0; i < game->player_shots_count; i++) {
        if (game->player_shots[i].is_hit) {
            SDL_SetRenderDrawColor(game->renderer, 160, 18, 18, 0);
        } else {
            SDL_SetRenderDrawColor(game->renderer, 24, 70, 206, 0);
        }

        SDL_RenderFillRect(game->renderer, &game->player_shots[i].rect);
    }
}

void renderer_draw_opponent_shots(struct game *game)
{
    for (int i = 0; i < game->opponent_shots_count; i++) {
        if (game->opponent_shots[i].is_hit) {
            SDL_SetRenderDrawColor(game->renderer, 160, 18, 18, 0);
        } else {
            SDL_SetRenderDrawColor(game->renderer, 24, 70, 206, 0);
        }

        SDL_RenderFillRect(game->renderer, &game->opponent_shots[i].rect);
    }
}