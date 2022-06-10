#ifndef __SDL_H__
#define __SDL_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void setTextTextureAndRect(SDL_Renderer * renderer, int x, int y, char * text,
                           TTF_Font * font, SDL_Texture ** textTexture, SDL_Rect * textRect);

#endif
