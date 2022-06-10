#include <math.h>
#include <stdbool.h>
#include "include/game.h"
#include "include/util.h"
#include "include/gameplay.h"

void gameplay_start(struct game * game)
{
    gameplay_add_player_ships(game);
    gameplay_add_opponent_ships(game);
    gameplay_reset_player_aim(game);
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

void gameplay_add_opponent_ships(struct game * game)
{
    int ship_sizes[] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};

    // This needs to be initialized otherwise getting some garbage value.
    for (int i = 0; i < 10; i++) {
        game->opponent_ships[i].is_placed = false;
    }

    for (int i = 0; i < 10; i++) {
        bool ship_can_be_placed = false;
        int tries = 0;

        orientation new_ship_orientation;

        int new_ship_x;
        int new_ship_y;
        int new_ship_w;
        int new_ship_h;

        while (ship_can_be_placed == false || tries > 1000) {
            bool rnd_orientation = rand() & 1;

            if (rnd_orientation == 1) {
                new_ship_orientation = HORIZONTAL;
            } else {
                new_ship_orientation = VERTICAL;
            }

            new_ship_x = util_rnd_number(game->opponent_grid_offset_x, game->opponent_grid_offset_x + (10 * game->cell_size));
            new_ship_x = (new_ship_x / game->cell_size) * game->cell_size;
            new_ship_x = new_ship_x + 30;

            new_ship_y = util_rnd_number(game->grid_offset_y, game->grid_offset_y + (10 * game->cell_size));
            new_ship_y = (new_ship_y / game->cell_size) * game->cell_size;
            new_ship_y = new_ship_y + 40;

            if (new_ship_orientation == HORIZONTAL) {
                new_ship_w = ship_sizes[i] * game->cell_size;
                new_ship_h = game->cell_size;
            } else {
                new_ship_w = game->cell_size;
                new_ship_h = ship_sizes[i] * game->cell_size;
            }

            /**
             * Check if the new ship is out of bounds and if it is
             * then generate a new random ship.
             */
            int new_ship_x_end = new_ship_x + new_ship_w;
            int new_ship_y_end = new_ship_y + new_ship_h;

            if (new_ship_x_end > game->opponent_grid_offset_x + (10 * game->cell_size) || new_ship_y_end > game->grid_offset_y + (10 * game->cell_size)) {
                tries++;
                continue;
            }

            /**
             * Loop through all placed ships and determine if the new
             * ship overlaps the placed ship's boundary.
             */
            ship_can_be_placed = true;

            for (int j = 0; j < 10; j++) {
                if (game->opponent_ships[j].is_placed == true) {
                    int outer_boundary_x_start = game->opponent_ships[j].rect.x - game->cell_size;
                    int outer_boundary_x_end = game->opponent_ships[j].rect.x + game->opponent_ships[j].rect.w + game->cell_size;

                    int outer_boundary_y_start = game->opponent_ships[j].rect.y - game->cell_size;
                    int outer_boundary_y_end = game->opponent_ships[j].rect.y + game->opponent_ships[j].rect.h + game->cell_size;

                    bool ships_overlap = util_rectangles_overlap(
                        new_ship_x, new_ship_x_end, new_ship_y, new_ship_y_end,
                        outer_boundary_x_start, outer_boundary_x_end, outer_boundary_y_start, outer_boundary_y_end
                    );

                    if (ships_overlap) {
                        ship_can_be_placed = false;
                        break;
                    }
                }
            }

            if (ship_can_be_placed == false) {
                tries++;
            }

            if (tries > 1000) {
                printf("Error: tries > 1000! \n");
                exit(1);
            }
        }

        game->opponent_ships[i].rect.x      = new_ship_x;
        game->opponent_ships[i].rect.y      = new_ship_y;
        game->opponent_ships[i].rect.w      = new_ship_w;
        game->opponent_ships[i].rect.h      = new_ship_h;
        game->opponent_ships[i].is_placed   = true;
        game->opponent_ships[i].orientation = new_ship_orientation;
    }
}

void gameplay_reset_player_aim(struct game * game)
{
    game->player_aim.x = game->opponent_grid_offset_x;
    game->player_aim.y = game->grid_offset_y;
    game->player_aim.w = game->cell_size;
    game->player_aim.h = game->cell_size;
}

void gameplay_place_ship(struct game * game) 
{
    bool ships_overlap = false;

    // Check if the new ship overlaps another
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
                return;
            }
        }
    }

    game->player_ships[game->placing_ship_index].is_placed = true;

    if (game->placed_ships < 9) {
        game->placed_ships++;
        game->placing_ship_index++;
    } else {
        game->is_shooting = true;
    }
}