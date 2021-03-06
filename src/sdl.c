#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "include/sdl.h"

void setTextTextureAndRect(SDL_Renderer * renderer, int x, int y, char * text,
                           TTF_Font * font, SDL_Texture ** textTexture, SDL_Rect * textRect)
{
    int textWidth;
    int textHeight;

    SDL_Surface *surface;
    SDL_Color textColor = {255, 255, 255, 0};

    surface = TTF_RenderText_Blended(font, text, textColor);
    *textTexture = SDL_CreateTextureFromSurface(renderer, surface);

    textWidth = surface->w;
    textHeight = surface->h;

    SDL_FreeSurface(surface);

    textRect->x = x;
    textRect->y = y;
    textRect->w = textWidth;
    textRect->h = textHeight;
}