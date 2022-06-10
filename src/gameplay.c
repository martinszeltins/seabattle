#include <stdbool.h>
#include "include/game.h"
#include "include/gameplay.h"

void gameplay_start(struct game * game)
{
    gameplay_add_player_ships(game);
}

void gameplay_add_player_ships(struct game * game)
{
    int ship_sizes[] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};

    for (int i = 0; i < 10; i++) {
        game->player_ships[i].rect.x      = game->player_grid_offset_x;
        game->player_ships[i].rect.y      = game->grid_offset_y;
        game->player_ships[i].rect.w      = 1 * game->cell_size;
        game->player_ships[i].rect.h      = ship_sizes[i] * game->cell_size;
        game->player_ships[i].is_placed   = false;
        game->player_ships[i].orientation = VERTICAL;
    }
}