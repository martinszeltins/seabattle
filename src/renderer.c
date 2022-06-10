#include <SDL2/SDL.h>
#include "include/game.h"
#include "include/renderer.h"

void renderer_draw(struct game * game)
{
    renderer_clear_screen(game->renderer);
    renderer_draw_title(game);
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