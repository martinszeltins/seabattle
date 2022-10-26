#ifndef __SDL_H__
#define __SDL_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void set_text_texture_and_rect(SDL_Renderer * renderer, int x, int y, char * text,
                           TTF_Font * font, SDL_Texture ** textTexture, SDL_Rect * textRect);

#endif
