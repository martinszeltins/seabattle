#include <SDL.h>
#include <time.h>
#include "include/game.h"
#include "include/input.h"
#include "include/window.h"
#include "include/renderer.h"

struct game * game_create()
{
    struct game *game = NULL;

    game = (struct game *)malloc(sizeof(struct game));
    bzero(game, sizeof(struct game));

    return game;
}

void game_run(struct game * game)
{
    game_init(game);

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

    game->is_running = true;
    game->window = window_create();
    game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);
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
    free(game);
    
    return 0;
}