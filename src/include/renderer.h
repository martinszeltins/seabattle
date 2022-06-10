#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <SDL2/SDL.h>

void renderer_draw(struct game * game);
void renderer_clear_screen(SDL_Renderer * renderer);

#endif
