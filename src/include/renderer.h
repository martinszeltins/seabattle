#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <SDL2/SDL.h>

void renderer_draw(struct game * game);
void renderer_clear_screen(SDL_Renderer * renderer);
void renderer_draw_title(struct game * game);
void renderer_draw_grid_lines(struct game * game);

#endif
