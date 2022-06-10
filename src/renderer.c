#include <SDL.h>
#include "include/game.h"
#include "include/renderer.h"

void renderer_draw(struct game * game)
{
    renderer_clear_screen(game->renderer);

    // Test render a rect
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 0);
        SDL_Rect test_rect = {0, 0, 100, 50};
        SDL_RenderFillRect(game->renderer, &test_rect);

    SDL_RenderPresent(game->renderer);

    SDL_Delay(1000 / 25);
}

void renderer_clear_screen(SDL_Renderer * renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
}