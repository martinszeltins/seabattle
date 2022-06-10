#include <SDL2/SDL.h>
#include "include/game.h"
#include "include/renderer.h"

void renderer_draw(struct game * game)
{
    renderer_clear_screen(game->renderer);
    renderer_draw_title(game);

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