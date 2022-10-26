#include <time.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "include/sdl.h"
#include <SDL2/SDL_ttf.h>
#include "include/game.h"
#include "include/input.h"
#include "include/window.h"
#include "include/renderer.h"
#include "include/gameplay.h"

struct game * game_create()
{
    struct game * game;

    game = malloc(sizeof(struct game));

    return game;
}

void game_run(struct game * game)
{
    game_init(game);
    gameplay_start(game);

    while (game->is_running) {
        input_handle(game);
        renderer_draw(game);
    }

    game_terminate(game);
}

void game_init(struct game * game)
{
    srand(time(NULL));
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    game->is_running = true;
    game->window = window_create();
    game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);
    game->title = game_get_title(game);
    game->cell_size = 60;
    game->grid_width = 10;
    game->grid_height = 10;
    game->grid_offset_y = 280;
    game->placing_ship_index = 0;
    game->player_grid_offset_x = 280;
    game->opponent_grid_offset_x = 1050;
    game->placed_ships = 0;
    game->player_hits = 0;
    game->opponent_hits = 0;
    game->player_shots_count = 0;
    game->opponent_shots_count = 0;
    game->is_shooting = false;
}

text game_get_title(struct game *game)
{
    char * font_path = "src/resources/fonts/the_california_hustle.ttf";

    text title;
    TTF_Font * font;
    font = TTF_OpenFont(font_path, 80);

    setTextTextureAndRect(game->renderer, 760, 60, "Seabattle 2.0", font, &title.texture, &title.rect);

    return title;
}

void game_quit(struct game * game)
{
    game->is_running = false;
}

int game_terminate(struct game * game)
{
    if (game == NULL) return 0;

    SDL_DestroyWindow(game->window);
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyTexture(game->title.texture);
    TTF_Quit();
    free(game);
    SDL_Quit();

    return 0;
}
