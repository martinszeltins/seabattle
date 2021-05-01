#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

void setTextTextureAndRect(SDL_Renderer *renderer, int x, int y, char *text, TTF_Font *font, SDL_Texture **textTexture, SDL_Rect *textRect);


/**
 * A program to demonstrate text rendering
 * using the SDL2 library.
 */
int main()
{
    TTF_Font * font;
    SDL_Event event;
    SDL_Rect titleRect;
    SDL_Window * window;
    SDL_Renderer * renderer;
    SDL_Texture * titleTexture;

    char * fontPath = "TheCaliforniaHustle.ttf";
    int quit = 0;

    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED , &window, &renderer);
 
    font = TTF_OpenFont(fontPath, 80);
    setTextTextureAndRect(renderer, 760, 60, "Sea Battle", font, &titleTexture, &titleRect);

    while (!quit)
    {
        while (SDL_PollEvent(&event) == 1) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(titleTexture);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

/**
 * Set the text's texture and rectangle
 */
void setTextTextureAndRect(SDL_Renderer *renderer, int x, int y, char *text, TTF_Font *font, SDL_Texture **textTexture, SDL_Rect *textRect)
{
    int textWidth;
    int textHeight;

    SDL_Surface * surface;
    SDL_Color textColor = { 255, 255, 255, 0 };

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